#include "testApp.h"

// TODO:
// - Smooth skeleton data.
// - - Rotate torso when shoulders rotate. 
// - - Fix hands - rotate them to face down when over the decks.
// - - Reduce gimbal lock by not allowing forearm to ben inward too much.
// - - Rotate legs when hips rotate. 
// - Add configurable camera angles - OSC and MIDI.
// - Change background to green and remove the anti-aliasing - ready for greenscreen keying.
// - Fix crashing when 2nd person enters.
// - Add animated facial expressions - - cz, how are you getting on with these?


void testApp::setup()
{
    kinectManager.setup();
	jagSkillsApp.setup();
}

void testApp::update()
{
	// ofxKinectNui bollocks workaround
	kinectManager.jointPosOffset = jagSkillsApp.jointPosOffset;
	kinectManager.jointScale = jagSkillsApp.jointScale;
	kinectManager.skeletonRotDegrees = jagSkillsApp.skeletonRotDegrees;
	kinectManager.skeletonZReductionScale = jagSkillsApp.skeletonZReductionScale;
	kinectManager.skeletonSmoothing = jagSkillsApp.skeletonSmoothing;


	//if (ofGetFrameNum() == 10)
 //       kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");

    if (!jagSkillsApp.isPaused) kinectManager.update();
    
	jagSkillsApp.update();
	jagSkillsApp.scene.update(kinectManager.smoothSkeletons); //kinectManager.getActiveSkeleton());
}

void testApp::draw()
{
    ofBackground(40);
    kinectManager.draw();
    
    jagSkillsApp.draw(kinectManager.smoothSkeletons);
}

void testApp::keyPressed(int key)
{
    if (key == 'p')
        jagSkillsApp.isPaused = !jagSkillsApp.isPaused;
    else if (key == 'l')
        kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");
    else if (key == 'f')
    {
        jagSkillsApp.isFullscreen = !jagSkillsApp.isFullscreen;
        ofSetFullscreen(jagSkillsApp.isFullscreen);
    }
    else if (key == 'r')
        jagSkillsApp.scene.loadShader();
	else if (key == '1')
	{
		jagSkillsApp.scene.currentCameraIndex = 0;
	}
	else if (key == '2')
	{
		jagSkillsApp.scene.currentCameraIndex = 1;
	}
	else if (key == '3')
	{
		jagSkillsApp.scene.currentCameraIndex = 2;
	}
	else if (key == '4')
	{
		jagSkillsApp.scene.currentCameraIndex = 3;
	}
	else if (key == '5')
	{
		jagSkillsApp.scene.currentCameraIndex = 4;
	}
}

void testApp::keyReleased(int key){

}

void testApp::mouseMoved(int x, int y){

}

void testApp::mouseDragged(int x, int y, int button){

}

void testApp::mousePressed(int x, int y, int button){

}

void testApp::mouseReleased(int x, int y, int button){
}

void testApp::windowResized(int w, int h){
}

void testApp::gotMessage(ofMessage msg){

}

void testApp::dragEvent(ofDragInfo dragInfo){

}


void testApp::exit()
{
	kinectManager.exit();
}