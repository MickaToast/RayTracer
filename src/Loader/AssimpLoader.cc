/* Copyright (c) 2018 mickael.leclerc@epitech.eu charles.fraisse@epitech.eu
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE. */

#include <iostream>
#include "AssimpLoader.h"
#include "../Mesh/Object.h"

namespace rt {
    AssimpLoader::AssimpLoader() {
        _scene = nullptr;
    }

    AssimpLoader::~AssimpLoader() {
    }

    bool AssimpLoader::LoadFile(std::string const& filePath) {
        _scene = _importer.ReadFile(filePath, aiProcess_Triangulate
                                               | aiProcess_GenSmoothNormals
                                               | aiProcess_FixInfacingNormals);
        if (!_scene) {
            std::cout << "ERROR while importing scene:" << _importer.GetErrorString() << std::endl;
            return false;
        }
        return true;
    }

    std::vector<std::shared_ptr<Mesh>> const AssimpLoader::GetMeshesFromScene() const {
        std::vector<std::shared_ptr<Mesh>> meshes;
        for (std::uint32_t meshIdx = 0u; meshIdx < _scene->mNumMeshes; ++meshIdx) {
            aiMesh* mesh = _scene->mMeshes[meshIdx];
            aiMaterial* aiMat = _scene->mMaterials[mesh->mMaterialIndex];
            Material mat;
            aiColor3D color;
            float coef;
            if (aiMat->Get(AI_MATKEY_SHININESS, coef) == AI_SUCCESS) {
                mat.Ns = coef;                
            }
            aiString name;
            aiMat->Get(AI_MATKEY_NAME,name);
            mat.name = name.C_Str();
            if (aiMat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS) {
                mat.Ka = Vector3<float>(color.r, color.g, color.b);                
            }
            if (aiMat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
                mat.Kd = Vector3<float>(color.r, color.g, color.b);                
            }
            if (aiMat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
                mat.Ks = Vector3<float>(color.r, color.g, color.b);                
            }
            if (aiMat->Get(AI_MATKEY_COLOR_EMISSIVE, color) == AI_SUCCESS) {
                mat.Ke = Vector3<float>(color.r, color.g, color.b);                
            }
            if (aiMat->Get(AI_MATKEY_REFRACTI, coef) == AI_SUCCESS) {
                mat.Ni = coef;                
            }
            if (aiMat->Get(AI_MATKEY_OPACITY, coef) == AI_SUCCESS) {
                mat.d = coef;                
            }
            if (aiMat->Get(AI_MATKEY_SHADING_MODEL, coef) == AI_SUCCESS) {
                mat.illum = coef;
            }
            std::vector<Triangle> triangles;
            for (std::uint32_t faceIdx = 0u; faceIdx < mesh->mNumFaces; ++faceIdx) {
                triangles.push_back(Triangle(
                    Vector3<float>(
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[0]].x,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[0]].y,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[0]].z
                    ),
                    Vector3<float>(
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[1]].x,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[1]].y,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[1]].z
                    ),
                    Vector3<float>(
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[2]].x,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[2]].y,
                        mesh->mVertices[mesh->mFaces[faceIdx].mIndices[2]].z
                    )
                ));
            }
            std::cout << "Creating KDTree for " << triangles.size() << " triangles" << std::endl;
            meshes.push_back(std::shared_ptr<Mesh>(new Object(triangles, mat)));
            std::cout << "Done" << std::endl;
        }
        return meshes;
    }

}  // namespace rt
