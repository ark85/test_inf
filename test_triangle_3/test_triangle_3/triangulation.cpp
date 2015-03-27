#include <iostream>
#include "poin.h"
#include "edge.h"
#include <list>
#include "triangle.h"
#include "triangulation.h"
using namespace std;

#define lim1 1000 // граница триангуляции
#define lim2 800

double eps = 0.0000001;
int complete = 0;
double size_x = 0;
double size_y = 0;

int compare_points(const void * x1, const void * y1)   // функция сравнения элементов массива точек
{
	point_t x2 = *(point_t*)x1;
	point_t y2 = *(point_t*)y1;
	if (x2.get_x() < y2.get_x())
	{
		return -1;
	}
	else if (x2.get_x() > y2.get_x())
	{
		return 1;
	}
	else return 0;
}

int compare_edges_up(const void * x1, const void * y1)   // функция сравнения элементов массива отрезков по Х
	// для сортировки по возрастанию Х
{
	edge_t x2 = *(edge_t*)x1;
	edge_t y2 = *(edge_t*)y1;
	point_t x1x = x2.get_b();
	point_t y1x = y2.get_b();
	if (x1x.get_x() < y1x.get_x())
	{
		return -1;
	}
	else if (x1x.get_x() > y1x.get_x())
	{
		return 1;
	}
	else return 0;
}

int compare_edges_down(const void * x1, const void * y1)   // функция сравнения элементов массива отрезков по Х
	// для сортировки по убыванию Х
{
	edge_t x2 = *(edge_t*)x1;
	edge_t y2 = *(edge_t*)y1;
	point_t x1x = x2.get_b();
	point_t y1x = y2.get_b();
	if (x1x.get_x() > y1x.get_x())
	{
		return -1;
	}
	else if (x1x.get_x() < y1x.get_x())
	{
		return 1;
	}
	else return 0;
}

int is_cross(edge_t s_in, edge_t s_out) // пересекаются ли отрезки 
{
	point_t a1, a2, b1, b2;
	//double ta, tb;
	a1 = s_in.get_a();
	a2 = s_in.get_b();
	b1 = s_out.get_a();
	b2 = s_out.get_b(); 
	double ta1=(b2.get_x()-b1.get_x())*(a1.get_y()-b1.get_y())-(b2.get_y()-b1.get_y())*(a1.get_x()-b1.get_x());
	double t=(b2.get_y()-b1.get_y())*(a2.get_x()-a1.get_x())-(b2.get_x()-b1.get_x())*(a2.get_y()-a1.get_y());
	double tb1=(a2.get_x()-a1.get_x())*(a1.get_y()-b1.get_y())-(a2.get_y()-a1.get_y())*(a1.get_x()-b1.get_x());
	if (t == 0) return 0; //отрезки параллельные
	if (t == ta1) return 0; // отрезки совпадают
        if (ta1 / t > 0 && ta1 / t < 1 && tb1 / t > 0 && tb1 / t < 1) return 1; // отрезки пересекаются
	return 0;
}

point_t find_big_y(list<triangle> *tri) //самая высокая точка в данной триангуляции
{
	point_t max(0, -1000, 0);
	list <triangle>::iterator tr_Iter;
	for ( tr_Iter = tri->begin(); tr_Iter != tri->end(); tr_Iter++)
	{
		point_t a1, b1, c1;
		triangle_t t;
		t = *tr_Iter;
		a1 = t.get_p();
		b1 = t.get_q();
		c1 = t.get_r();
		if (a1.get_y() > max.get_y()) max = a1;
		if (b1.get_y() > max.get_y()) max = b1;
		if (c1.get_y() > max.get_y()) max = c1;
	}
	size_y = max.get_y();
	return max;
}

point_t find_low_y(list<triangle> *tri) // самая низкая точка в данной триангуляции
{
	point_t min(0, 1000, 0);
	list <triangle>::iterator tr_Iter;
	for ( tr_Iter = tri->begin(); tr_Iter != tri->end(); tr_Iter++)
	{
		point_t a1, b1, c1;
		triangle_t t;
		t = *tr_Iter;
		a1 = t.get_p();
		b1 = t.get_q();
		c1 = t.get_r();
		if (a1.get_y() < min.get_y()) min = a1;
		if (b1.get_y() < min.get_y()) min = b1;
		if (c1.get_y() < min.get_y()) min = c1;
	}
	return min;
}

