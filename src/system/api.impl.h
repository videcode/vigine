#pragma once

#define API_INTERFACE_IWINDOW_IMPL	"system/subsystem/os/iwindow.impl.h"
#define API_INTERFACE_IEVENT_IMPL	"subsystem/core/ievent.impl.h"
#define API_INTERFACE_ICAMERA_IMPL	"subsystem/camera/icamera.impl.h"
#define API_INTERFACE_IFIGURE_IMPL	"subsystem/graphics/ifigure.impl.h"
#define API_INTERFACE_IRENDER_IMPL	"subsystem/graphics/vulkan/irender.impl.h"

#ifdef API_INTERFACE_ALL_IMPL_INCLUDE // define before api.impl.h

    #include API_INTERFACE_IWINDOW_IMPL
    #include API_INTERFACE_IEVENT_IMPL
    #include API_INTERFACE_ICAMERA_IMPL
    #include API_INTERFACE_IFIGURE_IMPL
    #include API_INTERFACE_IRENDER_IMPL

    #undef API_INTERFACE_ALL_IMPL_INCLUDE

#endif
