//
//  Legs.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "HandR.h"

void HandR::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

void HandR::drawFaces()
{
    BodyPart::drawFaces();
}


void HandR::drawWireframe()
{
    BodyPart::drawWireframe();
}

