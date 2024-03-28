#pragma once
#include "pch.h"
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

// Type representing an undefined type
#define undefined void
// Type representing a None type
struct NoneT {};
// Literal Types
// int, uint, real,bit, byte, str

enum CandType : std::size_t {
	undefined_ = 'v',
	none_ = 'n',
	int_ = 'i',
	uint_ = 'u',
	real_ = 'r',
	bit_ = 'b',
	byte_ = 'c',
	string_ = 's',
	method_ = 'm',
	object_ = 'c',
};






template<typename T,std::size_t Indentity>
struct TypeIdentity {
	using type = T;
	static constexpr std::size_t identity = Indentity;
	const std::size_t id = Indentity;
};

template<typename... Ts>
struct TypeIdentityIndex {
	using type_identities_t = std::tuple<Ts...>;
	static constexpr type_identities_t type_identities{};

	std::size_t index;
	// WARNING: C++17 or above required
	template <size_t I = 0, typename... Ts>
	static constexpr void hasTypeIdentity(std::tuple<Ts...> tup, std::size_t index, bool& is_found)
	{
		// If we have iterated through all elements
		if
			constexpr (I == sizeof...(Ts))
		{
			// Last case, if nothing is left to
			// iterate, then exit the function
			return;
		}
		else {
			// Acces the tuple and go to next element
			if (get<I>(tup).id == index) {
				is_found = true;
			}

			// Going for next element.
			hasTypeIdentity<I + 1>(tup, index, is_found);
		}
	}

	// find the identity with the same index as the given index
	constexpr auto is_valid() const {
		bool is_found = false;
		hasTypeIdentity(type_identities, index, is_found);
		return is_found;
	}
};

using my_types = TypeIdentityIndex<
	TypeIdentity<undefined, CandType::undefined_>,//void
	TypeIdentity<NoneT, CandType::none_>,
	TypeIdentity<int, CandType::int_>,
	TypeIdentity<float, CandType::real_>,
	TypeIdentity<bool, CandType::bit_>,
	TypeIdentity<char, CandType::byte_>,
	TypeIdentity<std::string, string_>>;

my_types type_identity_index{ 0 };


// Source: https://www.perry.cz/clanky/functions.html
template<int... Is> struct seq {};

template<int N, int... Is>
struct gen_seq2 : gen_seq2 < N - 1, N - 1, Is... > {};

template<int ...S>
struct gen_seq2 < 0, S... > { typedef seq<S...> type; };

struct AnyTypePtr;//fwd decl

//class AnyVisitorFunctionBase
//{
//public:
//	virtual void call(AnyTypePtr const& any_ptr) = 0;
//};
//
//// Source:https://www.perry.cz/clanky/functions.html
//template <typename R, typename ...ARGS>
//class AnyVisitorFunction : public AnyVisitorFunctionBase
//{
//public:
//	R retVal;
//	std::tuple<ARGS...> args;
//
//	std::function<R(AnyTypePtr const& ,ARGS...)> f;
//
//	AnyVisitorFunction() = default;
//	AnyVisitorFunction(std::function<R(AnyTypePtr const&, ARGS...)> f) : f(f) {}
//
//	virtual void call(AnyTypePtr const& any_ptr)
//	{
//		this->retVal = this->callFunc(any_ptr,typename gen_seq2<sizeof...(ARGS)>::type());
//	};
//
//	template<int ...S>
//	R callFunc(AnyTypePtr const& any_ptr,seq<S...>)
//	{
//		return f((any_ptr,std::get<S>(args)) ...);
//	}
//};

//auto test(const AnyTypePtr & any_ptr, int i) {
//	return i;
//}
//
////AnyVisitorFunction<int, int> test2;
//auto test3(){
//	test2.f = test;
//	test2.f = [](const AnyTypePtr& any_ptr, int i) {return i; };
//
//}

//
//struct AnyTypePtr {
//	// Utils
//	// Source: https://stackoverflow.com/questions/66863244/use-unique-ptr-to-wrap-and-unwrap-void
//	template<class T>
//	std::unique_ptr<void, void(*)(void*)> wrap_void_ptr(T* ptr) {
//		return { ptr, [](void* ptr) { delete static_cast<T*>(ptr); } };
//	}
//
//	static std::vector<std::type_index> type_map;
//	std::unique_ptr<void, void(*)(void*)> ptr{ wrap_void_ptr(new NoneT) };
//	std::type_index type{typeid(NoneT)};
//
//	// Constructors
//	AnyTypePtr() = default;
//	AnyTypePtr(const AnyTypePtr& other) {
//		if(other.is<int>()) {
//			ptr = wrap_void_ptr(new int(*other.getp<int>()));
//		}
//		else if (other.is<float>()) {
//			ptr = wrap_void_ptr(new float(*other.getp<float>()));
//		}
//		else if (other.is<char>()) {
//			ptr = wrap_void_ptr(new char(*other.getp<char>()));
//		}
//		else if (other.is<bool>()) {
//			ptr = wrap_void_ptr(new bool(*other.getp<bool>()));
//		}
//		else if (other.is<std::string>()) {
//			ptr = wrap_void_ptr(new std::string(*other.getp<std::string>()));
//		}
//		else if (other.is<std::vector<AnyTypePtr>>()) {
//			ptr = wrap_void_ptr(new std::vector<AnyTypePtr>(*other.getp<std::vector<AnyTypePtr>>()));
//		}
//		else {
//			std::cerr << "[WARNING] Cannot copy construct an AnyTypePtr with an unsupported type." << std::endl;
//		})
//
//	};
//	AnyTypePtr(AnyTypePtr&& other) = default;
//	AnyTypePtr& operator=(const AnyTypePtr& other) = default;
//	AnyTypePtr& operator=(AnyTypePtr&& other) = default;
//
//	template<typename T> requires (!std::is_same_v<std::decay_t<T>, AnyTypePtr>) 
//		&& (!std::is_same_v<std::decay_t<T>, std::type_index>) 
//		&& (!std::is_same_v<std::decay_t<T>, ViperType>)
//		&& (!std::is_same_v<std::decay_t<T>, std::type_info>)
//	AnyTypePtr(T&& any_val) {
//		construct(std::forward<T>(any_val));
//	}
//
//	template<typename T> requires (std::is_same_v<std::decay_t<T>, AnyTypePtr>) 
//		&& (!std::is_same_v<std::decay_t<T>, std::type_index>) 
//		&& (!std::is_same_v<std::decay_t<T>, ViperType>)
//		&& (!std::is_same_v<std::decay_t<T>, std::type_info>)
//	AnyTypePtr(T&& any_type_ptr) {
//		type = any_type_ptr.type;
//		ptr = std::move(any_type_ptr.ptr);
//	}
//	
//	void construct(auto&& arg) {
//		type = std::type_index(typeid(decltype(arg)));
//		auto found = std::find_if(type_map.begin(), type_map.end(), [this](auto&& val) { return val == type; });
//		if (found == type_map.end()) {
//			std::cerr << "[WARNING] Cannot construct an AnyTypePtr with an unsupported type." << std::endl;
//			return;
//		}
//		else {
//			//ptr = new std::decay_t<decltype(arg)>(std::forward<decltype(arg)>(arg)); if using regular void*
//			ptr = wrap_void_ptr(new std::decay_t<decltype(arg)>(std::forward<decltype(arg)>(arg)));
//		}
//	}
//
//	template<typename T>
//	constexpr bool is() const {
//		return type == typeid(T);
//	}
//
//
//	template<typename T>
//	auto getp() {
//		return static_cast<T*>(ptr.get());
//	}
//
//
//	void visit(const std::function<void(AnyTypePtr const&)>& func) const {
//		func(*this);	
//	}
//
//
//	//Case: void visitor with no arguments.
//	void poly_visit(const auto& visitor) const requires std::is_same_v<void,typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type> 
//	{
//			std::function<void(AnyTypePtr const&)> func(visitor);
//			func(*this);
//	}
//
//	//Case: non-void visitor with no arguments.
//	auto poly_visit(const auto& visitor) const -> typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type
//		requires (!std::is_same_v<void, typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type>)
//	{
//		std::function<typename std::invoke_result<decltype(visitor), AnyTypePtr const&>::type(AnyTypePtr const&)> func(visitor);
//		return func(*this);
//	}
//
//	// Case void visitor with arguments.
//	template<typename ... ArgTs>
//	void poly_visit(const auto& visitor, ArgTs&&... args) const requires std::is_same_v<void, typename std::invoke_result<decltype(visitor), AnyTypePtr const&, ArgTs...>::type>
//	{
//		std::function<void(AnyTypePtr const&, ArgTs...)> func(visitor);
//		func(*this, std::forward<ArgTs>(args)...); // Ignore func definition not found, intellisense does not recognize func as a functor object.
//	}
//
//	// Case non-void visitor with arguments.
//	template<typename ... ArgTs>
//	auto poly_visit(const auto& visitor, ArgTs&&... args) const -> typename std::invoke_result<decltype(visitor), const AnyTypePtr &, ArgTs...>::type
//		requires (!std::is_same_v<void, typename std::invoke_result<decltype(visitor), const AnyTypePtr &, ArgTs...>::type>)
//	{
//		using return_type = typename std::invoke_result<decltype(visitor), const AnyTypePtr &, ArgTs...>::type;
//		std::function<return_type(AnyTypePtr const&, ArgTs...)> func(visitor);
//		return func(*this, std::forward<ArgTs>(args)...);
//	}
//
//	 //Case: no arguments, non-void return type or void return type(Version without auto deduction of return type)
//	template<typename RT>
//	RT poly_visit(const auto& visitor) const {
//		if constexpr (std::is_same_v<RT, void>) {
//			std::function<RT(AnyTypePtr const&)> func(visitor);
//			func(*this);
//		}
//		else {
//			std::function<RT(AnyTypePtr const&)> func(visitor);
//			return func(*this);
//		}
//	}
//
//	// Case: arguments (Version without auto deduction of return type)
//	
//	template<typename RT,typename ... ArgTs>
//	RT poly_visit(const auto& visitor, ArgTs&&... args) const {
//		if constexpr (std::is_same_v<RT, void>) {
//			std::function<RT(AnyTypePtr const&,ArgTs...)> func(visitor);
//			func(*this, std::forward<ArgTs>(args)...);
//		}
//		else {
//			std::function<RT(AnyTypePtr const&,ArgTs...)> func(visitor);
//			return func(*this, std::forward<ArgTs>(args)...);
//		}
//	}
//	
//	// How can we get away with specializing away the return type ?
//
//};
//
//
//std::vector<std::type_index> AnyTypePtr::type_map{
//	{std::type_index(typeid(void))},
//	{std::type_index(typeid(NoneT))},
//	{std::type_index(typeid(int))},
//	{std::type_index(typeid(float))},
//	{std::type_index(typeid(char))},
//	{std::type_index(typeid(bool))},
//	{std::type_index(typeid(std::string))},
//	{std::type_index(typeid(std::vector<AnyTypePtr>))}
//};


