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
#include "../Light/PointLight.h"

namespace rt {
    AssimpLoader::AssimpLoader(): _camera() {
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
        _loadNode(_scene->mRootNode, aiMatrix4x4());   
        return true;
    }

    Camera AssimpLoader::GetCameraFromScene() const {
        return _camera;
    }

    std::vector<std::shared_ptr<Mesh>> const& AssimpLoader::GetMeshesFromScene() const {
        return _meshes;
    }

    std::vector<std::shared_ptr<Light>> const& AssimpLoader::GetLightsFromScene() const {
        return _lights;
    }

    Vector3<float> AssimpLoader::_transform(aiMatrix4x4 const& mat, Vector3<float> const& point) const {
        return Vector3<float>(
            mat.a1 * point.X + mat.a2 * point.Y + mat.a3 * point.Z + mat.a4,
            -mat.c1 * point.X - mat.c2 * point.Y - mat.c3 * point.Z - mat.c4,
            mat.b1 * point.X + mat.b2 * point.Y + mat.b3 * point.Z + mat.b4
        );
    }

    Material const AssimpLoader::_loadMaterialFromMesh(unsigned int matIdx) const {
        aiMaterial* aiMat = _scene->mMaterials[matIdx];
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
        return mat;
    }

    void AssimpLoader::_loadNode(aiNode *node, aiMatrix4x4 const& parent) {
        aiMatrix4x4 matrix = parent * node->mTransformation;

        if (_scene->mNumCameras > 0 && node->mName == _scene->mCameras[0]->mName) {
            _camera.SetMatrix(
                Vector3<float>(matrix.a1, -matrix.c1, matrix.b1),
                Vector3<float>(matrix.a2, -matrix.c2, matrix.b2),
                Vector3<float>(matrix.a3, -matrix.c3, matrix.b3),
                Vector3<float>(matrix.a4, -matrix.c4, matrix.b4)
            );
        }
        
        for (std::uint32_t lightIdx = 0; lightIdx < _scene->mNumLights; ++lightIdx) {
            aiLight* light = _scene->mLights[lightIdx];
            if (light->mName == node->mName) {
                if (light->mType == aiLightSource_POINT) {
                    _lights.emplace_back(new PointLight(
                         _transform(matrix, Vector3<float>(light->mPosition.x, light->mPosition.y, light->mPosition.z)),
                        Color(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b)
                    ));
                }
            }
        }

        for (std::uint32_t meshIdx = 0u; meshIdx < node->mNumMeshes; ++meshIdx) {
            aiMesh* mesh = _scene->mMeshes[node->mMeshes[meshIdx]];
            if (!(mesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE) || mesh->mNumVertices <= 0) continue;
            std::vector<Triangle> triangles;
            for (std::uint32_t faceIdx = 0u; faceIdx < mesh->mNumFaces; ++faceIdx) {
                if (mesh->mFaces[faceIdx].mNumIndices == 3) {
                    unsigned int v1Idx = mesh->mFaces[faceIdx].mIndices[0];
                    unsigned int v2Idx = mesh->mFaces[faceIdx].mIndices[1];
                    unsigned int v3Idx = mesh->mFaces[faceIdx].mIndices[2];
                    Vertex v1 = Vertex(_transform(matrix, Vector3<float>(
                            mesh->mVertices[v1Idx].x,
                            mesh->mVertices[v1Idx].y,
                            mesh->mVertices[v1Idx].z
                        )));
                    Vertex v2 = Vertex(_transform(matrix, Vector3<float>(
                            mesh->mVertices[v2Idx].x,
                            mesh->mVertices[v2Idx].y,
                            mesh->mVertices[v2Idx].z
                        )));
                    Vertex v3 = Vertex(_transform(matrix, Vector3<float>(
                            mesh->mVertices[v3Idx].x,
                            mesh->mVertices[v3Idx].y,
                            mesh->mVertices[v3Idx].z
                        )));
                    if (mesh->mNormals) {
                        v1.SetNormal(Vector3<float>(
                            mesh->mNormals[v1Idx].x,
                            mesh->mNormals[v1Idx].y,
                            mesh->mNormals[v1Idx].z
                        ));
                        v2.SetNormal(Vector3<float>(
                            mesh->mNormals[v2Idx].x,
                            mesh->mNormals[v2Idx].y,
                            mesh->mNormals[v2Idx].z
                        ));
                        v2.SetNormal(Vector3<float>(
                            mesh->mNormals[v3Idx].x,
                            mesh->mNormals[v3Idx].y,
                            mesh->mNormals[v3Idx].z
                        ));
                    }
                    triangles.emplace_back(v1, v2, v3);
                }
            }
            std::cout << "Creating KDTree for " << triangles.size() << " triangles" << std::endl;
            _meshes.emplace_back(new Object(triangles, _loadMaterialFromMesh(mesh->mMaterialIndex)));
            std::cout << "Done" << std::endl;
        }

        for (size_t i = 0; i < node->mNumChildren; ++i) {
            _loadNode(node->mChildren[i], matrix);
        }
    }
}  // namespace rt
