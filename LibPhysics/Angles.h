#ifndef _PHYSICS_ANGLES_
#define _PHYSICS_ANGLES_

#pragma once

#include "PhysicsConstants.h"

PHYSICS_NAMESPACE_BEGIN(units)

class Degrees {
private:
	FloatType value = 0.0;
public:
	Degrees();
	Degrees(const Radians& radianRef);
	Degrees(const Degrees& degreeRef);

	FloatType getValue() const;

	operator FloatType() {
		return this->value;
	}

	FloatType asRadians() const;

public:
	void operator +=(FloatType value);
	void operator +=(const Radians& radians);

	void operator -=(FloatType value);
	void operator -=(const Radians& radians);

	void operator *=(FloatType value);
	void operator *=(const Radians& radians);

	void operator /=(FloatType value);
	void operator /=(const Radians& radians);

public:
	friend Degrees& operator+(Degrees& degreesRef, FloatType value);
	friend Degrees& operator+(Degrees& degreesRef, const Radians& radians);
	
	friend Degrees& operator-(Degrees& degreesRef, FloatType value);
	friend Degrees& operator-(Degrees& degreesRef, const Radians& radians);
	
	friend Degrees& operator*(Degrees& degreesRef, FloatType value);
	friend Degrees& operator*(Degrees& degreesRef, const Radians& radians);
	
	friend Degrees& operator/(Degrees& degreesRef, FloatType value);
	friend Degrees& operator/(Degrees& degreesRef, const Radians& radians);
};

class Radians {
private:
	FloatType value;

public:
	Radians(const Degrees& degreeRef);

	FloatType getValue() const;

	operator FloatType() {
		return this->value;
	}

	FloatType asDegrees() const;

};

class Angle {
private:
	FloatType value;

public:
	Angle() {}
};

PHYSICS_NAMESPACE_END

#endif