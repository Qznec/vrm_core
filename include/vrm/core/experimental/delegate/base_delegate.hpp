// Copyright (c) 2015-2016 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// http://vittorioromeo.info | vittorio.romeo@outlook.com

#pragma once

#include <vector>
#include <functional>
#include <vrm/core/config.hpp>
#include <vrm/core/utility_macros/fwd.hpp>
#include <vrm/core/type_aliases/numerical.hpp>
#include <vrm/core/experimental/delegate/signature_helper.hpp>

VRM_CORE_NAMESPACE
{
    namespace impl
    {
        template <template <typename...> class TFunction, typename TSignature>
        class VRM_CORE_CLASS_API base_delegate
        {
        protected:
            using fn_signature = TSignature;

        private:
            using this_type = base_delegate<TFunction, fn_signature>;

        public:
            using fn_type = TFunction<fn_signature>;
            using fn_return_type = signature_return_type<TSignature>;

        protected:
            std::vector<fn_type> _functions;

            template <typename TF>
            void emplace_function(TF&& f)
            {
                _functions.emplace_back(FWD(f));
            }

            template <typename TSelf, typename TF, typename... Ts>
            static void call_and_use_result_impl                // .
                (TSelf&& self, TF&& result_handler, Ts&&... xs) // .
                noexcept(
                    noexcept(result_handler(self._functions.back()(xs...))))
            {
                for(auto&& f : self._functions) result_handler(f(xs...));
            }

            template <typename TSelf, typename... Ts>
            static void call_impl(TSelf&& self, Ts&&... xs) // .
                noexcept(noexcept(self._functions.back()(xs...)))
            {
                for(auto&& f : self._functions) f(xs...);
            }

            template <typename TSelf, typename... Ts>
            static auto call_and_return_vector_impl(TSelf&& self, Ts&&... xs)
            {
                std::vector<fn_return_type> result;
                result.reserve(self._functions.size());

                call_and_use_result_impl(FWD(self),
                    [&result](auto&& x)
                    {
                        result.emplace_back(FWD(x));
                    },
                    FWD(xs)...);

                return result;
            }

        public:
#define VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(qualifier)            \
    template <typename TF, typename... Ts>                                  \
    auto call_and_use_result(TF&& result_handler, Ts&&... xs)               \
        qualifier noexcept(noexcept(call_and_use_result_impl(               \
            this_type{}, result_handler, FWD(xs)...)))                      \
    {                                                                       \
        return call_and_use_result_impl(*this, result_handler, FWD(xs)...); \
    }                                                                       \
                                                                            \
    template <typename... Ts>                                               \
    auto operator()(Ts && ... xs)                                           \
        qualifier noexcept(noexcept(call_impl(this_type{}, FWD(xs)...)))    \
    {                                                                       \
        return call_impl(*this, FWD(xs)...);                                \
    }                                                                       \
                                                                            \
    template <typename... Ts>                                               \
    auto call_and_return_vector(Ts&&... xs) qualifier noexcept(             \
        noexcept(call_and_return_vector_impl(this_type{}, FWD(xs)...)))     \
    {                                                                       \
        return call_and_return_vector_impl(*this, FWD(xs)...);              \
    }

            VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&)
            VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(const&)
            VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS(&&)

#undef VRM_CORE_IMPL_DEFINE_DELEGATE_IMPLEMENTATIONS

            void reserve(sz_t x) { _functions.reserve(x); }
            void clear() noexcept { _functions.clear(); }
            auto empty() const noexcept { return _functions.empty(); }
        };
    }
}
VRM_CORE_NAMESPACE_END
