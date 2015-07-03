#include "colour.h"

void Colour::mul(Fixed factor) {
	r=(r*factor).getInt();
	g=(g*factor).getInt();
	b=(b*factor).getInt();
}