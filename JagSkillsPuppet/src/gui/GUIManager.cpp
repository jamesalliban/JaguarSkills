//
//  GUIManager.cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUIManager.h"



void GUIManager::setup(string _guiPath)
{
    guiPath = _guiPath;
    
    ofAddListener(ofEvents().keyPressed, this, &GUIManager::keyPressed);
    ofAddListener(ofEvents().mouseReleased, this, &GUIManager::mouseReleased);
    ofAddListener(ofEvents().exit, this, &GUIManager::exit);
    
    currentUIID = 0;
    dim = 12;
	canvasW = 300;
    canvasH = ofGetScreenHeight();
    xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    length = canvasW - xInit* 2;
    toggleSize = 12;
    spacerW = canvasW - xInit* 2;
    spacerH = 1;
    colorBack = ofColor(100, 100, 100, 230);
    colorFill = ofColor(255, 100, 100, 230);
    colorHighlight = ofColor(255, 100, 100, 230);
    colorOutline = ofColor(255, 100, 100, 230);
    colorOutlineHighlight = ofColor(255, 100, 100, 230);
    colorPadded = ofColor(255, 100, 100, 230);
    colorPaddedHighlight = ofColor(255, 100, 100, 230);
    isVisible = false;
	isAutoSave = true;
    
    buildSideBarGUI();
}


bool GUIManager::getVisible()
{
    return isVisible;
}

bool GUIManager::isMouseOver()
{
    if (guiPages[currentUIID]->getRect()->inside(ofGetMouseX(), ofGetMouseY()) ||
        sideBarGui->getRect()->inside(ofGetMouseX(), ofGetMouseY()))
        return true;
    else
        return false;
}

void GUIManager::buildSideBarGUI()
{
	sideBarGui = new ofxUICanvas(canvasW, 0, sidebarLength, 146);
    sideBarGui->setColorBack(colorBack);
    
	sideBarGui->setName(SIDE_TITLE);
//    sideBarGui->setFont(guiPath + "/NewMedia Fett.ttf");
    
	sideBarGui->addWidgetRight(new ofxUIFPS(OFX_UI_FONT_MEDIUM));
    
#ifdef TARGET_OSX
    sideBarGui->setGlobalButtonDimension(45);
#endif

#ifdef TARGET_OSX
    sideBarGui->addImageToggle(SIDE_AUTO_SAVE, "GUI/images/auto_save_image.png", true);
#else
	sideBarGui->addWidgetDown(new ofxUILabelToggle(true, SIDE_AUTO_SAVE));
#endif

	sideBarGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    
#ifdef TARGET_OSX
    sideBarGui->addImageButton(SIDE_SAVE, "GUI/images/save_image.png", false);
#else
	sideBarGui->addWidgetRight(new ofxUILabelButton(false, SIDE_SAVE));
#endif

    sideBarGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    sideBarGui->addSpacer(length * 0.5, 1);

    sideBarGui->autoSizeToFitWidgets();
    
	ofAddListener(sideBarGui->newGUIEvent, this, &GUIManager::sideBarGUIEvent);
	finaliseCanvas(sideBarGui, true);
}



ofxUICanvas* GUIManager::getNewGUI(string title)
{
    ofxUICanvas* gui = new ofxUICanvas(0, 0, canvasW, canvasH);
    gui->setColorBack(colorBack);
	gui->setName(title);
//    gui->setFont(guiPath + "/NewMedia Fett.ttf");
	gui->addWidgetDown(new ofxUILabel(gui->getName(), OFX_UI_FONT_MEDIUM));
    gui->addSpacer(spacerW, spacerH);
    return gui;
}



void GUIManager::finaliseCanvas(ofxUICanvas* gui, bool isSidebar)
{
    string name = gui->getName();
    string xmlPath = guiPath + "/" + name + "GuiPageSettings.xml";
    gui->loadSettings(xmlPath);
    gui->setVisible(false);
    
    gui->autoSizeToFitWidgets();
    if (!isSidebar) guiPages.push_back(gui);
    
    if (!isSidebar)
    {
#ifdef TARGET_OSX
        sideBarGui->addWidgetDown(new ofxUILabelToggle(name, false));
#else
        sideBarGui->addWidgetDown(new ofxUILabelToggle(false, name));
#endif
		sideBarGui->autoSizeToFitWidgets();

    }
}



void GUIManager::sideBarGUIEvent(ofxUIEventArgs &e) //---------------- Top bar
{
	string name = e.widget->getName();
    
	if (name == SIDE_AUTO_SAVE)
	{
		ofxUIToggle *toggle = (ofxUIToggle *)e.widget;
		isAutoSave = toggle->getValue();
	}
	else if (name == SIDE_SAVE)
	{
		saveSettings();
	}
	else if (name == SIDE_NEXT)
	{
		ofxUIButton *button = (ofxUIButton *)e.widget;
		if (button->getValue()) nextPage();
	}
	else if (name == SIDE_PREVIOUS)
	{
		ofxUIButton *button = (ofxUIButton *)e.widget;
		if (button->getValue()) previousPage();
	}
    else
    {
        for (int i = 0; i < (int)guiPages.size(); i++)
            if (name == guiPages[i]->getName()) currentUIID = i;
        
        showGUI(name);
    }
}


