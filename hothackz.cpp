/*
 * Simple app that sets a hotkey and runs start.sh, stop.sh consequtively for every call.
 * Usage example: play the midi/mp3 music files for Age Of Empires from the sound/midi directory.
 *
 * Useful if this does not work under wine+timidity despite you do all the stuff mentined on wine/midi
 * even though age 1 works (but only when aconnect is made to route from 14->128).
 * Oh yeah I know about that there is some regedit trick, but for me it never works! Not even if I 
 * tried to "read out" the source code just like as if it would be some book...
 *
 * Configuration is done via start.sh and stop.sh (see example files)
 * Hotkey CTRL+SHIFT+Y starts/stops playback using scripts.
 *
 * Build with (has makefile):
 * g++ hothackz.cpp -o hothackz -lX11
 */

#include <signal.h>
#include <cstdio>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

const char* start_cmd = "./start.sh&";
const char* stop_cmd = "./stop.sh&";

Display* dpy;
int keycode_y;
unsigned int modifiers;
Window	grab_window;

// Needed for cleanup because we only quit using CTRL+C
void handler(int dummy) {
	system(stop_cmd);
	XUngrabKey(dpy,keycode_y,modifiers,grab_window);
	/*
	XCloseDisplay(dpy);
	*/
	exit(0);
}

int main() {
	if(signal(SIGQUIT, handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle sigquit!\n");
	}
	if(signal(SIGINT, handler) == SIG_ERR) {
		fprintf(stderr, "Cannot handle sigint!\n");
	}

	dpy = XOpenDisplay(0);
	Window root = DefaultRootWindow(dpy);
	XEvent ev;
	bool isPlaying = false;

	modifiers = ControlMask | ShiftMask;
	keycode_y = XKeysymToKeycode(dpy,XK_Y);
	grab_window = root;
	Bool owner_events = False;
	int pointer_mode = GrabModeAsync;
	int keyboard_mode = GrabModeAsync;

	XGrabKey(dpy, keycode_y, modifiers, grab_window, owner_events, pointer_mode,
			keyboard_mode);

	XSelectInput(dpy, root, KeyPressMask);
	printf("Just quit the app with CTRL+C from the terminal. Use CTRL+SHIFT+Y to start/stop\n");
	while(true)
	{
		XNextEvent(dpy, &ev);
		switch(ev.type)
		{
			case KeyPress:
				printf("Hotkey (CTRL+SHIFT+Y) -> ");
				if(isPlaying) {
					printf("%s\n", stop_cmd);
					system(stop_cmd);
				} else {
					printf("%s\n", start_cmd);
					system(start_cmd);
				}
				isPlaying = !isPlaying;
				break;
		}
	}

	// We only quit by CTRL+C
	// I think there is no real reason to complicate this with an other combo for quitting!
	printf("THIS SHOULD NEVER GET PRINTED!");
	return 0;
}
