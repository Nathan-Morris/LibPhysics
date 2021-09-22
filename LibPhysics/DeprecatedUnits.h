#ifndef _PHYSICS_UNITS_
#define _PHYSICS_UNITS_


#pragma once

#include "PhysicsGlobalInclude.h"

//
// UnitTypes
//

enum class UnitType : unsigned char {
	TIME				= 0x0,
	LENGTH				= 0x1,
	MASS				= 0x2,
	CURRENT				= 0x3,
	TEMPERATURE			= 0x4,
	SUBSTANCE_QUANTITY	= 0x5,
	LUMINOSITY			= 0x6
};
typedef UnitType* pUnitType;

typedef const UnitType cUnitType, *pcUnitType;

static const char* unitTypeName(UnitType unitType) {
	switch (unitType)
	{
	case UnitType::TIME:				return "Time";
	case UnitType::LENGTH:				return "Length";
	case UnitType::MASS:				return "Mass";
	case UnitType::CURRENT:				return "Electric Current";
	case UnitType::TEMPERATURE:			return "Temperature";
	case UnitType::SUBSTANCE_QUANTITY:	return "Substance Quantity";
	case UnitType::LUMINOSITY:			return "Luminosity";
	}
}

//
// Generic Unit Class
//

template<const UnitType unitType, const FloatType* toBaseRatio, const FloatType* fromBaseRatio>
class Unit {
private:
	FloatType value = 0.0;

	FloatType valueFromUnitRatio(FloatType inValue, const FloatType* convertToBaseRatio) const {
		return (inValue * (*convertToBaseRatio)) * (*fromBaseRatio);
	}

public:	// Construction
	Unit(FloatType initialValue) { this->value = initialValue; }
	Unit(const Unit<unitType, toBaseRatio, fromBaseRatio>& copyUnit) : Unit(copyUnit) { }
	Unit() { }

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	Unit(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value = this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

public:	// Value Fetching
	UnitType getUnitType() const { return unitType; }
	FloatType getValue() const { return this->value; }
	operator FloatType() { return this->getValue(); }

public:	// Assignment Operations
	template<const UnitType assignUnitType, const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	Unit<unitType, toBaseRatio, fromBaseRatio>& operator=(const Unit<assignUnitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		if (assignUnitType != unitType) {
			throw std::runtime_error(Formatter(
				"Unable to Assign a Unit of Type %s to a Unit of Type %s", unitTypeName(assignUnitType), unitTypeName(unitType)
			));
		}
		return *this;
	}

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	Unit<unitType, toBaseRatio, fromBaseRatio>& operator=(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value = this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
		return *this;
	}

	Unit<unitType, toBaseRatio, fromBaseRatio>& operator=(FloatType unitValue) {
		this->value = unitValue;
	}

public:	// Arithmetic Member Operations

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	void operator +=(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value += this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	void operator -=(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value -= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	void operator /=(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value /= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	template<const FloatType* assignToBaseRatio, const FloatType* assignFromBaseRatio>
	void operator *=(const Unit<unitType, assignToBaseRatio, assignFromBaseRatio>& assignUnit) {
		this->value *= this->valueFromUnitRatio(assignUnit.getValue(), assignToBaseRatio);
	}

	void operator +=(const FloatType& unitValue) { this->value *= unitValue; }
	void operator -=(const FloatType& unitValue) { this->value -= unitValue; }
	void operator /=(const FloatType& unitValue) { this->value /= unitValue; }
	void operator *=(const FloatType& unitValue) { this->value *= unitValue; }

public: // Arithmetic Friend Operations

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		FloatType unitValue
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		FloatType unitValue
	);
	
	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		FloatType unitValue
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		FloatType unitValue
	);

	//
	//
	//

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	);

	template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
	friend Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
		const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
		const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	);
};

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() + unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() - unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() / unitValue);
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	FloatType unitValue
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() * unitValue);
}

//
//
//

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value + friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value - friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value / friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
	) {
	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value * friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
}

//
//
//


//
// Common Unit Type Conversion Declarations
//

// namespace UnitConversionRatios {
// 	extern const FloatType MICROSECONDS_TO_BASE;
// 	extern const FloatType MICROSECONDS_FROM_BASE;
// 
// 	extern const FloatType MILLISECONDS_TO_BASE;
// 	extern const FloatType MILLISECONDS_FROM_BASE;
// 
// 	extern const FloatType SECONDS_TO_BASE;
// 	extern const FloatType SECONDS_FROM_BASE;
// 	extern const FloatType MINUTES_TO_BASE;
// 	extern const FloatType MINUTES_FROM_BASE;
// 	extern const FloatType HOURS_TO_BASE;
// 	extern const FloatType HOURS_FROM_BASE;
// 	extern const FloatType DAYS_TO_BASE;
// 	extern const FloatType DAYS_FROM_BASE;
// 	extern const FloatType WEEKS_TO_BASE;
// 	extern const FloatType WEEKS_FROM_BASE;
// 	extern const FloatType YEARS_TO_BASE;
// 	extern const FloatType YEARS_FROM_BASE;
// 
// 
// };

//
// Common Unit Definitions
//

//using Seconds	= Unit<UnitType::TIME, &UnitConversionRatios::SECONDS_TO_BASE,	&UnitConversionRatios::SECONDS_FROM_BASE>;
//using Minutes	= Unit<UnitType::TIME, &UnitConversionRatios::MINUTES_TO_BASE,	&UnitConversionRatios::MINUTES_FROM_BASE>;
//using Hours		= Unit<UnitType::TIME, &UnitConversionRatios::HOURS_TO_BASE,	&UnitConversionRatios::HOURS_FROM_BASE>;
//using Days		= Unit<UnitType::TIME, &UnitConversionRatios::DAYS_TO_BASE,		&UnitConversionRatios::DAYS_FROM_BASE>;
//using Weeks		= Unit<UnitType::TIME, &UnitConversionRatios::WEEKS_TO_BASE,	&UnitConversionRatios::WEEKS_FROM_BASE>;
//using Years		= Unit<UnitType::TIME, &UnitConversionRatios::YEARS_TO_BASE,	&UnitConversionRatios::YEARS_FROM_BASE>;

#endif