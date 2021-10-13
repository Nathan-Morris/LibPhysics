#include "Angles.h"

PHYSICS_NAMESPACE_BEGIN(units)

Angle::Angle(FloatType thetaIn) : theta(thetaIn) {

}

//
//
//

Degrees::Degrees(FloatType degrees) : Angle(degrees) {

}

FloatType Degrees::radians() const {
	return this->theta * physics_constants::pi / (FloatType)180;
}

FloatType Degrees::degrees() const {
	return this->theta;
}

Degrees& Degrees::operator=(const Angle& aRef) {
	this->theta = aRef.degrees();
	return *this;
}

Degrees& Degrees::operator=(FloatType degrees) {
	this->theta = degrees;
	return *this;
}

//
//
//

Radians::Radians(FloatType radians) : Angle(radians) {

}

FloatType Radians::radians() const {
	return this->theta;
}

FloatType Radians::degrees() const {
	return this->theta / physics_constants::pi * 180;
}

Radians& Radians::operator=(const Angle& aRef) {
	this->theta = aRef.radians();
	return *this;
}

Radians& Radians::operator=(FloatType radians) {
	this->theta = radians;
	return *this;
}

PHYSICS_DEFAULT_NAMESPACE_END