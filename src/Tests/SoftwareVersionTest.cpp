#include <gtest/gtest.h>
#include "../Version/SoftwareVersion.h"
//-----------------------------------------------
TEST(SoftwareVersionTest, Validity)
{
  EXPECT_GT(getSoftwareVersion(), 0);
}
//-----------------------------------------------
