#ifndef _PHYSICS_UNITS_RATIO_
#define _PHYSICS_UNITS_RATIO_

#pragma once

#include "Units.h"

PHYSICS_NAMESPACE_BEGIN(units)

template<
	const UnitType topUnitType, const UnitType bottomUnitType,
	const FloatType* topToBaseRatio, const FloatType* bottomToBaseRatio
>
class UnitRatio {
private:
	Unit<topUnitType, topToBaseRatio> topUnit;
	Unit<bottomUnitType, bottomToBaseRatio> bottomUnit;

public:

};

PHYSICS_NAMESPACE_END

#endif