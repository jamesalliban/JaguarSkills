//
//  BodyPart.h
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"

class BodyPart
{
public:
    virtual void setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader);
    virtual void update(ofVec3f _skelJointPos, ofVec3f _skelJointTarget);
    virtual void drawFaces();
    virtual void drawWireframe();
    virtual void drawDebug(ofColor col);
    virtual void formatConnections();
    
    void drawBox(ofVec3f pos, ofVec3f target);
    
    ofTexture *texture;
    ofTexture *bumpMap;
    ofShader *shader;
    
    static ofFloatColor ambient;
    static ofFloatColor diffuse;
    static ofFloatColor specular;
    static float shinyness;
    static float shadowIntensity;
    static bool isBumpMapActive;
	static float bumpMapStrength;
	static bool isShadingActive;
    
    ofxAssimpModelLoader model;
    
    ofImage img;
    
    ofVec3f skelJointPos;
    ofVec3f skelJointTarget;
    ofVec3f direction;
    ofQuaternion qt;
    ofVec3f qaxis;
    float qangle;
    
    float scaleW, scaleD, scaleH;
    float rotX, rotY, rotZ;
    
    vector<ofVec3f> connectingPoints;
    vector<ofVec3f> connectingPointsAbsolute;
    ofVec3f *originPoint;
    float distToNextPoint;

	ofMesh mesh;
    ofVec3f meshVertsOffset;
	bool isUseOfMesh;

	bool isVisible;
};