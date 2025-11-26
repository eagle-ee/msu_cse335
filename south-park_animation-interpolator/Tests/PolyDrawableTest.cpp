/**
 * @file PolyDrawableTest.cpp
 * @author Brennan Eagle
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <PolyDrawable.h>

#include <Actor.h>
#include <Picture.h>

using namespace std;

TEST(PolyDrawableTest, Constructor)
{
    PolyDrawable poly(L"Polygon");
    ASSERT_EQ(std::wstring(L"Polygon"), poly.GetName());
}

TEST(PolyDrawableTest, ColorDefault)
{
    PolyDrawable poly(L"Polygon");
    ASSERT_EQ(*wxBLACK, poly.GetColor());
}

TEST(PolyDrawableTest, ColorGetterSetter)
{
    PolyDrawable poly(L"Polygon");

    poly.SetColor(*wxRED);
    ASSERT_EQ(*wxRED, poly.GetColor());

    poly.SetColor(*wxGREEN);
    ASSERT_EQ(*wxGREEN, poly.GetColor());
}

/** This tests that the animation of the rotation of a drawable works */
TEST(PolyDrawableTest, Animation)
{
    // Create a picture object
    auto picture = std::make_shared<Picture>();

    // Create an actor and add it to the picture
    auto actor = std::make_shared<Actor>(L"Actor");

    // Create a drawable for the actor
    auto drawable = std::make_shared<PolyDrawable>(L"Drawable");
    actor->SetRoot(drawable);
    actor->AddDrawable(drawable);

    picture->AddActor(actor);

    auto channel = drawable->GetAngleChannel();

    // First we will ensure it works with no keyframes set
    picture->SetAnimationTime(0);
    drawable->SetRotation(1.33);

    // The channel should not be valid
    ASSERT_FALSE(channel->IsValid());

    // Getting a keyframe should not changle the angle
    actor->GetKeyframe();
    ASSERT_NEAR(1.33, drawable->GetRotation(), 0.00001);

    // Now we'll set one keyframe and see if that works
    picture->SetAnimationTime(1.5);
    drawable->SetRotation(2.7);
    actor->SetKeyframe();

    // Change angle
    drawable->SetRotation(0.3);
    ASSERT_NEAR(0.3, drawable->GetRotation(), 0.00001);

    // Wherever we move, now, the keyframe angle should be used
    picture->SetAnimationTime(0);
    ASSERT_NEAR(2.7, drawable->GetRotation(), 0.00001);

    drawable->SetRotation(0.3);
    picture->SetAnimationTime(1.5);
    ASSERT_NEAR(2.7, drawable->GetRotation(), 0.00001);

    drawable->SetRotation(0.3);
    picture->SetAnimationTime(3);
    ASSERT_NEAR(2.7, drawable->GetRotation(), 0.00001);

    // We'll set a second keyframe and see if that works
    picture->SetAnimationTime(3.0);
    drawable->SetRotation(-1.8);
    actor->SetKeyframe();

    // Test before the keyframes
    drawable->SetRotation(0.3);
    picture->SetAnimationTime(0);
    ASSERT_NEAR(2.7, drawable->GetRotation(), 0.00001);

    // Test at first keyframe
    drawable->SetRotation(0.3);
    picture->SetAnimationTime(1.5);
    ASSERT_NEAR(2.7, drawable->GetRotation(), 0.00001);

    // Test at second keyframe
    drawable->SetRotation(0.3);
    picture->SetAnimationTime(3.0);
    ASSERT_NEAR(-1.8, drawable->GetRotation(), 0.00001);

    // Test after second keyframe
    drawable->SetRotation(0.3);
    picture->SetAnimationTime(4);
    ASSERT_NEAR(-1.8, drawable->GetRotation(), 0.00001);

    // Test between the two keyframs
    drawable->SetRotation(0.3);
    // Halfway between the two keyframes
    picture->SetAnimationTime(2.25);
    ASSERT_NEAR((2.7 + -1.8) / 2,
            drawable->GetRotation(), 0.00001);

    drawable->SetRotation(0.3);
    // 1/3 between the two keyframes
    picture->SetAnimationTime(2.0);
    ASSERT_NEAR(2.7 + 1.0 / 3.0 * (-1.8 - 2.7),
            drawable->GetRotation(), 0.00001);
}