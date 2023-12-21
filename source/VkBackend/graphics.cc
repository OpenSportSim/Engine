#include<backends/vulkan.hh>
#include<optional>

inline vk::PhysicalDevice pickPhysicalDevice(vk::Instance& instance) {
	const auto physicalDevices = instance.enumeratePhysicalDevices();
	uint32_t score = 0;
	std::optional<vk::PhysicalDevice> best;
	best.value() = physicalDevices[0];
	return best.value();
}

OpenSportSim::Backend::Vulkan::Context::Context(const OpenSportSim::Backend::Vulkan::AppInfo& info) {
	vk::ApplicationInfo appInfo{
		.pApplicationName = info.Name.c_str(),
		.applicationVersion = info.Version,
		.pEngineName = "OpenSportSim",
		.engineVersion = 1,
		.apiVersion = VK_API_VERSION_1_1
	};
	vk::InstanceCreateInfo createInfo{
		.pApplicationInfo = &appInfo
	};
	this->instance = vk::createInstance(createInfo);
	this->createDevice();
}

OpenSportSim::Backend::Vulkan::Context::~Context() {
	this->commandFactory = nullptr;
	this->device.destroy();
	this->instance.destroy();
}

void OpenSportSim::Backend::Vulkan::Context::createDevice() {
	auto physicalDevice = pickPhysicalDevice(this->instance);
	auto qFamProp = physicalDevice.getQueueFamilyProperties();
	auto propertyIterator = std::find_if(qFamProp.begin(), qFamProp.end(), [](auto const & qfp){ return qfp.queueFlags & vk::QueueFlagBits::eGraphics;});
	size_t graphicsQueueFamIndex = std::distance(qFamProp.begin(), propertyIterator);
	assert(graphicsQueueFamIndex < qFamProp.size());

	auto qPriority = 0.0f;
	const vk::DeviceQueueCreateInfo queueCreateInfo{
		.flags = vk::DeviceQueueCreateFlags(),
		.queueFamilyIndex = static_cast<uint32_t>(graphicsQueueFamIndex),
		.pQueuePriorities = &qPriority
	};
	vk::DeviceCreateInfo createInfo{
		.flags = vk::DeviceCreateFlags(),
		.pQueueCreateInfos = &queueCreateInfo
	};
	vk::CommandPoolCreateInfo cmdPoolCreateInfo{
		.flags = vk::CommandPoolCreateFlags(),
		.queueFamilyIndex = queueCreateInfo.queueFamilyIndex
	};
	this->device = physicalDevice.createDevice(createInfo);
	this->commandFactory = std::make_unique<OpenSportSim::Backend::Vulkan::CommandFactory>(this->device, graphicsQueueFamIndex);
}

