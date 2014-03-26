//
//  Torso.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Torso.h"

void Torso::setup(string modelPath)
{
    BodyPart::setup(modelPath);
    
    img.loadImage("models/texturesv1/chest_diff_combined.tif");
    
    model.loadModel(modelPath, true);
    
    model.setScale(0.2, 0.2, 0.2);
    model.setRotation(0, -90, 0, 0, 1);
//    model.setRotation(0, 180, 0, 1, 0);
//    model.setRotation(1, -90, 1, 0, 0);
    
    for (int i = 0; i < 2; i++)
    {
        connectingPoints.push_back(ofVec3f(0,0,0));
        connectingPointsRotated.push_back(ofVec3f(0, 0, 0));
    }
}



void Torso::drawFaces()
{
    BodyPart::drawFaces();
    
    formatConnections();
}


void Torso::formatConnections()
{
    // set connection points. These are used to position the axes of the child body parts
    for (int i = 0; i < connectingPointsRotated.size(); i++)
    {
        connectingPointsRotated[i] = connectingPoints[i];
        connectingPointsRotated[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
        connectingPointsRotated[i] += skelJointPos;
        
        ofPushMatrix();
        ofTranslate(connectingPointsRotated[i]);
        ofDrawAxis(20);
        ofPopMatrix();
        
        ofPushStyle();
        ofSetColor(0, 0, 255, 255);
        ofDrawSphere(connectingPointsRotated[i], 5);
        ofPopStyle();
    }
}