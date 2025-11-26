/**
 * @file Platform.h
 * @author Brennan Eagle
 *
 * Platform class
 */
 
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Item.h"

class CollisionVisitor;

class Platform : public Item {
public:
    /// Default constructor (disabled)
    Platform() = delete;

    /// Copy constructor (disabled)
    Platform(const Platform &) = delete;

    /// Assignment operator
    void operator=(const Platform &) = delete;

    /**
     * Constructor
     * @param game Game this platform is in
     * @param filename Image file for this platform segment
     */
    Platform(Game* game, const std::wstring& filename);

    /**
     * Accept a collision visitor
     * @param visitor The collision visitor
     */
    void Accept(CollisionVisitor* visitor) override;

};



#endif //PLATFORM_H
