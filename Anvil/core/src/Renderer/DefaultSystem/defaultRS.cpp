#include "defaultRS.h"
#include <Util/anvLog.hpp>

namespace Anvil
{
	void defaultRS::Init()
	{
		load_shaders();
		create_pipeline();
	}

	void defaultRS::NewFrame()
	{
	}

	void defaultRS::load_shaders()
	{
		ENGINE_INFO("Default System: Loading Shaders");
		auto vert = GraphicsFactory::CreateShader("shaders/DefaultRSVert.glsl", VERTEX);
		auto frag = GraphicsFactory::CreateShader("shaders/DefaultRSFrag.glsl", FRAGMENT);

		m_Shaders.push_back(vert);
		m_Shaders.push_back(frag);
	}

	void defaultRS::create_pipeline()
	{
		ENGINE_INFO("Default System: Creating Pipeline");
		m_Pipeline = GraphicsFactory::CreatePipeline(m_Shaders);
	}
}