//
//  UpperArmL.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "UpperArmL.h"

void UpperArmL::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
    
	isUseOfMesh = true;

    // connection to legs
    connectingPoints.push_back(ofVec3f(0,0,0));
    connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
}


void UpperArmL::drawFaces()
{
    BodyPart::drawFaces();
    BodyPart::formatConnections();
}



void UpperArmL::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}

