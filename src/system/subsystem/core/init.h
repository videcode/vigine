#pragma once

#include <stdio.h>
#include <iostream>
#include <string>

#ifdef linux
    #undef linux
#endif // linux

#define OS_LINUX
//#define OS_WINDOWS
//#define RENDER_OPENGL
#define RENDER_VULKAN




namespace core{
    class Init{
        public:
            Init();
            virtual ~Init();


        protected:

        private:
    };
}

