
#include <math.h>
#include <iostream>
#include <iomanip>
#include <conio.h>

namespace std;
class complex
{
	private:
		float real;      // Real Part
		float imag;      //  Imaginary Part


	public:
		complex(float,float);
		complex(complex&);
		complex operator +(complex);
		complex operator -(complex);
		complex operator *(complex);
		complex operator /(complex);
		complex getconjugate();
		complex getreciprocal();
		float getmodulus();
		void setdata(float,float);
		void getdata();
		float getreal();
		float getimaginary();
		bool operator ==(complex);
		void operator =(complex);
		friend ostream& operator <<(ostream &s,complex &c);
};
//CONSTRUCTOR
complex::complex(float r=0.0f,float im=0.0f)
{
	real=r;
	imag=im;
}

//COPY CONSTRUCTOR
complex::complex(complex &c)
{
	this->real=c.real;
	this->imag=c.imag;
}

void complex::operator =(complex c)
{
	real=c.real;
	imag=c.imag;
}

complex complex::operator +(complex c)
{
	complex tmp;
	tmp.real=this->real+c.real;
	tmp.imag=this->imag+c.imag;
	return tmp;
}
complex complex::operator -(complex c)
{
	complex tmp;
	tmp.real=this->real - c.real;
	tmp.imag=this->imag - c.imag;
	return tmp;
}

complex complex::operator *(complex c)
{
	complex tmp;
	tmp.real=(real*c.real)-(imag*c.imag);
	tmp.imag=(real*c.imag)-(imag*c.real);
	return tmp;
}

complex complex::operator /(complex c)
{
	float div=(c.real*c.real) + (c.imag*c.imag);
	complex tmp;
	tmp.real=(real*c.real)+(imag*c.imag);
	tmp.real/=div;
	tmp.imag=(imag*c.real)-(real*c.imag);
	tmp.imag/=div;
	return tmp;
}

complex complex::getconjugate()
{
	complex tmp;
	tmp.real=this->real;
	tmp.imag=this->imag * -1;
	return tmp;
}

complex complex::getreciprocal()
{
	complex t;
	t.real=real;
	t.imag=imag * -1;
	float div;
	div=(real*real)+(imag*imag);
	t.real/=div;
	t.imag/=div;
	return t;
}

float complex::getmodulus()
{
	float z;
	z=(real*real)+(imag*imag);
	z=sqrt(z);
	return z;
}

void complex::setdata(float r,float i)
{
	real=r;
	imag=i;
}

void complex::getdata()
{
	cout<<"Enter Real:";
	cin>>this->real;
	cout<<"Enter Imaginary:";
	cin>>this->imag;

}

float complex::getreal()
{
	return real;
}

float complex::getimaginary()
{
	return imag;
}

bool complex::operator ==(complex c)
{
	return (real==c.real)&&(imag==c.imag) ? 1 : 0;
}

ostream& operator <<(ostream &s,complex &c)
{
	s<<"Real Part = "<<c.real<<endl
		<<"Imaginary Part = "<<c.imag<<endl;
	s<<"z = "<<c.real<<setiosflags(ios::showpos)
		<<c.imag<<"i"<<endl<<resetiosflags(ios::showpos);
	return s;
}



void main()
{
	complex a(10.0f,-2.f); // Calls Constructor
	cout<<a<<endl;         // Calls the overloaded << operator
	complex b(-2);         // Calls Constructor
	complex c=b;           // Calls Copy Constructor
	c=a;                   // calls overloaded = operator
	b.getdata();          // Calls Getdata()
	c.getdata();
	if(b==c)            // calls overloaded == operator
		cout<<"b == c";
	else
		cout<<"b != c";


	cout<<endl<<c.getmodulus()<<endl; // calls getmodulus function()
	complex d;
	d=a+b;   // Calls overloaded +
	cout<<d<<endl;
	d=a-b;                 // Calls overloaded -
	cout<<d<<endl;
	d=a*b;        // calls overloaded *
	cout<<d<<endl;
	d=a/b;        // calls overloaded /
	cout<<d<<endl;

	getch();
} 
