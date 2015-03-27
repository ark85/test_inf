#pragma once
typedef class poin // точка
{
	double x,y,f;
public:
	
	poin(void);
	~poin(void);
	poin(double,double,double);
	void set_x(double);
	void set_y(double);
	void set_f(double);
	double get_x();
	double get_y();
	double get_f();
	poin& operator=(poin &p_1)
	{
		x = p_1.get_x();
		y = p_1.get_y();
		f = p_1.get_f();
		return *this;
	}
	poin& operator-(poin &p_1)
	{
		double q = p_1.get_x();
		x = x - q;
		q = p_1.get_y();
		y = y - q;
		f = -1000;
		return *this;
	}

	bool poin::operator!=(poin &p_1)
	{
		if (p_1.get_f() != this->get_f()) return 1;
		if (p_1.get_x() != this->get_x()) return 1;
		if (p_1.get_y() != this->get_y()) return 1;
		return 0;
	}
	bool poin::operator==(poin &p_1)
	{
		if (p_1.get_f() == this->get_f())
		if (p_1.get_x() == this->get_x())
		if (p_1.get_y() == this->get_y()) return 1;
		return 0;
	}

}point_t;


