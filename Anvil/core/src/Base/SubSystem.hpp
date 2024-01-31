#pragma once
#include "Pointer.hpp"
#include ""

//namespace Anvil
//{
//
//	class AppSubSystem
//	{
//		virtual void Init() = 0;
//		virtual void Update() = 0;
//
//		virtual void OnEvent() = 0;
//	};
//
//    class EngineSubSystem {
//    public:
//        // Function to get the singleton instance
//        static Ref<EngineSubSystem> getInstance() {
//            // Create the instance if it doesn't exist
//            if (!instance) {
//                instance = Ref<EngineSubSystem>(new EngineSubSystem);
//            }
//            return instance;
//        }
//
//        // Your other member functions go here
//
//    private:
//        // Private constructor to prevent instantiation
//        EngineSubSystem(const char* name) {
//            ENGINE_INFO("Initializing: {}", name);
//        }
//
//        // Private destructor to prevent deletion
//        ~EngineSubSystem() {
//            // Cleanup if necessary
//        }
//
//        // Declare other private members as needed
//
//        // The singleton instance
//        static Ref<EngineSubSystem> instance;
//    };
//}