/*
 * Copyright (C) 2015  absurdworlds
 * Copyright (C) 2015  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_optional_to_string_h
#define aw_optional_to_string_h
#include <aw/types/optional.h>
#include <aw/utility/to_string.h>
namespace aw {
//! Convert nullopt_t to string.
template <>
struct string_converter<nullopt_t> {
	string_converter(nullopt_t) {}

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		return fmt.literal("nullopt");
	}
};

/*!
 * Convert optional to string
 * \return
 *    Contained value, converted to string,
 *    or empty string if optional is empty.
 */
template <typename T>
struct string_converter<optional<T>> {
	optional<T> const& opt;

	template<typename Formatter>
	std::string operator()( Formatter& fmt ) const
	{
		if (opt) fmt.convert( *opt );
		return fmt;
	}
};

} // namespace aw
#endif//aw_optional_to_string_h
