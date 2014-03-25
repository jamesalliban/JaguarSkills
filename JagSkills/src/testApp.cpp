#include "testApp.h"

// TODO:
// - Get the app working with the PC and Kinect.
// - Smooth skeleton data.
// - Add constraints to make sure limbs\head don't bend unnaturally.
// - Ensure hand rotation looks good (hands down over decks).
// - Add animated facial expressions - - cz, how are you getting on with these?
// - Add configurable camera angles.
// - Add decks.
// - Change background to green and remove the anti-aliasing - ready for greenscreen keying.


void testApp::setup()
{
    ofSetFrameRate(30);
//    ofEnableArbTex();
    ofDisableArbTex();
    ofSetWindowPosition(10, 10);
    ofSetWindowShape(1600, 1000);
    
    kinectManager.setup();
    scene.setup();
    
    gui.setup();
    
	isPaused = false;
}

void testApp::update()
{
    if (ofGetFrameNum() == 10)
        kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");

    
    ofSetFullscreen(isFullscreen);
    
    scene.setMouseCamEnabled(gui.isMouseOver());
    

        
    
    ofSetFrameRate(frameRate);
    
    if (!isPaused) kinectManager.update();
    
    if (kinectManager.skeletons.size() > 0)
        scene.update(kinectManager.skeletons[0]);
}

void testApp::draw()
{
    ofBackground(40);
    kinectManager.draw();
    
    if (kinectManager.skeletons.size() > 0)
        scene.draw(kinectManager.skeletons[0]);
}

void testApp::keyPressed(int key)
{
    if (key == 'p')
    {
        isPaused = !isPaused;
    }
    else if (key == 'l')
    {
        kinectManager.kinectRecorder.startPlayback("images/rec/back_and_forth_4p_4k.png");
//        kinectRecorder.startPlayback("images/rec/back_and_for_2p_3k.png");
    }
    else if (key == 'f')
    {
        isFullscreen = !isFullscreen;
        ofSetFullscreen(isFullscreen);
    }
    else if (key == 'r')
    {
        scene.loadShader();
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