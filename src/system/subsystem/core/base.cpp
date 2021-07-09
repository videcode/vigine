#include "base.h"


namespace std{
    template class vector<glm::vec3>;
    template class vector<unsigned int>;
}

template<typename T, typename... V>
void print(T var){
    std::cout << var << std::endl;
}

template<>
inline void print<bool>(bool var){
    std::boolalpha(std::cout);
    std::cout << var << std::endl;
}

void print(const glm::vec3& var){
    print("vec3: ");
    print("x/y/z: " + std::to_string(var.x) + " / " + std::to_string(var.y)+ " / " + std::to_string(var.z));
}

void print(const glm::mat4& var){
    print("mat4: ");
    print("[0].x/[0].y/[0].z: " + std::to_string(var[0].x) + " / " + std::to_string(var[0].y)+ " / " + std::to_string(var[0].z));
    print("[1].x/[1].y/[1].z: " + std::to_string(var[1].x) + " / " + std::to_string(var[1].y)+ " / " + std::to_string(var[1].z));
    print("[2].x/[2].y/[2].z: " + std::to_string(var[2].x) + " / " + std::to_string(var[2].y)+ " / " + std::to_string(var[2].z));
}
