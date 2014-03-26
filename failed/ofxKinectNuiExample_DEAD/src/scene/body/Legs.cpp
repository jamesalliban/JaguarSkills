//
//  Legs.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Legs.h"

void Legs::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

void Legs::drawFaces()
{
    BodyPart::drawFaces();
}



void Legs::drawWireframe()
{
    BodyPart::drawWireframe();
}


