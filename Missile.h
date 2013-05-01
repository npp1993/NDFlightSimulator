//
//  Missle.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/30/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Missle_h
#define FinalProjectFund2_Missle_h
#include "ComputerPlane.h"

class Missile : public ComputerPlane {
    
    
public:
    double missileSpeed;
    double missileTimer;
    Missile() : ComputerPlane() {
        wingspan = .5;
    };
    void moveMissile(){
        huntEnemyPlane();
        speed = missileSpeed*(missileTimer/100) + defaultSpeed*1.5;
        movePlane();
        missileTimer++;
    }
    void drawMissile(){
        glTranslatef(x, y, z);
        glColor3f(.16, .16, .16);
        
        glPushMatrix();
        glRotatef(planeYaw, 0, 1, 0);
        glRotatef(roll, 1, 0, 0);
        glRotatef(pitch, 0, 0, 1);
        
        //Draw Engines
        glColor3f(.1, .1, .1);
        
        glTranslatef(0, 0, -wingspan/2);
        glRotatef(90, 0, 1, 0);
        glutSolidCone(wingspan/10, wingspan/.7, 10, 10);
        glColor3f(1, .25, 0);
        glutSolidSphere(wingspan/11, 20, 20);
        glColor3f(.1, .1, .1);
        glRotatef(-90, 0, 1, 0);
        glTranslatef(0, 0, wingspan/2);
        glPopMatrix();
        glTranslatef(-x, -y, -z);
    }
};


#endif
