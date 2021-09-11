#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
//#define GLM_EXTERNAL_TEMPLATE
#include "glm/ext.hpp"
#include "glm/glm.hpp"
//#undef GLM_EXTERNAL_TEMPLATE

namespace api {

	template <typename T, typename... V> void print(T var, V... v){
		if constexpr (sizeof... (V) > 0){
			std::cout << var << ", ";
			print(v...);
		}else
		    std::cout << var << std::endl;
	  }

	template <>
	inline void print<bool>(bool var){
		std::boolalpha(std::cout);
		std::cout << var << std::endl;
	 }

	template <>
	inline void print(const glm::vec3 &var){
		api::print("vec3: ");
		api::print("x/y/z: " + std::to_string(var.x) + " / " + std::to_string(var.y) +
		           " / " + std::to_string(var.z));
	 }

	template <>
	inline void print(const glm::mat4 &var){
		api::print("mat4: ");
		api::print("[0].x/[0].y/[0].z: " + std::to_string(var[0].x) + " / " +
		           std::to_string(var[0].y) + " / " + std::to_string(var[0].z));
		api::print("[1].x/[1].y/[1].z: " + std::to_string(var[1].x) + " / " +
		           std::to_string(var[1].y) + " / " + std::to_string(var[1].z));
		api::print("[2].x/[2].y/[2].z: " + std::to_string(var[2].x) + " / " +
		           std::to_string(var[2].y) + " / " + std::to_string(var[2].z));
	 }
}

