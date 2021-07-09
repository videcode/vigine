#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>

#include "../ishader.h"
#include "opengl.h"


namespace render{
    namespace OpenGL{
        class Shader: public iShader{
            public:
                Shader(){};
                virtual ~Shader(){};

                void compile() override{

                    auto func_compile = [](unsigned int id, std::string& path){

                        std::string shaderCode;
                        std::ifstream VertexShaderStream(path.c_str(), std::ios::in);
                        if(VertexShaderStream.is_open()){
                            std::stringstream sstr;
                            sstr << VertexShaderStream.rdbuf();
                            shaderCode = sstr.str();
                            VertexShaderStream.close();
//std::cout << "shader code: " << shaderCode << std::endl;
std::cout << "shader id: " << id << std::endl;

                            OpenGL::GLint Result = GL_FALSE;
                            int InfoLogLength;

                            // Compile Shader
                            //printf("Compiling shader::base : %s\n", this->path.c_str());
                            OpenGL::GLchar const* vertexSourcePointer = shaderCode.c_str();
                            OpenGL::glShaderSource(id, 1, &vertexSourcePointer , NULL);
                            OpenGL::glCompileShader(id);

                            // Check Shader
                            OpenGL::glGetShaderiv(id, GL_COMPILE_STATUS, &Result);
                            OpenGL::glGetShaderiv(id, GL_INFO_LOG_LENGTH, &InfoLogLength);
                            if ( InfoLogLength > 0 ){
                                GLchar* buf = (GLchar*)malloc(sizeof(GLchar)*InfoLogLength+1);
                                //std::vector<char> vertexShaderErrorMessage(InfoLogLength+1);
                                OpenGL::glGetShaderInfoLog(id, InfoLogLength, NULL, buf);

                                std::cout << "shader func_compile (" << std::string(buf) << ") InfoLogLength: " << InfoLogLength << std::endl;
                                free(buf);
                                //exit(0);
                            }

                        }else{
                            printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", path.c_str());
                            exit(0);
                        }
                    };

                    // vertex shader compile
                    this->idVertex      = OpenGL::glCreateShader(GL_VERTEX_SHADER);
                    this->idFragment    = OpenGL::glCreateShader(GL_FRAGMENT_SHADER);
std::cout << "this->idVertex id: " << OpenGL::glCreateShader(GL_VERTEX_SHADER) << " err: " << GL_INVALID_ENUM << std::endl;

                    func_compile(this->idVertex, this->pathVertex);
                    func_compile(this->idFragment, this->pathFragment);

                    this->idProgram = OpenGL::glCreateProgram();
                    OpenGL::glAttachShader(this->idProgram, this->idVertex);
                    OpenGL::glAttachShader(this->idProgram, this->idFragment);
                    OpenGL::glLinkProgram(this->idProgram);


                    // Check the program
                    OpenGL::GLint Result = GL_FALSE;
                    int InfoLogLength;
                    OpenGL::glGetProgramiv(this->idProgram, GL_LINK_STATUS, &Result);
                    OpenGL::glGetProgramiv(this->idProgram, GL_INFO_LOG_LENGTH, &InfoLogLength);
                    if ( InfoLogLength > 0 ){
                        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
                        OpenGL::glGetProgramInfoLog(this->idProgram, InfoLogLength, NULL, &ProgramErrorMessage[0]);
                        printf("%s\n", &ProgramErrorMessage[0]);
                    }


                    OpenGL::glDetachShader(this->idProgram, this->idVertex);
                    OpenGL::glDetachShader(this->idProgram, this->idFragment);

                    OpenGL::glDeleteShader(this->idVertex);
                    OpenGL::glDeleteShader(this->idFragment);

                }

                void use() override{
                    OpenGL::glUseProgram(this->idProgram);
                }

            protected:

            private:
        };
    }
}

