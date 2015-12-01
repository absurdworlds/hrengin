/*
 * aw  engine
 * Copyright (C) 2013-2015  absurdworlds
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License, version 3
 * as published by the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>. 
 */
#ifndef _aw_sound_
#define _aw_sound_
#include <aw/config/visibility.h>

#ifdef AW_MODULE_SOUND
	#define AW_SND_EXP AW_EXPORT
#else
	#define AW_SND_EXP AW_IMPORT
#endif

// Namespace descriptions for Doxygen
namespace aw {
//! Everything related to audio output is contained in this namespace
namespace sound {}
}
#endif//_aw_sound_
