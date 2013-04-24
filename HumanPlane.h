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
class HumanPlane : public ComputerPlane {
    
    
public:
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
