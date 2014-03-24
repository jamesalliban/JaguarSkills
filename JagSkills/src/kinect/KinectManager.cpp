//
//  KinectManager.cpp
//  JagSkills_puppet
//
//  Created by James Alliban's MBP on 18/03/2014.
//
//

#include "KinectManager.h"
#include "ofxSkeletonRecorder.h"


void KinectManager::setup()
{
    kinectRecorder.setup();
}



void KinectManager::update()
{
    if (kinectRecorder.isPlaybackActive())
    {
        skeletons.clear();
        skeletons = kinectRecorder.getRecordedSkeletons();
        formatSkeletonData();
    }
}



void KinectManager::draw()
{
    
}


void KinectManager::formatSkeletonData()
{
    for (int i = 0; i < skeletons.size(); i++)
    {
        SkeletonDataObject *skeletonData = &skeletons[i];
        
        for (int j = 0; j < skeletonData->skeletonPositions.size(); j++)
        {
            // currently the range of joint positions is x:0 - 320, y:0 - 240 and z:0 - 30000. This is stupid. The first thing we
            // will do is convert this to x:-160 - 160, y:-120 - 120 and z:-15000 - 15000. This will make scaling easier
            ofVec3f *joint = &skeletonData->skeletonPositions[j];
            
            // this places the user in the centre of the scene. The skeleton range is usually 1-320. This sets the range to -160 - 160
            joint->x -= 160;
            //joint->y -= 120;
            //joint->z -= 15000;
            
            
            // y comes in upside down and z is in 10ths of a millimeter - this fixes that
            joint->y -= 240;
            joint->y *= -1;
            joint->z = (joint->z * -1) * skeletonZReductionScale;
            
            //            // rotate skeleton
            joint->rotate(skeletonRotDegrees, ofVec3f(0.0, 0.0, 0.0), ofVec3f(1, 0, 0));
//
//            // offset positions
//            joint->x += jointPosOffset.x; //userMan->skeletonPosOffsetX[clientID];
            joint->y += jointPosOffset.y; // -65;
            joint->z += jointPosOffset.z; // 92;
//
//            // adjust scale
//            if (isSkelScaled)
//            {
//                joint->x *= userMan->skeletonScale[clientID];
//                joint->y *= userMan->skeletonScale[clientID];
//                joint->z *= userMan->skeletonScale[clientID];
//            }
//
//            if (isSkelScaleFromZ)
//            {
//                //capture the hip vector then fix the z scaling bug
//                if (i == 0) hipOffset = ofVec3f(jointPositions[CELL_HIP_CENTRE]);
//                performZScaleFix(&jointPositions[i]);
//            }
//
//            if (isZSpreadOffset)
//            {
//                joint->z = ofMap(joint->z, zSpreadInputMin, zSpreadInputMax, zSpreadOutputMin, zSpreadOutputMax);
//            }
//
//            //joint->x += (UserManager::xSpreadRangeNormalMax[clientID]);// * userMan->skeletonScale[clientID]); // * 0.5;
//
//            if (isXSpreadOffset)
//            {
//                float zPosNorm = ofMap(joint->z, zSpreadOutputMin, zSpreadOutputMax, 0, 1);
//                float xPosOffset = (userMan->skeletonPosOffsetX[clientID]) * userMan->skeletonScale[clientID];
//                float xPosNorm = ofMap(joint->x, UserManager::xSpreadRangeNormalMin[clientID] + xPosOffset, UserManager::xSpreadRangeNormalMax[clientID] + xPosOffset, 0, 1);
//                float frontXpos = ofMap(xPosNorm, 0, 1, UserManager::xFrontSkewedMin[clientID], UserManager::xFrontSkewedMax[clientID]);
//                float backXpos = ofMap(xPosNorm, 0, 1, UserManager::xBackSkewedMin[clientID], UserManager::xBackSkewedMax[clientID]);
//
//                if (clientID == 0 && i == CELL_HIP_CENTRE) printf("zPosNorm:%f, xPosNorm:%f, xPosOffset:%f, frontXpos:%f, backXPos:%f \n", zPosNorm, xPosNorm, xPosOffset, frontXpos, backXpos);
//
//                if (i == CELL_HIP_CENTRE)
//                {
//                    float hipCentreX = joint->x;
//                    float newHipCentreX = ofLerp(frontXpos, backXpos, zPosNorm);
//                    hipXSpreadOffset = newHipCentreX - hipCentreX;
//                    joint->x = newHipCentreX;
//                    joint->x += userMan->skeletonPosOffsetX[clientID] * userMan->skeletonScale[clientID];
//                }
//                else
//                {
//                    
//                    joint->x += hipXSpreadOffset;
//                    joint->x += userMan->skeletonPosOffsetX[clientID] * userMan->skeletonScale[clientID];
//                }
//            }
        }
    }
}
