//
//  UpperArm.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "UpperArm.h"

void UpperArm::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
    
    // connection to legs
    connectingPoints.push_back(ofVec3f(0,0,0));
    connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
}


void UpperArm::drawFaces()
{
    BodyPart::drawFaces();
    BodyPart::formatConnections();
}



void UpperArm::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}

