//
//  Headers.h
//  test2
//
//  Created by Victor Young on 12/26/15.
//  Copyright (c) 2015 FrozenShore. All rights reserved.
//

#ifndef test2_Headers_h
#define test2_Headers_h

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif

#include "model.h"
#include "bmpReader.h"
#include "simpleDraw.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#endif
