/**
 * @file DrawableTest.cpp
 * @author Brennan Eagle
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <Drawable.h>

/**
 * Mock class for testing Drawable
 */
class DrawableMock : public Drawable {
public:
    DrawableMock(const std::wstring &name) : Drawable(name) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override {}
    virtual bool HitTest(wxPoint pos) override { return false; }
};

TEST(DrawableTest, Constructor)
{
    DrawableMock drawable(L"Test Drawable");
    ASSERT_EQ(std::wstring(L"Test Drawable"), drawable.GetName());
}

TEST(DrawableTest, PositionDefault)
{
    DrawableMock drawable(L"Test Drawable");
    ASSERT_EQ(wxPoint(0, 0), drawable.GetPosition());
}

TEST(DrawableTest, PositionGetterSetter)
{
    DrawableMock drawable(L"Test Drawable");

    drawable.SetPosition(wxPoint(100, 200));
    ASSERT_EQ(wxPoint(100, 200), drawable.GetPosition());

    drawable.SetPosition(wxPoint(50, 75));
    ASSERT_EQ(wxPoint(50, 75), drawable.GetPosition());
}

TEST(DrawableTest, RotationDefault)
{
    DrawableMock drawable(L"Test Drawable");
    ASSERT_DOUBLE_EQ(0, drawable.GetRotation());
}

TEST(DrawableTest, RotationGetterSetter)
{
    DrawableMock drawable(L"Test Drawable");

    drawable.SetRotation(1.5);
    ASSERT_DOUBLE_EQ(1.5, drawable.GetRotation());

    drawable.SetRotation(3.14159);
    ASSERT_DOUBLE_EQ(3.14159, drawable.GetRotation());
}