point_t find_big_x(list<triangle> *tri) //самая "дальняя" точка в данной триангуляции
{
	point_t max(-1000, 0, 0);
	list <triangle>::iterator tr_Iter;
	for ( tr_Iter = tri->begin(); tr_Iter != tri->end(); tr_Iter++)
	{
		point_t a1, b1, c1;
		triangle_t t;
		t = *tr_Iter;
		a1 = t.get_p();
		b1 = t.get_q();
		c1 = t.get_r();
		if (a1.get_x() > max.get_x()) max = a1;
		if (b1.get_x() > max.get_x()) max = b1;
		if (c1.get_x() > max.get_x()) max = c1;
	}
	size_x = max.get_x();
	return max;
}


int  cmp_point (point_t *p1, point_t *p2)
{
	if (p1->get_f() == p2->get_f())
	{
		if (p1->get_x() == p2->get_x())
		{
			if (p1->get_y() == p2->get_y())
				return 1;
		}
	}
	return 0;
}


int gluing(list<triangle> *tri1, list<triangle> *tri2, list<triangle> *tri_res) // склейка
{

	point_t P0, P1, P2, P3, P4;
	P0 = find_big_y(tri1);
	P1 = find_big_y(tri2);
	P2 = find_low_y(tri1);
	P3 = find_low_y(tri2);
	list<triangle> t_g;
	list<edge> ed_1;
	list<edge> ed_2;
	list <triangle>::iterator tr_Iter;
		for ( tr_Iter = tri1->begin(); tr_Iter != tri1->end(); tr_Iter++)
		{
			triangle_t t;
			t = *tr_Iter;
			ed_1.push_back(t.get_side_a());
			ed_1.push_back(t.get_side_b());
			ed_1.push_back(t.get_side_c());
		}
		for ( tr_Iter = tri2->begin(); tr_Iter != tri2->end(); tr_Iter++)
		{
			triangle_t t;
			t = *tr_Iter;
			ed_2.push_back(t.get_side_a());
			ed_2.push_back(t.get_side_b());
			ed_2.push_back(t.get_side_c());
		}

		edge_t e_10;
		edge_t e_23;
		e_10.set_ab(P0, P1);
		e_23.set_ab(P2, P3);
		// есть ли пересечения, нужно проверить
		int j = 0;
		while (cmp_point(&P0, &P2) == 0 || cmp_point(&P1, &P3) == 0)
		{
			int j1 = 0;
			if (j == 0)
			{
				j1 = 1;
				j = 1;
				if (cmp_point(&P1, &P3) == 0)
				{
					list<edge> E_P1;
					// двигаем P1
					list <edge>::iterator ed_Iter;
					for ( ed_Iter = ed_2.begin(); ed_Iter != ed_2.end(); ed_Iter++)
					{
						edge_t e;
						e = *ed_Iter;
						point_t P_h1, P_h2; // вспомогательные точки
						P_h1 = e.get_a();
						P_h2 = e.get_b();
						if (P1 == P_h1 && P1.get_y() > P_h2.get_y())
							E_P1.push_back(e);
						if (P1 == P_h2 && P1.get_y() > P_h1.get_y())
							E_P1.push_back(e);
					}
						
					int n = E_P1.size();
					if (n == 0) // если "справа" две самые нижние точки совпадают по У
					{
						triangle_t t;
						list <edge>::iterator ed_Iter;
						for ( ed_Iter = ed_2.begin(); ed_Iter != ed_2.end(); ed_Iter++)
						{
							edge_t e;
							e = *ed_Iter;
							point_t P_h1, P_h2; // вспомогательные точки
							P_h1 = e.get_a();
							P_h2 = e.get_b();
							if (P1 == P_h1 && P1.get_y() == P_h2.get_y())
							{
								t.set_pqr(P0, P1, e.get_b());
								P1 = e.get_b();
							}
							if (P1 == P_h2 && P1.get_y() > P_h1.get_y())
							{
								t.set_pqr(P0, P1, e.get_a());
								P1 = e.get_a();
							}
						}
					}
					edge_t *E_P11;
					E_P11 = new edge_t[n];
					int l = 0;
					list <edge>::iterator E_P11_Iter;
					for ( E_P11_Iter = E_P1.begin(); E_P11_Iter != E_P1.end(); E_P11_Iter++)
					{
						E_P11[l] = *E_P11_Iter;
						if (P1 != E_P11[l].get_a())
						{
							point_t m1, m2;
							m1 = E_P11[l].get_a();
							m2 = E_P11[l].get_b();
							E_P11[l].set_a(m2);
							E_P11[l].set_b(m1);
						}
						l++;
					}
					qsort(E_P11, n, sizeof(edge_t), compare_edges_up);
					E_P1.clear();
					for (int l = 0; l < n; l++)
					{
						E_P1.push_back(E_P11[l]);
					}
					for ( E_P11_Iter = E_P1.begin(); E_P11_Iter != E_P1.end(); E_P11_Iter++)
					{
						edge_t e;
						e = *E_P11_Iter;
						triangle_t t;
						t.set_pqr(P0, P1, e.get_b());
						if (t.is_tringle_exist() == 1)
						{
							int k = 0; // кол-во пересечений
							list <edge>::iterator ed_Iter1;
							for ( ed_Iter1 = ed_1.begin(); ed_Iter1 != ed_1.end(); ed_Iter1++)
							{
								edge_t si;
								si = *ed_Iter1;
								if (is_cross(t.get_side_c(), si) == 1)
									k++;
							}
							for ( ed_Iter1 = ed_2.begin(); ed_Iter1 != ed_2.end(); ed_Iter1++)
							{
								edge_t si;
								si = *ed_Iter1;
								if (is_cross(t.get_side_c(), si) == 1)
									k++;
							}
							if (k == 0)
							{
								t_g.push_back(t);
								//P4 = P1;
								P1 = t.get_r();
								j = 1;
								j1 = 1;
								break;
							}
						}
					}
				}
			}
			if (j == 1 && j1 == 0)
			{
				if (cmp_point(&P0, &P2) == 0)
					{
					list<edge> E_P1;
					// двигаем P0
					list <edge>::iterator ed_Iter;
					for ( ed_Iter = ed_1.begin(); ed_Iter != ed_1.end(); ed_Iter++)
					{
						edge_t e;
						e = *ed_Iter;
						point_t P_h1, P_h2; // вспомогательные точки
						P_h1 = e.get_a();
						P_h2 = e.get_b();
						if (P0 == P_h1 && P0.get_y() > P_h2.get_y())
							E_P1.push_back(e);
						if (P0 == P_h2 && P0.get_y() > P_h1.get_y())
							E_P1.push_back(e);
					}
					int n = E_P1.size();
					if (n == 0)  // если "слева" две самые нижние точки совпадают по У
					{
						triangle_t t;
						list <edge>::iterator ed_Iter;
						for ( ed_Iter = ed_1.begin(); ed_Iter != ed_1.end(); ed_Iter++)
						{
							edge_t e;
							e = *ed_Iter;
							point_t P_h1, P_h2; // вспомогательные точки
							P_h1 = e.get_a();
							P_h2 = e.get_b();
							if (P0 == P_h1 && P0.get_y() == P_h2.get_y())
							{
								t.set_pqr(P1, P0, e.get_b());
								P0 = e.get_b();
							}
							if (P0 == P_h2 && P0.get_y() == P_h1.get_y())
							{
								t.set_pqr(P1, P0, e.get_a());
								P0 = e.get_a();
							}
						}
					}
					edge_t *E_P11;
					E_P11 = new edge_t[n];
					int l = 0;
					list <edge>::iterator E_P11_Iter;
					for ( E_P11_Iter = E_P1.begin(); E_P11_Iter != E_P1.end(); E_P11_Iter++)
					{
						E_P11[l] = *E_P11_Iter;
						if (P0 != E_P11[l].get_a())
						{
							point_t m1, m2;
							m1 = E_P11[l].get_a();
							m2 = E_P11[l].get_b();
							E_P11[l].set_a(m2);
							E_P11[l].set_b(m1);
						}
						l++;
					}
					qsort(E_P11, n, sizeof(edge_t), compare_edges_down);
					E_P1.clear();
					for (int l = 0; l < n; l++)
					{
						E_P1.push_back(E_P11[l]);
					}
					for ( E_P11_Iter = E_P1.begin(); E_P11_Iter != E_P1.end(); E_P11_Iter++)
					{
						edge_t e;
						e = *E_P11_Iter;
						triangle_t t;
						t.set_pqr(P1, P0, e.get_b());
						if (t.is_tringle_exist() == 1)
						{
							int k = 0;
							list <edge>::iterator ed_Iter1;
							for ( ed_Iter1 = ed_1.begin(); ed_Iter1 != ed_1.end(); ed_Iter1++)
							{
								edge_t si;
								si = *ed_Iter1;
								if (is_cross(t.get_side_c(), si) == 1)
									k++;
							}
							for ( ed_Iter1 = ed_2.begin(); ed_Iter1 != ed_2.end(); ed_Iter1++)
							{
								edge_t si;
								si = *ed_Iter1;
								if (is_cross(t.get_side_c(), si) == 1)
									k++;
							}
							if (k == 0)
							{
								t_g.push_back(t);
								//P4 = P0;
								P0 = t.get_r();
								j = 0;
								break;
							}
						}
					}
				}
			}
		}
	list<triangle>::iterator where_iter;
	where_iter = tri_res->end();
	tri_res->splice(where_iter, t_g);
	return 0;
}

