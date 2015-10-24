#include "../../utils/test_utils.hpp"
#include <vrm/core/resizable_buffer.hpp>

#include <cassert>
#include <cstddef>
#include <functional>
#include <new>
#include <utility>


volatile int cc = 0;
volatile int dd = 0;
volatile int copies = 0;

struct item
{
    int l;
    item() { ++cc; }

    item(const item&) { ++copies; }
    item(item&&) = delete;

    item& operator=(const item&)
    {
        ++copies;
        return *this;
    }

    ~item() { ++dd; }
};



void run_test()
{
    using namespace vrm::core;
    auto all_null = [](const auto& dt)
    {
        bool result{true};

        for_tuple(
            [&result](const auto& p)
            {
                if(p != nullptr) result = false;
            },
            dt);

        return result;
    };

    cc = dd = copies = 0;

    multi_resizable_buffer<resizable_buffer<item>, resizable_buffer<item>,
        resizable_buffer<int>, resizable_buffer<std::string>> rb;

    TEST_ASSERT(all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 20);

    rb.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 60);
}

void run_test2()
{
    using namespace vrm::core;
    auto all_null = [](const auto& dt)
    {
        bool result{true};

        for_tuple(
            [&result](const auto& p)
            {
                if(p != nullptr) result = false;
            },
            dt);

        return result;
    };

    cc = dd = copies = 0;

    multi_resizable_buffer<resizable_buffer<item>, resizable_buffer<item>,
        resizable_buffer<int>, resizable_buffer<std::string>> rb;

    TEST_ASSERT(all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 20);

    auto rb2(std::move(rb));

    TEST_ASSERT(!all_null(rb2.data()));
    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 20);

    rb2.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 60);
}

void run_test3()
{
    using namespace vrm::core;
    auto all_null = [](const auto& dt)
    {
        bool result{true};

        for_tuple(
            [&result](const auto& p)
            {
                if(p != nullptr) result = false;
            },
            dt);

        return result;
    };

    cc = dd = copies = 0;

    multi_resizable_buffer<resizable_buffer<item>, resizable_buffer<item>,
        resizable_buffer<int>, resizable_buffer<std::string>> rb;

    TEST_ASSERT(all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 0);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(0, 10);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 20);
    TEST_ASSERT_OP(copies, ==, 0);
    TEST_ASSERT_OP(dd, ==, 0);

    rb.grow_and_construct(10, 20);

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 20);
    TEST_ASSERT_OP(dd, ==, 20);

    auto rb2(rb.copy(20));

    TEST_ASSERT(!all_null(rb.data()));
    TEST_ASSERT(!all_null(rb2.data()));
    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 60);
    TEST_ASSERT_OP(dd, ==, 20);

    rb.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 60);
    TEST_ASSERT_OP(dd, ==, 60);

    rb2.destroy_and_deallocate(20);

    TEST_ASSERT_OP(cc, ==, 40);
    TEST_ASSERT_OP(copies, ==, 60);
    TEST_ASSERT_OP(dd, ==, 100);
}

int main()
{
    using namespace vrm::core;

    run_test();
    run_test2();
    run_test3();

    return 0;
}