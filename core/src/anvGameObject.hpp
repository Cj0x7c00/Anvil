#pragma once

#include "anvModel.hpp"

// std
#include <memory>

namespace AnvilEngine {

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
  Transform2dComponent transform2d{};
  RigidBody2dComponent rigidBody2d{};

 private:
  anvGameObject(id_t objId) : id{objId} {}

  id_t id;
};
}  // namespace lve