#include "Units.h"


//
//
//

//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	FloatType unitValue
//) { return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() + unitValue); }
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	FloatType unitValue
//) { return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() - unitValue); }
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	FloatType unitValue
//) { return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() / unitValue); }
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio>
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	FloatType unitValue
//) { return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.getValue() * unitValue); }
//
////
////
////
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator+(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
//) {
//	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value += friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
//}
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator-(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
//) {
//	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value -= friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
//}
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator/(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
//) {
//	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value /= friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
//}
//
//template<const UnitType friendUnitType, const FloatType* friendToBaseRatio, const FloatType* friendFromBaseRatio, const UnitType modderUnitType, const FloatType* modderToBaseRatio, const FloatType* modderFromBaseRatio >
//Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio> operator*(
//	const Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>& friendUnit,
//	const Unit<modderUnitType, modderToBaseRatio, modderFromBaseRatio>& modderUnit
//) {
//	return Unit<friendUnitType, friendToBaseRatio, friendFromBaseRatio>(friendUnit.value *= friendUnit.valueFromUnitRatio(modderUnit.getValue(), modderToBaseRatio));
//}
//
//
//
//


const FloatType UnitConversionRatios::MICROSECONDS_TO_BASE = (FloatType)(1.0 / 1e+6);
const FloatType UnitConversionRatios::MILLISECONDS_TO_BASE = (FloatType)(1.0 / 1000);
const FloatType UnitConversionRatios::SECONDS_TO_BASE = (FloatType)1.0;
const FloatType UnitConversionRatios::MINUTES_TO_BASE = (FloatType)60.0;
const FloatType UnitConversionRatios::HOURS_TO_BASE = (FloatType)3600.0;
const FloatType UnitConversionRatios::DAYS_TO_BASE = (FloatType)86400.0;
const FloatType UnitConversionRatios::WEEKS_TO_BASE = (FloatType)604800.0;
const FloatType UnitConversionRatios::YEARS_TO_BASE = (FloatType)3.154e+7;


const FloatType NANOMETERS_TO_BASE = (FloatType)(1.0 / 1.0e+9);
const FloatType MICROMETERS_TO_BASE = (FloatType)(1.0 / 1.0e+6);
const FloatType MILLIMETERS_TO_BASE = (FloatType)(1.0 / 1000.0);
const FloatType CENTIMETERS_TO_BASE = (FloatType)(1.0 / 100.0);
const FloatType DECIMETERS_TO_BASE = (FloatType)(1.0 / 10.0);
const FloatType METERS_TO_BASE = (FloatType)1.0;
const FloatType HECTOMETERS_TO_BASE = (FloatType)100.0;
const FloatType KILOMETERS_TO_BASE = (FloatType)1000.0;
const FloatType NAUTICAL_MILES_TO_BASE = (FloatType)1852.0;
const FloatType MILES_TO_BASE = (FloatType)1609.344;
const FloatType YARDS_TO_BASE = (FloatType)(1.0 / 1094);
const FloatType FEET_TO_BASE = (FloatType)(1.0 / 3.281);
const FloatType INCHES_TO_BASE = (FloatType)(1.0 / 39.37);