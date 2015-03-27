#include <iostream>
#include "poin.h"
#include "edge.h"
#include <fstream>
#include <list>
#include "triangle.h"
#include "triangulation.h"
using namespace std;


int main()
{
	ifstream file;
	char *fname = "data.txt";
	file.open(fname);
	int N;
	file >> N;
	point_t *ar;
	ar = new point_t[N]; //
	for (int i = 0; i < N; i++)
	{
		double x,y,f;
		file >> x >> y >> f;
		ar[i].set_x(x);
		ar[i].set_y(y);
		ar[i].set_f(f);
	}
	qsort(ar, N, sizeof(point_t), compare_points); // отсортированный массив точек
	// удаление одинаковых точек
	for (int i = 0; i < N; i++)
	{
		for (int j = i; j < N; j++)
			if (ar[i].get_x() == ar[j].get_x() && ar[i].get_x() == ar[j].get_x())
				ar[j].set_f(ar[i].get_f());
	}
	list<poin> p_l;
	for (int i = 0; i < N; i++)
	{
		p_l.push_back(ar[i]);
	}
	p_l.unique();

	N = p_l.size();
	point_t *ar_n;
	ar_n = new point_t[N]; //
	int i = 0;
	list <poin>::iterator p_Iter;
	for ( p_Iter = p_l.begin(); p_Iter != p_l.end(); p_Iter++)
	{
		point_t p1;
		p1 = *p_Iter;
		ar_n[i].set_x(p1.get_x());
		ar_n[i].set_y(p1.get_y());
		ar_n[i].set_f(p1.get_f());
		i++;
	}

	list<triangle> tr;
	tr.clear();
	triangulation(&tr, ar_n, N);
	//list<triangle> corr_tr = corr_triangles(&tr);
		list <triangle>::iterator tr_Iter;
		for ( tr_Iter = tr.begin(); tr_Iter != tr.end(); tr_Iter++)
		{
			point_t a1,b1,c1;
			triangle_t t;
			t = *tr_Iter;
			a1 = t.get_p();
			b1 = t.get_q();
			c1 = t.get_r();
			cout << a1.get_x() << ' ' << a1.get_y() << endl;
			cout << b1.get_x() << ' ' << b1.get_y() << endl;
			cout << c1.get_x() << ' ' << c1.get_y() << endl << endl;
		}
		cout << tr.size() << endl;
	point_t siz;
	siz = find_big_y(&tr);
	cout << siz.get_y() << endl;
	siz = find_big_x(&tr);
	cout << siz.get_x() << endl;
	cout << tr.size() << endl;
	file.close();
	return 0;
}