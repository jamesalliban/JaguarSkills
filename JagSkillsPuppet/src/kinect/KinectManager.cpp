//
//  KinectManager.cpp
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#include "KinectManager.h"
#include "ofxSkeletonRecorder.h"
#include "ofxKinectNuiDraw.h"

void KinectManager::setup()
{
	isKinectAttached = true;
    kinectRecorder.setup();


	//kinect.init(false, false, false, true, true, false, false, true); // enable all captures
	//kinect.open(false);
//	kinect.open(true); // when you want to use near mode

	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = true;
	initSetting.grabDepth = true;
	initSetting.grabAudio = true;
	initSetting.grabLabel = true;
	initSetting.grabSkeleton = true;
	initSetting.grabCalibratedVideo = true;
	initSetting.grabLabelCv = true;
	initSetting.videoResolution = NUI_IMAGE_RESOLUTION_640x480;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_640x480;
	kinect.init(initSetting);
//	kinect.setMirror(false); // if you want to get NOT mirror mode, uncomment here
//	kinect.setNearmode(true); // if you want to set nearmode, uncomment here
	kinect.open();


	kinect.addKinectListener(this, &KinectManager::kinectPlugged, &KinectManager::kinectUnplugged);
	
	ofSetVerticalSync(true);

	kinectSource = &kinect;
	//angle = kinect.getCurrentAngle();
	//bPlugged = kinect.isConnected();

	bDrawVideo = false;
	bDrawDepthLabel = false;
	bDrawSkeleton = false;
	bDrawCalibratedTexture = false;

	videoDraw_ = ofxKinectNuiDrawTexture::createTextureForVideo(kinect.getVideoResolution());
	depthDraw_ = ofxKinectNuiDrawTexture::createTextureForDepth(kinect.getDepthResolution());
	labelDraw_ = ofxKinectNuiDrawTexture::createTextureForLabel(kinect.getDepthResolution());
	skeletonDraw_ = new ofxKinectNuiDrawSkeleton();
	kinect.setVideoDrawer(videoDraw_);
	kinect.setDepthDrawer(depthDraw_);
	kinect.setLabelDrawer(labelDraw_);
	kinect.setSkeletonDrawer(skeletonDraw_);
	
	//framesSinceSkeletonLost = 0;
	//for(int i = 0; i < 1; i++)
	//{
	//	SkeletonDataObject skelData;
	//	for (int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++)
	//	{
	//		skelData.skeletonPositions.push_back(ofVec3f(0, 0, 0));
	//	}
	//	smoothSkeletons.push_back(skelData);
	//}
}



void KinectManager::update()
{
	if (isKinectAttached)
		kinectSource->update();

	ofPoint* skelPoints[ofxKinectNui::SKELETON_COUNT]; ///////////////////////////////////////////////////////////////////////////
		
	int skeletonCount = kinect.getSkeletonPoints(skelPoints);

	//printf("skeletonCount = %i\n", skeletonCount);

	//if (skeletonCount == 2) skeletonCount = 1; 

	 
	if(kinect.isFoundSkeleton())
	{
		framesSinceSkeletonLost = 0;
		if (skeletons.size() == 0)
		{
			for(int i = 0; i < 2; i++)
			{
				SkeletonDataObject skelData;
				for (int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++)
					skelData.skeletonPositions.push_back(ofVec3f(0, 0, 0));
				
				smoothSkeletons.push_back(skelData);
			}
		}
		skeletons.clear();
		for(int i = 0; i < ofxKinectNui::SKELETON_COUNT; i++)
		{
			if(kinect.isTrackedSkeleton(i))
			{
				//if (skelPoints[i][0].z > 0)
				//{
					SkeletonDataObject skelData;
					for(int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++)
					{
						ofPoint joint = skelPoints[i][j];
						skelData.skeletonPositions.push_back(joint);
					}
					skeletons.push_back(skelData);
				}
			//}
		}
		formatSkeletonData();
	}
	else
	{
		if (++framesSinceSkeletonLost > 2)
		{
			skeletons.clear();
			smoothSkeletons.clear();
		}
	}


    if (isKinectAttached && kinectRecorder.isPlaybackActive())
    {
        skeletons.clear();
        skeletons = kinectRecorder.getRecordedSkeletons();
        formatSkeletonData();
    }

	//return;

	// smoothing
	if(kinect.isFoundSkeleton())
	{
		for (int i = 0; i < skeletons.size(); i++)
		{
			for(int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++)
			{
				smoothSkeletons[i].skeletonPositions[j] -= (smoothSkeletons[i].skeletonPositions[j] - skeletons[i].skeletonPositions[j]) * skeletonSmoothing;
			}
		}
	}
}



