// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/pp.hpp>
#include <vrm/core/config.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/tuple_utils/apply.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>
#include <vrm/core/args_utils/args_slice.hpp>
#include <vrm/core/args_utils/args_slice_aliases.hpp>

// TODO: macro, add other aliases.

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER(name, fn)           \
    template <sz_t TN>                                              \
    struct name                                                     \
    {                                                               \
        template <typename... Ts>                                   \
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) operator()( \
            Ts && ... xs) noexcept                                  \
        {                                                           \
            return fn<TN>(FWD(xs)...);                              \
        }                                                           \
    };

#define VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(fn) \
    VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER(VRM_PP_CAT(fn, _wrapper), fn)

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TFArgGetter, typename TF, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto)        // .
            args_call_wrapper(TFArgGetter, TF&& f, Ts&&... xs) // .
            VRM_CORE_IMPL_NOEXCEPT_AND_RETURN_BODY_VA(         // .
                apply(f, TFArgGetter{}(FWD(xs)...))            //.
                )
    }

    namespace impl
    {
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(first_n_args)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(last_n_args)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_from)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_after)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_until)
        VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN(all_args_before)
    }
}
VRM_CORE_NAMESPACE_END

#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER_SN
#undef VRM_CORE_IMPL_DEFINE_ARGS_SLICE_WRAPPER
