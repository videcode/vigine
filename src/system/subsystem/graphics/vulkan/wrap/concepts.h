#pragma once

#include <concepts>

template<typename TClass>
concept cInfo = requires(TClass obj){
    {obj.getInfo()};
};