void GUIManager::keyPressed(ofKeyEventArgs& eventArgs) //int key)
{
    printf("keyPressed - key = %c \n", eventArgs.key);
    switch (eventArgs.key)
    {
		case '[':
            previousPage();
            break;
            
        case ']':
            nextPage();
            break;
            
        case ' ':
            toggleVisible();
    }
}


void GUIManager::mouseReleased(ofMouseEventArgs& eventArgs)
{
	if (isAutoSave)
		saveSettings();
}


void GUIManager::nextPage()
{
	++currentUIID;
	if (currentUIID > guiPages.size() - 1) currentUIID = 0;
    showGUI(guiPages[currentUIID]->getName());
}


void GUIManager::previousPage()
{
	--currentUIID;
	if (currentUIID < 0) currentUIID = guiPages.size() - 1;
    showGUI(guiPages[currentUIID]->getName());
}

void GUIManager::showGUI(string guiName)
{
    for (int i = 0; i < (int)guiPages.size(); i++)
        guiPages[i]->setVisible(false);
    
	isVisible = true;
    if (guiPages.size() > 0)
    {
        int newVisibleGUIID = currentUIID % (int)guiPages.size();
        guiPages[newVisibleGUIID]->setVisible(true);
	}
    sideBarGui->setVisible(true);
    
    
    
    for (int i = 0; i < sideBarGui->getWidgets().size(); i++)
    {
        vector<ofxUIWidget*> buttons = sideBarGui->getWidgets();
        ofxUIWidget* button = buttons[i];
        int labelStrPos = button->getName().find(" LABEL");
        
        // make sure only the selected GUI page button is highlighted
        if (button->getKind() == OFX_UI_WIDGET_LABELTOGGLE)
        {
            ofxUILabelToggle *labelToggle = (ofxUILabelToggle*)buttons[i];
            if (button->getName() != guiName)
                labelToggle->setValue(false);
            else
                labelToggle->setValue(true);
        }
        else if (button->getKind() == OFX_UI_WIDGET_LABEL)
        {
            ofxUILabel *label = (ofxUILabel*)buttons[i];
            if (button->getName().substr(0, labelStrPos) == guiName.substr(0, labelStrPos))
            {
                label->setDrawBack(true);
                label->setDrawFill(true);
            }
        }
    }
}


void GUIManager::toggleVisible()
{
    isVisible = !isVisible;
    if (isVisible)
    {
        showGUI(guiPages[currentUIID]->getName());
    }
    else
    {
        for (int i = 0; i < (int)guiPages.size(); i++)
        {
            guiPages[i]->setVisible(false);
        }
		sideBarGui->setVisible(false);
    }
}


void GUIManager::saveSettings()
{
	for (int i = 0; i < (int)guiPages.size(); i++)
    {
        string xmlPath = guiPath + "/" + guiPages[i]->getName() + "guiPagesettings.xml";
        guiPages[i]->saveSettings(xmlPath);
    }
    //sideBarGui->saveSettings("GUI/" + sideBarGui->getName() + "guiPagesettings.xml");
}


void GUIManager::setGUIColour()
{
    for (int i = 0; i < (int)guiPages.size(); i++)
    {
        guiPages[i]->setColorBack(colorBack);
        
        for (int j = 0; j < guiPages[i]->getWidgets().size(); j++)
        {
            vector<ofxUIWidget*> widgets = guiPages[i]->getWidgets();
            ofxUIWidget* widget = widgets[j];
            widget->setColorBack(colorBack);
            widget->setColorFill(colorFill);
            widget->setColorFillHighlight(colorHighlight);
            widget->setColorOutline(colorOutline);
            widget->setColorOutlineHighlight(colorOutlineHighlight);
            widget->setColorPadded(colorPadded);
            widget->setColorPaddedOutline(colorPaddedHighlight);
        }
    }
    sideBarGui->setColorBack(colorBack);
    
    for (int j = 0; j < sideBarGui->getWidgets().size(); j++)
    {
        vector<ofxUIWidget*> widgets = sideBarGui->getWidgets();
        ofxUIWidget* widget = widgets[j];
        widget->setColorBack(colorBack);
        widget->setColorFill(colorFill);
        widget->setColorFillHighlight(colorHighlight);
        widget->setColorPadded(colorPadded);
        widget->setColorPaddedOutline(colorPaddedHighlight);
    }
}


void GUIManager::exit(ofEventArgs& eventArgs)
{
    if (isAutoSave) saveSettings();
	delete sideBarGui;
    for (int i = 0; i < guiPages.size(); i++)
        delete guiPages[i];
}

