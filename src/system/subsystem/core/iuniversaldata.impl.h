#pragma once
#include <vector>
#include <any>
#include "interface/core/iuniversaldata.h"

namespace subsystem {
	namespace core {
		class UniversalData{
			public:
				UniversalData(){}

				void destroy(){
				};

				template<typename TData>
				void  set(TData data){this->vData.push_back(std::any(data));}

				template<typename TData>
				void  insert(TData data, unsigned int index){
					this->vData.insert(std::next(this->vData.begin(), index), std::any(data));
				}

				template<typename TData>
				TData get(unsigned int index){
					return std::any_cast<TData>(vData[index]);
				}
				void del(unsigned int index){
					this->vData.erase(std::next(this->vData.begin(), index));
				}
				size_t size(){return this->vData.size();}
			private:
				std::vector<std::any> vData;
		};
	}
}

