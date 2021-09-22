#include "Formatter.h"

Formatter::Formatter(const char* formatter, ...) {
	int writtenLen;
	va_list varArgList;

	if (formatter == NULL) {
		return;
	}
	
	va_start(varArgList, formatter);

	// initial formatted buffer length check
	writtenLen = vsnprintf(this->formatBuffer.data(), this->formatBuffer.size(), formatter, varArgList);

	// buffer too small
	if (writtenLen >= this->formatBuffer.size()) {
		// resize buffer to fit formatted string
		this->formatBuffer.resize((size_t)writtenLen + 1);
		
		// write formatted string to buffer
		vsnprintf(this->formatBuffer.data(), this->formatBuffer.size(), formatter, varArgList);
	}

	// encoding error
	else  if (writtenLen < 0) { }

	va_end(varArgList);
}

const char* Formatter::cStr() {
	return this->formatBuffer.data();
}

