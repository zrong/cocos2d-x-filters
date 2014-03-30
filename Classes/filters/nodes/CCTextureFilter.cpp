#include "CCTextureFilter.h"

CCTextureFilter::CCTextureFilter()
{
}


CCTextureFilter::~CCTextureFilter()
{

}

void CCTextureFilter::blurInput(void* $input, void* $output,
	CCTexture2DPixelFormat $format, int $width, int $height,
	CCSize $contentSize, int $radius, CCRect $rect)
{
	int read, i, xl, yl, yi, ym, ri, riw;
	const int wh = $width*$height;
	
	CCSize size = CCSizeMake($rect.size.width, $rect.size.height);

	size.width = (size.width == 0) ? $contentSize.width : size.width;
	size.height = (size.height == 0) ? $contentSize.height : size.height;

	//Check data
	CCPoint position = CCPointMake(MAX(0, $rect.origin.x), MAX(0, $rect.origin.y));
	size.width = position.x + size.width - MAX(0, (position.x + size.width) - $width);
	size.height = position.y + size.height - MAX(0, (position.y + size.height) - $height);
	yi = position.y*$width;

	//Generate Gaussian kernel
	$radius = MIN(MAX(1, $radius), 248);
	const int kernelSize = 1 + $radius * 2;
	int kernel[kernelSize];
	int g = 0, sum = 0;

	//Gaussian filter	
	for (i = 0; i<$radius; i++)
	{
		g = i*i*i + 1;
		kernel[i] = kernel[kernelSize - i - 1] = g;
		sum += g * 2;
	}
	g = $radius*$radius;
	kernel[$radius] = g;
	sum += g;

	if ($format == kTexture2DPixelFormat_RGBA8888){
		int cr, cg, cb, ca;

		const ccColor4B *originalData = (ccColor4B*)$input;
		ccColor4B *data = (ccColor4B*)$output;
		ccColor4B *temp = malloc(wh * 4);
		ccColor4B *pixel;

		//Horizontal blur
		for (yl = position.y; yl<size.y; yl++){
			for (xl = position.x; xl<size.width; xl++){
				cb = cg = cr = ca = 0;
				ri = xl - radius;

				for (i = 0; i<kernelSize; i++){
					read = yi + ri + i;

					pixel = &originalData[read];
					cr += pixel->r*kernel[i];
					cg += pixel->g*kernel[i];
					cb += pixel->b*kernel[i];
					ca += pixel->a*kernel[i];
				}
				pixel = &temp[yi + xl];
				pixel->r = cr / sum;
				pixel->g = cg / sum;
				pixel->b = cb / sum;
				pixel->a = ca / sum;
			}
			yi += width;
		}
		yi = (position.y)*width;

		//Vertical blur
		for (yl = position.y; yl<size.y; yl++){
			for (xl = position.x; xl<size.width; xl++){
				cb = cg = cr = ca = 0;
				ri = yl - radius;

				for (i = 0; i<kernelSize; i++){
					if ((ri + i) >= position.y && (ri + i) < size.y)
						read = (ri + i) * width + xl;
					else
						read = yl * width + xl;

					pixel = &temp[read];
					cr += pixel->r * kernel[i];
					cg += pixel->g * kernel[i];
					cb += pixel->b * kernel[i];
					ca += pixel->a * kernel[i];
				}
				pixel = &data[yi + xl];
				pixel->r = cr / sum;
				pixel->g = cg / sum;
				pixel->b = cb / sum;
				pixel->a = ca / sum;
			}
			yi += width;
		}

		//Free temp data
		free(temp);

	}
	else if (format == kTexture2DPixelFormat_A8){
		int ca;

		const unsigned char *originalData = (const unsigned char*)input;
		unsigned char *data = (unsigned char*)output;
		unsigned char *temp = malloc(wh);

		//Horizontal blur
		for (yl = position.y; yl<size.y; yl++){
			for (xl = position.x; xl<size.width; xl++){
				ca = 0;
				ri = xl - radius;
				for (i = 0; i<kernelSize; i++){
					read = ri + i;
					if (read >= position.x && read<size.width){
						read += yi;
						ca += originalData[read] * kernel[i];
					}
				}
				ri = yi + xl;
				temp[ri] = ca / sum;;
			}
			yi += width;
		}
		yi = position.y*width;

		//Vertical blur
		for (yl = position.y; yl<size.y; yl++){
			ym = yl - radius;
			riw = ym*width;
			for (xl = position.x; xl<size.width; xl++){
				ca = 0;
				ri = ym;
				read = xl + riw;
				for (i = 0; i<kernelSize; i++){
					if (ri<size.y && ri >= position.y)
						ca += temp[read] * kernel[i];

					ri++;
					read += width;
				}
				data[xl + yi] = ca / sum;;

			}
			yi += width;
		}

		//Free temp data
		free(temp);

	}
	else
		[NSException raise : @"AWTextureFilter" format:@"Pixel format don't supported. It should be RGBA8888 or A8"];
}

CCTexture2DMutable* CCTextureFilter::blur(CCTexture2DMutable* $texture, int $radius, CCRect $rect)
{

}

CCTexture2DMutable* CCTextureFilter::blur(CCTexture2DMutable* $texture, int $radius)
{

}