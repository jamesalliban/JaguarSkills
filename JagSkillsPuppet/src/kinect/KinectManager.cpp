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

	bDrawVideo = true;
	bDrawDepthLabel = true;
	bDrawSkeleton = true;
	bDrawCalibratedTexture = false;

	videoDraw_ = ofxKinectNuiDrawTexture::createTextureForVideo(kinect.getVideoResolution());
	depthDraw_ = ofxKinectNuiDrawTexture::createTextureForDepth(kinect.getDepthResolution());
	labelDraw_ = ofxKinectNuiDrawTexture::createTextureForLabel(kinect.getDepthResolution());
	skeletonDraw_ = new ofxKinectNuiDrawSkeleton();
	kinect.setVideoDrawer(videoDraw_);
	kinect.setDepthDrawer(depthDraw_);
	kinect.setLabelDrawer(labelDraw_);
	kinect.setSkeletonDrawer(skeletonDraw_);
}



void KinectManager::update()
{
	if (isKinectAttached)
	{
		kinectSource->update();
	}

	ofPoint* skelPoints[ofxKinectNui::SKELETON_COUNT];
		
	int skeletonCount = kinect.getSkeletonPoints(skelPoints);

	printf(" skeletonCount:%i \n", skeletonCount);

	skeletons.clear();

	if(kinect.isFoundSkeleton())
	{
		for(int i = 0; i < ofxKinectNui::SKELETON_COUNT; i++)
		{
			if(kinect.isTrackedSkeleton(i))
			{
				SkeletonDataObject skelData;
				//skelData.trackingID = i;
				for(int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++)
				{
					ofPoint joint = skelPoints[i][j];
					//printf("skelPoints[%i], x:%f, y:%f, z:%f \n", j, joint.x, joint.y, joint.z);
					
					skelData.skeletonPositions.push_back(joint);
				}
				skeletons.push_back(skelData);
			}
		}
		formatSkeletonData();
	}



	if (skeletonCount > 0)
	{
		int n = skeletonCount * 20;
		for (int j = 0; j < n; j++)
		{
			//printf("skelPoints[%i], x:%f, y:%f, z:%f \n", j, skelPoints[j]->x, skelPoints[j]->y, skelPoints[j]->z);
		}
	}
		//}
	//}



	////Loop through all skeleton containers from ofxKinectNui
	//for(int i = 0; i < kinect::nui::SkeletonFrame::SKELETON_COUNT; i++)
	//{
	//	ofPoint skelPoint = kinect.getSkeletonPoints()[i][0];
	//	//is this ofxKinectNui skeleton is empty
	//	if (skelPoint.x == -1 && skelPoint.y == -1 && skelPoint.z == -1) 
	//	{
	//		//Check SkeletonData objects to see if there is a skel with this array index and if it was 
	//		//previously active. If so, reset the SkeletonData object
	//		for (int j = 0; j < (int)skeletonDataObjects.size(); j++)
	//			if (skeletonDataObjects[j].arrayIndex == i && skeletonDataObjects[j].isActive)
	//				resetSkeletonData(j);
	//	}
	//	
	//	
	//	//if ofxKinectNui skeleton is active 
	//	if (skelPoint.x != -1 && skelPoint.y != -1 && skelPoint.z != -1) 
	//	{
	//		bool hasNewSkeletonBeenAsigned = false;
	//		//loop through SkeletonData objects to see if one has this arrayIndex
	//		for (int j = 0; j < (int)skeletonDataObjects.size(); j++)
	//		{
	//			SkeletonData* skelData = &skeletonDataObjects[j];
	//			//if there is a match, populate it with the data from this skeleton
	//			if (skelData->arrayIndex == i)
	//			{
	//				populateSkeletonData(i, j, false);
	//				hasNewSkeletonBeenAsigned = true;
	//			}
	//			if (hasNewSkeletonBeenAsigned) break;
	//		}

	//		//the skeleton has not been assigned so it is new. 
	//		if (!hasNewSkeletonBeenAsigned)
	//		{
	//			//Loop through the SkeletonData objects to find the first empty one, assign it to this 
	//			//array index and populate it with data
	//			for (int j = 0; j < (int)skeletonDataObjects.size(); j++)
	//			{
	//				SkeletonData* skelData = &skeletonDataObjects[j];
	//				if (!skelData->isActive)
	//				{
	//					populateSkeletonData(i, j, true);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}




    if (isKinectAttached && kinectRecorder.isPlaybackActive())
    {
        skeletons.clear();
        skeletons = kinectRecorder.getRecordedSkeletons();
        formatSkeletonData();
    }
}



