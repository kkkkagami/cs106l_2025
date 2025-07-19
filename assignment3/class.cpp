#include"class.h"
#include<cmath>
double Point::get_x() const { return x; }

double Point::get_y() const { return y; }

void Point::write_x(double _x) { x=_x; }

void Point::write_y(double _y) { y=_y; }

bool Triangle::is_valid_shape() const{
    return p1.get_x()==p2.get_x() && p1.get_y()==p2.get_y() ||
            p3.get_x()==p2.get_x() && p3.get_y()==p2.get_y() ||
            p1.get_x()==p3.get_x() && p1.get_y()==p3.get_y();
}

double Triangle::get_area() const{
    if(!is_valid_shape()) return 0;

    return 0.5 * std::abs(
            p1.get_x() * (p2.get_y() - p3.get_y()) +
            p2.get_x() * (p3.get_y() - p1.get_y()) +
            p3.get_x() * (p1.get_y() - p2.get_y())
        );
}
