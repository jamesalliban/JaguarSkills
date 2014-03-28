//
//  Torso.h
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "BodyPart.h"

class Torso : public BodyPart
{
public:
    virtual void setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader);
	void calculateShoulderRotation(ofVec3f shoulder1, ofVec3f shoulder2);
	virtual void update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget);
    virtual void drawFaces();
    virtual void drawWireframe();
    
    virtual void formatConnections();
    
	float shoulderRotation;
};