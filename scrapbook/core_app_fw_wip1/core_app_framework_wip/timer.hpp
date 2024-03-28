///
/// <@author> Anton Yashchenko (bigteeny.com)
/// <@date> 8/25/2020.
/// <@file> timer.hpp
/// <@module> gtl::timex
/// <@classes> Timer, Timecycle, Timeframe
/// <@brief> Utility classes for timing events or executing events within an alloted timeframe.

#ifndef GTL_HEADGUARD_TIMEX_TIMER_HPP
#define GTL_HEADGUARD_TIMER_TIMER_HPP

//#include <utility>
//#include <cmath>
#include <chrono> // std::chrono::time_point, std::chrono::steady_clock
#include <cassert>


namespace gtl {
    // std::chrono typedefs
    using SysClock = std::chrono::system_clock;
    using StdClock = std::chrono::steady_clock;
    template<typename ...T> using StdDuration = std::chrono::duration<T...>;
    template<typename ...T> using StdTimePoint = std::chrono::time_point<T...>;
    using StdNanoseconds = std::chrono::nanoseconds;
    using StdMicroseconds = std::chrono::microseconds;
    using StdMicrosecondsD = StdDuration<double, std::micro>;

    /// <@class:Timer>
    /// <@brief:> General purpose clock/timer, stores time as double in microseconds.
    class Timer {
        StdTimePoint<StdClock> reset_point; // Time of last reset, in microseconds.
    public:
        Timer() : reset_point(StdClock::now()) {}
        [[nodiscard]] StdMicrosecondsD elapsedTime() const;
        [[nodiscard]] StdMicrosecondsD lastResetPoint() const;
        StdMicrosecondsD reset();
        Timer& restart();
    };

    /// <@class:Timecycle>
    /// <@brief> Used to lock a section of code to only occur only for an allotted period of time.
    ///           Executes the code in steps which report leftover when attempting to finish the timeframe.
    ///           Reported negative time indicates amount required to finish the previous step (delay).
    ///           Positive indicates extra time remaining after completing the previous step.
    /// <@example> Use to lock a game's physics update loop to 60 fps.
    /* while(program_running) {
     *      bool is_rendered{false};
     *      StdMicrosecondsD physics_delay;
     *      auto time_from_prev_physics_step_ = physics_timeframe.start();
     *      while(physics_timeframe.is_updating()){
     *          // Do all the physics stuff here
     *
     *          physics_step_delay = physics_timeframe.tryFinish();
     *          if(physics_timeframe.isFinished()) {
     *              // Do stuff in response to completing the timeframe using the leftover time.
     *              is_rendered = false;
     *          }
     *          else {
     *              // Do stuff in response to not completing the step within the allocated timeframe.
     *              break;
     *          }
     *      } // This loop will exit once delta time elapsed.
     *
     *      // Continue doing other things
     *
     *      // Wont happen until the time frame is finished
     *      if(physics_timeframe.isFinished()){
     *          if(!is_rendered){
     *              // Render the stuff
     *              is_rendered = true;
     *          }
     *          else {
     *              // Already rendered... do other stuff instead
     *          }
     *      }
     *
     *
     *  }
     *
     * */
    class Timecycle {
        Timer timer_;
        StdMicrosecondsD delta_;            // Time per cycle of this frame.
        StdMicrosecondsD accumulator_;      // Time accumulated from end of previous step
        StdMicrosecondsD leftover_;         // Left-over time from previous step
                                            // negative values indicate a delay time.
        bool is_processing_;
        bool is_finished_;
    public:
        explicit Timecycle(double microseconds_per_frame)
            : timer_()
            , delta_(microseconds_per_frame)
            , accumulator_(0.0)
            , leftover_(0.0)
            , is_processing_(false)
            , is_finished_(false) {
        }
        StdMicrosecondsD start();
        StdMicrosecondsD tryFinish();
        [[nodiscard]] bool isUpdating() const;
        [[nodiscard]] bool isFinished() const;
    };

    /// <@class:Timecycle>
    /// <@brief: similar to the timecycle class but is able to pause and unpause.
    class Timeframe {
    public:
        using steady_clock = std::chrono::steady_clock;
        using steady_timepoint = std::chrono::time_point<std::chrono::steady_clock>;
        using micro_duration = std::chrono::duration<double, std::micro>;

    private:
        steady_timepoint epoch_point;                 ///< Time of construction, in microseconds.>
        steady_timepoint reset_point;                 ///< Time of last reset, in microseconds.>
        std::vector<steady_timepoint> pause_points;   ///< Pause/Unpause points always in that order.>
        bool was_paused;                  ///< True if the clock was paused or unpause at any point.>

    public:
        Timeframe()
            : epoch_point(steady_clock::now()), reset_point(steady_clock::now()), pause_points(),
            was_paused(false) {
        }

        micro_duration pause();

        micro_duration reset();

        bool is_paused();

        [[nodiscard]] micro_duration elapsed_time() const;

        [[nodiscard]] micro_duration total_time() const;

