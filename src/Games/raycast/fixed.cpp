#include <cassert>

#include "fixed.h"

Fixed::Fixed(void) {
}

Fixed::Fixed(float value) {
	set(value);
}

float Fixed::min(void) {
	return Fixed::rawToFloat(INT16_MIN);
}

float Fixed::max(void) {
	return Fixed::rawToFloat(INT16_MAX);
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

int16_t Fixed::getRawValue(void) const {
	return rawValue;
}

void Fixed::setRawValue(int16_t value) {
	rawValue=value;
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

Fixed Fixed::operator-() const {
	Fixed f;
	f.setRawValue(-this->rawValue);
	return f;
}

int Fixed::floor(void) const {
	// TODO: Can probably do this (and ceil) much faster.
	return floorf(getFloat());
}

int Fixed::ceil(void) const {
	return ceilf(getFloat());
}

Fixed Fixed::abs(const Fixed &x) {
	Fixed y=x;
	y.setRawValue(std::abs(x.getRawValue()));
	return y;
}

Fixed Fixed::sqrt(const Fixed &x) {
	return Fixed(sqrtf(x.getFloat()));
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

Fixed Fixed::asin(const Fixed &x) {
	return Fixed(asinf(x.getFloat()));
}

Fixed Fixed::acos(const Fixed &x) {
	return Fixed(acosf(x.getFloat()));
}

Fixed Fixed::atan(const Fixed &x) {
	return Fixed(atanf(x.getFloat()));
}

int16_t Fixed::intToRaw(int i){
	return (i<<BitsFrac);
}

int Fixed::rawToInt(int16_t r){
	return (r>>BitsFrac);
}

int16_t Fixed::floatToRaw(float f) {
	assert(f>=Fixed::min() && f<=Fixed::max());
	return floorf(f*powf(2.0, (float)BitsFrac));
}

float Fixed::rawToFloat(int16_t r) {
	return r/powf(2.0, (float)BitsFrac);
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