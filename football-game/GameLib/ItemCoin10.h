/**
 * @file ItemCoin10.h
 * @author Brennan Eagle
 *
 *
 */
 
#ifndef ITEMCOIN_H
#define ITEMCOIN_H
#include "Item.h"

/**
 * Coin class (value 10)
 */
class ItemCoin10 : public Item {
private:

public:
    /// Default constructor (disabled)
    ItemCoin10() = delete;

    /// Copy constructor (disabled)
    ItemCoin10(const ItemCoin10 &) = delete;

    /// Assignment operator
    void operator=(const ItemCoin10 &) = delete;

    ItemCoin10(Game* game);
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void Accept(CollisionVisitor* visitor) override;
    void Update(double elapsed) override;
};



#endif //ITEMCOIN_H
