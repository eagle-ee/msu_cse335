/**
 * @file Wall.h
 * @author Brennan Eagle
 *
 *
 */
 
#ifndef WALL_H
#define WALL_H

#include "Item.h"

class CollisionVisitor;

/**
 * Wall class
 */
class Wall : public Item
{
public:
    /// Default constructor (disabled)
    Wall() = delete;

    /// Copy constructor (disabled)
    Wall(const Wall &) = delete;

    /// Assignment operator
    void operator=(const Wall &) = delete;

    Wall(Game* game, const std::wstring& filename);

    void Accept(CollisionVisitor* visitor) override;
};

#endif //WALL_H
