#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <functional>

#define	GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE
#define GLM_ENABLE_EXPERIMENTAL
//#define GLM_EXTERNAL_TEMPLATE
    #include "glm/glm.hpp"
    #include "glm/ext.hpp"
//#undef GLM_EXTERNAL_TEMPLATE

template<typename T, typename... V>
void print(T var);

template<>
inline void print<bool>(bool var);

void print(const glm::vec3& var);
void print(const glm::mat4& var);
