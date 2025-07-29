#pragma once

#include <vector>
#include <memory>
#include <string>
#include <mesh.hpp>
#include <matrix.hpp>
#include <component.hpp>

using EntityID = uint32_t;

class Entity {
public:
    std::string _name;
    bool _active;
    bool _static;

    std::vector<std::shared_ptr<Entity>> children;

    std::shared_ptr<Mesh> meshes = nullptr;
    std::shared_ptr<Transform> transform = nullptr;
    std::vector<std::shared_ptr<SystemLogic>> scripts;
    // std::shared_ptr<Camera> meshes = nullptr;

    Entity(std::string name) : _name(name), _active(true), _static(false) {}
    ~Entity() = default;

    bool add_children(std::shared_ptr<Entity> entity) {
        for (std::shared_ptr<Entity> child : children) {
            if (child->_name == entity->_name) {
                return false;
            }
        }

        children.push_back(entity);
        return true;
    }

    bool remove_children(std::string name) {
        for (std::shared_ptr<Entity> child : children) {
            if (child->_name == name) return true;
        }

        return false;
    }

    std::shared_ptr<Entity> get_children_by_name(std::string name) {
        for (std::shared_ptr<Entity> child : children) {
            if (child->_name == name) return child;
        }

        return nullptr;
    }

    std::shared_ptr<Entity> get_children_by_index(unsigned int index) {
        if (children.empty()) return nullptr;
        if (index >= children.size()) return nullptr;

        return children[index];
    }

    void starts() {
        for (std::shared_ptr<SystemLogic> script : scripts) {
            script->start();
        }
    }

    void ends() {
        for (std::shared_ptr<SystemLogic> script : scripts) {
            script->end();
        }
    }

    void update(float dt) {
        for (std::shared_ptr<SystemLogic> script : scripts) {
            script->update();
        }

        for (std::shared_ptr<Entity> child : children) {
            child->update(dt);
        }
    }
};