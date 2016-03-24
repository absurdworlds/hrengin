/*
 * Copyright (C) 2016  Hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_traits_detection
#define aw_traits_detection
//#include <experimental/type_traits>
#include <aw/types/traits/void_t.h>
namespace aw {
namespace detail {
template <class, template<class...> class Op, class... Args>
struct detector : std::false_type {};

template <template<class...> class Op, class... Args>
struct detector<void_t<Op<Args...>>, Op, Args...> : std::true_type {};
} // namespace detail

template <template<class...> class Op, class... Args>
constexpr auto is_detected = detail::detector<void, Op, Args...>::value;
} // namespace aw
#endif//aw_traits_detection