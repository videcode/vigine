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

