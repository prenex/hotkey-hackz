/*
 * Simple app that plays the midi music files for Age Of Empires from the sound/midi dictionary
 *
 * Useful if this does not work under wine+timidity despite you do all the stuff mentined on wine/midi
 * even though age 1 works (but only when aconnect is made to route from 14->128).
 * Oh yeah I know about that there is some regedit trick, but for me it never works! Not even if I 
 * tried to "read out" the source code just like as if it would be some book...
 *
 * Build with:
 * g++ musicplayer.cpp -o musicplayer -lX11
 */

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main() {
	Display*	dpy		= XOpenDisplay(0);
	Window		root	= DefaultRootWindow(dpy);
	XEvent		ev;

	unsigned int	modifiers		= ControlMask | ShiftMask;
	int				keycode			= XKeysymToKeycode(dpy,XK_Y);
	Window			grab_window		=  root;
	Bool			owner_events	= False;
	int				pointer_mode	= GrabModeAsync;
	int				keyboard_mode	= GrabModeAsync;

	XGrabKey(dpy, keycode, modifiers, grab_window, owner_events, pointer_mode,
			keyboard_mode);

	XSelectInput(dpy, root, KeyPressMask );
	while(true)
	{
		bool shouldQuit = false;
		XNextEvent(dpy, &ev);
		switch(ev.type)
		{
			case KeyPress:
				// TODO: start to play music
				std::cout << "Hot key pressed!" << std::endl;
				XUngrabKey(dpy,keycode,modifiers,grab_window);
				shouldQuit = true;

			default:
				break;
		}

		if(shouldQuit)
			break;
	}

	XCloseDisplay(dpy);
	return 0;
}
