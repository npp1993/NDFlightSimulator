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
#include <iostream>
#include <vector>

class TerrainTile {
    
	public:

		float x;
		float y;

		float tileSize;

		float xMax;
		float yMax;

		float red;
		float green;
		float blue;
		float alpha;

		float z1;
		float z2;
		float z3;
		float z4;

		double hasTree;
		double hasBuilding;

		TerrainTile(float i, float j, float size)
		{
			x = i;
			y = j;

			tileSize = size;

			xMax = x + tileSize;
			yMax = y + tileSize;

			z1 = 0;
			z2 = 0;
			z3 = 0;
			z4 = 0;

			red = 0.1;
			green = 0.15;
			blue = 0.05;
			alpha = 1;

			hasTree = 0;
			hasBuilding = 0;
		}

		void drawTile(float xOff, float yOff)
		{
			//draw tiles relative to the x and y offset of the user's plane
			glColor4f(red, green, blue, alpha);
			glVertex3f(x + xOff, z1, y + yOff);
			glVertex3f(x+xOff, z2, yMax+yOff);
			glVertex3f(xMax+xOff, z3, yMax+yOff);
			glVertex3f(xMax+xOff, z4, y+yOff);
		}
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
