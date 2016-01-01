/*
 * Copyright (C) 2014      absurdworlds
 * Copyright (C) 2014-2015 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_math_angle
#define _aw_math_angle
#include <aw/math/math.h>
#include <aw/math/constants.h>

namespace aw {
namespace math {
//! Convert degrees to radians
template<typename T>
inline T degToRad(T deg)
{
	return deg * RadiansInDegree;
}

//! Convert radians to degrees
template<typename T>
inline T radToDeg(T rad)
{
	return rad * DegreesInRadian;
}

/*!
 * Normalize angle between -180 and 180 degrees
 * \param angle
 *    angle to normalize, in degrees
 * \return
 *    input angle normalized to (-180;180] range
 */
inline f32 normalizeAngle(f32 angle)
{
	angle = fmod(angle, 360.0f);
	return    angle >   180.0f ? angle - 360.0f
		: angle <= -180.0f ? angle + 360.0f 
		: angle;
}

/*! Alias for normalizeAngle */
inline f32 wrapAngle(f32 angle)
{
	return normalizeAngle(angle);
}

/*!
 * Normalize angle between -Pi and Pi radians
 * \param angle Value in radians to normalize
 * \return Angle in (-Pi;Pi] range
 */
inline f32 wrapAngleRad(f32 angle)
{
	angle = fmod(f64(angle), DoublePi);
	return    angle >   Pi ? angle - DoublePi
		: angle <= -Pi ? angle + DoublePi 
		: angle;
}
} //namespace math
} //namespace aw
#endif //_aw_math_