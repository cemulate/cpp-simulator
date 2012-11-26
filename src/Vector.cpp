#include "Vector.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cm_sim;

Vector::Vector(long double a, long double b) {
    x = a;
    y = b;
}

Vector::Vector() {
    x = 0;
    y = 0;
}

Vector Vector::operator+(Vector v) {
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(Vector v) {
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator-() {
    return Vector(-x, -y);
}

Vector Vector::operator*(long double s) {
    return Vector(x*s, y*s);
}

Vector Vector::operator/(long double s) {
    return Vector(x/s, y/s);
}

Vector& Vector::operator+=(const Vector &v2)
{
	this->x += v2.x;
	this->y += v2.y;

	return *this;
}

double Vector::dot(Vector &v2)
{
	return (x * v2.x) + (y * v2.y);
}

double Vector::mag() {
    return sqrt(x*x+y*y);
}

double Vector::angle()
{
	return atan2(y, x);
}

Vector Vector::normalize()
{
	double m = this->mag();
	return Vector(x/m, y/m);
}

double Vector::scalarCross(Vector v2)
{
	return (x*v2.y) - (v2.x * y);
}

Vector Vector::clockwiseOrthagonalVector()
{
	return Vector(-y, x);
}

Vector Vector::rotate(double angle)
{
	double xt = (x * cosf(angle)) - (y * sinf(angle));
	double yt = (y * cosf(angle)) + (x * sinf(angle));
	return Vector(xt, yt);
}

Vector Vector::counterClockwiseOrthagonalVector()
{
	return Vector(y, -x);
}

Vector Vector::projectionOn(Vector &v2)
{
	return ((this->dot(v2)) / (v2.dot(v2))) * v2;
}



Vector operator*(long double s, Vector v) {
    return Vector(v.x*s, v.y*s);
}

ostream& operator<<(ostream& o, Vector v) {
    //o << "<" << v.x << ", " << v.y << ">";
	o << v.x << "," << v.y;
    return o;
}
