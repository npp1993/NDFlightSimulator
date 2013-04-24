//
//  Plane.h
//  FinalProjectFund2
//
//  Created by Matt McGlynn on 3/30/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef FinalProjectFund2_Plane_h
#define FinalProjectFund2_Plane_h

#include <math.h>
#include "GraphicsHeader.h"
#include "Bullet.h"
#include <vector>

class Plane { 
    
	public:
		double x;
		double y;
		double z;
		double roll;
		double pitch;
		double yaw;
		double wingspan;
		double speed;
		double planeYaw;
		bool planeRed = 0;
		bool planeBlue = 0;
		int dead = 0;
		//std::vector<Bullet> userBullets;
		
		Plane()
		{
			x = -100;
			y = 5;
			z = 0;
			roll = 0;
			pitch = 0;
			wingspan = 8;
			speed = .8;
			planeYaw = 0;
			planeRed = 0;
		}
    
		void movePlane(){
			if (pitch>60) {
				pitch=60;
			}
			if (roll>130){
				roll = 130;
			}
			if (pitch<-60) {
				pitch= -60;
			}
			if (roll<-130){
				roll = -130;
			}
			if (abs(roll)<10){
				roll/=1.002;
			}
			if (abs(pitch)<10){
				pitch/=1.002;
			}
			double pi = 3.14159262;
			
			//yaw is the cross product of roll and pitch
			int neg =  -2*((roll>90) || (roll<-90))+1;
			double rollRad = (roll*pi)/180;
			if (rollRad>pi/2) {
				rollRad-=pi;
			}
			if (rollRad<-pi/2) {
				rollRad-=pi;
			}
			
			double pitchRad = (pitch*pi)/180;
			//yaw += asin(sin(rollRad)*sin(pitchRad))*6;
			double yawPitchCotribution = pitch;
			if (yawPitchCotribution>90) {
				yawPitchCotribution-=90;
			}
			else if (yawPitchCotribution>50) {
				yawPitchCotribution = 50;
			}
			double planeYawDelta = (roll/30*yawPitchCotribution/30)/2;
			if (planeYawDelta>2) {
				planeYawDelta = 2;
			}
			if (planeYawDelta<-2) {
				planeYawDelta = -2;
			}
			planeYaw-=planeYawDelta;
			double yawRad = (planeYaw*pi)/180;
			//yawRad = asin(sin(rollRad)*sin(pitchRad))*6;
			//Motion based on yaw
			x = x + speed*cos(yawRad);
			z = z - speed*sin(yawRad);
			//std::cout<<planeYaw<<"\n";
			//Motion based on pitch
			y = y + neg*(speed*sin(pitchRad)-speed*abs(sin(rollRad)));
        
        
			//yaw is the cross product of roll and pitch
			int neg = -2 * ( (roll > 90) || (roll < -90)) + 1;
			double rollRad = (roll * pi) / 180;

			if (rollRad > pi/2)
			{
				rollRad-=pi;
			}

			if (rollRad < -pi/2)
			{
				rollRad-=pi;
			}
        
			double pitchRad = (pitch*pi)/180;
			//yaw += asin(sin(rollRad)*sin(pitchRad))*6;
			double planeYawDelta = (roll/30*pitch/30)/2;

			if (planeYawDelta>2)
			{
				planeYawDelta = 2;
			}
			if (planeYawDelta<-2)
			{
				planeYawDelta = -2;
			}

			planeYaw-=planeYawDelta;
			double yawRad = (planeYaw*pi)/180;

			//Motion based on yaw
			xVelocity = speed * cos(yawRad);
			zVelocity = speed * sin(yawRad);
			x += xVelocity;
			z -= zVelocity;

			//Motion based on pitch
			y += neg * (speed * sin(pitchRad) - speed * abs(sin(rollRad)));
		}
    
		void drawPlane()
		{
			glTranslatef(x, y, z);
			glColor3f(.16, .16, .16);
			
			if (planeRed)
			{
				glColor3f(.3, .1, .1);
			}
			else if (planeBlue)
			{
				glColor3f(.1, .1, .3);
			}

			glPushMatrix();
			glRotatef(planeYaw, 0, 1, 0);
			glRotatef(roll, 1, 0, 0);
			glRotatef(pitch, 0, 0, 1);
			glBegin(GL_TRIANGLES);
        
			//Draw main wing
			glVertex3f(-.5*wingspan, 0, -wingspan);
			glVertex3f(-.5*wingspan, 0, wingspan);
			glVertex3f(+.5*wingspan, 0, 0);
        
			//Draw fins
			glColor3f(.07, .07, .07);
			glVertex3f(-.5*wingspan, 0, -wingspan/2);
			glVertex3f(.0*wingspan, 0, -wingspan/2);
			glVertex3f(-.5*wingspan, wingspan/3.5, -wingspan/2);
			glVertex3f(-.5*wingspan, 0, wingspan/2);
			glVertex3f(.0*wingspan, 0, wingspan/2);
			glVertex3f(-.5*wingspan, wingspan/3.5, wingspan/2);
        
			//Draw cockpit
			glColor3f(.36, .16, 0);
			glVertex3f(.46*wingspan, 0, 0);
			glVertex3f(.35*wingspan, 0, -wingspan/10);
			glVertex3f(.35*wingspan, .1*wingspan, 0);
			glVertex3f(.46*wingspan, 0, 0);
			glVertex3f(.35*wingspan, 0, wingspan/10);
			glVertex3f(.35*wingspan, .1*wingspan, 0);
			glVertex3f(.1*wingspan, 0, 0);
			glVertex3f(.35*wingspan, 0, -wingspan/10);
			glVertex3f(.35*wingspan, .1*wingspan, 0);
			glVertex3f(.1*wingspan, 0, 0);
			glVertex3f(.35*wingspan, 0, wingspan/10);
			glVertex3f(.35*wingspan, .1*wingspan, 0);
        
			glEnd();
        
			//Draw Engines
			glColor3f(.1, .1, .1);
        
			glTranslatef(-.7*wingspan, 0, -wingspan/2);
			glRotatef(90, 0, 1, 0);
			glutSolidCone(wingspan/10, wingspan/1.5, 10, 10);
			glColor3f(1, .55, 0);
			glutSolidSphere(wingspan/11, 20, 20);
			glColor3f(.1, .1, .1);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(.7*wingspan, 0, wingspan/2);
			glTranslatef(-.7*wingspan, 0, wingspan/2);
			glRotatef(90, 0, 1, 0);
			glColor3f(1, .55, 0);
			glutSolidSphere(wingspan/11, 20, 20);
			glColor3f(.1, .1, .1);
			glutSolidCone(wingspan/10, wingspan/1.5, 10, 10);
			glRotatef(-90, 0, 1, 0);
			glTranslatef(.7*wingspan, 0, -wingspan/2);
			glPopMatrix();
			glTranslatef(-x, -y, -z);
		}
    
		Bullet fireBullet()
		{
			Bullet shot;
			shot.x = x;
			shot.y = y;
			shot.z = z;
			shot.pitch = pitch;
			shot.yaw = planeYaw;
			shot.speed = speed*5;
			shot.moveBullet();
			return shot;
		} 
		
		void userFire()
		{
			Bullet newBullet = fireBullet();
			//userBullets.push_back(newBullet);
		}
};

#endif
