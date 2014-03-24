//
//  ofxSkeletonRecorder.cpp
//  emptyExample
//
//  Created by James Alliban's MBP on 14/03/2014.
//
//

#include "ofxSkeletonRecorder.h"


// TODO:
// - Add timer mechanism to recording to attempt to achieve the same playback speed
// -


void ofxSkeletonRecorder::setup()
{
    clientAmount = 1;
    
    recordedFramesMax = 1000;
	recordingPixels.allocate(60 * (clientAmount * 2), recordedFramesMax, OF_IMAGE_COLOR);
	isRecording = false;
	isPlayback = false;
	isPlaybackPaused = false;
	
	currentPlayingScene = 0;
	framesRecorded = 0;
}


void ofxSkeletonRecorder::draw(int x, int y)
{
//    if (isRecording || isPlayback)
//	{
		recordingImg.setFromPixels(recordingPixels);
		
        ofDisableDepthTest();
        
        ofPushStyle();
        ofPushMatrix();
        //ofTranslate(ofGetWidth() - recordingPixels.getWidth() - 10, 0);
		recordingImg.draw(0, 0);
		ofSetColor(255, 0, 0);
		ofLine(0, currentPlaybackFrame, recordingPixels.getWidth(), currentPlaybackFrame);
		ofSetColor(255);
        ofDrawBitmapString(currentPlaybackPath, 10, 10);
        ofPopMatrix();
        ofPopStyle();
        
        ofEnableDepthTest();
//	}
}


vector<SkeletonDataObject> ofxSkeletonRecorder::getRecordedSkeletons()
{
    vector<SkeletonDataObject> skeletons;
    
	for (int client = 0; client < clientAmount; client++)
	{
		for (int skel = 0; skel < 2; skel++)
		{
            SkeletonDataObject skeletonDataObject;
            skeletonDataObject.skeletonPositions.resize(20);
            int startX = (client * 120) + (skel * 60) + (client * 2) + skel;
            
			// red (0 or 1) = isActive,  green = client, blue = skelId;
			bool isActive = (recordingPixels.getColor(startX, currentPlaybackFrame).r == 0) ? false : true;
			skeletonDataObject.clientID = recordingPixels.getColor(startX, currentPlaybackFrame).g;
			skeletonDataObject.skelID = recordingPixels.getColor(startX, currentPlaybackFrame).b;
            
            //printf("currentPlaybackFrame:%i, startX:%i, isActive:%i \n", currentPlaybackFrame, startX, (isActive ? 1 : 0));
            
			// If the skeleton is active make it clientID_skelID e.g. 0_1, 2_0, 3_1 etc. if inactive make the trackingID '-1'.
			if (isActive)
				skeletonDataObject.trackingID = ofToString(skeletonDataObject.clientID) + "_" + ofToString(skeletonDataObject.skelID);
            else
                skeletonDataObject.trackingID = "-1";
			
			if (isActive)
			{
				for (int joint = 0; joint < 20; joint++)
				{
					skeletonDataObject.skeletonPositions[joint].x = getCoordFromCol(recordingPixels.getColor(startX + 1 + (joint * 3), currentPlaybackFrame));
					skeletonDataObject.skeletonPositions[joint].y = getCoordFromCol(recordingPixels.getColor(startX + 2 + (joint * 3), currentPlaybackFrame));
					skeletonDataObject.skeletonPositions[joint].z = getCoordFromCol(recordingPixels.getColor(startX + 3 + (joint * 3), currentPlaybackFrame));
				}
			}
			else
			{
				for (int joint = 0; joint < 20; joint++)
				{
					skeletonDataObject.skeletonPositions[joint].x = -1;
					skeletonDataObject.skeletonPositions[joint].y = -1;
					skeletonDataObject.skeletonPositions[joint].z = -1;
				}
			}
            //printf("client:%i, skel:%i, skelPos[0].x:%f \n", client, skel, skeletonDataObject.skeletonPositions[0].x);
            
            skeletons.push_back(skeletonDataObject);
		}
	}
    
    if (!isPlaybackPaused)
        if(++currentPlaybackFrame == recordedFramesMax) currentPlaybackFrame = 0;
    
    return skeletons;
}


void ofxSkeletonRecorder::startRecording(int clients, int secondsToRecord)
{
	if (isRecording || isPlayback) return;
	//printf("startRecording()\n");
	recordingPixels.clear();
    // TODO: Get average fps - calculate this from an automatically called update function
	recordingPixels.allocate(60 * (clients * 2), ofGetFrameRate() * secondsToRecord, OF_IMAGE_COLOR);
	isRecording = true;
	framesRecorded = 0;
}




