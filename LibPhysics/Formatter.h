#ifndef _FORMATTER_
#define _FORMATTER_

#pragma once

#include <climits>
#include <cstdarg>
#include <cstdio>
#include <vector>

class Formatter {
private:
	std::vector<char> formatBuffer;
public:
	Formatter(const char* formatter, ...);
	
	const char* cStr();

	operator const char* () {
		return this->cStr();
	}
};

#endif