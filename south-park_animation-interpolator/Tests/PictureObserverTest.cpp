/**
 * @file PictureObserverTest.cpp
 * @author Brennan Eagle
 */

#include <pch.h>

#include <Picture.h>
#include <gtest/gtest.h>
#include <PictureObserver.h>

class PictureObserverMock : public PictureObserver
{
public:
    bool mUpdated = false;
    PictureObserverMock() : PictureObserver() {}
    void UpdateObserver() override { mUpdated = true; }

};

TEST(PictureObserverTest, Construct) {
    PictureObserverMock observer;
}

TEST(PictureObserverTest, OneObserver) {
    // Allocate a Picture object
    auto picture = std::make_shared<Picture>();

    // Create a mock observer object
    PictureObserverMock observer;

    // And set it for the observer:
    observer.SetPicture(picture);

    picture->UpdateObservers();

    ASSERT_TRUE(observer.mUpdated);
}

TEST(PictureObserver, GetPicture)
{
    auto picture = std::make_shared<Picture>();
    PictureObserverMock observer;
    observer.SetPicture(picture);

    auto testPicture = observer.GetPicture();
    ASSERT_EQ(testPicture, picture);
}

TEST(PictureObserver, MultipleObservers)
{
    auto picture = std::make_shared<Picture>();
    PictureObserverMock observer;
    PictureObserverMock observer2;
    observer.SetPicture(picture);
    observer2.SetPicture(picture);

    //Test both update
    picture->UpdateObservers();
    ASSERT_TRUE(observer.mUpdated);
    ASSERT_TRUE(observer2.mUpdated);

    //Test one destroyed
    {
        PictureObserverMock observer3;
        observer3.SetPicture(picture);
    }


}