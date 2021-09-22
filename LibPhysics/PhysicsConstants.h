#ifndef _PHYSICS_CONSTANTS_
#define _PHYSICS_CONSTANTS_

#ifdef _PHYSICS_DOUBLE_PRECISION
	typedef double FloatType;
	typedef unsigned long long IntegralType;
#else
	typedef float FloatType;
	typedef unsigned long IntegralType;
#endif

#pragma once

namespace constants {
	extern const FloatType e;
	extern const FloatType pi;
};

#endif