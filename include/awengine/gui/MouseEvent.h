/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_MouseEvent_
#define _awrts_MouseEvent_
#include <awengine/common/types.h>
#include <awengine/common/Event.h>

namespace awrts {
namespace gui {
enum MouseState {
	MOUSE_LEFT = 0x01,
	MOUSE_RIGHT = 0x02,
	MOUSE_MIDDLE = 0x04
};

class MouseEvent : EventId<MouseEvent> {
public:
	enum Action {
		Moved,
		Wheel,
		LButtonDown,
		RButtonDown,
		MButtonDown,
		LButtonUp,
		RButtonUp,
		MButtonUp,
		LDoubleClick,
		RDoubleClick,
		MDoubleClick,
		LTripleClick,
		RTripleClick,
		MTripleClick
	}

private:
	Action action;
	i32 mouseX;
	i32 mouseY;
	f32 mouseZ; // wheel
	u8 buttonStates;
};
} // namespace gui
} // namespace awrts
#endif //_awrts_MouseEvent_
