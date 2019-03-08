/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hdf_node_h
#define aw_fileformat_hdf_node_h
#include <iosfwd>
#include <string>
#include <algorithm>
#include <aw/types/string_view.h>
#include <aw/fileformat/hdf/value.h>
#include <aw/log/log_fwd.h>
namespace aw::hdf {
inline namespace v1 {
struct parser;

template<typename T>
struct list : private std::vector<std::pair<std::string, T>> {
	typedef std::vector<std::pair<std::string, T>> base_type;

	using iterator   = typename base_type::iterator;
	using value_type = typename base_type::value_type;

	using base_type::begin;
	using base_type::end;

	using base_type::empty;
	using base_type::size;

	T* find(string_view name)
	{
		auto compare_name = [name] (value_type const& pair) {
			return pair.first == name;
		};

		auto it = std::find_if(begin(), end(), compare_name);
		if (it == end())
			return nullptr;
		return &it->second;
	}

	void add(std::string name, T const& node)
	{
		base_type::emplace_back(value_type{std::move(name), node});
	}
};

struct node {
	typedef list<node>::iterator  node_iter;
	typedef list<value>::iterator value_iter;

	template<typename T>
	T try_get(string_view name, T def)
	{
		if (auto* value = values.find(name))
			return value->try_get(def);
		return def;
	}

	bool empty() const
	{
		return values.empty() && nodes.empty();
	}

	list<value> values;
	list<node>  nodes;
};
} // inline namespace v1
} // namespace aw::hdf
#endif//aw_fileformat_hdf_node_h
