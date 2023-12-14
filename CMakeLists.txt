cmake_minimum_required(VERSION 3.6)
project(OpenSportSim-Engine)
find_package(Vulkan REQUIRED)
add_library(OpenSportSim_VkBackend source/VkBackend/graphics.cc source/VkBackend/commands.cc)
target_link_libraries(OpenSportSim_VkBackend ${Vulkan_LIBRARIES})
target_include_directories(OpenSportSim_VkBackend PRIVATE ${Vulkan_INCLUDE_DIRS} PRIVATE include/)
set_property(TARGET OpenSportSim_VkBackend PROPERTY CXX_STANDARD 20)

