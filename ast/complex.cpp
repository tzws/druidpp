/*
 * C++ Program to Implement Complex Numbers using Classes
*/
#include <iostream>
using namespace std;

class Complex
{
	private:
		int real;
		int imag;    

	public:

		Complex(int r = 0, int i = 0): real(r), imag(i) {};
		void setComplex(void)
		{
			cout << "Enter the real and imaginary parts : ";
			cin >> this->real;
			cin >> this->imag;
		}  

		Complex add(const Complex& c)
		{
			Complex comp;
			comp.real = this->real + c.real;
			comp.imag = this->imag + c.imag;
			return comp;
		}

		Complex subtract(const Complex& c)
		{
			Complex comp;
			comp.real = this->real - c.real;
			comp.imag = this->imag - c.imag;
			return comp;
		}

		void printComplex(void)
		{
			cout << "Real      : " << this->real << endl
				<< "Imaginary : " << this->imag << endl;
		}
};


int main()
{
	Complex a, b, c, d;
	cout << "Setting first complex number " << endl;
	a.setComplex();
	cout << "Setting second complex number " << endl;
	b.setComplex();

	/* Adding two complex numbers */
	cout << "Addition of a and b    : " << endl;
	c = a.add(b);
	c.printComplex();

	/* Subtracting two complex numbers */

	cout << "Subtraction of a and b : " << endl;
	d = a.subtract(b);
	d.printComplex();

}

