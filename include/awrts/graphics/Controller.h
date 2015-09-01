/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Controller_
#define _awrts_Controller_

namespace awrts {
namespace graphics {
//! Class used to control scene node behavior
class Controller {
public:
	//! Virtual destructor
	virtual ~Controller()
	{
	}

	virtual bool update() = 0;
};

} // namespace graphics
} // namespace awrts
#endif//_awrts_Controller_