//template<typename RT, class ValT, class FuncT> requires std::is_invocable_v<FuncT, ValT const&>
//static inline std::pair<const std::type_index, std::function<RT(std::any const&)>> to_any_visitor(FuncT const& func) {
//	return{ std::type_index(typeid(ValT)),
//		[visitor = func](std::any const& a) -> RT {
//			if constexpr (std::is_void_v<RT>) {
//				if constexpr (std::is_void_v<ValT>)
//					visitor();
//				else
//					visitor(std::any_cast<ValT const&>(a));
//			}
//			else {
//				if constexpr (std::is_void_v<ValT>)
//					return visitor();
//				else
//					return visitor(std::any_cast<ValT const&>(a));
//			}
//		}
//	};
//}

struct ViperIdentityCategory {
	using enum_t = char;
	static constexpr enum_t TYPE = 't';
	static constexpr enum_t VARIABLE = 'v';
	static constexpr enum_t METHOD = 'm';
	static constexpr enum_t CLASS = 'c';
};


template<typename IdentityCategoriesT>
struct Identity {
	using category_type = typename IdentityCategoriesT; // The struct containing the enum_t type alias describing the underlying integral type of the identity category.
	using category_enum_type = typename IdentityCategoriesT::enum_t; // The enum_t type alias describing the underlying integral type of the identity category.

	//key_type key; // The key used for equality and ordering

	//// Const references to the key values
	//const std::string& name{std::get<0>(key)}; 
	//const category_enum_type& kind{ std::get<1>(key) };
	//const std::size_t& scope{ std::get<2>(key) };

	std::string name;
	category_enum_type  kind;
	std::size_t scope;

	// Explicit constructor, currently we will not allow default construction
	explicit constexpr Identity(const std::string& name, category_enum_type kind,std::size_t scope = 0) : name(name), kind(kind), scope(scope){
	}

	// Equality operator for the Identity struct
	//constexpr bool operator==(const Identity& other) const {
	//	/*return key == other.key;*/
	//	return name == other.name && kind == other.kind && scope == other.scope;
	//}


	auto operator<=>(const Identity&) const = default;
	// Less than operator for the Identity struct
	//// To elegantly write a operator < for the Identity struct we simply define a tuple as the key which implements operator < for us.
	//constexpr bool operator<(const Identity& other) const { // Why is this necessary ? To allow std::set ordering
	//	return key < other.key;
	//}
};

// template parameters:
//	IdentityCategoriesT: 
//		a struct containing the enum_t type alias describing the underlying integral type of the identity category.
//  IdentityT: 
//		a struct containing a member variable named category of type IdentityCategoriesT::enum_t describing the identity category of the identity.
//		IdentityT must also contain a member variable named name of type std::string_view describing the name of the identity.
//		Identity must also contain a member variable named scope of integral type describing the scope index of the identity.
//		IdentityT must have a constexpr constructor taking a std::string_view and an IdentityCategoriesT::enum_t.
//		IdentityT must have a constexpr bool operator==(const IdentityT&) const. for std::set equality
//		IdentityT must have a constexpr bool operator<(const IdentityT&) const. for std::set ordering where each element is unique based on the key_type of the identifier
template<typename IdentityCategoriesT>
class IdTable {
public:
	using identity_type = Identity<IdentityCategoriesT>;
	using id_category_type = identity_type::category_type;
	using id_category_enum_type = identity_type::category_enum_type;
private:
	std::set<identity_type> table_;
private:
	// Creates a const reference to the identity with the given name and kind, assumes identity exists in the table.
	template<id_category_enum_type IDENTITY_KIND>
	inline auto make_id_ref(const std::string& name,std::size_t scope) const {
		return std::cref(*table_.find(identity_type(name, IDENTITY_KIND, scope)));
	}

public:
	// Checks if the table contains an identity with the given name and kind
	template<id_category_enum_type IDENTITY_KIND>
	constexpr bool has(const std::string& name,std::size_t scope) const {
		return table_.contains(identity_type(name, IDENTITY_KIND,scope));
	}

	// Returns a const reference to the identity with the given name and kind, if it exists
	template<id_category_enum_type IDENTITY_KIND>
	constexpr std::optional<std::reference_wrapper<const identity_type>> get(const std::string& name, std::size_t scope) {
		if (!has<IDENTITY_KIND>(name, scope)) {
			// Element does not exist.
			return std::nullopt;
		}
		else {
			return make_id_ref<IDENTITY_KIND>(name,scope);
		}
	}

	// Adds an identity with the given name and kind to the table, if it doesn't already exist
	template<id_category_enum_type IDENTITY_KIND>
	constexpr std::optional<std::reference_wrapper<const identity_type>> add(const std::string& name, std::size_t scope) {
		auto inserted = table_.insert(identity_type(name, IDENTITY_KIND, scope));
		if (!inserted.second) {
			// Element already exists.
			return std::nullopt;
		}
		else {
			// Return inserted element reference
			return make_id_ref<IDENTITY_KIND>(name, scope);
		}
	}

	// Removes an identity with the given name and kind from the table, if it doesnt exist does nothing.
	template<id_category_enum_type IDENTITY_KIND>
	constexpr void remove(const std::string& name, std::size_t scope) {
		table_.erase(identity_type(name, IDENTITY_KIND, scope));
	}

	constexpr void clear() {
		table_.clear();
	}

	constexpr auto empty() {
		return table_.empty();
	}

	using Id = id_category_type;
};

// A void type index will be used to indicate that a type is not specified.
// An actual type may be used to represent a None / Void type. eg. std::monostate
static const auto VOID_TYPE_INDEX = std::type_index(typeid(void));

// A type table will contain strings associated with run-time type information.
class TypeTable {
	struct TypeDefinition {
		std::string name;
		std::size_t scope;
		std::type_index type;

		TypeDefinition(const std::string& name, std::size_t scope) : name(name), scope(scope), type(VOID_TYPE_INDEX) {}
		TypeDefinition(const std::string& name, std::size_t scope, std::type_index type) : name(name), scope(scope), type(type) {}
		
		constexpr bool operator==(const TypeDefinition& other) const {
			return name == other.name && scope == other.scope;
		}
		constexpr auto operator<=>(const TypeDefinition& other) const { // Why is this necessary ? To allow std::set ordering
			if (name < other.name or (name == other.name and scope < other.scope))
				return std::strong_ordering::less;
			if (name > other.name or (name == other.name and scope > other.scope))
				return std::strong_ordering::greater;
			return std::strong_ordering::equivalent;
		}
	};

	std::set<TypeDefinition> table_;

	public:
	// Checks if the table contains a type with the given name
	bool has(const std::string& name,std::size_t scope) const {
		return table_.contains(TypeDefinition(name,scope));
	}

	// Returns a const reference to the type with the given name, if it exists
	std::optional<std::reference_wrapper<const TypeDefinition>> get(const std::string& name, std::size_t scope) {
		auto found = table_.find(TypeDefinition(name, scope));
		if (found == table_.end()) {
			return std::nullopt;
		}
		else {
			return std::cref(*found);
		}
	}

	// Adds a type with the given name to the table, if it doesn't already exist, else returns nullopt
	std::optional<std::reference_wrapper<const TypeDefinition>> add(const std::string& name, std::size_t scope,std::type_index type_index) {
		auto inserted = table_.insert(TypeDefinition(name, scope,type_index));
		if (inserted.second == false) {
			return std::nullopt;
		}
		else {
			return std::cref(*(inserted.first));
		}
	}

	// Replaces a type in the type table, if it exists, else returns nullopt
	std::optional<std::reference_wrapper<const TypeDefinition>> replace(const std::string& name, std::size_t scope, std::type_index type_index) {
		auto found = table_.find(TypeDefinition(name, scope));
		if (found == table_.end()) {
			return std::nullopt;
		}
		else {
			auto extracted = table_.extract(found);
			extracted.value().type = type_index;
			table_.insert(std::move(extracted));
			return get(name,scope);
		}
	}

	// Creates an alias for a type in the type table, if it exists, else returns nullopt
	std::optional<std::reference_wrapper<const TypeDefinition>> alias(const std::string& name, std::size_t scope, const std::string& alias_name,std::size_t alias_scope) {
		auto found = get(name, scope);
		// Find the type we wish to alias
		if (!found.has_value()) {
			return std::nullopt; // The type we wish to alias does not exist
		}
		else {
			// Check if the alias is already defined in the table, if the alias already exists, return nullopt
			if (has(alias_name, alias_scope)) {
				return std::nullopt;
			}
			else {
				// Insert the alias into the table with the same type as the type we wish to alias
				auto inserted = table_.insert(TypeDefinition(alias_name, alias_scope, found->get().type));
				return std::cref(*(inserted.first));
			}
		}
	}

	// Removes a type with the given name from the table, if it doesnt exist does nothing.
	void remove(const std::string& name, std::size_t scope) {
		table_.erase(TypeDefinition(name, scope));
	}

	void clear() {
		table_.clear();
	}

	bool empty() {
		return table_.empty();
	}
};

// A variable instance will contain a name, a scope, a type and a value.
struct VariableInstance {
	
	std::string_view identity{""};
	std::size_t scope{0};
	std::type_index type{ VOID_TYPE_INDEX };

