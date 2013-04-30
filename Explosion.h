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

class Explosion
{
	public:
		std::vector<Particle> particles;
		int life;

		Explosion(float x, float y, float z, float vx, float vy, float vz)  //initialize explosion
		{
			life = 100;

			for(int i = 0; i < 100; i++)
			{
				Particle p(x, y, z, vx, vy, vz);
				particles.push_back(p);
			}
		}

		bool drawExplosion()  //returns false if explosion has disappeared after this iteration
		{
			for(int i = 0; i < particles.size(); i++)
			{
				if(particles[i].advanceState())
				{
					float x = particles[i].x;
					float y = particles[i].y;
					float z = particles[i].z;

					glColor4f(particles[i].r,particles[i].g,particles[i].b, particles[i].life);

					glBegin(GL_TRIANGLE_STRIP);
					glVertex3f(x+0.5f, y+0.5f, z);
					glVertex3f(x-0.5f, y+0.5f, z);
					glVertex3f(x+0.5f, y-0.5f, z);
					glVertex3f(x-0.5f, y-0.5f, z);
					glEnd();
				}
			}
			
			life--;
			
			return life <= 0;
		}
};

#endif
