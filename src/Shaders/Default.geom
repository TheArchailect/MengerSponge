#version 460 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 Normal;
out vec3 Position;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main() {
    vec3 A = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 n =  normalize(cross(A, B));
    
    for (int i = 0; i < 3; i++) {
        gl_Position = Projection * View * Model * gl_in[i].gl_Position; 
        Position = (Model * gl_in[i].gl_Position).xyz;
        Normal = mat3(transpose(inverse(Model))) * n;
        EmitVertex();
    }
    EndPrimitive();
}