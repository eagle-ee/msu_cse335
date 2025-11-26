/**
 * @file PictureFactory.h
 * @author b3big
 *
 * A factory class that builds our picture.
 */
 
#ifndef PICTUREFACTORY_H
#define PICTUREFACTORY_H
#include <complex.h>

#include "Picture.h"

/**
 * Factory to create picture
 */
class PictureFactory {
private:

public:
    std::shared_ptr<Picture> Create(std::wstring imagesDir);
};



#endif //PICTUREFACTORY_H
