template <char ...Chars>
struct type_string_t {
	static constexpr const char size = { sizeof...(Chars) };
	static constexpr const char data[sizeof...(Chars)] = { Chars... };
};

template <char s(std::size_t), std::size_t ...I>
consteval auto type_string_impl(std::index_sequence<I...>) {
	return type_string_t<s(I)...>();
}

#define type_string(s) decltype(type_string_impl<[](size_t i) {return s[i];}> (std::make_index_sequence<sizeof(s)-1>{}))

struct any_type {
	std::any val;

	any_type() = default;
	any_type(std::any val) : val(val) {}

	template <typename T>
	constexpr auto get() const {
		if constexpr (std::is_same_v<T, type_string("int")>) {
			return std::any_cast<int>(val);
		}
		else if constexpr (std::is_same_v<T, type_string("float")>) {
			return std::any_cast<float>(val);
		}
		else {
			return {};
		}
	}
};

struct CandilTypeKind {
	static constexpr char int_ = 'i';
	static constexpr char unsigned_ = 'u';
	static constexpr char real_ = 'r';
	static constexpr char char_ = 'c';
	static constexpr char bool_ = 'b';
	static constexpr char string_ = 's';
	static constexpr char array_ = 'a';
	static constexpr char tuple_ = 't';
	static constexpr char method_ = 'f';
	static constexpr char class_ = 'l';
	static constexpr char enum_ = 'e';
	static constexpr char struct_ = 's';
	static constexpr char union_ = 'n';
	static constexpr char void_ = 'v';
};

/// A CandilType is an Identifier associated with a type.
template<typename IdentityT, typename TypeT = void>
struct CandilType {};

using candil_int_identifier = type_string("int");
using candil_float_identifier = type_string("float");
using candil_char_identifier = type_string("char");
using candil_bool_identifier = type_string("bool");

template<>
struct CandilType<void, void> {
	using identity_t = type_string("void");
	using type_t = void;
	static constexpr auto identity = type_string("void")::data;
	static constexpr char type = CandilTypeKind::void_;
};

using candil_void = CandilType<void, void>;

template<>
struct CandilType<candil_int_identifier, void> {
	using identity_t = type_string("int");
	using type_t = int;
	static constexpr auto identity = type_string("int")::data;
	static constexpr char type = CandilTypeKind::int_;
};

template<>
struct CandilType<candil_float_identifier, void> {
	using identity_t = type_string("float");
	using type_t = float;
	static constexpr auto identity = type_string("float")::data;
	static constexpr char type = CandilTypeKind::real_;
};

template<>
struct CandilType<candil_char_identifier, void> {
	using identity_t = type_string("char");
	using type_t = char;
	static constexpr auto identity = type_string("char")::data;
	static constexpr char type = CandilTypeKind::char_;
};

template<>
struct CandilType<candil_bool_identifier, void> {
	using identity_t = type_string("bool");
	using type_t = bool;
	static constexpr auto identity = type_string("bool")::data;
	static constexpr char type = CandilTypeKind::bool_;
};

// A candil variable is an Identity associated with a CandilType.
template<typename IdentityT, typename TypeIdentityT>
struct CandilVariable {
	using identity_t = IdentityT;
	using type_identity = TypeIdentityT;
	using type_t = typename CandilType<TypeIdentityT>;
	using value_t = typename CandilType<TypeIdentityT>::type_t;

	value_t value{};

	consteval CandilVariable() = default;
	consteval CandilVariable(value_t value) : value(value) {}
};

// A candil method is a functor object, associated with a return type, and zero or more arguments.
template<typename IdentityT, typename FunctorT, typename RetTypeIdentityT = std::tuple<>, typename ArgTypeIdentityT = std::tuple<>>
struct CandilMethod {
	using identity_t = IdentityT;
	using functor_t = FunctorT;
	using return_type_t = RetTypeIdentityT;
	using argument_type_t = ArgTypeIdentityT;

	static constexpr auto functor_v = functor_t{};

	inline static constexpr return_type_t call(argument_type_t arg) {
		return functor_v(arg);
	}
};


/*template<typename IdentityT, typename FunctorT, typename CandilTypeRet, typename ...CandilTypeArgs >
struct CandilMethod {
	using identity_t = IdentityT;
	using return_tuple_t = std::tuple<CandilTypeRet>;
	using argument_tuple_t = std::tuple<CandilTypeArgs::type_t...>;
	using method_t = FunctorT;
	static constexpr auto identity = IdentityT::data;
	static constexpr char type = CandilTypeKind::method_;
	static constexpr method_t method{};

	static constexpr auto call(argument_tuple_t args) {
		return method(args);
	}

};


template<typename IdentityT,typename MethodsTs, typename VariableTs>
struct CandilClass {
	using identity_t = IdentityT;
	using methods_t = MethodsTs;
	using variables_t = VariableTs;
	static constexpr auto identity = IdentityT::data;
	static constexpr char type = CandilTypeKind::class_;

	static constexpr methods_t methods{};
	static constexpr variables_t variables{};

	constexpr CandilClass() = default;
	constexpr CandilClass(methods_t methods, variables_t variables) : methods(methods), variables(variables) {}
};	*/