	VariableInstance(const std::string_view& identity, std::size_t scope, std::type_index type, std::any&& value) : identity(identity), type(type) {}
	VariableInstance(const std::string_view& identity, std::size_t scope, std::type_index type) : identity(identity), type(type){}
	VariableInstance(const std::string_view& identity,std::size_t scope) : identity(identity){}
	VariableInstance() = default;

	constexpr bool operator==(const VariableInstance& other) const {
		return identity == other.identity && scope == other.scope;
	}

	constexpr bool operator<(const VariableInstance& other) const { // Why is this necessary ? To allow std::set ordering
		return identity < other.identity || (identity == other.identity && scope < other.scope);
	}
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// <@name:Variable Table>
// <@class:VariableTable>
// <@brief:Contain a set of variable instances of type VariableInstance.
//		   The key comparison is the identity and scope of the variable instance.
class VariableTable {
	std::map<VariableInstance,std::any> table_;
public:
	void clear() {
		table_.clear();
	}

	bool empty() {
		return table_.empty();
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@method:has(const std::string_view& identity,std::size_t scope)>
	// <@brief:Checks if the table contains a variable instance with the given identity>
	bool has(const std::string_view& identity,std::size_t scope) const {
		return table_.contains(VariableInstance(identity,scope));
	}
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@method:has(const std::string_view& identity,std::size_t scope,std::type_index type)>
	// <@brief:Checks if the table contains a variable instance with the given identity and type_index>
	bool has(const std::string_view& identity, std::size_t scope,std::type_index type) const {
		auto found = table_.find(VariableInstance(identity, scope));
		if (found != table_.end()) {
			if (found->first.type == type) {
				return true;
			}
		}
		return false;
	}
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:Returns a const reference to a variable instance with the given identity, if it exists>
	std::optional<std::reference_wrapper<const VariableInstance>> getc(const std::string_view& identity, std::size_t scope) {
		auto found = table_.find(VariableInstance(identity, scope));
		if (found == table_.end()) {
			return std::nullopt;
		}
		else {
			return std::cref(found->first);
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:Returns a reference the value contained in a variable instance with the given identity, if it exists>
	std::optional<std::reference_wrapper<std::any>> get_value_ref(const std::string_view& identity, std::size_t scope) {
		auto found = table_.find(VariableInstance(identity, scope));

		if (found == table_.end()) {
			return std::nullopt;
		}
		else {
			return table_.at(VariableInstance(identity, scope));
		}
	}
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	template<typename T>
	std::optional<std::reference_wrapper<T>> get_cast_value_ref(const std::string_view& identity, std::size_t scope) {
		auto found = table_.find(VariableInstance(identity, scope));

		if (found == table_.end()) {
			return std::nullopt;
		}
		else {		
			return std::any_cast<T&>(table_.at(VariableInstance(identity, scope)));
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <name: Variable Assignment>
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:Assigns a value to a variable instance with the given identity, if it exists, returns a reference to the value>
	std::optional<std::reference_wrapper<std::any>> assign(const std::string_view& identity, std::size_t scope, std::any&& value) {
		auto found = table_.find(VariableInstance(identity, scope));
		if (found == table_.end()) {
			std::cerr << "[WARNING] Cannot assign a value to a variable that does not exist." << std::endl;
			return std::nullopt;
		}
		else {
			// If the type of the value is not the same as the type of the variable instance, we will have an error
			if (found->first.type != value.type()) {
				std::cerr << "[WARNING] Cannot assign a value of type " << value.type().name() << " to a variable of type " << found->first.type.name() << "." << std::endl;
				return std::nullopt;
			}
			else {
				// Insert the new variable instance into the table
				table_[found->first] = (std::move(value));

				// return a constant reference to the variable instance
				return table_[found->first];
			}
		}
	}

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@name: Anonymous Variable Declaration>
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:Adds a variable instance with the given identity to the table, if it doesn't already exist, else returns nullopt
	// We will allow the user to instantiate a variable by only providing an identity and a scope
	//      In this case, we will set the type_index to VOID_TYPE_INDEX
	//      And we will set the value to std::nullopt
	//      If the identity already exists in the table, we will return std::nullopt
	//      If the identity does not exist in the table, we will insert the variable instance into the table>
	std::optional<std::reference_wrapper<const VariableInstance>> declare(const std::string_view& identity,std::size_t scope) {
		auto find = table_.find(VariableInstance(identity, scope));
		if (find != table_.end()) {
			return std::nullopt;
		}
		else {
			return table_.insert({ (VariableInstance(identity, scope)) ,std::any{} }).first->first;
		}
	} // end declare
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@name: Type Constrained Variable Declaration>
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:If a variable instance is provided with and identity , scope and type_index, the value is set to std::nullopt
	//      In this case we will check if the identity already exists in the table
	//      If it does, will set the type_index to the type_index of the variable instance
	//      If it does not, we will insert the variable instance into the table
	//      We will not allow variable to be re-defined with a different type_index unless the type is previously VOID_TYPE_INDEX>
	std::optional<std::reference_wrapper<const VariableInstance>> declare(const std::string_view& identity,std::size_t scope,std::type_index type_index) {  
		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
		assert(type_index != VOID_TYPE_INDEX && "[ERROR] Cannot assign void type to variable declaration.");

		// Variable Type Assignment
		if (has(identity,scope)) {
			if (!has(identity,scope,VOID_TYPE_INDEX)) {
				std::cerr << "[WARNING] Cannot re-define a variable with a different type." << std::endl;
				return std::nullopt; // Cannot re-define a variable with a different type
			}
			else {
				// Remove the existing variable instance
				// Replace it with a new variable instance with the same identity and scope but a new type_index
				table_.erase(VariableInstance(identity, scope));
				// Insert and return a reference to the new variable instance
				return table_.insert({ VariableInstance(identity, scope, type_index) ,std::nullopt }).first->first;
			}
		} // end if

		// Variable Type Definition
		// NOTE: We return directly and not check if the variable already exists in the table 
		//		 because we already did above in: if(has(identity,scope))
		// Insert and return a reference to the new variable instance
		return table_.insert({ VariableInstance(identity, scope, type_index) ,std::any{} }).first->first;

	}// end declare
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@name: Full Variable Declaration>
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:If a variable instance is provided with and identity , scope and type_index, and a value, the value is moved into the variable instance
	//      In this case we will check if the identity already exists in the table
	//      If it does then we will have an error. This variable was already fully defined.
	//      If it does not, we will insert the variable instance into the table>
	std::optional<std::reference_wrapper<const VariableInstance>> declare(const std::string_view& identity, std::size_t scope, std::type_index type_index, std::any value) {
		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
		assert(type_index != VOID_TYPE_INDEX && "[ERROR] Cannot assign void type to variable declaration.");

		// Variable Type Assignment
		if (has(identity, scope)) {
			std::cerr << "[WARNING] Cannot re-define a variable with a different type." << std::endl;
			return std::nullopt; // Cannot re-define a variable with a different type
		} // end if

		// Variable Type Definition
		// NOTE: We return directly and not check if the variable already exists in the table 
		//		 because we already did above in: if(has(identity,scope))
		return table_.insert({ VariableInstance(identity, scope, type_index),std::move(value) }).first->first;

	}// end declare
	//
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	// <@name: Variable Assignment Declaration>
	// <@method:get(const std::string_view& identity,std::size_t scope)>
	// <@brief:If a variable instance is provided with and identity , scope and VOID_TYPE_INDEX and a a value, the value is moved into the variable instance
	//      In this case the type_index is determined by the type of the value
	//      If the identity already exists in the table, we will check if the type_index matches the type of the value
	//      If it does not, we will have an error. You cannot assign a value of type T to a variable of type U.
	//      If it does, we will insert the variable instance into the table>
	std::optional<std::reference_wrapper<const VariableInstance>> declare(const std::string_view& identity, std::size_t scope, std::any value) {
		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
		const auto & type_index = value.type();

		// Variable Type Assignment
		if (has(identity, scope)) {
			if (!has(identity, scope, type_index)) {
				std::cerr << "[WARNING] Cannot assign a value of type " << type_index.name() << " to a variable of type " << getc(identity, scope)->get().type.name() << "." << std::endl;
				return std::nullopt; // Cannot assign a value of type T to a variable of type U.
			}
			else {
				// Remove the existing variable instance
				// Replace it with a new variable instance with the same identity and scope but a new type_index
				table_.erase(VariableInstance(identity, scope));
				// Insert and return a reference to the new variable instance
				return table_.insert({ VariableInstance(identity, scope, type_index), std::move(value) }).first->first;
			}
		} // end if

		// Variable Type Definition
		// NOTE: We return directly and not check if the variable already exists in the table 
		//		 because we already did above in: if(has(identity,scope))
		return table_.insert({ VariableInstance(identity, scope, type_index), std::move(value) }).first->first;

	}// end declare
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//

};

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------//



//// A variable instance will contain a name, a scope, a type and a value.
//struct VariableInstance2 {
//
//	std::string_view identity{ "" };
//	std::size_t scope{ 0 };
//	std::type_index type{ VOID_TYPE_INDEX };
//
//	VariableInstance2(const std::string_view& identity, std::size_t scope, std::type_index type) : identity(identity), type(type) {}
//	VariableInstance2(const std::string_view& identity, std::size_t scope) : identity(identity) {}
//	VariableInstance2() = default;
//
//	constexpr bool operator==(const VariableInstance2& other) const {
//		return identity == other.identity && scope == other.scope;
//	}
//
//	constexpr bool operator<(const VariableInstance2& other) const { // Why is this necessary ? To allow std::set ordering
//		return identity < other.identity || (identity == other.identity && scope < other.scope);
//	}
//};
//
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//// <@name:Variable Table>
//// <@class:VariableTable>
//// <@brief:Contain a set of variable instances of type VariableInstance.
////		   The key comparison is the identity and scope of the variable instance.
//class VariableTable2 {
//	std::map<VariableInstance2, AnyTypePtr> table_;
//public:
//	void clear() {
//		table_.clear();
//	}
//
//	bool empty() {
//		return table_.empty();
//	}
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:has(const std::string_view& identity,std::size_t scope)>
//	// <@brief:Checks if the table contains a variable instance with the given identity>
//	bool has(const std::string_view& identity, std::size_t scope) const {
//		return table_.contains(VariableInstance2(identity, scope));
//	}
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:has(const std::string_view& identity,std::size_t scope,std::type_index type)>
//	// <@brief:Checks if the table contains a variable instance with the given identity and type_index>
//	bool has(const std::string_view& identity, std::size_t scope, std::type_index type) const {
//		auto found = table_.find(VariableInstance2(identity, scope));
//		if (found != table_.end()) {
//			if (found->first.type == type) {
//				return true;
//			}
//		}
//		return false;
//	}
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:Returns a const reference to a variable instance with the given identity, if it exists>
//	std::optional<std::reference_wrapper<const VariableInstance2>> getc(const std::string_view& identity, std::size_t scope) {
//		auto found = table_.find(VariableInstance2(identity, scope));
//		if (found == table_.end()) {
//			return std::nullopt;
//		}
//		else {
//			return std::cref(found->first);
//		}
//	}
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:Returns a reference the value contained in a variable instance with the given identity, if it exists>
//	std::optional<std::reference_wrapper<AnyTypePtr>> get_value_ref(const std::string_view& identity, std::size_t scope) {
//		auto found = table_.find(VariableInstance2(identity, scope));
//
//		if (found == table_.end()) {
//			return std::nullopt;
//		}
//		else {
//			return table_.at(VariableInstance2(identity, scope));
//		}
//	}
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//
//	std::optional<std::pair<ViperType, std::reference_wrapper<AnyTypePtr>>> get_value_ptr(const std::string_view& identity, std::size_t scope) {
//		auto found = table_.find(VariableInstance2(identity, scope));
//
//		if (found == table_.end()) {
//			return std::nullopt;
//		}
//		else {
//			auto& a = table_.at(VariableInstance2(identity, scope));
//
//			// You can check the type of the value
//			if (a.is<ViperType::int_>())
//				return std::make_pair(ViperType::int_,std::ref(a));
//			else if (a.is<ViperType::real_>())
//				return std::make_pair(ViperType::real_, std::ref(a));
//			else if (a.is<ViperType::string_>())
//				return std::make_pair(ViperType::string_, std::ref(a));
//			else if (a.is<ViperType::bool_>())
//				return std::make_pair(ViperType::bool_, std::ref(a));
//			else if (a.is<ViperType::char_>())
//				return std::make_pair(ViperType::char_, std::ref(a));
//			else if (a.is<ViperType::void_>())
//				return std::make_pair(ViperType::void_, std::ref(a));
//			else if (a.is<ViperType::none_>())
//				return std::make_pair(ViperType::none_, std::ref(a));
//			else
//				return std::nullopt; // Unknown type
//		}
//	}
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <name: Variable Assignment>
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:Assigns a value to a variable instance with the given identity, if it exists, returns a reference to the value>
//	std::optional<std::reference_wrapper<AnyTypePtr>> assign(const std::string_view& identity, std::size_t scope, AnyTypePtr&& value) {
//		auto found = table_.find(VariableInstance2(identity, scope));
//		if (found == table_.end()) {
//			std::cerr << "[WARNING] Cannot assign a value to a variable that does not exist." << std::endl;
//			return std::nullopt;
//		}
//		else {
//			// If the type of the value is not the same as the type of the variable instance, we will have an error
//			if (found->first.type != value.type) {
//				std::cerr << "[WARNING] Cannot assign a value of type " << value.type.name() << " to a variable of type " << found->first.type.name() << "." << std::endl;
//				return std::nullopt;
//			}
//			else {
//				// Insert the new variable instance into the table
//				table_[found->first] = (std::move(value));
//
//				// return a constant reference to the variable instance
//				return table_[found->first];
//			}
//		}
//	}
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@name: Anonymous Variable Declaration>
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:Adds a variable instance with the given identity to the table, if it doesn't already exist, else returns nullopt
//	// We will allow the user to instantiate a variable by only providing an identity and a scope
//	//      In this case, we will set the type_index to VOID_TYPE_INDEX
//	//      And we will set the value to std::nullopt
//	//      If the identity already exists in the table, we will return std::nullopt
//	//      If the identity does not exist in the table, we will insert the variable instance into the table>
//	std::optional<std::reference_wrapper<const VariableInstance2>> declare(const std::string_view& identity, std::size_t scope) {
//		auto find = table_.find(VariableInstance2(identity, scope));
//		if (find != table_.end()) {
//			return std::nullopt;
//		}
//		else {
//			return table_.insert({ (VariableInstance2(identity, scope)) ,AnyTypePtr{} }).first->first;
//		}
//	} // end declare
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@name: Type Constrained Variable Declaration>
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:If a variable instance is provided with and identity , scope and type_index, the value is set to std::nullopt
//	//      In this case we will check if the identity already exists in the table
//	//      If it does, will set the type_index to the type_index of the variable instance
//	//      If it does not, we will insert the variable instance into the table
//	//      We will not allow variable to be re-defined with a different type_index unless the type is previously VOID_TYPE_INDEX>
//	std::optional<std::reference_wrapper<const VariableInstance2>> declare(const std::string_view& identity, std::size_t scope, std::type_index type_index) {
//		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
//		assert(type_index != VOID_TYPE_INDEX && "[ERROR] Cannot assign void type to variable declaration.");
//
//		// Variable Type Assignment
//		if (has(identity, scope)) {
//			if (!has(identity, scope, VOID_TYPE_INDEX)) {
//				std::cerr << "[WARNING] Cannot re-define a variable with a different type." << std::endl;
//				return std::nullopt; // Cannot re-define a variable with a different type
//			}
//			else {
//				// Remove the existing variable instance
//				// Replace it with a new variable instance with the same identity and scope but a new type_index
//				table_.erase(VariableInstance2(identity, scope));
//				// Insert and return a reference to the new variable instance
//				return table_.insert({ VariableInstance2(identity, scope, type_index) ,AnyTypePtr{} }).first->first;
//			}
//		} // end if
//
//		// Variable Type Definition
//		// NOTE: We return directly and not check if the variable already exists in the table 
//		//		 because we already did above in: if(has(identity,scope))
//		// Insert and return a reference to the new variable instance
//		return table_.insert({ VariableInstance2(identity, scope, type_index) ,AnyTypePtr{} }).first->first;
//
//	}// end declare
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@name: Full Variable Declaration>
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:If a variable instance is provided with and identity , scope and type_index, and a value, the value is moved into the variable instance
//	//      In this case we will check if the identity already exists in the table
//	//      If it does then we will have an error. This variable was already fully defined.
//	//      If it does not, we will insert the variable instance into the table>
//	std::optional<std::reference_wrapper<const VariableInstance2>> declare(const std::string_view& identity, std::size_t scope, std::type_index type_index, AnyTypePtr value) {
//		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
//		assert(type_index != VOID_TYPE_INDEX && "[ERROR] Cannot assign void type to variable declaration.");
//
//		// Variable Type Assignment
//		if (has(identity, scope)) {
//			std::cerr << "[WARNING] Cannot re-define a variable with a different type." << std::endl;
//			return std::nullopt; // Cannot re-define a variable with a different type
//		} // end if
//
//		// Variable Type Definition
//		// NOTE: We return directly and not check if the variable already exists in the table 
//		//		 because we already did above in: if(has(identity,scope))
//		return table_.insert({ VariableInstance2(identity, scope, type_index),std::move(value) }).first->first;
//
//	}// end declare
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@name: Variable Assignment Declaration>
//	// <@method:get(const std::string_view& identity,std::size_t scope)>
//	// <@brief:If a variable instance is provided with and identity , scope and VOID_TYPE_INDEX and a a value, the value is moved into the variable instance
//	//      In this case the type_index is determined by the type of the value
//	//      If the identity already exists in the table, we will check if the type_index matches the type of the value
//	//      If it does not, we will have an error. You cannot assign a value of type T to a variable of type U.
//	//      If it does, we will insert the variable instance into the table>
//	std::optional<std::reference_wrapper<const VariableInstance2>> declare(const std::string_view& identity, std::size_t scope, AnyTypePtr value) {
//		// The type of the variable (VOID_TYPE_INDEX means the type is not specified - you cannot have a void variable)
//		const auto& type_index = value.type;
//
//		// Variable Type Assignment
//		if (has(identity, scope)) {
//			if (!has(identity, scope, type_index)) {
//				std::cerr << "[WARNING] Cannot assign a value of type " << type_index.name() << " to a variable of type " << getc(identity, scope)->get().type.name() << "." << std::endl;
//				return std::nullopt; // Cannot assign a value of type T to a variable of type U.
//			}
//			else {
//				// Remove the existing variable instance
//				// Replace it with a new variable instance with the same identity and scope but a new type_index
//				table_.erase(VariableInstance2(identity, scope));
//				// Insert and return a reference to the new variable instance
//				return table_.insert({ VariableInstance2(identity, scope, type_index), std::move(value) }).first->first;
//			}
//		} // end if
//
//		// Variable Type Definition
//		// NOTE: We return directly and not check if the variable already exists in the table 
//		//		 because we already did above in: if(has(identity,scope))
//		return table_.insert({ VariableInstance2(identity, scope, type_index), std::move(value) }).first->first;
//
//	}// end declare
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//};
//
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
////------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//class MethodTable {
//	std::map<std::string, std::vector<std::pair<std::vector<std::type_index>, std::type_index>>> table_;
//public:
//void clear() {
//		table_.clear();
//	}
//
//	bool empty() {
//		return table_.empty();
//	}
//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:has(const std::string& identity)>
//	// <@brief:Checks if the table contains a method with the given identity>
//	bool has(const std::string& identity) const {
//		return table_.contains(identity);
//	}
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//	// <@method:has(const std::string& identity,const std::vector<std::type_index>& parameter_types)>
//	// <@brief:Checks if the table contains a method with the given identity and parameter types>
//	bool has(const std::string& identity, const std::vector<std::type_index>& parameter_types) const {
//		auto found = table_.find(identity);
//		if (found != table_.end()) {
//			for (const auto& [params, return_type] : found->second) {
//				if (params == parameter_types) {
//					return true;
//				}
//			}
//		}
//		return false;
//	}
//	//
//	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//
//
//};

TEST(RegisterIdentity, IdentityTableTest) {
	using ViperIdTable = IdTable<ViperIdentityCategory>;
	ViperIdTable table;

	// Test adding a global identity to the table
	// Add a new global type identity to the table
	auto new_global_type_identity = table.add<ViperIdTable::Id::TYPE>("int",0);
	EXPECT_TRUE(new_global_type_identity.has_value() && "[TEST][IdentityTable][Failed to insert global identity element.]");


	// Retrieve the global identity from the table
	auto existing_global_type_identity = table.get<ViperIdTable::Id::TYPE>("int",0);
	EXPECT_TRUE(existing_global_type_identity.has_value() && "[TEST][IdentityTable][Failed to retrieve global identity element.]");

	// Result should equal to the new global identity
	EXPECT_EQ(new_global_type_identity.value().get(), existing_global_type_identity.value().get());
	std::cout << "[TEST][IdentityTable][Global identity element added and retrieved successfully.]" << std::endl;


	// Test adding a local identity to the table
	// Add a new local type identity to the table
	auto new_local_type_identity = table.add<ViperIdTable::Id::TYPE>("int",1);
	EXPECT_TRUE(new_local_type_identity.has_value() && "[TEST][IdentityTable][Failed to insert local identity element.]");


	// Retrieve the local identity from the table
	auto existing_local_type_identity = table.get<ViperIdTable::Id::TYPE>("int",1);
	EXPECT_TRUE(existing_local_type_identity.has_value() && "[TEST][IdentityTable][Failed to retrieve local identity element.]");

	// Result should equal to the new local identity
	EXPECT_EQ(new_local_type_identity.value().get(), existing_local_type_identity.value().get());
	std::cout << "[TEST][IdentityTable][Local identity element added and retrieved successfully.]" << std::endl;



	// Test adding an existing identity to the table
	// Attempt to add the same global type identity to the table
	// Should return nullopt
	auto new_global_type_identity2 = table.add<ViperIdTable::Id::TYPE>("int",0);
	EXPECT_EQ(new_global_type_identity2.has_value(), false);
	std::cout << "[TEST][IdentityTable][Successfuly failed to insert existing global identity element.]" << std::endl;

	// Attempt to add the same local type identity to the table
	// Should return nullopt
	auto new_local_type_identity2 = table.add<ViperIdTable::Id::TYPE>("int",1);
	EXPECT_EQ(new_local_type_identity2.has_value(), false);
	std::cout << "[TEST][IdentityTable][Successfuly failed to insert existing local identity element.]" << std::endl;

	// Clear the table
	table.clear();
	EXPECT_TRUE(table.empty());
	std::cout << "[TEST][IdentityTable][Table cleared successfully.]" << std::endl;

	// Add identities of diffrent types but the same name. Get each one and compare them. Result should equal to the new identity
	auto new_global_variable_identity = table.add<ViperIdTable::Id::VARIABLE>("int",0);
	auto existing_global_variable_identity = table.get<ViperIdTable::Id::VARIABLE>("int",0);
	EXPECT_EQ(new_global_variable_identity.value().get(), existing_global_variable_identity.value().get());

	auto new_local_variable_identity = table.add<ViperIdTable::Id::VARIABLE>("int",1);
	auto existing_local_variable_identity = table.get<ViperIdTable::Id::VARIABLE>("int",1);
	EXPECT_EQ(new_local_variable_identity.value().get(), existing_local_variable_identity.value().get());

	auto new_global_method_identity = table.add<ViperIdTable::Id::METHOD>("int",0);
	auto existing_global_method_identity = table.get<ViperIdTable::Id::METHOD>("int",0);
	EXPECT_EQ(new_global_method_identity.value().get(), existing_global_method_identity.value().get());

	auto new_local_method_identity = table.add<ViperIdTable::Id::METHOD>("int",1);
	auto existing_local_method_identity = table.get<ViperIdTable::Id::METHOD>("int",1);
	EXPECT_EQ(new_local_method_identity.value().get(), existing_local_method_identity.value().get());

	auto new_global_class_identity = table.add<ViperIdTable::Id::CLASS>("int",0);
	auto existing_global_class_identity = table.get<ViperIdTable::Id::CLASS>("int",0);
	EXPECT_EQ(new_global_class_identity.value().get(), existing_global_class_identity.value().get());

	auto new_local_class_identity = table.add<ViperIdTable::Id::CLASS>("int",1);
	auto existing_local_class_identity = table.get<ViperIdTable::Id::CLASS>("int",1);
	EXPECT_EQ(new_local_class_identity.value().get(), existing_local_class_identity.value().get());

	std::cout << "[TEST][IdentityTable][Identity elements added and retrieved successfully for different identity categories.]" << std::endl;

	// Test removing an identity from the table
	// Remove all the identities one by one.
	table.remove<ViperIdTable::Id::TYPE>("int",0);
	table.remove<ViperIdTable::Id::TYPE>("int",1);
	table.remove<ViperIdTable::Id::VARIABLE>("int",0);
	table.remove<ViperIdTable::Id::VARIABLE>("int",1);
	table.remove<ViperIdTable::Id::METHOD>("int",0);
	table.remove<ViperIdTable::Id::METHOD>("int",1);
	table.remove<ViperIdTable::Id::CLASS>("int",0);
	table.remove<ViperIdTable::Id::CLASS>("int",1);

	// Table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][IdentityTable][Identity elements from diffrent categories removed successfully.]" << std::endl;
}

TEST(RegisterType, TypeTableTest) {
	// A type table will contain strings associated with run-time type information.
	// Add a new global type identity to the table
	TypeTable table;

	// Test adding a global type to the table
	auto new_global_type = table.add("int",0,typeid(int));
	EXPECT_TRUE(new_global_type.has_value() && "[TEST][TypeTable][Failed to insert global type element.]");

	// Retrieve the global type from the table
	auto existing_global_type = table.get("int",0);
	EXPECT_TRUE(existing_global_type.has_value() && "[TEST][TypeTable][Failed to retrieve global type element.]");

	// Result should equal to the new global type
	EXPECT_EQ(new_global_type.value().get(), existing_global_type.value().get());
	std::cout << "[TEST][TypeTable][Global type element added and retrieved successfully.]" << std::endl;

	// Test adding a local type to the table
	auto new_local_type = table.add("int",1,typeid(int));
	EXPECT_TRUE(new_local_type.has_value() && "[TEST][TypeTable][Failed to insert local type element.]");

	// Retrieve the local type from the table
	auto existing_local_type = table.get("int",1);
	EXPECT_TRUE(existing_local_type.has_value() && "[TEST][TypeTable][Failed to retrieve local type element.]");

	// Result should equal to the new local type
	EXPECT_EQ(new_local_type.value().get(), existing_local_type.value().get());
	std::cout << "[TEST][TypeTable][Local type element added and retrieved successfully.]" << std::endl;

	// Test adding an existing type to the table
	// Attempt to add the same global type to the table
	// Should return nullopt
	auto new_global_type2 = table.add("int",0,typeid(int));
	EXPECT_EQ(new_global_type2.has_value(), false);
	std::cout << "[TEST][TypeTable][Successfuly failed to insert existing global type element.]" << std::endl;

	// Attempt to add the same local type to the table
	// Should return nullopt
	auto new_local_type2 = table.add("int",1,typeid(int));
	EXPECT_EQ(new_local_type2.has_value(), false);
	std::cout << "[TEST][TypeTable][Successfuly failed to insert existing local type element.]" << std::endl;

	// Attempt to replace the global type with a new type
	// Should return a reference to the new type
	auto new_global_type3 = table.replace("int",0,typeid(float));
	EXPECT_TRUE(new_global_type3.has_value() && "[TEST][TypeTable][Failed to replace global type element.]");

	// Retrieve the global type from the table
	auto existing_global_type3 = table.get("int",0);
	EXPECT_TRUE(existing_global_type3.has_value() && "[TEST][TypeTable][Failed to retrieve global type element.]");

	// Result should equal to the new global type
	EXPECT_EQ(new_global_type3.value().get(), existing_global_type3.value().get());
	std::cout << "[TEST][TypeTable][Global type element replaced and retrieved successfully.]" << std::endl;

	// Attempt to replace the local type with a new type
	// Should return a reference to the new type
	auto new_local_type3 = table.replace("int",1,typeid(float));
	EXPECT_TRUE(new_local_type3.has_value() && "[TEST][TypeTable][Failed to replace local type element.]");

	// Retrieve the local type from the table
	auto existing_local_type3 = table.get("int",1);
	EXPECT_TRUE(existing_local_type3.has_value() && "[TEST][TypeTable][Failed to retrieve local type element.]");

	// Result should equal to the new local type
	EXPECT_EQ(new_local_type3.value().get(), existing_local_type3.value().get());
	std::cout << "[TEST][TypeTable][Local type element replaced and retrieved successfully.]" << std::endl;

	// Clear the table
	table.clear();

	// table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][TypeTable][Table cleared successfully.]" << std::endl;

	// Add types of diffrent scopes and types but the same name.
	auto new_global_type4 = table.add("integer",0,typeid(int));
	auto new_global_type5 = table.add("integer", 1, typeid(unsigned));
	auto new_global_type6 = table.add("integer", 2, typeid(float));
	auto new_global_type7 = table.add("integer", 3, typeid(double));
	auto new_global_type8 = table.add("integer", 4, typeid(long));
	auto new_global_type9 = table.add("integer", 5, typeid(long long));
	auto new_global_type10 = table.add("integer", 6, typeid(short));
	auto new_global_type11 = table.add("integer", 7, typeid(char));
	auto new_global_type12 = table.add("integer", 8, typeid(bool));
	auto new_global_type13 = table.add("integer", 9, typeid(std::string));
	auto new_global_type14 = table.add("integer", 10, typeid(void));


	// Retrieve each type from the table
	auto existing_global_type4 = table.get("integer", 0);
	auto existing_global_type5 = table.get("integer", 1);
	auto existing_global_type6 = table.get("integer", 2);
	auto existing_global_type7 = table.get("integer", 3);
	auto existing_global_type8 = table.get("integer", 4);
	auto existing_global_type9 = table.get("integer", 5);
	auto existing_global_type10 = table.get("integer", 6);
	auto existing_global_type11 = table.get("integer", 7);
	auto existing_global_type12 = table.get("integer", 8);
	auto existing_global_type13 = table.get("integer", 9);
	auto existing_global_type14 = table.get("integer", 10);

	// Result should equal to the new type
	EXPECT_EQ(new_global_type4.value().get(), existing_global_type4.value().get());
	EXPECT_EQ(new_global_type5.value().get(), existing_global_type5.value().get());
	EXPECT_EQ(new_global_type6.value().get(), existing_global_type6.value().get());
	EXPECT_EQ(new_global_type7.value().get(), existing_global_type7.value().get());
	EXPECT_EQ(new_global_type8.value().get(), existing_global_type8.value().get());
	EXPECT_EQ(new_global_type9.value().get(), existing_global_type9.value().get());
	EXPECT_EQ(new_global_type10.value().get(), existing_global_type10.value().get());
	EXPECT_EQ(new_global_type11.value().get(), existing_global_type11.value().get());
	EXPECT_EQ(new_global_type12.value().get(), existing_global_type12.value().get());
	EXPECT_EQ(new_global_type13.value().get(), existing_global_type13.value().get());
	EXPECT_EQ(new_global_type14.value().get(), existing_global_type14.value().get());

	std::cout << "[TEST][TypeTable][Type elements added and retrieved successfully for different scopes and types.]" << std::endl;

	// Test removing a type from the table
	// Remove all the types one by one.
	table.remove("integer",0);
	table.remove("integer",1);
	table.remove("integer",2);
	table.remove("integer",3);
	table.remove("integer",4);
	table.remove("integer",5);
	table.remove("integer",6);
	table.remove("integer",7);
	table.remove("integer",8);
	table.remove("integer",9);
	table.remove("integer",10);

	// Table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][TypeTable][Type elements from diffrent scopes removed successfully.]" << std::endl;
}

TEST(RegisterTypeAlias, TypeTableTest) {
	// A type table will contain strings associated with run-time type information.
	TypeTable table;

	// Add a type to the type table
	auto new_global_type = table.add("int",0,typeid(int));

	// Add an alias to the type table
	auto new_global_type_alias = table.alias("int",0,"integer",0);

	// Retrieve the alias from the table
	auto existing_global_type_alias = table.get("integer",0);

	// The type of the alias should be the same as the type we added
	EXPECT_EQ(new_global_type.value().get().type, existing_global_type_alias.value().get().type);

	std::cout << "[TEST][TypeTable][Type alias added and retrieved successfully.]" << std::endl;

	// Test adding an existing alias to the table

	// Attempt to add the same alias to the table
	// Should return nullopt
	auto new_global_type_alias2 = table.alias("int",0,"integer",0);
	EXPECT_EQ(new_global_type_alias2.has_value(), false);
	std::cout << "[TEST][TypeTable][Successfuly failed to insert existing alias element.]" << std::endl;

	// Attempt to add an alias to a non-existing type
	// Should return nullopt
	auto new_global_type_alias3 = table.alias("random_type",0,"integer",1);
	EXPECT_EQ(new_global_type_alias3.has_value(), false);
	std::cout << "[TEST][TypeTable][Successfuly failed to insert alias element for non-existing type.]" << std::endl;

	// Clear the table
	table.clear();

	// table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][TypeTable][Table cleared successfully.]" << std::endl;
}

TEST(AnonymousVariableDeclaration, VariableTableTest) {
	VariableTable table;

	// Test adding an anonymous variable to the table
	auto new_global_variable = table.declare("a",0);
	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][VariableTable][Failed to insert anonymous variable element.]");

	// Retrieve the anonymous variable from the table
	auto existing_global_variable = table.getc("a",0);
	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][VariableTable][Failed to retrieve anonymous variable element.]");

	// Result should equal to the new anonymous variable
	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());

	// The type of an anonymous variable should be VOID_TYPE_INDEX
	EXPECT_EQ(existing_global_variable.value().get().type, VOID_TYPE_INDEX);

	// The value of an anonymous variable should be void
	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), false);

