/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.lslboost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_KEY_OF_IMPL_HPP

#include <lslboost/fusion/container/map/detail/value_of_impl.hpp>

namespace lslboost { namespace fusion { namespace extension
{
    template <typename>
    struct key_of_impl;

    template <>
    struct key_of_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                value_of_impl<map_iterator_tag>::
                    template apply<It>::type::first_type
            type;
        };
    };
}}}

#endif
