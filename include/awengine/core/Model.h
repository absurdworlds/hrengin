/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Model_
#define _awrts_Model_
#include <vector>
#include <awengine/core/models.h>

namespace awrts {

class Model {
public:
	std::vector<Primitive> primitives;
};

} // namespace awrts
#endif//_awrts_Model_
