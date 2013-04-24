//
//  Bullet.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 3/31/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Bullet_h
#define FinalProjectFund2_Bullet_h

#include "GraphicsHeader.h"

class Bullet {
    
    
public:
    
    double x;
    double y;
    double z;
    double radius;
    double speed;
    double yaw;
    double pitch;
    double hasHit = 0;
    
    
    Bullet(){radius = 0.4;};
    Bullet(double xPos, double yPos, double zPos, double speedD, double yawA, double pitchA){
        x = xPos;
        y = yPos;
        z = zPos;
        speed = speedD;
        yaw = yawA;
        pitch = pitchA;
        radius = .4;
        
    }
    void moveBullet(){
        double pi = 3.14159262;
        double yawRad = (yaw * pi)/180;
        double pitchRad = (pitch *pi)/180;
        x = x + speed*cos(yawRad);
        z = z - speed*sin(yawRad);
        y = y + speed*sin(pitchRad);
    }
    void drawBullet(){
        
        glTranslatef(x, y, z);
        glColor4f(.16, .15, .15, .6);
        glPushMatrix();
        glutSolidSphere(radius, 20, 20);
        
        
        
        
        
        glPopMatrix();
        glTranslatef(-x, -y, -z);
    }
    
};

#endif
