#include "irender.impl.h"
using namespace std;

graphics::vulkan::Render::Render(){

}

graphics::vulkan::Render::~Render()
{
	std::cout << "Render destructor" << std::endl;
}


void graphics::vulkan::Render::init(){
	this->inst.init();
}

void graphics::vulkan::Render::reg(std::shared_ptr<api::iFigure> fig){

}

void graphics::vulkan::Render::draw(){

}

void graphics::vulkan::Render::upd(){

}

void graphics::vulkan::Render::xlibInit(X11::Window win, X11::Display* dpy){
	this->inst.xlibData(win, dpy);
}

void graphics::vulkan::print_prop(vk::PhysicalDevice& device, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    VkPhysicalDeviceProperties prop;
    vkGetPhysicalDeviceProperties(device, &prop);

    cout << "apiVersion: " << prop.apiVersion << endl;
    cout << "driverVersion: " << prop.driverVersion << endl;
    cout << "vendorID: " << prop.vendorID << endl;
    cout << "deviceID: " << prop.deviceID << endl;
    cout << "deviceName: " << prop.deviceName << endl;

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::PhysicalDeviceMemoryProperties& memProp){
    using namespace std;

    cout << "memoryTypeCount: " << memProp.memoryTypeCount << endl;
    cout << "memoryHeapCount: " << memProp.memoryHeapCount << endl;

    for(int i = 0;i < memProp.memoryTypeCount;i++){
		vk::MemoryType memType = memProp.memoryTypes[i];
        cout << "memoryType: [" << i << "]: " << endl;
        cout << "   heapIndex: " << memType.heapIndex << endl;

		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eDeviceLocal){
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostVisible){
            cout << "   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostCoherent){
            cout << "   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_COHERENT_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eHostCached){
            cout << "   VK_MEMORY_PROPERTY_HOST_CACHED_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_HOST_CACHED_BIT is 0" << endl;
        }
		if(memType.propertyFlags & vk::MemoryPropertyFlagBits::eLazilyAllocated){
            cout << "   VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT is 0" << endl;
        }

        print("   ---");
    }

    for(int i = 0;i < memProp.memoryHeapCount;i++){
        VkMemoryHeap memHeap = memProp.memoryHeaps[i];
        cout << "memoryHeap [" << i << "]: " << endl;
        cout << "   size: " << memHeap.size << endl;

        // Provided by VK_VERSION_1_0
        if(memHeap.flags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT){
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT is 0" << endl;
        }

        // Provided by VK_VERSION_1_1
        if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT){
            cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 1" << endl;
        }else {
            cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 0" << endl;
        }

        // Provided by VK_KHR_device_group_creation
        // VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR = VK_MEMORY_HEAP_MULTI_INSTANCE_BIT
        #ifdef VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR
            if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR){
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR is 1" << endl;
            }else {
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR is 0" << endl;
            }
            #else
            if(memHeap.flags & VK_MEMORY_HEAP_MULTI_INSTANCE_BIT){
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 1" << endl;
            }else {
                cout << "   VK_MEMORY_HEAP_MULTI_INSTANCE_BIT is 0" << endl;
            }
        #endif // VK_MEMORY_HEAP_MULTI_INSTANCE_BIT_KHR


        print("   ---");
    }


}

void graphics::vulkan::print_prop(vk::LayerProperties& prop){
    using namespace std;

    cout << "layerName: " << prop.layerName << endl;
}

void graphics::vulkan::print_prop(vk::ExtensionProperties& extProp){
    using namespace std;

    cout << "extName: " << extProp.extensionName << endl;
}

