//
//  KinectManager.h
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "ofxKinectNui.h"
#include "ofxKinectNuiPlayer.h"

#include "ofxSkeletonRecorder.h"

class KinectManager
{
public:
    void setup();
    void update();
    void draw();
    void formatSkeletonData();
    
    
    ofxSkeletonRecorder kinectRecorder;
    vector<SkeletonDataObject> skeletons;
    
    ofVec3f jointPosOffset;
    float skeletonZReductionScale;
    float skeletonRotDegrees;
};