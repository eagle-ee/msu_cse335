/**
 * @file Wall.cpp
 * @author Brennan Eagle
 */
 
#include "pch.h"
#include "Wall.h"
#include "CollisionVisitor.h"

/**
 * Constructor
 * @param game Game this wall is in
 * @param filename Image file for this wall
 */
Wall::Wall(Game* game, const std::wstring& filename) : Item(game, filename)
{
}

/**
 * Accept a collision visitor
 * @param visitor The collision visitor
 */
void Wall::Accept(CollisionVisitor* visitor)
{
    visitor->VisitWall(this);
}