/**
 * @file Game.cpp
 * @author Saransh S and Eduardo Jimenez
 */

#include "pch.h"
#include "Game.h"

#include "Enemy.h"
#include "Football.h"
#include "GoalPost.h"
#include "Item.h"
#include "ItemCoin10.h"
#include "ItemCoin100.h"
#include "PowerUp.h"
#include "Background.h"
#include "CollisionVisitor.h"
#include "MovingPlatform.h"
#include "Platform.h"
#include "FloatingText.h"

using namespace std;

/// Level 0's xml file
const wstring Level0File = L"levels/level0.xml";

/// Level 1's xml file
const wstring Level1File = L"levels/level1.xml";

/// Level 2's xml file
const wstring Level2File = L"levels/level2.xml";

/// Level 3's xml file
const wstring Level3File = L"levels/level3.xml";

const vector<wstring> Levels = {Level0File,Level1File,Level2File,Level3File};
/**
 * Constructor
 */
Game::Game()
{
    mFootball = std::make_shared<Football>(this);
    Add(mFootball);
    LoadLevel(1);
    //mFootball->SetLocation(450,200);
}

/**
 * Draw the game area
 * @param gc The graphics context to draw on
 * @param width The width of the client window
 * @param height The height of the client window
 */
void Game::OnDraw(shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Automatic Scaling
    //
    mScale = double(height) / double(Height);
    graphics->Scale(mScale, mScale);

    auto virtualWidth = (double)width / mScale;
    graphics->PushState();

    //
    // Draw in virtual pixels on the graphics context
    //

    for (auto item : mItems)
    {
        item->Draw(graphics, mXOffset);
    }

    for (auto& text : mFloatingTexts)
    {
        text->Draw(graphics, mXOffset);
    }

    graphics->PopState();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update in seconds
 */
void Game::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->UpdatePrev();
    }

    for (auto item : mItems)
    {
        item->Update(elapsed);
    }
    mScoreboard->Update(elapsed);

    if (mFootball)
    {
        bool hasTerrainCollision = false;
        CollisionVisitor visitor(this);
        std::vector<std::shared_ptr<Item>> itemsToRemove;  // Collect items to remove

        for (auto& item : mItems)
        {
            if (item.get() == mFootball.get())
            {
                continue;
            }

            if (mFootball->CollisionTest(item.get()))
            {
                // Use visitor to handle collision
                item->Accept(&visitor);

                // Check if this was a terrain collision for grounding
                if (visitor.HasTerrainCollision())
                {
                    hasTerrainCollision = true;
                    mFootball->CollisionResolve(item.get());
                }

                // Check if this item should be removed
                if (visitor.ShouldRemoveItem())
                {
                    itemsToRemove.push_back(item);
                }
            }
        }

        // Now safely remove items after iteration
        for (auto& item : itemsToRemove)
        {
            Remove(item);
        }

        // Remove any items that should be removed after update
        std::vector<std::shared_ptr<Item>> itemsAutoRemove;
        for (auto& item : mItems)
        {
            if (item->ShouldRemove(this))
            {
                itemsAutoRemove.push_back(item);
            }
        }
        for (auto& item : itemsAutoRemove)
        {
            Remove(item);
        }

        // Update floating texts
        for (auto& text : mFloatingTexts)
        {
            text->Update(elapsed);
        }

        // Remove expired texts
        mFloatingTexts.erase(
            std::remove_if(mFloatingTexts.begin(), mFloatingTexts.end(),
                [](const auto& text) {
                    return text->IsExpired();
                }),
            mFloatingTexts.end()
        );

        // Update grounded state
        if (!hasTerrainCollision)
        {
            mFootball->SetGrounded(false);
            mFootball->SetStandingOn(nullptr);
        }

        const double screenBottom = 1000; // screen height
        const double footballY = mFootball->GetY();
        if (footballY <= 0 || footballY >= screenBottom)
        {
            ReloadCurrentLevel();
            return;
        }

        const double worldCenter = 500;
        mXOffset = mFootball->GetX()-worldCenter;
    }
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add Floating Text when coin is collected
 * @param text Text to display
 * @param x location
 * @param y location
 * @param points to display
 */
void Game::AddFloatingText(const wxString& text, double x, double y, int points)
{
    mFloatingTexts.push_back(
        std::make_unique<FloatingText>(text, x, y, points)
    );
}

/**
 * Remove item from game
 * @param item to remove
 */
void Game::Remove(std::shared_ptr<Item>& item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if(loc != end(mItems))
    {
        mItems.erase(loc);
    }
}

