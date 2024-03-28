#ifndef NTONESDK_TIME_HPP
#define NTONESDK_TIME_HPP

#include <vector> // std::vector
#include <chrono> // std::chrono::time_point,
// std::chrono::steady_clock ,
// std::chrono::duration<double, std::micro>.

namespace gtl::time {
    /// <@class:gtlTimeframe.>
    class gtlTimeframe {
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
        gtlTimeframe()
            : epoch_point(steady_clock::now()), reset_point(steady_clock::now()), pause_points(),
            was_paused(false) {
        }

        micro_duration pause();

        micro_duration reset();

        bool is_paused();

        [[nodiscard]] micro_duration elapsed_time() const;

        [[nodiscard]] micro_duration total_time() const;

        [[nodiscard]] micro_duration running_time() const;
    }; /// <@endclass:gtlTimeframe>


    /// <@class:gtlClock.>
    class gtlClock {
    public:
        using steady_clock = std::chrono::steady_clock;
        using steady_timepoint = std::chrono::time_point<std::chrono::steady_clock>;
        using micro_duration = std::chrono::duration<double, std::micro>;
    private:
        steady_timepoint epoch_point; ///< Time of construction, in microseconds
        steady_timepoint reset_point; ///< Time of last reset, in microseconds
    public:
        explicit gtlClock(steady_timepoint initial_timepoint)
            : epoch_point(initial_timepoint), reset_point(initial_timepoint) {
        }

        gtlClock() : epoch_point(steady_clock::now())
            , reset_point(steady_clock::now()) {
        }

        [[nodiscard]] micro_duration elapsed_time() const;

        micro_duration restart();
    };
} /// <endnamespace:gtlClock.>

#endif //NTONESDK_TIME_HPP


//
// Created by zbook15 on 8/25/2020.
//

#ifndef PPP_TIMEX_HPP
#define PPP_TIMEX_HPP
#include <utility>
#include <cmath>
#include <chrono> // std::chrono::time_point, std::chrono::steady_clock
#include <cassert>

template<typename T>
static consteval decltype(auto) assert_consteval(T&& eval) {
    return std::forward<T>(eval);
}

namespace timex {
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

    /// <@class:Timeframe>
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
    class Timeframe {
        Timer timer_;
        StdMicrosecondsD delta_;         // Time per cycle of this frame.
        StdMicrosecondsD accumulator_;   // Time accumulated from end of previous step
        StdMicrosecondsD leftover_;      // Left-over time from previous step
                                        // negative values indicate a delay time.
        bool is_processing_;
        bool is_finished_;
    public:
        explicit Timeframe(double microseconds_per_frame)
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
}

//// Concept that satisfies requirements of a standard library clock
//template<typename T>
//concept StdChronoClock_ = requires ( T t){
//    // 1. Has a typedef named "duration" of type "std::chrono::nanoseconds".
//    requires std::same_as<typename T::duration,StdNanoseconds>;
//    // 2. Has a typedef dependant on "duration" named "rep" of type "duration::rep".
//    requires std::same_as<typename T::rep,typename T::duration::rep>;
//    // 3. Has a typedef dependant on "duration" named "period" of type "duration::period".
//    requires std::same_as<typename T::period,typename T::duration::period>;
//    // 4. Has a typedef dependant on "decltype(*this)" and "duration" named time_point
//    //    of type std::chrono::time_point<decltype(*this)>,duration>.
//    requires std::same_as<typename T::time_point,StdTimePoint<T,typename T::duration>>;
//    // 5. Has a static constexpr member "is_steady" of type "bool".
//    { assert_consteval(T::is_steady) } -> std::same_as<const bool &>;
//    // 6. Has a static noexcept method named "now" which returns a "T::time_point" type
//    { T::now() } -> std::same_as<typename T::time_point>;
//    // 7. Time point should be able to accept StdChronoClock_ as template parameter
//    { StdTimePoint<T>{}} -> std::same_as<StdTimePoint<T>>;
//};
//
////    struct TEST_StdChronoClock {
////        typedef std::chrono::nanoseconds			duration;
////        typedef duration::rep					rep;
////        typedef duration::period					period;
////        typedef std::chrono::time_point<TEST_StdChronoClock, duration> 	time_point;
////        static constexpr bool is_steady = true;
////        static time_point now(){}
////    };
//
//static_assert(StdChronoClock_<StdClock>);
//static_assert(StdChronoClock_<SysClock>);
////static_assert(StdChronoClock_<TEST_StdChronoClock>); // TODO: Shouldn't satisfy

#endif //PPP_TIME_HPP
