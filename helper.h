#include <gd.h>
#include <gdfx.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontl.h>
#include <gdfontg.h>
#include <math.h>

// convert v to 0-255
int BJconvcolor(int v)
{
	int t;
	double t1;
	t1 = (double)v / 255.0;
	t = (int)t1;
	return t;
}

double BJrmse(gdImagePtr buf1, gdImagePtr buf2)
{
	int w, h;
	w = buf1->sx;
	h = buf1->sy;
	double size;
	size = (double)w * (double)h;
	
	int c1, c2; // color1 from buf1, color2 from buf2

	int r1, r2, g1, g2, b1, b2;
	double re, ge, be, f;
	
	u_int64_t rsum = 0;
	u_int64_t gsum = 0;
	u_int64_t bsum = 0;

	int rr, gg, bb;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			c1 = gdImageGetPixel(buf1, x, y);
			c2 = gdImageGetPixel(buf2, x, y);

			r1 = gdTrueColorGetRed(c1);
			r2 = gdTrueColorGetRed(c2);
			g1 = gdTrueColorGetGreen(c1);
			g2 = gdTrueColorGetGreen(c2);
			b1 = gdTrueColorGetBlue(c1);
			b2 = gdTrueColorGetBlue(c2);

			//
			// printf("%i %i %i %i %i %i \n",r1,r2,g1,g2,b1,b2);
			//
			rr = abs(r2 - r1);
			gg = abs(g2 - g1);
			bb = abs(b2 - b1);
			// if(r1>255 || r2>255 || g1>255 || g2>255 || b1>255 || b2>255){
			//	printf("x:%i y:%i r1:%i g1%i b1%i r2:%i g2:%i b2:%i rr:%i gg:%i bb:%i\n",x,y,r1,g1,b1,r2,g2,b2,rr,gg,bb);
			// }

			rsum += (u_int64_t)rr * (u_int64_t)rr;
			gsum += (u_int64_t)gg * (u_int64_t)gg;
			bsum += (u_int64_t)bb * (u_int64_t)bb;
		}
	}

	// printf("rsum:%i gsum:%i bsum:%i\n",rsum,gsum,bsum);

	re = sqrt((double)rsum / size);
	ge = sqrt((double)gsum / size);
	be = sqrt((double)bsum / size);

	f = be + ge + re;

	// printf("re:%f ge:%f be:%f f:%f\n",re,ge,be,f);

	return f;
}