/**
 * Load the game from a .xml file.
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(const wxString& filename)
{
    Clear();
    // Reset power-up state when loading or restarting a level
    ResetCoinMultiplier();

    wxXmlDocument doc;
    if (!doc.Load(filename))
    {
        return;
    }

    auto root = doc.GetRoot();
    if (root->GetName() != L"level")
    {
        return;
    }

    // Parse start position - football starting position
    double startX, startY;
    root->GetAttribute(L"start-x", L"0").ToDouble(&startX);
    root->GetAttribute(L"start-y", L"0").ToDouble(&startY);
    
    // Position football at start
    if (mFootball)
    {
        mFootball->SetLocation(startX, startY);
    }

    // Process items section
    auto child = root->GetChildren();
    while (child)
    {
        if (child->GetName() == L"declarations")
        {
            XmlDeclarations(child);
        }
        else if (child->GetName() == L"items")
        {
            XmlItems(child);
        }
        child = child->GetNext();
    }
}

/**
 * Save the game as a .xml file.
 *
 * Open an XML file and stream the game data to it.
 *
 * @param filename The filename of the file to save the game to
 */
void Game::Save(const wxString &filename)
{
    // This will be filled in with XML saving logic
}

/**
 * Clear the game data.
 *
 * Deletes all known items in the game.
 */
void Game::Clear()
{
    // Remove football temporarily
    auto loc = find(begin(mItems), end(mItems), mFootball);
    if (loc != end(mItems))
    {
        mItems.erase(loc);
    }
    
    // Clear all other items
    mItems.clear();
    
    // Clear image cache for new level
    mImageCache.clear();

    // Reset coin multiplier when level cleared
    ResetCoinMultiplier();

    // Re-add football
    if (mFootball)
    {
        Add(mFootball);
    }
}

/**
 * Load the game from a .xml file.
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param level The level to load the game from.
 */
void Game::LoadLevel(int level)
{
    Clear();
    if (Levels.empty())
    {
        wxMessageBox(L"No levels defined!");
        return;
    }

    mLevel = level % Levels.size();
    const std::wstring filename = Levels[mLevel];
    // Set the on-screen message
    SetLevelMessage(L"Level " + std::to_wstring(mLevel ));

    wxTimer* timer = new wxTimer();
    timer->Bind(wxEVT_TIMER, [this, level, timer](wxTimerEvent&) {
        mLevelMessage.clear(); // remove the message
        delete timer;
    });
    timer->StartOnce(2000); // 2000 ms = 2 seconds

    wxXmlDocument doc;
    if (!doc.Load(filename))
    {
        wxMessageBox(L"Cannot load level file: " + filename);
        return;
    }

    Clear();

    auto root = doc.GetRoot();
    if (!root || root->GetName() != L"level")
    {
        wxMessageBox(L"Invalid level file format");
        return;
    }

    root->GetAttribute(L"start-x",L"0").ToDouble(&mStartX);
    root->GetAttribute(L"start-y",L"0").ToDouble(&mStartY);

    /// Load declarations first
    for (auto node = root->GetChildren(); node; node = node->GetNext())
    {
        if (node->GetName() == L"declarations")
            XmlDeclarations(node);

    }

    /// Load items
    for (auto node = root->GetChildren(); node; node = node->GetNext())
    {
        if (node->GetName() == L"items")
            XmlItems(node);
    }
    Add(mFootball);

    // Reset football to starting position
    mFootball->SetLocation(mStartX,mStartY);
    mFootball->UpdatePrev();
    mFootball->SetXVelocity(0);
    mFootball->SetYVelocity(0);
    mFootball->SetGrounded(false);
    mFootball->SetStandingOn(nullptr);

    //wxLogStatus(L"Level " + std::to_wstring(level) + L" loaded!");
    wxLogStatus(wxString::Format("Level %d loaded!", level));
}


/**
 * Handle an XML node of type Declarations.
 * @param node XML node
 */
void Game::XmlDeclarations(wxXmlNode* node)
{
    for (auto child = node->GetChildren(); child; child = child->GetNext())
    {
        DeclarationInfo info;
        info.type = child->GetName().ToStdWstring();

        /// Store all attributes
        for (auto attr = child->GetAttributes(); attr; attr = attr->GetNext())
        {
            info.attributes[attr->GetName().ToStdWstring()] = attr->GetValue().ToStdWstring();
        }

        std::wstring id = child->GetAttribute(L"id", L"").ToStdWstring();
        if (!id.empty())
            mDeclarations[id] = info;
    }

}

/**
 * Handle an XML node of type items.
 * @param node XML node
 */
