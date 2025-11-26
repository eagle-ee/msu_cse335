/**
 * @file AnimChannelAngleTest.cpp
 * @author b3big
 */
#include <pch.h>
#include "gtest/gtest.h"

#include <AnimChannelAngle.h>

TEST(AnimChannelAngleTest, Name)
{
    AnimChannelAngle channel;
    channel.SetName(L"Test Channel");
    ASSERT_EQ(std::wstring(L"Test Channel"), channel.GetName());
}