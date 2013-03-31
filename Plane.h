//
//  Plane.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 3/30/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Plane_h
#define FinalProjectFund2_Plane_h

#include <math.h>
#include "GraphicsHeader.h"

class Plane {
    
    
public:
    double x;
    double y;
    double z;
    double roll;
    double pitch;
    double yaw;
    double wingspan;
    double speed;
    double planeYaw;
    Plane(){
        x = -100;
        y = 5;
        z = 0;
        roll = 0;
        pitch = 0;
        wingspan = 10;
        speed = .2;
        planeYaw = 0;
    }
    
    void movePlane(){
        if (pitch>60) {
            pitch=60;
        }
        if (roll>90){
            roll = 90;
        }
        if (pitch<-60) {
            pitch= -60;
        }
        if (roll<-90){
            roll = -90;
        }
        if (abs(roll)<10){
            roll/=1.002;
        }
        if (abs(pitch)<10){
            pitch/=1.002;
        }
        double pi = 3.14159262;
        
        //yaw is the cross product of roll and pitch
        
        double rollRad = (roll*pi)/180;
        double pitchRad = (pitch*pi)/180;
        //yaw += asin(sin(rollRad)*sin(pitchRad))*6;
        planeYaw-=roll/30*pitch/30;
        double yawRad = (planeYaw*pi)/180;
        //yawRad = asin(sin(rollRad)*sin(pitchRad))*6;
        //Motion based on yaw
        x = x + speed*cos(yawRad);
        z = z - speed*sin(yawRad);
        //std::cout<<planeYaw<<"\n";
        //Motion based on pitch
        y = y + speed*sin(pitchRad)-speed*abs(sin(rollRad));
        
        
        //std::cout<<y;
        
    }
    
    void drawPlane(){
        glTranslatef(x, y, z);
        glColor3f(.16, .16, .16);
        
        glPushMatrix();
        glRotatef(planeYaw, 0, 1, 0);
        glRotatef(roll, 1, 0, 0);
        glRotatef(pitch, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        //Draw main wing
        glVertex3f(-.5*wingspan, 0, -wingspan);
        glVertex3f(-.5*wingspan, 0, wingspan);
        glVertex3f(+.5*wingspan, 0, 0);
        
        //Draw fins
        glVertex3f(-.5*wingspan, 0, -wingspan/2);
        glVertex3f(.0*wingspan, 0, -wingspan/2);
        glVertex3f(-.5*wingspan, wingspan/3.5, -wingspan/2);
        glVertex3f(-.5*wingspan, 0, wingspan/2);
        glVertex3f(.0*wingspan, 0, wingspan/2);
        glVertex3f(-.5*wingspan, wingspan/3.5, wingspan/2);
        
        //Draw cockpit
        glColor3f(.36, .16, 0);
        glVertex3f(.46*wingspan, 0, 0);
        glVertex3f(.35*wingspan, 0, -wingspan/10);
        glVertex3f(.35*wingspan, .1*wingspan, 0);
        glVertex3f(.46*wingspan, 0, 0);
        glVertex3f(.35*wingspan, 0, wingspan/10);
        glVertex3f(.35*wingspan, .1*wingspan, 0);
        glVertex3f(.1*wingspan, 0, 0);
        glVertex3f(.35*wingspan, 0, -wingspan/10);
        glVertex3f(.35*wingspan, .1*wingspan, 0);
        glVertex3f(.1*wingspan, 0, 0);
        glVertex3f(.35*wingspan, 0, wingspan/10);
        glVertex3f(.35*wingspan, .1*wingspan, 0);
        
        glEnd();
        
        //Draw Engines
        glColor3f(.1, .1, .1);
        
        glTranslatef(-.7*wingspan, 0, -wingspan/2);
        glRotatef(90, 0, 1, 0);
        glutSolidCone(wingspan/10, wingspan/1.5, 10, 10);
        glColor3f(1, .55, 0);
        glutSolidSphere(wingspan/11, 20, 20);
        glColor3f(.1, .1, .1);
        glRotatef(-90, 0, 1, 0);
        glTranslatef(.7*wingspan, 0, wingspan/2);
        glTranslatef(-.7*wingspan, 0, wingspan/2);
        glRotatef(90, 0, 1, 0);
        glColor3f(1, .55, 0);
        glutSolidSphere(wingspan/11, 20, 20);
        glColor3f(.1, .1, .1);
        glutSolidCone(wingspan/10, wingspan/1.5, 10, 10);
        glRotatef(-90, 0, 1, 0);
        glTranslatef(.7*wingspan, 0, -wingspan/2);
        glPopMatrix();
        //
        glTranslatef(-x, -y, -z);

    }
    
};

#endif