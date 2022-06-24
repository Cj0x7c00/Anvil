#include "basic_app.hpp"
#include <iostream>

namespace AnvilEngine
{

basic_anvApp::basic_anvApp() : AnvilLayer("Basic App Layer") {}

void basic_anvApp::Attach()
{
    std::cout << "Hello, Anvil! From youe dear friend, Basic App" << '\n';
    std::cout << "\t - Counter App!!!" << '\n';
}

void basic_anvApp::Update()
{
    if (counter % 152 == 0)
    {
        std::cout << counter <<"\n";
    }

    counter++;
}

void basic_anvApp::Detach()
{
    std::cout << "Layer Detach" << '\n';
}
}