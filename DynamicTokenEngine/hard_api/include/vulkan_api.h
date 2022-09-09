#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <string>
#include <optional>
#include <Windows.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
namespace hard_api {
	#define VK_FAILED(vkresult) vkresult != VK_SUCCESS
	#define E_VK_INSTANCE(arg) vk_instance::getvk_instance(arg)
	#define VK_INSTANCE E_VK_INSTANCE("DTE")
	struct swapchainsupportdetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentmodes;
	};
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugcallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageseverity, VkDebugUtilsMessageTypeFlagsEXT messagetype,const VkDebugUtilsMessengerCallbackDataEXT* callbackdata, void* userdata);
	inline std::vector<const char*> getrequiredextensions();
	inline VkResult fillswapchainsupportdetails(swapchainsupportdetails* details, VkPhysicalDevice physicaldevice, VkSurfaceKHR surface);
	class window {
		//сюда вписать и glfw и swapchain и поверхность
		public:
			window();
			~window();
			bool createsurface();
			bool createswapchain(VkDevice* device);
			VkSurfaceKHR* getsurface();
			GLFWwindow* getwin();
			VkResult getvkres();
		private:
			VkResult vkres = VK_SUCCESS;
			VkSurfaceKHR surface = VK_NULL_HANDLE;
			VkSwapchainKHR swapchain = VK_NULL_HANDLE;
			GLFWwindow* win;
			VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	};
	class logicdevice {
		public:
			logicdevice(VkPhysicalDevice physicaldevice, const VkDeviceCreateInfo* createinfo);
			~logicdevice();
			VkDevice* getdevice();
			VkResult getvkres();
		private:
			VkResult vkres;
			VkDevice device;
			VkQueue graphicsqueue;
			VkQueue presentqueue;
	};
	class vk_instance {
		public:
			struct rategpuweights {
				bool mustsupportgeomtericshaders = true;
				float isdiscrete = 1.0f;
				float d2dsize = 1.0f;
				float d3dsize = 1.0f;
			};
			static vk_instance* getvk_instance(std::string appname = "DTE");
			void release();
			void createlogicdevice(logicdevice* &devicepointer, uint32_t queueflagbits, const VkDeviceCreateInfo* createinfo, const rategpuweights* weights = &defaultweights);
			VkInstance* getinstance();
			void createwindow(window* &win);
		private:
			struct queuefamilyindices {
				std::optional<uint32_t> graphicsfamily;
				std::optional<uint32_t> presentfamily;
				bool iscomplete() {
					return graphicsfamily.has_value() && presentfamily.has_value();
				}
			};
			struct swapchainsupportdetails {
				VkSurfaceCapabilitiesKHR capabilities;
				std::vector<VkSurfaceFormatKHR> formats;
				std::vector<VkPresentModeKHR> presentmodes;
				bool swapchainsupported();
			};
			VkResult vkres;
			VkInstance instance;
			VkDebugUtilsMessengerEXT debugmessenger;
			std::vector<logicdevice> logicdevices;
			static inline vk_instance* self;
			static inline const rategpuweights defaultweights;
			const std::vector<const char*> validationLayers = {
				"VK_LAYER_KHRONOS_validation"
			};
			const std::vector<const char*> deviceextensions = {
				VK_KHR_SWAPCHAIN_EXTENSION_NAME
			};
			const VkDebugUtilsMessengerCreateInfoEXT debugmessengercreateinfo = {
				VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
				nullptr,
				NULL,
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
				debugcallback,
				nullptr
			};
			vk_instance(std::string appname);
			~vk_instance();
			std::vector<VkPhysicalDevice> findgpu();
			float rategpu(VkPhysicalDevice device, const rategpuweights* weights = &defaultweights);
			queuefamilyindices fillqueuefamilyindices(VkPhysicalDevice device, VkSurfaceKHR* surface);
			swapchainsupportdetails fillswapchainsupportdetails(VkPhysicalDevice device, VkSurfaceKHR* surface);
			bool isgpusiutable(VkPhysicalDevice device);
			bool extensionssupported(VkPhysicalDevice device);
			VkResult createdebugmessenger(VkDebugUtilsMessengerEXT* debugmessenger, const VkAllocationCallbacks* allocator = nullptr);
			void destroydebugmessenger(const VkAllocationCallbacks* allocator = nullptr);
	};
}