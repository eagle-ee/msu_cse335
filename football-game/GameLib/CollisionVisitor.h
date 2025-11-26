/**
 * @file CollisionVisitor.h
 * @author Brennan Eagle
 *
 * Collision Visitor
 */
 
#ifndef COLLISIONVISITOR_H
#define COLLISIONVISITOR_H

#include "Item.h"
#include "Wall.h"

class Enemy;
class ItemCoin10;
class ItemCoin100;
class PowerUp;
class Platform;
class GoalPost;
class Game;


/**
 * Handle collision
 */
class CollisionVisitor {
private:
    Game *mGame; ///<pointer to game
    bool mLastWasTerrain = false;  ///< was last collision w/ terrain?
    bool mShouldRemove = false; ///< remove an item from a list?
public:
    /**
     * Constructor
     * @param game pointer to the game
     */
    CollisionVisitor(Game* game) : mGame(game) {}

    ///visit a platform (terrain collision)
    void VisitPlatform(Platform* platform);

    ///visit a wall (terrain collision)
    void VisitWall(Wall* wall);

    ///visit coin 10 (collect and remove)
    void VisitCoin10(ItemCoin10* coin);
    ///visit coin 100
    void VisitCoin100(ItemCoin100* coin);

    ///visit an enemy (game over)
    void VisitEnemy(Enemy* enemy);

    ///visit a goal (level complete > load next)
    void VisitGoalPost(GoalPost* goal);

    ///visit the powerup
    void VisitPowerUp(PowerUp* powerup);

    /**
     * Check if the last collision was with terrain
     * @return True if last collision was terrain
     */
    bool HasTerrainCollision() const { return mLastWasTerrain; }

    /**
     * Check if the current item should be removed
     * @return True if item should be removed
     */
    bool ShouldRemoveItem() const { return mShouldRemove; }

};



#endif //COLLISIONVISITOR_H
