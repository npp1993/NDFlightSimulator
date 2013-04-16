//
//  WaterTile.h
//
//  Created by Nathaniel Pawelczyk on 4/11/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef WaterTile_H
#define WaterTile_H

#include <iostream>
#include "GraphicsHeader.h"
#include "TerrainTile.h"
#include <math.h>
#include <iostream>
#include <vector>



class WaterTile : public TerrainTile
{
    
    WaterTile() : TerrainTile(0, 0, size)
	{
		red = 0;
		green = 0;
		blue = 0.1;
		alpha = 0.4;

		z1 = 0;
		z2 = 0;
		z3 = 0;
		z4 = 0;

		x=minX;
		y=minY;

		xMax =maxX;
		yMax =maxY;
    }

    void drawTile()
	{
        glColor4f(red, green, blue, alpha);
        glVertex3f(x, z1, y);
        glVertex3f(x, z2, yMax);
        glVertex3f(xMax, z3, yMax);
        glVertex3f(xMax, z4, y);
    }
    
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
