//
//  KinectManager.h
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#pragma once

#include "ofxKinectNui.h"
#include "ofMain.h"
#include "ofxSkeletonRecorder.h"
#include "SkeletonDataObject.h"

class ofxKinectNuiDrawTexture;
class ofxKinectNuiDrawSkeleton;

class KinectManager
{
public:
    void setup();
    void update();
    void draw();
    void formatSkeletonData();
	SkeletonDataObject getActiveSkeleton();
    
	void kinectPlugged();
	void kinectUnplugged();
	
	void exit();

	ofxKinectNui kinect;
	ofxBase3DVideo* kinectSource;
    
	vector<string> liveKinectJoints;
	vector<SkeletonDataObject> skeletonDataObjects;

    ofxSkeletonRecorder kinectRecorder;
    vector<SkeletonDataObject> skeletons;
    vector<SkeletonDataObject> smoothSkeletons;
    
    ofVec3f jointPosOffset;
	float jointScale;
    float skeletonZReductionScale;
    float skeletonRotDegrees;
	float skeletonSmoothing;

	bool bPlugged;
	bool isKinectAttached;

	bool bRecord;
	bool bPlayback;
	bool bDrawVideo;
	bool bDrawDepthLabel;
	bool bDrawSkeleton;
	bool bDrawCalibratedTexture;

	int framesSinceSkeletonLost;
	

	// Please declare these texture pointer and initialize when you want to draw them
	ofxKinectNuiDrawTexture*	videoDraw_;
	ofxKinectNuiDrawTexture*	depthDraw_;
	ofxKinectNuiDrawTexture*	labelDraw_;
	ofxKinectNuiDrawSkeleton*	skeletonDraw_;

};