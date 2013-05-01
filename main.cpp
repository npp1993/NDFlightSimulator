#include "GraphicsHeader.h"
#include <math.h>
//#include <random>
#include "Carrier.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include "Plane.h"
#include "Bullet.h"
#include "Terrain.h"
#include "ComputerPlane.h"
#include "HumanPlane.h"
#include "ExplosionManager.h"

float angle=0.0,deltaAngle = 0.0,ratio,rotationAngleDelta = 0,rotationAngle = 0;
float x=-10.0f,y=21.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0;
int shipRotationAngle = 0;
HumanPlane mainPlane;
std::vector <Bullet> bulletsArray;
std::vector <ComputerPlane> enemyPlanes;
std::vector <ComputerPlane> friendlyPlanes;
Terrain terrain;
ExplosionManager explosionManager(&x, &y, &z);

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

void advanceLevel(){
    if ((currentTime-previousTime)>5000) {
        previousTime = currentTime;
        ComputerPlane newFriend;
        newFriend.x = (rand()%400)-200;
        newFriend.y = (rand()%20)+45;
        newFriend.z = (rand()%400)-200;
        
        ComputerPlane newEnemy;
        //newEnemy.x = (rand()%400)-200;
        //newEnemy.y = (rand()%20)+45;
        //newEnemy.z = (rand()%400)-200;
        int g = (rand()%terrain.carriers.size());
        newEnemy.x = terrain.carriers[g].x;
        newEnemy.z = terrain.carriers[g].z;
        newEnemy.y = terrain.carriers[g].y+terrain.carriers[g].length/12;
        //newEnemy.enemyPlane = &mainPlane;
        //newEnemy.huntEnemyPlane();
        //enemyPlanes.push_back(newEnemy);
        newEnemy.planeRed = 1;
        newFriend.planeBlue = 1;
        //Determine friends enemy
        if (friendlyPlanes.size()==0) {
            return;
        }
        int i = rand()%(enemyPlanes.size()-1);
        newFriend.enemyPlane = &enemyPlanes[i];
        i = rand()%(friendlyPlanes.size()-1);
        newEnemy.enemyPlane = &friendlyPlanes[i];
        newFriend.huntEnemyPlane();
        newEnemy.huntEnemyPlane();
        enemyPlanes.push_back(newEnemy);
        friendlyPlanes.push_back(newFriend);
        
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
	
	flightsimDL = glGenLists(1);  // Create the id for the list
	
	glNewList(flightsimDL,GL_COMPILE);  // start list
	
	glEndList();  // endList

	return flightsimDL;
}

void buildEnemyPlanes()
{
    for (int i = -100; i<101; i+=151)
	{
        for (int j = -100; j<101; j+=151)
		{
            ComputerPlane newEnemy;
            newEnemy.x = i;
            newEnemy.y = 10;
            newEnemy.z = j;
            newEnemy.planeRed = 1;
            Plane* mainPlanePointer = &mainPlane;
            newEnemy.enemyPlane = mainPlanePointer;
            newEnemy.huntEnemyPlane();
            enemyPlanes.push_back(newEnemy);
        }
    }

    for (int i = -100; i<101; i+=151)
	{
        for (int j = -100; j<101; j+=151)
		{
            ComputerPlane newFriend;
            newFriend.x = i+2;
            newFriend.planeBlue = 1;
            newFriend.y = 10;
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

void drawPlane()
{
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
        if (enemyPlanes[i].enemyPlane->dead) {
            enemyPlanes[i].enemyPlane = &friendlyPlanes[(rand()%(friendlyPlanes.size()-1))];
        }
    }
    //Draw Friendly Planes
    for (int i = 0; i<friendlyPlanes.size(); i++) {
        if (friendlyPlanes[i].y>0) {
            friendlyPlanes[i].movePlane();
            friendlyPlanes[i].drawPlane();
        }
        //friendlyPlanes[i].adjustAttitudeFacingPlane(mainPlane);
        if (!friendlyPlanes[i].dead) {
            friendlyPlanes[i].huntEnemyPlane();
        }
        friendlyPlanes[i].drawBullets();
        if (friendlyPlanes[i].enemyPlane->dead) {
            friendlyPlanes[i].enemyPlane = &enemyPlanes[(rand()%(enemyPlanes.size()-1))];
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
    mainPlane.movePlane();
    mainPlane.drawPlane();
}

void renderScene(void) {
    
    //GLfloat lightpos[] = {-x,-z,-y};
    //glTranslatef(lightpos[0], lightpos[1], lightpos[2]);
    glColor3f(1, 1, 1);
    //glutSolidSphere(30, 20, 20);
    //glTranslatef(-lightpos[0], -lightpos[1], -lightpos[2]);
    //glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	if (deltaMove)
	{
		moveMeFlat(deltaMove);
	}

	if (deltaAngle)
	{
		angle += deltaAngle;
		orientMe(angle);
        //rotateMe(angle);
	}

    if (rotationAngleDelta)
	{
        rotationAngle+=rotationAngleDelta;
        rotationAngleDelta=0;
        rotateMe(rotationAngle);
    }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Draw ground
    
    for (int i = 0; i<bulletsArray.size(); i++)
	{
        bulletsArray[i].moveBullet();
        bulletsArray[i].drawBullet();
    }

	terrain.drawTerrain();
	drawPlane();

	explosionManager.drawExplosions();

	advanceLevel();
    
    calculateFPS();
	glutSwapBuffers();
    terrain.indexer++;
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
            mainPlane.pitch-=6; break;
        case 'k':
            mainPlane.pitch+=6; break;
        case 'j':
            mainPlane.roll-=10;break;
        case 'l':
            mainPlane.roll+=10;break;
        case 'p':
            mainPlane.speed+=.1;break;
        case 'o':
            mainPlane.speed-=.1;break;
        case 'u':
            //mainPlane.userFire();
    
            Bullet newBullet = mainPlane.fireBullet();
            bulletsArray.push_back(newBullet);
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

int main(int argc, char **argv)
{
	srand(time(NULL));
    buildEnemyPlanes();

    mainPlane.y = 45;
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1480,920);
	glutCreateWindow("Flight Simulator Basic");
    
	initScene();
    
    // Enable lighting
	explosionManager.generateExplosion(0, 45, -100, 0, 0, 0);
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
	glEnable( GL_BLEND );
    glClearColor(0.0f, 0.0f, .3f, .5f);
    
	glutIgnoreKeyRepeat(.1);
	//glutSpecialFunc(pressKey);
    glutKeyboardFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
    
	glutReshapeFunc(changeSize);
    
	glutMainLoop();
    
	return(0);
}
