#pragma once
#include <iostream>
#include <vector>
#include <filesystem>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "Mesh.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace ga {
    class Model {
    public:
        Model(const std::string &filename);
        mat4<float> getModelView() const;
        glm::mat4 getModelView_glm() const;
    //private:
        // properties:
        vec3<float> position{ 0.f, 0.f, 0.f };
        vec3<float> scale{ 1.f, 1.f, 1.f };
        vec3<float> rotation{};


        std::vector<Mesh> meshes;
        std::string s_FileDirectory{};

        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    };
}


