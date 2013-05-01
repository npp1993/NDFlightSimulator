//
//  Tree.h
//  GraphicsExample
//
//  Created by Matt McGlynn on 3/29/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef Tree_H
#define Tree_H

#include <iostream>
#include "GraphicsHeader.h"
class Tree {
    
  
public:
    float height;
    float baseWidth;
    float leavesWidth;
    float x;
    float y;
    float z;
    Tree(){
        height = 2;
        baseWidth = 0.5;
        leavesWidth = 1;
        x = 0;
        y = 0;
        z = 0;
    }
    void drawTree(){
        
        glTranslatef(x, z, y);
        glPushMatrix();
        glRotatef(-90, 1, 0, 0);
        GLUquadricObj *quadratic;
        quadratic = gluNewQuadric();
        glColor4f(.2, .15, 0.05, 1);
        glutSolidCone(baseWidth, height*2, 2, 4);
        glTranslatef(0, 0, 3*height/4);
        glColor4f(0, .2, 0, 1);
        glutSolidCone(leavesWidth, height*2, 5, 5);
        glTranslatef(0, 0, -3*height/4);
        glPopMatrix();
        glTranslatef(-x, -z, -y);
    }
};

#endif /* defined(__GraphicsExample__Tree__) */
