"precision mediump float;\n\
uniform sampler2D CC_Texture0;\n\
uniform float u_radius;\n\
\n\
const float total = (1. + 8. + 28. + 56.) * 2. + 70.;\n\
\n\
void main()\n\
{\n\
	vec2 st = gl_TexCoord[0].st;\n\
	//vec2 st = vec2(1,0);\n\
\n\
	vec4 color = vec4(0.0,0.0,0.0,0.0);\n\
	color += (1. / total) * texture2D(CC_Texture0, st - u_radius * vec2(4. / 4., 0.));\n\
	color += (8. / total)  * texture2D(CC_Texture0, st - u_radius * vec2(3. / 4., 0.));\n\
	color += (28. / total)  * texture2D(CC_Texture0, st - u_radius * vec2(2. / 4., 0.));\n\
	color += (56. / total)  * texture2D(CC_Texture0, st - u_radius * vec2(1. / 4., 0.));\n\
\n\
	color +=  (70. / total) * texture2D(CC_Texture0, st);\n\
\n\
	color += (1. / total) * texture2D(CC_Texture0, st + u_radius * vec2(4. / 4., 0.));\n\
	color += (8. / total)  * texture2D(CC_Texture0, st + u_radius * vec2(3. / 4., 0.));\n\
	color += (28. / total)  * texture2D(CC_Texture0, st + u_radius * vec2(2. / 4., 0.));\n\
	color += (56. / total)  * texture2D(CC_Texture0, st + u_radius * vec2(1. / 4., 0.));\n\
\n\
	gl_FragColor = color;\n\
	//gl_FragColor.a = 1.0;\n\
}";

