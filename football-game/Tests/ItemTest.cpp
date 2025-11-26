/**
 * @file ItemTest.cpp
 * @author Brennan Eagle
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Item.h>
#include <Game.h>

/// Coin filename
const std::wstring coin10Image = L"images/coin10.png";

/** Mock class for testing the class Item */
class ItemMock : public Item {
public:
    ItemMock(Game *game) : Item(game, coin10Image) {}

    void Draw(wxDC *dc) {}
    void Update(double elapsed) override { SetLocation(GetX() + elapsed, GetY() + elapsed); }

};

TEST(ItemTest, Construct)
{
    Game game;
    ItemMock item(&game);
}

TEST(ItemTest, GetterSetters)
{
    Game game;
    ItemMock item(&game);

    //Test initial
    ASSERT_NEAR(0, item.GetX(), 0.0001);
    ASSERT_NEAR(0, item.GetY(), 0.0001);

    // Test SetLocation, GetX, and GetY
    item.SetLocation(10.5, 17.2);
    ASSERT_NEAR(10.5, item.GetX(), 0.0001);
    ASSERT_NEAR(17.2, item.GetY(), 0.0001);

    // Test a second with different values
    item.SetLocation(-72, -107);
    ASSERT_NEAR(-72, item.GetX(), 0.0001);
    ASSERT_NEAR(-107, item.GetY(), 0.0001);
}

TEST(ItemTest, Update)
{
    Game game;
    ItemMock coin(&game);
    coin.SetLocation(10, 20);

    coin.Update(5);  // Move 5 pixels on x and y
    ASSERT_NEAR(15, coin.GetX(), 0.0001);
    ASSERT_NEAR(25, coin.GetY(), 0.0001);
}

TEST(ItemTest, HitTest)
{
    Game game;
    ItemMock coin(&game);

    coin.SetLocation(100, 200);

    ASSERT_TRUE(coin.HitTest(100, 200));
    ASSERT_FALSE(coin.HitTest(300, 200));
    ASSERT_FALSE(coin.HitTest(100, 400));

}


TEST(ItemTest, UpdatePrev)
{
    Game game;
    ItemMock item(&game);

    item.SetLocation(10, 20);
    item.UpdatePrev();

    ASSERT_NEAR(10, item.GetPrevX(), 0.0001);
    ASSERT_NEAR(20, item.GetPrevY(), 0.0001);

    // Move again — ensure previous values stay the same until UpdatePrev() is called again
    item.SetLocation(50, 60);
    ASSERT_NEAR(10, item.GetPrevX(), 0.0001);
    ASSERT_NEAR(20, item.GetPrevY(), 0.0001);

    item.UpdatePrev();
    ASSERT_NEAR(50, item.GetPrevX(), 0.0001);
    ASSERT_NEAR(60, item.GetPrevY(), 0.0001);
}