#ifndef _PHYSICS_UNITS_
#define _PHYSICS_UNITS_

#pragma once

#include <stdexcept>

#include "Formatter.h"
#include "PhysicsConstants.h"
#include "PhysicsGlobalInclude.h"

PHYSICS_NAMESPACE_BEGIN(unit_converions)

const FloatType MICROSECONDS_TO_BASE = (FloatType)(1.0 / 100000);
const FloatType MILLISECONDS_TO_BASE = (FloatType)(1.0 / 1000);
const FloatType SECONDS_TO_BASE = (FloatType)1.0;	// base unit
const FloatType MINUTES_TO_BASE = (FloatType)60.0;
const FloatType HOURS_TO_BASE = (FloatType)3600.0;
const FloatType DAYS_TO_BASE = (FloatType)86400.0;
const FloatType WEEKS_TO_BASE = (FloatType)604800.0;
const FloatType YEARS_TO_BASE = (FloatType)3.154e+7;


const FloatType NANOMETERS_TO_BASE = (FloatType)(1.0 / 1.0e+9);
const FloatType MICROMETERS_TO_BASE = (FloatType)(1.0 / 1.0e+6);
const FloatType MILLIMETERS_TO_BASE = (FloatType)(1.0 / 1000.0);
const FloatType CENTIMETERS_TO_BASE = (FloatType)(1.0 / 100.0);
const FloatType DECIMETERS_TO_BASE = (FloatType)(1.0 / 10.0);
const FloatType METERS_TO_BASE = (FloatType)1.0;	// base unit
const FloatType HECTOMETERS_TO_BASE = (FloatType)100.0;
const FloatType KILOMETERS_TO_BASE = (FloatType)1000.0;
const FloatType NAUTICAL_MILES_TO_BASE = (FloatType)1852.0;
const FloatType MILES_TO_BASE = (FloatType)1609.344;
const FloatType YARDS_TO_BASE = (FloatType)(1.0 / 1094);
const FloatType FEET_TO_BASE = (FloatType)(1.0 / 3.281);
const FloatType INCHES_TO_BASE = (FloatType)(1.0 / 39.37);


const FloatType METRIC_TONS_TO_BASE = (FloatType)1000.0;
const FloatType KILOGRAMS_TO_BASE = (FloatType)1.0;	// base unit
const FloatType GRAMS_TO_BASE = (FloatType)(1.0 / 1000.0);
const FloatType MILLIGRAMS_TO_BASE = (FloatType)(1.0 / 1.0e+6);
const FloatType MICROGRAMS_TO_BASE = (FloatType)(1.0 / 1.0e+9);
const FloatType IMPERIAL_TONS_TO_BASE = (FloatType)1016.05;
const FloatType POUNDS_TO_BASE = (FloatType)0.453592;
const FloatType OUNCES_TO_BASE = (FloatType)(1.0 / 35.274);


const FloatType AMPS_TO_BASE = (FloatType)1.0;	// base unit


const FloatType KELVIN_TO_BASE = (FloatType)1.0;	// base unit


const FloatType MOLES_TO_BASE = (FloatType)1.0;	// base unit


const FloatType CANDELAS_TO_BASE = (FloatType)1.0;	// base unit

const FloatType RADIANS_TO_BASE = (FloatType)1.0;	// base unit
const FloatType DEGREES_TO_BASE = (FloatType)(physics_constants::pi / 180.0);

PHYSICS_NAMESPACE_END

//
//
//

PHYSICS_NAMESPACE_BEGIN(units)

//
// UnitTypes
//

enum class UnitType : unsigned char {
	TIME = 0x0,
	LENGTH = 0x1,
	MASS = 0x2,
	CURRENT = 0x3,
	TEMPERATURE = 0x4,
	SUBSTANCE_QUANTITY = 0x5,
	LUMINOSITY = 0x6,
	ANGLE = 0x7
};
typedef UnitType* pUnitType;
typedef const UnitType cUnitType, * pcUnitType;

static const char* unitTypeName(const UnitType unitType) {
	switch (unitType)
	{
	case UnitType::TIME:				return "Time";
	case UnitType::LENGTH:				return "Length";
	case UnitType::MASS:				return "Mass";
	case UnitType::CURRENT:				return "Electric Current";
	case UnitType::TEMPERATURE:			return "Temperature";
	case UnitType::SUBSTANCE_QUANTITY:	return "Substance Quantity";
	case UnitType::LUMINOSITY:			return "Luminosity";
	case UnitType::ANGLE:				return "Angle";

	default:
		return "None";
	}
}

