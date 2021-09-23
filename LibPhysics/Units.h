#ifndef _PHYSICS_UNITS_
#define _PHYSICS_UNITS_


#pragma once

#include <stdexcept>

#include "Formatter.h"
#include "PhysicsConstants.h"
#include "PhysicsGlobalInclude.h"


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
	LUMINOSITY = 0x6
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

	//


	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator+(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator-(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator/(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator*(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<friendUnitType, modderToBaseRatio>& modderUnit);

	//

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator+(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<modderUnitType, modderToBaseRatio>& modderUnit) = delete;

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator-(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<modderUnitType, modderToBaseRatio>& modderUnit) = delete;

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator/(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<modderUnitType, modderToBaseRatio>& modderUnit) = delete;

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio> operator*(const Unit<friendUnitType, friendToBaseRatio>& friendUnit, const Unit<modderUnitType, modderToBaseRatio>& modderUnit) = delete;
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
//
//


//
// Common Unit Type Conversion Declarations
//

class UnitConversionRatios {
public:
	static const FloatType MICROSECONDS_TO_BASE;
	static const FloatType MILLISECONDS_TO_BASE;
	static const FloatType SECONDS_TO_BASE; // base
	static const FloatType MINUTES_TO_BASE;
	static const FloatType HOURS_TO_BASE;
	static const FloatType DAYS_TO_BASE;
	static const FloatType WEEKS_TO_BASE;
	static const FloatType YEARS_TO_BASE;

	static const FloatType NANOMETERS_TO_BASE;
	static const FloatType MICROMETERS_TO_BASE;
	static const FloatType MILLIMETERS_TO_BASE;
	static const FloatType CENTIMETERS_TO_BASE;
	static const FloatType DECIMETERS_TO_BASE;
	static const FloatType METERS_TO_BASE;	// base
	static const FloatType HECTOMETERS_TO_BASE;
	static const FloatType KILOMETERS_TO_BASE;
	static const FloatType NAUTICAL_MILES_TO_BASE;
	static const FloatType MILES_TO_BASE;
	static const FloatType YARDS_TO_BASE;
	static const FloatType FEET_TO_BASE;
	static const FloatType INCHES_TO_BASE;

	static const FloatType METRIC_TONS_TO_BASE;
	static const FloatType KILOGRAMS_TO_BASE;	// base
	static const FloatType GRAMS_TO_BASE;
	static const FloatType MILLIGRAMS_TO_BASE;
	static const FloatType MICROGRAMS_TO_BASE;
	static const FloatType IMPERIAL_TONS_TO_BASE;
	static const FloatType POUNDS_TO_BASE;
	static const FloatType OUNCES_TO_BASE;
	
	static const FloatType AMPS_TO_BASE;	// base

	static const FloatType KELVIN_TO_BASE;	// base

	static const FloatType MOLES_TO_BASE;	// base

	static const FloatType CANDELAS_TO_BASE;	// base
};

//
// Common Unit Definitions
//

// UnitType::TIME
using Seconds = Unit<UnitType::TIME, &UnitConversionRatios::SECONDS_TO_BASE>;
using Minutes = Unit<UnitType::TIME, &UnitConversionRatios::MINUTES_TO_BASE>;
using Hours = Unit<UnitType::TIME, &UnitConversionRatios::HOURS_TO_BASE>;
using Days = Unit<UnitType::TIME, &UnitConversionRatios::DAYS_TO_BASE>;
using Weeks = Unit<UnitType::TIME, &UnitConversionRatios::WEEKS_TO_BASE>;
using Years = Unit<UnitType::TIME, &UnitConversionRatios::YEARS_TO_BASE>;

// UnitType::LENGTH
using Micrometers = Unit<UnitType::LENGTH, &UnitConversionRatios::MICROMETERS_TO_BASE>;
using Nanometers = Unit<UnitType::LENGTH, &UnitConversionRatios::NANOMETERS_TO_BASE>;
using Millimeters = Unit<UnitType::LENGTH, &UnitConversionRatios::MILLIMETERS_TO_BASE>;
using Centimeters = Unit<UnitType::LENGTH, &UnitConversionRatios::CENTIMETERS_TO_BASE>;
using Decimeters = Unit<UnitType::LENGTH, &UnitConversionRatios::DECIMETERS_TO_BASE>;
using Meters = Unit<UnitType::LENGTH, &UnitConversionRatios::METERS_TO_BASE>;
using Hectometers = Unit<UnitType::LENGTH, &UnitConversionRatios::HECTOMETERS_TO_BASE>;
using Kilometers = Unit<UnitType::LENGTH, &UnitConversionRatios::KILOMETERS_TO_BASE>;
using NauticalMiles = Unit<UnitType::LENGTH, &UnitConversionRatios::NAUTICAL_MILES_TO_BASE>;
using Miles = Unit<UnitType::LENGTH, &UnitConversionRatios::MILES_TO_BASE>;
using Yards = Unit<UnitType::LENGTH, &UnitConversionRatios::YARDS_TO_BASE>;
using Feet = Unit<UnitType::LENGTH, &UnitConversionRatios::FEET_TO_BASE>;
using Inches = Unit<UnitType::LENGTH, &UnitConversionRatios::INCHES_TO_BASE>;

// UnitType::MASS
using MetricTons = Unit<UnitType::MASS, &UnitConversionRatios::METRIC_TONS_TO_BASE>;
using Kilograms = Unit<UnitType::MASS, &UnitConversionRatios::KILOGRAMS_TO_BASE>;
using Grams = Unit<UnitType::MASS, &UnitConversionRatios::GRAMS_TO_BASE>;
using Milligrams = Unit<UnitType::MASS, &UnitConversionRatios::MILLIGRAMS_TO_BASE>;
using Micrograms = Unit<UnitType::MASS, &UnitConversionRatios::MICROGRAMS_TO_BASE>;
using ImperialTons = Unit<UnitType::MASS, &UnitConversionRatios::IMPERIAL_TONS_TO_BASE>;
using Pounds = Unit<UnitType::MASS, &UnitConversionRatios::POUNDS_TO_BASE>;
using Ounces = Unit<UnitType::MASS, &UnitConversionRatios::OUNCES_TO_BASE>;

// UnitType::CURRENT
using Amps = Unit<UnitType::CURRENT, &UnitConversionRatios::AMPS_TO_BASE>;

// UnitType::TEMPERATURE
using Kelvin = Unit<UnitType::TEMPERATURE, &UnitConversionRatios::KELVIN_TO_BASE>;

// UnitType::SUBSTANCE_QUANTITY
using Moles = Unit<UnitType::SUBSTANCE_QUANTITY, &UnitConversionRatios::MOLES_TO_BASE>;

// UnitType::LUMINOSITY
using Candelas = Unit<UnitType::LUMINOSITY, &UnitConversionRatios::CANDELAS_TO_BASE>;


PHYSICS_NAMESPACE_END


#endif