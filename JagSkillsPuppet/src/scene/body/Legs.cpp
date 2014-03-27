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
	
    // connection to abdomen
    connectingPoints.push_back(ofVec3f(0,0,0));
    connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
}

void Legs::drawFaces()
{
    BodyPart::drawFaces();
    formatConnections();
    //BodyPart::formatConnections();
}



void Legs::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}


void Legs::formatConnections()
{
    // set connection points. These are used to position the axes of the child body parts
    for (int i = 0; i < connectingPointsAbsolute.size(); i++)
    {
        // rotate and position the absolute connection ponts
        connectingPointsAbsolute[i] = connectingPoints[i];
        connectingPointsAbsolute[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
        connectingPointsAbsolute[i] += *originPoint; //skelJointPos;
    }
	
	
	ofPushStyle();
    ofSetColor(0, 0, 255, 255);

#ifdef TARGET_OSX
    ofDrawSphere(connectingPointsAbsolute[0], 5);
#else
    ofSphere(connectingPointsAbsolute[0], 5);
#endif

	ofPopStyle();
}

