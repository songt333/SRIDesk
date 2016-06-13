#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <cairo.h>
#include <cairo-xlib.h>
/* ... */
 
int clickAt(int x, int y){
  Display *dpy = XOpenDisplay(NULL);
  if(dpy == NULL){
    return 0;
  }
 
  XEvent event;
 
  Window root = RootWindow(dpy, DefaultScreen(dpy));
  /* get info about current pointer position */
  XQueryPointer(dpy, root,
      &event.xbutton.root, &event.xbutton.window,
      &event.xbutton.x_root, &event.xbutton.y_root,
      &event.xbutton.x, &event.xbutton.y,
      &event.xbutton.state);
 
/*  XImage *img = XGetImage(dpy, root, 0, 0, 400, 400, XAllPlanes(), ZPixmap);
  unsigned long red_mask = img->red_mask;
  unsigned long green_mask = img->green_mask;
  unsigned long blue_mask = img->blue_mask;

  int  i,j;
  for (i = 0; i < 400; i++)
     for (j = 0; j < 400; j++)
     {
	unsigned long pixel = XGetPixel(img,i,j);
	unsigned char blue = pixel & blue_mask;
	unsigned char green = (pixel & green_mask) >> 8;
	unsigned char red = (pixel & red_mask) >> 16;
     }
*/
  cairo_surface_t *cs;
  cs = cairo_xlib_surface_create(dpy, root, DefaultVisual(dpy, 0),400,400);
  cairo_surface_write_to_png(cs,"hello.png");
  XTestFakeMotionEvent(dpy, -1, x, y, 0);
  XTestFakeButtonEvent(dpy, 1, 1, 0);
  XTestFakeButtonEvent(dpy, 1, 0, 0);
  XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_c), 1, CurrentTime);
  XTestFakeKeyEvent(dpy, XKeysymToKeycode(dpy, XK_c), 0, CurrentTime);
  /* place the mouse where it was */
//  XTestFakeMotionEvent(dpy, -1, event.xbutton.x, event.xbutton.y, 0);
  XCloseDisplay(dpy);
  return 1;
}

int main(int argc, char* argv[])
{
    clickAt(100,100);

}
