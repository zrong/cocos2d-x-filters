/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __CC_FILTER_SHADER_H__
#define __CC_FILTER_SHADER_H__

#include "CCGL.h"
#include "platform/CCPlatformMacros.h"

//NS_CC_BEGIN

/**
 * @addtogroup shaders
 * @{
 */

extern CC_DLL const GLchar * ccFilterShader_gray_frag;

extern CC_DLL const GLchar * ccFilterShader_hblur_vert;
extern CC_DLL const GLchar * ccFilterShader_vblur_vert;
extern CC_DLL const GLchar * ccFilterShader_blur_frag;

extern CC_DLL const GLchar * ccFilterShader_sharpen_vert;
extern CC_DLL const GLchar * ccFilterShader_sharpen_frag;

extern CC_DLL const GLchar * ccFilterShader_rgb_frag;

extern CC_DLL const GLchar * ccFilterShader_brightness_frag;

extern CC_DLL const GLchar * ccFilterShader_exposure_frag;

extern CC_DLL const GLchar * ccFilterShader_contrast_frag;

extern CC_DLL const GLchar * ccFilterShader_saturation_frag;

extern CC_DLL const GLchar * ccFilterShader_gamma_frag;

extern CC_DLL const GLchar * ccFilterShader_hue_frag;

extern CC_DLL const GLchar * ccFilterShader_haze_frag;

extern CC_DLL const GLchar * ccFilterShader_zoom_blur_frag;

extern CC_DLL const GLchar * ccFilterShader_motion_blur_vert;
extern CC_DLL const GLchar * ccFilterShader_motion_blur_frag;

//==============================
extern CC_DLL const GLchar * ccFilterShader_gaussian_hblur_vert;
extern CC_DLL const GLchar * ccFilterShader_gaussian_hblur_frag;
extern CC_DLL const GLchar * ccFilterShader_gaussian_vblur_frag;

extern CC_DLL const GLchar * ccFilterShader_colorramp_frag;

extern CC_DLL const GLchar * ccFilterShader_emboss_frag;

extern CC_DLL const GLchar * ccFilterShader_embossmov_frag;

extern CC_DLL const GLchar * ccFilterShader_grass_frag;

// end of shaders group
/// @}

//NS_CC_END

#endif /* __CC_FILTER_SHADER_H__ */
