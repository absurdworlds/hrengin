#ifndef _hrengin_ALutil_
#define _hrengin_ALutil_

#include <AL/al.h>

#include <hrengin/common/hrengintypes.h>

inline ALenum toAlEnum(short channels, short samples)
{
	bool stereo = (channels > 1);

	switch (samples) {
	case 16:
		if (stereo) {
			return AL_FORMAT_STEREO16;
		} else {
			return AL_FORMAT_MONO16;
		}
	case 8:
		if (stereo) {
			return AL_FORMAT_STEREO8;
		} else {
			return AL_FORMAT_MONO8;
		}
	default:
		return -1;
	}
}

#endif//_hrengin_ALutil_