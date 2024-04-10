#include <iostream>
#include <stdarg.h>
#include <cmath>
using namespace std;
class matrix {
private:
	double** _elements;
	size_t _n;
	double det;
public:
	matrix() {_elements = nullptr; _n = 0; }
	matrix(int count, ...);
	matrix(matrix const& m);
	~matrix();
	void show() const;
	matrix& operator=(matrix const& ob);
	matrix operator+(matrix const& ob);
	matrix operator*(matrix const& ob);
	matrix operator*(double num);
	friend matrix operator*(double num, matrix const& ob);
	matrix operator-(matrix const& ob);
	double determinant();
	void transposition();
	matrix inverse() const;
};
matrix::matrix(int count, ...) 
{
	_n = sqrt(count);
	va_list va;
	va_start(va, count);
	_elements = new double* [_n];
	for (int i = 0; i < _n; i++) 
	{
		_elements[i] = new double[_n];
		for (int j = 0; j < _n; j++) 
		{
			_elements[i][j] = va_arg(va, double);
		}
	}
	va_end(va);
}
matrix::matrix(matrix const& ob)
{
	_n = ob._n;
	_elements = new double* [_n];
	for (int i = 0; i < _n; i++)
	{
		_elements[i] = new double[_n];
		for (int j = 0; j < _n; j++)
		{ 
			_elements[i][j] = ob._elements[i][j];
		}
	}
}
matrix& matrix::operator=(matrix const& ob) 
{
	for (int i = 0; i < _n; i++)
	{
		delete _elements[i]; 
	}
	delete[]_elements;
	_n = ob._n;
	_elements = new double* [_n];
	for (int i = 0; i < _n; i++) 
	{
		_elements[i] = new double[_n];
		for (int j = 0; j < _n; j++) 
		{ 
			_elements[i][j] = ob._elements[i][j];
		}
	}
	return *this;
}
matrix::~matrix()
{
	for (int i = 0; i < _n; i++)
	{
		delete _elements[i];
	}
	delete[]_elements;
}
void matrix::show() const 
{
	for (int i = 0; i < _n; i++) 
	{
		for (int j = 0; j < _n; j++)
		{ 
			cout << _elements[i][j] << "\t"; 
		}
		cout << endl;
	}
}
matrix matrix::operator+(matrix const& ob)
{
	matrix temp = *this;
	if (_n != ob._n)
	{
		cout << "Сложить матрицы невозможно." << endl;
	}
	else 
	{
		for (int i = 0; i < _n; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				temp._elements[i][j] += ob._elements[i][j];
			}
		}
	}
	return temp;
}
matrix matrix::operator*(matrix const& ob) 
{
	matrix temp = *this;
	if (_n != ob._n)
	{
		cout << "Умножить матрицы невозможно." << endl;
	}
	else
	{
		for (int i = 0; i < _n; i++)
		{
			for (int j = 0; j < _n; j++) 
			{
				temp._elements[i][j] = 0;
				for (int k = 0; k < _n; k++)
				{
					temp._elements[i][j] += _elements[i][k] * ob._elements[k][j];
				}
			}
		}
	}
	return temp;
}
matrix matrix::operator*(double num) 
{
	matrix temp = *this;
	for (int i = 0; i < _n; i++) 
	{
		for (int j = 0; j < _n; j++)
		{
			temp._elements[i][j] *= num;
		}
	}
	return temp;
}
matrix operator*(double num, matrix const& ob) 
{
	matrix temp = ob;
	for (int i = 0; i < temp._n; i++) 
	{
		for (int j = 0; j < temp._n; j++)
		{
			temp._elements[i][j] *= num; 
		}
	}
	return temp;
}
matrix matrix::operator-(matrix const& ob) 
{
	matrix temp = *this;
	if (_n != ob._n) 
	{
		cout << "Вычитать матрицы невозможно." << endl;
	}
	else 
	{
		for (int i = 0; i < _n; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				temp._elements[i][j] -= ob._elements[i][j];
			}
		}
	}
	return temp;
}
double matrix::determinant() 
{
	matrix m = *this;
	size_t n = m._n;
	double d = 1;
	for (size_t i = 0; i < n; ++i)
	{
		double pivotElement = m._elements[i][i];
		size_t pivotRow = i;
		for (size_t row = i + 1; row < n; ++row)
		{
			if (abs(m._elements[row][i]) > abs(pivotElement)) 
			{
				pivotElement = m._elements[row][i];
				pivotRow = row;
			}
		}
		if (pivotElement == 0) 
		{ 
			return 0; 
		}
		if (pivotRow != i) 
		{
			swap(m._elements[i], m._elements[pivotRow]);
			d *= -1;
		}
		d *= pivotElement;
		for (size_t row = i + 1; row < n; ++row) 
		{
			for (size_t col = i + 1; col < n; ++col)
			{
				m._elements[row][col] -= m._elements[row][i] * m._elements[i][col] / pivotElement;
			}
		}
	}

	return d;
}
void matrix::transposition() 
{
	for (int i = 0; i < _n; i++)
	{
		for (int j = i; j < _n; j++) 
		{
			swap(_elements[i][j], _elements[j][i]);
		}
	}
}
matrix matrix::inverse() const 
{
	matrix temp = *this; 
	matrix identity = *this; 
	for (int i = 0; i < _n; i++)
	{
		for (int j = 0; j < _n; j++) 
		{
			identity._elements[i][j] = 0;
		}
	}
	for (int i = 0; i < _n; i++)
	{
		identity._elements[i][i] = 1.0;
	}

	for (size_t i = 0; i < _n; i++) 
	{
		size_t pivot_row = i;
		for (size_t j = i + 1; j < _n; j++)
		{
			if (abs(temp._elements[j][i]) > abs(temp._elements[pivot_row][i]))
			{
				pivot_row = j;
			}
		}

		if (pivot_row != i) 
		{
			for (size_t j = 0; j < _n; j++)
			{
				swap(temp._elements[i][j], temp._elements[pivot_row][j]);
				swap(identity._elements[i][j], identity._elements[pivot_row][j]);
			}
		}

		double pivot = temp._elements[i][i];
		for (size_t j = 0; j < _n; j++) 
		{
			temp._elements[i][j] /= pivot;
			identity._elements[i][j] /= pivot;
		}

		for (size_t k = 0; k < _n; k++)
		{
			if (k != i) 
			{
				double factor = temp._elements[k][i];
				for (size_t j = 0; j < _n; j++) 
				{
					temp._elements[k][j] -= factor * temp._elements[i][j];
					identity._elements[k][j] -= factor * identity._elements[i][j];
				}
			}
		}
	}
	return identity;
}
int main()
{
	matrix ob1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
	matrix ob2(ob1), ob3;
	ob1.show();
	cout << endl;
	ob2.show();
	cout << endl;
	ob3 = 2 * (ob1 * 2);
	ob3.show();
	cout << endl;
	ob3 = ob3 - ob1;
	ob3.show();
	cout << endl;
	cout << ob1.determinant() << endl;
	ob1.transposition();
	ob1.show();
	cout << endl;
	ob3 = ob1.inverse();
	ob3.show();
}