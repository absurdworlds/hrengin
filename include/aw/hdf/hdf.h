/*
 * Copyright (C) 2013-2016  absurdworlds
 * Copyright (C)      2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_hdf_
#define _aw_hdf_
#include <aw/config.h>

#ifdef AW_MODULE_HDF
	#define AW_HDF_EXP AW_EXPORT
#else
	#define AW_HDF_EXP AW_IMPORT
#endif
#endif//_aw_hdf_
