/**
 * @file ItemCoin100.h
 * @author Brennan Eagle
 *
 *
 */
 
#ifndef ITEMCOIN100_H
#define ITEMCOIN100_H

#include "Item.h"

/**
 * Coin class (value 100)
 */
class ItemCoin100 : public Item {
private:

public:
    /// Default constructor (disabled)
    ItemCoin100() = delete;

    /// Copy constructor (disabled)
    ItemCoin100(const ItemCoin100 &) = delete;

    /// Assignment operator
    void operator=(const ItemCoin100 &) = delete;

    ItemCoin100(Game* game);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void Accept(CollisionVisitor* visitor) override;
    void Update(double elapsed) override;
};



#endif //ITEMCOIN100_H
