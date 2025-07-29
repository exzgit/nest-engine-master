#pragma once

#include <mesh.hpp>
#include <memory>
#include <tiny_obj_loader.h>


std::shared_ptr<Mesh> load_obj(const std::string& path) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str());

    if (!warn.empty()) std::cout << "[TinyObjLoader] Warning: " << warn << std::endl;
    if (!err.empty()) std::cerr << "[TinyObjLoader] Error: " << err << std::endl;

    if (!ret) return nullptr;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            Vertex vertex{};
            vertex.position = {
                attrib.vertices[3 * index.vertex_index + 0],
                attrib.vertices[3 * index.vertex_index + 1],
                attrib.vertices[3 * index.vertex_index + 2]
            };

            if (!attrib.colors.empty()) {
                vertex.color = {
                    attrib.colors[3 * index.vertex_index + 0],
                    attrib.colors[3 * index.vertex_index + 1],
                    attrib.colors[3 * index.vertex_index + 2]
                };
            } else {
                vertex.color = {1.0f, 1.0f, 1.0f}; // default white
            }

            if (index.texcoord_index >= 0) {
                vertex.texCoord = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attrib.texcoords[2 * index.texcoord_index + 1] // Flip Y
                };
            } else {
                vertex.texCoord = {0.0f, 0.0f};
            }

            vertices.push_back(vertex);
            indices.push_back(indices.size());
        }
    }

    return std::make_shared<Mesh>(vertices, indices);
}