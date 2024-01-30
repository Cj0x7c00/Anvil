#pragma once

#include "core/src/Base/anvApplication.hpp"
#include "core/src/Layer/anvLayer.hpp"
#include "core/src/Scene/Scene.h"
#include "core/src/Scene/Entity.h"
#include "core/src/Scene/Components.h"
#include "core/src/Util/Time/anvTimeStep.hpp"
#include "core/src/Util/anvLog.hpp"

/*=== RENDERING ===*/
#include "core/src/Renderer/Renderer.h"
#include "core/src/Renderer/GrComp/GraphicsFactory.h" // Shaders, Pipelines

typedef Anvil::Ref<Anvil::Scene>    SCENE;
typedef Anvil::Entity               ENTITY;

typedef Anvil::Ref<Anvil::Shader>	SHADER;
typedef Anvil::Ref<Anvil::Pipeline> PIPELINE;


