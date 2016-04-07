#include "../../utils/test_utils.hpp"
#include <vrm/core/config.hpp>
#include <vrm/core/tuple_utils/apply.hpp>

int main()
{
    auto t0 = std::make_tuple(0, 1, 2, 3);
    auto t1 = std::make_tuple(10.f, 25.0, 'b');
    auto t2 = std::make_tuple('a', 1, 3);

    auto first = [](auto&& x, auto&&...)
    {
        return x;
    };
    auto second = [](auto&&, auto&& x, auto&&...)
    {
        return x;
    };
    auto count = [](auto&&... xs)
    {
        // TODO: GCC: BUG: gcc complains about xs... not being used.
        [](auto&&... ys)
        {
            (void)std::forward_as_tuple(FWD(ys)...);
        }(FWD(xs)...);
        return sizeof...(xs);
    };

    using namespace vrm::core;

    TEST_ASSERT_OP(apply(first, t0), ==, 0);
    TEST_ASSERT_OP(apply(first, t1), ==, 10.f);
    TEST_ASSERT_OP(apply(first, t2), ==, 'a');

    TEST_ASSERT_OP(apply(second, t0), ==, 1);
    TEST_ASSERT_OP(apply(second, t1), ==, 25.0);
    TEST_ASSERT_OP(apply(second, t2), ==, 1);

    TEST_ASSERT_OP(apply(count, t0), ==, 4);
    TEST_ASSERT_OP(apply(count, t1), ==, 3);
    TEST_ASSERT_OP(apply(count, t2), ==, 3);

    TEST_ASSERT_OP(apply_all_sequential(first, t0, t1, t2), ==, 0);
    TEST_ASSERT_OP(apply_all_sequential(second, t0, t1, t2), ==, 1);
    TEST_ASSERT_OP(apply_all_sequential(count, t0, t1, t2), ==, 4 + 3 + 3);

    return 0;
}
