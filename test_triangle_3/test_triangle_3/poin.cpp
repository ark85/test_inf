#include "poin.h"
#include <iostream>

poin::poin(void)
{

	x = 0;
	y = 0;
	f = 0;
}

poin::poin(double x1, double y1, double f1)
{
	x = x1;
	y = y1;
	f = f1;
}

poin::~poin(void)
{
	//std::cout << "Destr_point" << std::endl; //
}
void poin::set_x(double p)
{
	x = p;
}
	
void poin::set_y(double p)
{
	y = p;
}
void poin::set_f(double p)
{
	f = p;
}

double poin::get_x()
{
	return x;
}
double poin::get_y()
{
	return y;
}
double poin::get_f()
{
	return f;
}