void graphics::vulkan::print_prop(vk::QueueFamilyProperties& prop, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    cout << "VkQueueFamilyProperties.queueCount: " << prop.queueCount << endl;
    cout << "VkQueueFamilyProperties.timestampValidBits: " << prop.timestampValidBits << endl;

	if(prop.queueFlags & vk::QueueFlagBits::eGraphics){
        cout << "   VK_QUEUE_GRAPHICS_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_GRAPHICS_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eCompute){
        cout << "   VK_QUEUE_COMPUTE_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_COMPUTE_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eTransfer){
        cout << "   VK_QUEUE_TRANSFER_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_TRANSFER_BIT is 0" << endl;
    }
	if(prop.queueFlags & vk::QueueFlagBits::eSparseBinding){
        cout << "   VK_QUEUE_SPARSE_BINDING_BIT is 1" << endl;
    }else {
        cout << "   VK_QUEUE_SPARSE_BINDING_BIT is 0" << endl;
    }

    cout << "VkQueueFamilyProperties.minImageTransferGranularity: " << endl;
    cout << "   width: " << prop.minImageTransferGranularity.width << endl;
    cout << "   height: " << prop.minImageTransferGranularity.height << endl;
    cout << "   depth: " << prop.minImageTransferGranularity.depth << endl;

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::PhysicalDeviceFeatures& prop, std::string str){
    using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

    if(prop.robustBufferAccess == VK_TRUE){
        cout << "   robustBufferAccess: true" << endl;
    }else{
        cout << "   robustBufferAccess: false" << endl;
    }

    if(prop.fullDrawIndexUint32 == VK_TRUE){
        cout << "   fullDrawIndexUint32: true" << endl;
    }else{
        cout << "   fullDrawIndexUint32: false" << endl;
    }

    if(prop.imageCubeArray == VK_TRUE){
        cout << "   imageCubeArray: true" << endl;
    }else{
        cout << "   imageCubeArray: false" << endl;
    }

    if(prop.independentBlend == VK_TRUE){
        cout << "   independentBlend: true" << endl;
    }else{
        cout << "   independentBlend: false" << endl;
    }

    if(prop.geometryShader == VK_TRUE){
        cout << "   geometryShader: true" << endl;
    }else{
        cout << "   geometryShader: false" << endl;
    }

    if(prop.tessellationShader == VK_TRUE){
        cout << "   tessellationShader: true" << endl;
    }else{
        cout << "   tessellationShader: false" << endl;
    }

    if(prop.sampleRateShading == VK_TRUE){
        cout << "   sampleRateShading: true" << endl;
    }else{
        cout << "   sampleRateShading: false" << endl;
    }

    if(prop.dualSrcBlend == VK_TRUE){
        cout << "   dualSrcBlend: true" << endl;
    }else{
        cout << "   dualSrcBlend: false" << endl;
    }

    if(prop.logicOp == VK_TRUE){
        cout << "   logicOp: true" << endl;
    }else{
        cout << "   logicOp: false" << endl;
    }

    if(prop.multiDrawIndirect == VK_TRUE){
        cout << "   multiDrawIndirect: true" << endl;
    }else{
        cout << "   multiDrawIndirect: false" << endl;
    }

    if(prop.drawIndirectFirstInstance == VK_TRUE){
        cout << "   drawIndirectFirstInstance: true" << endl;
    }else{
        cout << "   drawIndirectFirstInstance: false" << endl;
    }

    if(prop.depthClamp == VK_TRUE){
        cout << "   depthClamp: true" << endl;
    }else{
        cout << "   depthClamp: false" << endl;
    }

    if(prop.depthBiasClamp == VK_TRUE){
        cout << "   depthBiasClamp: true" << endl;
    }else{
        cout << "   depthBiasClamp: false" << endl;
    }

    if(prop.fillModeNonSolid == VK_TRUE){
        cout << "   fillModeNonSolid: true" << endl;
    }else{
        cout << "   fillModeNonSolid: false" << endl;
    }

    if(prop.depthBounds == VK_TRUE){
        cout << "   depthBounds: true" << endl;
    }else{
        cout << "   depthBounds: false" << endl;
    }

    if(prop.wideLines == VK_TRUE){
        cout << "   wideLines: true" << endl;
    }else{
        cout << "   wideLines: false" << endl;
    }

    if(prop.largePoints == VK_TRUE){
        cout << "   largePoints: true" << endl;
    }else{
        cout << "   largePoints: false" << endl;
    }

    if(prop.alphaToOne == VK_TRUE){
        cout << "   alphaToOne: true" << endl;
    }else{
        cout << "   alphaToOne: false" << endl;
    }

    if(prop.multiViewport == VK_TRUE){
        cout << "   multiViewport: true" << endl;
    }else{
        cout << "   multiViewport: false" << endl;
    }

    if(prop.samplerAnisotropy == VK_TRUE){
        cout << "   samplerAnisotropy: true" << endl;
    }else{
        cout << "   samplerAnisotropy: false" << endl;
    }

    if(prop.textureCompressionETC2 == VK_TRUE){
        cout << "   textureCompressionETC2: true" << endl;
    }else{
        cout << "   textureCompressionETC2: false" << endl;
    }

    if(prop.textureCompressionASTC_LDR == VK_TRUE){
        cout << "   textureCompressionASTC_LDR: true" << endl;
    }else{
        cout << "   textureCompressionASTC_LDR: false" << endl;
    }

    if(prop.textureCompressionBC == VK_TRUE){
        cout << "   textureCompressionBC: true" << endl;
    }else{
        cout << "   textureCompressionBC: false" << endl;
    }

    if(prop.occlusionQueryPrecise == VK_TRUE){
        cout << "   occlusionQueryPrecise: true" << endl;
    }else{
        cout << "   occlusionQueryPrecise: false" << endl;
    }

    if(prop.pipelineStatisticsQuery == VK_TRUE){
        cout << "   pipelineStatisticsQuery: true" << endl;
    }else{
        cout << "   pipelineStatisticsQuery: false" << endl;
    }

    if(prop.vertexPipelineStoresAndAtomics == VK_TRUE){
        cout << "   vertexPipelineStoresAndAtomics: true" << endl;
    }else{
        cout << "   vertexPipelineStoresAndAtomics: false" << endl;
    }

    if(prop.fragmentStoresAndAtomics == VK_TRUE){
        cout << "   fragmentStoresAndAtomics: true" << endl;
    }else{
        cout << "   fragmentStoresAndAtomics: false" << endl;
    }

    if(prop.shaderTessellationAndGeometryPointSize == VK_TRUE){
        cout << "   shaderTessellationAndGeometryPointSize: true" << endl;
    }else{
        cout << "   shaderTessellationAndGeometryPointSize: false" << endl;
    }

    if(prop.shaderImageGatherExtended == VK_TRUE){
        cout << "   shaderImageGatherExtended: true" << endl;
    }else{
        cout << "   shaderImageGatherExtended: false" << endl;
    }

    if(prop.shaderStorageImageExtendedFormats == VK_TRUE){
        cout << "   shaderStorageImageExtendedFormats: true" << endl;
    }else{
        cout << "   shaderStorageImageExtendedFormats: false" << endl;
    }

    if(prop.shaderStorageImageMultisample == VK_TRUE){
        cout << "   shaderStorageImageMultisample: true" << endl;
    }else{
        cout << "   shaderStorageImageMultisample: false" << endl;
    }

    if(prop.shaderStorageImageReadWithoutFormat == VK_TRUE){
        cout << "   shaderStorageImageReadWithoutFormat: true" << endl;
    }else{
        cout << "   shaderStorageImageReadWithoutFormat: false" << endl;
    }

    if(prop.shaderStorageImageWriteWithoutFormat == VK_TRUE){
        cout << "   shaderStorageImageWriteWithoutFormat: true" << endl;
    }else{
        cout << "   shaderStorageImageWriteWithoutFormat: false" << endl;
    }

    if(prop.shaderUniformBufferArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderUniformBufferArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderUniformBufferArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderSampledImageArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderSampledImageArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderSampledImageArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderStorageBufferArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderStorageBufferArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderStorageBufferArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderStorageImageArrayDynamicIndexing == VK_TRUE){
        cout << "   shaderStorageImageArrayDynamicIndexing: true" << endl;
    }else{
        cout << "   shaderStorageImageArrayDynamicIndexing: false" << endl;
    }

    if(prop.shaderClipDistance == VK_TRUE){
        cout << "   shaderClipDistance: true" << endl;
    }else{
        cout << "   shaderClipDistance: false" << endl;
    }

    if(prop.shaderCullDistance == VK_TRUE){
        cout << "   shaderCullDistance: true" << endl;
    }else{
        cout << "   shaderCullDistance: false" << endl;
    }

    if(prop.shaderFloat64 == VK_TRUE){
        cout << "   shaderFloat64: true" << endl;
    }else{
        cout << "   shaderFloat64: false" << endl;
    }

    if(prop.shaderInt64 == VK_TRUE){
        cout << "   shaderInt64: true" << endl;
    }else{
        cout << "   shaderInt64: false" << endl;
    }

    if(prop.shaderInt16 == VK_TRUE){
        cout << "   shaderInt16: true" << endl;
    }else{
        cout << "   shaderInt16: false" << endl;
    }

    if(prop.shaderResourceResidency == VK_TRUE){
        cout << "   shaderResourceResidency: true" << endl;
    }else{
        cout << "   shaderResourceResidency: false" << endl;
    }

    if(prop.shaderResourceMinLod == VK_TRUE){
        cout << "   shaderResourceMinLod: true" << endl;
    }else{
        cout << "   shaderResourceMinLod: false" << endl;
    }

    if(prop.sparseBinding == VK_TRUE){
        cout << "   sparseBinding: true" << endl;
    }else{
        cout << "   sparseBinding: false" << endl;
    }

    if(prop.sparseResidencyBuffer == VK_TRUE){
        cout << "   sparseResidencyBuffer: true" << endl;
    }else{
        cout << "   sparseResidencyBuffer: false" << endl;
    }

    if(prop.sparseResidencyImage2D == VK_TRUE){
        cout << "   sparseResidencyImage2D: true" << endl;
    }else{
        cout << "   sparseResidencyImage2D: false" << endl;
    }

    if(prop.sparseResidencyImage3D == VK_TRUE){
        cout << "   sparseResidencyImage3D: true" << endl;
    }else{
        cout << "   sparseResidencyImage3D: false" << endl;
    }

    if(prop.sparseResidency2Samples == VK_TRUE){
        cout << "   sparseResidency2Samples: true" << endl;
    }else{
        cout << "   sparseResidency2Samples: false" << endl;
    }

    if(prop.sparseResidency4Samples == VK_TRUE){
        cout << "   sparseResidency4Samples: true" << endl;
    }else{
        cout << "   sparseResidency4Samples: false" << endl;
    }

    if(prop.sparseResidency8Samples == VK_TRUE){
        cout << "   sparseResidency8Samples: true" << endl;
    }else{
        cout << "   sparseResidency8Samples: false" << endl;
    }

    if(prop.sparseResidency16Samples == VK_TRUE){
        cout << "   sparseResidency16Samples: true" << endl;
    }else{
        cout << "   sparseResidency16Samples: false" << endl;
    }

    if(prop.sparseResidencyAliased == VK_TRUE){
        cout << "   sparseResidencyAliased: true" << endl;
    }else{
        cout << "   sparseResidencyAliased: false" << endl;
    }

    if(prop.variableMultisampleRate == VK_TRUE){
        cout << "   variableMultisampleRate: true" << endl;
    }else{
        cout << "   variableMultisampleRate: false" << endl;
    }

    if(prop.inheritedQueries == VK_TRUE){
        cout << "   inheritedQueries: true" << endl;
    }else{
        cout << "   inheritedQueries: false" << endl;
    }

	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(std::vector<vk::PresentModeKHR>& arr, string str){
}

void graphics::vulkan::print_prop(vk::SurfaceCapabilitiesKHR& var, string str){

	using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

	/*
// Provided by VK_KHR_surface
typedef struct VkSurfaceCapabilitiesKHR {
	uint32_t                         minImageCount;
	uint32_t                         maxImageCount;
	VkExtent2D                       currentExtent;
	VkExtent2D                       minImageExtent;
	VkExtent2D                       maxImageExtent;
	uint32_t                         maxImageArrayLayers;
	VkSurfaceTransformFlagsKHR       supportedTransforms;
	VkSurfaceTransformFlagBitsKHR    currentTransform;
	VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
	VkImageUsageFlags                supportedUsageFlags;
} VkSurfaceCapabilitiesKHR;
	*/
	print(".minImageCount: " + std::to_string(var.minImageCount));
	print(".maxImageCount: " + std::to_string(var.maxImageCount));
	print(".maxImageArrayLayers: " + std::to_string(var.maxImageArrayLayers));
	print_extent<2>(var.currentExtent, ".currentExtent");
	print_extent<2>(var.currentExtent, ".minImageExtent");
	print_extent<2>(var.currentExtent, ".maxImageExtent");

	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eIdentity, ".supportedTransforms.eIdentity");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate90, ".supportedTransforms.eRotate90");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate180, ".supportedTransforms.eRotate180");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eRotate270, ".supportedTransforms.eRotate270");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror, ".supportedTransforms.eHorizontalMirror");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90, ".supportedTransforms.eHorizontalMirrorRotate90");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180, ".supportedTransforms.eHorizontalMirrorRotate180");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270, ".supportedTransforms.eHorizontalMirrorRotate270");
	print_bit(var.supportedTransforms, vk::SurfaceTransformFlagBitsKHR::eInherit, ".supportedTransforms.eInherit");
	print(" ");

	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eIdentity, ".currentTransform.eIdentity");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate90, ".currentTransform.eRotate90");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate180, ".currentTransform.eRotate180");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eRotate270, ".currentTransform.eRotate270");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirror, ".currentTransform.eHorizontalMirror");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate90, ".currentTransform.eHorizontalMirrorRotate90");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate180, ".currentTransform.eHorizontalMirrorRotate180");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eHorizontalMirrorRotate270, ".currentTransform.eHorizontalMirrorRotate270");
	print_bit(var.currentTransform, vk::SurfaceTransformFlagBitsKHR::eInherit, ".currentTransform.eInherit");
	print(" ");

	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::eOpaque, ".supportedCompositeAlpha.eOpaque");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::ePreMultiplied, ".supportedCompositeAlpha.ePreMultiplied");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::ePostMultiplied, ".supportedCompositeAlpha.ePostMultiplied");
	print_bit(var.supportedCompositeAlpha, vk::CompositeAlphaFlagBitsKHR::eInherit, ".supportedCompositeAlpha.eInherit");
	print(" ");

	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eSampled, ".supportedUsageFlags.eSampled");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eStorage, ".supportedUsageFlags.eStorage");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eColorAttachment, ".supportedUsageFlags.eColorAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eDepthStencilAttachment, ".supportedUsageFlags.eDepthStencilAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eInputAttachment, ".supportedUsageFlags.eInputAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eTransientAttachment, ".supportedUsageFlags.eTransientAttachment");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eFragmentShadingRateAttachmentKHR, ".supportedUsageFlags.eFragmentShadingRateAttachmentKHR");
	print_bit(var.supportedUsageFlags, vk::ImageUsageFlagBits::eFragmentDensityMapEXT, ".supportedUsageFlags.eFragmentDensityMapEXT");


	if(!str.empty())
		print("--- end "+str+" ---");
}

void graphics::vulkan::print_prop(vk::SurfaceFormatKHR& var, string str){

	using namespace std;
	if(!str.empty())
		print("--- "+str+" ---");

	print(".format."+vk::to_string(var.format));
	print(".colorSpace."+vk::to_string(var.colorSpace));

	if(!str.empty())
		print("--- end "+str+" ---");
}

template<typename T, typename T2>
void graphics::vulkan::print_bit(T var, T2 var2, string str, bool print_if_eual){
	if(var & var2)
		print(str+": 1");
	else
		if(!print_if_eual)
			print(str+": 0");

}

template<typename T, typename T2>
void graphics::vulkan::print_equal(T var, T2 var2, string str ){
	if(var == var2)
		print(str);
}

template<int n, typename T>
void graphics::vulkan::print_extent(T var, std::string str){

	if constexpr (n == 2){
		print(str+".width: "+std::to_string(var.width));
		print(str+".height: "+std::to_string(var.height));
	}
	if constexpr (n == 3){
		print(str+".width: "+std::to_string(var.width));
		print(str+".height: "+std::to_string(var.height));
		print(str+".depth: "+std::to_string(var.depth));
	}
}


