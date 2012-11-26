#ifndef _Vector_h
#define _Vector_h

#include <iostream>
#include <cmath>

namespace cm_sim
{

	class Vector {
    public:
        long double x, y;

        Vector(long double a, long double b);
        Vector();

        Vector operator+(Vector v);
        Vector operator-(Vector v);
        Vector operator-();
        Vector operator*(long double s);
        Vector operator/(long double s);

		Vector& operator+=(const Vector &v2);

        double dot(Vector &v2);

        double mag();
        double angle();

        Vector normalize();

        double scalarCross(Vector v2);

        Vector clockwiseOrthagonalVector();
        Vector counterClockwiseOrthagonalVector();
        Vector rotate(double angle);

        Vector projectionOn(Vector &v2);
	};

}

cm_sim::Vector operator*(long double, cm_sim::Vector);
std::ostream& operator<<(std::ostream& o, cm_sim::Vector v);


#endif /*_Vector_h*/
