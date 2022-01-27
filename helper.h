#include <gd.h>
#include <gdfx.h>
#include <gdfontt.h>
#include <gdfonts.h>
#include <gdfontmb.h>
#include <gdfontl.h>
#include <gdfontg.h>
#include <math.h>

// convert v to 0-255
int BJconvcolor( int v ) {
	int t;
	double t1;
	t1 = (double)v / 255.0;
	t = (int)t1;
	return t;
}

double BJrmse(gdImagePtr buf1, gdImagePtr buf2) {
	int w,h;
	w = buf1->sx;
  	h = buf1->sy;
	double size;
	size = (double)w * (double)h;
	//printf("%i %i %f\n",w,h,size);
	int x,y; // x,y indexs
	
	int c1,c2; // color1 from buf1, color2 from buf2

	//int a1,a2
	int r1,r2,g1,g2,b1,b2;
	double re,ge,be,f;
	uint rsum,gsum,bsum;
	int rr,gg,bb;
	
//	int red1,green1,blue1;
//	int red2,green2,blue2;

	

	for(y=0;y<h;y++) {
		for(x=0;x<w;x++){
			c1 = gdImageGetPixel(buf1,x,y);
			c2 = gdImageGetPixel(buf2,x,y);

			//a1 = (c1 & 0x7F000000) >> 24;
			//a2 = (c2 & 0x7F000000) >> 24;
			r1 = (c1 & 0x00FF0000) >> 16;
			r2 = (c2 & 0x00FF0000) >> 16;
			g1 = (c1 & 0x0000FF00) >> 8;
			g2 = (c2 & 0x0000FF00) >> 8;
			b1 = c1 & 0x000000FF;
			b2 = c2 & 0x000000FF;

			// Convert int to 0-255 values
			//red1 = BJconvcolor(r1);
			//red2 = BJconvcolor(r2);
			//green1 = BJconvcolor(g1);
			//green2 = BJconvcolor(g2);
			//blue1 = BJconvcolor(b1);
			//blue2 = BJconvcolor(b2);
			//
			//printf("%i %i %i %i %i %i \n",r1,r2,g1,g2,b1,b2);
			//
			rr = r2 - r1;
			gg = g2 - g1;
			bb = b2 - b1;
			//if(r1>255 || r2>255 || g1>255 || g2>255 || b1>255 || b2>255){
			//	printf("x:%i y:%i r1:%i g1%i b1%i r2:%i g2:%i b2:%i rr:%i gg:%i bb:%i\n",x,y,r1,g1,b1,r2,g2,b2,rr,gg,bb);
			//}

			rsum += (uint)rr * (uint)rr;
			gsum += (uint)gg * (uint)gg;
			bsum += (uint)bb * (uint)bb;

		}
	}
	
	//printf("rsum:%i gsum:%i bsum:%i\n",rsum,gsum,bsum);

	re = sqrt((double)rsum/size);
	ge = sqrt((double)gsum/size);
  	be = sqrt((double)bsum/size);

	f = be + ge + re;

	//printf("re:%f ge:%f be:%f f:%f\n",re,ge,be,f);
		
	return f;
}