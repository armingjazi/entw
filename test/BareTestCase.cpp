#include <include/gmock/gmock.h>
#include <include/gtest/gtest.h>

#include <core/inc/Bare.h>

using namespace testing;

namespace entw
{
    TEST(UnitTest_Bare, bare)
    {
        Bare bare;

        bare.set(10);

        EXPECT_EQ(10, bare.get());
    }
}