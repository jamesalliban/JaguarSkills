//
//  Head.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Head.h"

void Head::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
}

void Head::drawFaces()
{
    BodyPart::drawFaces();
}


void Head::drawWireframe()
{
	BodyPart::drawWireframe();
}

