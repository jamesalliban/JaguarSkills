#pragma once

//#include "ofxKinectNui.h"
#include "KinectManager.h"
#include "ofMain.h"
#include "ofxSkeletonRecorder.h"
#include "Scene.h"
//#include "GUI.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void formatSkeletonData();
    void drawBodyPart(int _pos, int _target);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    Scene scene;
   // GUI gui;
    KinectManager kinectManager;
    
    bool isPaused;
    
    float frameRate;
    bool isFullscreen;


//    gui->addSlider("Frame rate", 1, 60, &app->frameRate, length, dim);
//    gui->addToggle("Fullscreen", &app->scene.isDrawPolylines, toggleSize, toggleSize);
//    gui->addSpacer(length, 1);
//    gui->addLabel("WINDOW");
//    gui->addSlider("Window X", 0, 1000, &app->windowX, length, dim);
//    gui->addSlider("Window Y", 0, 1000, &app->windowY, length, dim);
//    gui->addSlider("Window width", 100, 1800, &app->windowW, length, dim);
//    gui->addSlider("Window height", 100, 1200, &app->windowH, length, dim);
};
