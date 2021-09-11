#pragma once
#include <vector>
#include <any>

namespace subsystem {
	namespace core {
		class UniversalData{
			public:
				UniversalData();

				void destroy(){
				};

				template<typename TData>
				void  set(TData data, unsigned int index){this->vData[index] = std::any(data);}
				template<typename TData>
				void  set(TData data){this->vData.push_back(std::any(data));}
				template<typename TData>
				TData get(unsigned int index){
					return std::any_cast<TData>(vData[index]);
				}
			private:
				std::vector<std::any> vData;
		};
	}
}

