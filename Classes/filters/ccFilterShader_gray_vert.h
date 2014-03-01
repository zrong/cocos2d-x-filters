"													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
attribute vec4 a_grayParam;								\n\
													\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
varying mediump vec4 v_grayParam;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
varying vec4 v_grayParam;					\n\
#endif												\n\
													\n\
void main()											\n\
{													\n\
    gl_Position = CC_MVPMatrix * a_position;		\n\
	v_fragmentColor = a_color;						\n\
	v_texCoord = a_texCoord;						\n\
	v_grayParam = a_grayParam;						\n\
}													\n\
";