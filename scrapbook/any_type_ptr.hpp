#pragma once

#include <memory>
#include <string>
#include <type_traits>
#include <any>
#include <utility>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <any>
#include <variant>
#include <optional>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <typeindex>
#include <typeinfo>
#include <type_traits>

namespace csl {
	// Type representing a None type
	struct NoneType {};

	enum class AnyTypeEnum : char {
		void_ = 'v',
		none_ = 'n',
		int_ = 'i',
		real_ = 'r',
		char_ = 'c',
		bool_ = 'b',
		string_ = 's'
	};

	struct AnyTypePtr {
		// Utils
		// Source: https://stackoverflow.com/questions/66863244/use-unique-ptr-to-wrap-and-unwrap-void
		template<class T>
		std::unique_ptr<void, void(*)(void*)> wrap_void_ptr(T* ptr) {
			return { ptr, [](void* ptr) { delete static_cast<T*>(ptr); } };
		}

		static std::vector<std::pair<std::type_index, AnyTypeEnum>> type_map;
		std::unique_ptr<void, void(*)(void*)> ptr{ wrap_void_ptr(new NoneType) };
		std::type_index type{ typeid(void) };
		AnyTypeEnum type_enum{ AnyTypeEnum::void_ };



		// Constructors
		AnyTypePtr() = default;
		AnyTypePtr(const AnyTypePtr& other) = default;
		AnyTypePtr(AnyTypePtr&& other) = default;
		AnyTypePtr& operator=(const AnyTypePtr& other) = default;
		AnyTypePtr& operator=(AnyTypePtr&& other) = default;

		template<typename T> requires (!std::is_same_v<std::decay_t<T>, AnyTypePtr>)
			&& (!std::is_same_v<std::decay_t<T>, std::type_index>)
			&& (!std::is_same_v<std::decay_t<T>, AnyTypeEnum>)
			&& (!std::is_same_v<std::decay_t<T>, std::type_info>)
			AnyTypePtr(T&& any_val) {
			construct(std::forward<T>(any_val));
		}

		template<typename T> requires (std::is_same_v<std::decay_t<T>, AnyTypePtr>)
			&& (!std::is_same_v<std::decay_t<T>, std::type_index>)
			&& (!std::is_same_v<std::decay_t<T>, AnyTypeEnum>)
			&& (!std::is_same_v<std::decay_t<T>, std::type_info>)
			AnyTypePtr(T&& any_type_ptr) {
			type = any_type_ptr.type;
			type_enum = any_type_ptr.type_enum;
			ptr = std::move(any_type_ptr.ptr);
		}

		void construct(auto&& arg) {
			type = std::type_index(typeid(decltype(arg)));
			auto found = std::find_if(type_map.begin(), type_map.end(), [this](auto&& pair) { return pair.first == type; });
			if (found == type_map.end()) {
				std::cerr << "[WARNING] Cannot construct an AnyTypePtr with an unsupported type." << std::endl;
				return;
			}
			else {
				type_enum = found->second;
				//ptr = new std::decay_t<decltype(arg)>(std::forward<decltype(arg)>(arg));
				ptr = wrap_void_ptr(new std::decay_t<decltype(arg)>(std::forward<decltype(arg)>(arg)));
			}
		}

		template<AnyTypeEnum ViperT>
		constexpr bool is() const {
			return type_enum == ViperT;
		}

		constexpr bool is_void() const {
			return type_enum == AnyTypeEnum::void_;
		}

		constexpr bool is_none() const {
			return type_enum == AnyTypeEnum::none_;
		}

		constexpr bool has_value() const {
			return type_enum != AnyTypeEnum::void_;
		}

		template<AnyTypeEnum ViperT>
		auto get() const {
			if constexpr (ViperT == AnyTypeEnum::void_) {
				return {};
			}
			else if constexpr (ViperT == AnyTypeEnum::int_) {
				return *static_cast<int*>(ptr.get());
			}
			else if constexpr (ViperT == AnyTypeEnum::real_) {
				return *static_cast<float*>(ptr.get());
			}
			else if constexpr (ViperT == AnyTypeEnum::char_) {
				return *static_cast<char*>(ptr.get());
			}
			else if constexpr (ViperT == AnyTypeEnum::bool_) {
				return *static_cast<bool*>(ptr.get());
			}
			else if constexpr (ViperT == AnyTypeEnum::string_) {
				return *static_cast<std::string*>(ptr.get());
			}
			else {
				return {};
			}
		}

		void visit(const std::function<void(AnyTypePtr const&)>& func) const {
			func(*this);
		}


		//Case: void visitor with no arguments.
		void poly_visit(const auto& visitor) const requires std::is_same_v<void, typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type>
		{
			std::function<void(AnyTypePtr const&)> func(visitor);
			func(*this);
		}

		//Case: non-void visitor with no arguments.
		auto poly_visit(const auto& visitor) const -> typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type
			requires (!std::is_same_v<void, typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type>)
		{
			std::function<typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type(AnyTypePtr const&)> func(visitor);
			return func(*this);
		}

