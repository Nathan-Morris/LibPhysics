#include "Angles.h"

PHYSICS_NAMESPACE_BEGIN(units)

Degrees::Degrees() { }

Degrees::Degrees(const Radians& radianRef) {
	this->value* physics_constants::pi / 180.0;
}

Degrees::Degrees(const Degrees& degreeRef) {
	this->value = degreeRef.value;
}

FloatType Degrees::getValue() const {
	return this->value;
}

Radians Degrees::asRadians() const {
	return ;
}

void Degrees::operator +=(FloatType value) { this->value += value; }
void Degrees::operator +=(const Radians& radians) { this->value += radians.asDegrees().getValue(); }

void Degrees::operator -=(FloatType value) { this->value -= value; }
void Degrees::operator -=(const Radians& radians) { this->value -= radians.asDegrees().getValue();}
 
void Degrees::operator *=(FloatType value) { this->value *= value;  }
void Degrees::operator *=(const Radians& radians) { this->value *= radians.asDegrees().getValue(); }

void Degrees::operator /=(FloatType value) { this->value /= value; }
void Degrees::operator /=(const Radians& radians) { this->value /= radians.asDegrees().getValue(); }


Degrees& operator+(Degrees& degreesRef, FloatType value);
Degrees& operator+(Degrees& degreesRef, const Radians& radians);


Degrees& operator-(Degrees& degreesRef, FloatType value);
Degrees& operator-(Degrees& degreesRef, const Radians& radians);


Degrees& operator*(Degrees& degreesRef, FloatType value);
Degrees& operator*(Degrees& degreesRef, const Radians& radians);


Degrees& operator/(Degrees& degreesRef, FloatType value);
Degrees& operator/(Degrees& degreesRef, const Radians& radians);

PHYSICS_DEFAULT_NAMESPACE_END