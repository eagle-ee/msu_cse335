/**
 * @file Game.h
 * @author Saransh S
 *
 *
 */

#ifndef PROJECT1_GAME_H
#define PROJECT1_GAME_H
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <wx/dcbuffer.h>
#include "Football.h"
#include "Scoreboard.h"
#include "FloatingText.h"

class Item;
class wxGraphicsContext;
class wxXmlNode;
class FloatingText;

/**
 * @struct DeclarationInfo
 * @brief Holds information about a declared item from the XML file.
 *
 * This structure stores the type of the item (e.g., "background", "platform", "coin")
 * and a map of all its attributes as key-value pairs (e.g., image file, value, dimensions).
 *
 * It is used when parsing the <declarations> section of the XML to store reusable item
 * templates, which are later used to create actual items in the game.
 */
struct DeclarationInfo
{
    std::wstring type;
    std::map<std::wstring, std::wstring> attributes;
};

/**
 * Game class
 */
class Game
{
private:
    /// All the items in our game
    std::vector<std::shared_ptr<Item>> mItems;
    /// Floating texts for coin collection
    std::vector<std::unique_ptr<FloatingText>> mFloatingTexts;
    /// Scoreboard
    Scoreboard* mScoreboard;

    /// Scale of the display
    double mScale = 1.0;

    /// X offset for scrolling
    double mXOffset = 0;

    /// Y offset for scrolling
    double mYOffset = 0;

    /// Game area height in virtual pixels
    const static int Height = 1024;

    /// The player football
    std::shared_ptr<Football> mFootball;

    /// Current level
    int mLevel = 0;

    /// Starting x for this level
    double mStartX=0;
    /// Starting Y for this level
    double mStartY=0;

    /// Maps declaration IDs to their corresponding DeclarationInfo (parsed from XML)
    std::map<std::wstring, DeclarationInfo> mDeclarations;

    /// Cache of images
    std::map<std::wstring, std::shared_ptr<wxBitmap>> mImageCache;

    /// Pending reload flag
    bool mReloadPending = false;

    /// Coin value multiplier from power-ups
    int mCoinMultiplier = 1;
    ///StopWatch to track time
    wxStopWatch* mStopWatch = nullptr;

    std::wstring mMessage;      /// Message to display ("YOU LOSE")
    wxStopWatch mMessageTimer;  /// Stopwatch to time message duration

    std::wstring mLevelMessage;  /// Message to display for levels
public:
    Game();

    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);
    void Update(double elapsed);
    void Add(std::shared_ptr<Item> item);
    void AddFloatingText(const wxString& text, double x, double y, int points);
    void Remove(std::shared_ptr<Item>& item);
    void Load(const wxString &filename);
    void Save(const wxString &filename);
    void Clear();

    /// Load the specified level by number.
    void LoadLevel(int level);

    /// Parse the <declarations> section of the XML and store items information
    void XmlDeclarations(wxXmlNode* node);

    /// Parse the <items> section of the XML and creates items of file
    void XmlItems(wxXmlNode* itemsNode);

    /**
     * Get the height of the level
     * @return Level height in virtual pixels (always 1024)
     */
    int GetHeight() const { return Height; }

    /**
     * Get the game football
     * @return Game football
     */
    std::shared_ptr<Football> GetFootball() const { return mFootball; }

    /**
     * Get a cached image, loading it if necessary
     * @param filename image filename
     * @return shared pointer to cached bitmap
     */
    std::shared_ptr<wxBitmap> GetCachedImage(const std::wstring& filename);

    /**
     * Set the game's scoreboard
     * @param scoreboard to set
     */
    void SetScoreboard(Scoreboard *scoreboard)
    {
        mScoreboard = scoreboard;
    }

    /**
     * Get the scoreboard
     * @return scoreboard
     */
    Scoreboard *GetScoreboard() const { return mScoreboard; }

    void ReloadCurrentLevel();
    void LoadNextLevel();

    /**
     * Request reloading the current level
     */
    void RequestReload() { mReloadPending = true; }

    /**
     * Get current coin multiplier
     */
    int GetCoinMultiplier() const { return mCoinMultiplier; }

    /**
     * Double the coin multiplier
     */
    void DoubleCoinMultiplier() { mCoinMultiplier *= 2; }

    /**
     * Reset coin multiplier
     */
    void ResetCoinMultiplier() { mCoinMultiplier = 1; }

    /**
     * Count each item for tests
     */
    double CountItems();
    void StartLevel(int level);

    void SetStopWatch(wxStopWatch* stopWatch)
    {
        mStopWatch = stopWatch;
    }
    std::wstring GetMessage() const { return mMessage; }
    void ResetCurrentLevelState();
    void SetLevelMessage(const std::wstring& msg) { mLevelMessage = msg; }
    std::wstring GetLevelMessage() const { return mLevelMessage; }
    /**
     * Get the current level number
     * @return Current level number
     */
    int GetLevel() const { return mLevel; }

};


#endif //PROJECT1_GAME_H