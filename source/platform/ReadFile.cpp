/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <stdio.h>

#include <awrts/core/Logger.h>

#include <awrts/io/ReadFile.h>

namespace awrts {
namespace io {

ReadFile::ReadFile(std::string const& path)
	: File(path)
{
	this->open();
}

ReadFile::~ReadFile()
{
	if(isOpen()) {
		fclose(file_);
	}
}

void ReadFile::open()
{
	if (path_.size() == 0) {
		return;
	}

	file_ = fopen(path_.c_str(), "rb");

	if (file_) {
		fseek(file_, 0, SEEK_END);
		size_ = tell();
		fseek(file_, 0, SEEK_SET);
	} else {
	}
}

i32 ReadFile::read(void* buffer, u32 size)
{
	if (!isOpen()) {
		return -1;
	}

	return (i32)fread(buffer, 1, size, file_);
}

i32 ReadFile::seek(i32 offset, bool relative)
{
	if (!isOpen()) {
		return -1;
	}

	return fseek(file_, offset, relative ? SEEK_CUR : SEEK_SET);
}

u32 ReadFile::tell() const
{
	return ftell(file_);
}

u32 ReadFile::getSize() const
{
	return size_;
}

std::string const& ReadFile::getPath() const
{
	return path_;
}

} // namespace io
} // namespace awrts