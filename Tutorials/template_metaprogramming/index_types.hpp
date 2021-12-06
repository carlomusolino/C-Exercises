#pragma once

#include<type_traits>
#include <stddef.h>


namespace FourVectors {

    // index types
    struct upper_t;
    struct lower_t;
    struct none_t;
    
    template<typename T>
    struct is_upper_t : std::false_type {};
    template<> struct is_upper_t<upper_t> : std::true_type {};
    template<typename T>
    struct is_lower_t : std::false_type {};
    template<> struct is_lower_t<lower_t> : std::true_type {};

    template<typename index_t_, size_t ndim>
    struct general_property_t {
        using index_t = index_t_;
        static constexpr size_t ndim_t = ndim; 
    };

    template<typename E1, typename E2>
    struct arithmetic_expression_property_t {
        static_assert(std::is_same<typename E1::property_t::index_t,typename E2::property_t::index_t>::value, "Indices don't match!");
        using index_t = typename E1::property_t::index_t;
        static constexpr size_t ndim_t = E1::property_t::ndim_t;
    };

    template<typename E1, typename E2>
    struct contraction_expression_property_t {
        static constexpr bool is_compatible = !(std::is_same<typename E1::property_t::index_t, typename E2::property_t::index_t>::value) ;
        static_assert(is_compatible, "Error! Unsuitable index structure for contraction!"    );
        using index_t = none_t;
        static constexpr size_t ndim_t = E1::property_t::ndim_t;
    };
    /*
    enum index_type {upper=0,lower=1};

    template<index_type I>
    using index_type = std::integral_type<index_type,I>;
    template<index_type I>
    using index_type_t = typedef index_type<I>::type;
    template<>
    inline static constexpr struct index_type_v : index_type<I>::value {};

    template<>
    using upper_type = index_type<upper>;
    template<>
    using upper_type_t = typedef upper_type::type;
    template<>
    inline static constexpr struct upper_type_v : upper_type::value {};

    template<>
    using lower_type = index_type<lower>;
    template<>
    using lower_type_t = typedef lower_type::type;
    template<>
    inline static struct lower_type_v : lower_type::value {};

    template<typename T>
    static constexpr struct is_index_t : std::false_type {};
    template<>
    static constexpr struct is_index_t<index_type> : std::true_type {};

    template<typename T>
    static constexpr struct is_upper_t : std::false_type {};
    template<>
    static constexpr struct is_upper_t<upper_type_t> : std::true_type {};

    template<typename T>
    static constexpr struct is_lower_t : std::false_type {};
    template<>
    static constexpr struct is_lower_t<lower_type_t> : std::true_type {};

    */


}