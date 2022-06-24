#include "app.hpp"

#include "simpleRenderSystem.hpp"

namespace AnvilEngine{

        class GravityPhysicsSystem {
        public:
        GravityPhysicsSystem(float strength) : strengthGravity{strength} {}
        RigidBody2dComponent rigidBody2d;
        const float strengthGravity;
        
        // dt stands for delta time, and specifies the amount of time to advance the simulation
        // substeps is how many intervals to divide the forward time step in. More substeps result in a
        // more stable simulation, but takes longer to compute
        void update(std::vector<anvGameObject>& objs, float dt, unsigned int substeps = 1) {
            const float stepDelta = dt / substeps;
            for (int i = 0; i < substeps; i++) {
            stepSimulation(objs, stepDelta);
            }
        }
        
        glm::vec2 computeForce(anvGameObject& fromObj, anvGameObject& toObj) const {
            auto offset = fromObj.transform2d.translation - toObj.transform2d.translation;
            float distanceSquared = glm::dot(offset, offset);
        
            // clown town - just going to return 0 if objects are too close together...
            if (glm::abs(distanceSquared) < 1e-10f) {
            return {.0f, .0f};
            }
        
            float force =
                strengthGravity * toObj.rigidBody2d.mass * fromObj.rigidBody2d.mass / distanceSquared;
            return force * offset / glm::sqrt(distanceSquared);
        }
        
        private:
        void stepSimulation(std::vector<anvGameObject>& physicsObjs, float dt) {
            // Loops through all pairs of objects and applies attractive force between them
            for (auto iterA = physicsObjs.begin(); iterA != physicsObjs.end(); ++iterA) {
            auto& objA = *iterA;
            for (auto iterB = iterA; iterB != physicsObjs.end(); ++iterB) {
                if (iterA == iterB) continue;
                auto& objB = *iterB;
        
                auto force = computeForce(objA, objB);
                objA.rigidBody2d.velocity += dt * -force / objA.rigidBody2d.mass;
                objB.rigidBody2d.velocity += dt * force / objB.rigidBody2d.mass;
            }
            }
        
            // update each objects position based on its final velocity
            for (auto& obj : physicsObjs) {
            obj.transform2d.translation += dt * obj.rigidBody2d.velocity;
            }
        }
    };
    
    class Vec2FieldSystem {
        public:
        void update(
            const GravityPhysicsSystem& physicsSystem,
            std::vector<anvGameObject>& physicsObjs,
            std::vector<anvGameObject>& vectorField) {
            // For each field line we caluclate the net graviation force for that point in space
            for (auto& vf : vectorField) {
            glm::vec2 direction{};
            for (auto& obj : physicsObjs) {
                direction += physicsSystem.computeForce(obj, vf);
            }
        
            // This scales the length of the field line based on the log of the length
            // values were chosen just through trial and error based on what i liked the look
            // of and then the field line is rotated to point in the direction of the field
            vf.transform2d.scale.x =
                0.005f + 0.045f * glm::clamp(glm::log(glm::length(direction) + 1) / 3.f, 0.f, 1.f);
            vf.transform2d.rotation = atan2(direction.y, direction.x);
            }
        }
    };
    
    std::unique_ptr<anvModel> createSquareModel(AnvDevice& device, glm::vec2 offset) {
        std::vector<anvModel::Vertex> vertices = {
            {{-0.5f, -0.5f}},
            {{0.5f, 0.5f}},
            {{-0.5f, 0.5f}},
            {{-0.5f, -0.5f}},
            {{0.5f, -0.5f}},
            {{0.5f, 0.5f}},  //
        };
        for (auto& v : vertices) {
            v.position += offset;
        }
        return std::make_unique<anvModel>(device, vertices);
        }
        
        std::unique_ptr<anvModel> createCircleModel(AnvDevice& device, unsigned int numSides) {
        std::vector<anvModel::Vertex> uniqueVertices{};
        for (int i = 0; i < numSides; i++) {
            float angle = i * glm::two_pi<float>() / numSides;
            uniqueVertices.push_back({{glm::cos(angle), glm::sin(angle)}});
        }
        uniqueVertices.push_back({});  // adds center vertex at 0, 0
        
        std::vector<anvModel::Vertex> vertices{};
        for (int i = 0; i < numSides; i++) {
            vertices.push_back(uniqueVertices[i]);
            vertices.push_back(uniqueVertices[(i + 1) % numSides]);
            vertices.push_back(uniqueVertices[numSides]);
        }
        return std::make_unique<anvModel>(device, vertices);
    }


        AnvilEngineApplication::AnvilEngineApplication()
        {

            BasicApp = new basic_anvApp();
            PushLayer(BasicApp);

            LoadGameObjects();
            vkDeviceWaitIdle(anvDevice.m_device);
        }

