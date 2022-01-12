#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

const int N_int = 10;
const double x0 = -M_PI;
const double x1 = M_PI;
const int N_sim = 500;
const int N = 100;  // Change N here

// functions
double s_func(double);
vector<double> s_func(vector<double>);
void init_interval(vector<double> &);
double s_exp_theor(double, int);
vector<double> s_exp_theor(vector<double>, int);
double s_exp_num_simpson(double, int);
vector<double> s_exp_num_simpson(vector<double>, int);
double s_exp_num_trapezoid(double, int);
vector<double> s_exp_num_trapezoid(vector<double>, int);

// main
int main()
{
	ostringstream file_name_simpson, file_name_trapezoid;
	file_name_simpson << "fourier_simpson_N" << N << "_Nint" << N_int << ".dat";
	file_name_trapezoid << "fourier_trapezoid_N" << N << "_Nint" << N_int << ".dat";
	ofstream ofs_simpson(file_name_simpson.str().c_str());
	ofstream ofs_trapezoid(file_name_trapezoid.str().c_str());
	vector<double> x(N_int);
	vector<double> s(N_int);
	vector<double> s_theor(N_int);
	vector<double> s_num_simpson(N_int);
	vector<double> s_num_trapezoid(N_int);

	init_interval(x);			// initialize interval
	s = s_func(x);				// compute square wave function
	s_theor = s_exp_theor(x,N);		// theoretical Fourier expansion order N
	s_num_simpson = s_exp_num_simpson(x,N);			// numerical Fourier coefficients order N, simpson
	s_num_trapezoid = s_exp_num_trapezoid(x,N);			// numerical Fourier coefficients order N, trapezoid

	for (int i=0; i<x.size(); i++){		// printing to a file
		ofs_simpson << x[i] << "\t" << s[i] << "\t" << s_theor[i] << "\t" << s_num_simpson[i] << endl;
		ofs_trapezoid << x[i] << "\t" << s[i] << "\t" << s_theor[i] << "\t" << s_num_trapezoid[i] << endl;
	}

	ofs_simpson.close();
	ofs_trapezoid.close();

	return 0;
}

/*-------------------------------------------*/
// square wave function
double s_func(double x)
{
	x = fmod(x,x1-x0);
	if (x<0) return -1.;
	else if (x>=0) return 1.;
}

// calculate square wave for interval
vector<double> s_func(vector<double> x)
{
	vector<double> s(x.size());

	for (int i=0; i<x.size(); i++)
	{
		s[i] = s_func(x[i]);
	}
	return s;
}

// initialze interval
void init_interval(vector<double> &vec)
{
	for (int i=0; i<vec.size(); i++)
		//vec[i] = x0 + (x1-x0)/(N_int-1)*i;
		vec[i] = x0 + (x1-x0)/(N_int)*i; // corrected (Arijit)
}

// theoretical Fourier expansion order N
// see http://mathworld.wolfram.com/FourierSeriesSquareWave.html
double s_exp_theor(double x, int N)
{
	double a_k, b_k;		// Fourier coeff
	double s_exp = 0;		// Fourier expansion approximation

	for (int k=1; k<N; k++)		// up to order N
	{
		a_k = 0.;
		if (k%2!=0) b_k = 4./(k*M_PI);	// actual coefficient
		else b_k = 0.;
		s_exp += a_k*cos(k*x) + b_k*sin(k*x);
	}
	return s_exp;
}

// compute theoretical Fourier expansion order N for interval
vector<double> s_exp_theor(vector<double> x, int N)
{
	vector<double> s_exp(x.size());

	for (int i=0; i<x.size(); i++)
	{
		s_exp[i] = s_exp_theor(x[i],N);
	}
	return s_exp;
}

// Simpson integral of function func for the interval [x0, x1]
double simpson_integral(double (*func)(double, int), int k, double x0, double x1, int n)
{
	double I = 0.;
	double x = x0;
	//double h = (x1-x0)/(n-1);	// stepsize
	double h = (x1-x0)/n;// corrected (Arijit)
	do
	{
		I += h/6.* (func(x,k)+4.*func(x+h/2.,k)+func(x+h,k));
		x += h;
	}
	while (x<=x1);
	return I;
}

// Trapezoid integral of function func for the interval [x0,x1]
double trapezoid_integral(double (*func)(double,int), int k, double x0, double x1, int n)
{
	double I = 0.;
	double x = x0;
	//double h = (x1-x0)/(n-1);
	double h = (x1-x0)/n;// corrected (Arijit)
	do
	{
		I += h*(func(x,k) + func(x+h,k))/2.;
		x += h;
	}
	while (x<=x1);
	return I;
}


// integrand of the a_k coefficient
double a_k_func(double x, int k)
{
	return s_func(x)*cos(2*M_PI*k*x/(x1-x0));
}

// integrand of the b_k coefficient
double b_k_func(double x, int k)
{
	return s_func(x)*sin(2*M_PI*k*x/(x1-x0));
}

// numerical Fourier expansion order N, simpson rule
double s_exp_num_simpson(double x, int N)
{
	double a_k, b_k;		// Fourier coeff
	double s_exp = 0;		// Fourier expansion approximation

	for (int k=0; k<N; k++)		// up to order N
	{
		a_k = (2./(x1-x0))*simpson_integral(&a_k_func, k, x0, x1, N_sim);
		b_k = (2./(x1-x0))*simpson_integral(&b_k_func, k, x0, x1, N_sim);
		s_exp += a_k*cos(k*x) + b_k*sin(k*x);
	}
	return s_exp;

}

// numerical Fourier expansion order N, trapezoid rule
double s_exp_num_trapezoid(double x, int N)
{
	double a_k, b_k;		// Fourier coeff
	double s_exp = 0;		// Fourier expansion approximation

	for (int k=0; k<N; k++)		// up to order N
	{
		a_k = (2./(x1-x0))*trapezoid_integral(&a_k_func, k, x0, x1, N_sim);
		b_k = (2./(x1-x0))*trapezoid_integral(&b_k_func, k, x0, x1, N_sim);
		s_exp += a_k*cos(k*x) + b_k*sin(k*x);
	}
	return s_exp;

}

// compute numerical Fourier expansion order N for interval, simpson rule
vector<double> s_exp_num_simpson(vector<double> x, int N)
{
	vector<double> s_exp(x.size());

	for (int i=0; i<x.size(); i++)
	{
		s_exp[i] = s_exp_num_simpson(x[i],N);
	}
	return s_exp;
}

// compute numerical Fourier expansion order N for interval, trapezoid rule
vector<double> s_exp_num_trapezoid(vector<double> x, int N)
{
	vector<double> s_exp(x.size());

	for (int i=0; i<x.size(); i++)
	{
		s_exp[i] = s_exp_num_trapezoid(x[i],N);
	}
	return s_exp;
}
