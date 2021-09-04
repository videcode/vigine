#pragma once

#include <concepts>

template<typename TClass, typename TInfo>
concept cInfo = requires(TClass obj){
    {obj.getInfo()}-> std::same_as<TInfo> ;
};

template<typename TClass, typename TInfo> requires cInfo<TClass, TInfo>
class CheckInfo{};
