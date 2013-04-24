#include "GraphicsHeader.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include "Terrain.h"
#include "Plane.h"
#include "Bullet.h"
#include "EnemyPlane.h"

double frameCount, currentTime, fps, previousTime, totalFPS = 0, iterations = 0;
float angle=0.0, deltaAngle = 0.0, ratio, rotationAngleDelta = 0, rotationAngle = 0;
float x=-10.0f, y=21.75f, z=5.0f;
float lx=0.0f, ly=0.0f, lz=-1.0f;
int deltaMove = 0;
int indexer = 0;
int shipRotationAngle = 0;

Plane mainPlane;
Terrain terrain;
std::vector <Bullet> bulletsArray;
std::vector <EnemyPlane> enemyPlanes;

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

void orientMe(float ang)
{
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void moveMeFlat(int direction)
{
	x = x + direction*(lx)*0.1;
	z = z + direction*(lz)*0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void rotateMe(float ang)
{
    orientMe(ang);
	ly = -sin(ang);
	lx = -cos(ang);
    lz = 1;
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}

void advanceLevel()
{
    if( (currentTime - previousTime) > 3000 )
	{
        previousTime = currentTime;
        EnemyPlane newEnemy;
        newEnemy.x = (rand()%400)-200;
        newEnemy.y = 10;
        newEnemy.z = (rand()%400)-200;
        enemyPlanes.push_back(newEnemy);
    }
}

void changeSize(int w, int h)
{ 
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
	{
		h = 1;
	}
    
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
	glNewList(flightsimDL, GL_COMPILE);
    
    
	// endList
	glEndList();
    
	return(flightsimDL);
}

void buildEnemyPlanes()
{
    for (int i = -100; i < 101; i+=50)
	{
        for (int j = -100; j < 101; j+=50)
		{
            EnemyPlane newEnemy;
            newEnemy.x = i;
            newEnemy.y = 10;
            newEnemy.z = j;
            newEnemy.adjustAttitudeFacingPlane(mainPlane);
            enemyPlanes.push_back(newEnemy);
        }
    }
}

void initScene()
{
	glEnable(GL_DEPTH_TEST);
}


void drawPlanes()
{    
    //Draw Enemy planes
    for (int i = 0; i < enemyPlanes.size(); i++)
	{
        enemyPlanes[i].movePlane();
        enemyPlanes[i].drawPlane();
        enemyPlanes[i].adjustAttitudeFacingPlane(mainPlane);
        enemyPlanes[i].drawBullets();
    }
    //Chase View
    
    y = mainPlane.y+2;
    double planeYawRad = mainPlane.planeYaw * 3.14159262 / 180;
    z = mainPlane.z+30*sin(planeYawRad);
    x = mainPlane.x-30*cos(planeYawRad);
    orientMe(1.57 - planeYawRad);
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
    
	for (int i = 0; i < bulletsArray.size(); i++)
	{
		bulletsArray[i].moveBullet();
		bulletsArray[i].drawBullet();
	}

	drawPlanes();

	terrain.drawTerrain();

    //advanceLevel();  uncomment this when bringing enemy planes back in game


    calculateFPS();
	glutSwapBuffers();

    indexer++;
}



void pressKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT :
			deltaAngle = -0.014f;
			break;

		case GLUT_KEY_RIGHT :
			deltaAngle = 0.014f;
			break;

		case GLUT_KEY_UP :
			deltaMove = 3;
			break;

		case GLUT_KEY_DOWN :
			deltaMove = -3;
			break;

        case 'v':
            rotationAngleDelta = -.008;
			break;

        case 'c':
            rotationAngleDelta = .008;
			break;

        case 'i':
            mainPlane.pitch-=6;
			break;

        case 'k':
            mainPlane.pitch+=6;
			break;

        case 'j':
            mainPlane.roll-=10;
			break;
        case 'l':
            mainPlane.roll+=10;
			break;

        case 'p':
            mainPlane.speed+=.01;
			break;

        case 'o':
            mainPlane.speed-=.01;
			break;

        case 'u':
            Bullet newBullet = mainPlane.fireBullet();
            bulletsArray.push_back(newBullet);
            break;
	}
}

void releaseKey(int key, int x, int y) {
	switch (key)
	{
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT :
			deltaAngle = 0.0f;
			break;

		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN :
			deltaMove = 0;
			break;

        case 'm':
            rotationAngleDelta  = 0;
			break;

        case 'K':
            rotationAngleDelta = 0;
			break;
	}
}



int main(int argc, char **argv)
{
    //buildEnemyPlanes();
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1480, 920);
	glutCreateWindow("ND Flight Simulator");
    
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
    glClearColor(0.0f, 0.0f, .3f, .5f);
    
	glutIgnoreKeyRepeat(0.1);
	glutSpecialFunc(pressKey);
    //glutKeyboardFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
    
	glutReshapeFunc(changeSize);
    
	glutMainLoop();
    
	return(0);
}
