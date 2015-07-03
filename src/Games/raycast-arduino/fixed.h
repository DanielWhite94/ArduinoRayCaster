#ifndef FIXED_H
#define FIXED_H

#include "inc.h"

#include <stdint.h>
#include <stdlib.h>

namespace RayCast {

	// Helper functions
	template<typename T>
	T max(T a, T b) {
		return a > b ? a : b;
	}

	template<typename T>
	T min(T a, T b) {
		return a < b ? a : b;
	}

	template <typename T> 
	T clip(const T& n, const T& lower, const T& upper) {
  		return max(lower, min(n, upper));
  	}

	class Fixed {
	public:
		const static unsigned int BitsTotal=16;
		const static unsigned int BitsFrac=7;

		Fixed(void);
		Fixed(float value);

		static float min(void);
		static float max(void);

		int getInt(void) const ;
		float getFloat(void) const ;

		void set(float value);

		int16_t getRawValue(void) const;
		void setRawValue(int16_t value);

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

		Fixed operator-() const ;

		int floor(void) const ; // TODO: Should probably overload std::floor instead (similarly for ceil).
		int ceil(void) const ;

		static Fixed abs(const Fixed &x);

		static Fixed sqrt(const Fixed &x);

		static Fixed sin(const Fixed &x);
		static Fixed cos(const Fixed &x);
		static Fixed tan(const Fixed &x);
		static Fixed cosec(const Fixed &x);
		static Fixed sec(const Fixed &x);
		static Fixed cot(const Fixed &x);
		static Fixed asin(const Fixed &x);
		static Fixed acos(const Fixed &x);
		static Fixed atan(const Fixed &x);

		friend void swap(Fixed &first, Fixed &second) {
			int16_t temp;
			temp = first.rawValue;
			second.rawValue = first.rawValue;
			first.rawValue = temp;
		}

		Fixed &operator=(Fixed other) {
			swap(*this, other);
			return *this;
		}

	private:
		int16_t rawValue;

		static int16_t intToRaw(int i);
		static int rawToInt(int16_t r);
		static int16_t floatToRaw(float f);
		static float rawToFloat(int16_t r);
	};

	Fixed operator+(Fixed lhs, const Fixed &rhs);
	Fixed operator-(Fixed lhs, const Fixed &rhs);
	Fixed operator*(Fixed lhs, const Fixed &rhs);
	Fixed operator/(Fixed lhs, const Fixed &rhs);
}


#endif