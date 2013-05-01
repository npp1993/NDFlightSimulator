//
//  HumanPlane.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/23/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_HumanPlane_h
#define FinalProjectFund2_HumanPlane_h
#include "ComputerPlane.h"
#include "Missile.h"
class HumanPlane : public ComputerPlane {

    
    
public:
    std::vector<Bullet> userBullets;
    std::vector<Missile> userMissiles;
    int health;
    double desiredPitch;
    double desiredRoll;
    double hitCount = 300;
    Plane *lockOnTarget;
    int humanLock;
    HumanPlane(){
        x = -100;
        y = 5;
        z = 0;
        roll = 0;
        pitch = 0;
        wingspan = 8;
        speed = .8;
        planeYaw = 0;
        planeRed = 0;
        health = 100;
        desiredPitch = 0;
        desiredRoll = 0;
        manuverability = 2;
        humanLock = 0;
        
    }
    void manageHealth(){
        if (dead) {
            health-=10;
            dead = 0;
        }
        drawHealth();
    }
    void drawHealth(){
        glTranslatef(x, y+20, z);
        glColor3f(1, 0, 0);
        glutSolidSphere(20, 20, 20);
        glColor3f(0, 1, 0);
        glutSolidSphere((health/100)*20, 20, 20);
        glTranslatef(-x, -(y+20), -z);
    }
    
    void fireMissile(std::vector <ComputerPlane> * enemies){
        if(!humanLock) return;
        Missile newMissile;
        newMissile.y = y;
        newMissile.z = z;
        newMissile.x = x;
        newMissile.pitch = 0;
        newMissile.planeYaw = planeYaw;
        newMissile.timer = 10;
        newMissile.missileTimer = 0;
        newMissile.missileSpeed = 20;
        newMissile.wingspan = 5;
        newMissile.manuverability = 3.4;
        newMissile.enemyPlane = lockOnTarget;
        //newMissile.enemyPlane = &((*enemies)[rand()%((*enemies).size()-1)]);
        userMissiles.push_back(newMissile);
    }
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
                    enemyPlane->pitch = -40;
                    //enemyPlane->speed= 0;
                    userBullets[i].speed = 0;
                    userBullets[i].hasHit = 1;
                    userBullets.erase(userBullets.begin()+i);
                }else{
                    userBullets[i].moveBullet();
                }
                userBullets[i].drawBullet();
                
            }
            
        }
        lockOn(enemies);
        drawMissiles();
    }
    
    void lockOn(std::vector <ComputerPlane> * enemies){
        humanLock = 0;
        isLock = 0;
        for (int i = 0; i<(*enemies).size(); i++) {
            enemyPlane = &((*enemies)[i]);
            if((*enemyPlane).dead)continue;
            double deltaZ = (*enemyPlane).z-z;
            double deltaX = (*enemyPlane).x-x;
            double pi = 3.14159262;
            double flatDistance = sqrt(pow(deltaX,2)+pow(deltaZ,2));
            //*********
            double desiredAngleRad = atan(-deltaZ/deltaX);
            if (deltaX == 0){
                if (deltaZ>0) desiredAngleRad = 0.5*pi; else desiredAngleRad = 1.5*pi;
            }
            if (deltaX<0) desiredAngleRad += pi;
            if (desiredAngleRad < 0) {
                desiredAngleRad+=2*pi;
            }
            double planeYawDesired = (desiredAngleRad*180)/pi;
            if(planeYaw<0){
                planeYaw+=360;
            }
            if(planeYaw>360){
                planeYaw-=360;
            }
            //------
            //if(flatDistance<20)isLock=1;
            if ((abs(planeYawDesired-planeYaw)<10||(abs(planeYawDesired-planeYaw)>350))&&abs(y-(*enemyPlane).y)<80) {
                if(flatDistance<400){
                    isLock = 1;
                }
            }
            if(isLock){
                lockOnTarget = enemyPlane;
                Plane coord = *enemyPlane;
                glTranslatef(coord.x, coord.y, coord.z);
                glColor3f(1, 0, 0);
                glRotatef(90, 0, 1, 0);
                glutSolidTorus(2, 20, 20, 20);
                glRotatef(-90, 0, 1, 0);
                glTranslatef(-coord.x, -coord.y, -coord.z);
                humanLock = 1;
                return;
            }
            
            
            //if (temp.isLock) {
            //    lockOnTarget = temp.enemyPlane;
            //    humanLock = 1;
            //}
        }
    }
    
    void drawMissiles(){
        for (int k = 0; k<userMissiles.size(); k++) {
            Plane *enemyPlane = userMissiles[k].enemyPlane;
            if ((abs(userMissiles[k].x-enemyPlane->x)<6)&&(abs(userMissiles[k].z-enemyPlane->z)<6)&&(abs(userMissiles[k].y-enemyPlane->y)<3)) {
                enemyPlane->dead = 1;
                //enemyPlane->speed= 0;
                enemyPlane->pitch= -30;
                userMissiles[k].speed = 0;
                userMissiles.erase(userMissiles.begin()+k);
                (*explosives).generateExplosion(enemyPlane->x, enemyPlane->y, enemyPlane->z, 0, 0, 0);
            }else{
                userMissiles[k].moveMissile();
            }
            userMissiles[k].drawMissile();
            if(userMissiles[k].missileTimer>200) userMissiles.erase(userMissiles.begin()+k);
            
        }
        
        
    }

    void convertDesiredToActual(){
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
        double pitchDelta = 1.2*manuverability;
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
    
    void userFire(){
        double tempSpeed = speed;
        speed = .4;
        Bullet x = fireBullet();
        x.pitch = pitch * (90 - abs(roll))/90;
        userBullets.push_back(x);
        speed = tempSpeed;
    
    }
     
};

#endif
