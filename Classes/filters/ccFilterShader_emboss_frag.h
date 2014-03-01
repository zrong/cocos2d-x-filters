"\n\
#ifdef GL_ES\n\
precision mediump float;\n\
#endif\n\
 \n\
// 1\n\
varying vec2 v_texCoord;\n\
uniform sampler2D u_texture;\n\
 \n\
void main()\n\
{\n\
  // 2\n\
  vec2 onePixel = vec2(1.0 / 480.0, 1.0 / 320.0);\n\
 \n\
  // 3\n\
  vec2 texCoord = v_texCoord;\n\
 \n\
  // 4\n\
  vec4 color;\n\
  color.rgb = vec3(0.5);\n\
  color -= texture2D(u_texture, texCoord - onePixel) * 5.0;\n\
  color += texture2D(u_texture, texCoord + onePixel) * 5.0;\n\
  // 5\n\
  color.rgb = vec3((color.r + color.g + color.b) / 3.0);\n\
  gl_FragColor = vec4(color.rgb, 1);\n\
}";

