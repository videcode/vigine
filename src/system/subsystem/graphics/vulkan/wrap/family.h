#pragma once

#include "queue.h"

namespace graphics {
	namespace vulkan {
		class Family{
			public:
				Family();

			private:
				Queue queue;
		};
	}
}
