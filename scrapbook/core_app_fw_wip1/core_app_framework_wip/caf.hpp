#pragma once
#include "requires.hpp"

#define CAF_VERSION_MAJOR 1
#define CAF_VERSION_MINOR 0
#define CAF_VERSION_PATCH 0
#define CAF_OPENGL_TARGET_VERSION_MAJOR 3
#define CAF_OPENGL_TARGET_VERSION_MINOR 3

#include "caf_debug.hpp"
#include "caf_resource_manager.hpp"


//struct $Component_type {
//    int a;
//    int* c;
//    const int* f;
//    constexpr $Component_type() = default;
//};
//
//__CASET concept Component_ = requires (T t) {
//    requires std::is_trivial_v<T>;
//    requires std::is_standard_layout_v<T>;
//    requires not std::has_virtual_destructor_v<T>;
//    requires not std::is_abstract_v<T>;
//    requires not std::is_polymorphic_v<T>;
//    requires not std::is_empty_v<T>;
//};
//
//static_assert(Component_<$Component_type>);
//
//class $Subsystem_type {
//    bool is_on_;
//    bool is_running_;
//public:
//    [[nodiscard]] const bool& isInit() const { return is_on_; }
//    [[nodiscard]] const bool& isOn() const { return is_on_; }
//    [[nodiscard]] const bool& isRunning() const { return is_running_; }
//
//    [[nodiscard]] bool init() { return true; }
//    [[nodiscard]] bool start() { return true; }
//    [[nodiscard]] bool execute() { return true; }
//    [[nodiscard]] bool finish() { return true; }
//    [[nodiscard]] bool terminate() { return true; }
//
//    constexpr $Subsystem_type(const $Subsystem_type& other) = delete;
//    constexpr const $Subsystem_type& operator=(const $Subsystem_type&) = delete;
//
//};
//
//template<typename T>
//concept Subsystem_ = requires (T t) {
//    // 1. Cannot be moved, copied or swapped.
//    requires gtl::req::NonCopyable_<T>;
//
//    { t.isInit() } -> std::same_as<const bool&>;
//    { t.isOn() } -> std::same_as<const bool&>;
//    { t.isRunning() } -> std::same_as<const bool&>;
//
//    { t.init() } -> std::same_as<bool>;
//    { t.start() } -> std::same_as<bool>;
//    { t.execute() } -> std::same_as<bool>;
//    { t.finish() } -> std::same_as<bool>;
//    { t.terminate() } -> std::same_as<bool>;
//};
//
//static_assert(Subsystem_<$Subsystem_type>);
//
//class $System_type {
//    bool is_on_;
//    bool is_running_;
//public:
//    [[nodiscard]] const bool& isInit() const { return is_on_; }
//    [[nodiscard]] const bool& isOn() const { return is_on_; }
//    [[nodiscard]] const bool& isRunning() const { return is_running_; }
//
//    [[nodiscard]] bool init() { return true; }
//    [[nodiscard]] bool start() { return true; }
//    [[nodiscard]] bool execute() { return true; }
//    [[nodiscard]] bool finish() { return true; }
//    [[nodiscard]] bool terminate() { return true; }
//
//    constexpr $System_type(const $System_type& other) = delete;
//    constexpr const $System_type& operator=(const $System_type&) = delete;
//
//    constexpr $System_type($System_type&& other) = delete;
//    constexpr $System_type& operator=($System_type&&) = delete;
//};
//
//template<typename T>
//concept System_ = requires (T t) {
//    // 1. Cannot be moved, copied or swapped.
//    requires gtl::req::Singular_<T>;
//
//    { t.isInit() } -> std::same_as<const bool&>;
//    { t.isOn() } -> std::same_as<const bool&>;
//    { t.isRunning() } -> std::same_as<const bool&>;
//
//    { t.init() } -> std::same_as<bool>;
//    { t.start() } -> std::same_as<bool>;
//    { t.execute() } -> std::same_as<bool>;
//    { t.finish() } -> std::same_as<bool>;
//    { t.terminate() } -> std::same_as<bool>;
//};
//
//static_assert(System_<$System_type>);
//
//namespace caf {
//    /// <summary>
//    /// Systems
//    /// </summary>
//    class Subsystem {
//        bool is_on_;
//        bool is_running_;
//    public:
//        [[nodiscard]] const bool& isInit() const { return is_on_; }
//        [[nodiscard]] const bool& isOn() const { return is_on_; }
//        [[nodiscard]] const bool& isRunning() const { return is_running_; }
//
//        [[nodiscard]] bool init() { return true; }
//        [[nodiscard]] bool start() { return true; }
//        [[nodiscard]] bool execute() { return true; }
//        [[nodiscard]] bool finish() { return true; }
//        [[nodiscard]] bool terminate() { return true; }
//
//        Subsystem() = default;
//        constexpr Subsystem(const Subsystem& other) = delete;
//        constexpr const Subsystem& operator=(const Subsystem&) = delete;
//
//        constexpr Subsystem(Subsystem&& other) = delete;
//        constexpr Subsystem& operator=(Subsystem&&) = delete;
//    };
//
//    class Engine {
//        bool is_on_;
//        bool is_running_;
//    public:
//        [[nodiscard]] const bool& isInit() const { return is_on_; }
//        [[nodiscard]] const bool& isOn() const { return is_on_; }
//        [[nodiscard]] const bool& isRunning() const { return is_running_; }
//
//        [[nodiscard]] bool init() { return true; }
//        [[nodiscard]] bool start() { return true; }
//        [[nodiscard]] bool execute() { return true; }
//        [[nodiscard]] bool finish() { return true; }
//        [[nodiscard]] bool terminate() { return true; }
//
//        Engine() = default;
//        constexpr Engine(const Engine& other) = delete;
//        constexpr const Engine& operator=(const Engine&) = delete;
//
//        constexpr Engine(Engine&& other) = delete;
//        constexpr Engine& operator=(Engine&&) = delete;
//    };
//}
//static_assert(EngineSystem<EngineTypePack>() != nullptr);