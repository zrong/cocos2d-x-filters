"uniform sampler2D CC_Texture0;\n\
uniform vec2 u_resolution;\n\
\n\
varying vec4 v_fragmentColor;\n\
varying vec2 v_texCoord;\n\
\n\
void main() {\n\
	vec4 texColor = texture2D(CC_Texture0, v_texCoord);\n\
	vec2 position = (gl_FragCoord.xy/u_resolution.xy) - vec2(0.5);\n\
	float len = length(position);\n\
	//gl_FragColor = vec4(texColor.rgb*(1.0-len), 1.0);\n\
	float r = 0.1;\n\
	float softness=0.02;\n\
	float vignette = smoothstep(r, r-softness, len);\n\
	//texColor.rgb *= mix(texColor.rgb, texColor.rgb*vignette, 0.5);\n\
	//gl_FragColor=vec4(vec3(len), 1.0);\n\
	//gl_FragColor=texColor;\n\
	//gl_FragColor=vec4(vec3(smoothstep(r, r-softness,len)), 1.0);\n\
	//gl_FragColor=vec4(vec3(1,0,0), texColor.a);\n\
	texColor.rgb = 1.0-texColor.rgb;\n\
	//gl_FragColor=vec4(vec3(v_texCoord.s, v_texCoord.t, v_texCoord.t), texColor.a);\n\
	//gl_FragColor=texColor;\n\
	gl_FragColor=texColor*v_fragmentColor;\n\
}";
