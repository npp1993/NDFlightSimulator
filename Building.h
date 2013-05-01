//
//  Building.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 3/30/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Building_h
#define FinalProjectFund2_Building_h

#include "GraphicsHeader.h"

class Building {
    
    
public:
    double x;
    double y;
    double z;
    double height;
    double maxX;
    double maxY;
    double maxZ;
    Building(){
        x = 0;
        y = 0;
        z = 0;
        height = 10;
        
    }
    void drawBuilding(){
        glColor3f(.16, .16, .16);
        double width = 2*height/10;
        maxX = x + width;
        maxY = y + width;
        maxZ = z + height;
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        //glFrontFace(GL_CW);
        glBegin(GL_QUADS);
        
        //X face
        glVertex3d(x, z, y);
        glVertex3d(x, z, maxY);
        glVertex3d(x, maxZ, maxY);
        glVertex3d(x, maxZ, y);
        
        
        //Y face
        glVertex3d(x, z, y);
        glVertex3d(maxX, z, y);
        glVertex3d(maxX, maxZ, y);
        glVertex3d(x, maxZ, y);
        
        //maxX face
        glVertex3d(maxX, z, y);
        glVertex3d(maxX, z, maxY);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(maxX, maxZ, y);
        
        //maxY face
        glVertex3d(x, z, maxY);
        glVertex3d(maxX, z, maxY);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(x, maxZ, maxY);
        
        //Building Top
        glVertex3d(x, maxZ, y);
        glVertex3d(maxX, maxZ, y);
        glVertex3d(maxX, maxZ, maxY);
        glVertex3d(x, maxZ, maxY);
        
        //Draw windows
        glColor4f(0.0f, 0.0f, .1f, .8f);
        double windowWidth = width/8;
        double windowHeight = windowWidth*2;
        for (double xStep = x+windowWidth/2; xStep<maxX; xStep+=windowWidth*2) {
            for (double zStep= z+height/6; zStep<maxZ-windowHeight; zStep+=windowHeight*2) {
                glVertex3d(xStep, zStep, y-.01);
                glVertex3d(xStep+windowWidth, zStep, y-.01);
                glVertex3d(xStep+windowWidth, zStep+windowHeight, y-.01);
                glVertex3d(xStep, zStep+windowHeight, y-.01);
                
                glVertex3d(xStep, zStep, maxY+.01);
                glVertex3d(xStep+windowWidth, zStep, maxY+.01);
                glVertex3d(xStep+windowWidth, zStep+windowHeight, maxY+.01);
                glVertex3d(xStep, zStep+windowHeight, maxY+.01);
            }
        }
        
        for (double yStep = y+windowWidth/2; yStep<maxY; yStep+=windowWidth*2) {
            for (double zStep= z+height/6; zStep<maxZ-windowHeight; zStep+=windowHeight*2) {
                glVertex3d(x-.01,zStep,yStep);
                glVertex3d(x-.01, zStep, yStep+windowWidth);
                glVertex3d(x-.01, zStep+windowHeight, yStep+windowWidth);
                glVertex3d(x-.01, zStep+windowHeight, yStep);;
                
                glVertex3d(maxX+.01,zStep,yStep);
                glVertex3d(maxX+.01, zStep, yStep+windowWidth);
                glVertex3d(maxX+.01, zStep+windowHeight, yStep+windowWidth);
                glVertex3d(maxX+.01, zStep+windowHeight, yStep);;
            }
        }
        glEnd();
    }
};




#endif
