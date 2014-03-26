//
//  Scene.h
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "SkeletonDataObject.h"
#include "BodyPart.h"
#include "Torso.h"
#include "Abdomen.h"
#include "Legs.h"
#include "UpperArm.h"
#include "Forearm.h"
#include "Hand.h"
#include "ofxAssimpModelLoader.h"


class Scene
{
public:
    void setup();
    void update(SkeletonDataObject skeleton);
    void draw(SkeletonDataObject skeleton);
    void drawLineSkeleton(SkeletonDataObject skeleton);
    void setMouseCamEnabled(bool isGUIMouseOver);
    void loadShader();
    
    ofEasyCam easyCam;
    ofLight light;
    ofRectangle viewport;
    
    ofVec3f cameraPosition;
    ofVec3f cameraTargetPosition;
    ofVec3f lightPosition;
    ofShader shader;
    
    Torso torso;
    Abdomen abdomen;
    Legs legs;
    BodyPart head;
    UpperArm upperArmL;
    UpperArm upperArmR;
    Forearm forearmL;
    Forearm forearmR;
    Hand handL;
    Hand handR;
	
    ofxAssimpModelLoader decks;
	ofImage decksImg;
    ofxAssimpModelLoader mixer;

	ofVec3f decksRot;
	ofVec3f decksScale;
    ofVec3f decks1Pos;
    ofVec3f decks2Pos;

	ofVec3f mixerRot;
	ofVec3f mixerScale;
	ofVec3f mixerPos;
    

    ofImage chestImg;
    ofImage headarmsImg;
    ofImage pantsImg;
    ofImage chestBumpImg;
    ofImage headarmsBumpImg;
    ofImage pantsBumpImg;

    float modelAlpha;
    
    bool isMouseCam;
    bool isDrawFaces;
    bool isDrawDebug;
    bool isDrawModel;

	bool isEquipmentVisible;
};