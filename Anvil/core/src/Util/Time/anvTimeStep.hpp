#pragma once
#include <GLFW/glfw3.h>


namespace Anvil
{
    class Timestep
    {
        public: 
          Timestep() = default;
          Timestep(float time) : mTime(time)
          {

          }

          float GetSeconds() {return mTime;}
          float GetMilliseconds() {return mTime * 1000.0;}
        private:

          float mTime;

    };
}