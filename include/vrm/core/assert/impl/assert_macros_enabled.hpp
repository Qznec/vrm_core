// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <cassert>
#include <vrm/pp/utils.hpp>
#include <vrm/pp/sep_to_str.hpp>
#include <vrm/core/utility_macros/likely_unlikely.hpp>

#define VRM_CORE_IMPL_ASSERT(lhs, op, rhs, msg)                                \
    do                                                                         \
    {                                                                          \
        if(VRM_CORE_LIKELY(lhs op rhs)) break;                                 \
                                                                               \
        auto lhs_res(lhs);                                                     \
        auto rhs_res(rhs);                                                     \
                                                                               \
        const char* code_str = VRM_PP_SEP_TOSTR(" ", lhs, op, rhs);            \
        const char* line_str = VRM_PP_TOSTR(__LINE__);                         \
        const char* file_str = VRM_PP_TOSTR(__FILE__);                         \
        const char* lhs_str = VRM_PP_TOSTR(lhs);                               \
        const char* op_str = VRM_PP_TOSTR(op);                                 \
        const char* rhs_str = VRM_PP_TOSTR(rhs);                               \
        const char* msg_str = msg;                                             \
                                                                               \
        ::vrm::core::impl::assert::fire(code_str, line_str, file_str, lhs_str, \
            op_str, rhs_str, msg_str, lhs_res, rhs_res);                       \
                                                                               \
    } while(false)

#define VRM_CORE_IMPL_CONSTEXPR_ASSERT(lhs, op, rhs, msg) \
    do                                                    \
    {                                                     \
        assert(lhs op rhs);                               \
                                                          \
    } while(false)
