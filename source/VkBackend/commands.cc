#include<backends/vulkan.hh>

OpenSportSim::Backend::Vulkan::CommandFactory::CommandFactory(const vk::Device& device, const uint32_t graphicsQFamIndex): device(device) {
	vk::CommandPoolCreateInfo createInfo{
		.flags = vk::CommandPoolCreateFlags(),
		.queueFamilyIndex = graphicsQFamIndex
	};
	this->pool = device.createCommandPool(createInfo);
}
OpenSportSim::Backend::Vulkan::CommandFactory::~CommandFactory() { this->device.destroyCommandPool(this->pool); }
const size_t* OpenSportSim::Backend::Vulkan::CommandFactory::AllocateBuffers(const uint32_t quantity) {
	vk::CommandBufferAllocateInfo allocInfo{
		.commandPool = this->pool,
		.level = vk::CommandBufferLevel::ePrimary,
		.commandBufferCount = quantity
	};
	auto buffers = this->device.allocateCommandBuffers(allocInfo);
	size_t* indices = new size_t[quantity];
	for (size_t i = 0; i < buffers.size(); i++) {
		indices[i] = this->buffers.size();
		this->buffers.push_back(buffers[i]);
	}
	return indices;
}

