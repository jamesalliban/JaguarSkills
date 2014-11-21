//
//  Legs.cpp
//  JagSkills
//
//  Created by James Alliban's MBP on 22/03/2014.
//
//

#include "Legs.h"

void Legs::setup(string modelPath, ofTexture *_texture, ofTexture *_bumpMap, ofShader *_shader)
{
    BodyPart::setup(modelPath, _texture, _bumpMap, _shader);
	
	//isUseOfMesh = true;

    // connection to abdomen
    connectingPoints.push_back(ofVec3f(0,0,0));
    connectingPointsAbsolute.push_back(ofVec3f(0, 0, 0));
}




void Legs::drawFaces()
{
    ofPushMatrix();
    ofTranslate(*originPoint);
    // rotate in direction of target
    ofRotate(qangle, qaxis.x, qaxis.y, qaxis.z);
    
    float ambientArray[4];
    ambientArray[0] = ambient.r;
    ambientArray[1] = ambient.g;
    ambientArray[2] = ambient.b;
    ambientArray[3] = ambient.a;
    float diffuseArray[4];
    diffuseArray[0] = diffuse.r;
    diffuseArray[1] = diffuse.g;
    diffuseArray[2] = diffuse.b;
    diffuseArray[3] = diffuse.a;
    float specularArray[4];
    specularArray[0] = specular.r;
    specularArray[1] = specular.g;
    specularArray[2] = specular.b;
    specularArray[3] = specular.a;
    
	if (isShadingActive)
	{
		shader->begin();
		shader->setUniformTexture("tex0", *texture, texture->getTextureData().textureID);
		shader->setUniformTexture("texDepthMap", *bumpMap, bumpMap->getTextureData().textureID);
		shader->setUniform4fv("ambient", ambientArray);
		shader->setUniform4fv("diffuse", diffuseArray);
		shader->setUniform4fv("specular", specularArray);
		shader->setUniform1f("shinyness", shinyness);
		shader->setUniform1f("shadowIntensity", shadowIntensity);
		shader->setUniform1i("isBumpMapActive", (isBumpMapActive) ? 1 : 0);
		shader->setUniform1f("bumpMapStrength", bumpMapStrength);
	}

    if (isUseOfMesh)
	{
		ofPushMatrix();
		ofScale(scaleW, scaleH, scaleD);
		ofRotate(rotX, 1, 0, 0);
		ofRotate(rotY, 0, 1, 0);
		ofRotate(rotZ, 0, 0, 1);

		if (isVisible)
		{
			for (int i = 0; i < meshes.size(); i++)
				meshes[i].drawFaces();
		}

		ofPopMatrix();
	}
	else
	{
		if (isVisible)
		    model.drawFaces();
	}
    
    if (isShadingActive) shader->end();

    ofPopMatrix();




    formatConnections();
    //BodyPart::formatConnections();
}



void Legs::drawWireframe()
{
    BodyPart::drawWireframe();
    formatConnections();
}


void Legs::formatConnections()
{
    // set connection points. These are used to position the axes of the child body parts
    for (int i = 0; i < connectingPointsAbsolute.size(); i++)
    {
        // rotate and position the absolute connection ponts
        connectingPointsAbsolute[i] = connectingPoints[i];
        connectingPointsAbsolute[i].rotate(qangle, ofVec3f(qaxis.x, qaxis.y, qaxis.z));
        connectingPointsAbsolute[i] += *originPoint; //skelJointPos;
    }
	
	
	if (isDrawDebug)
	{
		ofPushStyle();
		ofSetColor(0, 0, 255, 255);

#ifdef TARGET_OSX
		ofDrawSphere(connectingPointsAbsolute[0], 5);
#else
		ofSphere(connectingPointsAbsolute[0], 5);
#endif

		ofPopStyle();
	}
}

