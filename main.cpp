#include "GraphicsHeader.h"
#include <math.h>
//#include <random>
#include "Carrier.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include "TerrainTile.h"
#include "Tree.h"
#include "Building.h"
#include "Plane.h"
#include "Bullet.h"
#include "ComputerPlane.h"
#include "HumanPlane.h"
#include "Collision.h"
#include "ExplosionManager.h"
float angle=0.0,deltaAngle = 0.0,ratio,rotationAngleDelta = 0,rotationAngle = 0;
float x=-10.0f,y=21.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0;
int indexer = 0;
int shipRotationAngle = 0;
int loadBuildings = 1;
double pi = 3.14159262;
HumanPlane mainPlane;
Collision cDetector;
std::vector <ComputerPlane> enemyPlanes;
std::vector <ComputerPlane> friendlyPlanes;
std::vector <Carrier> carriers;
std::vector<Building> buildings;
ExplosionManager explosives(&x,&y,&z);


std::vector <std::vector <TerrainTile> >  tiles;
double frameCount,currentTime,fps,previousTime,totalFPS=0, iterations=0;

void calculateFPS()
{
    //  Increase frame count
    frameCount++;
    
    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    //  Calculate time passed
    int timeInterval = currentTime - previousTime;
    
    if(timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);
        
        //  Set time
        //previousTime = currentTime;
        
        //  Reset frame count
        frameCount = 0;
        totalFPS+=fps;
        iterations++;
        //std::cout<<"FPS: "<<fps<<"\n";
        //std::cout<<"Average FPS: "<<totalFPS/iterations<<"\n";
    }
    
}






