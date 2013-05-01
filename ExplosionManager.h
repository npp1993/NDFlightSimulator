//
//  ExplosionManager.h
//
//  Created by Nathaniel Pawelczyk on 4/10/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef EXPLOSIONMANAGER_H
#define EXPLOSIONMANAGER_H

#include <vector>
#include "Explosion.h"
#include <iostream>

class ExplosionManager
{
private:
    float* camx;
    float* camy;
    float* camz;
    double* planeYaw;
    std::vector<Explosion> explosions;
    
public:
    ExplosionManager(float* cx, float* cy, float* cz,double* planeYawIn)
    {
        camx = cx;
        camy = cy;
        camz = cz;
        planeYaw = planeYawIn;
    }
    
    void generateExplosion(float x, float y, float z, float vx, float vy, float vz)  //create a new explosion
    {
        Explosion e(x, y, z, vx, vy, vz, camx, camy, camz);
        e.yawAngle = planeYaw;
        explosions.push_back(e);
    }
    
    void drawExplosions()  //draw all explosions
    {
        for(int i = 0; i < explosions.size(); i++)
        {
            if(explosions[i].drawExplosion())  //if explosion's life is over, remove it from vector of explosions
            {
                explosions.erase(explosions.begin() + i);				
            }
        }
    }
};

#endif