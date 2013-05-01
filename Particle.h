//
//  Particle.h
//
//  Created by Nathaniel Pawelczyk on 4/10/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "GraphicsHeader.h"

class Particle
{
private:
    float vx;
    float vy;
    float vz;
    
    float drag;
    float gravity;
    
    float fade;
    
public:
    float r;
    float g;
    float b;
    
    float x;
    float y;
    float z;
    int splash;
    float life;
    
    Particle(float xo, float yo, float zo, float vxo, float vyo, float vzo,int sp)
    {
        r = 0.8 + float(rand()%100-50.0f)/300.0f;  //randomize
        g = 0.2;
        b = 0.0;
    
        
        x = xo;  //initialize position
        y = yo;
        z = zo;
        
        vx = vxo + float((rand()%50)-25.0)/30.0f;  //initialize velocity
        vy = vyo + float((rand()%50)-25.0)/30.0f;
        vz = vzo + float((rand()%50)-25.0)/30.0f;
        
        drag = 0.3;
        gravity = 0.05;
        
        life = 1.0;
        fade = 0.02 + float(rand()%10)/300.0f;
        splash = sp;
        if (splash) {
            r = 1;
            b = 1;
            g = 1;
            fade = 0.07+float(rand()%10)/300.0f;
        }
    }
    
    bool advanceState()  //move particle and reduce life, return false if life <= 0
    {
        if(life > 0)
        {
            x += vx;  //advance position based on velocity
            y += vy;
            z += vz;
            
            vx += fabs((long)vx) * ((vx > 0) ? (-1*drag) : drag);  //apply drag in x and z directions opposite to velocity
            vz += fabs((long)vz) * ((vz > 0) ? (-1*drag) : drag);
            
            vy -= gravity;  //apply gravity in y direction
			
            life -= fade;  //fade particle out
            
            if(!splash) g = ((1-life)/1)*.5+0.2;
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

#endif