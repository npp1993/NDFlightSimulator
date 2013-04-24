//
//  TerrainTile.h
//  GraphicsExample
//
//  Created by Matt McGlynn on 3/26/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef TerrainTile_H
#define TerrainTile_H

#include <iostream>
#include "GraphicsHeader.h"
#include <math.h>
//#include <random>
#include <iostream>
#include <vector>



class TerrainTile {
    
public:
    float x;
    float xMax;
    float y;
    float yMax;
    float z;
    float zMax;
    float red;
    float green;
    float blue;
    float z1;
    float z2;
    float z3;
    float z4;
    float alpha;
    double hasTree;
    double hasBuilding;
    double hasSilo;
    TerrainTile(){
        alpha = 1;
        x = 0;
        xMax = 0;
        y = 0;
        yMax = 0;
        z = 0;
        zMax = 0;
        z1 = 0;
        z2 = 0;
        z3 = 0;
        z4 = 0;
		hasTree = 0;
		hasBuilding = 0;
        hasSilo = 0;
    }
    void drawTile(){
        glColor4f(red,green,blue,alpha);
        glVertex3f(x, z1, y);
        glVertex3f(x, z2, yMax);
        glVertex3f(xMax, z3, yMax);
        glVertex3f(xMax, z4, y);
        
        /*Useful for tile orientation testing
         double baseX = x;
         double baseY = y;
         glColor3f(1,1,1);
         baseX = x;
         baseY = y;
         glVertex3f(baseX, 2, baseY);
         glVertex3f(baseX, 2, baseY+2);
         glVertex3f(baseX+2, 2, baseY+2);
         glVertex3f(baseX+2, 2, baseY);
         glColor3f(1,0,0);
         baseX = x;
         baseY = yMax;
         glVertex3f(baseX, 1, baseY);
         glVertex3f(baseX, 1, baseY+2);
         glVertex3f(baseX+2, 1, baseY+2);
         glVertex3f(baseX+2, 1, baseY);
         glColor3f(0,1,0);
         baseX = xMax;
         baseY = yMax;
         glVertex3f(baseX, 1.5, baseY);
         glVertex3f(baseX, 1.5, baseY+2);
         glVertex3f(baseX+2, 1.5, baseY+2);
         glVertex3f(baseX+2, 1.5, baseY);
         glColor3f(0,0,1);
         baseX = xMax;
         baseY = y;
         glVertex3f(baseX, 1.7, baseY);
         glVertex3f(baseX, 1.7, baseY+2);
         glVertex3f(baseX+2, 1.7, baseY+2);
         glVertex3f(baseX+2, 1.7, baseY);
         */
    }
    
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
