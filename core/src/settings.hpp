/**
 * 
 * This file will be used later on...
 * 
 */


#pragma once

#define VERSION 0
#define ENGINE_NAME "Anvil Engine ver. 0.0.0"
#define DEBUG      // Mode ~NDEBUG

#ifdef __APPLE__
 #define PLATFORM_APPLE 1
#endif
#ifndef __APPLE__
 #error "UNKNOWN PLATFORM"
#endif

struct Anvil_Settings
{
    struct Graphics_Settings
    {
        bool VSYNC = true;
    } Graphics_Settings;
} Anvil_Settings;

//#define PATH_TO_VULKAN "../include/Vulkan/vulkan.h"
//#define PATH_TO_GLFW "../include/GLFW/glfw3.h"