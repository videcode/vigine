#pragma once

#include <concepts>

template<typename TClass>
concept cInfo = requires(TClass obj){
    requires std::is_lvalue_reference_v<decltype(obj.getInfo())>;
    requires requires (decltype(obj.getInfo()) info){
        info.sType;
        info.pNext;
    };
};

template<typename TClass>
concept cDestroy = requires(TClass obj){
    obj.destroy();
};

template<typename TClass>
concept cInstance = requires (TClass obj){
    requires cInfo<TClass>;
    requires cDestroy<TClass>;
};

template<typename TClass>
concept cDevice = requires (TClass obj){
    requires cInfo<TClass>;
    requires cDestroy<TClass>;
};

template<typename TClass>
concept cSurface = requires (TClass obj){
    requires cInfo<TClass>;
    requires cDestroy<TClass>;
};

template<typename TClass>
concept cBuffer = requires (TClass obj){
    requires cInfo<TClass>;
    //requires cDestroy<TClass>;
};

template<cInfo T>
using cInfo_t = T;

template<cInstance T>
using cInst_t = T;

template<cDevice T>
using cDevice_t = T;

template<cSurface T>
using cSurf_t = T;

template<cBuffer T>
using cBuff_t = T;





