#include "Model.hpp"

namespace vn {
    Model::Model(const std::string &filename) {
        std::filesystem::path filepath(filename);
        if (!std::filesystem::exists(filepath)) {
            std::cerr << "Model file " << filename << " could not be found!\n";
            exit(1);
        }
        this->s_FileDirectory = std::filesystem::absolute(filepath).remove_filename();
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);
        this->processNode(scene->mRootNode, scene);
    }

    mat4<float> Model::getModelView() const {
        mat4<float> transformation = mat4<float>::rotate3d(this->rotation) * mat4<float>::scale3d(this->scale) * mat4<float>::translate3d(this->position);
        return transformation;
    }

    glm::mat4 Model::getModelView_glm() const {
        glm::mat4 m_ModelView(1.f);
        m_ModelView = glm::scale(m_ModelView, { scale.x, scale.y, scale.z });
        m_ModelView = glm::translate(m_ModelView, { position.x, position.y, position.z });
        glm::mat4 m_View = glm::lookAt({0, 0, -3}, glm::vec3{0, 0, -3} + glm::vec3{0, 0, 1}, glm::vec3{0.f, 1.f, 0.f});
        m_ModelView = m_View * m_ModelView;
        return m_ModelView;
    }

    void Model::processNode(aiNode *node, const aiScene *scene) {
        for (std::uint32_t i = 0; i < node->mNumMeshes; i++) {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.emplace_back(processMesh(mesh, scene));
        }
        for (std::uint32_t i = 0; i < node->mNumChildren; i++) {
            processNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
        std::vector<Vertex>        vertices;
        std::vector<std::uint32_t> indices;
        std::vector<Tex2d>         textures;

        for (std::uint32_t i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex{};
            // DO STUFF
            const auto& o_vert = mesh->mVertices[i];
            const auto& o_norm = mesh->mNormals[i];

            vertex.position = { o_vert.x, o_vert.y, o_vert.z };
            vertex.normal = { o_norm.x, o_norm.y, o_norm.z };

            if (auto& t_coords = mesh->mTextureCoords[0]; t_coords) {
                vertex.tex_coords = { t_coords[i].x, t_coords[i].y };
            } else {
                vertex.tex_coords = { 0, 0 };
            }

            vertices.emplace_back(vertex);
        }
        for (std::uint32_t i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            for (std::uint32_t j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            for(std::uint32_t i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
                aiString str;
                material->GetTexture(aiTextureType_DIFFUSE, i, &str);
                textures.emplace_back(this->s_FileDirectory + str.C_Str());
            }
        }
        return Mesh(vertices, indices, textures);
    }
}