void Game::XmlItems(wxXmlNode* itemsNode)
{
    for (auto child = itemsNode->GetChildren(); child; child = child->GetNext())
    {
        std::wstring id = child->GetAttribute(L"id", L"").ToStdWstring();
        auto it = mDeclarations.find(id);
        if (it == mDeclarations.end())
            continue;

        const auto& decl = it->second;
        std::wstring type = decl.type;

        double x = wxAtof(child->GetAttribute(L"x", L"0"));
        double y = wxAtof(child->GetAttribute(L"y", L"0"));
        double width = wxAtof(child->GetAttribute(L"width", L"0"));
        double height = wxAtof(child->GetAttribute(L"height", L"0"));

        /// Handle different item types
        if (type == L"background")
        {
            std::wstring imageFile = L"images/" + decl.attributes.at(L"image");
            auto item = std::make_shared<Background>(this, imageFile);
            item->SetLocation(x, y);
            Add(item);
        }
        else if (type == L"platform")
        {
            std::wstring leftImg  = L"images/" + decl.attributes.at(L"left-image");
            std::wstring midImg   = L"images/" + decl.attributes.at(L"mid-image");
            std::wstring rightImg = L"images/" + decl.attributes.at(L"right-image");

            auto img = GetCachedImage(midImg);

            int imgPixelWidth = img->GetWidth();

            int segmentWidth = imgPixelWidth;
            int numMid = int((width - 2 * segmentWidth) / segmentWidth);

            int adjustedWidth = (numMid+2)*segmentWidth;

            // Left
            auto left = std::make_shared<Platform>(this, leftImg);
            left->SetLocation(x - adjustedWidth / 2 + segmentWidth / 2, y);
            Add(left);



            // Middle segments
            for (int i = 0; i < numMid; i++)
            {
                auto mid = std::make_shared<Platform>(this, midImg);
                mid->SetLocation(x - adjustedWidth / 2 + segmentWidth + i * segmentWidth + segmentWidth / 2, y);
                Add(mid);
            }



            // Right
            auto right = std::make_shared<Platform>(this, rightImg);
            right->SetLocation(x + adjustedWidth / 2 - segmentWidth / 2, y);
            Add(right);
        }
        else if (type == L"movingplatform")
        {
            std::wstring leftImg  = L"images/" + decl.attributes.at(L"left-image");
            std::wstring midImg   = L"images/" + decl.attributes.at(L"mid-image");
            std::wstring rightImg = L"images/" + decl.attributes.at(L"right-image");

            double cx = wxAtof(child->GetAttribute(L"cx", std::to_wstring(x)));
            double cy = wxAtof(child->GetAttribute(L"cy", std::to_wstring(y)));
            double radius = wxAtof(child->GetAttribute(L"radius", L"0"));
            double omega = wxAtof(child->GetAttribute(L"omega", L"0"));
            int segmentWidth = 32;

            if (width > 0)
            {
                int numMid = int((width - 2 * segmentWidth) / segmentWidth);

                // Left
                auto left = std::make_shared<MovingPlatform>(this, leftImg);
                double leftOffsetX = -width / 2 + segmentWidth / 2;
                left->SetLocation(cx + leftOffsetX, cy);
                left->SetMotion(cx + leftOffsetX, cy, radius, omega);
                Add(left);

                // Middle segments
                for (int i = 0; i < numMid; i++)
                {
                    auto mid = std::make_shared<MovingPlatform>(this, midImg);
                    double midOffsetX = -width / 2 + segmentWidth + i * segmentWidth + segmentWidth / 2;
                    mid->SetLocation(cx + midOffsetX, cy);
                    mid->SetMotion(cx + midOffsetX, cy, radius, omega);
                    Add(mid);
                }

                // Right
                auto right = std::make_shared<MovingPlatform>(this, rightImg);
                double rightOffsetX = width / 2 - segmentWidth / 2;
                right->SetLocation(cx + rightOffsetX, cy);
                right->SetMotion(cx + rightOffsetX, cy, radius, omega);
                Add(right);
            }
            else
            {
                //single
                auto movingPlatform = std::make_shared<MovingPlatform>(this, midImg);
                movingPlatform->SetLocation(cx, cy);
                movingPlatform->SetMotion(cx, cy, radius, omega);
                Add(movingPlatform);
            }
        }
        else if (type == L"wall")
        {
            auto itImage = decl.attributes.find(L"image");
            if (itImage == decl.attributes.end())
            {
                wxLogError(L"Wall declaration missing image attribute for id %s", id);
                continue;
            }

            std::wstring imageFile = L"images/" + itImage->second;
            int segmentHeight = 32;

            //multi segment
            if (height > 0)
            {
                int numSegments = int(height / segmentHeight);

                for (int i = 0; i < numSegments; i++)
                {
                    auto wall = std::make_shared<Wall>(this, imageFile);
                    wall->SetLocation(x, y - height / 2 + i * segmentHeight + segmentHeight / 2);
                    Add(wall);
                }
            }
            else
            {
                //single
                auto wall = std::make_shared<Wall>(this, imageFile);
                wall->SetLocation(x, y);
                Add(wall);
            }
        }
        else if (type == L"coin")
        {
            /// the "value" attribute defines which coin type to create
            int value = wxAtoi(decl.attributes.at(L"value"));

            if (value == 10)
            {
                auto coin = std::make_shared<ItemCoin10>(this);
                coin->SetLocation(x, y);
                Add(coin);
            }
            if (value == 100)
            {
                auto coin = std::make_shared<ItemCoin100>(this);
                coin->SetLocation(x, y);
                Add(coin);
            }
        }
        else if (type == L"power-up")
        {
            auto powerUp = std::make_shared<PowerUp>(this);
            powerUp->SetLocation(x, y);
            //powerUp->SetLocation(512, 384); // roughly middle if your screen is 1024x768
            Add(powerUp);
        }
        else if (type == L"enemy")
        {
            /**
            // Manually create enemies to test
            auto enemy1 = std::make_shared<Enemy>(this, L"images/U-M.png");
            enemy1->SetLocation(300, 384); // left side of screen
            Add(enemy1);

            auto enemy2 = std::make_shared<Enemy>(this, L"images/ND.png");
            enemy2->SetLocation(724, 384); // right side of screen
            Add(enemy2);

            ***/
            auto itImage = decl.attributes.find(L"image");
            if (itImage == decl.attributes.end())
            {
                continue;
            }
            std::wstring imageFile = L"images/" + itImage->second;
            auto enemy = std::make_shared<Enemy>(this, imageFile);
            enemy->SetLocation(x,y);
            Add(enemy);
        }
        else if (type == L"goalpost")
        {
            auto goalpost = std::make_shared<GoalPost>(this);
            //powerUp->SetLocation(512, 384); // roughly middle if your screen is 1024x768
            goalpost->SetLocation(x, y);
            Add(goalpost);
        }
    }
}

