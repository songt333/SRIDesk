/* xgetfocus.c - link against libX11 */
#include <stdio.h>
#include <X11/Xlib.h>

int window2ppm(Display *display, Window window, int x, int y, int width, int height);

int main(int argc, char *argv[])
{
	Display *display;
	Window focus;
	int revert;
	XWindowAttributes attr;
	int x, y;
	Window junkwin;

	if (!(display = XOpenDisplay(NULL))) {
		return 1;
	}

	XGetInputFocus(display, &focus, &revert);
	if (!XGetWindowAttributes(display, focus, &attr)) {
		return 1;
	}
	(void) XTranslateCoordinates(display, focus, attr.root,
				     -attr.border_width, -attr.border_width,
				     &x, &y, &junkwin);

	//printf("x: %d\ny: %d\nwidth: %d\nheight: %d\n", x, y, attr.width, attr.height);
	window2ppm(display, RootWindow(display, DefaultScreen(display)), x, y, attr.width, attr.height);

	return 0;
}

int window2ppm(Display *display, Window window, int x, int y, int width, int height)
{
	XImage* ximg = XGetImage(display, window, x, y, width, height, AllPlanes, ZPixmap);

	unsigned long red_mask   = ximg->red_mask;
	unsigned long green_mask = ximg->green_mask;
	unsigned long blue_mask  = ximg->blue_mask;

	const char *ofile = "snapshot.ppm";
	FILE *fout = fopen(ofile, "w");

	fprintf(fout, "P3 %d %d %d\n", width, height, blue_mask);
	fprintf(fout, "# depth = %d\n", ximg->depth);
	fprintf(fout, "# mask  = %04x %04x %04x\n", red_mask, green_mask, blue_mask);
	int nbits_mask = ximg->depth/3;
	//TODO: if bits per color not the same?
	int yp, xp;
	for (yp=0; yp<height; yp++) {
		for (xp=0; xp<width; xp++) {
			unsigned long pix = XGetPixel(ximg, xp, yp);
			unsigned int red   = (pix & red_mask)  >> (nbits_mask + nbits_mask);
			unsigned int green = (pix & green_mask)>> nbits_mask;
			unsigned int blue  = pix & blue_mask;
			fprintf(fout, "%ld %ld %ld\n", red, green, blue);
		}
	}
	fclose(fout);
	XDestroyImage(ximg);
	return 1;
}
