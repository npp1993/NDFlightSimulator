//
//  Terrain.h
//
//  Created by Nathaniel Pawelczyk on 4/29/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include "GraphicsHeader.h"
#include <vector>
#include "TerrainTile.h"
#include "Tree.h"
#include "Carrier.h"
#include "Building.h"
#include "Explosion.h"
#include "Carrier.h"
//#include "Silo.h"


//std::vector<Silo> silos;

class Terrain{

	public:
		int indexer;
		std::vector <std::vector <TerrainTile> >  tiles;
		std::vector <Carrier> carriers;

	Terrain()
	{
		indexer = 0;
		buildTerrain();
		buildCarrierGroup();
		buildSilos();
	}

	void drawTerrain()
	{
		float minX=200000, maxX=0, minY=20000, maxY=0;

		glBegin(GL_QUADS);

		for (int i = 20; i <tiles.size()-20; i++)
		{
			for (int j = 20; j <tiles.size()-20; j++)
			{
				if(tiles[i][j].xMax>maxX)
				{
					maxX = tiles[i][j].xMax;
				}

				if(tiles[i][j].yMax>maxY)
				{
					maxY = tiles[i][j].yMax;
				}

				if(tiles[i][j].x<minX)
				{
					minX = tiles[i][j].x;
				}

				if(tiles[i][j].y<minY)
				{
					minY = tiles[i][j].y;
				}

				if (tiles[i][j].z>-.7)
				{
					tiles[i][j].drawTile();
				}
			}
		}

		drawWater(maxX*40, maxY*40, minX*40, minY*40);
		glEnd();
    
		drawTrees();
		drawBuildings();
		//drawSilos();
		drawCarrierGroup();
	}

	private:

