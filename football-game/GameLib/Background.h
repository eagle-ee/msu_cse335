/**
 * @file Background.h
 *
 * @author Michael Dreon
 */

#ifndef PROJECT1_BACKGROUND_H
#define PROJECT1_BACKGROUND_H
#include "Item.h"

/**
 * Background class
 */
class Background : public Item
{
private:

public:
    /// Default constructor (disabled)
    Background() = delete;

    /// Copy constructor (disabled)
    Background(const Background &) = delete;

    /// Assignment operator
    void operator=(const Background &) = delete;

    Background(Game* game, const std::wstring& filename);
    wxXmlNode* XmlSave(wxXmlNode* node) override;

    bool IsCollidable() override { return false; }
};


#endif //PROJECT1_BACKGROUND_H