#version 330

//Uniform variables
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 viewerPosition;
uniform vec4 lp1;
uniform vec4 lp2;


//Attributes
in vec4 vertex; //Vertex coordinates in model space
in vec2 texCoord0;
in vec4 normal; //Vertex normal in model space

//Varying variables

out vec4 l1;
out vec4 l2;
out vec4 n;
out vec4 v;
out vec2 iTexCoord0;


void main(void) {    
    l1 = normalize(V * lp1 - V * M * vertex); 
    l2 = normalize(V*lp2-V*M*vertex);
    v = normalize(viewerPosition - V * M * vertex); //vector towards the viewer in eye space
    n = normalize(V * M * normal); //normal vector in eye space

    iTexCoord0 = texCoord0;


    gl_Position = P * V * M * vertex;
}
