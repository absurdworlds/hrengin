/*
 * Copyright (C) 2015  hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_common_Event_
#define _awrts_common_Event_
#include <awengine/common/types.h>
namespace awrts {
class Event {
public:
	virtual bool is(size_t id) = 0;
	virtual size_t getType() = 0;
protected:
	static size_t types_count;
};

template <class Derived>
class EventType : public Event {
public:
	static size_t type() {
		static size_t id = eventTypes++;
		return type;
	}

	virtual bool is(size_t id)
	{
		return type() == id;
	}
	virtual size_t getType() {
		return type;
	}
protected:
	EventType<Derived>()
	{
	}
};

template <class E>
E* event_cast(Event* event) {
	if (event.is(E::getType()))
		return static_cast<E*>(event);

	return nullptr;
}
} // namespace awrts
#endif //_awrts_common_Event_
