#version 330

/*
	The fragment shader runs once for every fragment in the rasterised primitive
	You can think of a fragment as just the same as a screen pixel (it is a bit different when multisampling)
	Its main job is to output a colour for the fragment

	Note: I set the extension to .frag to avoid a clash with NSight but still allow the highlighting
	plugin to work (GLSL Languaage integration - highly recommended).
*/

// We want to output a 4 element colour (RGBA)
uniform sampler2D sam_tex;
uniform samplerCube sky;

in vec2 varying_coords;
in vec3 varying_normal;
in vec3 varying_position;

out vec4 fragment_colour;
out vec4 FragColour;

void main(void)
{
	vec3 texture_colour = texture(sam_tex, varying_coords).rgb;

	fragment_colour = vec4(texture_colour, 1.0);
}