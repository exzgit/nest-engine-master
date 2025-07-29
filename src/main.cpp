#include <iostream>
#include <game.hpp>
#include <entity.hpp>
#include <mesh_loader.hpp>
#include <matrix.hpp>
#include <memory>

auto main() -> int {

    auto game = GameLoop("My Game", 1024, 600);
    game.init();

    auto* worldManager = game.getWorldManager();

    Entity sphere = Entity("Sphere");
    sphere.meshes = load_obj("./models/Sphere.obj");
    Transform transform = Transform{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}};
    sphere.transform = std::make_shared<Transform>(transform);

    worldManager->getActive()->ecs.add_entity(std::make_shared<Entity>(sphere));

    game.run();

    return 0;
}