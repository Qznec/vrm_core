// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/type_traits.hpp>
#include <vrm/core/ostream_utils.hpp>
#include <vrm/core/type_traits/common.hpp>
#include <vrm/core/type_traits/qualifiers.hpp>
#include <vrm/core/ostream_utils/nullptr_printer.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename TDerived, typename TBase, typename TOut,
            typename TPtr>
        VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) polymorphic_cast(
            TPtr&& ptr) noexcept
        {
            VRM_CORE_STATIC_ASSERT_NM(is_same_or_derived_of<TDerived, TBase>{});
            VRM_CORE_ASSERT_OP(ptr, !=, nullptr);

            return static_cast<TOut>(ptr);
        }
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase * base) noexcept
    {
        return impl::polymorphic_cast<TDerived, TBase, // .
            copy_cv_qualifiers<TDerived, TBase>*>(base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived * derived) noexcept
    {
        return impl::polymorphic_cast<TDerived, TBase, // .
            copy_cv_qualifiers<TBase, TDerived>*>(derived);
    }

    template <typename TDerived, typename TBase>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_derived(
        TBase && base) noexcept
    {
        return *to_derived<TDerived>(&base);
    }

    template <typename TBase, typename TDerived>
    VRM_CORE_ALWAYS_INLINE constexpr decltype(auto) to_base(
        TDerived && derived) noexcept
    {
        return *to_base<TBase>(&derived);
    }
}
VRM_CORE_NAMESPACE_END
