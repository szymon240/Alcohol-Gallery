#version 330


out vec4 pixelColor; //Fragment shader output variable


uniform vec4 color=vec4(1,1,1,1);

void main(void) {
	pixelColor=color;
}