	std::cout << "[TEST][VariableTable][Anonymous variable element added and retrieved successfully.]" << std::endl;

}

TEST(TypeConstrainedVariableDeclaration, VariableTableTest) {
	VariableTable table;

	// Test adding a type constrained variable to the table
	auto new_global_variable = table.declare("a",0,typeid(int));
	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][VariableTable][Failed to insert type constrained variable element.]");

	// Retrieve the type constrained variable from the table
	auto existing_global_variable = table.getc("a",0);
	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][VariableTable][Failed to retrieve type constrained variable element.]");

	// Result should equal to the new type constrained variable
	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());

	// The type of a type constrained variable should be the type we specified
	EXPECT_EQ(existing_global_variable.value().get().type, typeid(int));

	// The value of a type constrained variable should be std::nullopt
	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), false);

	std::cout << "[TEST][VariableTable][Type constrained variable element added and retrieved successfully.]" << std::endl;

	// Test adding an existing type constrained variable to the table
	// Attempt to add the same type constrained variable to the table
	// Should return nullopt
	auto new_global_variable2 = table.declare("a",0,typeid(int));
	EXPECT_EQ(new_global_variable2.has_value(), false);
	std::cout << "[TEST][VariableTable][Successfuly failed to insert existing type constrained variable element.]" << std::endl;

	// Test adding a type constrained variable to the table with a different type
	// Attempt to add the same type constrained variable to the table
	// Should return nullopt
	auto new_global_variable3 = table.declare("a",0,typeid(float));
	EXPECT_EQ(new_global_variable3.has_value(), false);
	std::cout << "[TEST][VariableTable][Successfuly failed to insert type constrained variable element with a different type.]" << std::endl;

	// Clear the table
	table.clear();

	// table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][VariableTable][Table cleared successfully.]" << std::endl;
}

