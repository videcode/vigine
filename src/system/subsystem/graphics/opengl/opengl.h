#pragma once

#include "x11/x11.h"

namespace render{
    namespace OpenGL{

        extern "C" {
		    using namespace X11;

            #define GL_GLEXT_PROTOTYPES // for activate functions

            #include<GL/gl.h>
            #include<GL/glx.h>

            #include<GL/glu.h>
            #include<GL/glut.h>

            #include <GL/glext.h>


        }
    }
}