void ofxSkeletonRecorder::stopRecording()
{
	//printf("stopRecording()\n");
	isRecording = false;
	isPlayback = false;
}




void ofxSkeletonRecorder::saveRecording()
{
	if (!isRecording)
    {
		ofSaveImage(recordingPixels, "images/recordedSkeletons/NEW_" + ofGetTimestampString() + ".png", OF_IMAGE_QUALITY_BEST);
    }
}



void ofxSkeletonRecorder::startPlayback(string recordedPath)
{
	if (ofGetFrameNum() < 10) return;
    
	if (!isRecording)
	{
		if (recordedPath != "")
		{
			recordingImg.loadImage(recordedPath);
            currentPlaybackPath = recordedPath;
			recordingPixels.setFromPixels(recordingImg.getPixels(), recordingImg.getWidth(), recordingImg.getHeight(), OF_IMAGE_COLOR);
		}
		currentPlaybackFrame = recordingImg.getHeight() - 2;
		isPlayback = true;
	}
}



void ofxSkeletonRecorder::skipToFrame(int x, int y)
{
    ofRectangle rect = ofRectangle(ofGetWidth() - recordingPixels.getWidth() - 10, 0, recordingPixels.getWidth(), recordingPixels.getHeight());
    if (rect.inside(x, y))
    {
        currentPlaybackFrame = y;
    }
}


void ofxSkeletonRecorder::recordSkeletonData(vector<SkeletonDataObject> trackedSkeletons)
{
    if (isRecording)
	{
		for (int i = 0; i < clientAmount * 2; i++)
		{
			SkeletonDataObject* skeletonDataObject = &trackedSkeletons[i];
            
			int isActive = (skeletonDataObject->skeletonPositions[00].x != -1) ? 1 : -1;
            
			if (framesRecorded > recordingPixels.getHeight() - 30) stopRecording();
			addSkelDataToRecording(isActive, skeletonDataObject->clientID, skeletonDataObject->skelID);
            
			for (int j = 0; j < 20; j++)
			{
				if (isRecording && isActive)
					addJointToRecording(skeletonDataObject->clientID, skeletonDataObject->skelID, j, skeletonDataObject->skeletonPositions[j], isActive);
			}
            
		}
		++framesRecorded;
	}
}



void ofxSkeletonRecorder::addSkelDataToRecording(int isActive, int client, int id)
{
	ofColor skelData;
	// isActive
	skelData.r = (isActive == 1) ? 1 : 0;
	// id
	skelData.g = client;
	//client
	skelData.b = id;
    
	int x = (client * 120) + (id * 60) +  (client * 2) + id;
	recordingPixels.setColor(x, framesRecorded, skelData);
}


void ofxSkeletonRecorder::addJointToRecording(int client, int id, int jointId, ofVec3f joint, bool isActive)
{
	// convert the incoming joint vector to 3 pixels - one each for x, y, z.
	// r is the amount of times the number can be divided by 255
	// g is the remainder
	// b is whether the number is positive or negative
    
	int x = (client * 120) + (id * 60) + (jointId * 3) +  (client * 2) + id;
    
	ofColor colX;
	colX.r = (int)joint.x / 255;
	colX.g = (int)joint.x % 255;
	colX.b = (joint.x < 0) ? 0 : 255;
	recordingPixels.setColor(x + 1, framesRecorded, colX);
	
	ofColor colY;
	colY.r = (int)joint.y / 255;
	colY.g = (int)joint.y % 255;
	colY.b = (joint.y < 0) ? 0 : 255;
	recordingPixels.setColor(x + 2, framesRecorded, colY);
	
	ofColor colZ;
	colZ.r = (int)joint.z / 255;
	colZ.g = (int)joint.z % 255;
	colZ.b = (joint.z < 0) ? 0 : 255;
	recordingPixels.setColor(x + 3, framesRecorded, colZ);
}


float ofxSkeletonRecorder::getCoordFromCol(ofColor col)
{
	float coord = ((col.r * 255) + col.g) * ((col.b == 0) ? -1 : 1);
	//printf("r:%i, g:%i, b:%i, coord:%f, (col.r * 255):%i, mod mult:%i \n", col.r, col.g, col.b, coord, (col.r * 255), ((col.b == 0) ? -1 : 1));
	return coord;
}
