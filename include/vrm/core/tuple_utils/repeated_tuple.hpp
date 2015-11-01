// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <tuple>
#include <vrm/core/config.hpp>
#include <vrm/core/assert.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/tuple_utils/for.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename, std::size_t, typename>
        struct tuple_repeat_impl_helper;

        template <typename T, std::size_t TS, typename... Ts>
        struct tuple_repeat_impl_helper<T, TS, std::tuple<Ts...>>
        {
            using type = typename tuple_repeat_impl_helper<T, TS - 1,
                std::tuple<Ts..., T>>::type;
        };

        template <typename T, typename... Ts>
        struct tuple_repeat_impl_helper<T, 0, std::tuple<Ts...>>
        {
            using type = std::tuple<Ts...>;
        };

        template <typename T, std::size_t TS>
        struct tuple_repeat_impl
        {
            using type =
                typename tuple_repeat_impl_helper<T, TS, std::tuple<>>::type;
        };
    }

    /// @brief Type of a tuple with `T` repeated `TN` times.
    /// @code
    /// vrm::core::repeated_tuple<int, 5>
    /// // ...is equal to...
    /// std::tuple<int, int, int, int, int>
    /// @endcode
    template <std::size_t TN, typename T,
        typename TIdxs = std::index_sequence<TN>>
    using repeated_tuple = typename impl::tuple_repeat_impl<T, TN>::type;

    template <std::size_t TN, typename T>
    VRM_CORE_ALWAYS_INLINE auto make_repeated_tuple(const T& x = T{}) noexcept
    {
        auto result(repeated_tuple<TN, T>{});

        for_tuple(
            [&x](auto& elem)
            {
                elem = x;
            },
            result);

        return result;
    }
}
VRM_CORE_NAMESPACE_END