        [[nodiscard]] micro_duration running_time() const;
    }; /// <@endclass:gtlTimecycle>


    [[nodiscard]] StdMicrosecondsD Timer::elapsedTime() const {
        return StdClock::now() - reset_point;
    };

    [[nodiscard]] StdMicrosecondsD Timer::lastResetPoint() const {
        return reset_point.time_since_epoch();
    };

    StdMicrosecondsD Timer::reset() {
        auto ret_duration = elapsedTime();
        reset_point = StdClock::now();
        return ret_duration;
    }

    Timer& Timer::restart() {
        reset_point = StdClock::now();
        return *this;
    }

    StdMicrosecondsD Timecycle::start() {
        assert(!is_processing_ && "timex::Timecycle | start() called but the frame step was already started.");
        accumulator_ += timer_.reset();
        accumulator_ += leftover_;
        is_processing_ = true;
        return accumulator_; // Time from end of last step
    }

    [[nodiscard]] bool Timecycle::isUpdating() const {
        assert(is_processing_ && "timex::Timecycle | isUpdating() called before a timeframe was ever started.");
        // Did we NOT accumulate enough time in the previous step?
        // true -> No, we need to continue stepping.
        // false -> Yes, the time frame has occurred for delta time.
        return accumulator_.count() >= delta_.count();
    }

    StdMicrosecondsD Timecycle::tryFinish() {
        assert(is_processing_ && "timex::Timecycle | tryFinish() called before a timeframe was ever started.");
        leftover_ = accumulator_ - delta_;
        accumulator_ = StdMicrosecondsD::zero();

        // Is another frame step required ? Yes by default.
        // If there is partial negative extra frame time ?
        // Then we need to perform more updates to finish this frame.
        // false -> We need to update more to finish this frame.
        // true -> updating finished, continue to next frame.
        is_finished_ = !std::signbit(leftover_.count());

        is_processing_ = !is_finished_;

        return leftover_;
    }


    [[nodiscard]] bool Timecycle::isFinished() const {
        return is_finished_;
    }


    bool Timeframe::is_paused() {
        if (!was_paused) { // We never paused.
            return false;
        }
        else {
            if (pause_points.size() % 2) { // We are currently unpaused
                return false;
            }
            else {
                return false; // We are currently paused.
            }
        }
    }

    Timeframe::micro_duration Timeframe::pause() {
        return pause_points.emplace_back(steady_clock::now()) - epoch_point;
    }


    [[nodiscard]] Timeframe::micro_duration Timeframe::elapsed_time() const {
        // If we never paused, return time since last reset point.
        if (!was_paused)
            return std::chrono::steady_clock::now() - reset_point;
        else { // We paused and/or unpaused at some point since the last reset point.
            if (pause_points.size() == 1u) // Single pause point case
                return pause_points.back() - reset_point;
            else if (pause_points.size() % 2) { // We are currently unpaused.
                // Assume pause_points_ vector is a non-zero divisible by 2 size, with at least one pause/unpause pair.
                // For each pause/unpause pair:
                // 1. Get the difference from the pause point to unpause point to get the duration spent paused.
                // 2. Add result duration value to the total accumulated paused time duration.
                micro_duration total_pause_duration = micro_duration::zero();
                auto it_p = pause_points.begin();
                for (auto it_up = pause_points.begin() + 1; it_up != pause_points.end(); it_p + 2, it_up + 2) {
                    auto paused_duration = (*it_up) - (*it_p);
                    total_pause_duration += paused_duration;
                }
                // Subtract the accumulated paused duration from the current elapsed time, and return.
                return (std::chrono::steady_clock::now() - reset_point) - total_pause_duration;
            }
            else { // We are currently paused
                if (pause_points.size() == 1u) // Single pause point case
                    return pause_points.back() - reset_point;
                else {
                    // Assume pause_points_ vector is a non-zero odd size, with at least one pause/unpause pair
                    micro_duration total_pause_duration = micro_duration::zero();
                    auto it_p = pause_points.begin();
                    for (auto it_up = pause_points.begin() + 1; it_up != pause_points.end(); it_p + 2, it_up + 2) {
                        auto paused_duration = (*it_up) - (*it_p);
                        total_pause_duration += paused_duration;
                    } // Upon exit it_p is equal to the iterator to the last pause. (pause_points.end() - 1).

                    // Return the last pause point as the now() parameter for the elapsed time.
                    return (*it_p - reset_point) - total_pause_duration;
                }
            }
        }
    }

    [[nodiscard]] Timeframe::micro_duration Timeframe::total_time() const {
        // TODO: implement this
        return std::chrono::steady_clock::now() - epoch_point;
    }

    [[nodiscard]] Timeframe::micro_duration Timeframe::running_time() const {
        return std::chrono::steady_clock::now() - epoch_point;
    }

    Timeframe::micro_duration Timeframe::reset() {
        auto ret_duration = elapsed_time();
        reset_point = std::chrono::steady_clock::now();
        was_paused = false;
        return ret_duration;
    }

}

#endif //GTL_HEADGUARD_TIMEX_TIMER_HPP
