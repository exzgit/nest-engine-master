#pragma once


#include <vector>
#include <memory>
#include <string>
#include <mesh.hpp>
#include <matrix.hpp>
#include <component.hpp>
#include <render.hpp>
#include <entity.hpp>

class ECS {
    public:
        std::vector<std::shared_ptr<Entity>> entities;

        ECS() {}

        void add_entity(std::shared_ptr<Entity> entity) {
            entities.push_back(entity);
        }

        bool remove_entity(std::string name) {
            for (std::shared_ptr<Entity> child : entities) {
                if (child->_name == name) return true;
            }

            return false;
        }
        

        std::shared_ptr<Entity> get_entity_by_name(std::string name) {
        for (std::shared_ptr<Entity> child : entities) {
            if (child->_name == name) return child;
        }

        return nullptr;
    }

    std::shared_ptr<Entity> get_entity_by_index(unsigned int index) {
        if (entities.empty()) return nullptr;
        if (index >= entities.size()) return nullptr;

        return entities[index];
    }

    void update(float dt) {
        for (std::shared_ptr<Entity> child : entities) {
            child->update(dt);
        }
    }

    void render(RenderSystem& renderer) {
        renderer.render_all(entities);
    }
};