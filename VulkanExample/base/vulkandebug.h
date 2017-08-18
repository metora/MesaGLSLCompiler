#pragma once

#include "vulkan/vulkan.h"

#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <stdio.h>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#endif
#ifdef __ANDROID__
#include "vulkanandroid.h"
#endif

namespace vkDebug
{
	// Default validation layers
	extern int validationLayerCount;
	extern const char *validationLayerNames[];
    extern std::vector <VkLayerProperties> kAvailableLayers;
    extern std::vector <const char*> kValidationLayers;

	// Default debug callback
	VkBool32 __stdcall messageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData);

    void checkValidationLayerSupport ();

	// Load debug function pointers and set debug callback
	// if callBack is NULL, default message callback will be used
	void setupDebugging(
		VkInstance instance, 
		VkDebugReportFlagsEXT flags, 
		VkDebugReportCallbackEXT callBack);
	// Clear debug callback
	void freeDebugCallback(VkInstance instance);
}
