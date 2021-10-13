#ifndef _PHYSICS_ANGLES_
#define _PHYSICS_ANGLES_

#pragma once

#include "PhysicsGlobalInclude.h"
#include "PhysicsConstants.h"

PHYSICS_NAMESPACE_BEGIN(units)

class Angle {
protected:
	FloatType theta;

protected:
	Angle(FloatType theta);

public:
	virtual FloatType radians() const = 0;
	virtual FloatType degrees() const = 0;

};

class Degrees : public Angle {
public:
	Degrees(FloatType degrees);
	
	operator FloatType() const {
		return this->theta;
	}

	FloatType radians() const;
	FloatType degrees() const;

	Degrees& operator=(const Angle& aRef);
	Degrees& operator=(FloatType degrees);

public:

};

class Radians : public Angle {
public:
	Radians(FloatType radians);

	operator FloatType() const {
		return this->theta;
	}

	FloatType radians() const;
	FloatType degrees() const;

	Radians& operator=(const Angle& aRef);
	Radians& operator=(FloatType radians);
};

PHYSICS_NAMESPACE_END

#endif