void KinectManager::draw()
{
	ofSetColor(255);
    kinectRecorder.draw(0,0);

	// Draw video only
	if(bDrawVideo){
		// draw video images from kinect camera
		kinect.drawVideo(0, 0, 320, 240);
	// Draw depth + users label only
	}
	if(bDrawDepthLabel)
	{
		ofEnableAlphaBlending();

		// draw depth images from kinect depth sensor
		kinect.drawDepth(0, 240, 320, 240);
		// draw players' label images on video images
		kinect.drawLabel(0, 240, 320, 240);
		ofDisableAlphaBlending();
	// Draw skeleton only
	}
	if(bDrawSkeleton)
	{
		kinect.drawSkeleton(0, 240, 320, 240);	// draw skeleton images on video images
	}
}


SkeletonDataObject KinectManager::getActiveSkeleton()
{
	for (int i = 0; i < skeletons.size(); i++)
	{
		return skeletons[i];
	}
}



void KinectManager::formatSkeletonData()
{
    for (int i = 0; i < skeletons.size(); i++)
    {
        SkeletonDataObject *skeletonData = &skeletons[i];
        
        for (int j = 0; j < skeletonData->skeletonPositions.size(); j++)
        {
            // currently the range of joint positions is x:0 - 320, y:0 - 240 and z:0 - 30000. This is stupid. The first thing we
            // will do is convert this to x:-160 - 160, y:-120 - 120 and z:-15000 - 15000. This will make scaling easier
            ofVec3f *joint = &skeletonData->skeletonPositions[j];
            
            // this places the user in the centre of the scene. The skeleton range is usually 1-320. This sets the range to -160 - 160
            joint->x -= 160;
            // y comes in upside down and z is in 10ths of a millimeter - this fixes that
			joint->y -= 240;
            joint->y *= -1;
            joint->z = (joint->z * -1) * skeletonZReductionScale;
            
            // rotate skeleton
            joint->rotate(skeletonRotDegrees, ofVec3f(0.0, 0.0, 0.0), ofVec3f(1, 0, 0));

            // offset positions
            joint->x += jointPosOffset.x; // userMan->skeletonPosOffsetX[clientID];
            joint->y += jointPosOffset.y; // -65;
            joint->z += jointPosOffset.z; // 92;

            // adjust scale
			joint->x *= jointScale;
            joint->y *= jointScale;
            joint->z *= jointScale;
        }
    }
}




void KinectManager::kinectPlugged()
{
	bPlugged = true;
}

void KinectManager::kinectUnplugged()
{
	bPlugged = false;
}


void KinectManager::exit() 
{
	if(videoDraw_) {
		videoDraw_->destroy();
		videoDraw_ = NULL;
	}
	if(depthDraw_) {
		depthDraw_->destroy();
		depthDraw_ = NULL;
	}
	if(labelDraw_) {
		labelDraw_->destroy();
		labelDraw_ = NULL;
	}
	if(skeletonDraw_) {
		delete skeletonDraw_;
		skeletonDraw_ = NULL;
	}

	//kinect.setAngle(0);
	kinect.close();
	kinect.removeKinectListener(this);
}