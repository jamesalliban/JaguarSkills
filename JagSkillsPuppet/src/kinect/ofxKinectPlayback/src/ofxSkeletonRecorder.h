//
//  ofxSkeletonRecorder.h
//  emptyExample
//
//  Created by James Alliban's MBP on 14/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "SkeletonDataObject.h"

// TODO:
// - Change to SkeletonUtils
//   - Add Skeleton formatting for multiple clients
//   - Add skeleton smoothing
//   - Add skeleton velocities?
// - try to replicate speed
// - add a setMaximumRecordedFrames() method. Used to allocate recordingPixels. Recording can be less than this.
// -

class ofxSkeletonRecorder
{
public:
    
    void setup();
    
    void draw(int x, int y);
    
    vector<SkeletonDataObject> getRecordedSkeletons();
    void startRecording(int clients, int secondsToRecord);
    void stopRecording();
    void saveRecording();
    void startPlayback(string recordedPath);
    void skipToFrame(int x, int y);
    void recordSkeletonData(vector<SkeletonDataObject> trackedSkeletons);
    void addSkelDataToRecording(int isActive, int client, int id);
    bool isPlaybackActive() { return isPlayback; };
    
    // setters - - - - client amount, recording length
    
    
private:
    void addJointToRecording(int client, int id, int jointId, ofVec3f joint, bool isActive);
    float getCoordFromCol(ofColor col);
    
    
    ofPixels recordingPixels;
	ofImage recordingImg;
	bool isRecording;
	bool isPlayback;
    bool isPlaybackPaused;
	int currentPlayingScene;
	int framesRecorded;
	int currentPlaybackFrame;
	int recordedFramesMax;
    int clientAmount;
	string currentPlaybackPath;
};