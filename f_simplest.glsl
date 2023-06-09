#version 330

uniform sampler2D textureMap0;
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
#define NR_LIGHTS 4  
uniform vec4 pointLights[NR_LIGHTS];
uniform int active_nr_lights;

out vec4 pixelColor;

in vec4 n;
in vec4 pos;
in vec4 v;
in vec2 iTexCoord0;

vec4 CalcPointLight(int index, vec4 Normal, vec4 kd) {
    vec4 LightDirection = normalize(V*pointLights[index] -  V*M*pos);
   // vec4 AmbientColor = vec4(0.05, 0.05, 0.05, 1.0); // Ambient light color

    // Diffuse light calculation
    float DiffuseFactor = max(dot(Normal, LightDirection), 0.0);
    vec4 DiffuseColor = DiffuseFactor * kd;

    // Specular light calculation
    vec4 ViewDirection = normalize(v);
    vec4 ReflectionDirection = reflect(-LightDirection, Normal);
    float SpecularFactor = pow(max(dot(ViewDirection, ReflectionDirection), 0), 25.0);
    vec4 SpecularColor = SpecularFactor * vec4(1.0, 1.0, 1.0, 1.0); // Specular light color

    return (DiffuseColor + SpecularColor);
}

void main(void) {
    // Normalized interpolated vectors
  //  vec4 ml = normalize(l);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);

    vec4 TotalLight = vec4(0.0, 0.0, 0.0, 1.0);
     vec4 kd = texture(textureMap0, iTexCoord0); 
    for (int i = 0; i <  1; i++) {
        TotalLight += CalcPointLight(i, mn,kd);
    }

    // Surface parameters
   //TotalLight = clamp(TotalLight,0,1);

    // Final color calculation
    pixelColor = TotalLight ;
}