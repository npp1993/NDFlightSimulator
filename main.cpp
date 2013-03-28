#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <random>
#include <iostream>
#include <vector>
#include "TerrainTile.h"
float angle=0.0,deltaAngle = 0.0,ratio,rotationAngleDelta = 0,rotationAngle = 0;
float x=0.0f,y=21.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0;
int indexer = 0;

 std::vector <std::vector <TerrainTile> >  tiles;

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
	ly = sin(ang);
	lx = cos(ang);
    lz=0;
	glLoadIdentity();
	gluLookAt(x, y, z,
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
    
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
void buildTerrain(){
    double tileSize = .8;
    for (double j = -200; j<200; j+=tileSize) {
        std::vector<TerrainTile> tiledRow;
        for (double i= -200; i<200; i+=tileSize) {
            TerrainTile newTile;
            newTile.red = 0.1;
            newTile.green = 0.15;
            newTile.blue = 0.05;
            newTile.x = j;
            newTile.y = i;
            newTile.xMax = j+tileSize;
            newTile.yMax = i+tileSize;
            newTile.z = 1*(rand()%600-300);
            newTile.z1=newTile.z;
            newTile.z2=newTile.z;
            newTile.z3=newTile.z;
            newTile.z4=newTile.z;
            newTile.zMax = newTile.z;
            tiledRow.push_back(newTile);
        }
        tiles.push_back(tiledRow);
    }
    for (int x = 1; x<200; x++) {
        for (int i = 1; i <tiles.size()-5; i++) {
            for (int j = 1; j <tiles.size()-5; j++) {
                float totalRed = 0;
                totalRed += tiles[i][j-1].red;
                totalRed += tiles[i+1][j].red;
                totalRed += tiles[i][j+1].red;
                totalRed += tiles[i-1][j].red;
                float newRed = totalRed/4+.00012*((rand()%1000)-500);
                if (newRed>.15) newRed = .15;
                if (newRed<0) newRed = 0;
                tiles[i][j].red = newRed;
                
                float totalGreen = 0;
                totalGreen += tiles[i][j-1].green;
                totalGreen += tiles[i+1][j].green;
                totalGreen += tiles[i][j+1].green;
                totalGreen += tiles[i-1][j].green;
                float newGreen = totalGreen/4+.000002*((rand()%1000)-500);
                if (newGreen>.3) newGreen = .3;
                if (newGreen<0) newGreen = 0;
                tiles[i][j].green = newGreen;
              
                
                float totalBlue = 0;
                totalBlue += tiles[i][j-1].blue;
                totalBlue += tiles[i+1][j].blue;
                totalBlue += tiles[i][j+1].blue;
                totalBlue += tiles[i-1][j].blue;
                float newBlue = totalBlue/4+.00006*((rand()%1000)-500);
                if (newBlue>.05) newBlue = .05;
                if (newBlue<0) newBlue = 0;
                tiles[i][j].blue = newBlue;
                
                //Terrain Smoothing
                float zTotal = 0;
                zTotal += tiles[i][j-1].z;
                zTotal  += tiles[i+1][j].z;
                zTotal  += tiles[i][j+1].z;
                zTotal  += tiles[i-1][j].z;
                tiles[i][j].z = zTotal/4 +(.0003*(rand()%1000-500));
                tiles[i][j].z1 = tiles[i][j].z;
                tiles[i-1][j].z4 = tiles[i][j].z;
                tiles[i-1][j-1].z3 = tiles[i][j].z;
                tiles[i][j-1].z2 = tiles[i][j].z;
                if (i==1|j==1|(i==tiles.size()-2)|(j==tiles.size()-2)){
                    tiles[i][j].z2 = z;
                    tiles[i][j].z3 = z;
                    tiles[i][j].z4 = z;
                }
                
            }
        }

    }
        std::cout<<tiles.size();
    std::cout<<tiles[0].size();
}
void initScene() {
	glEnable(GL_DEPTH_TEST);
}




void renderScene(void) {
    //GLfloat lightpos[] = {static_cast<GLfloat>(-x+100), static_cast<GLfloat>(-y+300), static_cast<GLfloat>(-z), 3.};
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
    //drawTerrain();
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
    for (int i = 20; i <tiles.size()-20; i++) {
        for (int j = 20; j <tiles.size()-20; j++) {
            tiles[i][j].drawTile();
        }
    }
	glEnd();
    
    glBegin(GL_TRIANGLES);
    glColor3f(.5,.5,.5);
    glVertex3f(x, y-2, z-5);
    glVertex3f(x+.5, y-2, z-5);
    glVertex3f(x, y-2, z-5.5);
    glRotatef(angle, x+2, y, z);
    glEnd();
    std::cout<<" ";
	glutSwapBuffers();
    indexer++;

}


void pressKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_LEFT :
			deltaAngle = -0.004f;break;
		case GLUT_KEY_RIGHT :
			deltaAngle = 0.004f;break;
		case GLUT_KEY_UP :
			deltaMove = 1;break;
		case GLUT_KEY_DOWN :
			deltaMove = -1;break;
        case 'm':
            rotationAngleDelta = -.004;break;
        case 'k':
            rotationAngleDelta = .004;break;
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
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1480,920);
	glutCreateWindow("Flight Simulator Basic");
    
	initScene();
    
    // Enable lighting
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    
	glutIgnoreKeyRepeat(1);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
    
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
    
	glutReshapeFunc(changeSize);
    
	glutMainLoop();
    
	return(0);
}
