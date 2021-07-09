#include "render.h"

namespace render{
    namespace OpenGL{

        RenderObject* make_render_object(){
            return new RenderObject();
        }

        void destroy_render_object(RenderObject* pRendObj){

        }

    }
}
