#pragma once
#include <type_traits>

using ue_byte_t= char;

using ue_float32_t= float;
using ue_float64_t= double;
using ue_float128_t= long double;

template <typename T>
concept ue_standard_layout= std::is_standard_layout<T>::value;

template <typename T>
concept ue_trivial= std::is_trivial<T>::value;