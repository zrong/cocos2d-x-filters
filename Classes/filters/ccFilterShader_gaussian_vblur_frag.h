"precision mediump float;\n\
uniform sampler2D CC_Texture0;\n\
uniform float u_radius;\n\
\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
void main()\n\
{\n\
	vec2 st = gl_TexCoord[0].st;\n\
\n\
	vec4 color = vec4(0.0,0.0,0.0,0.0);\n\
	color += (1. / total) * texture2DRect(CC_Texture0, st - u_radius * vec2(0., 4. / 4.));\n\
	color += (8. / total)  * texture2DRect(CC_Texture0, st - u_radius * vec2(0., 3. / 4.));\n\
	color += (28. / total)  * texture2DRect(CC_Texture0, st - u_radius * vec2(0., 2. / 4.));\n\
	color += (56. / total)  * texture2DRect(CC_Texture0, st - u_radius * vec2(0., 1. / 4.));\n\
\n\
	color +=  (70. / total) * texture2DRect(CC_Texture0, st);\n\
\n\
	color += (1. / total) * texture2DRect(CC_Texture0, st + u_radius * vec2(0., 4. / 4.));\n\
	color += (8. / total)  * texture2DRect(CC_Texture0, st + u_radius * vec2(0., 3. / 4.));\n\
	color += (28. / total)  * texture2DRect(CC_Texture0, st + u_radius * vec2(0., 2. / 4.));\n\
	color += (56. / total)  * texture2DRect(CC_Texture0, st + u_radius * vec2(0., 1. / 4.));\n\
\n\
	gl_FragColor = color;\n\
	//gl_FragColor.a = 1.0;\n\
}";

