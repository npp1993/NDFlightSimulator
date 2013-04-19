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
	public:

		WaterTile(float size) : TerrainTile(size)
		{
			red = 0;
			green = 0;
			blue = 0.1;
			alpha = 0.4;
		}
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
