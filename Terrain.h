//
//  Terrain.h
//
//  Created by Nathaniel Pawelczyk on 4/22/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <math.h>
#include <time.h>
#include "GraphicsHeader.h"
#include "Terrain.h"
#include "TerrainTile.h"
#include "Point.h"

using namespace std;

class Terrain
{
	private:
		int xSize;
		int ySize;
		static int const tileSize = 1; //if this is changed, make sure to change corresponding tileSize in Point and TerrainTile
		std::vector < std::vector<float> > heights;
		std::vector < std::vector<TerrainTile> > tiles;


	public:

		Terrain()
		{
			xSize = 257;
			ySize = 257;

			srand(time(NULL));

			for(int i = 0; i < xSize/tileSize; i++)
			{
				std::vector<float> temp;

				for(int j = 0; j < ySize/tileSize; j++)
				{
					temp.push_back(2.0f);
				}

				heights.push_back(temp);
			}

			
			heights[0][0] = rand() % 100 - 50;  //initialize terrain structure corner height
			heights[0][ySize-1] = rand() % 100 - 50;
			heights[xSize-1][0] = rand() % 100 - 50;
			heights[xSize-1][ySize-1] = rand() % 100 - 50;

			Point p1(0, 0);  //initial points
			Point p2(0, ySize-1);
			Point p3(xSize-1, ySize-1);
			Point p4(xSize-1, 0);

			generateTerrain(p1, p2, p3, p4);  //generate heights

			createTiles();  //create tiles from heights

			drawTerrain();  //draw tiles
		}

		void generateTerrain(Point p1, Point p2, Point p3, Point p4)  //p1 bottom left point, counterclockwise around to upper left point p4
		{
			int rectSize = abs(p1.x - p4.x);

			if(rectSize <= tileSize)  //base case
			{
				return;
			}

			int randFactor = (rand() % 10 - 3)/5;
			randFactor*=rectSize;

			float midLeft = (heights[p1.x][p1.y] + heights[p4.x][p4.y])/2;  //generate midpoint heights
			float midRight = (heights[p2.x][p2.y] + heights[p3.x][p3.y])/2;
			float midTop = (heights[p3.x][p3.y] + heights[p4.x][p4.y])/2;
			float midBottom = (heights[p1.x][p1.y] + heights[p2.x][p2.y])/2;
			float midMid = (heights[p1.x][p1.y] + heights[p2.x][p2.y] + heights[p3.x][p3.y] + heights[p4.x][p4.y])/4.0f+randFactor;

			Point midLeftPoint((p1.x+p4.x)/2, p1.y);  //generate midpoints
			Point midRightPoint((p2.x+p3.x)/2, p2.y);
			Point midTopPoint(p3.x, (p3.y+p4.y)/2);
			Point midBottomPoint(p1.x, (p1.y+p2.y)/2);
			Point midMidPoint((p1.x+p4.x)/2, (p1.y+p2.y)/2);

			//printf("left z: %f (%i, %i)  right z: %f (%i, %i)    mid: %f (%i, %i)\n", heights[p1.x][p1.y], p1.x, p1.y, heights[p2.x][p2.y], p2.x, p2.y, midBottom, midBottomPoint.x, midBottomPoint.y);

			heights[midLeftPoint.x][midLeftPoint.y] = midLeft;  //assign heights to midpoints
			heights[midRightPoint.x][midRightPoint.y] = midRight;
			heights[midTopPoint.x][midTopPoint.y] = midTop;
			heights[midBottomPoint.x][midBottomPoint.y] = midBottom;
			heights[midMidPoint.x][midMidPoint.y] = midMid;

			generateTerrain(p1, midBottomPoint, midMidPoint, midLeftPoint);  //recursive calls
			generateTerrain(midBottomPoint, p2, midRightPoint, midMidPoint);
			generateTerrain(midMidPoint, midRightPoint, p3, midTopPoint);
			generateTerrain(midLeftPoint, midMidPoint, midTopPoint, p4);
		}

		void createTiles()
		{
			for(int i = 0; i < heights.size() - 1; i++)
			{
				std::vector<TerrainTile> temp;

				for(int j = 0; j < heights[i].size() - 1; j++)
				{
					TerrainTile newTile;

					newTile.z1 = heights[i][j];
					newTile.z2 = heights[i][j+1];
					newTile.z3 = heights[i+1][j+1];
					newTile.z4 = heights[i+1][j];

					temp.push_back(newTile);
				}

				tiles.push_back(temp);
			}
		}

		void drawTerrain()
		{
			glBegin(GL_QUADS);

			for(int i = 0; i < tiles.size(); i++)
			{
				for(int j = 0; j < tiles[i].size(); j++)
				{
					tiles[i][j].drawTile(i-xSize/2, j-ySize/2);
				}
			}

			glEnd();
		}
};

#endif