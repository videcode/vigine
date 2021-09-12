#pragma once

#include "api.h"
#include API_INTERFACE_IFIGURE

#include <vector>
#include "interface/graphics/ifigure.h"
#include "api/graphics/shader.h"


namespace subsystem{
	namespace graphics {
		class Figure{
			public:
				void destroy(){}
				void shader(std::shared_ptr<api::Shader> spShaderIn){
					this->spShader = spShaderIn;
				}
				std::shared_ptr<api::Shader> shader(){return this->spShader;}

			private:
				std::shared_ptr<api::Shader> spShader;
		};
	}
}



namespace render {
/*
class Figure : public api::iFigure {
public:
  Figure();
  virtual ~Figure();

  void change(){};
  void shader(api::iShader *pShd) { this->pShader = pShd; }
  api::iShader *shader() { return this->pShader; }
  void matrix(const glm::mat4 &matrixIn) { this->matrix_ = matrixIn; }
  glm::mat4 matrix() { return this->matrix_; }
  glm::mat4 &rmatrix() { return this->matrix_; }

  template <TYPE arr_t> size_t arrSize() {

    if constexpr (arr_t == TYPE::VERTEX) {
      return this->vertexArr.size();
    } else if constexpr (arr_t == TYPE::NORMAL) {
      return this->normalArr.size();
    } else if constexpr (arr_t == TYPE::COLOR) {
      return this->colorArr.size();
    } else if constexpr (arr_t == TYPE::VERTEX_INDEX) {
      return this->vertexIndexArr.size();
    } /*else
         static_assert(false, "ARR_SIZE bad type in func size_t arrSize()");

  }

  template <TYPE arr_t> size_t arrSizeof() {

    if constexpr (arr_t == TYPE::VERTEX) {
      return this->vertexArr.size() * sizeof(glm::vec3);
    } else if constexpr (arr_t == TYPE::NORMAL) {
      return this->normalArr.size() * sizeof(glm::vec3);
    } else if constexpr (arr_t == TYPE::COLOR) {
      return this->colorArr.size() * sizeof(glm::vec3);
    } else if constexpr (arr_t == TYPE::VERTEX_INDEX) {
      return this->vertexIndexArr.size() * sizeof(unsigned int);
    } /*else
         static_assert(false, "ARR_SIZE bad type in func size_t arrSizeof()");

  }

  template <TYPE arr_t> auto *arrData() {

    if constexpr (arr_t == TYPE::VERTEX) {
      return this->vertexArr.data();
    } else if constexpr (arr_t == TYPE::NORMAL) {
      return this->normalArr.data();
    } else if constexpr (arr_t == TYPE::COLOR) {
      return this->colorArr.data();
    } else if constexpr (arr_t == TYPE::VERTEX_INDEX) {
      return this->vertexIndexArr.data();
    } /*else
         static_assert(false, "ARR_SIZE bad type in func size_t arrData()");

  }

protected:
  std::vector<glm::vec3> vertexArr;
  std::vector<glm::vec3> normalArr;
  std::vector<glm::vec3> colorArr;

  std::vector<unsigned int> vertexIndexArr;

  glm::mat4 matrix_; // Model
  api::iShader *pShader{nullptr};
  // Texture     texture;

private:
};
*/
} // namespace render
