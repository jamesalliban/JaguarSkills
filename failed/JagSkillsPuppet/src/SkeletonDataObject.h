//
//  SkeletonDataObject.cpp
//  emptyExample
//
//  Created by James Alliban's MBP on 14/03/2014.
//
//

#pragma once

#include "ofMain.h"


#define KINECT_SDK_HIP_CENTRE 0
#define KINECT_SDK_SPINE 1
#define KINECT_SDK_SHOULDER_CENTRE 2
#define KINECT_SDK_HEAD 3
#define KINECT_SDK_SHOULDER_LEFT 4
#define KINECT_SDK_ELBOW_LEFT 5
#define KINECT_SDK_WRIST_LEFT 6
#define KINECT_SDK_HAND_LEFT 7
#define KINECT_SDK_SHOULDER_RIGHT 8
#define KINECT_SDK_ELBOW_RIGHT 9
#define KINECT_SDK_WRIST_RIGHT 10
#define KINECT_SDK_HAND_RIGHT 11
#define KINECT_SDK_HIP_LEFT 12
#define KINECT_SDK_KNEE_LEFT 13
#define KINECT_SDK_ANKLE_LEFT 14
#define KINECT_SDK_FOOT_LEFT 15
#define KINECT_SDK_HIP_RIGHT 16
#define KINECT_SDK_KNEE_RIGHT 17
#define KINECT_SDK_ANKLE_RIGHT 18
#define KINECT_SDK_FOOT_RIGHT 19


struct SkeletonDataObject
{
    int clientID;
    int skelID;
    string trackingID;
    vector<ofVec3f> skeletonPositions;
};
