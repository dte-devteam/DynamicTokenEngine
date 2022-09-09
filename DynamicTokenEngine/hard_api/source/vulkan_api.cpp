#include "../include/vulkan_api.h"
VkBool32 hard_api::debugcallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageseverity, VkDebugUtilsMessageTypeFlagsEXT messagetype, const VkDebugUtilsMessengerCallbackDataEXT* callbackdata, void* userdata) {
	std::cerr << callbackdata->pMessage << std::endl;
	return VK_FALSE;
}
std::vector<const char*> hard_api::getrequiredextensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwext = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	std::vector<const char*> extensions(glfwext, glfwext + glfwExtensionCount);
	#ifndef NDEBUG
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	#endif
	return extensions;
}
VkResult hard_api::fillswapchainsupportdetails(hard_api::swapchainsupportdetails* details, VkPhysicalDevice physicaldevice, VkSurfaceKHR surface) {
	VkResult res;
	res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicaldevice, surface, &details->capabilities);
	if (VK_FAILED(res)) return res; //add log
	uint32_t num;
	res = vkGetPhysicalDeviceSurfaceFormatsKHR(physicaldevice, surface, &num, nullptr);
	if (VK_FAILED(res)) return res; //add log
	details->formats.resize(num);
	res = vkGetPhysicalDeviceSurfaceFormatsKHR(physicaldevice, surface, &num, details->formats.data());
	if (VK_FAILED(res)) return res; //add log
	res = vkGetPhysicalDeviceSurfacePresentModesKHR(physicaldevice, surface, &num, nullptr);
	if (VK_FAILED(res)) return res; //add log
	details->presentmodes.resize(num);
	return vkGetPhysicalDeviceSurfacePresentModesKHR(physicaldevice, surface, &num, details->presentmodes.data());
}





hard_api::window::window() {
	win = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr); //изменить и сделать более гибким
}
hard_api::window::~window() {
	//vkDestroySwapchainKHR(*device, swapchain, nullptr);
	vkDestroySurfaceKHR(*VK_INSTANCE->getinstance(), surface, nullptr);
	glfwDestroyWindow(win);
}
bool hard_api::window::createsurface() {
	vkres = glfwCreateWindowSurface(*VK_INSTANCE->getinstance(), win, nullptr, &surface);
	return vkres == VK_SUCCESS;
}
bool hard_api::window::createswapchain(VkDevice* device) {
	//vkCreateSwapchainKHR(*device, &createInfo, nullptr, &swapChain);
	//to do
	return true;
}
VkSurfaceKHR* hard_api::window::getsurface() {
	return &surface;
}
GLFWwindow* hard_api::window::getwin() {
	return win;
}
VkResult hard_api::window::getvkres() {
	return vkres;
}
VkSurfaceFormatKHR hard_api::window::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}





hard_api::logicdevice::logicdevice(VkPhysicalDevice physicaldevice, const VkDeviceCreateInfo* createinfo) {
	vkres = vkCreateDevice(physicaldevice, createinfo, nullptr, &device);
	vkGetDeviceQueue(device, createinfo->pQueueCreateInfos[0].queueFamilyIndex, 0, &graphicsqueue);
	vkGetDeviceQueue(device, createinfo->pQueueCreateInfos[1].queueFamilyIndex, 0, &presentqueue);
}
hard_api::logicdevice::~logicdevice() {
	vkDestroyDevice(device, nullptr);
}
VkDevice* hard_api::logicdevice::getdevice() {
	return &device;
}
VkResult hard_api::logicdevice::getvkres() {
	return vkres;
}









