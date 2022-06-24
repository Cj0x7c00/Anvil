#include "anvLayer.hpp"

namespace AnvilEngine
{
    AnvilLayer::AnvilLayer(const std::string name) : layer_name{name} { ENGINE_INFO("Layer Created: " + layer_name, "`AnvilLayer()`"); }

    void AnvilLayer::Attach(){};
    void AnvilLayer::Update(){};
    void AnvilLayer::Detach(){};
}

/**
 * Hi! This Layer commit will be the LAST commit until AUG 21st!
 * Reson Being:
 * 
 *  _____                           ______                        _____                                                _                       _ 
 *  (____ \                         / _____)                      (_____)        _                                _    (_)                     | |
 *   _   \ \  ____  _   _  ____    | /       ___    ____  ____       _    ____  | |_   ____   ____  ____    ____ | |_   _   ___   ____    ____ | |
 *  | |   | |/ ___)| | | ||    \   | |      / _ \  / ___)|  _ \     | |  |  _ \ |  _) / _  ) / ___)|  _ \  / _  ||  _) | | / _ \ |  _ \  / _  || |
 *  | |__/ /| |    | |_| || | | |  | \_____| |_| || |    | | | |   _| |_ | | | || |__( (/ / | |    | | | |( ( | || |__ | || |_| || | | |( ( | || |
 *  |_____/ |_|     \____||_|_|_|   \______)\___/ |_|    | ||_/   (_____)|_| |_| \___)\____)|_|    |_| |_| \_||_| \___)|_| \___/ |_| |_| \_||_||_|
 *                                                       |_|                                                                                      
 * YES! I will be preforming with the Guardians Drum and Bugle Corp for their 2022 season!
 * and after that - its UI time >:)
 * 
 */