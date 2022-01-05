#pragma once
#include<array>
#include<tuple>
#include<algorithm>
#include<stdlib.h>
namespace MyOdeInt{

    template<typename F, size_t N>
    static inline void EulerStep(std::array<double,N> &y, F const & func, double const dt){
        std::array<double,N> dy = func(y);
        for(int i=0; i<N; i++) y[i] += dt*dy[i] ;
    }

    template<typename F, size_t N>
    static void RK4Step(std::array<double,N> &y, F const & f, double const dt){
        std::array<double,4> b{{1./6.,1./3.,1./3.,1./6.}};
        std::array<double,N> k1,k2,k3,k4,tmp ;
        k1 = f(y); 
        for(int i=0; i<N; i++) tmp[i] = y[i] + 0.5 * dt * k1[i];
        k2 = f(tmp);
        for(int i=0; i<N; i++) tmp[i] = y[i] + 0.5 * dt * k2[i];
        k3 = f(tmp);
        for(int i=0; i<N; i++) tmp[i] = y[i] + dt * k3[i];
        k4 = f(tmp);
        auto kappas = std::tie(k1,k2,k3,k4);
        for(int i=0; i<N; i++){
            y[i] += dt * ( b[0] * k1[i] + b[1] * k2[i] + b[2] * k3[i] + b[3] * k4[i] );        
        }
    }

    template<typename F, size_t N>
    static inline void LeapFrog(std::array<double,N> &y, std::array<double,2*N> const& y_old, F const & func, double const dt){
        std::array<double,N> dy = f(y);
        for(int i=0; i<N; i++) y[i] = y_old[i] + 2*dt*dy[i] ;
    }
}