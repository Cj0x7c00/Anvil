#pragma once

#include "./Vulkan/Model/anvModel.hpp"

#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>

namespace Anvil {

struct Transform2dComponent {
  glm::vec2 translation{};  // (position offset)
  glm::vec2 scale{1.f, 1.f};
  float rotation;

  glm::mat2 mat2() {
    const float s = glm::sin(rotation);
    const float c = glm::cos(rotation);
    glm::mat2 rotMatrix{{c, s}, {-s, c}};

    glm::mat2 scaleMat{{scale.x, .0f}, {.0f, scale.y}};
    return rotMatrix * scaleMat;
  }
};

struct TransformComponent {
  glm::vec3 translation{};  // (position offset)
  glm::vec3 scale{1.f, 1.f, 1.f};
  glm::vec3 rotation{};

  glm::mat4 mat4() {
    const float c3 = glm::cos(rotation.z);
    const float s3 = glm::sin(rotation.z);
    const float c2 = glm::cos(rotation.x);
    const float s2 = glm::sin(rotation.x);
    const float c1 = glm::cos(rotation.y);
    const float s1 = glm::sin(rotation.y);
    return glm::mat4{
    {
        scale.x * (c1 * c3 + s1 * s2 * s3),
        scale.x * (c2 * s3),
        scale.x * (c1 * s2 * s3 - c3 * s1),
        0.0f,
    },
    {
        scale.y * (c3 * s1 * s2 - c1 * s3),
        scale.y * (c2 * c3),
        scale.y * (c1 * c3 * s2 + s1 * s3),
        0.0f,
    },
    {
        scale.z * (c2 * s1),
        scale.z * (-s2),
        scale.z * (c1 * c2),
        0.0f,
    },
    {translation.x, translation.y, translation.z, 1.0f}};
  }
};

struct RigidBody2dComponent {
  glm::vec2 velocity;
  float mass{1.0f};
};

class anvGameObject {
 public:
  using id_t = unsigned int;

  static anvGameObject CreateGameObject() {
    static id_t currentId = 0;
    return anvGameObject{currentId++};
  }

  anvGameObject(const anvGameObject &) = delete;
  anvGameObject &operator=(const anvGameObject &) = delete;
  anvGameObject(anvGameObject &&) = default;
  anvGameObject &operator=(anvGameObject &&) = default;

  id_t getId() { return id; }

  std::shared_ptr<anvModel> model{};
  glm::vec3 color{};
  TransformComponent transform{};
  

 private:
  anvGameObject(id_t objId) : id{objId} {}

  id_t id;
};
}  // namespace lve