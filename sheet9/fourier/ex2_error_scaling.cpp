#include<iostream>
#include<math.h>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

const double x0 = -M_PI;
const double x1 = M_PI;

// Simpson integral of function func for the interval [x0, x1]
double simpson_integral(double (*func)(double, int), int k, double x0, double x1, int n)
{
	double I = 0.;
	//double h = (x1-x0)/(n-1);	// stepsize
	double h = (x1-x0)/n;// stepsize (corrected by Arijit)

	//for(int i=0;i<(n-1);i++){
	for(int i = 0; i < n; i++){ // corrected by Arijit
		I += func(x0+i*h,k) + 4.*func(x0+(i+0.5)*h,k) + func(x0+(i+1)*h,k);
	}
	I *= h/6.;
	/*
	do
	{
		I += h/6.* (func(x,k)+4.*func(x+h/2.,k)+func(x+h,k));
		x += h;
	}
	while (x<x1);*/
	return I;
}

// Trapezoid integral of function func for the interval [x0,x1]
double trapezoid_integral(double (*func)(double,int), int k, double x0, double x1, int n)
{
	double I = 0.;

	//double h = (x1-x0)/(n-1);
	double h = (x1-x0)/n; // corrected by Arijit

	//for(int i=0;i<(n-1);i++){
	for(int i = 0; i < n; i++){ // corected by Arijit
		I += func(x0+i*h,k) + func(x0+(i+1)*h,k);
	}

	I*= h/2.;
	/*
	do
	{
		I += h*(func(x,k) + func(x+h,k))/2.;
		x += h;
	}
	while (x<x1); */
	return I;
}

// square wave function
double s_func(double x)
{
	x = fmod(x,x1-x0);
	if (x<0) return -1.;
	else if (x>=0) return 1.;
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


double a_k_simpson(int k, int N_int){
    return (2./(x1-x0))*simpson_integral(&a_k_func, k, x0, x1, N_int);
}

double b_k_simpson(int k, int N_int){
    return (2./(x1-x0))*simpson_integral(&b_k_func, k, x0, x1, N_int);
}

double a_k_trapezoid(int k, int N_int){
    return (2./(x1-x0))*trapezoid_integral(&a_k_func, k, x0, x1, N_int);
}

double b_k_trapezoid(int k, int N_int){
    return (2./(x1-x0))*trapezoid_integral(&b_k_func, k, x0, x1, N_int);
}


double a_k_theo(int k){
    return 0.;
}

double b_k_theo(int k){
    if (k%2!=0)
        return 4./(k*M_PI);	// actual coefficient
    else return 0.;
}


double sqfunc(double x,int k){
	return x*x*x;
}

int main(){
    string file_name_simpson_a = string("error_scaling_simpson_a.dat");
	string file_name_trapezoid_a = string("error_scaling_trapezoid_a.dat");

    string file_name_simpson_b = string("error_scaling_simpson_b.dat");
	string file_name_trapezoid_b = string("error_scaling_trapezoid_b.dat");

    ofstream ofs_simpson_a(file_name_simpson_a.c_str());
    ofstream ofs_trapezoid_a(file_name_trapezoid_a.c_str());

    ofstream ofs_simpson_b(file_name_simpson_b.c_str());
    ofstream ofs_trapezoid_b(file_name_trapezoid_b.c_str());

	ofstream ofs_xsquare("error_xsqur.dat");

	for (int N = 10;N<=10000;N+=100){
		ofs_xsquare << fabs(simpson_integral(&sqfunc, 1, -1., 1., N)-
	.0) << "\t" << fabs(trapezoid_integral(&sqfunc, 1, -1., 1., N) - .0) << endl;
	}

    for(int k=0;k<10;k++){
        for(int N = 10;N<=10000;N+=100){
            ofs_simpson_a << fabs(a_k_simpson(k,N)-a_k_theo(k)) << "\t";
    		ofs_trapezoid_a << fabs(a_k_trapezoid(k,N)-a_k_theo(k)) << "\t";

            ofs_simpson_b << fabs(b_k_simpson(k,N)-b_k_theo(k)) << "\t";
    		ofs_trapezoid_b << fabs(b_k_trapezoid(k,N)-b_k_theo(k)) << "\t";
        }
        ofs_simpson_a << endl;
        ofs_trapezoid_a << endl;
        ofs_simpson_b << endl;
        ofs_trapezoid_b << endl;
    }
    ofs_simpson_a.close();
    ofs_trapezoid_a.close();
    ofs_simpson_b.close();
    ofs_trapezoid_b.close();
    return 0;
}
