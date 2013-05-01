//
//  Explosion.h
//
//  Created by Nathaniel Pawelczyk on 4/10/13.
//  Copyright (c) 2013 Nathaniel Pawelczyk. All rights reserved.
//

#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "GraphicsHeader.h"
#include <vector>
#include "Particle.h"
#include "maths.h"  //from lighthouse3d.com, used in billboarding functions

class Explosion
{
	private:
		float* camx;  //pointers to camera position; used pointers so camera location always current
		float* camy;
		float* camz;

	public:
		std::vector<Particle> particles;

		Explosion(float x, float y, float z, float vx, float vy, float vz, float* cx, float* cy, float* cz)  //initialize explosion
		{
			camx = cx;
			camy = cy;
			camz = cz;

			for(int i = 0; i < 300; i++)
			{
				Particle p(x, y, z, vx, vy, vz);
				particles.push_back(p);
			}
		}

		bool drawExplosion()  //returns true if explosion has disappeared after this iteration
		{
			for(int i = 0; i < particles.size(); i++)
			{
				if(particles[i].advanceState())
				{
					float x = particles[i].x;
					float y = particles[i].y;
					float z = particles[i].z;

					glColor4f(particles[i].r,particles[i].g, particles[i].b, particles[i].life);

					billboardSphericalBegin(*camx, *camy, *camz, x, y, z);

					glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(x+0.3f, y+0.3f, z);
					glVertex3f(x-0.3f, y+0.3f, z);
					glVertex3f(x+0.3f, y-0.3f, z);
					glVertex3f(x-0.3f, y-0.3f, z);
					glEnd();

					glPopMatrix();
				}
				else
				{
					particles.erase(particles.begin() + i);  //erase particle if it is transparent
				}
			}

			return (particles.size() == 0);
		}

	private: 

		void billboardSphericalBegin(float camX, float camY, float camZ, float objPosX, float objPosY, float objPosZ)  //billboarding funciton from lighthouse3d.com
		{

			float lookAt[3],objToCamProj[3], objToCam[3], upAux[3];
			float modelview[16],angleCosine;

			glPushMatrix();

			// objToCamProj is the vector in world coordinates from the 
			// local origin to the camera projected in the XZ plane
			objToCamProj[0] = camX - objPosX ;
			objToCamProj[1] = 0;
			objToCamProj[2] = camZ - objPosZ ;

			// This is the original lookAt vector for the object 
			// in world coordinates
			lookAt[0] = 0;
			lookAt[1] = 0;
			lookAt[2] = 1;


			// normalize both vectors to get the cosine directly afterwards
			mathsNormalize(objToCamProj);

			// easy fix to determine wether the angle is negative or positive
			// for positive angles upAux will be a vector pointing in the 
			// positive y direction, otherwise upAux will point downwards
			// effectively reversing the rotation.

			mathsCrossProduct(upAux,lookAt,objToCamProj);

			// compute the angle
			angleCosine = mathsInnerProduct(lookAt,objToCamProj);

			// perform the rotation. The if statement is used for stability reasons
			// if the lookAt and objToCamProj vectors are too close together then 
			// |angleCosine| could be bigger than 1 due to lack of precision
			if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
			{
				glRotatef(acos(angleCosine)*180/3.14,upAux[0], upAux[1], upAux[2]);
			}
      
			// so far it is just like the cylindrical billboard. The code for the 
			// second rotation comes now
			// The second part tilts the object so that it faces the camera

			// objToCam is the vector in world coordinates from 
			// the local origin to the camera
			objToCam[0] = camX - objPosX;
			objToCam[1] = camY - objPosY;
			objToCam[2] = camZ - objPosZ;

			// Normalize to get the cosine afterwards
			mathsNormalize(objToCam);

			// Compute the angle between objToCamProj and objToCam, 
			//i.e. compute the required angle for the lookup vector

			angleCosine = mathsInnerProduct(objToCamProj,objToCam);


			// Tilt the object. The test is done to prevent instability 
			// when objToCam and objToCamProj have a very small
			// angle between them

			if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
			{
				if (objToCam[1] < 0)
				{
					glRotatef(acos(angleCosine)*180/3.14,1,0,0);
				}
				else
				{
					glRotatef(acos(angleCosine)*180/3.14,-1,0,0);
				}
			}
		}
};

#endif
