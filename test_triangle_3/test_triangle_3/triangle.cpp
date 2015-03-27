#include "triangle.h"
#include "edge.h"
#include "poin.h"
#include <iostream>


triangle::triangle(void)
{
	point_t p(0,0,0);
	side_a.set_ab(p, p);
	side_b.set_ab(p, p);
	side_c.set_ab(p, p);
}


triangle::~triangle(void)
{
	//std::cout << "Destr_triangle" << std::endl; //
}

void triangle::set_side_a(edge_t side)
{
	point_t s1 = side.get_a();
	point_t s2 = side.get_b();
	side_a.set_ab(s1, s2);
}
void triangle::set_side_b(edge_t side)
{
	point_t s1 = side.get_a();
	point_t s2 = side.get_b();
	side_b.set_ab(s1, s2);
}
void triangle::set_side_c(edge_t side)
{
	point_t s1 = side.get_a();
	point_t s2 = side.get_b();
	side_c.set_ab(s1, s2);
}
	edge_t triangle::get_side_a ()
{
	return side_a;
}
edge_t triangle::get_side_b ()
{
	return side_b;
}
edge_t triangle::get_side_c ()
{
	return side_c;
}
int triangle::is_tringle_exist()
{
	double la = side_a.get_len();
	double lb = side_b.get_len();
	double lc = side_c.get_len();
	if (la < lb + lc && lb < la + lc && lc < la + lb)
		return 1;
	else return 0;
}

point_t triangle::get_p()
{
	return p;
}
	
point_t triangle::get_q()
{
	return q;
}
point_t triangle::get_r()
{
	return r;
}

void triangle::set_p(point_t p1)
{
	p = p1;
}
void triangle::set_q(point_t p1)
{
	q = p1;
}
void triangle::set_r(point_t p1)
{
	r = p1;
}

void triangle::set_pqr(point_t p1, point_t q1, point_t r1)
{
	p = p1;
	q = q1;
	r = r1;
	side_a.set_ab(p, q);
	side_b.set_ab(q, r);
	side_c.set_ab(r, p);
}