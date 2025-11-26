/**
 * @file JoeFactory.h
 * @author b3big
 *
 * Class that builds a character, Joe
 */
 
#ifndef JOEFACTORY_H
#define JOEFACTORY_H
#include "Actor.h"

/**
 * Factory that builds joe
 */
class JoeFactory {
private:

public:
     std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //JOEFACTORY_H
