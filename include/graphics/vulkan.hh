#pragma once
#define VULKAN_HPP_NO_CONSTRUCTORS
#include<vulkan/vulkan.hpp>
#include<string>
#include<memory>
#include<cstdint>
#include<vector>

namespace OpenSportSim {
namespace Backend {
namespace Vulkan {
struct AppInfo {
	std::string Name;
	uint32_t Version;
};
class CommandFactory {
	vk::CommandPool pool;
	std::vector<vk::CommandBuffer> buffers;
	const vk::Device& device;
public:
	CommandFactory(const vk::Device& device, const uint32_t graphicsQFamIndex);
	~CommandFactory();
	const size_t* AllocateBuffers(const uint32_t quantity);
	void DestroyBuffer(const size_t);
	vk::CommandBuffer& operator[](const size_t);
};
class Context {
	std::unique_ptr<CommandFactory> commandFactory;
	vk::Instance instance;
	vk::Device device;
	void createDevice();
public:
	Context(const AppInfo&);
	~Context();
	CommandFactory& GetCommandFactory();
};

};// Vulkan
};// Backend
};// OpenSportSim
