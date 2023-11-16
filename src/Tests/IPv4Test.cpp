#include <gtest/gtest.h>
#include "IPv4.h"
//-----------------------------------------------
TEST(IPv4Test, FillIPv4FromString)
{
  {
    IPv4 ip;
    ASSERT_TRUE(ip.fill("192.168.0.100"));
    EXPECT_EQ(ip._addr[0], 192);
    EXPECT_EQ(ip._addr[1], 168);
    EXPECT_EQ(ip._addr[2], 0);
    EXPECT_EQ(ip._addr[3], 100);
  }
  {
    IPv4 ip;
    ASSERT_TRUE(ip.fill("0.0.0.0"));
    EXPECT_EQ(ip._addr[0], 0);
    EXPECT_EQ(ip._addr[1], 0);
    EXPECT_EQ(ip._addr[2], 0);
    EXPECT_EQ(ip._addr[3], 0);
  }
  {
    IPv4 ip;
    ASSERT_TRUE(ip.fill("0.0.0.0"));
    EXPECT_EQ(ip._addr[0], 0);
    EXPECT_EQ(ip._addr[1], 0);
    EXPECT_EQ(ip._addr[2], 0);
    EXPECT_EQ(ip._addr[3], 0);
  }
  {
    IPv4 ip;
    ASSERT_FALSE(ip.fill("-1.168.0.100"));
  }
  {
    IPv4 ip;
    ASSERT_FALSE(ip.fill("192.168.256.100"));
  }
  {
    IPv4 ip;
    ASSERT_FALSE(ip.fill("192.168.0"));
  }
  {
    IPv4 ip;
    ASSERT_FALSE(ip.fill(""));
  }
}
//-----------------------------------------------
TEST(IPv4Test, SortInReverseLexicographical)
{
  VecIPv4 ips(10);
  ips[0].fill("1.1.1.1");
  ips[1].fill("2.20.1.1");
  ips[2].fill("2.2.2.1");
  ips[3].fill("3.2.1.1");
  ips[4].fill("4.3.12.1");
  ips[5].fill("4.3.3.2");
  ips[6].fill("8.3.3.3");
  ips[7].fill("8.5.3.3");
  ips[8].fill("10.10.4.3");
  ips[9].fill("10.5.4.4");

  VecIPv4 expect(10);
  expect[0].fill("10.10.4.3");
  expect[1].fill("10.5.4.4");
  expect[2].fill("8.5.3.3");
  expect[3].fill("8.3.3.3");
  expect[4].fill("4.3.12.1");
  expect[5].fill("4.3.3.2");
  expect[6].fill("3.2.1.1");
  expect[7].fill("2.20.1.1");
  expect[8].fill("2.2.2.1");
  expect[9].fill("1.1.1.1");

  sort(ips);
  EXPECT_EQ(expect, ips);
}
//-----------------------------------------------
TEST(IPv4Test, StrictFilter)
{
  VecIPv4 ips(10);
  ips[0].fill("1.1.1.1");
  ips[1].fill("2.2.1.1");
  ips[2].fill("2.2.2.1");
  ips[3].fill("3.2.1.1");
  ips[4].fill("3.3.2.1");
  ips[5].fill("3.3.3.2");
  ips[6].fill("4.3.3.3");
  ips[7].fill("4.4.3.3");
  ips[8].fill("4.4.4.3");
  ips[9].fill("4.4.4.4");

  VecIPv4 expected{ips[1], ips[2], ips[3]};
  EXPECT_EQ(expected, getFilteredStrict(ips, {-1, 2, -1, -1}));

  expected = {ips[6], ips[7], ips[8]};
  EXPECT_EQ(expected, getFilteredStrict(ips, {4, -1, -1, 3}));

  expected = {ips[8], ips[9]};
  EXPECT_EQ(expected, getFilteredStrict(ips, {4, 4, 4, -1}));
}
//-----------------------------------------------
TEST(IPv4Test, AnyFilter)
{
  VecIPv4 ips(10);
  ips[0].fill("1.1.1.1");
  ips[1].fill("2.2.1.1");
  ips[2].fill("2.2.2.1");
  ips[3].fill("3.2.1.1");
  ips[4].fill("3.3.2.1");
  ips[5].fill("3.3.3.2");
  ips[6].fill("4.3.3.3");
  ips[7].fill("4.4.3.3");
  ips[8].fill("4.4.4.3");
  ips[9].fill("4.4.4.4");

  VecIPv4 expected{ips[1], ips[2], ips[3]};
  EXPECT_EQ(expected, getFilteredAny(ips, {-1, 2, -1, -1}));

  expected = {ips[0], ips[1], ips[2], ips[3], ips[4], ips[6], ips[7], ips[8], ips[9]};
  EXPECT_EQ(expected, getFilteredAny(ips, {4, -1, -1, 1}));

  EXPECT_EQ(ips, getFilteredAny(ips, {4, 3, 2, 1}));
}
//-----------------------------------------------
