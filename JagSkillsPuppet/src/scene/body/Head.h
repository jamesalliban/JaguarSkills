//
//  HandR.h
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "BodyPart.h"

class Head : public BodyPart
{
public:
    virtual void setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader);
	virtual void update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget);
    virtual void drawFaces();
    virtual void drawWireframe();

	float rotXNodOffsetAngleInMin, rotXNodOffsetAngleInMax, rotXNodOffsetAngleOutMin, rotXNodOffsetAngleOutMax;
};