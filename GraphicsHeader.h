//
//  GraphicsHeader.h
//  GraphicsExample
//
//  Created by Matt McGlynn on 3/29/13.
//  Copyright (c) 2013 Matt McGlynn. All rights reserved.
//

#ifndef GraphicsHeader_h
#define GraphicsHeader_h


#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#endif
