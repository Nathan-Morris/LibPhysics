#ifndef _PHYSICS_CONSTANTS_
#define _PHYSICS_CONSTANTS_

#include "PhysicsGlobalInclude.h"

#ifdef _PHYSICS_DOUBLE_PRECISION
	typedef double FloatType;
	typedef unsigned long long IntegralType;
#else
	typedef float FloatType;
	typedef unsigned long IntegralType;
#endif

#pragma once

PHYSICS_NAMESPACE_BEGIN(constants)

extern const FloatType e;
extern const FloatType pi;

PHYSICS_NAMESPACE_END

#endif