//
// Generic Unit Class
//

template<const UnitType unitType, const FloatType* toBaseRatio>
class Unit {
private:
	FloatType value = 0.0;

	FloatType valueFromUnitRatio(FloatType inValue, const FloatType* convertToBaseRatio) const {
		return ((inValue * (*convertToBaseRatio))) * (1 / (*toBaseRatio));
	}

public:	// Construction
	Unit(FloatType initialValue) { this->value = initialValue; }
	Unit(const Unit<unitType, toBaseRatio>& copyUnit) : Unit(copyUnit) { }
	Unit() { }

	template<const FloatType* assignToBaseRatio>
	Unit(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value = this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	Unit(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;

public:	// Value Fetching
	UnitType getUnitType() const { return unitType; }
	FloatType getValue() const { return this->value; }
	operator FloatType() { return this->getValue(); }

public:	// Assignment Operations
	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	Unit<unitType, toBaseRatio>& operator=(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;

	template<const FloatType* assignToBaseRatio>
	Unit<unitType, toBaseRatio>& operator=(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value = this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
		return *this;
	}

	Unit<unitType, toBaseRatio>& operator=(FloatType unitValue) {
		this->value = unitValue;
		return *this;
	}

public:	// Arithmetic Member Operations

	template<const FloatType* assignToBaseRatio>
	void operator +=(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value += this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio>
	void operator -=(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value -= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio>
	void operator /=(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value /= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio>
	void operator *=(const Unit<unitType, assignToBaseRatio>& assignUnit) {
		this->value *= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	void operator +=(const FloatType& unitValue) { this->value *= unitValue; }
	void operator -=(const FloatType& unitValue) { this->value -= unitValue; }
	void operator /=(const FloatType& unitValue) { this->value /= unitValue; }
	void operator *=(const FloatType& unitValue) { this->value *= unitValue; }

	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	void operator +=(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;
	
	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	void operator -=(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;
	
	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	void operator *=(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;

	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio>
	void operator /=(const Unit<assignUnitType, assignToBaseRatio>& assignUnit) = delete;

public: // Arithmetic Friend Operations

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator+(
		const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
		FloatType unitValue
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator-(
		const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
		FloatType unitValue
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator*(
		const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
		FloatType unitValue
		);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator/(
		const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
		FloatType unitValue
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator+(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator-(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator/(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator*(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

public:
	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator==(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator!=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator<(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator>(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);
	
	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator<=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend bool operator>=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight);

};

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator+(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.getValue() + unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator-(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.getValue() - unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator/(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.getValue() / unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator*(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.getValue() * unitValue);
}

//
//
//

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator+(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	const Unit<friendUnitType, modderToBaseRatio>& modderUnit
) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.value + friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator-(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	const Unit<friendUnitType, modderToBaseRatio>& modderUnit
) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.value - friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator/(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	const Unit<friendUnitType, modderToBaseRatio>& modderUnit
) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.value / friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
Unit<friendUnitType, friendToBaseRatio> operator*(
	const Unit<friendUnitType, friendToBaseRatio>& friendUnit,
	const Unit<friendUnitType, modderToBaseRatio>& modderUnit
) {
	return Unit<friendUnitType, friendToBaseRatio>(friendUnit.value * friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

//

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator==(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	if (*friendToBaseRatio == *modderToBaseRatio) {
		return equUnitLeft.value == equUnitRight.value;
	}
	return (*friendToBaseRatio * equUnitLeft.value) == (*modderToBaseRatio * equUnitRight.value);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator!=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	return !(equUnitLeft == equUnitRight);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator<(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	if (*friendToBaseRatio == *modderToBaseRatio) {
		return equUnitLeft.value < equUnitRight.value;
	}
	return (*friendToBaseRatio * equUnitLeft.value) < (*modderToBaseRatio * equUnitRight.value);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator>(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	if (*friendToBaseRatio == *modderToBaseRatio) {
		return equUnitLeft.value > equUnitRight.value;
	}
	return (*friendToBaseRatio * equUnitLeft.value) > (*modderToBaseRatio * equUnitRight.value);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator<=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	return !(equUnitLeft > equUnitRight);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
bool operator>=(const Unit<friendUnitType, friendToBaseRatio>& equUnitLeft, const Unit<friendUnitType, modderToBaseRatio>& equUnitRight) {
	return !(equUnitLeft < equUnitRight);
}

//
//
//


//
// Common Unit Definitions
//

// UnitType::TIME
using Microseconds = Unit<UnitType::TIME, &physics_unit_converions::MICROSECONDS_TO_BASE>;
using Milliseconds = Unit<UnitType::TIME, &physics_unit_converions::MILLISECONDS_TO_BASE>;
using Seconds = Unit<UnitType::TIME, &physics_unit_converions::SECONDS_TO_BASE>;
using Minutes = Unit<UnitType::TIME, &physics_unit_converions::MINUTES_TO_BASE>;
using Hours = Unit<UnitType::TIME, &physics_unit_converions::HOURS_TO_BASE>;
using Days = Unit<UnitType::TIME, &physics_unit_converions::DAYS_TO_BASE>;
using Weeks = Unit<UnitType::TIME, &physics_unit_converions::WEEKS_TO_BASE>;
using Years = Unit<UnitType::TIME, &physics_unit_converions::YEARS_TO_BASE>;

// UnitType::LENGTH
using Micrometers = Unit<UnitType::LENGTH, &physics_unit_converions::MICROMETERS_TO_BASE>;
using Nanometers = Unit<UnitType::LENGTH, &physics_unit_converions::NANOMETERS_TO_BASE>;
using Millimeters = Unit<UnitType::LENGTH, &physics_unit_converions::MILLIMETERS_TO_BASE>;
using Centimeters = Unit<UnitType::LENGTH, &physics_unit_converions::CENTIMETERS_TO_BASE>;
using Decimeters = Unit<UnitType::LENGTH, &physics_unit_converions::DECIMETERS_TO_BASE>;
using Meters = Unit<UnitType::LENGTH, &physics_unit_converions::METERS_TO_BASE>;
using Hectometers = Unit<UnitType::LENGTH, &physics_unit_converions::HECTOMETERS_TO_BASE>;
using Kilometers = Unit<UnitType::LENGTH, &physics_unit_converions::KILOMETERS_TO_BASE>;
using NauticalMiles = Unit<UnitType::LENGTH, &physics_unit_converions::NAUTICAL_MILES_TO_BASE>;
using Miles = Unit<UnitType::LENGTH, &physics_unit_converions::MILES_TO_BASE>;
using Yards = Unit<UnitType::LENGTH, &physics_unit_converions::YARDS_TO_BASE>;
using Feet = Unit<UnitType::LENGTH, &physics_unit_converions::FEET_TO_BASE>;
using Inches = Unit<UnitType::LENGTH, &physics_unit_converions::INCHES_TO_BASE>;

// UnitType::MASS
using MetricTons = Unit<UnitType::MASS, &physics_unit_converions::METRIC_TONS_TO_BASE>;
using Kilograms = Unit<UnitType::MASS, &physics_unit_converions::KILOGRAMS_TO_BASE>;
using Grams = Unit<UnitType::MASS, &physics_unit_converions::GRAMS_TO_BASE>;
using Milligrams = Unit<UnitType::MASS, &physics_unit_converions::MILLIGRAMS_TO_BASE>;
using Micrograms = Unit<UnitType::MASS, &physics_unit_converions::MICROGRAMS_TO_BASE>;
using ImperialTons = Unit<UnitType::MASS, &physics_unit_converions::IMPERIAL_TONS_TO_BASE>;
using Pounds = Unit<UnitType::MASS, &physics_unit_converions::POUNDS_TO_BASE>;
using Ounces = Unit<UnitType::MASS, &physics_unit_converions::OUNCES_TO_BASE>;

// UnitType::CURRENT
using Amps = Unit<UnitType::CURRENT, &physics_unit_converions::AMPS_TO_BASE>;

// UnitType::TEMPERATURE
using Kelvin = Unit<UnitType::TEMPERATURE, &physics_unit_converions::KELVIN_TO_BASE>;

// UnitType::SUBSTANCE_QUANTITY
using Moles = Unit<UnitType::SUBSTANCE_QUANTITY, &physics_unit_converions::MOLES_TO_BASE>;

// UnitType::LUMINOSITY
using Candelas = Unit<UnitType::LUMINOSITY, &physics_unit_converions::CANDELAS_TO_BASE>;

// UnitType::ANGLE
//using Radians = Unit<UnitType::ANGLE, &physics_unit_converions::RADIANS_TO_BASE>;
//using Degrees = Unit<UnitType::ANGLE, &physics_unit_converions::DEGREES_TO_BASE>;

PHYSICS_NAMESPACE_END


#endif