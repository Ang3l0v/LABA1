#include <iostream>
using namespace std;
class logical_values_array
{
private:
	unsigned int _value;
public:
	logical_values_array(unsigned int value = 0) { _value = value; }
	unsigned int accesor() { return _value; }
	void inversion() { _value = ~_value; }
	void conjunction(logical_values_array& ob) { _value = _value & ob._value; }
	void disjunction(logical_values_array& ob) { _value = _value | ob._value; }
	void implication(logical_values_array& ob) { _value = (~_value) | ob._value; }
	void coimplication(logical_values_array& ob) { _value = ~((~_value) | ob._value); }
	void equivalence(logical_values_array& ob) { _value = ((_value & ob._value) | (~(_value) & ~(ob._value))); }
	void arrow(logical_values_array& ob) { _value = ~(_value | ob._value); }
	void hatch(logical_values_array& ob) { _value = ~(_value & ob._value); }
	void add_mod_2(logical_values_array& ob){ _value = (~(_value)&ob._value) | (_value & ~(ob._value)); }
	static bool equals(logical_values_array& ob1, logical_values_array& ob2) { return ob1._value == ob2._value; }
	bool get_bit(unsigned int possition) { return (_value & (1 << possition)) >> possition; }
	void dectobin(char* string);
};
void logical_values_array::dectobin(char* b)
{
	if (_value == 0) {
		b[0] = '0';
		b[1] = '\0';
	}
	else {
		int i = 0;
		long long temp = _value;
		for (i = 0; temp > 0; temp = temp >> 1, i++);

		b[i] = '\0';
		while (_value > 0) {
			i -= 1;
			b[i] = '0' + (_value - (_value >> 1) * 2);
			_value = _value >> 1;
		}
	}
}
int main()
{
	logical_values_array ob(10);
	char* str = new char[255];
	ob.dectobin(str);
	cout << str << endl;
	logical_values_array ob2(2), ob3(3), ob4(4), ob5(5), ob6(3), ob7;
	ob2.conjunction(ob3);
	ob2.coimplication(ob4);
	ob7.equals(ob3, ob6);
	ob6.equivalence(ob3);
	ob5.arrow(ob2);
	ob3.disjunction(ob3);
	ob3.add_mod_2(ob5);
	ob6.get_bit(1);
	ob3.hatch(ob7);

}