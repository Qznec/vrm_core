// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <iosfwd>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros.hpp>
#include <vrm/core/type_aliases.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <typename T>
        VRM_CORE_CLASS_API class ignore_manipulator
        {
        private:
            T _str;

        public:
            ignore_manipulator() = default;

            template <typename TStr>
            ignore_manipulator(TStr&& str);


            template <typename TStr>
            auto& operator=(TStr&& str);

            operator const T&() const noexcept;

            auto begin() const noexcept;
            auto end() const noexcept;
        };

        template <typename>
        struct is_ignore_manipulator : std::false_type
        {
        };

        template <typename T>
        struct is_ignore_manipulator<ignore_manipulator<T>> : std::true_type
        {
        };
    }

    template <typename T>
    auto make_ignore_manipulator(T && x);

    template <typename T>
    auto operator<<(std::ostream & o, const T& im)
        ->std::enable_if_t<impl::is_ignore_manipulator<T>{}, std::ostream&>;
}
VRM_CORE_NAMESPACE_END
