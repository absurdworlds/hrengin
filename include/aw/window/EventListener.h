/*
 * Copyright (C) 2015  hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_common_EventListener_
#define _aw_common_EventListener_
#include <aw/common/Event.h>
namespace aw {
class EventListener {
public:
	/*!
	 * Receive an event.
	 * \return
	 *     false if event is consumed (event will
	 *     not propagate further).
	 */
	virtual bool onEvent(Event* event) = 0;
};

} // namespace aw
#endif //_aw_common_EventListener_