TEST(TestFullVariableDeclaration, VariableTableTest) {
	VariableTable table;

	// Test adding a full variable to the table
	auto new_global_variable = table.declare("a",0,typeid(int),1);
	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][VariableTable][Failed to insert full variable element.]");

	// Retrieve the full variable from the table
	auto existing_global_variable = table.getc("a",0);
	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][VariableTable][Failed to retrieve full variable element.]");

	// Result should equal to the new full variable
	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());

	// The type of a full variable should be the type we specified
	EXPECT_EQ(existing_global_variable.value().get().type, typeid(int));

	// The value shoould be the value we specified
	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), true);

	EXPECT_EQ(std::any_cast<int>(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get()), 1);

	std::cout << "[TEST][VariableTable][Full variable element added and retrieved successfully.]" << std::endl;

	// Test adding an existing full variable to the table
	// Attempt to add the same full variable to the table
	// Should return nullopt
	auto new_global_variable2 = table.declare("a",0,typeid(int),1);
	EXPECT_EQ(new_global_variable2.has_value(), false);
	std::cout << "[TEST][VariableTable][Successfuly failed to insert existing full variable element.]" << std::endl;

	// Test adding a full variable to the table with a different type
	// Attempt to add the same full variable to the table
	// Should return nullopt
	auto new_global_variable3 = table.declare("a",0,typeid(float),1);
	EXPECT_EQ(new_global_variable3.has_value(), false);
	std::cout << "[TEST][VariableTable][Successfuly failed to insert full variable element with a different type.]" << std::endl;

	// Clear the table
	table.clear();

	// table should be empty
	EXPECT_TRUE(table.empty());

	std::cout << "[TEST][VariableTable][Table cleared successfully.]" << std::endl;
}

