#pragma once
#define VULKAN_HPP_NO_CONSTRUCTORS
#include<vulkan/vulkan.hpp>
#include<string>
#include<cstdint>
#include<vector>
#include<memory>

namespace OpenSportSim {
struct AppInfo {
	std::string Name;
	uint32_t Version;
};
namespace Backend {
namespace Vulkan {
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
	vk::Instance instance;
	vk::Device device;
	std::unique_ptr<CommandFactory> commandFactory;
	void createDevice();
public:
	Context(const AppInfo&);
	~Context();
	CommandFactory& GetCommandFactory();
};

};// Vulkan
};// Backend
};// OpenSportSim
