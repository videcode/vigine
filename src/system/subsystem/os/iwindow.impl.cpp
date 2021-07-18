#include "iwindow.impl.h"


subsystem::os::Window::Window(){
	std::cout << "linux::Window constructor" << std::endl;
}

subsystem::os::Window::~Window(){
	std::cout << "linux::Window destructor" << std::endl;
}

void subsystem::os::Window::init(){

	std::cout << "linux::Window init() "  << std::endl;


	this->dpy = X11::XOpenDisplay(NULL);

	if(this->dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0);
	}
	{
		using namespace X11;
		this->root = DefaultRootWindow(this->dpy);
	}

#ifdef RENDER_OPENGL
	std::cout << "create opengl context" << std::endl;

	render::OpenGL::Render* pRendLocal = static_cast<render::OpenGL::Render*>(this->pRend);

	///////////// render::OpenGL
	this->vi = render::OpenGL::glXChooseVisual(this->dpy, 0, pRendLocal->attr);

	if(this->vi == NULL) {
		 printf("\n\tno appropriate visual found\n\n");
		 exit(0);
	}else {
		 printf("\n\tvisual %p selected\n", (void *)this->vi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}

	this->cmap = X11::XCreateColormap(this->dpy, this->root, this->vi->visual, AllocNone);
	this->swa.colormap = this->cmap;
	this->swa.event_mask = ExposureMask |
	                 KeyPressMask		|
	                 ButtonPressMask	|
	                 ButtonReleaseMask	|
	                 Button1MotionMask	|
	                 Button2MotionMask	|
	                 Button3MotionMask  |
	                 StructureNotifyMask |
	                 SubstructureNotifyMask
	                 ;

	this->win = X11::XCreateWindow(this->dpy,
	                               this->root, 0, 0, this->width_, this->height_, 0,
	                               this->vi->depth,
	                               InputOutput,
	                               this->vi->visual,
	                               CWColormap | CWEventMask,
	                               &this->swa);

	X11::XMapWindow(this->dpy, this->win);
	X11::XStoreName(this->dpy, this->win, "VERY SIMPLE APPLICATION");


	std::cout << "create opengl context" << std::endl;

///////////// render::OpenGL
	pRendLocal->glc = render::OpenGL::glXCreateContext(this->dpy, this->vi, NULL, GL_TRUE);
	render::OpenGL::glXMakeCurrent(this->dpy, this->win, pRendLocal->glc);



	std::cout << "***********: " << this->height_ << std::endl;
	render::OpenGL::glViewport(0,0,this->width_,this->height_);


#else
    #ifdef RENDER_VULKAN

		{
			using namespace X11;
			//this->cmap = XCreateColormap(this->dpy, this->root, CopyFromParent, AllocNone);
			this->cmap = XDefaultColormap(this->dpy, XDefaultScreen(this->dpy));
			/*
			for (i=0; i <= 255 && i < colormap_size; i++)
				XAllocColor(this->dpy, cmap, &colors[i]);
*/
			this->swa.colormap = this->cmap;
			this->swa.event_mask = ExposureMask |
			                 KeyPressMask		|
			                 ButtonPressMask	|
			                 ButtonReleaseMask	|
			                 Button1MotionMask	|
			                 Button2MotionMask	|
			                 Button3MotionMask  |
			                 StructureNotifyMask |
			                 SubstructureNotifyMask
			                 ;
			this->win = XCreateWindow(this->dpy,
			                          this->root, 0, 0, this->width_, this->height_, 0,
			                          0,
			                          InputOutput,
			                          CopyFromParent,
			                          CWColormap | CWEventMask,
			                          &this->swa);

		}

	    //pRendLocal->xlibInit(this->win, this->dpy);
	    this->pRend->windowDisplaySystemData<api::WINDOW_DISPLAY_SYSTEM::x11>(this->win, this->dpy);
	    this->pRend->wh(this->width(), this->height());
    #endif
#endif

	    this->pRend->init();
}
void subsystem::os::Window::run(){

	auto pEventHelperClose = pEventClose->helper<api::iWindow::close_func_t>();
	auto pEventHelperResize = pEventResize->helper<api::iWindow::resize_func_t, int, int>();
	auto pEventHelperKeyPress = pEventKeyPress->helper<api::iWindow::keyPress_func_t, int>();
	auto pEventHelperClickLeft = pEventMouseClickLeft->helper<api::iWindow::mouseClickLeft_func_t, int, int>();
	auto pEventHelperClickRight = pEventMouseClickRight->helper<api::iWindow::mouseClickRight_func_t, int, int>();
	auto pEventHelperWheelUp = pEventMouseWheelUp->helper<api::iWindow::mouseWheelUp_func_t, int, int>();
	auto pEventHelperWheelDown = pEventMouseWheelDown->helper<api::iWindow::mouseWheelDown_func_t, int, int>();
	auto pEventHelperClickWheel = pEventMouseClickWheel->helper<api::iWindow::mouseClickWheel_func_t, int, int>();

	X11::Atom  atom1, atom2;

	atom1 = XInternAtom(this->dpy, "WM_PROTOCOLS", 0);
	atom2 = XInternAtom(this->dpy, "WM_DELETE_WINDOW", 0);
	X11::XSetWMProtocols(this->dpy, this->win, &atom1, 0);
	X11::XSetWMProtocols(this->dpy, this->win, &atom2, 1);
	X11::XMapWindow(this->dpy, this->win);

	while(1){
		X11::XGetWindowAttributes(this->dpy, this->win, &this->gwa);
		//X11::XNextEvent(this->dpy, &this->xev);;

		if(X11::XCheckTypedEvent (this->dpy, Expose, &this->xev)){
			this->width_	= this->gwa.width;
			this->height_	= this->gwa.height;

            #ifdef RENDER_OPENGL
			    render::OpenGL::glViewport(0,0, this->width_, this->height_);
                #else
                    #ifdef RENDER_VULKAN
			            std::cout << "error: not now render" << std::endl;
                    #endif // WINDOWS
            #endif // RENDER_OPENGL

						pEventHelperResize->on(this->width_, this->height_);
						//this->pEventClose.on();
						goto DRAW;
		}

		if(X11::XCheckTypedEvent (this->dpy, ClientMessage, &this->xev)){
			if(this->xev.xclient.message_type == atom1 && this->xev.xclient.data.l[0] == atom2) {
				pEventHelperClose->on();
				this->pRend->Delete();
				XDestroyWindow(this->dpy, this->xev.xclient.window);
				XCloseDisplay (this->dpy); // повинно бути розкоментоване
				break;
			}
			continue;
		}

		if(X11::XCheckTypedEvent (this->dpy, DestroyNotify, &this->xev)){

			break;
		}

		if(X11::XCheckTypedEvent (this->dpy, KeyPress, &this->xev)){

			pEventHelperKeyPress->on(this->xev.xkey.keycode);

			switch(this->xev.xkey.keycode){
				case 38: // a

					break;
				case 25: // w


					break;
				case 40: // d

					break;
				case 39: // s


					break;

				case 24: // q

					break;
				case 26: // e

					break;

				case 27: // r

					break;
			}

			goto DRAW;
		}

		if(X11::XCheckTypedEvent (this->dpy, ButtonPress, &this->xev)){

			switch (this->xev.xbutton.button) {
				case Button1:

					break;
				case Button2:

					break;
				case Button3:

					break;
				case Button4: // mouse wheel up

					break;
				case Button5: // mouse wheel down

					break;
			}

			goto DRAW;
		}

		if(X11::XCheckTypedEvent (this->dpy, ButtonRelease, &this->xev)){

			switch (this->xev.xbutton.button) {
				case Button1:

					pEventHelperClickLeft->on(xev.xbutton.x, xev.xbutton.y);
					break;
				case Button2:
					pEventHelperClickWheel->on(xev.xbutton.x, xev.xbutton.y);
					break;
				case Button3:
					pEventHelperClickRight->on(xev.xbutton.x, xev.xbutton.y);

					break;
				case Button4: // mouse wheel up
					pEventHelperWheelUp->on(xev.xbutton.x, xev.xbutton.y);
					break;
				case Button5: // mouse wheel down
					pEventHelperWheelDown->on(xev.xbutton.x, xev.xbutton.y);
					break;
			}

			goto DRAW;

		}

		if(X11::XCheckTypedEvent (this->dpy, MotionNotify, &this->xev)){

			goto DRAW;
		}


        DRAW:
		pRend->draw();
		X11::XFlush(this->dpy);

        #ifdef RENDER_OPENGL

		    render::OpenGL::glXSwapBuffers(this->dpy, this->win);

			render::OpenGL::glClearColor(0.0, 0.0, 0.0, 1.0f);
			render::OpenGL::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

            #else
                #ifdef RENDER_VULKAN
		            //std::cout << "error run(): not now render 2" << std::endl;
                #endif // WINDOWS
        #endif // RENDER_OPENGL
	}
}



