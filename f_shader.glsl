#version 330

out vec4 pixelColor; // Output variable. Almost final pixel color.

// Varying variables
in vec2 iTexCoord0;
in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 v;


uniform sampler2D textureMap1;
uniform sampler2D textureMap0;
uniform vec4 ambientLightColor = vec4(0.2, 0.2, 0.2, 0.2);

float calculateDiff(vec4 l, vec4 reflect) {
    float nl = max(dot(reflect, l), 0.0);
    nl = nl*(1/length(l)) *0.5;
    return nl;
}

float calculateSpec(vec4 vertex, vec4 reflect,float p) {
    float rv = pow(max(dot(reflect, vertex), 0.0), 50.0);
    return rv;
}

void main(void) {
    // Normalized, interpolated vectors
    vec4 texColor = texture(textureMap0, iTexCoord0);
    vec4 ml1 = normalize(l1);
    vec4 ml2 = normalize(l2);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);

    // Reflected vectors
    vec4 mr1 = reflect(-ml1, mn);
    vec4 mr2 = reflect(-ml2, mn);
    vec4 spec;
  
    float diffuse1 = calculateDiff(ml1, mr1);
    float diffuse2 = calculateDiff(ml2, mr2);

    vec4 diff = texColor * (diffuse1 + diffuse2);
    vec4 ambient = ambientLightColor * texColor;
        
    float specular1 = calculateSpec(mv, mr1,25.0);
    float specular2 = calculateSpec(mv, mr2,25.0);
    spec = vec4(specular1 + specular2);
       // Final pixel color calculation with ambient light
    pixelColor = clamp(diff + spec + ambient , 0.0, 1.0);
    
}
