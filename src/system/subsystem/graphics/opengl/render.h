#pragma once

#include "../irender.h"
#include "opengl.h"


namespace render{

    namespace OpenGL{

        struct RenderObject{

            iFigure* pFig{nullptr};

            OpenGL::GLuint vbo{0};
            OpenGL::GLuint vao{0};
            OpenGL::GLuint normalBuffer{0};
            OpenGL::GLuint colorBuffer{0};
            OpenGL::GLuint textureCoordBuffer{0};

            OpenGL::GLuint textureId{0};
            OpenGL::GLuint matrixId{0};

            glm::mat4 MVP{glm::mat4(1.0f)};
        };

        RenderObject*   make_render_object();
        void            destroy_render_object(RenderObject* pRendObj);

        class Render: public render::iRender{
            public:
                		/* opengl structs */
                OpenGL::GLXContext           glc;
                OpenGL::GLint                attr[5]{ GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };


                Render(){
                    std::cout << "Render constructor" << std::endl;
                };
                virtual ~Render(){};

                void init() override {
                    //OpenGL::glEnable(GL_MULTISAMPLE);
                    OpenGL::glEnable(GL_DEPTH_TEST);
                    // Accept fragment if it closer to the camera than the former one
                    OpenGL::glDepthFunc(GL_LESS);
                    //OpenGL::glEnable(GL_CULL_FACE);
                    OpenGL::glEnable(GL_BLEND);
                    OpenGL::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                }

                void reg(iFigure* pFig) override{

                    pFig->shader()->compile();

                    RenderObject* pRendObj = make_render_object();
                    pRendObj->pFig = pFig;

                    OpenGL::glGenVertexArrays(1, &pRendObj->vao);
                    OpenGL::glGenBuffers(1, &pRendObj->vbo);

                    OpenGL::glBindVertexArray(pRendObj->vao);
                    {
                        OpenGL::glBindBuffer(GL_ARRAY_BUFFER, pRendObj->vbo);
                        {
                           OpenGL::glBufferData
                                    (
                                        GL_ARRAY_BUFFER,
                                        pRendObj->pFig->arrSizeof<iFigure::TYPE::VERTEX>(),
                                        pRendObj->pFig->arrData<iFigure::TYPE::VERTEX>(),
                                        GL_STATIC_DRAW
                                    );
                            OpenGL::glEnableVertexAttribArray(static_cast<OpenGL::GLuint>(iFigure::TYPE::VERTEX));
                            OpenGL::glVertexAttribPointer(
                                static_cast<OpenGL::GLuint>(iFigure::TYPE::VERTEX),           // attribute. No particular reason for 1, but must match the layout in the shader.
                                3,           // size
                                GL_FLOAT,    // type
                                GL_FALSE,    // normalized?
                                0,           // stride
                                (void*)0     // array buffer offset
                            );

                            OpenGL::glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
                        }

                        if(pRendObj->pFig->arrSize<iFigure::TYPE::NORMAL>() > 0){
                            OpenGL::glGenBuffers(1, &pRendObj->normalBuffer);
                            OpenGL::glBindBuffer(GL_ARRAY_BUFFER, pRendObj->normalBuffer);
                            {
                               OpenGL::glBufferData
                                        (
                                            GL_ARRAY_BUFFER,
                                            pRendObj->pFig->arrSizeof<iFigure::TYPE::NORMAL>(),
                                            pRendObj->pFig->arrData<iFigure::TYPE::NORMAL>(),
                                            GL_STATIC_DRAW
                                        );
                                OpenGL::glEnableVertexAttribArray(static_cast<OpenGL::GLuint>(iFigure::TYPE::NORMAL));
                                OpenGL::glVertexAttribPointer(
                                    static_cast<OpenGL::GLuint>(iFigure::TYPE::NORMAL),           // attribute. No particular reason for 1, but must match the layout in the shader.
                                    3,           // size
                                    GL_FLOAT,    // type
                                    GL_FALSE,    // normalized?
                                    0,           // stride
                                    (void*)0     // array buffer offset
                                );

                                OpenGL::glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
                            }
                        }

                        if(pRendObj->pFig->arrSize<iFigure::TYPE::COLOR>() > 0){
                            OpenGL::glGenBuffers(1, &pRendObj->colorBuffer);
                            OpenGL::glBindBuffer(GL_ARRAY_BUFFER, pRendObj->colorBuffer);
                            {
                               OpenGL::glBufferData
                                        (
                                            GL_ARRAY_BUFFER,
                                            pRendObj->pFig->arrSizeof<iFigure::TYPE::COLOR>(),
                                            pRendObj->pFig->arrData<iFigure::TYPE::COLOR>(),
                                            GL_STATIC_DRAW
                                        );
                                OpenGL::glEnableVertexAttribArray(static_cast<OpenGL::GLuint>(iFigure::TYPE::COLOR));
                                OpenGL::glVertexAttribPointer(
                                    static_cast<OpenGL::GLuint>(iFigure::TYPE::COLOR),           // attribute. No particular reason for 1, but must match the layout in the shader.
                                    3,           // size
                                    GL_FLOAT,    // type
                                    GL_FALSE,    // normalized?
                                    0,           // stride
                                    (void*)0     // array buffer offset
                                );

                                OpenGL::glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
                            }
                        }
                    }
                    OpenGL::glBindVertexArray(0); // unbind VAO

                    // register matrix in shader
                    pRendObj->matrixId = (OpenGL::GLuint)OpenGL::glGetUniformLocation(pFig->shader()->id<iShader::TYPE::PROGRAMM>(), "MVP");

                    this->rendArr.push_back(pRendObj);
                }

                void draw() override{
                    // draw all objects

                    for(auto itemRendObj: this->rendArr){

                        OpenGL::glBindVertexArray(itemRendObj->vao);

                        {// insert matrix in shader
                            itemRendObj->pFig->shader()->use();

                            itemRendObj->MVP   = this->pCam_->proj();           // project
                            itemRendObj->MVP  *= this->pCam_->view();           // view
                            itemRendObj->MVP  *= itemRendObj->pFig->matrix();   // model

                            OpenGL::glUniformMatrix4fv(itemRendObj->matrixId, 1, GL_FALSE, &itemRendObj->MVP[0][0]);
                        }


                        OpenGL::glDrawElements(
                                    GL_TRIANGLES,
                                    itemRendObj->pFig->arrSize<iFigure::TYPE::VERTEX_INDEX>(),
                                    GL_UNSIGNED_INT,
                                    itemRendObj->pFig->arrData<iFigure::TYPE::VERTEX_INDEX>()
                                );
                    }
                    OpenGL::glBindVertexArray(0); // unbind last VAO

                    // update changed objects
                    upd();
                }

                void upd() override{
                    //std::cout << "render upd()" << std::endl;
                }

            protected:

            private:
                std::vector<RenderObject*> rendArr;
        };
    }
}





























