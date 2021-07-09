#pragma once

#include "api.h"
#include API_INTERFACE_IBASE

namespace api{

	class iShader: public iBase{
		public:

			enum class TYPE{
				VERTEX = 0,
				FRAGMENT,
				PROGRAMM
			};


			iShader(){};
			virtual ~iShader(){};

			virtual void compile()	= 0;
			virtual void use()		= 0;

			template<iShader::TYPE shader_type>
			void path(std::string pathIn);

			template<iShader::TYPE shader_type>
			unsigned int id();

		protected:
		private:
	};
}



namespace render{
	class iShader{

		public:
            enum class TYPE{
                VERTEX = 0,
                FRAGMENT,
                PROGRAMM
            };


            iShader(){};
            virtual ~iShader(){};

			virtual void compile()                  = 0;
			virtual void use()                      = 0;

            template<iShader::TYPE shader_type>
			void path(std::string pathIn){

				if constexpr(shader_type == iShader::TYPE::VERTEX){
					this->pathVertex = pathIn;

				}else if constexpr(shader_type == iShader::TYPE::FRAGMENT){
					this->pathFragment = pathIn;
				}

			}

            template<iShader::TYPE shader_type>
			unsigned int id(){

				if constexpr(shader_type == iShader::TYPE::VERTEX){
					return this->idVertex;

				}else if constexpr(shader_type == iShader::TYPE::FRAGMENT){
					return this->idFragment;

				}else if constexpr(shader_type == iShader::TYPE::PROGRAMM){
					return this->idProgram;

				}else
				    return 0;

			}

		protected:
			unsigned int idProgram{0};
			unsigned int idVertex{0};
			unsigned int idFragment{0};

			std::string pathVertex;
			std::string pathFragment;

        private:
    };
}

























