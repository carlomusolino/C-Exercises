#pragma once
#include "index_types.hpp"

#include <vector>
#include <array>
#include <type_traits>
#include <stddef.h>
#include<iostream>

namespace FourVectors{
    static constexpr const size_t NDIM = 4;

    template <typename E>
    class VecExpression {
        public:
        // this is how we force the explicit evaluation of the vector expression! Not optimal
        // but good enough and I don't think we should make it more complicated than needed! 
        inline decltype(auto) operator[](size_t i) const {
            return static_cast<E const&>(*this)[i];
        }
        inline decltype(auto) eval() const {
            return static_cast<E const&>(*this).eval() ;
        }
        inline size_t size(){
            return static_cast<E const&>(*this).size();
        }
    };

    template<typename T, typename index_t_, size_t ndim = NDIM>
    class Vect: public VecExpression<Vect<T,index_t_,ndim>> {
        public:
        using index_t = index_t_;
        using property_t = general_property_t<index_t_,ndim>;
        protected:
        std::array<T,ndim> val;
        public:
        template<typename E>
        Vect(VecExpression<E> const& vec_expr ) {
            static_assert(std::is_same<index_t,typename E::property_t::index_t>::value, "Indices don't match!");
            for(int i=0; i<ndim; i++) val[i] = vec_expr[i]; //notice we use the access operator here --> We are evaluating the VecExpression on the RHS
        }

        Vect(std::initializer_list<T> const& _v){
            for(int i=0;i<ndim;i++) val[i] = _v.begin()[i];
        };
        
        inline decltype(auto) eval() const { return 1; } ;
        inline T operator[](size_t i) const {
            return val[i];
        }
        inline size_t size() const {
            return val.size();
        }
    };

    template <typename T, size_t ndim=NDIM>
    class Scalar: public VecExpression<Scalar<T,ndim>> {
        public:
        using index_t = none_t;
        using property_t = general_property_t<none_t,ndim>;
        private:
        T val_;
        public:
        template<typename E>
        Scalar(VecExpression<E> const &v) {
            static_assert(std::is_same<index_t,typename E::property_t::index_t>::value,"Error! Cannot initialize a scalar with a vector!");
            val_ = v.eval();
        }
        Scalar(T const& x): val_(x) {} ;
        inline decltype(auto) val() const { return val_; };
    };

    template<typename E1, typename E2>
    class VectSum: public VecExpression<VectSum<E1,E2>> {
        public:
        using property_t = arithmetic_expression_property_t<E1,E2>;
        protected:
        E1 _u;
        E2 _v;
        public:
        VectSum(E1 const& u,E2 const& v ): _v(v), _u(u) {
            static_assert(std::is_same<typename E1::property_t::index_t,typename E2::property_t::index_t>::value, "Indices don't match!");
        } 

        inline decltype(auto) operator[] (const size_t i) const {
            return _u[i] + _v[i] ;
        }

    };
    template <typename E1, typename E2>
    VectSum<E1,E2> operator+(VecExpression<E1> const& u, VecExpression<E2> const& v) {
        return VectSum<E1,E2>(*static_cast<const E1*>(&u), *static_cast<const E2*>(&v)) ;
    }
    
    template<typename E1, typename E2>
    class VectContraction: public VecExpression<VectContraction<E1,E2>> {
        public:
        using property_t = contraction_expression_property_t<E1,E2>;
        protected:
        E1 _u;
        E2 _v;
        public:
        VectContraction(E1 const& u,E2 const& v ): _v(v), _u(u) { }; 

        inline decltype(auto) eval() const { // because we chose to evaluate with the access operator we get this ugly function...
            decltype(_u[0]) tmp = static_cast<decltype(_u[0])>(0.) ;
            for( int k = 0; k < property_t::ndim_t; k++) tmp += _u[k] * _v[k] ; 
            return tmp;
        }
    };

    }