//
//  Legs.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "HandL.h"

void HandL::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

void HandL::drawFaces()
{
    BodyPart::drawFaces();
}


void HandL::drawWireframe()
{
    BodyPart::drawWireframe();
}

