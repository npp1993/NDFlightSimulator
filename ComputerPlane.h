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
#include "Bullet.h" 
#include "GraphicsHeader.h"
#include "ExplosionManager.h"

class ComputerPlane : public Plane {
    
    int fireCount = 0;
    double targetDisplaceX = 0; //(rand()%10)-5;
    double targetDisplaceZ = 0; //(rand()%10)-5;
    
    int fireNumber = rand()%30;
    
    
    
    
    std::vector<Bullet> bullets;
    
public:
    ExplosionManager *explosives;
    double defaultSpeed = 6*.12 + .12;
    double manuverability = 1;
    double isLock = 0;
     Plane* enemyPlane;
    double cruiseSpeed;
    int timer;
    ComputerPlane(){
        x = -50;
        y = 7;
        z = 0;
        roll = 0;
        pitch = 0;
        wingspan = 4;
        speed = defaultSpeed+((rand()%5)*.06);
        cruiseSpeed = speed;
        planeYaw = 0;

        
    }
    void huntEnemyPlane(){
        adjustAttitudeFacingPlane(*enemyPlane);
    }
    
    void adjustAttitudeFacingPlane(Plane enemy){
        if (timer) {
            //speed = ((300-timer)/300)*defaultSpeed;
            timer--;
            return;
        }
        double pi = 3.14159262;
        double deltaX = 0;
        double deltaZ = 0;
        double deltaY = 0;
        double enemyYawRad = enemy.planeYaw*3.14159262/180;
        double targetZ = enemy.z+(targetDisplaceX)*sin(enemyYawRad);
        double targetX = enemy.x-(targetDisplaceZ)*cos(enemyYawRad);
        deltaZ = targetZ - z;
        deltaX = targetX - x;
        deltaY = enemy.y - y;
        double distance = sqrt(pow(deltaX,2)+pow(deltaZ,2)+pow(deltaY,2));
        double flatDistance = sqrt(pow(deltaX,2)+pow(deltaZ,2));
        if (flatDistance<30) {
            //speed = (enemy.speed+speed)/2;
            if (speed<enemy.speed){
                speed = enemy.speed;
            }
            if (speed>defaultSpeed) {
                speed = defaultSpeed;
            }
        }else{
            speed = defaultSpeed;
        }
        if (dead) {
            speed = 0;
        }
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
        double maxDelta = .6*manuverability;
        double desiredRoll = 0;
        double planeYawDesired = (desiredAngleRad*180)/pi;

        if (((planeYawDesired-planeYaw)<180)&&((planeYawDesired-planeYaw)>0)) {
            if (abs(planeYawDesired-planeYaw)>1) {
                planeYaw+=maxDelta;
                desiredRoll = -70;
            }else{
                desiredRoll = 0;
            }
        }else{
            if (abs(planeYawDesired-planeYaw)>1) {
                planeYaw-=maxDelta;
                desiredRoll = 70;
            }
            else{
                desiredRoll = 0;
            }
        }
        //Handle shifting to desired roll
        double rollDelta = 1.3*manuverability;
        if (desiredRoll>roll) {
            if(abs(desiredRoll-roll)>2){
                roll+=rollDelta;
            }
        }
        if (desiredRoll<roll) {
            if(abs(desiredRoll-roll)>2){
                roll-=rollDelta;
            }
        }
        
        //******************************
        
            if (planeYaw>360) {
                planeYaw-=360;
            }
            if (planeYaw<0) {
                planeYaw+=360;
            }
        
        if (!(planeYaw<360||planeYaw>0)) {
            planeYaw = 0;
        }
        
        double pitchDelta = 1.4*manuverability;
        double pitchRad = asin((enemy.y - y)/distance);
        double desiredPitch = 0;
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
        desiredPitch = pitchRad*180/pi;
            if (y < 50&&(x>-200&&x<200)&&(z>-200&&z<200)) {
                desiredPitch = 0;
            }
            if (y < 45&&(x>-200&&x<200)&&(z>-200&&z<200)) {
                desiredPitch = 5;
            }
            if (desiredPitch>pitch) {
                if(abs(desiredPitch-pitch)>2){
                pitch+=pitchDelta;
                }
            }
            if (desiredPitch<pitch) {
                if(abs(desiredPitch-pitch)>2){
                    pitch-=pitchDelta;
                }
            }
            if (pitch>30) {
                pitch = 30;
            }
            if (pitch<-30) {
                pitch = -30;
            }
        }
        
        //pitch = (pitchRad*180)/pi;
        if ((abs(planeYawDesired-planeYaw)<2)&& (abs(desiredPitch-pitch)<2)&&flatDistance<100) {
            if ((fireCount%20) == fireNumber) {
                speed*=2;
                bullets.push_back(fireBullet());
                speed/=2;
            }
            
        }
        if ((abs(planeYawDesired-planeYaw)<20)&&abs(y-(*enemyPlane).y)<20) {
            if(flatDistance<200){
                isLock = 1;
            }
        }
        
        fireCount++;
    }
    
    void drawBullets(){
        for (int i = 0; i<bullets.size(); i++) {
            if (bullets.size()<1) {
                break;
            }
            if (bullets.size()>10) {
                bullets.erase(bullets.begin());
            }
            if ((abs(bullets[i].x-enemyPlane->x)<6)&&(abs(bullets[i].z-enemyPlane->z)<6)&&(abs(bullets[i].y-enemyPlane->y)<3)&&!bullets[i].hasHit) {
                bullets[i].radius = .8;
                enemyPlane->dead = 1;
                enemyPlane->pitch = -30;
                enemyPlane->roll = 0;
                //enemyPlane->speed= 0;
                bullets.erase(bullets.begin()+i);
                //bullets[i].speed = 0;
                //bullets[i].hasHit = 1;
                double hitX,hitY,hitZ;
                hitX = enemyPlane->x;
                hitY = enemyPlane->y;
                hitZ = enemyPlane->z;
                (*explosives).generateExplosion(hitX, hitY, hitZ, 0, 0, 0);
                
            }else{
                bullets[i].moveBullet();
            }
            bullets[i].drawBullet();
            
        }
    }

    /*
    void drawUserBullets(std::vector <ComputerPlane> * enemies){
        for (int k = 0; k<(*enemies).size(); k++) {
            ComputerPlane *enemyPlane = &((*enemies)[k]);
            for (int i = 0; i<userBullets.size(); i++) {
                if (userBullets.size()<1) {
                    break;
                }
                if (userBullets.size()>10) {
                    userBullets.erase(userBullets.begin());
                }
                if ((abs(userBullets[i].x-enemyPlane->x)<6)&&(abs(userBullets[i].z-enemyPlane->z)<6)&&(abs(userBullets[i].y-enemyPlane->y)<3)&&!userBullets[i].hasHit) {
                    userBullets[i].radius = .8;
                    enemyPlane->dead = 1;
                    enemyPlane->speed= 0;
                    userBullets[i].speed = 0;
                    userBullets[i].hasHit = 1;
                }else{
                    userBullets[i].moveBullet();
                }
                userBullets[i].drawBullet();
                
            }
            
        }
    }
     */

};

#endif
