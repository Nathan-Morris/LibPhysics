#ifndef _PHYSICS_GLOBAL_INCLUDE_
#define _PHYSICS_GLOBAL_INCLUDE_

#pragma once


#define PHYSICS_NAMESPACE_MAKE_NAME(SUB_SPACE)	physics_##SUB_SPACE

#define PHYSICS_NAMESPACE_BEGIN(SUB_SPACE)		namespace PHYSICS_NAMESPACE_MAKE_NAME(SUB_SPACE) {
#define PHYSICS_NAMESPACE_END					};

#define PHYSICS_DEFAULT_NAMESPACE_BEGIN			namespace physics {
#define PHYSICS_DEFAULT_NAMESPACE_END			PHYSICS_NAMESPACE_END

#ifdef _LIB_PHYSICS_DOUBLE_PRECISION
	typedef double FloatType;
	typedef unsigned long long IntegralType;
#	define strtoft	strtod
#else
	typedef float FloatType;
	typedef unsigned long IntegralType;
#	define strtoft	strtof
#endif

#include <stdexcept>
#include <ostream>
#include <cmath>

static inline bool __PHYSICS_INIT__() {

	return true;
}

extern const bool __PHYSICS_INITD__;

#endif