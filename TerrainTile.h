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
		float tileSize;

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

		TerrainTile(float size)
		{
			tileSize = size;

			z1 = 0;
			z2 = 0;
			z3 = 0;
			z4 = 0;

			red = 0.1;
			green = 0.15;
			blue = 0.05;
			alpha = 1.0;

			hasTree = 0;
			hasBuilding = 0;
		}

		void drawTile(float x, float y)  //draw tiles relative to the x and y offset of the user's plane
		{
			glColor4f(red, green, blue, alpha);
			glVertex3f(x, z1, y);
			glVertex3f(x, z2, y + tileSize);
			glVertex3f(x + tileSize, z3, y + tileSize);
			glVertex3f(x + tileSize, z4, y);
		}
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
