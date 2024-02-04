#pragma once
#include "../Util/anvLog.hpp"
#include "../Base/anvpch.hpp"
#include "../Base/macros.hpp"
#include "../Base/Pointer.hpp"

struct VkExtent2D;

namespace Anvil
{
    typedef void (*ResizeCallbackFn)();

    struct Extent2D
    {
        int width;
        int height;

        bool operator==(const Extent2D& _ext)
        {
            if (_ext.width == width && _ext.height == height)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        Extent2D operator=(VkExtent2D& ext);
    };

    struct WindowProps
    {
        uint32_t width;
        uint32_t height;
        const char* name;

        WindowProps(uint32_t w=900, uint32_t h = 700, const char* n="Window")
            : width{w}, height{h}, name{n}
        {

        }
    };

 
    class Window
    {

        public:

            static Ref<Window> Create(WindowProps _p);

            virtual void ResetWindowResizedFlag() = 0;

            virtual void SetRezizeCallback(ResizeCallbackFn fn) = 0;

            virtual void PollEvents() = 0;

            virtual void* Get() = 0;

            virtual bool WasWindowResized() = 0;

            virtual bool ShouldClose() = 0;

            virtual Extent2D GetExtent() = 0;

            virtual void* GetSurface() = 0;
         
    private:
        WindowProps  m_Props;
            
    }; 


} 

