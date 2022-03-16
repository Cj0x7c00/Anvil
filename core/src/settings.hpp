/**
 * 
 * This file will be used later on...
 * 
 */


#pragma once

#define VERSION 0
#define DEBUG      // Mode ~NDEBUG

#ifdef __APPLE__
 #define PLATFORM_APPLE
#endif
#ifndef __APPLE__
 #error "UNKNOWN PLATFORM"
#endif

//#define PATH_TO_VULKAN "../include/Vulkan/vulkan.h"
//#define PATH_TO_GLFW "../include/GLFW/glfw3.h"