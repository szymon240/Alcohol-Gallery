#version 330

out vec4 pixelColor; //Output variable. Almost final pixel color.

//Varying variables
in vec2 iTexCoord0;
in vec4 n;
in vec4 l1;
in vec4 l2;
in vec4 v;

uniform sampler2D textureMap0;
uniform vec4 ambientLightColor = vec4(0.1,0.1,0.1,0.1);

float calculateDiff(vec4 l, vec4 reflect) {
    float nl = clamp(dot(reflect, l), 0, 1);
    return nl;
}

float calculateSpec(vec4 vertex, vec4 reflect) {
    float rv = pow(clamp(dot(reflect, vertex), 0, 1), 50);
    return rv;
}

void main(void) {
    //Normalized, interpolated vectors
    vec4 spec = texture(textureMap0, iTexCoord0);
    vec4 diff = texture(textureMap0, iTexCoord0);
    vec4 ml1 = normalize(l1);
    vec4 ml2 = normalize(l2);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);

    //Reflected vector
    vec4 mr1 = reflect(-ml1, mn);
    vec4 mr2 = reflect(-ml2, mn);
  
    //Surface parameters
    diff = clamp(vec4(diff.rgb * calculateDiff(ml1, mr1)+ diff.rgb *calculateDiff(ml2,mr2), diff.a),0,1);
    //diff *= vec4(diff.rgb * calculateDiff(ml2, mr2), diff.a);
    spec = clamp(vec4(spec.rgb * calculateSpec(mv, mr1) + spec.rgb* calculateSpec(mv,mr2), 0),0,1);
    //spec *= vec4(spec.rgb * calculateSpec(mv, mr2),0) ;

    // Ambient light calculation
    vec4 ambient = ambientLightColor * texture(textureMap0, iTexCoord0);
  
    // Final pixel color calculation with ambient light
    pixelColor = clamp(diff + spec +ambient, 0.0, 1.0);
}