// склейка линия + линия
// склейка линия + триангуляция

int triangulation(list<triangle> *tri, point_t *p, int number_of_points) // рекурсивный алгоритм, N > 5
{
	if (number_of_points == 3)
	{
		point_t x1, x2, x3;
		x1 = p[0];
		x2 = p[1];
		x3 = p[2];
		triangle_t t;
		t.set_pqr(x1, x2, x3);
		if(t.is_tringle_exist() == 1)
		tri->push_back(t);
		else
		{
			if(x1.get_y() == x2.get_y() && x1.get_y() == x3.get_y())
			{
				x2.set_y(x2.get_y() + eps);
				t.set_pqr(x1,x2,x3);
				if(t.is_tringle_exist() == 1)
				tri->push_back(t);
			}
			if(x1.get_x() == x2.get_x() && x1.get_x() == x3.get_x())
			{
				if((x1.get_y() > x2.get_y() && x1.get_y() < x3.get_y()) || (x1.get_y() > x3.get_y() && x1.get_y() < x2.get_y()))
				{
					x1.set_x(x1.get_x() + eps);
					t.set_pqr(x1,x2,x3);
					tri->push_back(t);
				}
				if((x2.get_y() > x1.get_y() && x2.get_y() < x3.get_y()) || (x2.get_y() > x3.get_y() && x2.get_y() < x1.get_y()))
				{
					x2.set_x(x2.get_x() + eps);
					t.set_pqr(x1,x2,x3);
					tri->push_back(t);
				}
				if((x3.get_y() > x2.get_y() && x3.get_y() < x1.get_y()) || (x3.get_y() > x1.get_y() && x3.get_y() < x2.get_y()))
				{
					x3.set_x(x3.get_x() + eps);
					t.set_pqr(x1,x2,x3);
					tri->push_back(t);
				}
			}
		
		}
		return 0;
	}
	if (number_of_points == 4)
	{
		point_t x1, x2, x3, x4; //
		x1 = p[0];
		x2 = p[1];
		x3 = p[2];
		x4 = p[3];
		triangle_t t; //
		t.set_pqr(x1, x2, x3);
		if(t.is_tringle_exist() == 1)
		{
			double k1, k2, k3; //модули векторного произведения
			k1=(x1.get_x()-x4.get_x())*(x2.get_y()-x1.get_y())-(x2.get_x()-x1.get_x())*(x1.get_y()-x4.get_y());
			k2=(x2.get_x()-x4.get_x())*(x3.get_y()-x2.get_y())-(x3.get_x()-x2.get_x())*(x2.get_y()-x4.get_y());
			k3=(x3.get_x()-x4.get_x())*(x1.get_y()-x3.get_y())-(x1.get_x()-x3.get_x())*(x3.get_y()-x4.get_y());
			if ((k1 > 0 && k2 > 0 && k3 > 0) || (k1 < 0 && k2 < 0 && k3 < 0)) // точка x4 - внутри треугольника
			{
				t.set_pqr(x1, x2, x4);
				tri->push_back(t);
				t.set_pqr(x1, x3, x4);
				tri->push_back(t);
				t.set_pqr(x3, x2, x4);
				tri->push_back(t);
				return 0;
			}
			if (k1 == 0) // точка x4 - на стороне х1х2 треугольника
			{
				t.set_pqr(x1, x3, x4);
				tri->push_back(t);
				t.set_pqr(x2, x3, x4);
				tri->push_back(t);
				return 0;
			}
			if (k2 == 0) // точка x4 - на стороне х2х3 треугольника
			{
				t.set_pqr(x1, x3, x4);
				tri->push_back(t);
				t.set_pqr(x2, x1, x4);
				tri->push_back(t);
				return 0;
			}
			if (k3 == 0) // точка x4 - на стороне х1х3 треугольника
			{
				t.set_pqr(x1, x2, x4);
				tri->push_back(t);
				t.set_pqr(x2, x3, x4);
				tri->push_back(t);
				return 0;
			}
			if (k2 * k3 < 0 || k1 * k2 < 0 || k1 * k3 < 0) // точка x4 - вне треугольника
			{
				edge_t *a;
				a = new edge_t[6];
				a[0].set_ab(x1, x2);
				a[1].set_ab(x1, x3);
				a[2].set_ab(x1, x4);
				a[3].set_ab(x4, x2);
				a[4].set_ab(x4, x3);
				a[5].set_ab(x3, x2);
				if(is_cross(a[0],a[4]) == 1 && is_cross(a[1],a[3]) == 0 && is_cross(a[2],a[5]) == 0) 
				{
					t.set_pqr(x1, x2, x3);
					tri->push_back(t);
					t.set_pqr(x2, x1, x4);
					tri->push_back(t);
					return 0;
				}
				if(is_cross(a[1],a[3]) == 1 && is_cross(a[0],a[4]) == 0 && is_cross(a[2],a[5]) == 0) 
				{
					t.set_pqr(x1, x2, x3);
					tri->push_back(t);
					t.set_pqr(x1, x3, x4);
					tri->push_back(t);
					return 0;
				}
				if(is_cross(a[2],a[5]) == 1 && is_cross(a[0],a[4]) == 0 && is_cross(a[1],a[3]) == 0) 
				{
					t.set_pqr(x1, x2, x4);
					tri->push_back(t);
					t.set_pqr(x1, x3, x4);
					tri->push_back(t);
					return 0;
				}
				else
				{
					t.set_pqr(x1, x3, x4);
					tri->push_back(t);
					t.set_pqr(x1, x2, x3);
					tri->push_back(t);
					t.set_pqr(x2, x3, x4);
					tri->push_back(t);
					return 0;
				}
			}
		}
		else
		{
			// три точки на одной прямой
			double x1x, x1y, x2x, x2y, x3x, x3y, x4x, x4y;
			x1x = x1.get_x();
			x1y = x1.get_y();
			x2x = x2.get_x();
			x2y = x2.get_y();
			x3x = x3.get_x();
			x3y = x3.get_y();
			x4x = x4.get_x();
			x4y = x4.get_y();

			if((x1x>x2x&&x1x<x3x)||(x1x>x3x&&x1x<x2x)||(x1y>x2y&&x1y<x3y)||(x1y>x3y&&x1y<x2y))
				// x1 между x2 и x3
			{
				t.set_pqr(x1, x2, x4);
				tri->push_back(t);
				t.set_pqr(x1, x3, x4);
				tri->push_back(t);
				return 0;
			}
			if((x2x>x1x&&x2x<x3x)||(x3x>x2x&&x2x<x1x)||(x2y>x1y&&x2y<x3y)||(x2y>x3y&&x2y<x1y)) 
				// x2 между x1 и x3
			{
				t.set_pqr(x1, x2, x4);
				tri->push_back(t);
				t.set_pqr(x2, x3, x4);
				tri->push_back(t);
				return 0;
			}
			if((x3x>x2x&&x3x<x1x)||(x3x>x1x&&x3x<x2x)||(x3y>x2y&&x3y<x1y)||(x3y>x1y&&x3y<x2y)) 
				// x3 между x1 и x2
			{
				t.set_pqr(x1, x3, x4);
				tri->push_back(t);
				t.set_pqr(x2, x3, x4);
				tri->push_back(t);
				return 0;
			}
			return 0;
		}

	} // конец number = 4

	if (number_of_points == 8)
	{
		list<triangle> tri1; //
		point_t *p1;
		list<triangle> tri2; //
		point_t *p2;
		p1 = new point_t[4]; //
		p2 = new point_t[4]; //
		for (int i = 0; i < 4; i++)
		{
			p1[i] = p[i];
			p2[i] = p[i + 4];
		}
		triangulation(&tri1, p1, 4);
		triangulation(&tri2, p2, 4);

		gluing(&tri1, &tri2, tri);

		list<triangle>::iterator where_iter;
		where_iter = tri->end();
		tri->splice(where_iter, tri1);
		where_iter = tri->end();
		tri->splice(where_iter, tri2);
		if (p1 > 0) delete[]p1;
		if (p2 > 0) delete[]p2;
		return 0;
	}

	if (number_of_points < 12)
	{
		list<triangle> tri1; //
		point_t *p1;
		list<triangle> tri2; //
		point_t *p2;
		p1 = new point_t[3]; //
		p2 = new point_t[number_of_points - 3]; //
		for (int i = 0; i < 3; i++)
		{
			p1[i] = p[i];
		}
		for (int i = 0; i < number_of_points - 3; i++)
		{
			p2[i] = p[i + 3];
		}
		tri1.clear();
		tri2.clear();
		triangulation(&tri1, p1, 3);
		triangulation(&tri2, p2, number_of_points - 3);
		
		gluing(&tri1, &tri2, tri);
		list<triangle>::iterator where_iter;
		where_iter = tri->end();
		tri->splice(where_iter, tri1);
		where_iter = tri->end();
		tri->splice(where_iter, tri2);
		if (p1 > 0) delete[]p1;
		if (p2 > 0) delete[]p2;
		return 0;
	}

	if (number_of_points >= 12)
	{
		list<triangle> tri1; //
		point_t *p1;
		list<triangle> tri2; //
		point_t *p2;

		int n1 = number_of_points / 2; //
		int n2; //
		if (number_of_points % 2 == 1)
		{
			n2 = number_of_points / 2 + 1;
		}
		else n2 = number_of_points / 2;
		p1 = new point_t[n1]; //
		p2 = new point_t[n2]; //
		for (int i = 0; i < n1; i++)
		{
			p1[i] = p[i];
		}
		for (int i = 0; i < n2; i++)
		{
			p2[i] = p[i + n1];
		}
		triangulation(&tri1, p1, n1);
		triangulation(&tri2, p2, n2);

		gluing(&tri1, &tri2, tri);

		list<triangle>::iterator where_iter;
		where_iter = tri->end();
		tri->splice(where_iter, tri1);
		where_iter = tri->end();
		tri->splice(where_iter, tri2);
		if (p1 > 0) delete[]p1;
		if (p2 > 0) delete[]p2;
		return 0;
	}
	return 0;
}  // конец triangulation