/**
 * Reload current level
 */
void Game::ReloadCurrentLevel()
{
    // Show "YOU LOSE" message
    mMessage = L"YOU LOSE!";
    mMessageTimer.Start();

    // Pause stopwatch
    mStopWatch->Pause();

    // Schedule reset after delay
    wxTimerEvent dummy;
    wxTimer *timer = new wxTimer();
    timer->Bind(wxEVT_TIMER, [this, timer](wxTimerEvent&) {
        ResetCurrentLevelState();
        mStopWatch->Start();
        mMessage.clear(); // Remove message
        delete timer;
    });
    timer->StartOnce(2000); // wait 2 seconds
}

/**
 * Load next level
 */
void Game::LoadNextLevel()
{
    if(mLevel < 3)
    {
        mLevel = mLevel + 1;
    }

    // Power-up works only at the current level
    ResetCoinMultiplier();
    LoadLevel(mLevel);
    
    // Reset score for the new level
    if (mScoreboard)
    {
        mScoreboard->Reset();
    }
}

/**
  * Get a cached image, loading it if necessary
  * @param filename image filename
  * @return Shared pointer to cached bitmap
  */
std::shared_ptr<wxBitmap> Game::GetCachedImage(const std::wstring& filename)
{
    // Check if already cached
    auto it = mImageCache.find(filename);
    if (it != mImageCache.end())
    {
         // Return cached image
        return it->second;
    }
    
    // If not cached, load it
    auto image = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    auto bitmap = std::make_shared<wxBitmap>(*image);
    
    // Cache it
    mImageCache[filename] = bitmap;
    
    return bitmap;
}

/**
 * Resets the current level state without reloading the level.
 */
void Game::ResetCurrentLevelState()
{
    // Clear or reset anything related to level state

    mStopWatch->Pause();
    mFootball->SetLocation(mStartX, mStartY);
    mFootball->UpdatePrev();
    mFootball->SetXVelocity(0);
    mFootball->SetYVelocity(0);
    mFootball->SetGrounded(false);
    mFootball->SetStandingOn(nullptr);
    mXOffset = 0;
    mYOffset = 0;

    if (mScoreboard)
    {
        mScoreboard->Reset();
    }

    ResetCoinMultiplier();
}


/**
 * Count each item for tests
 */
double Game::CountItems()
{
    double count = 0;
    for (auto i : mItems)
    {
        count++;
    }
    return count;
}

