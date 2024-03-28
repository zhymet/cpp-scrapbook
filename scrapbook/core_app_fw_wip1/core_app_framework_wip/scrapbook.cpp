//template<typename T>
//static consteval decltype(auto) assert_consteval(T&& eval) {
//    return std::forward<T>(eval);
//}


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