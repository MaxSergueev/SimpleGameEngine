#include "Vector2.h"

const Vector2 Vector2::Zero(0,0);
const Vector2 Vector2::One(1,1);

float Vector2::GetSqrLength() {
	return x*x + y*y;
};