//TEST(AnyPointConstruct, AnyPointerTest) {
//	AnyTypePtr a;
//
//	a.construct(5);
//	a.construct(5.0f);
//	a.construct(std::string("Hello World"));
//
//	// You can check the type of the value
//	if(a.is<ViperType::int_>())
//		std::cout << a.get<ViperType::int_>() << std::endl;
//	else if(a.is<ViperType::real_>())
//		std::cout << a.get<ViperType::real_>() << std::endl;
//	else if(a.is<ViperType::string_>())
//		std::cout << a.get<ViperType::string_>() << std::endl;
//
//	// You can also use a visitor pattern to visit the type
//	auto my_printer = [](auto& value) -> void {
//		if (value.is<ViperType::int_>())
//			std::cout << value.get<ViperType::int_>() << std::endl;
//		else if (value.is<ViperType::real_>())
//			std::cout << value.get<ViperType::real_>() << std::endl;
//		else if (value.is<ViperType::string_>())
//			std::cout << value.get<ViperType::string_>() << std::endl;
//	};
//
//	// You can also use a visitor pattern to visit the type
//	auto my_cooler_printer = [](const auto& value,std::string msg)-> void {
//		if (value.is<ViperType::int_>())
//			std::cout << value.get<ViperType::int_>() << msg.c_str() << std::endl;
//		else if (value.is<ViperType::real_>())
//			std::cout << value.get<ViperType::real_>() << msg.c_str() << std::endl;
//		else if (value.is<ViperType::string_>())
//			std::cout << value.get<ViperType::string_>() << msg.c_str() << std::endl;
//	};
//
//	auto bound_cool_printer = std::bind(my_cooler_printer, std::placeholders::_1, std::string(" is a cool number!"));
//
//	a.visit(my_printer);
//	a.visit(bound_cool_printer);
//
//
//	// You can also create a visitor which returns and takes arguments directly.
//	auto my_number_generator = [](auto& value, int number) -> int {
//		if (value.is<ViperType::int_>())
//			return value.get<ViperType::int_>() + number;
//		else if (value.is<ViperType::real_>())
//			return value.get<ViperType::real_>() + number;
//		else
//			return number;
//	};
//
//	// Bind the number generator
//	auto bound_number_generator = std::bind(my_number_generator, std::placeholders::_1, 5);
//
//	auto myint = a.poly_visit<int>(bound_number_generator); // Visit and return the result of the visitor
//	a.poly_visit<void>(my_printer); // void visitor
//	a.poly_visit<void>(bound_cool_printer); // void visitor with bound arguments.
//
//	// Version with mandatory return type and optional arguments
//	// If we add the second template specialization to the visitor, we can pass arguments directly to the visitor
//	a.poly_visit<void>(my_cooler_printer, std::string(" is a cool number!"));
//
//	// not specifying return type ?? = void visitor
//	a.poly_visit(my_printer);
//
//	// if we try to use the wrong return type, we will get a compile error 
//	//a.poly_visit(bound_number_generator);
//
//	// But if we create a specialization for all non voids?
//    auto integer = a.poly_visit(bound_number_generator);
//
//	// Now what if we want to pass arguments to the visitor?
//	// We can use std::bind to bind the arguments to the visitor
//	//auto bound_cool_printer = std::bind(my_cooler_printer, std::placeholders::_1, std::string(" is a cool number!"));
//	// or
//	// We can create another template specialization for the visitor which takes arguments
//	auto integer2 = a.poly_visit(my_number_generator, 5); // Amazing!
//
//	// Try a void visitor with arguments
//	a.poly_visit(my_cooler_printer, std::string(" is a cool number!"));
//
//
//
//	//a.visit(std::function<void(AnyTypePtr&,std::string)>(my_cooler_printer), std::string(" is a cool number!"));
//	
//	std::cout << "[TEST][AnyPointer][Any pointer constructed successfully.]" << std::endl;
//
//
//
//}
//
//TEST(TestCaseName, TestName) {
//	using ViperIdTable = IdTable<ViperIdentityCategory>;
//	
//	ViperIdTable table;
//	TypeTable type_table;
//	VariableTable variable_table;
//
//	// Add a new global type identity to the table
//	auto new_global_type_identity = table.add<ViperIdTable::Id::TYPE>("int",0);
//
//	if (new_global_type_identity.has_value()) { // Identity has been added to the table
//		// Register the type with the type table
//		type_table.add(new_global_type_identity->get().name, 0, typeid(int));
//
//		// we can also retrieve the registed type from the type table
//		auto registered_type = type_table.get(new_global_type_identity->get().name, 0); // Get a registered type from the type table
//
//		// we can also declare a variable of the registered type 
//		variable_table.declare("a", 0, registered_type->get().type, 1); // Declare a global variable 'a' of type 'int' with value 1.
//
//		// we can retrieve a reference to the std::any value of the variable(pointer)
//		auto value_ptr = variable_table.get_value_ref("a", 0);
//
//		// we can also retrieve the current value of the variable
//		const auto & cast_value = variable_table.get_cast_value_ref<int>("a", 0);
//	}
//	else {
//		// identity already exists, must get() to get the identity
//		// We can assume that means the identity has already been registered with the type table
//		auto existing_global_type_identity = table.get<ViperIdTable::Id::TYPE>("int", 0);
//
//		// If your language supports re-defining types, you can do this:
//		// Otherwise you can throw an error or do nothing.
//		// Register the type with the type table
//		// type_table.replace(new_global_type_identity->get().name, 0, typeid(int));
//
//		// we can also retrieve the registed type from the type table
//		//auto registered_type = type_table.get(existing_global_type_identity->get().name, 0);
//		// retrieve the type_index
//		//auto registered_type_index = registered_type->get().type;
//
//		// register the type with the type table 
//		// this would be dependant on the language implementation
//		// you could call this a "type alias" or "type synonym"
//		// you could throw an error or do nothing if the type already exists
//		//type_table.add("integer", 0, registered_type_index);
//
//		// we can also declare a variable of the type
//		auto registered_type = type_table.get(existing_global_type_identity->get().name, 0); // Get a registered type from the type table
//		// we can also declare a variable of the registered type 
//		variable_table.declare("a", 0, registered_type->get().type, 1); // Declare a global variable 'a' of type 'int' with value 1.
//
//		// we can retrieve a reference to the std::any value of the variable(pointer)
//		auto value_ptr = variable_table.get_value_ref("a", 0);
//
//		// we can also retrieve the current value of the variable
//		const auto& cast_value = variable_table.get_cast_value_ref<int>("a", 0);
//	}
//}
//
//
//TEST(AnonymousVariableDeclaration2, VariableTableUsingAnyPtrTest) {
//	VariableTable2 table;
//
//	// Test adding an anonymous variable to the table
//	auto new_global_variable = table.declare("a", 0);
//	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][AnyPtrVariableTable][Failed to insert anonymous variable element.]");
//
//	// Retrieve the anonymous variable from the table
//	auto existing_global_variable = table.getc("a", 0);
//	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][AnyPtrVariableTable][Failed to retrieve anonymous variable element.]");
//
//	// Result should equal to the new anonymous variable
//	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());
//
//	// The type of an anonymous variable should be VOID_TYPE_INDEX
//	EXPECT_EQ(existing_global_variable.value().get().type, VOID_TYPE_INDEX);
//
//	// The value of an anonymous variable should be None
//	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), false);
//
//	std::cout << "[TEST][AnyPtrVariableTable][Anonymous variable element added and retrieved successfully.]" << std::endl;
//
//
//}
//
//TEST(TypeConstrainedVariableDeclaration2, VariableTableUsingAnyPtrTest) {
//	VariableTable2 table;
//
//	// Test adding a type constrained variable to the table
//	auto new_global_variable = table.declare("a", 0, typeid(int));
//	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][VariableTable][Failed to insert type constrained variable element.]");
//
//	// Retrieve the type constrained variable from the table
//	auto existing_global_variable = table.getc("a", 0);
//	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][VariableTable][Failed to retrieve type constrained variable element.]");
//
//	// Result should equal to the new type constrained variable
//	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());
//
//	// The type of a type constrained variable should be the type we specified
//	EXPECT_EQ(existing_global_variable.value().get().type, typeid(int));
//
//	// The value of a type constrained variable should be std::nullopt
//	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), false);
//
//	std::cout << "[TEST][VariableTable][Type constrained variable element added and retrieved successfully.]" << std::endl;
//
//	// Test adding an existing type constrained variable to the table
//	// Attempt to add the same type constrained variable to the table
//	// Should return nullopt
//	auto new_global_variable2 = table.declare("a", 0, typeid(int));
//	EXPECT_EQ(new_global_variable2.has_value(), false);
//	std::cout << "[TEST][VariableTable][Successfuly failed to insert existing type constrained variable element.]" << std::endl;
//
//	// Test adding a type constrained variable to the table with a different type
//	// Attempt to add the same type constrained variable to the table
//	// Should return nullopt
//	auto new_global_variable3 = table.declare("a", 0, typeid(float));
//	EXPECT_EQ(new_global_variable3.has_value(), false);
//	std::cout << "[TEST][VariableTable][Successfuly failed to insert type constrained variable element with a different type.]" << std::endl;
//
//	// Clear the table
//	table.clear();
//
//	// table should be empty
//	EXPECT_TRUE(table.empty());
//
//	std::cout << "[TEST][VariableTable][Table cleared successfully.]" << std::endl;
//}
//
//TEST(TestFullVariableDeclaration2, VariableTableUsingAnyPtrTest) {
//	VariableTable2 table;
//
//	// Test adding a full variable to the table
//	auto new_global_variable = table.declare("a", 0, typeid(int), 1);
//	EXPECT_TRUE(new_global_variable.has_value() && "[TEST][VariableTable][Failed to insert full variable element.]");
//
//	// Retrieve the full variable from the table
//	auto existing_global_variable = table.getc("a", 0);
//	EXPECT_TRUE(existing_global_variable.has_value() && "[TEST][VariableTable][Failed to retrieve full variable element.]");
//
//	// Result should equal to the new full variable
//	EXPECT_EQ(new_global_variable.value().get(), existing_global_variable.value().get());
//
//	// The type of a full variable should be the type we specified
//	EXPECT_EQ(existing_global_variable.value().get().type, typeid(int));
//
//	// The value shoould be the value we specified
//	EXPECT_EQ(table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get().has_value(), true);
//
//	EXPECT_EQ((table.get_value_ref(existing_global_variable.value().get().identity, existing_global_variable.value().get().scope).value().get()).get<ViperType::int_>(), 1);
//
//	std::cout << "[TEST][VariableTable][Full variable element added and retrieved successfully.]" << std::endl;
//
//	// Test adding an existing full variable to the table
//	// Attempt to add the same full variable to the table
//	// Should return nullopt
//	auto new_global_variable2 = table.declare("a", 0, typeid(int), 1);
//	EXPECT_EQ(new_global_variable2.has_value(), false);
//	std::cout << "[TEST][VariableTable][Successfuly failed to insert existing full variable element.]" << std::endl;
//
//	// Test adding a full variable to the table with a different type
//	// Attempt to add the same full variable to the table
//	// Should return nullopt
//	auto new_global_variable3 = table.declare("a", 0, typeid(float), 1);
//	EXPECT_EQ(new_global_variable3.has_value(), false);
//	std::cout << "[TEST][VariableTable][Successfuly failed to insert full variable element with a different type.]" << std::endl;
//
//	// Clear the table
//	table.clear();
//
//	// table should be empty
//	EXPECT_TRUE(table.empty());
//
//	std::cout << "[TEST][VariableTable][Table cleared successfully.]" << std::endl;
//}

