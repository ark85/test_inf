#include <iostream>
#include "poin.h"
#include "edge.h"
#include <list>
#include "triangle.h"
using namespace std;



int compare_points(const void * x1, const void * y1);
int compare_edges_up(const void * x1, const void * y1);
int is_cross(edge_t s_in, edge_t s_out);
point_t find_big_y(list<triangle> *tri); //сама€ высока€ точка в данной триангул€ции
int compare_edges_down(const void * x1, const void * y1);
point_t find_low_y(list<triangle> *tri); // сама€ низка€ точка в данной триангул€ции
point_t find_big_x(list<triangle> *tri); //сама€ "дальн€€" точка в данной триангул€ции
int  cmp_point (point_t *p1, point_t *p2);
int gluing(list<triangle> *tri1, list<triangle> *tri2, list<triangle> *tri_res); // склейка
int triangulation(list<triangle> *tri, point_t *p, int number_of_points); // рекурсивный алгоритм, N > 5
void get_edges(list<edge> *ed, list<triangle> *tr);
//list<triangle> corr_triangles(list<triangle>*);