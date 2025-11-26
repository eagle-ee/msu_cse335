/**
 * @file Platform.cpp
 * @author Brennan Eagle
 */

#include "pch.h"
#include "Platform.h"
#include "CollisionVisitor.h"

/**
 * Constructor
 * @param game Game this platform is in
 * @param filename Image file for this platform segment
 */
Platform::Platform(Game* game, const std::wstring& filename) : Item(game, filename)
{
}

/**
 * Accept a collision visitor
 * @param visitor The collision visitor
 */
void Platform::Accept(CollisionVisitor* visitor)
{
    visitor->VisitPlatform(this);
}