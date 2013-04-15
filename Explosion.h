//
//  Explosion.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/10/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Explosion_h
#define FinalProjectFund2_Explosion_h
#include "GraphicsHeader.h"


class Explosion {
    
    
public:
    double x;
    double y;
    double z;
    
    Explosion(double newX,double newY,double newZ){
        x = newX;
        y = newY;
        z = newZ;
    }
    void drawExplosion(){
        glTranslatef(x, y, z);
        glColor3f(.7, .3, .3);
        //glutSolidSphere(15, 20, 20);
        glTranslatef(-x, -y, -z);
    }   
};
#endif
