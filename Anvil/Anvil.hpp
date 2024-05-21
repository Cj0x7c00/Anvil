#pragma once

#include "core/src/Base/anvApplication.hpp"
#include "core/src/Layer/anvLayer.hpp"
#include "core/src/Scene/Scene.h"
#include "core/src/Scene/Entity.h"
#include "core/src/Util/Time/anvTimeStep.hpp"
#include "core/src/Util/anvLog.hpp"

/*=== RENDERING ===*/
#include "core/src/Renderer/Renderer.h"
#include "core/src/Renderer/GrComp/GraphicsFactory.h" // Shaders, Pipelines
#include "core/src/Renderer/Camera.h"

/*====== UI ======*/
#include "core/src/UI/Canvas.h"
#include "core/src/UI/CanvasItems.h"

/*==== TYPES ====*/
typedef Anvil::Ref<Anvil::Scene>    SCENE;
typedef Anvil::Ref<Anvil::Entity>   ENTITY;

typedef Anvil::Ref<Anvil::Shader>	SHADER;
typedef Anvil::Ref<Anvil::Pipeline> PIPELINE;
typedef Anvil::Ref<Anvil::Camera>   CAMERA;

typedef Anvil::UI_Button UI_BUTTON;
typedef Anvil::UI_Window UI_WINDOW;
typedef Anvil::UI_Menue  UI_MENUE;



