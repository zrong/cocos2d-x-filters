"\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
uniform sampler2DRect tex0;\n\
uniform float fade;\n\
\n\
float kernel[9];\n\
vec2 offset[9];\n\
\n\
void main(void){\n\
   vec2 st = gl_TexCoord[0].st;\n\
   vec4 sum = vec4(0.0);\n\
   \n\
   offset[0] = vec2(-1.0, -1.0);\n\
   offset[1] = vec2(0.0, -1.0);\n\
   offset[2] = vec2(1.0, -1.0);\n\
   \n\
   offset[3] = vec2(-1.0, 0.0);\n\
   offset[4] = vec2(0.0, 0.0);\n\
   offset[5] = vec2(1.0, 0.0);\n\
   \n\
   offset[6] = vec2(-1.0, 1.0);\n\
   offset[7] = vec2(0.0, 1.0);\n\
   offset[8] = vec2(1.0, 1.0);\n\
   \n\
   kernel[0] = 1.0/16.0; kernel[1] = 2.0/16.0; kernel[2] = 1.0/16.0;\n\
   kernel[3] = 2.0/16.0; kernel[4] = 4.0/16.0; kernel[5] = 2.0/16.0;\n\
   kernel[6] = 1.0/16.0; kernel[7] = 2.0/16.0; kernel[8] = 1.0/16.0;\n\
   \n\
   int i = 0;\n\
   for (i = 0; i < 9; i++){\n\
	   vec4 tmp = texture2DRect(tex0, st + offset[i]);\n\
	   sum += tmp * kernel[i];\n\
   }\n\
   \n\
   vec4 previousValue = texture2DRect(tex0, st);\n\
   gl_FragColor = (1.0 - fade) * previousValue + fade * vec4(sum.rgb, previousValue.a);\n\
}";

