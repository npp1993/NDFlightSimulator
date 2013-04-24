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
#include <math.h>

class Explosion {
    
    
public:
    double x;
    double y;
    double z;
    double radius;
    
    Explosion(double newX,double newY,double newZ){
        x = newX;
        y = newY;
        z = newZ;
        radius = 0;
    }
    void drawExplosion(){
        radius+=.02;
        if(radius>9) return;
        glTranslatef(x, y, z);
        
        for(int i = 0; i<300; i++){
            double xOffset = (((rand()%500)-250)/100)*radius/3;
            double yOffset = (((rand()%500)-250)/100)*radius/3;
            double zOffset = (((rand()%500)-250)/100)*radius/3;
            double distance = sqrt(pow(xOffset, 2)+pow(xOffset, 2)+pow(xOffset, 2));
            glTranslatef(xOffset, yOffset, zOffset);
            glutSolidSphere(radius/2+((rand()%10)/10)*radius/2, 20, 20);
            double red = distance/9;
            double green = distance/9;
            glColor4f(red,green, .1,.1);
            glTranslatef(-xOffset, -yOffset, -zOffset);
        }
        glTranslatef(-x, -y, -z);
    }   
};
#endif
