
"                                           \n\
#ifdef GL_ES                                \n\
precision mediump float;                    \n\
#endif                                      \n\
\n\
varying vec4 v_fragmentColor;               \n\
varying vec2 v_texCoord;                    \n\
varying vec4 v_grayParam;					\n\
uniform sampler2D CC_Texture0;				\n\
\n\
void main(void)                             \n\
{                                           \n\
// Convert to greyscale using NTSC weightings               \n\
vec4 col = texture2D(CC_Texture0, v_texCoord);                \n\
//float grey = dot(col.rgb, vec3(0.299, 0.587, 0.114));       \n\
float grey = dot(col.rgba, v_grayParam);       \n\
gl_FragColor = vec4(grey, grey, grey, col.a);               \n\
}                                           \n\
";
