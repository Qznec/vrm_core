// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/assert.hpp>
#include <vrm/core/experimental/handle.hpp>
#include <vrm/core/experimental/delegate/base_delegate.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/strong_typedef.hpp>

// TODO: WIP:
// * use sparse int set?

// TODO:
// Strong handle typedefs for index/target

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <template <typename...> class TFunction, typename TSignature,
            typename TAllocator>
        class VRM_CORE_CLASS_API dynamic_delegate
            : public impl::base_delegate<TFunction, TSignature, TAllocator>
        {
        private:
            using handle_index_type = sz_t;
            using handle_counter_type = std::int8_t;

            using handle_settings_type =
                handle::settings<handle_index_type, handle_counter_type>;

            using handle_storage_type =
                handle::storage::hs_vector<handle_settings_type, TAllocator>;

            using handle_manager_type = handle::manager<handle_storage_type>;

            using metadata_type = typename handle_manager_type::metadata_type;
            using handle_type = typename handle_manager_type::handle_type;

            using base_type =
                impl::base_delegate<TFunction, TSignature, TAllocator>;

            handle_manager_type _hm;

            auto next_fn_idx() const noexcept;

        public:
            using fn_type = typename base_type::fn_type;

            dynamic_delegate() = default;

            dynamic_delegate(const dynamic_delegate&) = default;
            dynamic_delegate& operator=(const dynamic_delegate&) = default;

            dynamic_delegate(dynamic_delegate&&) = default;
            dynamic_delegate& operator=(dynamic_delegate&&) = default;

            template <typename TF>
            auto operator+=(TF&& f);

            void operator-=(const handle_type& h);
        };
    }

    template <typename TSignature,
        typename TAllocator =
            impl::default_delegate_allocator<std::function, TSignature>>
    using dynamic_delegate =
        impl::dynamic_delegate<std::function, TSignature, TAllocator>;
}
VRM_CORE_NAMESPACE_END
