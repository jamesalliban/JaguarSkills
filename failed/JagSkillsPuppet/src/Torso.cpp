//
//  Torso.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Torso.h"

void Torso::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
    
    model.loadModel(modelPath, true);
    
    // 3 connections for torso - L and R upper arms and abdomen
    for (int i = 0; i < 4; i++)
    {
        connectingPoints.push_back(ofVec3f(0,0,0));
        connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
    }
}



void Torso::drawFaces()
{
    BodyPart::drawFaces();
    formatConnections();
}



void Torso::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}


void Torso::formatConnections()
{
    // set connection points. These are used to position the axes of the child body parts
    for (int i = 0; i < connectingPointsAbsolute.size(); i++)
    {
        // rotate and position the absolute connection ponts
        connectingPointsAbsolute[i] = connectingPoints[i];
        connectingPointsAbsolute[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
        connectingPointsAbsolute[i] += skelJointPos;
    }
}