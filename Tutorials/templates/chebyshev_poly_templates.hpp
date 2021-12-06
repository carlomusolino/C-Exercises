/**
 * @file template_examples.hpp
 * @author Carlo Musolino <musolino@itp.uni-frankfurt.de>
 * Just some examples of templated functions
 */
#ifndef __MY_CHEBYSHEV_HPP__
#define __MY_CHEBYSHEV_HPP__

#include "omp.h"

namespace TemplatedChebyshev{
   /**
   * An example of template specialization
   */ 
    template <unsigned int N> 
    inline auto Tn(const double& x)
    {
        return ( (2.*x*Tn<N-1>(x)) - Tn<N-2>(x)  );
    }
    // full or complete specialization of the template parameters: we define our base cases for the recursion
    template <> inline auto Tn<0>(const double& x)
    {
        return 1.;
    }

    template <> inline auto Tn<1>(const double& x)
    {
        return x; 
    }

    // for reference, let us define the same but without templates:
    template <class T> 
    inline auto Tn_notemp(const T& x, const unsigned int N){
        switch (N){
            case 0:
                return static_cast<T>(1.);
            
            case 1:
                return x; 
            default:
                return ( (static_cast<T>(2.)*x*Tn_notemp<T>(x,N-1)) - Tn_notemp<T>(x,N-2)  );
        }
    }

}
#endif