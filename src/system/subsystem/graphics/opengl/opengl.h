#pragma once

#include "core/base.h"
#include "../../OS/linux/x11.h"

namespace render{
    namespace OpenGL{

        extern "C" {
            using namespace OS::linux::X11;

            #define GL_GLEXT_PROTOTYPES // for activate functions

            #include<GL/gl.h>
            #include<GL/glx.h>

            #include<GL/glu.h>
            #include<GL/glut.h>

            #include <GL/glext.h>


        }
    }
}
