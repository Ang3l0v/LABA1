#include <iostream>
#include <cmath>
using namespace std;
class complex
{
private:
	double _valid;
	double _imaginary;
public:
	complex(double valid = 0, double imaginary = 0) { _valid = valid; _imaginary = imaginary; }
	complex addition(complex& ob1, complex& ob2);
	complex subtraction(complex& ob1, complex& ob2);
	complex mult(complex& ob1, complex& ob2);
	complex addition(complex& ob1, complex& ob2);
	complex div(complex& ob1, complex& ob2);
	double get_valid() { return _valid; }
	double get_imag() { return _imaginary; }
	double module();
	double argument();
	void show();
};
complex complex::addition(complex& ob1, complex& ob2)
{
	complex temp;
	temp._imaginary = ob1._imaginary + ob2._imaginary;
	temp._valid = ob1._valid + ob2._valid;
	return temp;
}
complex complex::subtraction(complex& ob1, complex& ob2)
{
	complex temp;
	temp._imaginary = ob1._imaginary - ob2._imaginary;
	temp._valid = ob1._valid - ob2._valid;
	return temp;
}
complex complex::mult(complex& ob1, complex& ob2)
{
	complex temp;
	temp._valid = ob1._valid * ob2._valid;
	temp._imaginary = ob1._imaginary * ob2._imaginary;
	return temp;
}
complex complex::div(complex& ob1, complex& ob2)
{
	complex temp;
	temp._valid = (ob1._valid * ob2._valid + ob1._imaginary * ob2._imaginary) / (ob2._valid * ob2._valid + ob2._imaginary * ob2._imaginary);
	temp._imaginary = (ob1._imaginary * ob2._valid - ob1._valid - ob2._imaginary) / (ob2._valid * ob2._valid + ob2._imaginary * ob2._imaginary);
	return temp;
} 
double complex::module()
{
	return sqrt(_valid * _valid + _imaginary * _imaginary);
}
double complex::argument()
{
	return atan(_imaginary / _valid);
}
void complex::show()
{
	cout << _imaginary << endl << _valid << endl;
}
int main()
{
	complex ob1(2, 134), ob2(134, 2), ob3;
	ob3.addition(ob1, ob2);
	ob3.subtraction(ob1, ob2);
	ob3.mult(ob1, ob2);
	ob3.div(ob1, ob2);
	ob2.module();
	ob2.argument();


}