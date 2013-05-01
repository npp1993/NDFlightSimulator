//
//  Collision.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 4/30/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Collision_h
#define FinalProjectFund2_Collision_h


class Collision {
    
    
public:
    std::vector <std::vector <TerrainTile> >  *tiles;
    std::vector <ComputerPlane> *enemyPlanes;
    std::vector <ComputerPlane> *friendlyPlanes;
    std::vector <Carrier> *carriers;
    std::vector <Building> *buildings;
    HumanPlane *mainPlane;
    ExplosionManager *explosives;
    Collision(){};
    void detectCollisions(){
        //Detect collisions of friendly planes including main plane
        Plane *planeToCheck = mainPlane;
        detectTerrainCollisionForPlane(planeToCheck);
        detectBuildingCollisionsForPlane(planeToCheck);
        for (int i = 0; i<(*friendlyPlanes).size(); i++) {
           planeToCheck = &((*friendlyPlanes)[i]);
            detectTerrainCollisionForPlane(planeToCheck);
            detectBuildingCollisionsForPlane(planeToCheck);
        }
        for (int i = 0; i<(*enemyPlanes).size(); i++) {
            planeToCheck = &((*enemyPlanes)[i]);
            detectTerrainCollisionForPlane(planeToCheck);
            detectBuildingCollisionsForPlane(planeToCheck);
        }
    }
    void detectTerrainCollisionForPlane(Plane * planeToCheck){
        double zFloor = 0;
        zFloor = elevationAtXandZ((planeToCheck->x), (planeToCheck->z));
        
        if (planeToCheck->y<zFloor) {
                handleCollisionForPlane(planeToCheck);
            }
        
        

    }
    void handleCollisionForPlane(Plane * planeToCheck){
        if(planeToCheck->speed)(*explosives).generateExplosion(planeToCheck->x, planeToCheck->y, planeToCheck->z, 0, 0, 0);
        planeToCheck->dead = 1;
        planeToCheck->speed = 0;
        if (planeToCheck == mainPlane) {
            if (mainPlane->hitCount<50) {
                mainPlane->hitCount++;
            }else if(mainPlane->hitCount==300){
                mainPlane->hitCount = 0;
            }else{
                mainPlane->hitCount = 300;
                planeToCheck->x = -100;
                planeToCheck->z = 0;
                planeToCheck->y = 45;
                planeToCheck->pitch = 0;
                planeToCheck->planeYaw = 0;
                planeToCheck->roll = 0;
                planeToCheck->speed = 1.2;
                mainPlane->health-=10;
                mainPlane->desiredPitch = 0;
                mainPlane->desiredRoll = 0;
            }
        }else{
            if (planeToCheck->hitCount==300) {
                planeToCheck->hitCount = 0;
            }else if(planeToCheck->hitCount<50){
                planeToCheck->hitCount++;
            }else{
                planeToCheck->y = -5;
            }
        }
        
    }
    
    void detectBuildingCollisionsForPlane(Plane * planeToCheck){
        if (buildingAtXandZ(planeToCheck->x, planeToCheck->z)&&((planeToCheck->y)<14+(elevationAtXandZ(planeToCheck->x, planeToCheck->z))&&(elevationAtXandZ(planeToCheck->x, planeToCheck->z)>10))) {
            //handleCollisionForPlane(planeToCheck);
        }
    for (int i = 0; i<(*buildings).size(); i++) {
        double planeX = planeToCheck->x;
        double planeY = planeToCheck->y;
        double planeZ = planeToCheck->z;
        double buildingMinX = (*buildings)[i].x;
        double buildingMaxX = (*buildings)[i].maxX;
        double buildingMinZ = (*buildings)[i].y;
        double buildingMaxZ = (*buildings)[i].maxY;
        double buildingMinY = (*buildings)[i].z;
        double buildingMaxY = (*buildings)[i].maxZ;
        if((planeX>buildingMinX&&planeX<buildingMaxX+1)&&(planeY>buildingMinY&&planeY<buildingMaxY)&&(planeZ>buildingMinZ&&planeZ<buildingMaxZ+1)) handleCollisionForPlane(planeToCheck);
    }
        
    }
    int buildingAtXandZ(double x, double z){
        double tileSize = 0.8;
        int j = (x-(-200))/tileSize;
        int k = (z-(-200))/tileSize;
        if (j<20||k<20||j>(*tiles).size()-20||k>(*tiles).size()-20) {
            return 0;
        }else{
            for (int x=k-4; x<k+1; x++) {
                for (int y =j-4; y<j+1; y++) {
                    if ((*tiles)[x][y].hasBuilding>.7) {
                        return 1;
                    }
                }
            }
            return 0;
            //return (*tiles)[k][j].hasBuilding;
        }
        
        
    }
    double elevationAtXandZ(double x, double z){
        double tileSize = 0.8;
        int j = (x-(-200))/tileSize;
        int k = (z-(-200))/tileSize;
        if (j<20||k<20||j>(*tiles).size()-20||k>(*tiles).size()-20) {
            return 0;
        }else{
            return (*tiles)[k][j].z;
        }
        
        
    }
};

#endif