void KinectManager::draw()
{
	//ofSetColor(255);
    //kinectRecorder.draw(0,0);

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
	// Draw calibrated image only
	}


	//stringstream kinectReport;
	//if(bPlugged && !kinect.isOpened() && !bPlayback){
	//	ofSetColor(0, 255, 0);
	//	kinectReport << "Kinect is plugged..." << endl;
	//	ofDrawBitmapString(kinectReport.str(), 200, 300);
	//}else if(!bPlugged){
	//	ofSetColor(255, 0, 0);
	//	kinectReport << "Kinect is unplugged..." << endl;
	//	ofDrawBitmapString(kinectReport.str(), 200, 300);
	//}

	//// draw instructions
	//ofSetColor(255, 255, 255);
	//stringstream reportStream;
	//reportStream << "fps: " << ofGetFrameRate() << "  Kinect Nearmode: " << kinect.isNearmode() << endl
	//			 << "press 'c' to close the stream and 'o' to open it again, stream is: " << kinect.isOpened() << endl
	//			 << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
	//			 << "press LEFT and RIGHT to change the far clipping distance: " << farClipping << " mm" << endl
	//			 << "press '+' and '-' to change the near clipping distance: " << nearClipping << " mm" << endl
	//			 << "press 'r' to record and 'p' to playback, record is: " << bRecord << ", playback is: " << bPlayback << endl
	//			 << "press 'v' to show video only: " << bDrawVideo << ",      press 'd' to show depth + users label only: " << bDrawDepthLabel << endl
	//			 << "press 's' to show skeleton only: " << bDrawSkeleton << ",   press 'q' to show point cloud sample: " << bDrawCalibratedTexture;
	//ofDrawBitmapString(reportStream.str(), 20, 648);


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
            //joint->y -= 120;
            //joint->z -= 15000;
            
            
            // y comes in upside down and z is in 10ths of a millimeter - this fixes that
            joint->y -= 240;
            joint->y *= -1;
            joint->z = (joint->z * -1) * skeletonZReductionScale;
            
            //            // rotate skeleton
            joint->rotate(skeletonRotDegrees, ofVec3f(0.0, 0.0, 0.0), ofVec3f(1, 0, 0));
//
//            // offset positions
//            joint->x += jointPosOffset.x; //userMan->skeletonPosOffsetX[clientID];
            joint->y += jointPosOffset.y; // -65;
            joint->z += jointPosOffset.z; // 92;
//
//            // adjust scale
//            if (isSkelScaled)
//            {
//                joint->x *= userMan->skeletonScale[clientID];
//                joint->y *= userMan->skeletonScale[clientID];
//                joint->z *= userMan->skeletonScale[clientID];
//            }
//
//            if (isSkelScaleFromZ)
//            {
//                //capture the hip vector then fix the z scaling bug
//                if (i == 0) hipOffset = ofVec3f(jointPositions[CELL_HIP_CENTRE]);
//                performZScaleFix(&jointPositions[i]);
//            }
//
//            if (isZSpreadOffset)
//            {
//                joint->z = ofMap(joint->z, zSpreadInputMin, zSpreadInputMax, zSpreadOutputMin, zSpreadOutputMax);
//            }
//
//            //joint->x += (UserManager::xSpreadRangeNormalMax[clientID]);// * userMan->skeletonScale[clientID]); // * 0.5;
//
//            if (isXSpreadOffset)
//            {
//                float zPosNorm = ofMap(joint->z, zSpreadOutputMin, zSpreadOutputMax, 0, 1);
//                float xPosOffset = (userMan->skeletonPosOffsetX[clientID]) * userMan->skeletonScale[clientID];
//                float xPosNorm = ofMap(joint->x, UserManager::xSpreadRangeNormalMin[clientID] + xPosOffset, UserManager::xSpreadRangeNormalMax[clientID] + xPosOffset, 0, 1);
//                float frontXpos = ofMap(xPosNorm, 0, 1, UserManager::xFrontSkewedMin[clientID], UserManager::xFrontSkewedMax[clientID]);
//                float backXpos = ofMap(xPosNorm, 0, 1, UserManager::xBackSkewedMin[clientID], UserManager::xBackSkewedMax[clientID]);
//
//                if (clientID == 0 && i == CELL_HIP_CENTRE) printf("zPosNorm:%f, xPosNorm:%f, xPosOffset:%f, frontXpos:%f, backXPos:%f \n", zPosNorm, xPosNorm, xPosOffset, frontXpos, backXpos);
//
//                if (i == CELL_HIP_CENTRE)
//                {
//                    float hipCentreX = joint->x;
//                    float newHipCentreX = ofLerp(frontXpos, backXpos, zPosNorm);
//                    hipXSpreadOffset = newHipCentreX - hipCentreX;
//                    joint->x = newHipCentreX;
//                    joint->x += userMan->skeletonPosOffsetX[clientID] * userMan->skeletonScale[clientID];
//                }
//                else
//                {
//                    
//                    joint->x += hipXSpreadOffset;
//                    joint->x += userMan->skeletonPosOffsetX[clientID] * userMan->skeletonScale[clientID];
//                }
//            }
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