void orientMe(float ang) {
    
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void moveMeFlat(int direction) {
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}
void rotateMe(float ang) {
    orientMe(ang);
	ly = -sin(ang);
	lx = -cos(ang);
    lz = 1;
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
    
}

void drawTrees(){
    for (int i = 20; i <tiles.size()-20; i++) {
        for (int j = 20; j <tiles.size()-20; j++) {
            //std::cout<<tiles[i][j].hasTree;
            if (tiles[i][j].hasTree&&(tiles[i][j].z>2)) {//,78 for clumping
                //std::cout<<tiles[i][j].hasTree;
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

void advanceLevel(){
    if ((currentTime-previousTime)>2000) {
		explosives.generateExplosion(45, -100, 0, 0, 0, 0);
        previousTime = currentTime;
        ComputerPlane newFriend;
        newFriend.x = (rand()%400)-200;
        newFriend.y = (rand()%20)+75;
        newFriend.z = (rand()%400)-200;
        newFriend.manuverability=2.2;
        newFriend.explosives = &explosives;
        

        ComputerPlane newEnemy;
        //newEnemy.x = (rand()%400)-200;
        //newEnemy.y = (rand()%20)+45;
        //newEnemy.z = (rand()%400)-200;
        int g = (rand()%carriers.size());
        newEnemy.x = carriers[g].x;
        newEnemy.z = carriers[g].z+carriers[g].length/2.5;
        newEnemy.y = carriers[g].y+carriers[g].length/11;
        newEnemy.pitch = 0;
        newEnemy.planeYaw = 90;
        newEnemy.timer = 200;
        newEnemy.explosives = &explosives;
        //newEnemy.enemyPlane = &mainPlane;
        //newEnemy.huntEnemyPlane();
        //enemyPlanes.push_back(newEnemy);
        newEnemy.planeRed = 1;
        newFriend.planeBlue = 1;
        //Determine friends enemy
        int i;
        if (friendlyPlanes.size()<3||enemyPlanes.size()<3) {
            newEnemy.enemyPlane = &mainPlane;
            enemyPlanes.push_back(newEnemy);
            newFriend.enemyPlane = &newEnemy;
            friendlyPlanes.push_back(newFriend);
            friendlyPlanes[friendlyPlanes.size()-1].enemyPlane = &newEnemy;
            newFriend.huntEnemyPlane();
            advanceLevel();
        }else{
            i = rand()%(friendlyPlanes.size()-1);
            newEnemy.enemyPlane = &friendlyPlanes[i];
            if((rand()%5)>1){
                newEnemy.enemyPlane = &mainPlane;
            }
            i = rand()%(enemyPlanes.size()-1);
            newFriend.enemyPlane = &enemyPlanes[i];
            newFriend.huntEnemyPlane();
            newEnemy.huntEnemyPlane();
            enemyPlanes.push_back(newEnemy);
            if(rand()%5>3){
                friendlyPlanes.push_back(newFriend);
            }

        }
           }
    
}
void drawBuildings(){
    for (int i = 20; i <tiles.size()-20; i++) {
        for (int j = 20; j <tiles.size()-20; j++) {
            if (tiles[i][j].hasBuilding>.7&&tiles[i][j].z>4) {
                int step = 0;
                for (int x=-3; x<8; x++) {
                    for (int y=-3; y<8; y++) {
                        if (x==0&&y==0) {
                            continue;
                        }
                        
                        tiles[i+x][j+y].hasBuilding = 0;
                        tiles[i+x][j+y].hasTree = 0;
                        if (indexer<2) {
                            for (int z = 0; z<3; z++) {
                                tiles[i+x][j+y].red = (.2+tiles[i+x][j+y].red)/2;
                                tiles[i+x][j+y].green= (.2+tiles[i+x][j+y].green)/2;
                                tiles[i+x][j+y].blue= (.2+tiles[i+x][j+y].blue)/2;
                            }
                        }
                        step++;
                        step=step%5;
                        if (x<-1||y<-1||x>5||y>5) {
                            tiles[i+x][j+y].red = (.1+tiles[i+x][j+y].red)/2;
                            tiles[i+x][j+y].green= (.1+tiles[i+x][j+y].green)/2;
                            tiles[i+x][j+y].blue= (.1+tiles[i+x][j+y].blue)/2;
                        }
                        if ((x==-3||y==-3)&&step==2) {
                            tiles[i+x-1][j+y-1].hasTree=1;
                        }
                        if ((x==7||y==7)&&step==2) {
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
                if (loadBuildings) {
                    buildings.push_back(t);
                }
            }
        }
    }
}
void changeSize(int w, int h)
{
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;
    
	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
	// Set the clipping volume
	gluPerspective(45,ratio,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0f,1.0f,0.0f);
}


GLuint createDL() {
	GLuint flightsimDL;
    
	// Create the id for the list
	flightsimDL = glGenLists(1);
    
	// start list
	glNewList(flightsimDL,GL_COMPILE);
    
    
	// endList
	glEndList();
    
	return(flightsimDL);
}

void buildCarrierGroup(){
    for (int i = 0; i<4; i++) {
        Carrier newCarrier;
        newCarrier.x = (rand()%620)+300;
        newCarrier.z = (rand()%400)+300;
        carriers.push_back(newCarrier);
    }
}
void drawCarrierGroup(){
    for (int i = 0; i<carriers.size(); i++) {
        carriers[i].drawCarrier();
    }
}
void buildTerrain(){
    double tileSize = .8;
    for (double j = -200; j<200; j+=tileSize) {
        std::vector<TerrainTile> tiledRow;
        double prevZ = 0.0;
        for (double i= -200; i<200; i+=tileSize) {
            TerrainTile newTile;
            newTile.red = 0.1;
            newTile.green = 0.15;
            newTile.blue = 0.05;
            newTile.x = j;
            newTile.y = i;
            newTile.xMax = j+tileSize;
            newTile.yMax = i+tileSize;
            //newTile.z = .7*(rand()%600-300)+1.4;
            newTile.z = 1*(rand()%600-300)+2;
            //newTile.z = prevZ + .005*(rand()%600-300)-.008;
            //Build an island
            if (abs(i)>160||abs(j)>160) {
                newTile.z = 1*(rand()%100-50)-3;
            }
            if ((pow(abs(i),2)+ pow(abs(j),2))<pow((float)100,2)) {
                newTile.z = 1*(rand()%700-350)+20;
            }
            prevZ = newTile.z;
            newTile.z1=newTile.z;
            newTile.z2=newTile.z;
            newTile.z3=newTile.z;
            newTile.z4=newTile.z;
            newTile.zMax = newTile.z;
            if ((rand()%1000)>992) {
                newTile.hasTree = 1;
            }
            if ((rand()%10000)>9996) {
                newTile.hasSilo = 1;
            }
            if ((rand()%10000)>5000) {
                newTile.hasBuilding = 1;
            }
            tiledRow.push_back(newTile);
        }
        tiles.push_back(tiledRow);
    }
    for (int x = 1; x<200; x++) {
        double randCoeff = 1;
        for (int i = 2; i <tiles.size()-5; i++) {
            for (int j = 2; j <tiles.size()-5; j++) {
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
                //tiles[i][j].hasTree = newTree;
                
               
                
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
                if (i==1|j==1|(i==tiles.size()-2)|(j==tiles.size()-2)){
                    tiles[i][j].z2 = z;
                    tiles[i][j].z3 = z;
                    tiles[i][j].z4 = z;
                }
                
                
                if (tiles[i][j].z<.4&&x>195) {
                    tiles[i][j].red = (.9+tiles[i][j].red)/2;
                    tiles[i][j].green = (.7+tiles[i][j].green)/2;
                    tiles[i][j].blue = (.62+tiles[i][j].blue)/2;
                }
                if (tiles[i][j].z>20&&x==190) {
                    tiles[i][j].red = (.1+tiles[i][j].red)/2;
                    tiles[i][j].green = (.1+tiles[i][j].green)/2;
                    tiles[i][j].blue = (.1+tiles[i][j].blue)/2;
                    tiles[i][j].hasTree = ((rand()%100)>96);
                }
                if (x==192) {
                    //Color the island
                    randCoeff = 1;
                    if (tiles[i][j].z>2) {
                        //tiles[i][j].red = 8*abs(tiles[i][j].z/10)*tiles[i][j].red;
                    }
                    if (tiles[i][j].z>20) {
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
                    //std::cout<<zDiff;
                    if (tiles[i][j].z>15) {
                        tiles[i][j].hasBuilding = (rand()%1000)>520;
                    }else{
                        tiles[i][j].hasBuilding = (rand()%1000)>700;
                    }
                    if (zDiff<.3&&zDiff>.002) {
                        //tiles[i][j].hasBuilding = 0;
                    }
                    
                }
            }
        }
        
        
    }
}
void buildEnemyPlanes(){
    for (int i = -100; i<101; i+=151) {
        for (int j = -100; j<101; j+=151) {
            ComputerPlane newEnemy;
            newEnemy.x = i;
            newEnemy.y = 30;
            newEnemy.z = j;
            newEnemy.planeRed =1;
            Plane* mainPlanePointer = &mainPlane;
            newEnemy.enemyPlane = mainPlanePointer;
            newEnemy.huntEnemyPlane();
            enemyPlanes.push_back(newEnemy);
        }
    }
    for (int i = -100; i<101; i+=151) {
        for (int j = -100; j<101; j+=151) {
            ComputerPlane newFriend;
            newFriend.x = i+2;
            newFriend.planeBlue = 1;
            newFriend.y = 40;
            newFriend.z = j;
            Plane* mainPlanePointer = &enemyPlanes[rand()%3];
            newFriend.enemyPlane = mainPlanePointer;
            newFriend.huntEnemyPlane();
            friendlyPlanes.push_back(newFriend);
        }
    }
}


void initScene() {
	glEnable(GL_DEPTH_TEST);
}


void drawPlane(){
    
    //Draw Enemy planes
    for (int i = 0; i<enemyPlanes.size(); i++) {
        if (enemyPlanes[i].y>0) {
            enemyPlanes[i].movePlane();
            enemyPlanes[i].drawPlane();
        }
        //enemyPlanes[i].movePlane();
        //enemyPlanes[i].drawPlane();
        //enemyPlanes[i].adjustAttitudeFacingPlane(mainPlane);
        if (!enemyPlanes[i].dead) {
            enemyPlanes[i].huntEnemyPlane();
        }
        enemyPlanes[i].drawBullets();
        if (enemyPlanes[i].enemyPlane->dead||enemyPlanes[i].enemyPlane==NULL) {
            enemyPlanes[i].enemyPlane = &friendlyPlanes[(rand()%(friendlyPlanes.size()-1))];
            if((rand()%10)>7){
                enemyPlanes[i].enemyPlane = &mainPlane;
            }
        }
    }
    //Draw Friendly Planes
    for (int i = 1; i<friendlyPlanes.size(); i++) {
        if (friendlyPlanes[i].y>0) {
            friendlyPlanes[i].movePlane();
            friendlyPlanes[i].drawPlane();
        }else{
            friendlyPlanes.erase(friendlyPlanes.begin()+i);
            //continue;
        }
        //friendlyPlanes[i].adjustAttitudeFacingPlane(mainPlane);
        if (!friendlyPlanes[i].dead) {
            friendlyPlanes[i].huntEnemyPlane();
        }
        friendlyPlanes[i].drawBullets();
        if (friendlyPlanes[i].enemyPlane->dead||friendlyPlanes[i].enemyPlane==NULL) {
            if (enemyPlanes.size()<2) {
                advanceLevel();
            }else{
                friendlyPlanes[i].enemyPlane = &enemyPlanes[(rand()%(enemyPlanes.size()-1))];
            }
        }
    }
    //Chase View
    
    y = mainPlane.y+2;
    double planeYawRad = mainPlane.planeYaw*3.14159262/180;
    z = mainPlane.z+30*sin(planeYawRad);
    x = mainPlane.x-30*cos(planeYawRad);
    orientMe(1.57-planeYawRad);
    moveMeFlat(0);
    
    //Move and draw plane
    mainPlane.convertDesiredToActual();
    mainPlane.movePlane();
    mainPlane.drawPlane();
    //mainPlane.manageHealth();
    mainPlane.drawUserBullets(&enemyPlanes);
    
    
    
    
}

void drawWater(float maxX,float maxY,float minX,float minY){
    TerrainTile water;
    water.red = 0;
    water.green = 0;
    water.blue = .1;
    water.alpha = .8;
    water.z1 = 0; water.z2 = 0; water.z3 = 0; water.z4 = 0;
    water.x=minX;
    water.y=minY;
    water.xMax =maxX;
    water.yMax =maxY;
    water.drawTile();
    
}


void renderScene(void) {
    
    //GLfloat lightpos[] = {-x,-z,-y};
    //glTranslatef(lightpos[0], lightpos[1], lightpos[2]);
    glColor3f(1, 1, 1);
    //glutSolidSphere(30, 20, 20);
    //glTranslatef(-lightpos[0], -lightpos[1], -lightpos[2]);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	if (deltaMove)
		moveMeFlat(deltaMove);
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
        //rotateMe(angle);
	}
    if (rotationAngleDelta) {
        rotationAngle+=rotationAngleDelta;
        rotationAngleDelta=0;
        rotateMe(rotationAngle);
    }
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw ground
    
	
    float minX=200000,maxX=0,minY=20000,maxY=0;
    glBegin(GL_QUADS);
    for (int i = 20; i <tiles.size()-20; i++) {
        for (int j = 20; j <tiles.size()-20; j++) {
            if(tiles[i][j].xMax>maxX) maxX = tiles[i][j].xMax;
            if(tiles[i][j].yMax>maxY) maxY = tiles[i][j].yMax;
            if(tiles[i][j].x<minX) minX = tiles[i][j].x;
            if(tiles[i][j].y<minY) minY = tiles[i][j].y;
            if (tiles[i][j].z>-.7) {
                tiles[i][j].drawTile();
            }
            
            
        }
    }
    drawWater(maxX*40,maxY*40,minX*40,minY*40);
	glEnd();
    
    drawTrees();
    drawBuildings();
    advanceLevel();
    drawPlane();
    
    drawCarrierGroup();
    
    
    calculateFPS();
	glutSwapBuffers();

    indexer++;
    if (loadBuildings) {
        loadBuildings = 0;
        cDetector.buildings = &buildings;
    }
    cDetector.detectCollisions();
    //glLoadIdentity();
    glEnd();
    explosives.drawExplosions();
    
}



void pressKey(unsigned char key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
			deltaAngle = -0.014f;break;
		case GLUT_KEY_RIGHT :
			deltaAngle = 0.014f;break;
		case GLUT_KEY_UP :
			deltaMove = 3;break;
		case GLUT_KEY_DOWN :
			deltaMove = -3;break;
        case 'v':
            rotationAngleDelta = -.008;break;
        case 'c':
            rotationAngleDelta = .008;break;
        case 'i':
            //mainPlane.pitch-=6; break;
            mainPlane.desiredPitch-=5; break;
        case 'k':
            //mainPlane.pitch+=6; break;
            mainPlane.desiredPitch+=5; break;
        case 'j':
            //mainPlane.roll-=10;break;
            mainPlane.desiredRoll-=9; break;
        case 'l':
            //mainPlane.roll+=10;break;
            mainPlane.desiredRoll+=9; break;
        case 'p':
            mainPlane.speed+=.1;break;
        case 'o':
            mainPlane.speed-=.1;break;
        case 'u':
            mainPlane.userFire();
            break;
        case 'y':
            mainPlane.fireMissile(&enemyPlanes);
    
            //Bullet newBullet = mainPlane.fireBullet();
            //bulletsArray.push_back(newBullet);
            break;
        
	}
}

void releaseKey(int key, int x, int y) {
    
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT :
			deltaAngle = 0.0f;break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN :
			deltaMove = 0;break;
        case 'm':
            rotationAngleDelta  = 0;break;
        case 'K':
            rotationAngleDelta = 0;break;
        
            
	}
}



int main(int argc, char **argv) {
    buildTerrain();
    //Make the mian plane the lead friendly plane 
    friendlyPlanes.push_back(mainPlane);
    cDetector.carriers = &carriers;
    cDetector.tiles = &tiles;
    cDetector.friendlyPlanes = &friendlyPlanes;
    cDetector.enemyPlanes = &enemyPlanes;
    cDetector.mainPlane = &mainPlane;
    //buildEnemyPlanes();
    buildCarrierGroup();
    mainPlane.y = 45;
    mainPlane.explosives = &explosives;
    explosives.generateExplosion(0, 45, -100, 0, 0, 0);

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1480,920);
    //glutInitWindowSize(600,400);
	glutCreateWindow("Flight Simulator Basic");
    
	initScene();
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    GLfloat light_ambient[] = { 1, 1, 1, 1 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_pos[] = { 0.0, 30.0, 0.0, 1 };
    GLfloat light_dir[] = { 0.0, 0, 0};
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = { 10.0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0f, 0.0f, .6f, .5f);
    
	glutIgnoreKeyRepeat(.05);
	//glutSpecialFunc(pressKey);
    glutKeyboardFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
    
	glutReshapeFunc(changeSize);
    
	glutMainLoop();
    
	return(0);
}
