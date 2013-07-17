#ifndef BOOST_THREAD_THREAD_HPP
#define BOOST_THREAD_THREAD_HPP

//  thread.hpp
//
//  (C) Copyright 2007-8 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.lslboost.org/LICENSE_1_0.txt)

#include <lslboost/thread/detail/platform.hpp>

#if defined(BOOST_THREAD_PLATFORM_WIN32)
#include <lslboost/thread/win32/thread_data.hpp>
#elif defined(BOOST_THREAD_PLATFORM_PTHREAD)
#include <lslboost/thread/pthread/thread_data.hpp>
#else
#error "Boost threads unavailable on this platform"
#endif

#include <lslboost/thread/detail/thread.hpp>
#include <lslboost/thread/detail/thread_interruption.hpp>
#include <lslboost/thread/detail/thread_group.hpp>
#include <lslboost/thread/v2/thread.hpp>


#endif
