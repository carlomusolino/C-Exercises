#include<fstream>
#include<stdlib.h>
#include<cmath>
#include<iostream>
#include <iomanip>
// Let's measure some performance 
#include <chrono>
#include "odeint.hpp"
#include "odeint_conventions.hh"

#define NOEULER

using namespace MyOdeInt;

int main(){
  // Time measuring shenanigans 
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  // Set output precision
  std::cout << std::setprecision(5);
  std::ofstream f;
  f << std::setprecision(6); 
  // --------------------------------------
  const double k  = 1. ;
  const double dt = 1.e-02;
  const double tmax = 2.3e03;
  
  // Define ODE Right Hand Side
  auto const kepler_pot = [&] (std::array<double,2*NDIM> const& y){
    std::array<double,2*NDIM> dy ;
    auto const r = std::sqrt(y[X]*y[X] + y[Y]*y[Y]);
    dy[X] = y[VX];
    dy[Y] = y[VY];
    dy[VX] = -k*y[X]/(r*r*r);
    dy[VY] = -k*y[Y]/(r*r*r);
    return dy;
  };
  
  // And the energy function
  auto const kepler_energy = [&] (std::array<double,2*NDIM> const &y){
    auto const r = std::sqrt(y[X]*y[X] + y[Y]*y[Y]);
    auto const v = std::sqrt(y[VX]*y[VX] + y[VY]*y[VY]);
    return ( 0.5*v*v - k/r ); 
  };
  
  // Initial data, number of steps
  std::array<double,2*NDIM> const y_0{{3.0, 0.0, 0.0, .5}};
  const size_t nsteps = static_cast<size_t>(tmax/dt);

  // set up the evolved array
  auto y = y_0;
#ifndef NOEULER
  // Output file
  f.open("euler.dat");
  auto t1_eul = high_resolution_clock::now();
  // header
  f << "# t"<<"\t"<<"x"<<"\t"<<"y"<<"\t"<<"vx"<<"\t"<<"vy"<<"\t"<<"E"<<std::endl;
  // evolution loop
  for(int iter=0; iter<=nsteps; iter++){
    EulerStep(y,kepler_pot,dt);
    f << iter * dt << "\t";
    for(auto const& x: y) f << x << "\t";
    f << kepler_energy(y) << std::endl ;
  }// <-- end of for loop
  auto t2_eul = high_resolution_clock::now();
  f.close();
#endif
  
  y = y_0;
  f.open("rk4.dat");
  auto t1_rk4 = high_resolution_clock::now();
  // header
  f << "# t"<<"\t"<<"x"<<"\t"<<"y"<<"\t"<<"vx"<<"\t"<<"vy"<<"\t"<<"E"<<std::endl;
  // evolution loop
  for(int iter=0; iter<=nsteps; iter++){
    RK4Step(y,kepler_pot,dt);
    f << iter * dt << "\t";
    for(auto const& x: y) f << x << "\t";
    f << kepler_energy(y) << std::endl ;
  }// <-- end of for loop
  auto t2_rk4 = high_resolution_clock::now();
  f.close();
  
  auto y_1 = y_0;
  y = y_0 ;
  // Initialise the leapfrog staggered state
  EulerStep(y_1,kepler_pot,dt/2);
  f.open("leapfrog.dat");
  auto t1_lf = high_resolution_clock::now();
  // header
  f << "# t"<<"\t"<<"x"<<"\t"<<"y"<<"\t"<<"vx"<<"\t"<<"vy"<<"\t"<<"E"<<std::endl;
  for(int iter=0; iter<=nsteps; iter++){
    LeapFrogStep(y,y_1,kepler_pot,dt);
    f << iter * dt << "\t";
    for(auto const& x: y) f << x << "\t";
    f << kepler_energy(y) << std::endl ;
  }// <-- end of for loop
  auto t2_lf = high_resolution_clock::now();
  f.close();
  
  #ifndef NOEULER
  duration<double, std::milli> t_eul = t2_eul - t1_eul;
  #endif
  duration<double, std::milli> t_rk4 = t2_rk4 - t1_rk4;
  duration<double, std::milli> t_lf  = t2_lf  - t1_lf;

  std::cout << "All done, here are some performance metrics: "  << std::endl;
  std::cout << std::endl ;
  std::cout << "Number of steps: " << std::scientific << nsteps << std::endl;
  std::cout << std::fixed;
  std::cout << std::endl;
  #ifndef NOEULER
  std::cout << "Euler took:    "   << t_eul.count() << " ms"    << std::endl;
  #endif
  std::cout << "RK4 took:      "   << t_rk4.count() << " ms"    << std::endl;
  std::cout << "Leapfrog took: "   << t_lf.count()  << " ms"    << std::endl;
  std::cout << std::endl;
}
