/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.lslboost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED)
#if !defined(BOOST_PP_IS_ITERATING)

#include <lslboost/preprocessor/cat.hpp>
#include <lslboost/preprocessor/iteration/iterate.hpp>
#include <lslboost/preprocessor/repetition/enum_params.hpp>
#include <lslboost/preprocessor/repetition/enum_binary_params.hpp>
#include <lslboost/preprocessor/facilities/intercept.hpp>

#include <lslboost/utility/result_of.hpp>

#include <lslboost/config.hpp>

#include <lslboost/fusion/container/vector/vector.hpp>

#include <lslboost/fusion/functional/adapter/limits.hpp>
#include <lslboost/fusion/functional/adapter/detail/access.hpp>

#if defined (BOOST_MSVC)
#  pragma warning(push)
#  pragma warning (disable: 4512) // assignment operator could not be generated.
#endif

namespace lslboost { namespace fusion
{
    template <class Function, bool AllowNullary = true>
    class unfused;

    //----- ---- --- -- - -  -   -

    template <class Function> 
    class unfused<Function,true>
      : public unfused<Function,false>
    {
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        using unfused<Function,false>::operator();

        inline explicit unfused(func_const_fwd_t f = function())
            : unfused<Function,false>(f)
        { }

        typedef typename lslboost::result_of<
            function_c(fusion::vector0<> &) >::type call_const_0_result;

        inline call_const_0_result operator()() const
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }

        typedef typename lslboost::result_of< 
            function(fusion::vector0<> &) >::type call_0_result;

        inline call_0_result operator()() 
        {
            fusion::vector0<> arg;
            return this->fnc_transformed(arg);
        }
    };

    template <class Function> class unfused<Function,false>
    {
      protected:
        Function fnc_transformed;
        typedef typename detail::qf_c<Function>::type function_c;
        typedef typename detail::qf<Function>::type function;
        typedef typename detail::call_param<Function>::type func_const_fwd_t;
      public:

        inline explicit unfused(func_const_fwd_t f = function())
            : fnc_transformed(f)
        { }

        template <typename Sig>
        struct result;

        #define  BOOST_PP_FILENAME_1 \
            <lslboost/fusion/functional/adapter/unfused.hpp>
        #define  BOOST_PP_ITERATION_LIMITS \
            (1,BOOST_FUSION_UNFUSED_MAX_ARITY)
        #include BOOST_PP_ITERATE()
    };
}}

#if defined (BOOST_MSVC)
#  pragma warning(pop)
#endif

namespace lslboost 
{
    template<class F>
    struct result_of< lslboost::fusion::unfused<F> const () >
    {
        typedef typename lslboost::fusion::unfused<F>::call_const_0_result type;
    };
    template<class F>
    struct result_of< lslboost::fusion::unfused<F>() >
    {
        typedef typename lslboost::fusion::unfused<F>::call_0_result type;
    };
}

#define BOOST_FUSION_FUNCTIONAL_ADAPTER_UNFUSED_HPP_INCLUDED
#else // defined(BOOST_PP_IS_ITERATING)
////////////////////////////////////////////////////////////////////////////////
//
//  Preprocessor vertical repetition code
//
////////////////////////////////////////////////////////////////////////////////
#define N BOOST_PP_ITERATION()

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self const (BOOST_PP_ENUM_PARAMS(N,T)) >
            : lslboost::result_of< function_c(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <class Self, BOOST_PP_ENUM_PARAMS(N,typename T)>
        struct result< Self(BOOST_PP_ENUM_PARAMS(N,T)) >
            : lslboost::result_of< function(
                BOOST_PP_CAT(fusion::vector,N)< BOOST_PP_ENUM_BINARY_PARAMS(N,
                    typename detail::mref<T,>::type BOOST_PP_INTERCEPT) > & )>
        { };

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        inline typename lslboost::result_of<function_c(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) const
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }

        template <BOOST_PP_ENUM_PARAMS(N,typename T)>
        inline typename lslboost::result_of<function(BOOST_PP_CAT(fusion::vector,N)
            <BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT)> & )>::type
        operator()(BOOST_PP_ENUM_BINARY_PARAMS(N,T,& a)) 
        {
            BOOST_PP_CAT(fusion::vector,N)<
                  BOOST_PP_ENUM_BINARY_PARAMS(N,T,& BOOST_PP_INTERCEPT) >
                arg(BOOST_PP_ENUM_PARAMS(N,a));
            return this->fnc_transformed(arg);
        }
#undef N
#endif // defined(BOOST_PP_IS_ITERATING)
#endif

