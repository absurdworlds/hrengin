/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_ArgumentParser_impl_
#define _awrts_ArgumentParser_impl_
#include <deque>

#include <awengine/core/ArgumentParser.h>

namespace awrts {
namespace core {
namespace impl_ {
class ArgumentParser : public core::ArgumentParser {
public:
	ArgumentParser(char** argv);
	virtual ~ArgumentParser()
	{
	}

	virtual i32 getNextArgument(Argument& tok);
private:
	void parse(char** argv);
	void parseToken(char* argv);
	std::string readString(char* argv);

	std::deque<Argument> tokens_;
	bool term_;
};

} // namespace impl_
} // namespace core
} // namespace awrts
#endif//_awrts_ArgumentParser_impl_
