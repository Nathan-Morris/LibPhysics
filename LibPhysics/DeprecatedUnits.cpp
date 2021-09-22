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


//const FloatType MICROSECONDS_TO_BASE = (FloatType)0;
//const FloatType MICROSECONDS_FROM_BASE = (FloatType)0;
//
//const FloatType MILLISECONDS_TO_BASE = (FloatType)0;
//const FloatType MILLISECONDS_FROM_BASE = (FloatType)0;
//
//const FloatType UnitConversionRatios::SECONDS_TO_BASE = (FloatType)1.0;
//const FloatType UnitConversionRatios::SECONDS_FROM_BASE = (FloatType)1.0;
//const FloatType UnitConversionRatios::MINUTES_TO_BASE = (FloatType)60.0;
//const FloatType UnitConversionRatios::MINUTES_FROM_BASE = (FloatType)(1.0 / 60.0);
//const FloatType UnitConversionRatios::HOURS_TO_BASE = (FloatType)3600.0;
//const FloatType UnitConversionRatios::HOURS_FROM_BASE = (FloatType)(1.0 / 3600.0);
//const FloatType UnitConversionRatios::DAYS_TO_BASE = (FloatType)86400.0;
//const FloatType UnitConversionRatios::DAYS_FROM_BASE = (FloatType)(1.0 / 86400.0);
//const FloatType UnitConversionRatios::WEEKS_TO_BASE = (FloatType)604800.0;
//const FloatType UnitConversionRatios::WEEKS_FROM_BASE = (FloatType)(1.0 / 604800.0);
//const FloatType UnitConversionRatios::YEARS_TO_BASE = (FloatType)3.154e+7;
//const FloatType UnitConversionRatios::YEARS_FROM_BASE = (FloatType)(1.0 / 3.154e+7);