//
//  TerrainTile.h
//  GraphicsExample
//
//  Created by Nathaniel Pawelczyk on 3/26/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef TerrainData_H
#define TerrainData_H
#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include <vector>
#include <deque>
#include "GraphicsHeader.h"
#include "TerrainTile.h"
#include "WaterTile.h"
#include "Point.h"
#include "Tree.h"
#include "Building.h"
/*
class TerrainData {

	private:
		std::deque <std::deque <TerrainTile> > tiles;

		int tileSize;  //default tile length and width
		float xSize;  //x and y dimensions of terrain
		float ySize;
		float dx;  //x and y offsets that terrain are drawn at, used to make terrain look like it is moving under the plane
		float dy;
		float thetaX;
		float thetaY;
    
	public:

		TerrainData()
		{
			tileSize = 1;
			xSize = 400;  //must be integer multiple of tileSize
			ySize = 400;
			dx = 0;
			dy = 0;

			initTerrain();

			tiles[0][0].z1 = rand() % 10 - 5;  //initialize terrain structure
			tiles[xSize-1][0] = rand() % 10 - 5;
			tiles[xSize-1][ySize-1] = rand() % 10 - 5;
			tiles[0][ySize-1] = rand() % 10 - 5;

			generateTerrain(Point(0, 0), Point(xSize-1, 0), Point(xSize-1, ySize-1), Point(0, ySize-1));

			thetaX = 0;  //used to generate terrain randomness
			thetaY = 0;

			//initTerrain();  //initialize terrain data

			//terrain smoothing, building and forest generation
			//refine tiles
			/*
			for(int x = 1; x < 200; x++)
			{
				std::cout << x;

				for(int i = 1; i < tiles.size()-5; i++)
				{
					for (int j = 1; j < tiles.size()-5; j++)
					{
						float totalRed = 0;
						totalRed += tiles[i][j-1].red;
						totalRed += tiles[i+1][j].red;
						totalRed += tiles[i][j+1].red;
						totalRed += tiles[i-1][j].red;

						float newRed = totalRed / 4 + 0.00012 * ((rand() % 1000) - 500);

						if(newRed > 0.15)
						{
							newRed = 0.15;
						}

						if(newRed < 0)
						{
							newRed = 0;
						}

						tiles[i][j].red = newRed;
                
						float totalGreen = 0;
						totalGreen += tiles[i][j-1].green;
						totalGreen += tiles[i+1][j].green;
						totalGreen += tiles[i][j+1].green;
						totalGreen += tiles[i-1][j].green;
						float newGreen = totalGreen / 4+ 0.000002 * ((rand() % 1000) - 500);

						if (newGreen > 0.3) 
						{
							newGreen = 0.3;
						}

						if(newGreen < 0)
						{
							newGreen = 0;
						}

						tiles[i][j].green = newGreen;
                
						float totalBlue = 0;
						totalBlue += tiles[i][j-1].blue;
						totalBlue += tiles[i+1][j].blue;
						totalBlue += tiles[i][j+1].blue;
						totalBlue += tiles[i-1][j].blue;
						float newBlue = totalBlue / 4+ 0.00006 * ((rand() % 1000) - 500);

						if(newBlue > 0.05)
						{
							newBlue = 0.05;
						}

						if(newBlue < 0)
						{
							newBlue = 0;
						}

						tiles[i][j].blue = newBlue;
                
						//forest creation
						float totalTree = 0;
						totalTree += tiles[i][j-1].hasTree;
						totalTree += tiles[i+1][j].hasTree;
						totalTree += tiles[i][j+1].hasTree;
						totalTree += tiles[i-1][j].hasTree;

						float newTree = totalTree / 4 + 0.00045 * ((rand() % 1000) - 500);

						if(newTree > 0.8)
						{
							newTree = 0.8;
						}

						if(newTree < 0)
						{
							newTree = 0;
						}
						//tiles[i][j].hasTree = newTree;
                
						//building creation
						float totalBuilding = 0;
						totalBuilding += tiles[i][j-1].hasBuilding;
						totalBuilding += tiles[i+1][j].hasBuilding;
						totalBuilding += tiles[i][j+1].hasBuilding;
						totalBuilding += tiles[i-1][j].hasBuilding;

						float newBuilding = totalBuilding / 4 + 0.00015 * ((rand() % 1000) - 500);

						if(newBuilding > 0.8)
						{
							newBuilding = 0.8;
						}

						if(newBuilding < 0)
						{
							newBuilding = 0;
						}

						tiles[i][j].hasBuilding = newBuilding;
                
						//terrain smoothing
						float zTotal = 0;
						zTotal += tiles[i][j-1].z;
						zTotal += tiles[i+1][j].z;
						zTotal += tiles[i][j+1].z;
						zTotal += tiles[i-1][j].z;
						tiles[i][j].z = zTotal / 4 + (0.00016 * (rand() % 1000 - 500));
						tiles[i][j].z1 = tiles[i][j].z;
						tiles[i-1][j].z4 = tiles[i][j].z;
						tiles[i-1][j-1].z3 = tiles[i][j].z;
						tiles[i][j-1].z2 = tiles[i][j].z;
						if ( (i==1) | (j==1) | (i == tiles.size() - 2) | (j == tiles.size() - 2))
						{
							tiles[i][j].z2 = z;
							tiles[i][j].z3 = z;
							tiles[i][j].z4 = z;
						}
                
                
						//if (tiles[i][j].z<.2)
						//{
						//    tiles[i][j].red = .9;
						//    tiles[i][j].green = .7;
						//    tiles[i][j].blue = .62;
						//}
					}
				}
        
			}
			*/
			//std::cout<<tiles.size();
			//std::cout<<tiles[0].size();
    
			//save terrain to file
			/*
			std::ofstream myfile;
			myfile.open ("Level1");

			for (int i = 20; i <tiles.size() - 20; i++)
			{
				for (int j = 20; j <tiles.size() - 20; j++)
				{
            
					myfile << tiles[i][j].x << ","<< tiles[i][j].xMax << "," << tiles[i][j].y << "," << tiles[i][j].yMax << ","<< tiles[i][j].z;
					myfile << tiles[i][j].red << "," << tiles[i][j].green << "," << tiles[i][j].blue << "," << tiles[i][j].hasBuilding << "," << tiles[i][j].hasTree << "\n";
            
            
				}
			}

			myfile.close();

		}

		void initTerrain()
		{
			for(int i = 0; i < xSize/tileSize; i++)
			{
				std::deque<TerrainTile> tempDeque;

				for(int j = 0; j < ySize/tileSize; j++)
				{
					tempDeque.push_back(TerrainTile(tileSize));
				}

				tiles.push_back(tempDeque);
			}
			/*for(int i = -xSize/(2*tileSize); i < xSize/(2*tileSize); i++)
			{
				generateTerrainStripX(i);
			}*/
		}

		void generateTerrain(Point p1, Point p2, Point p3, Point p4)
		{
			if(p1 == p3)  //base case
			{
				//determine color of tiles based on height
				return;
			}

			generateTerrain(p1, p2, p3)
		}

		void drawTerrain(float xOff, float yOff)
		{
			glBegin(GL_QUADS);

			for (int i = 0; i < tiles.size(); i++)
			{
				for (int j = 0; j < tiles[i].size(); j++)
				{
					tiles[i][j].drawTile(tileSize * (((float)i)-tiles.size()/2) + xOff, tileSize * (((float)j)-tiles[i].size()/2) + yOff);
				}
			}

			//drawWater(xSize/2, ySize/2, -xSize/2, -ySize/2);  ***fix this, causes tearing currently***

			glEnd();
    
			//drawTrees();
			//drawBuildings();

		}

		void drawWater(float maxX, float maxY, float minX, float minY)
		{
		//	WaterTile water(0, 0, 2000);
		//	water.drawTile(mainPlane.x, mainPlane.y);
		}

		/*void drawTrees()
		{
			for (int i = 20; i <tiles.size()-20; i++)
			{
				for (int j = 20; j <tiles.size()-20; j++)
				{
					//std::cout<<terrain[i][j].hasTree;
					if(tiles[i][j].hasTree) {
						//std::cout<<terrain[i][j].hasTree;
						Tree t;
						t.x = tiles[i][j].x;
						t.y = tiles[i][j].y;
						t.z = tiles[i][j].z1;
						t.height = .5;
						t.baseWidth =.4;
						t.leavesWidth = .55;
						t.drawTree();
					}
				}
			}
		}*/

		/*
		void drawBuildings()
		{
			for(int i = 20; i <tiles.size()-20; i++)
			{
				for(int j = 20; j <tiles.size()-20; j++)
				{
					if(tiles[i][j].hasBuilding > 0.7)
					{
						int step = 0;
						for (int x=-3; x<8; x++)
						{
							for (int y=-3; y<8; y++)
							{
								if( x == 0 && y == 0 )
								{
									continue;
								}
                        
								tiles[i+x][j+y].hasBuilding = 0;
								tiles[i+x][j+y].hasTree = 0;

								//if(indexer < 2)  //what is this?
								//{
									for (int z = 0; z<3; z++)
									{
										tiles[i+x][j+y].red = (.2+tiles[i+x][j+y].red)/2;
										tiles[i+x][j+y].green= (.2+tiles[i+x][j+y].green)/2;
										tiles[i+x][j+y].blue= (.2+tiles[i+x][j+y].blue)/2;
									}
								//}

								step++;
								step = step%5;

								if( (x < -1) || (y < -1) || (x > 5) || (y > 5) )
								{
									tiles[i+x][j+y].red = (.1+tiles[i+x][j+y].red)/2;
									tiles[i+x][j+y].green= (.1+tiles[i+x][j+y].green)/2;
									tiles[i+x][j+y].blue= (.1+tiles[i+x][j+y].blue)/2;
								}
								if( (x == -3 || y == -3 ) && step == 2)
								{
									tiles[i+x-1][j+y-1].hasTree=1;
								}
								if ( (x == 7 || y == 7 ) && step == 2)
								{
									tiles[i+x+1][j+y+1].hasTree=1;
								}
							}
						}

						Building t;
						t.x = tiles[i][j].x;
						t.y = tiles[i][j].y;
						t.z = tiles[i][j].z1-2;
						t.height = 20;
						t.drawBuilding();
					}
				}
			}
		}
		*/

		void shiftTerrain(float xVel, float yVel)  //shifts the terrain under the user to represent flight over it
		{
			//shiftTerrainX(xVel);
			//shiftTerrainY(yVel);
		}

		void shiftTerrainX(float xVel)  //generate new terrain and discard old terrain as the user flys in the x direction
		{

			for(float i = 0; i < floor(xVel/tileSize); i++)
			{
				generateTerrainStripX(i);
			}
		}

		void generateTerrainStripX(int i)
		{
			std::deque<TerrainTile> tileRow;

			float x = sin(thetaX);
			thetaX += 0.1;

			for(int j = 0; j < ySize/tileSize; j++)
			{
				TerrainTile newTile(tileSize);  //translate map so that it is centered on (0, 0)

				/*float y = sin(thetaY);
				thetaY += 0.3;

				newTile.z3 = x + y;
					
				if(i == -xSize/(2*tileSize))  //only used when called from initTerrain()
				{
					newTile.z1 = x;
					newTile.z2 = x;
				}
				else
				{
					newTile.z1 = tiles.back()[j].z4;
					newTile.z2 = tiles.back()[j].z3;
				}

				if(j == 0)
				{
						newTile.z4 += y;
				}
				else
				{
					newTile.z4 = tileRow.back().z3;
				}

				newTile.red = rand() % 10 * 0.05;

				if( (rand() % 100) > 99)
				{
					//newTile.hasTree = 1;
				}

				if( (rand() % 100 ) > 5)
				{
					//newTile.hasBuilding = 1;
				}*/


				tileRow.push_back(newTile);  //add new tile
			}

			tiles.push_back(tileRow);  //add new row of tiles to 2D data structure

			if(tiles.size() > xSize/tileSize)
			{
				tiles.pop_front();  //pop the terrain row out of the current map
			}
		}

		void shiftTerrainY(float yVel)
		{
			for(float i = 0; i < floor(abs(yVel)/tileSize); i++)  //fix abs
			{
				float x = sin(thetaX);
				thetaX += 0.01;

				for(int j = 0; j < ySize/tileSize; j++)
				{
					TerrainTile newTile(tileSize);  //translate map so that it is centered on (0, 0)

					float y = sin(thetaY);
					thetaY += 0.03;

					newTile.z1 = tiles[j].back().z2;
					newTile.z4 = tiles[j].back().z3;
					newTile.z3 = x + y;
					
					if(j == 0)
					{
						newTile.z2 = x;
					}
					else
					{
						newTile.z2 = tiles[j-1].back().z3;
					}

					newTile.blue = rand() % 10 * 0.05;

					/*if( (rand() % 100) > 99)
					{
						//newTile.hasTree = 1;
					}

					if( (rand() % 100 ) > 5)
					{
						//newTile.hasBuilding = 1;
					}*/

					tiles[j].push_back(newTile);  //add new tile
					tiles[j].pop_front();
				}
			}
		}

		int size()
		{
			return tiles.size();
		}

		std::deque<TerrainTile> operator[](int i)  //allows syntax such as terrain[x][y] in main.cpp
		{
			return tiles[i];
		}
};
#endif /* defined(__GraphicsExample__TerrainData__) */