		// Case void visitor with arguments.
		template<typename ... ArgTs>
		void poly_visit(const auto& visitor, ArgTs&&... args) const requires std::is_same_v<void, typename std::invoke_result<decltype(visitor), AnyTypePtr const&, ArgTs...>::type>
		{
			std::function<void(AnyTypePtr const&, ArgTs...)> func(visitor);
			func(*this, std::forward<ArgTs>(args)...); // Ignore func definition not found, intellisense does not recognize func as a functor object.
		}

		// Case non-void visitor with arguments.
		template<typename ... ArgTs>
		auto poly_visit(const auto& visitor, ArgTs&&... args) const -> typename std::invoke_result<decltype(visitor), const AnyTypePtr&, ArgTs...>::type
			requires (!std::is_same_v<void, typename std::invoke_result<decltype(visitor), const AnyTypePtr&, ArgTs...>::type>)
		{
			using return_type = typename std::invoke_result<decltype(visitor), const AnyTypePtr&, ArgTs...>::type;
			std::function<return_type(AnyTypePtr const&, ArgTs...)> func(visitor);
			return func(*this, std::forward<ArgTs>(args)...);
		}

		//Case: no arguments, non-void return type or void return type(Version without auto dedeuction of return type)
		template<typename RT>
		RT poly_visit(const auto& visitor) const {
			if constexpr (std::is_same_v<RT, void>) {
				std::function<RT(AnyTypePtr const&)> func(visitor);
				func(*this);
			}
			else {
				std::function<RT(AnyTypePtr const&)> func(visitor);
				return func(*this);
			}
		}

		// Case: arguments (Version without auto dedeuction of return type)

		template<typename RT, typename ... ArgTs>
		RT poly_visit(const auto& visitor, ArgTs&&... args) const {
			if constexpr (std::is_same_v<RT, void>) {
				std::function<RT(AnyTypePtr const&, ArgTs...)> func(visitor);
				func(*this, std::forward<ArgTs>(args)...);
			}
			else {
				std::function<RT(AnyTypePtr const&, ArgTs...)> func(visitor);
				return func(*this, std::forward<ArgTs>(args)...);
			}
		}

		// How can we get away with specializing away the return type ?


		//template<typename RT>
		//RT poly_visit(const auto& visitor) const {
		//	return PolyVisitHelper<RT>::invoke(visitor, *this);
		//}

		// Case: arguments (Version with auto dedeuction of return type)
		//template <typename RT, typename... ArgTs>
		//RT poly_visit(const auto& visitor, ArgTs&&... args) const {
		//	return PolyVisitHelper<RT, ArgTs...>::invoke(visitor, *this, std::forward<ArgTs>(args)...);
		//}

		//// Case:  multiple arguments, non-void return type or void return type
		//template<typename RT, typename ArgT,typename... ArgTs> 
		//auto poly_visit(const auto& visitor, ArgT&& arg, ArgTs&&... args) const {

		//	if constexpr (std::is_same_v<RT, void>) {
		//		std::function<RT(AnyTypePtr const&, ArgT, ArgTs...)> funct(visitor);
		//		funct(*this, std::forward<ArgT>(arg), std::forward<ArgTs>(args)...);
		//	}
		//	else {
		//		std::function<RT(AnyTypePtr const&, ArgT, ArgTs...)> funct(visitor);
		//		return funct(*this, std::forward<ArgT>(arg), std::forward<ArgTs>(args)...);
		//	}
		//}


		//template<typename... ArgTs>
		//auto visit(const std::function<void(AnyTypePtr const&, ArgTs...)>& func,ArgTs&&... args) const {
		//	if (type_enum == AnyTypeEnum::void_) {
		//		func(*this,args...);
		//	}
		//	else if (type_enum == AnyTypeEnum::int_) {
		//		func(*this,args...);
		//	}
		//	else if (type_enum == AnyTypeEnum::real_) {
		//		func(*this, args...);
		//	}
		//	else if (type_enum == AnyTypeEnum::char_) {
		//		func(*this, args...);
		//	}
		//	else if (type_enum == AnyTypeEnum::bool_) {
		//		func(*this, args...);
		//	}
		//	else if (type_enum == AnyTypeEnum::string_) {
		//		func(*this, args...);
		//	}
		//	else {
		//		func(*this, args...);
		//	}
		//
		//}
	};


	std::vector<std::pair<std::type_index, AnyTypeEnum>> AnyTypePtr::type_map{
		{std::type_index(typeid(void)), AnyTypeEnum::void_},
		{std::type_index(typeid(NoneType)), AnyTypeEnum::none_},
		{std::type_index(typeid(int)), AnyTypeEnum::int_},
		{std::type_index(typeid(float)), AnyTypeEnum::real_},
		{std::type_index(typeid(char)), AnyTypeEnum::char_},
		{std::type_index(typeid(bool)), AnyTypeEnum::bool_},
		{std::type_index(typeid(std::string)), AnyTypeEnum::string_}
	};
} // namespace csl