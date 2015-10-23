// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <type_traits>
#include <vrm/core/internal.hpp>
#include <vrm/core/assert.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T, typename TStorage>
        using valid_storage = std::integral_constant<bool,
            sizeof(typename TStorage::type) >= sizeof(T) &&
                alignof(typename TStorage::type) >= alignof(T)>;
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `T&`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr T& from_storage(
        TStorage & storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(impl::valid_storage<T, TStorage>{});
        return reinterpret_cast<T&>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `T*`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr T* from_storage(
        TStorage * storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(impl::valid_storage<T, TStorage>{});
        return reinterpret_cast<T*>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `const T&`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr const T& from_storage(
        const TStorage& storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(impl::valid_storage<T, TStorage>{});
        return reinterpret_cast<const T&>(storage);
    }

    /// @brief Wrapper around `reinterpret_cast`, intended for use with aligned
    /// storages. Returns a `const T*`.
    template <typename T, typename TStorage>
    VRM_CORE_ALWAYS_INLINE constexpr const T* from_storage(
        const TStorage* storage) noexcept
    {
        VRM_CORE_STATIC_ASSERT_NM(impl::valid_storage<T, TStorage>{});
        return reinterpret_cast<const T*>(storage);
    }
}
VRM_CORE_NAMESPACE_END