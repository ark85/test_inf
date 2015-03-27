#pragma once
#include "edge.h"
#include "poin.h"
#include <list>
typedef class triangle
{
	point_t p;
	point_t q;
	point_t r;
	edge_t side_a; // pq
	edge_t side_b; // qr
	edge_t side_c; // rp

public:

	triangle(void);
	~triangle(void);
	void set_side_a(edge_t);
	void set_side_b(edge_t);
	void set_side_c(edge_t);
	edge_t get_side_a();
	edge_t get_side_b();
	edge_t get_side_c();
	point_t get_p();
	point_t get_q();
	point_t get_r();
	void set_p(point_t);
	void set_q(point_t);
	void set_r(point_t);
	void set_pqr(point_t, point_t, point_t);
	int is_tringle_exist();

	triangle& operator=(triangle &p_1)
	{
		p = p_1.get_p();
		q = p_1.get_q();
		r = p_1.get_r();
		side_a = p_1.get_side_a();
		side_b = p_1.get_side_b();
		side_c = p_1.get_side_c();
		return *this;
	}

}triangle_t;




