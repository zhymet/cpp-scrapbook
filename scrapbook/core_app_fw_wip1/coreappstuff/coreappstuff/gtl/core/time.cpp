#include "time.hpp"

namespace gtl::time {

    bool gtlTimeframe::is_paused() {
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

    gtlTimeframe::micro_duration gtlTimeframe::pause() {
        return pause_points.emplace_back(steady_clock::now()) - epoch_point;
    }


    [[nodiscard]] gtlTimeframe::micro_duration gtlTimeframe::elapsed_time() const {
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

    [[nodiscard]] gtlTimeframe::micro_duration gtlTimeframe::total_time() const {
        // TODO: implement this
        return std::chrono::steady_clock::now() - epoch_point;
    }

    [[nodiscard]] gtlTimeframe::micro_duration gtlTimeframe::running_time() const {
        return std::chrono::steady_clock::now() - epoch_point;
    }

    gtlTimeframe::micro_duration gtlTimeframe::reset() {
        auto ret_duration = elapsed_time();
        reset_point = std::chrono::steady_clock::now();
        was_paused = false;
        return ret_duration;
    }


    gtlClock::micro_duration gtlClock::elapsed_time() const {
        return std::chrono::steady_clock::now() - reset_point;
    }

    gtlClock::micro_duration gtlClock::restart() {
        auto ret_duration = elapsed_time();
        reset_point = std::chrono::steady_clock::now();
        return ret_duration;
    }
}


namespace timex {

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



    StdMicrosecondsD Timeframe::start() {
        //assert(!is_processing_ && "timex::Timeframe | start() called but the frame step was already started.");
        accumulator_ += timer_.reset();
        accumulator_ += leftover_;
        is_processing_ = true;
        return accumulator_; // Time from end of last step
    }

    [[nodiscard]] bool Timeframe::isUpdating() const {
        //assert(is_processing_ && "timex::Timeframe | isUpdating() called before a timeframe was ever started.");
        // Did we NOT accumulate enough time in the previous step?
        // true -> No, we need to continue stepping.
        // false -> Yes, the time frame has occurred for delta time.
        return accumulator_.count() >= delta_.count();
    }

    StdMicrosecondsD Timeframe::tryFinish() {
        assert(is_processing_ && "timex::Timeframe | tryFinish() called before a timeframe was ever started.");
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


    [[nodiscard]] bool Timeframe::isFinished() const {
        return is_finished_;
    }


}