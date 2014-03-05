"\n\
precision mediump float;\n\
\n\
varying vec2 v_texCoord;\n\
varying vec2 v_blurTexCoords[14];\n\
varying vec2 v_vblurTexCoords[14];\n\
uniform sampler2D CC_Texture0;\n\
\n\
void main()\n\
{\n\
    gl_FragColor = vec4(0.0);\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 0])*0.0044299121055113265;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 1])*0.00895781211794;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 2])*0.0215963866053;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 3])*0.0443683338718;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 4])*0.0776744219933;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 5])*0.115876621105;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 6])*0.147308056121;\n\
    gl_FragColor += texture2D(CC_Texture0, v_texCoord         )*0.159576912161;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 7])*0.147308056121;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 8])*0.115876621105;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[ 9])*0.0776744219933;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[10])*0.0443683338718;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[11])*0.0215963866053;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[12])*0.00895781211794;\n\
    gl_FragColor += texture2D(CC_Texture0, v_blurTexCoords[13])*0.0044299121055113265;\n\
	\n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[0])*0.0044299121055113265; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[1])*0.00895781211794; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[2])*0.0215963866053; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[3])*0.0443683338718; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[4])*0.0776744219933; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[5])*0.115876621105; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[6])*0.147308056121; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_texCoord)*0.159576912161; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[7])*0.147308056121; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[8])*0.115876621105; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[9])*0.0776744219933; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[10])*0.0443683338718; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[11])*0.0215963866053; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[12])*0.00895781211794; \n\
	//gl_FragColor += texture2D(CC_Texture0, v_vblurTexCoords[13])*0.0044299121055113265; \n\
}";