	void buildTerrain()
	{
		double tileSize = 0.8;

		for (double j = -200; j < 200; j+=tileSize)
		{
			std::vector<TerrainTile> tiledRow;
			double prevZ = 0.0;

			for (double i= -200; i<200; i+=tileSize)
			{
				TerrainTile newTile;
				newTile.red = 0.1;
				newTile.green = 0.15;
				newTile.blue = 0.05;
				newTile.x = j;
				newTile.y = i;
				newTile.xMax = j+tileSize;
				newTile.yMax = i+tileSize;
				newTile.z = 1*(rand()%600-300)+2;

				//Build an island
				if (abs(i)>160||abs(j)>160)
				{
					newTile.z = 1*(rand()%100-50)-3;
				}

				if ((pow(abs(i),2)+ pow(abs(j),2)) < pow((float)100,2))
				{
					newTile.z = 1*(rand()%700-350)+20;
				}

				prevZ = newTile.z;
				newTile.z1=newTile.z;
				newTile.z2=newTile.z;
				newTile.z3=newTile.z;
				newTile.z4=newTile.z;
				newTile.zMax = newTile.z;

				if ((rand()%1000)>992)
				{
					newTile.hasTree = 1;
				}

				if ((rand()%10000)>9996)
				{
					newTile.hasSilo = 1;
				}

				if ((rand()%10000)>5000)
				{
					newTile.hasBuilding = 1;
				}

				tiledRow.push_back(newTile);
			}

			tiles.push_back(tiledRow);
		}

		for (int x = 1; x<200; x++)
		{
			double randCoeff = 1;
			for (int i = 2; i <tiles.size()-5; i++)
			{
				for (int j = 2; j <tiles.size()-5; j++)
				{
					float totalRed = 0;
					totalRed += tiles[i][j-1].red;
					totalRed += tiles[i+1][j].red;
					totalRed += tiles[i][j+1].red;
					totalRed += tiles[i-1][j].red;
					float newRed = totalRed/4+.00012*((rand()%1000)-500)*randCoeff;
					if (newRed>.15) newRed = .15;
					if (newRed<0) newRed = 0;
					tiles[i][j].red = newRed;
                
					float totalGreen = 0;
					totalGreen += tiles[i][j-1].green;
					totalGreen += tiles[i+1][j].green;
					totalGreen += tiles[i][j+1].green;
					totalGreen += tiles[i-1][j].green;
					float newGreen = totalGreen/4+.000002*((rand()%1000)-500)*randCoeff;
					if (newGreen>.3) newGreen = .3;
					if (newGreen<0) newGreen = 0;
					tiles[i][j].green = newGreen;
                
                
					float totalBlue = 0;
					totalBlue += tiles[i][j-1].blue;
					totalBlue += tiles[i+1][j].blue;
					totalBlue += tiles[i][j+1].blue;
					totalBlue += tiles[i-1][j].blue;
					float newBlue = totalBlue/4+.00006*((rand()%1000)-500)*randCoeff;
					if (newBlue>.05) newBlue = .05;
					if (newBlue<0) newBlue = 0;
					tiles[i][j].blue = newBlue;
                
					//Forest creation
					float totalTree = 0;
					totalTree += tiles[i][j-1].hasTree;
					totalTree += tiles[i+1][j].hasTree;
					totalTree += tiles[i][j+1].hasTree;
					totalTree += tiles[i-1][j].hasTree;
					float newTree = totalTree/4 +0.00045*((rand()%1000)-500);
					if (newTree>.8) newTree = .8;
					if (newTree<0) newTree = 0;
                
					float totalBuilding = 0;
					totalBuilding += tiles[i][j-1].hasBuilding;
					totalBuilding += tiles[i+1][j].hasBuilding;
					totalBuilding += tiles[i][j+1].hasBuilding;
					totalBuilding += tiles[i-1][j].hasBuilding;
					float newBuilding = totalBuilding/4 +0.00015*((rand()%1000)-500);
					if (newBuilding>.8) newBuilding = .8;
					if (newBuilding<0) newBuilding = 0;
					tiles[i][j].hasBuilding = newBuilding;
                
					//Terrain Smoothing
					float zTotal = 0;
					zTotal += tiles[i][j-1].z;
					zTotal  += tiles[i+1][j].z;
					zTotal  += tiles[i][j+1].z;
					zTotal  += tiles[i-1][j].z;
					tiles[i][j].z = zTotal/4 +(.00016*(rand()%1000-500));
					tiles[i][j].z1 = tiles[i][j].z;
					tiles[i-1][j].z4 = tiles[i][j].z;
					tiles[i-1][j-1].z3 = tiles[i][j].z;
					tiles[i][j-1].z2 = tiles[i][j].z;

					if (i==1 || j==1 || (i==tiles.size()-2) || (j==tiles.size()-2) )
					{
						tiles[i][j].z2 = 0.0;//z;
						tiles[i][j].z3 = 0.0;//z;
						tiles[i][j].z4 = 0.0;//z;
					}
                
                
					if (tiles[i][j].z<.4&&x>195)
					{
						tiles[i][j].red = (.9+tiles[i][j].red)/2;
						tiles[i][j].green = (.7+tiles[i][j].green)/2;
						tiles[i][j].blue = (.62+tiles[i][j].blue)/2;
					}

					if (tiles[i][j].z>20&&x==190)
					{
						tiles[i][j].red = (.1+tiles[i][j].red)/2;
						tiles[i][j].green = (.1+tiles[i][j].green)/2;
						tiles[i][j].blue = (.1+tiles[i][j].blue)/2;
						tiles[i][j].hasTree = ((rand()%100)>96);
					}

					if (x==192)
					{
						//Color the island
						randCoeff = 1;
						if (tiles[i][j].z>2)
						{
							//tiles[i][j].red = 8*abs(tiles[i][j].z/10)*tiles[i][j].red;
						}

						if (tiles[i][j].z>20)
						{
							//tiles[i][j].red = .1;
							//tiles[i][j].green = .1;
							//tiles[i][j].blue = .1;
						}

						double zDiff = 0;
						zDiff += abs(tiles[i][j-2].z - tiles[i][j].z);
						zDiff  += abs(tiles[i+2][j].z- tiles[i][j].z);
						zDiff  += abs(tiles[i][j+2].z- tiles[i][j].z);
						zDiff  += abs(tiles[i-2][j].z- tiles[i][j].z);
						zDiff/=4;

						if (tiles[i][j].z>15)
						{
							tiles[i][j].hasBuilding = (rand()%1000)>520;
						}else
						{
							tiles[i][j].hasBuilding = (rand()%1000)>700;
						}
						if (zDiff<.3&&zDiff>.002)
						{
							//tiles[i][j].hasBuilding = 0;
						}
					}
				}
			}
		}
	}

