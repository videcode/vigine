#pragma once

#include <string>
#include <type_traits>
#include "interface/graphics/ishader.h"

namespace subsystem {
	namespace graphics {
		class Shader{
			public:
				void destroy(){}
				void compile(){}
				void use(){}
				void path(std::string pathStr){}
				unsigned int id(){return this->id_;}

			private:
				unsigned int id_{0};
		};
	}
}


/*
namespace render {
class iShader {

public:
  enum class TYPE { VERTEX = 0, FRAGMENT, PROGRAMM };

  iShader(){};
  virtual ~iShader(){};

  virtual void compile() = 0;
  virtual void use() = 0;

  template <iShader::TYPE shader_type> void path(std::string pathIn) {

    if constexpr (shader_type == iShader::TYPE::VERTEX) {
      this->pathVertex = pathIn;

    } else if constexpr (shader_type == iShader::TYPE::FRAGMENT) {
      this->pathFragment = pathIn;
    }
  }

  template <iShader::TYPE shader_type> unsigned int id() {

    if constexpr (shader_type == iShader::TYPE::VERTEX) {
      return this->idVertex;

    } else if constexpr (shader_type == iShader::TYPE::FRAGMENT) {
      return this->idFragment;

    } else if constexpr (shader_type == iShader::TYPE::PROGRAMM) {
      return this->idProgram;

    } else
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
} // namespace render
*/
