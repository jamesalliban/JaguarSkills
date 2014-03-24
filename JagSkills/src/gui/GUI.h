//
//  GUI.h
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#pragma once

#include "ofMain.h"
#include "GUIManager.h"

class testApp;

class GUI : public GUIManager
{
public:
    virtual void setup(string _guiPath = "GUI");
    
    void addKeyGUI();
    void addAppGUI();
    void addSceneGUI();
    void addSkeletonGUI();
    void addModelGlobalGUI();
    void addModelTorsoGUI();
    void addModelHeadGUI();
    void addModelAbdomenAndLegsGUI();
    void addModelArmsLGUI();
    void addModelArmsRGUI();
    void addModelHandsGUI();
    void addShadingGUI();
    void addBackgroundGUI();
    void addGUIDesignGUI();
    
    void guiModelGlobalGUIEvent(ofxUIEventArgs &e);
    void guiDesignGUIEvent(ofxUIEventArgs &e);
    
    virtual void update();
    virtual void draw();
    
    
    testApp* app;
};
