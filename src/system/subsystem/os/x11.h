#pragma once

namespace subsystem{
	namespace os {
		namespace X11 {
			extern "C" {
                #include<X11/X.h>
                #include<X11/Xutil.h>
                #include<X11/Xlib.h>
			}
		}
	}
}
