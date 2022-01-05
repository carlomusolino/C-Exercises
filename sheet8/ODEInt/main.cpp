#include<fstream>
#include<stdlib.h>
#include<cmath>
#include "odeint.hpp"
#include "odeint_conventions.hh"


using namespace MyOdeInt;

int main(){
    const double k  = 1. ;
    const double dt = 1.e-03;
    const double tmax = 1.e02;

    auto kepler_pot = [&] (std::array<double,2*NDIM> const& y){
        std::array<double,2*NDIM> dy ;
        auto const r = std::sqrt(y[X]*y[X] + y[Y]*y[Y]);
        dy[X] = y[VX];
        dy[Y] = y[VY];
        dy[VX] = -k*y[X]/(r*r*r);
        dy[VY] = -k*y[Y]/(r*r*r);
        return dy;
    };

    std::array<double,2*NDIM> const y_0{{3.0, 0.0, 0.0, .5}};
    const size_t nsteps = static_cast<size_t>(tmax/dt);

    auto y = y_0;
    std::ofstream f;
    f.open("euler.dat");
    f << "# t"<<"\t"<<"x"<<"\t"<<"y"<<"\t"<<"vx"<<"\t"<<"vy"<<std::endl;
    for(int iter=0; iter<=nsteps; iter++){
        EulerStep(y,kepler_pot,dt);
        f << iter * dt << "\t";
        for(auto const& x: y) f << x << "\t";
        f << std::endl ;
    }
    f.close();

    y = y_0;
    f.open("rk4.dat");
    for(int iter=0; iter<=nsteps; iter++){
        RK4Step(y,kepler_pot,dt);
        f << iter * dt << "\t";
        for(auto const& x: y) f << x << "\t";
        f << std::endl ;
    }
    f.close();
}