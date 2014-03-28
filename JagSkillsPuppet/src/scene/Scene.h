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
#include "Head.h"
#include "UpperArmR.h"
#include "UpperArmL.h"
#include "ForearmR.h"
#include "ForearmL.h"
#include "HandR.h"
#include "HandL.h"
#include "ofxAssimpModelLoader.h"


class Scene
{
public:
    void setup();
    void update(vector<SkeletonDataObject> skeletons);
    void draw(vector<SkeletonDataObject> skeletons);
    void drawLineSkeleton(SkeletonDataObject skeleton);
    void setMouseCamEnabled(bool isGUIMouseOver);
    void loadShader();
	void setCameraProps();
	void setCamerangle(int camIndex);
    
    ofEasyCam easyCam;
    ofCamera cam;
	vector<ofVec3f> camPositions;
	vector<ofVec3f> camTartetsPositions;
	int currentCameraIndex;

    ofLight light;
    ofRectangle viewport;
    
    ofVec3f cameraPosition;
    ofVec3f cameraTargetPosition;
    ofVec3f lightPosition;
    ofShader shader;
    
    Torso torso;
    Abdomen abdomen;
    Legs legs;
    Head head;
    UpperArmL upperArmL;
    UpperArmR upperArmR;
    ForearmL forearmL;
    ForearmR forearmR;
    HandL handL;
    HandR handR;
	
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

	bool isEquipmentVisible;

	bool isGridVisible;
	bool isDebugSkeletonVIsible;
};