#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;


layout (location = 3) in mat4 instanceModel;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat4 model = instanceModel;
    FragPos = vec3(model * vec4(position, 1.0));
    Normal = mat3(transpose(inverse(model))) * normal;
    TexCoords = texCoords;

    gl_Position = projection * view * model * vec4(position, 1.0);
}