/*
#type int = &int;
#static #var Foo int = 5; // Must be static or else an error, cannot expose non-static variables
// Non-static variables are dependand on scipt instances, and cannot be exposed to the namespace scope.
// A workaround would be to use a static var to hold the data and set it from within the script.

#exposed #func FooFoo(abar) = abar.Foo + Foo;
#func FooFoo2(abar) = abar.Foo + Foo;

#class Bar {
	#var Foo int = 10;
}

#expose Foo;

#return FooFoo(Bar()); // Note we are calling Bar(), a default constructor,

*/


template <typename CallableT, typename... ValTs>
auto apply_callable_impl(CallableT&& callable, ValTs... v) {
	return callable(v...);
}
// The interface to call. Sadly, it needs to dispatch to another function
// to deduce the sequence of indices created from std::make_index_sequence<N>
template <typename CallableT>
auto apply_callable(CallableT&& callable, auto&&... args) {
	return apply_callable_impl(std::forward<CallableT>(callable), std::forward<decltype(args)>(args)...);
}


template<class CallableT, class Tuple, std::size_t... Is>
auto apply_callable_to_tuple_impl(CallableT&& callable,
	const Tuple& tup,
	std::index_sequence<Is...>)
{
	return apply_callable(callable, std::get<Is>(tup)...);
}

