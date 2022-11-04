#version 460 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 color1;
uniform vec3 replace1;

void main()
{
	vec4 pixel = texture2D(image, gl_TexCoord[0].xy);

	if(pixel == vec4(color1, 1.0))
		pixel = vec4(replace1, 1.0);

	gl_FragColor = pixel;
}