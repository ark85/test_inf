#pragma once
#include "poin.h"
typedef class edge
{
	point_t a;
	point_t b;
	point_t ab;
public:
	
	edge(void);
	~edge(void);
	point_t get_ab ();
	void set_ab(point_t,point_t);
	void set_a(point_t);
	void set_b(point_t);
	point_t get_a ();
	point_t get_b ();
	double get_len();
	
	edge& operator=(edge &p_1)
	{
		a = p_1.get_a();
		b = p_1.get_b();
		ab = p_1.get_ab();
		return *this;
	}
}edge_t;

