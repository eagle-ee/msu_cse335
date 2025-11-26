/**
 * @file GoalPost.h
 * @author Eduardo Jimenez
 *
 *
 */

#ifndef PROJECT1_GOALPOST_H
#define PROJECT1_GOALPOST_H
#include "Item.h"


class GoalPost : public Item
{
private:

public:
    /// Default constructor (disabled)
    GoalPost() = delete;

    /// Copy constructor (disabled)
    GoalPost(const GoalPost &) = delete;

    /// Assignment operator
    void operator=(const GoalPost &) = delete;

    /// Constructor
    GoalPost(Game* game);

    /// Save GoalPost to XML
    wxXmlNode* XmlSave(wxXmlNode* node) override;

    void Accept(CollisionVisitor* visitor) override;
};


#endif //PROJECT1_GOALPOST_H