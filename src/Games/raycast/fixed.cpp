#include <cassert>

#include "fixed.h"

Fixed::Fixed(void) {
}

Fixed::Fixed(float value) {
	set(value);
}

float Fixed::min(void) const {
	return this->rawToFloat(INT16_MIN);
}

float Fixed::max(void) const {
	return this->rawToFloat(INT16_MAX);
}

int Fixed::getInt(void) const {
	return this->rawToInt(rawValue);
}

float Fixed::getFloat(void) const {
	return this->rawToFloat(rawValue);
}

void Fixed::set(float value) {
	// Restrict to valid range.
	value=clip(value, this->min(), this->max());

	// Set rawValue.
	this->rawValue=this->floatToRaw(value);
}

bool Fixed::operator==(const Fixed &rhs) const {
	return (this->rawValue==rhs.rawValue);
}

bool Fixed::operator!=(const Fixed &rhs) const {
	return !this->operator==(rhs);
}

bool Fixed::operator<(const Fixed &rhs) const {
	return (this->rawValue<rhs.rawValue);
}

bool Fixed::operator>(const Fixed &rhs) const {
	return (this->rawValue>rhs.rawValue);
}

bool Fixed::operator<=(const Fixed &rhs) const {
	return !this->operator>(rhs);
}

bool Fixed::operator>=(const Fixed &rhs) const {
	return !this->operator<(rhs);
}

Fixed &Fixed::operator+=(const Fixed &rhs) {
	this->rawValue+=rhs.rawValue;
	return *this;
}

Fixed &Fixed::operator-=(const Fixed &rhs) {
	this->rawValue-=rhs.rawValue;
	return *this;
}

Fixed &Fixed::operator*=(const Fixed &rhs) {
	this->rawValue=(this->rawValue*rhs.rawValue)/powf(2.0, (float)BitsFrac);
	return *this;
}

Fixed &Fixed::operator/=(const Fixed &rhs) {
	this->rawValue=(this->rawValue*powf(2.0, (float)BitsFrac))/rhs.rawValue;
	return *this;
}

Fixed Fixed::sin(const Fixed &x) {
	return Fixed(sinf(x.getFloat()));
}

Fixed Fixed::cos(const Fixed &x) {
	return Fixed(cosf(x.getFloat()));
}

Fixed Fixed::tan(const Fixed &x) {
	return Fixed(tanf(x.getFloat()));
}

Fixed Fixed::cosec(const Fixed &x) {
	return Fixed(1)/Fixed::sin(x);
}

Fixed Fixed::sec(const Fixed &x) {
	return Fixed(1)/Fixed::cos(x);
}

Fixed Fixed::cot(const Fixed &x) {
	return Fixed::cos(x)/Fixed::sin(x);
}

int16_t Fixed::intToRaw(int i) const {
	return (i<<BitsFrac);
}

int Fixed::rawToInt(int16_t r) const {
	return (r>>BitsFrac);
}

int16_t Fixed::floatToRaw(float f) const {
	assert(f>=this->min() && f<=this->max());
	return floorf(f*powf(2.0, (float)this->BitsFrac));
}

float Fixed::rawToFloat(int16_t r) const {
	return r/powf(2.0, (float)this->BitsFrac);
}

Fixed operator+(Fixed lhs, const Fixed &rhs) {
  lhs+=rhs;
  return lhs;
}

Fixed operator-(Fixed lhs, const Fixed &rhs) {
  lhs-=rhs;
  return lhs;
}

Fixed operator*(Fixed lhs, const Fixed &rhs) {
  lhs*=rhs;
  return lhs;
}

Fixed operator/(Fixed lhs, const Fixed &rhs) {
  lhs/=rhs;
  return lhs;
}