void get_edges(list<edge> *ed, list<triangle> *tr)
{
	list<triangle>::iterator tr_Iter;
	for ( tr_Iter = tr->begin(); tr_Iter != tr->end(); tr_Iter++)
	{
		triangle_t t;
		t = *tr_Iter;
		edge_t a ,b , c;
		a = t.get_side_a();
		b = t.get_side_b();
		c = t.get_side_c();
		ed->push_back(a);
		ed->push_back(b);
		ed->push_back(c);
	}
}

/*list<triangle> corr_triangles(list<triangle> *tr)
{
	list<triangle> tr1;
	list <triangle>::iterator tr_Iter;
	for ( tr_Iter = tr->begin(); tr_Iter != tr->end(); tr_Iter++)
	{
		triangle_t t;
		t = *tr_Iter;
		point_t p1, q1, r1;
		p1 = t.get_p();
		q1 = t.get_q();
		r1 = t.get_r();
		double px,py,qx,qy,rx,ry;
		px = p1.get_x();
		py = p1.get_y();
		qx = q1.get_x();
		qy = q1.get_y();
		rx = r1.get_x();
		ry = r1.get_y();
		double epsx1, epsx2, epsy1, epsy2;
		if (p1.get_x() == r1.get_x())
		{
			epsx1 = p1.get_x() - q1.get_x();
			epsx2 = q1.get_x() - p1.get_x();
		}
		if (p1.get_y() == r1.get_y())
		{
			epsy1 = p1.get_y() - q1.get_y();
			epsy2 = q1.get_y() - p1.get_y();
		}
		if (px==qx&&px==rx&&(py!=qy||py!=ry||qy!=ry)&&(eps==epsx1||eps==epsx2||eps==epsy1||eps==epsy2))
		{}
		else tr1.push_back(t);
		if (py==qy&&py==ry&&(px!=qx||px!=rx||qx!=rx)&&(eps==epsx1||eps==epsx2||eps==epsy1||eps==epsy2))
		{}
		else tr1.push_back(t);
		
	}
	return tr1;
}*/