        void AnvilEngineApplication::PushLayer(AnvilLayer* layer)
        {
            LayerStack.PushLayer(layer);
            layer->Attach();
        }

        void AnvilEngineApplication::Run(){


            
            // create some models
            std::shared_ptr<anvModel> squareModel = createSquareModel(
                anvDevice,
                {.5f, .0f});  // offset model by .5 so rotation occurs at edge rather than center of square
            std::shared_ptr<anvModel> circleModel = createCircleModel(anvDevice, 64);
            
            // create physics objects
            std::vector<anvGameObject> physicsObjects{};
            auto red = anvGameObject::CreateGameObject();
            red.transform2d.scale = glm::vec2{.05f};
            red.transform2d.translation = {.5f, .5f};
            red.color = {1.f, 0.f, 0.f};
            red.rigidBody2d.velocity = {-.5f, .0f};
            red.model = circleModel;
            physicsObjects.push_back(std::move(red));
            auto blue = anvGameObject::CreateGameObject();
            blue.transform2d.scale = glm::vec2{.05f};
            blue.transform2d.translation = {-.45f, -.25f};
            blue.color = {0.f, 0.f, 1.f};
            blue.rigidBody2d.velocity = {.5f, .0f};
            blue.model = circleModel;
            physicsObjects.push_back(std::move(blue));
            
            // create vector field
            std::vector<anvGameObject> vectorField{};
            int gridCount = 40;
            for (int i = 0; i < gridCount; i++) {
                for (int j = 0; j < gridCount; j++) {
                auto vf = anvGameObject::CreateGameObject();
                vf.transform2d.scale = glm::vec2(0.005f);
                vf.transform2d.translation = {
                    -1.0f + (i + 0.5f) * 2.0f / gridCount,
                    -1.0f + (j + 0.5f) * 2.0f / gridCount};
                vf.color = glm::vec3(1.0f);
                vf.model = squareModel;
                vectorField.push_back(std::move(vf));
                }
            }
            
            GravityPhysicsSystem gravitySystem{0.81f};
            Vec2FieldSystem vecFieldSystem{};



            SimpleRenderSystem sRenderSystem{anvDevice, AnvRenderer.getSwapChainRenderPass()};

            for (AnvilLayer* layer : LayerStack.Layers)
            {
                auto name = layer->GetName();
                ENGINE_INFO("Loaded Layer: " + name, "`Run()`");
            }

            while (!glfwWindowShouldClose(WindowManager.Window)){

                glfwPollEvents();

                if (auto commandBuffer = AnvRenderer.BeginFrame())
                {
                    // update systems


                    gravitySystem.update(physicsObjects, 1.f / 60, 5);
                    vecFieldSystem.update(gravitySystem, physicsObjects, vectorField);

                    AnvRenderer.BeginSwapChainRenderPass(commandBuffer);
                    sRenderSystem.RenderGameObjects(commandBuffer, physicsObjects);
                    sRenderSystem.RenderGameObjects(commandBuffer, vectorField);
                    AnvRenderer.EndSwapChainRenderPass(commandBuffer);
                    AnvRenderer.EndFrame();

                    for (AnvilLayer* layer : LayerStack.Layers)
                    {
                        layer->Update();
                    }
                }
                
            }

            vkDeviceWaitIdle(anvDevice.m_device);
        }

        void AnvilEngineApplication::LoadGameObjects()
        {
            std::vector<anvModel::Vertex> vertices{
                /*{{position}, {color}}*/
                /*TRIANGLE 1*/
                {{0.0f, -0.5f},{1.0f, 0.0f, 0.0f}},
                {{0.5f, 0.5f},{0.0f, 1.0f, 0.0f}},
                {{-0.5f, 0.5f},{0.0f, 0.0f, 1.0f}}
                
            };

            auto anv_model = std::make_shared<anvModel>(anvDevice, vertices);
           
            std::vector<glm::vec3> colors{
                {1.f, .8f, .80f},
                {1.f, .67f, .53f},
                {1.f, .87f, .73f},
                {.73f, 1.f, .8f},
                {.73, .88f, 1.f}  
            };
            for (auto& color : colors) {
                color = glm::pow(color, glm::vec3{2.2f});
            }


            for (int i = 0; i < 40; i++) {
                auto triangle = anvGameObject::CreateGameObject();
                triangle.model = anv_model;
                triangle.transform2d.scale = glm::vec2(.5f) + i * 0.025f;
                triangle.transform2d.rotation = i * glm::pi<float>() * .025f;
                triangle.color = colors[i % colors.size()];
                GameObjects.push_back(std::move(triangle));
            }
        }

}



