#version 460 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

out vec3 Normal;
out vec3 Position;
flat out int MaterialIndex;
uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform mat4 InverseModel;

int MaterialSelect(vec3 v)
{
    if(abs(v.x) > abs(v.y) && abs(v.x) > abs(v.z)) return 0;
    if(abs(v.y) > abs(v.x) && abs(v.y) > abs(v.z)) return 1;
    if(abs(v.z) > abs(v.y) && abs(v.z) > abs(v.x)) return 2;
}

void main() 
{
    vec3 A = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 B = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 n =  normalize(cross(A, B));
    int m = MaterialSelect(n);

    for (int i = 0; i < 3; i++) {
        gl_Position = Projection * View * Model * gl_in[i].gl_Position; 
        Position = (Model * gl_in[i].gl_Position).xyz;
        Normal = mat3(InverseModel) * n;
        MaterialIndex = m;
        EmitVertex();
    }
    EndPrimitive();
}

