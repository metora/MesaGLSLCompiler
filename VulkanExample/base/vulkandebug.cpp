/*
* Vulkan examples debug wrapper
*
* Copyright (C) 2016 by Sascha Willems - www.saschawillems.de
*
* This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
*/

#include "vulkandebug.h"
#include <iostream>

namespace vkDebug
{
	int validationLayerCount = 9;
	const char *validationLayerNames[] = 
	{
		"VK_LAYER_GOOGLE_threading",
		"VK_LAYER_LUNARG_mem_tracker",
		"VK_LAYER_LUNARG_object_tracker",
		"VK_LAYER_LUNARG_draw_state",
		"VK_LAYER_LUNARG_param_checker",
		"VK_LAYER_LUNARG_swapchain",
		"VK_LAYER_LUNARG_device_limits",
		"VK_LAYER_LUNARG_image",
		"VK_LAYER_GOOGLE_unique_objects",
	};

    std::vector <VkLayerProperties> kAvailableLayers;
    std::vector <const char*> kValidationLayers;

	PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallback;
	PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallback;
	PFN_vkDebugReportMessageEXT dbgBreakCallback;

	VkDebugReportCallbackEXT msgCallback;

	VkBool32 __stdcall messageCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject,
		size_t location,
		int32_t msgCode,
		const char* pLayerPrefix,
		const char* pMsg,
		void* pUserData)
	{
		char *message = (char *)malloc(strlen(pMsg) + 100);

		assert(message);

		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		{
			std::cout << "ERROR: " << "[" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg << "\n";
		}
		else
			if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
			{
				// Uncomment to see warnings
				//std::cout << "WARNING: " << "[" << pLayerPrefix << "] Code " << msgCode << " : " << pMsg << "\n";
			}
			else
			{
				return false;
			}

		fflush(stdout);

		free(message);
		return false;
	}

    void checkValidationLayerSupport ()
    {
        kValidationLayers.clear ();
        unsigned int uiLayerCount = 0;
        vkEnumerateInstanceLayerProperties (&uiLayerCount, NULL);
        kAvailableLayers.resize (uiLayerCount);
        vkEnumerateInstanceLayerProperties (&uiLayerCount, &kAvailableLayers [0]);
#if 0
        std::vector <VkLayerProperties>::iterator kIt;
        for (unsigned int uiIndex = 0; uiIndex < iValidationLayerCount; uiIndex++) {
            for (kIt = kAvailableLayers.begin (); kIt != kAvailableLayers.end (); ++kIt) {
                VkLayerProperties& kProp = *kIt;
                if (strcmp (pcValidationLayerNames [uiIndex], kProp.layerName) == 0) {
                    kValidationLayers.push_back (kProp.layerName);
                    break;
                }
            }
        }
#else
        std::vector <VkLayerProperties>::iterator kIt;
        for (kIt = kAvailableLayers.begin (); kIt != kAvailableLayers.end (); ++kIt) {
            VkLayerProperties& kProp = *kIt;
            if (strcmp ("VK_LAYER_RENDERDOC_Capture", kProp.layerName) == 0)
                continue;
            if (strcmp ("VK_LAYER_NV_optimus", kProp.layerName) == 0)
                continue;
            if (strcmp ("VK_LAYER_LUNARG_api_dump", kProp.layerName) == 0)
                continue;
            if (strcmp ("VK_LAYER_LUNARG_screenshot", kProp.layerName) == 0)
                continue;
            if (strcmp ("VK_LAYER_LUNARG_vktrace", kProp.layerName) == 0)
                continue;
            kValidationLayers.push_back (kProp.layerName);
        }

#endif
    }

	void setupDebugging(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportCallbackEXT callBack)
	{
		CreateDebugReportCallback = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		DestroyDebugReportCallback = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		dbgBreakCallback = (PFN_vkDebugReportMessageEXT)vkGetInstanceProcAddr(instance, "vkDebugReportMessageEXT");

		VkDebugReportCallbackCreateInfoEXT dbgCreateInfo;
		dbgCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
		dbgCreateInfo.pNext = NULL;
		dbgCreateInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)messageCallback;
		dbgCreateInfo.pUserData = NULL;
		dbgCreateInfo.flags = flags;
		VkDebugReportCallbackEXT debugReportCallback;
		VkResult err = CreateDebugReportCallback(
			instance,
			&dbgCreateInfo,
			NULL,
			&debugReportCallback);
		assert(!err);


	}
	
	void freeDebugCallback(VkInstance instance)
	{
		if (msgCallback != NULL)
		{
			DestroyDebugReportCallback(instance, msgCallback, nullptr);
		}
	}
}