#pragma once

#define OS_LINUX
#define RENDER_VULKAN
//#define RENDER_OPENGL

#define API_INTERFACE_IBASE "system/interface/ibase.h"
#define API_INTERFACE_IWINDOW "system/interface/os/iwindow.h"
#define API_INTERFACE_IEVENT "system/interface/ievent.h"
#define API_INTERFACE_ICAMERA "system/interface/icamera.h"
#define API_INTERFACE_IFIGURE "system/interface/graphics/ifigure.h"
#define API_INTERFACE_IRENDER "system/interface/graphics/irender.h"
#define API_INTERFACE_ISHADER "system/interface/graphics/ishader.h"

#define API_INTERFACE_IMESH "system/interface/graphics/imesh.h"
#define API_INTERFACE_IOBJECT "system/interface/iobject.h"
#define API_INTERFACE_IWORLD "system/interface/iworld.h"

#ifdef API_INTERFACE_ALL_INCLUDE // define before api.h

#include API_INTERFACE_IBASE
#include API_INTERFACE_IWINDOW
#include API_INTERFACE_IEVENT
#include API_INTERFACE_ICAMERA
#include API_INTERFACE_IFIGURE
#include API_INTERFACE_IRENDER
#include API_INTERFACE_ISHADER
#include API_INTERFACE_IMESH
#include API_INTERFACE_IOBJECT
#include API_INTERFACE_IWORLD

#undef API_INTERFACE_ALL_INCLUDE

#endif
