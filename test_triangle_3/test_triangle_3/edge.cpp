#include "edge.h"
#include "poin.h"
#include <cmath>
#include <iostream>
using namespace std;


edge::edge(void)
{
	point_t p(0,0,0);
	a = p;
	b = p;
	ab = p;
}


edge::~edge(void)
{
	//std::cout << "Destr_edge" << std::endl; //
}

point_t edge::get_ab ()
{
	return ab;
}
void edge::set_ab(point_t a1, point_t b1)
{
	a = a1;
	b = b1;
	ab = b1 - a1;
}
point_t edge::get_a ()
{
	return a;
}
point_t edge::get_b ()
{
	return b;
}

double edge::get_len()
{
	double x1 = ab.get_x();
	double y1 = ab.get_y();
	return sqrt(x1 * x1 + y1 * y1);
}

void edge::set_a(point_t a1)
{
	a = a1;
}
void edge::set_b(point_t b1)
{
	b = b1;
}