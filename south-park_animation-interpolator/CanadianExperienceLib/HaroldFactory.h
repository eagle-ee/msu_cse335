/**
 * @file HaroldFactory.h
 * @author b3big
 *
 *
 */
 
#ifndef HAROLDFACTORY_H
#define HAROLDFACTORY_H
#include <complex.h>

#include "Actor.h"


/**
 * Factory class that builds the Harold character
 */
class HaroldFactory {
private:

public:
    std::shared_ptr<Actor> Create(std::wstring imagesDir);
};



#endif //HAROLDFACTORY_H
