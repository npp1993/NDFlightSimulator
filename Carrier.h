//
//  Carrier.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/22/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Carrier_h
#define FinalProjectFund2_Carrier_h
#include "GraphicsHeader.h"
#include <math.h>
#include <iostream>
class Carrier {
    
    
public:
    double x;
    double y;
    double z;
    double length;
    double radarDirection;
    double radarSpeed;
    Carrier(){
        x = 0;
        y = 0;
        z = 0;
        length = 100;
        radarDirection = 0;
        radarSpeed = ((rand()%100))/100 + 1;
        
    }
    
void drawCarrier(){
    radarDirection+=radarSpeed;
    if(radarDirection>360) radarDirection-=360;
    glTranslatef(x, y, z);
    double widthMaxX = length/7;
    double widthMinX = -length/7;
    double lengthMaxZ = length/2;
    double lengthMinZ = -length/2;
    double upperCenterPoint = (length*3)/16;
    double lowerCenterPoint = -(length*3)/16;
    double height = length/12;
    double hullSink = -length/13;
    glBegin(GL_TRIANGLES);
    glColor3f(.16, .16, .16);
    //Bottom Triangle
    glVertex3d(widthMinX, height, lengthMinZ);
    glVertex3d(0, hullSink, lowerCenterPoint);
    glVertex3d(widthMaxX, height, lengthMinZ);
    //Upper Triangle
    glVertex3d(widthMinX, height, lengthMaxZ);
    glVertex3d(0, hullSink, upperCenterPoint);
    glVertex3d(widthMaxX, height, lengthMaxZ);
    glEnd();
    glBegin(GL_QUADS);
    //First Side Panel
    glVertex3d(0, hullSink, upperCenterPoint);
    glVertex3d(0, hullSink, lowerCenterPoint);
    glVertex3d(widthMaxX, height, lengthMinZ);
    glVertex3d(widthMaxX, height, lengthMaxZ);
    //Other side panel
    glVertex3d(0, hullSink, upperCenterPoint);
    glVertex3d(0, hullSink, lowerCenterPoint);
    glVertex3d(widthMinX, height, lengthMinZ);
    glVertex3d(widthMinX, height, lengthMaxZ);
    //Top sheet
    glColor3f(.07, .07, .07);
    glVertex3d(widthMaxX, height, lengthMinZ);
    glVertex3d(widthMinX, height, lengthMinZ);
    glVertex3d(widthMinX, height, lengthMaxZ);
    glVertex3d(widthMaxX, height, lengthMaxZ);
    glColor3f(.18, .18, .18);
    //Draw Command Tower
    double baseX = 2*widthMaxX/4;
    double baseY = lengthMaxZ/2;
    double baseZ = height;
    double cubeHeight = height/2;
    double cubeWidth = widthMaxX/2;
    double maxX = baseX + cubeWidth;
    double maxY = baseY + cubeWidth;
    double maxZ = baseZ + cubeHeight;
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);
    glBegin(GL_QUADS);
    
    //X face
    glVertex3d(baseX, baseZ, baseY);
    glVertex3d(baseX, baseZ, maxY);
    glVertex3d(baseX, maxZ, maxY);
    glVertex3d(baseX, maxZ, baseY );
    
    
    //Y face
    glVertex3d(baseX, baseZ, baseY );
    glVertex3d(maxX, baseZ, baseY );
    glVertex3d(maxX, maxZ, baseY );
    glVertex3d(baseX, maxZ, baseY );
    
    //maxX face
    glVertex3d(maxX, baseZ, baseY );
    glVertex3d(maxX, baseZ, maxY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(maxX, maxZ, baseY );
    
    //maxY face
    glVertex3d(baseX, baseZ, maxY);
    glVertex3d(maxX, baseZ, maxY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(baseX, maxZ, maxY);
    
    //Building Top
    glVertex3d(baseX, maxZ, baseY);
    glVertex3d(maxX, maxZ, baseY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(baseX, maxZ, maxY);
    //glPushMatrix();
    baseX = maxX;
    baseY = maxY;
    baseZ = maxZ;
    cubeHeight = height*1.2;
    cubeWidth = widthMaxX/80;
    maxX = baseX - cubeWidth;
    maxY = baseY - cubeWidth;
    maxZ = baseZ + cubeHeight;
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glFrontFace(GL_CW);
    
    //X face
    glVertex3d(baseX, baseZ, baseY);
    glVertex3d(baseX, baseZ, maxY);
    glVertex3d(baseX, maxZ, maxY);
    glVertex3d(baseX, maxZ, baseY );
    
    
    //Y face
    glVertex3d(baseX, baseZ, baseY );
    glVertex3d(maxX, baseZ, baseY );
    glVertex3d(maxX, maxZ, baseY );
    glVertex3d(baseX, maxZ, baseY );
    
    //maxX face
    glVertex3d(maxX, baseZ, baseY );
    glVertex3d(maxX, baseZ, maxY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(maxX, maxZ, baseY );
    
    //maxY face
    glVertex3d(baseX, baseZ, maxY);
    glVertex3d(maxX, baseZ, maxY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(baseX, maxZ, maxY);
    
    //Building Top
    glVertex3d(baseX, maxZ, baseY);
    glVertex3d(maxX, maxZ, baseY);
    glVertex3d(maxX, maxZ, maxY);
    glVertex3d(baseX, maxZ, maxY);

    glEnd();
      glPushMatrix();
    glTranslatef(baseX, maxZ-cubeHeight/2, maxY+length/100);
  
    glRotatef(radarDirection, 0,1, 0);
    glutSolidCone(length/32, length/50, 20, 20);
   
    glTranslatef(-baseX, -(maxZ-cubeHeight/2), -(maxY+length/100));
     glPopMatrix();
    
    
    glTranslatef(-x, -y, -z);
}
};

#endif
