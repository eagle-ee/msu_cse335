/**
 * @file Enemy.h
 * @author Eduardo Jimenez & Saransh S
 *
 */

#ifndef PROJECT1_ENEMY_H
#define PROJECT1_ENEMY_H
#include "Item.h"


class Enemy : public Item
{
private:
    /// Bottom Y position from which the enemy moves
    double mBaseY = 0;
    /// Time accumulator used to compute motion phase
    double mTime = 0;
    /// If the bottom position has been captured from initial position
    bool mHasBase = false;
    /// Distance to move upward from the bottom position in pixels
    double mAmplitude = 300;
    /// Time to move from bottom position to top in seconds
    double mHalfPeriod = 1.25;

public:
    /// Default constructor disabled
    Enemy() = delete;

    /// Copy constructor disabled
    Enemy(const Enemy&) = delete;

    /// Assignment operator disabled
    void operator=(const Enemy&) = delete;

    /// Constructor
    Enemy(Game* game, const std::wstring& filename);

    /// Save enemy to XML
    wxXmlNode* XmlSave(wxXmlNode* node) override;

    /// Update logic for enemy movement
    void Update(double elapsed) override;
    void Accept(CollisionVisitor* visitor) override;
};


#endif //PROJECT1_ENEMY_H