template<class CallableT, class... Args>
auto apply_callable_to_tuple(CallableT&& callable,
	const std::tuple<Args...>& t)
{
	return apply_callable_to_tuple_impl(std::forward<CallableT>(callable), std::forward<const std::tuple<Args...> &>(t), std::index_sequence_for<Args...>{});
}

namespace candi {

	struct script_example1 {
		std::unordered_map<std::string, std::any> exposed;
		auto run() {
			using type_int = int;
			type_int Foo = 5;

			auto FooFoo = [Foo](auto abar) {
				return abar.Foo + Foo;
			};

			class Bar {
			public:
				int Foo = 10;
			};

			/* Expose Foo */
			exposed["Foo"] = Foo;

			return FooFoo(Bar());
		}
	};

	/*
example2.candi
// These classes are unrelated in heiarchy.
// But We can still make a function that works with all of them.

#class Horse {
	#func make_sound() { #return "Neigh!"};
}

#class Cow {
	#func make_sound() { #return "Moo!"};
}

#class Wolf {
	#func make_sound() { #return "Oooo!"};
}

#class Cricket {
	#func make_sound() { #return "Chirp!"};
}

#func make_sound(animal) {
	#return animal.make_sound();
}

#var farm_animals = {Horse(), Cow()};
#var all_animals = farm_animals + {Horse(), Cow(), Sheep()}; // You can combine the generic list.


#func make_sounds(animal_list{}) {
	#var sounds &string;
	#for(animal : animal_list) {
		sounds += make_sound(animal);
	}
	#return sounds;
}

#return make_sounds(all_animals);

	*/

// Typedefs for ease of reading on stackoverflow, tranpilation would use the actual types/method calls.
using any_list = std::vector<std::any>;
any_list concat_vector(const any_list& a, const any_list& b) {
any_list result;
result.reserve(a.size() + b.size());
result.insert(result.end(), a.begin(), a.end());
result.insert(result.end(), b.begin(), b.end());
return result;
}

any_list operator+(const any_list& a, const any_list& b) {
return concat_vector(a, b);
}

// Classes are generated here:
class Horse {
public:
};
std::string make_sound(const Horse&) {
	return "Neigh!";
}

class Cow {
public:
};
std::string make_sound(const Cow&) {
	return "Moo!";
}

class Wolf {
public:
};
std::string make_sound(const Wolf&) {
	return "Oooo!";
}

class Cricket {
public:
};
std::string make_sound(const Cricket&) {
	return "Chirp!";
}


// CAUTION: The following deleted functions serve 2 purposes:
// 1. Prevent the compiler from complaining about missing global functions
//    `serialize()` and `draw()` when seeing the using declarations in
//    `ShapeModel::serialize()` and `ShapeModel::draw()`, as if the compiler
//    did not see the `friend` definitions within `class Shape`.
// 2. Prevent runaway recursion in case a concrete `Shape` such as `Circle`
//    does not define a `serialize(const Circle&)` or `draw(const Circle&)`
//    function.
// 3. On msvc we must forward declare everything
//#ifdef __clang__ 

// CAUTION: Workaround for clang and msvc.
// The following forward declarations of explicit specialization of
// `serialize()` and `draw()` prevent Clang from complaining about redefintion
// errors.

// 0.
// Each function must be defined as a deleted free function
template<typename T>
std::string make_sound(const T & self) = delete;

//all metaclasess are defined here
class candi_metaclass_has_make_sound;

template <>
std::string make_sound(const candi_metaclass_has_make_sound& shape);
//#endif  // __clang__


// 1 For each function and return type of a function of a class of a name, we generate a concept which checks if the class has the function.
// The [string]make_sound(void) was defined in the script, so we generate a concept for it.
template <typename T>
concept candi_metaclass_concept_has_make_sound = requires(T t) {
	{ make_sound(t) } -> std::same_as<std::string>;
};

#include "type_erasure_example.hpp"
// 2 we also generate a metaclass
class candi_metaclass_has_make_sound {
	// NOTE: Definition of the explicit specialization has to appear separately
	// later outside of class `candi_metaclass_has_make_sound`, otherwise it results in error such as:
	//
	// ```
	// error: defining explicit specialization 'make_sound<candi_metaclass_has_make_sound>' in friend declaration
	// ```
	//
	// Reference: https://en.cppreference.com/w/cpp/language/friend

	// 3  The class will have a friend declaration for each function of the concept. Note this is a template specialization.
	friend std::string make_sound<>(const candi_metaclass_has_make_sound & self);

	// 4 Inside the metaclass we define a virtual interface for the metaclass type
	// See The External Polymorphism Design Pattern
	class candi_metaclass_interface_has_make_sound {
	public:
		virtual ~candi_metaclass_interface_has_make_sound() {} // Virtual destructor
		// 5 For each function of the concept, we define a pure virtual function.
		virtual std::string make_sound() const = 0;

		// The Prototype Design Pattern for copying objects.
		virtual std::unique_ptr<candi_metaclass_interface_has_make_sound> clone() const = 0;

	};

	// 6 We define a model which inherits from the interface.
	template <typename T>
	class candi_metaclass_model_has_make_sound : public candi_metaclass_interface_has_make_sound {
		T self_;
		public:
			candi_metaclass_model_has_make_sound(const T& self) : self_(self) {}

			// 7. We implement an override for each virtual function of the interface which calls the 'friend' function declared in the metaclass.
			std::string make_sound() const override {
				// CAUTION: The using declaration tells the compiler to look up the free
				// make_sound() function rather than the member function.
				//
				// Reference: https://stackoverflow.com/a/32091297/4475887
				using candi::make_sound; // Use the static function
				return make_sound(self_); // call the function on self.
			}

			// 8. We implement the Prototype Design Pattern for copying objects.
			std::unique_ptr<candi_metaclass_interface_has_make_sound> clone() const override {
				return std::make_unique<candi_metaclass_model_has_make_sound<T>>(*this);
			}
	};

	// 9. We define a member pointer to the interface which will hold the model.
	// See The Bridge Design Pattern
	std::unique_ptr<candi_metaclass_interface_has_make_sound> implementation_;

	// 10. We define a constructor which takes a reference to the model and constructs the interface.
public:
	template<candi_metaclass_concept_has_make_sound T>
	candi_metaclass_has_make_sound(const T& self) : implementation_{ new candi_metaclass_model_has_make_sound<T>(self) } {}

	// 11. We define a copy construct which clones the model.
	candi_metaclass_has_make_sound(const candi_metaclass_has_make_sound& other) : implementation_{ other.implementation_->clone() } {}

	// 12. We define a move constructor which moves the model.
	candi_metaclass_has_make_sound(candi_metaclass_has_make_sound&& other) noexcept : implementation_{ std::move(other.implementation_) } {}

	// 13. We define a move and copy assignment operator
	candi_metaclass_has_make_sound& operator=(const candi_metaclass_has_make_sound & other) {
		implementation_ = other.implementation_->clone();
		return *this;
	}

	candi_metaclass_has_make_sound& operator=(candi_metaclass_has_make_sound&& other) noexcept{
		implementation_ = std::move(other.implementation_);
		return *this;
	}
	
};

// 14. We define the friend function which calls the virtual function of the interface for each function of the concept.
template<>
std::string make_sound(const candi_metaclass_has_make_sound& self) {
	return self.implementation_->make_sound();
}

template <typename T, typename = void>
struct is_iterable : std::false_type {};

// this gets used only when we can call std::begin() and std::end() on that type
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T&>())),
	decltype(std::end(std::declval<T&>()))
>
> : std::true_type {};

// Here is a helper:
template <typename T>
constexpr bool is_iterable_v = is_iterable<T>::value;

template<typename T>
concept candi_metaclass_concept_iterable_container_of_has_make_sound = requires(T t) {
	requires is_iterable_v<T>;
	{ make_sound(*std::begin(t)) } -> std::same_as<candi_metaclass_has_make_sound&>;
};
struct script_example2 {

auto run() {
	// 15. define a method object for the concept
	auto make_sound_method = [](candi_metaclass_has_make_sound& animal) {
		return make_sound(animal);
	};

	// WE KNOW farm_animals is of type std::vector<std::any> holding Horse, Cow types in the compilation stage - so we reflect that in the type. 
	// Check all properties of all insterted types. The vector now holds a metaclass which fufills all the requirements of the types. 
	// Compiler determined that only common thing is the make_sound method, so it created a metaclass for that - class it already generated - so we can use it.
	std::vector<candi_metaclass_has_make_sound> farm_animals;
	farm_animals.emplace_back(Horse());
	farm_animals.emplace_back(Cow());

	// make_sounds is a free method. The requirements are that animal_list be iterable and that each element have a make_sound method.
	// New concept is generate for the list of has_make_sound metaclasses.
	auto make_sounds = [](auto& animal_list) {
		// How can we know its a list ? We can't.
		std::string sounds;
		for (auto & animal : animal_list) { // Note: concept is used to validate the type.
			sounds += make_sound(animal);
		}
		return sounds;
	};


	return make_sounds(farm_animals);
}
};
};

#include "type_erasure_example.hpp"

TEST(TestFullVariableDeclaration2, SampleTranspilation) {

	candi::script_example1 script;
	auto result = script.run();
	std::cout << "Script result: " << result << std::endl;

	// After running you can access the exposed variables
	auto exposed_Foo = script.exposed["Foo"];
	std::cout << "Script exposed variable: " << std::any_cast<int>(exposed_Foo) << std::endl;

	// Type Erasure example script

	candi::script_example2 script2;

	auto result2 = script2.run();

	std::cout << "Script2 result: " << result2 << std::endl;


	




}