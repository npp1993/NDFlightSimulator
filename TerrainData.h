//
//  TerrainTile.h
//  GraphicsExample
//
//  Created by Nathaniel Pawelczyk on 3/26/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef TerrainData_H
#define TerrainData_H

#include <iostream>
#include <math.h>
#include <iostream>
#include <vector>
#include <deque>
#include "GraphicsHeader.h"
#include "TerrainTile.h"
#include "WaterTile.h"
#include "Tree.h"
#include "Building.h"

class TerrainData {

	private:
		std::deque <std::vector <TerrainTile> > tiles;
		float tileSize;
    
	public:

		TerrainData()
		{
			tileSize = 1.0;  //default tile length and width

			for(double i = -300; i < 300; i+=tileSize)
			{
				std::vector<TerrainTile> tileRow;

				for(double j = -300; j < 300; j+=tileSize)
				{
					TerrainTile newTile(i, j, tileSize);

					newTile.z1 = 0;
					newTile.z2 = 0;
					newTile.z3 = 0;
					newTile.z4 = 0;

					newTile.red = rand()%10 * 0.1;

					if( (rand() % 1000) > 992)
					{
						//newTile.hasTree = 1;
					}

					if( (rand() % 10000 ) > 5000)
					{
						//newTile.hasBuilding = 1;
					}

					tileRow.push_back(newTile);  //add new tile
				}

				tiles.push_back(tileRow);  //add new row of tiles to 2D data structure
			}


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
			*/
		}

		void drawTerrain(float xOff, float yOff)
		{	
			float minX=200000, maxX=0, minY=20000, maxY=0;
			glBegin(GL_QUADS);

			for (int i = 20; i <tiles.size() - 20; i++)
			{
				for (int j = 20; j <tiles.size() - 20; j++)
				{
					if(tiles[i][j].xMax > maxX)
					{
						maxX = tiles[i][j].xMax;
					}

					if(tiles[i][j].yMax > maxY)
					{
						maxY = tiles[i][j].yMax;
					}

					if(tiles[i][j].x < minX)
					{
						minX = tiles[i][j].x;
					}

					if(tiles[i][j].y < minY)
					{
						minY = tiles[i][j].y;
					}

					tiles[i][j].drawTile(xOff, yOff);
				}
			}

			//drawWater(maxX, maxY, minX, minY);  ***fix this, causes tearing currently***

			glEnd();
    
			drawTrees();
			drawBuildings();

		}

		/*void drawWater(float maxX, float maxY, float minX, float minY)
		{
			WaterTile water(0, 0, 2000);
			water.drawTile(mainPlane.x, mainPlane.y);
		}*/

		void drawTrees()
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
		}

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

		int size()
		{
				return tiles.size();
		}

		std::vector<TerrainTile> operator[](int i)  //allows syntax such as terrain[x][y] in main.cpp
		{
				return tiles[i];
		}
};
#endif /* defined(__GraphicsExample__TerrainTile__) */