//static_assert(std::is_same_v<CandilVariable<type_string("int"), CandilType<type_string("int"), void>>::value_t, int>);
//static_assert(CandilVariable<type_string("inat"), CandilType<type_string("int"), int>>::identity == type_string("inat")::data);

constexpr auto candil_method_add_int_int_int_object(auto args) {
	return std::make_tuple(std::get<0>(args) + std::get<1>(args));
} using candil_method_add_int_int_int_object_lambda = decltype([](auto args) {
	return candil_method_add_int_int_int_object(args);
});

//auto candil_class_A_member_method_add_int_int_object(auto args) {
//	return std::make_tuple(std::get<0>(std::get<0>(args).variables) + std::get<1>(args));
//} using candil_class_A_member_method_add_int_int_object_lambda = decltype([](auto args) {
//	return candil_class_A_member_method_add_int_int_object(args);
//});




///////////////////////////////////////////////////////////////////////////////////////////////////////
// Sample usage of abstract compile time string identified types.

// use like so:
using candil_int = CandilType <type_string("int")>; // Declare a candil type 'int'.
using candil_int_underlying_t = typename candil_int::type_t; // Get the underlying type of the candil type 'int'.

using candil_variable_a = CandilVariable<type_string("a"), candil_int::identity_t>; // Declare a candil variable 'a' of type 'int'.
using candil_variable_b = CandilVariable<type_string("b"), candil_int::identity_t>; // Declare a candil variable 'b' of type 'int'.

// Variable 'a' is of type 'int'.
static_assert(std::is_same_v<candil_variable_a::type_t, candil_int>); // Check  the candil type of the variable.
static_assert(std::is_same_v<candil_variable_a::value_t, int>); // Check the underlying type of the variable.

// Variable 'b' is of type 'int'.
static_assert(std::is_same_v<candil_variable_b::type_t, candil_int>); // Check the candil type of the variable.
static_assert(std::is_same_v<candil_variable_b::value_t, int>); // Check the underlying type of the variable.

// Compare the candil types of the variables.
static_assert(std::is_same_v<candil_variable_a::type_t, candil_variable_b::type_t>);
static_assert(std::is_same_v<candil_variable_a::type_t::identity_t, candil_variable_b::type_t::identity_t>);

// Compare the identities of the variables, they should not be equal.
static_assert(!std::is_same_v<candil_variable_a::identity_t, candil_variable_b::identity_t>);
///////////////////////////////////////////////////////////////////////////////////////////////////////
// Using and instantiating variables.
constexpr auto candil_variable_a_instance = candil_variable_a{ 1 }; // Instantiate a variable 'a' of type 'int' with value 1.
constexpr auto candil_variable_b_instance = candil_variable_b{ 2 }; // Instantiate a variable 'b' of type 'int' with value 2.

// Compare the values of the variables. They should not be equal.
static_assert(candil_variable_a_instance.value != candil_variable_b_instance.value);

// Create a copy of the variable 'a'.
constexpr auto candil_variable_a_instance_copy = candil_variable_a_instance;

// Create a reference to the variable 'a'.
constexpr auto& candil_variable_a_instance_ref = candil_variable_a_instance;

constexpr auto new_candil_variable_a_instance = candil_variable_a{ candil_variable_a_instance.value + 1 }; // Change the value of the variable 'a' to 2.

// Compare the values of b and new a instances. They should be equal.
static_assert(candil_variable_b_instance.value == new_candil_variable_a_instance.value);
// Compare the values of the new instance and last instance of a. They should not be equal.
static_assert(candil_variable_a_instance.value != new_candil_variable_a_instance.value);


///////////////////////////////////////////////////////////////////////////////////////////////////////
// Using and instantiating methods.
// you may use the type_string, or the typdef identity_t to refer to the identity of the type.
constexpr auto candil_method_add_object(auto args) {
	return std::make_tuple(std::get<0>(args) + std::get<1>(args));
} using candil_method_add_object_lambda = decltype([](auto args) {
	return candil_method_add_object(args);
});

using candil_method_add =
CandilMethod < type_string("add"),						// Identity of the method.
	candil_method_add_object_lambda, 		// Functor object.
	std::tuple<CandilType<type_string("int")>::type_t>, // Return type.
	std::tuple<candil_int::type_t, candil_int::type_t>>;// Argument types.

// Call the method with arguments 1 and 2.
static_assert(std::make_tuple(3) == candil_method_add::call(std::make_tuple(1, 2)));


