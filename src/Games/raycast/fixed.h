#ifndef FIXED_H
#define FIXED_H

#include <algorithm>
#include <cstdint>

template <typename T> T clip(const T& n, const T& lower, const T& upper) {
  return std::max(lower, std::min(n, upper));
}

class Fixed {
public:
	const unsigned int BitsTotal=16;
	const unsigned int BitsFrac=8;

	Fixed(void);
	Fixed(float value);

	float min(void) const ;
	float max(void) const ;

	int getInt(void);
	float getFloat(void);

	void set(float value);

	bool operator==(const Fixed &rhs) const ;
	bool operator!=(const Fixed &rhs) const ;
	bool operator<(const Fixed &rhs) const ;
	bool operator>(const Fixed &rhs) const ;
	bool operator<=(const Fixed &rhs) const ;
	bool operator>=(const Fixed &rhs) const ;

	Fixed &operator+=(const Fixed &rhs);
	Fixed &operator-=(const Fixed &rhs);
	Fixed &operator*=(const Fixed &rhs);
	Fixed &operator/=(const Fixed &rhs);

private:
	int16_t rawValue;

	int16_t intToRaw(int i) const ;
	int rawToInt(int16_t r) const ;
	int16_t floatToRaw(float f) const ;
	float rawToFloat(int16_t r) const ;
};

Fixed operator+(Fixed lhs, const Fixed &rhs);
Fixed operator-(Fixed lhs, const Fixed &rhs);
Fixed operator*(Fixed lhs, const Fixed &rhs);
Fixed operator/(Fixed lhs, const Fixed &rhs);

#endif