	void drawTrees()
	{
		for (int i = 20; i <tiles.size()-20; i++)
		{
			for (int j = 20; j <tiles.size()-20; j++)
			{
				if (tiles[i][j].hasTree&&(tiles[i][j].z>2))
				{
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

	void buildSilos()
	{
		/*for (int i = 20; i <tiles.size()-20; i++)
		{
			for (int j = 20; j <tiles.size()-20; j++)
			{
				if (tiles[i][j].hasSilo&&(tiles[i][j].z>2))
				{
					Silo t;
					t.siloRadius = 1;
					t.x = tiles[i][j].x;
					t.z = tiles[i][j].y;
					t.y = tiles[i][j].z1;
					silos.push_back(t);
				}
			}
		}*/
	}

	void drawSilos()
	{
		/*for (int i = 0; i<silos.size(); i++)
		{
			silos[i].adjustAttitudeFacingPlane(mainPlane);
			silos[i].drawSilo();
			silos[i].drawBullets();
		}*/
	}

	void drawBuildings()
	{
		for (int i = 20; i <tiles.size()-20; i++)
		{
			for (int j = 20; j <tiles.size()-20; j++)
			{
				if (tiles[i][j].hasBuilding>.7&&tiles[i][j].z>4)
				{
					int step = 0;
					for (int x=-3; x<8; x++)
					{
						for (int y=-3; y<8; y++)
						{
							if (x==0&&y==0)
							{
								continue;
							}
                        
							tiles[i+x][j+y].hasBuilding = 0;
							tiles[i+x][j+y].hasTree = 0;

							if (indexer<2)
							{
								for (int z = 0; z<3; z++)
								{
									tiles[i+x][j+y].red = (.2+tiles[i+x][j+y].red)/2;
									tiles[i+x][j+y].green= (.2+tiles[i+x][j+y].green)/2;
									tiles[i+x][j+y].blue= (.2+tiles[i+x][j+y].blue)/2;
								}
							}

							step++;
							step=step%5;

							if (x<-1||y<-1||x>5||y>5)
							{
								tiles[i+x][j+y].red = (.1+tiles[i+x][j+y].red)/2;
								tiles[i+x][j+y].green= (.1+tiles[i+x][j+y].green)/2;
								tiles[i+x][j+y].blue= (.1+tiles[i+x][j+y].blue)/2;
							}

							if ((x==-3||y==-3)&&step==2)
							{
								tiles[i+x-1][j+y-1].hasTree=1;
							}

							if ((x==7||y==7)&&step==2)
							{
								tiles[i+x+1][j+y+1].hasTree=1;
							}
						}
					}

					Building t;
					t.x = tiles[i][j].x;
					t.y = tiles[i][j].y;
					t.z = tiles[i][j].z-2;
					t.height = 20;
					t.drawBuilding();
				}
			}
		}
	}

	void buildCarrierGroup()
	{
		for (int i = 0; i < 4; i++)
		{
			Carrier newCarrier;
			newCarrier.x = (rand()%300)+400;
			newCarrier.z = (rand()%200)+400;
			carriers.push_back(newCarrier);
		}
	}

	void drawCarrierGroup()
	{
		for (int i = 0; i < carriers.size(); i++)
		{
			carriers[i].drawCarrier();
		}
	}

	void drawWater(float maxX,float maxY,float minX,float minY)
	{
		TerrainTile water;
		water.red = 0;
		water.green = 0;
		water.blue = .1;
		water.alpha = .4;
		water.z1 = 0; water.z2 = 0; water.z3 = 0; water.z4 = 0;
		water.x=minX;
		water.y=minY;
		water.xMax =maxX;
		water.yMax =maxY;
		water.drawTile();
	}

};



#endif