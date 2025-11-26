/**
 * @file PowerUp.h
 * @author Eduardo Jimenez
 *
 *
 */

#ifndef PROJECT1_POWERUP_H
#define PROJECT1_POWERUP_H
#include "Item.h"


class PowerUp : public Item
{
private:
    ///is powerup activated?
    bool mActivated = false;
    ///velocity
    double mVy = 0;
    ///g
    const double mGravity = 1000;

public:
    /// Default constructor (disabled)
    PowerUp() = delete;

    /// Copy constructor (disabled)
    PowerUp(const PowerUp &) = delete;

    /// Assignment operator
    void operator=(const PowerUp &) = delete;

    /// Constructor
    PowerUp(Game* game);

    /// Save PowerUp to XML
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void Accept(CollisionVisitor* visitor) override;
    void Update(double elapsed) override;
    bool TryActivate() { if (mActivated) return false; mActivated = true; return true; }
    bool ShouldRemove(const Game* game) const override;
};



#endif //PROJECT1_POWERUP_H