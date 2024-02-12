#version 330

/*
	The fragment shader runs once for every fragment in the rasterised primitive
	You can think of a fragment as just the same as a screen pixel (it is a bit different when multisampling)
	Its main job is to output a colour for the fragment

	Note: I set the extension to .frag to avoid a clash with NSight but still allow the highlighting
	plugin to work (GLSL Languaage integration - highly recommended).
*/

// We want to output a 4 element colour (RGBA)

in vec3 Texmex_coords;
in vec2 texture_colour;
out vec4 fragment_colour;
uniform sampler2D sampler_tex;
uniform samplerCube cubemap;

in vec3 CubeMapVert;

void main(void)
{
	
	fragment_colour = texture(cubemap, Texmex_coords);


}