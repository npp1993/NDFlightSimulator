//
//  TerrainTile.h
//
//  Created by Nathaniel Pawelczyk on 3/26/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
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
		static const int tileSize = 1.0;

		float red;
		float green;
		float blue;
		float alpha;

		float z1;
		float z2;
		float z3;
		float z4;

		int hasTree;
		int hasBuilding;
        int hasSilo;

		TerrainTile()
		{
			z1 = 0;
			z2 = 0;
			z3 = 0;
			z4 = 0;

			red = 0.1 + (rand()%10)/18.0;
			green = 0.15 + (rand()%10)/18.0;
			blue = 0.05 + (rand()%10)/18.0;
			alpha = 1.0;

			hasTree = 0;
			hasBuilding = 0;
			hasSilo = 0;
		}

		float averageHeight()
		{
			return (z1 + z2 + z3 + z4)/4.0f;
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

#endif
