


#include "ofMain.h"
#include "Scene.h"
#include "GUI.h"

class JagSkillsApp {
public:

	void setup();
	void update();
	void draw(SkeletonDataObject skeleton);
		
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
};