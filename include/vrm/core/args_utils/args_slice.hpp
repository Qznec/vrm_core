// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vrm/core/config.hpp>
#include <vrm/core/args_utils/nth_arg.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <std::size_t TIBegin, std::size_t... TIdxs, typename... Ts>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) build_args_slice(
            std::index_sequence<TIdxs...>, Ts&&... xs) noexcept
        {
            return make_ref_tpl(FWD(nth_arg<TIBegin + TIdxs>(FWD(xs)...))...);
        }
    }

    template <std::size_t TIBegin, std::size_t TIEnd, typename... Ts>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) args_slice(
        Ts && ... xs) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(TIEnd >= TIBegin);
        VRM_CORE_STATIC_ASSERT_NM(sizeof...(xs) >= TIEnd - TIBegin);

        return impl::build_args_slice<TIBegin>(
            std::make_index_sequence<TIEnd - TIBegin>(), FWD(xs)...);
    }
}
VRM_CORE_NAMESPACE_END