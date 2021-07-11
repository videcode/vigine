#pragma once

#include <vector>
#include "queue.h"

namespace graphics {
	namespace vulkan {
		class Family{
			public:
				Family();

			private:
				unsigned int		index{0};
				std::vector<Queue*>	queueArr;
		};
	}
}
