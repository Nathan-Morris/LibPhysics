#ifndef _PHYSICS_VECTOR_
#define _PHYSICS_VECTOR_

#include "PhysicsGlobalInclude.h"


PHYSICS_NAMESPACE_BEGIN(collections)

template<const unsigned int length>
class Vector {
private:
	FloatType vect[length] = { (FloatType)0 };

public:
	Vector() { }

	Vector(FloatType fill) {
		for (size_t i = 0; i != length; i++) {
			this->vect[i] = fill;
		}
	}

	Vector(const std::initializer_list<FloatType>& initList) {
		std::initializer_list<FloatType>::const_iterator iter = initList.begin();
		for (size_t i = 0; i != length && iter != initList.end(); i++, iter++) {
			this->vect[i] = *iter;
		}
	}

	Vector<length>& add(const Vector<length>& modder) {
		for (unsigned int i = 0; i != length; i++) {
			this->vect[i] += modder.vect[i];
		}
		return *this;
	}

	Vector<length>& sub(const Vector<length>& modder) {
		for (unsigned int i = 0; i != length; i++) {
			this->vect[i] -= modder.vect[i];
		}
		return *this;
	}

	Vector<length>& mult(const FloatType modder) {
		for (unsigned int i = 0; i != length; i++) {
			this->vect[i] *= modder;
		}
		return *this;
	}

	Vector<length>& div(const FloatType modder) {
		for (unsigned int i = 0; i != length; i++) {
			this->vect[i] /= modder;
		}
		return *this;
	}

	FloatType& at(unsigned int offset) {
		if (offset >= length) {
			offset = length - 1;
		}
		return this->vect[offset];
	}

	const FloatType& at(unsigned int offset) const {
		if (offset >= length) {
			offset = length - 1;
		}
		return this->vect[offset];
	}

	FloatType magnitude() const {
		FloatType sqSum = (FloatType)0;
		for (unsigned int i = 0; i != length; i++) {
			sqSum += (this->vect[i] * this->vect[i]);
		}
		return sqrt(sqSum);
	}

	FloatType dotProduct(const Vector<length>& modder) const {
		FloatType dotSum = (FloatType)0;
		for (unsigned int i = 0; i != length; i++) {
			dotSum += (this->at(i) * modder.at(i));
		}
		return dotSum;
	}

	Vector<length>& normalize() {
		FloatType mag = this->magnitude();
		for (unsigned int i = 0; i != length; i++) {
			this->at(i) /= mag;
		}
		return *this;
	}

public:
	Vector<length>& operator+=(const Vector<length>& modder) { return this->add(modder); }
	Vector<length>& operator-=(const Vector<length>& modder) { return this->sub(modder); }
	Vector<length>& operator*=(const Vector<length>& modder) { return this->dotProduct(modder); }
	Vector<length>& operator*=(FloatType modder) { return this->mult(modder); }
	Vector<length>& operator/=(FloatType modder) { return this->div(modder); }
};

template<const unsigned int vectorLength>
Vector<vectorLength> operator+(const Vector<vectorLength>& lVect, const Vector<vectorLength>& rVect) {
	return Vector<vectorLength>(lVect).add(rVect);
}

template<const unsigned int vectorLength>
Vector<vectorLength> operator-(const Vector<vectorLength>& lVect, const Vector<vectorLength>& rVect) {
	return Vector<vectorLength>(lVect).sub(rVect);
}

template<const unsigned int vectorLength>
FloatType operator*(const Vector<vectorLength>& lVect, const Vector<vectorLength>& rVect) {
	return lVect.dotProduct(rVect);
}

template<const unsigned int vectorLength>
Vector<vectorLength> operator*(const Vector<vectorLength>& lVect, FloatType modder) {
	return Vector<vectorLength>(lVect).mult(modder);
}

template<const unsigned int vectorLength>
Vector<vectorLength> operator/(const Vector<vectorLength>& lVect, FloatType modder) {
	return Vector<vectorLength>(lVect).div(modder);
}


template<const unsigned int vectorLength>
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& outStream, const Vector<vectorLength>& vect) {
	outStream.put('<');
	for (size_t i = 0; i != vectorLength; i++) {
		if (i) {
			outStream.put(',');
			outStream.put(' ');
		}
		outStream << vect.at(i);
	}
	outStream.put('>');
	return outStream;
}

PHYSICS_NAMESPACE_END


#endif