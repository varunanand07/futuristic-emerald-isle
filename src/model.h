
#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
    glm::vec3 Normal;
};

class Model {
public:
    Model(const std::string &path)
    {
        loadModel(path);
        setupMesh();
    }
    
    void Draw(Shader &shader)
    {
        shader.use();
        
        
        glBindVertexArray(VAO);
        if(indices.size() > 0)
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        else
            glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
        glBindVertexArray(0);
    }
    
private:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    
    GLuint VAO, VBO, EBO;
    
    void loadModel(const std::string &path)
    {
        std::ifstream file(path);
        if(!file.is_open()) {
            std::cerr << "ERROR: Could not open OBJ file: " << path << std::endl;
            return;
        }
        
        std::vector<glm::vec3> temp_positions;
        std::vector<glm::vec2> temp_texcoords;
        std::vector<glm::vec3> temp_normals;
        
        std::map<std::string, GLuint> uniqueVertices;
        GLuint index = 0;
        
        std::string line;
        while(std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;
            
            if(prefix == "v") {
                glm::vec3 position;
                iss >> position.x >> position.y >> position.z;
                temp_positions.push_back(position);
            }
            else if(prefix == "vt") {
                glm::vec2 texcoord;
                iss >> texcoord.x >> texcoord.y;
                temp_texcoords.push_back(texcoord);
            }
            else if(prefix == "vn") {
                glm::vec3 normal;
                iss >> normal.x >> normal.y >> normal.z;
                temp_normals.push_back(normal);
            }
            else if(prefix == "f") {
                std::string vertex1, vertex2, vertex3;
                iss >> vertex1 >> vertex2 >> vertex3;
                std::vector<std::string> verticesStr = {vertex1, vertex2, vertex3};
                for(auto &vStr : verticesStr) {
                    if(uniqueVertices.find(vStr) == uniqueVertices.end()) {
                        std::istringstream viss(vStr);
                        std::string v, vt, vn;
                        std::getline(viss, v, '/');
                        std::getline(viss, vt, '/');
                        std::getline(viss, vn, '/');
                        
                        Vertex vertex;
                        vertex.Position = temp_positions[std::stoi(v) - 1];
                        
                        if(!vt.empty())
                            vertex.TexCoords = temp_texcoords[std::stoi(vt) - 1];
                        else
                            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
                        
                        if(!vn.empty())
                            vertex.Normal = temp_normals[std::stoi(vn) - 1];
                        else
                            vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
                        
                        vertices.push_back(vertex);
                        uniqueVertices[vStr] = index;
                        indices.push_back(index);
                        index++;
                    }
                    else {
                        indices.push_back(uniqueVertices[vStr]);
                    }
                }
            }
        }
        
        file.close();
        std::cout << "Loaded model: " << path << " with " << vertices.size() << " vertices and " << indices.size() << " indices." << std::endl;
    }
    
    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        if(indices.size() > 0)
            glGenBuffers(1, &EBO);
        
        glBindVertexArray(VAO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
        
        if(indices.size() > 0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
        }
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);
        
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(2);
        
        glBindVertexArray(0);
    }
};

#endif
