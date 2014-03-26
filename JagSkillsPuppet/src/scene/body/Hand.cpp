//
//  Legs.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Hand.h"

void Hand::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

void Hand::drawFaces()
{
    BodyPart::drawFaces();
}


void Hand::drawWireframe()
{
    BodyPart::drawWireframe();
}

