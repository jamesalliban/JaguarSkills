//
//  Torso.h
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#pragma once

#include "ofMain.h"
#include "BodyPart.h"

class Torso : public BodyPart
{
public:
    virtual void setup(string modelPath);
    virtual void drawFaces();
    
    virtual void formatConnections();
    
};