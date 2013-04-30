//
//  TerrainTile.h
//  GraphicsExample
//
//  Created by Matt McGlynn on 3/26/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef TerrainTile_H
#define TerrainTile_H

#include "GraphicsHeader.h"
#include <math.h>
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

    TerrainTile()
	{
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

    void drawTile()
	{
        glColor4f(red,green,blue,alpha);
        glVertex3f(x, z1, y);
        glVertex3f(x, z2, yMax);
        glVertex3f(xMax, z3, yMax);
        glVertex3f(xMax, z4, y);
    }
    
};
#endif
