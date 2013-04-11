//
//  EnemyPlane.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/9/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_EnemyPlane_h
#define FinalProjectFund2_EnemyPlane_h

#include "Plane.h"
#include <iostream>
#include <vector>
#include "Bullet.h"

class EnemyPlane : public Plane {
    
    int fireCount;
    double targetDisplaceX;
    double targetDisplaceZ;
    int fireNumber;
    std::vector<Bullet> bullets;
public:
    EnemyPlane(){
        x = -50;
        y = 7;
        z = 0;
        roll = 0;
        pitch = 0;
        wingspan = 4;
        speed = (rand()%10)*.02;
        planeYaw = 0;
        planeRed = 1;
		fireCount = 0;
		targetDisplaceX = (rand()%10)-5;
		targetDisplaceZ = (rand()%10)-5;
		fireNumber = rand()%100;
    }
    
    void adjustAttitudeFacingPlane(Plane enemy){
        double pi = 3.14159262;
        double desiredRoll = 0;
        double desiredPitch = 0;
        double deltaX = 0;
        double deltaZ = 0;
        double deltaY = 0;
        double enemyYawRad = enemy.planeYaw*3.14159262/180;
        double targetZ = enemy.z+(5+targetDisplaceX)*sin(enemyYawRad);
        double targetX = enemy.x-(5+targetDisplaceZ)*cos(enemyYawRad);
        deltaZ = targetZ - z;
        deltaX = targetX - x;
        deltaY = enemy.y - y;
        double distance = sqrt(pow(deltaX,2)+pow(deltaZ,2)+pow(deltaY,2));
        double flatDistance = sqrt(pow(deltaX,2)+pow(deltaZ,2));
        if (distance<5) {
            return;
        }
        double desiredAngleRad = atan(-deltaZ/deltaX);
        if (deltaX == 0){
            if (deltaZ>0) desiredAngleRad = 0.5*pi; else desiredAngleRad = 1.5*pi;
        }
        if (deltaX<0) desiredAngleRad += pi;
        if (desiredAngleRad < 0) {
            desiredAngleRad+=2*pi;
        }
        
        planeYaw = (desiredAngleRad*180)/pi;
        
            if (planeYaw>360) {
                planeYaw-=360;
            }
            if (planeYaw<0) {
                planeYaw+=360;
            }
        
        if (!(planeYaw<360||planeYaw>0)) {
            planeYaw = 0;
        }
        
        double pitchRad = asin((enemy.y - y)/distance);
        if (!(pitchRad>-1||pitchRad<1)) {
            std::cout<<pitchRad;
            if (enemy.y>y+3) {
                pitch = 10;
            }else if (enemy.y<y-3){
                pitch = -10;
            }else{
                pitch = 0;
            }
        }else{
        pitch = pitchRad*180/pi;
            if (pitch>30) {
                pitch = 30;
            }
            if (pitch<-30) {
                pitch = -30;
            }
        }
        //pitch = (pitchRad*180)/pi;
        if ((fireCount%100) == fireNumber) {
            speed*=3;
            bullets.push_back(fireBullet());
            speed/=3;
        }
        fireCount++;
    }
    
    void drawBullets(){
        for (int i = 0; i<bullets.size(); i++) {
            if (i<bullets.size()-3) {
                continue;
            }
            bullets[i].drawBullet();
            bullets[i].moveBullet();
        }
    }
};

#endif
