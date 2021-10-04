#ifndef _PHYSICS_GLOBAL_INCLUDE_
#define _PHYSICS_GLOBAL_INCLUDE_

#pragma once

#ifdef _PHYSICS_DOUBLE_PRECISION
	typedef double FloatType;
	typedef unsigned long long IntegralType;
#else
	typedef float FloatType;
	typedef unsigned long IntegralType;
#endif

#define PHYSICS_NAMESPACE_MAKE_NAME(SUB_SPACE)	physics_##SUB_SPACE

#define PHYSICS_NAMESPACE_BEGIN(SUB_SPACE)		namespace PHYSICS_NAMESPACE_MAKE_NAME(SUB_SPACE) {
#define PHYSICS_NAMESPACE_END					};

#include <stdexcept>
#include <ostream>

static inline bool __PHYSICS_INIT__() {

	return true;
}

extern const bool __PHYSICS_INITD__;

#endif