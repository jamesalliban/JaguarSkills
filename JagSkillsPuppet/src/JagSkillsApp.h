


#include "ofMain.h"
#include "Scene.h"
#include "GUI.h"
#include "ofxOsc.h"

class JagSkillsApp {
public:

	void setup();
	void update();
	void draw(vector<SkeletonDataObject> skeletons);
		
    Scene scene;
    GUI gui;
	
    float frameRate;
    bool isFullscreen;
    bool isPaused;



	//KinectManager variables - they are here because ofofxKinectNui bollocks
	ofVec3f jointPosOffset;
	float jointScale;
    float skeletonZReductionScale;
    float skeletonRotDegrees;
	float skeletonSmoothing;

	float backgroundR, backgroundG, backgroundB;

	// networking
	ofxOscReceiver receiver;
};