hard_api::vk_instance* hard_api::vk_instance::getvk_instance(std::string appname) {
	if (!self) self = new vk_instance(appname);
	return self;
}
void hard_api::vk_instance::release() {
	if (self) delete self;
	self = nullptr;
}
void hard_api::vk_instance::createlogicdevice(hard_api::logicdevice* &devicepointer, uint32_t queueflagbits, const VkDeviceCreateInfo* createinfo, const rategpuweights* weights) {
	devicepointer = nullptr;
	//to do
}
VkInstance* hard_api::vk_instance::getinstance() {
	return &instance;
}
void hard_api::vk_instance::createwindow(hard_api::window* &win) {
	win = new window;
	if (!win->createsurface()) {
		delete win;
		win = nullptr;
		std::cout << "e1"; //add log
		return;
	}
	std::vector<VkPhysicalDevice> gpu_list = findgpu();
	std::vector<std::pair<VkPhysicalDevice*, float>> siutable_gpu_list;
	for (VkPhysicalDevice gpu : gpu_list) {
		if (isgpusiutable(gpu) && fillqueuefamilyindices(gpu, win->getsurface()).iscomplete() && fillswapchainsupportdetails(gpu, win->getsurface()).swapchainsupported()) {
			siutable_gpu_list.push_back(std::make_pair(&gpu, rategpu(gpu)));
		}
	}
	if (siutable_gpu_list.empty()) {
		delete win;
		win = nullptr;
		std::cout << "e2";
		return; //add log
	}
	size_t i = std::distance(siutable_gpu_list.begin(), std::max_element(siutable_gpu_list.begin(), siutable_gpu_list.end(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; }));
	queuefamilyindices indices = fillqueuefamilyindices(*siutable_gpu_list[i].first, win->getsurface());
	float priority = 1.0f;
	std::vector<VkDeviceQueueCreateInfo> queuecreateinfos;
	std::vector<const char*> extensions = getrequiredextensions();
	std::set<uint32_t> uniquequeuefamilies = { indices.graphicsfamily.value(), indices.presentfamily.value() };
	for (uint32_t queuefamily : uniquequeuefamilies) {
		VkDeviceQueueCreateInfo queuecreateinfo;
		queuecreateinfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queuecreateinfo.pNext = nullptr;
		queuecreateinfo.flags = 0;
		queuecreateinfo.queueFamilyIndex = queuefamily;
		queuecreateinfo.queueCount = 1;
		queuecreateinfo.pQueuePriorities = &priority;
		queuecreateinfos.push_back(queuecreateinfo);
	}
	VkPhysicalDeviceFeatures devicefeatures;
	vkGetPhysicalDeviceFeatures(*siutable_gpu_list[i].first, &devicefeatures);
	VkDeviceCreateInfo createinfo;
	createinfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createinfo.pNext = nullptr;
	createinfo.flags = 0;
	createinfo.queueCreateInfoCount = static_cast<uint32_t>(queuecreateinfos.size());
	createinfo.pQueueCreateInfos = queuecreateinfos.data();
	createinfo.enabledLayerCount = static_cast<uint32_t>(extensions.size());
	createinfo.ppEnabledLayerNames = extensions.data();;
	createinfo.enabledExtensionCount = static_cast<uint32_t>(deviceextensions.size());;
	createinfo.ppEnabledExtensionNames = deviceextensions.data();
	createinfo.pEnabledFeatures = &devicefeatures;
	logicdevices.push_back(logicdevice(*siutable_gpu_list[i].first, &createinfo));
	if (VK_FAILED(logicdevices.back().getvkres())) {
		delete win;
		win = nullptr;
		logicdevices.pop_back();
		std::cout << "e3";
		return; //add log
	}
}
bool hard_api::vk_instance::swapchainsupportdetails::swapchainsupported() {
	return !(formats.empty() || presentmodes.empty());
}
hard_api::vk_instance::vk_instance(std::string appname) {
	#ifndef NDEBUG
		const VkDebugUtilsMessengerCreateInfoEXT* debugmessengerpointer = &debugmessengercreateinfo;
	#else
		const VkDebugUtilsMessengerCreateInfoEXT* debugmessengerpointer = nullptr;
	#endif
	std::vector<const char*> extensions = getrequiredextensions();
	VkApplicationInfo appinfo;
	appinfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appinfo.pNext = nullptr,					
	appinfo.pApplicationName = appname.c_str(),				
	appinfo.applicationVersion = VK_MAKE_VERSION(0, 0, 0);	
	appinfo.pEngineName = "DynamicTokenEngine";			
	appinfo.engineVersion = 0;				
	appinfo.apiVersion = VK_API_VERSION_1_0;
	VkInstanceCreateInfo createinfo;
	createinfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createinfo.pNext = debugmessengerpointer;
	createinfo.flags = NULL;
	createinfo.pApplicationInfo = &appinfo;
	createinfo.enabledLayerCount = 0;
	createinfo.ppEnabledLayerNames = nullptr;
	createinfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createinfo.ppEnabledExtensionNames = extensions.data();
	vkres = vkCreateInstance(&createinfo, nullptr, &instance);
	#ifndef NDEBUG
		vkres = createdebugmessenger(&debugmessenger);
	#endif
}
hard_api::vk_instance::~vk_instance() {
	destroydebugmessenger();
	vkDestroyInstance(instance, nullptr);
}
std::vector<VkPhysicalDevice> hard_api::vk_instance::findgpu() {
	VkResult vkres;
	uint32_t num;
	vkres = vkEnumeratePhysicalDevices(instance, &num, nullptr);
	if (VK_FAILED(vkres)) {
		//log error
		return std::vector<VkPhysicalDevice>(0);
	}
	std::vector<VkPhysicalDevice> gpu_list(num);
	vkres = vkEnumeratePhysicalDevices(instance, &num, gpu_list.data());
	if (VK_FAILED(vkres)) {
		//log error
		return std::vector<VkPhysicalDevice>(0);
	}
	return gpu_list;
}
float hard_api::vk_instance::rategpu(VkPhysicalDevice device, const hard_api::vk_instance::rategpuweights* weights) {
	float score = 0.0f;
	VkPhysicalDeviceProperties deviceproperties;
	VkPhysicalDeviceFeatures devicefeatures;
	vkGetPhysicalDeviceProperties(device, &deviceproperties);
	vkGetPhysicalDeviceFeatures(device, &devicefeatures);
	if (!devicefeatures.geometryShader && weights->mustsupportgeomtericshaders) return score;
	if (deviceproperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) score += weights->isdiscrete;
	score += weights->d2dsize * deviceproperties.limits.maxImageDimension2D;
	score += weights->d3dsize * deviceproperties.limits.maxImageDimension3D;
	return score;
}
hard_api::vk_instance::queuefamilyindices hard_api::vk_instance::fillqueuefamilyindices(VkPhysicalDevice device, VkSurfaceKHR* surface) {
	queuefamilyindices familyindices;
	uint32_t num = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &num, nullptr);
	std::vector<VkQueueFamilyProperties> queuefamilies(num);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &num, queuefamilies.data());
	uint32_t i = 0;
	VkBool32 presentsupport = false;
	for (const auto& queuefamily : queuefamilies) {
		if (queuefamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			familyindices.graphicsfamily = i;
		}
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, *surface, &presentsupport);
		if (presentsupport) {
			familyindices.presentfamily = i;
		}
		if (familyindices.iscomplete()) {
			break;
		}
		i++;
	}
	return familyindices;
}
hard_api::vk_instance::swapchainsupportdetails hard_api::vk_instance::fillswapchainsupportdetails(VkPhysicalDevice device, VkSurfaceKHR* surface) {
	swapchainsupportdetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, *surface, &details.capabilities);
	uint32_t num;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, *surface, &num, nullptr);
	details.formats.resize(num);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, *surface, &num, details.formats.data());
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, *surface, &num, nullptr);
	details.presentmodes.resize(num);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, *surface, &num, details.presentmodes.data());
	return details;
}
bool hard_api::vk_instance::isgpusiutable(VkPhysicalDevice device) {
	VkPhysicalDeviceFeatures devicefeatures;
	vkGetPhysicalDeviceFeatures(device, &devicefeatures);
	return devicefeatures.geometryShader && extensionssupported(device);
}
bool hard_api::vk_instance::extensionssupported(VkPhysicalDevice device) {
	uint32_t num;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &num, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(num);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &num, availableExtensions.data());
	std::set<std::string> requiredextensions(deviceextensions.begin(), deviceextensions.end());
	for (const auto& extension : availableExtensions) {
		requiredextensions.erase(extension.extensionName);
	}
	return requiredextensions.empty();
}
VkResult hard_api::vk_instance::createdebugmessenger(VkDebugUtilsMessengerEXT* debugmessenger, const VkAllocationCallbacks* pallocator) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func) {
		return func(instance, &debugmessengercreateinfo, nullptr, debugmessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}
void hard_api::vk_instance::destroydebugmessenger(const VkAllocationCallbacks* pallocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func) {
		func(instance, debugmessenger, pallocator);
	}
}