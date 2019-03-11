# Hotkey hackz

Simple c++ app to have a hotkey accessible to run your stop/start scripts while playing. I use this to play background mp3 and midi music from a given directory. Useful for games where music does not work with wine for example.

This works as an on-off switch: when you press the hotkey (CTRL+SHIFT+Y as of now, but easy to change), you are calling start-stop-start-stop in this order and the system thinks that we are in a stopped state originally.

As it is said this fits well for games, and the example setup is made for making music work with AOE2: I just start this app from the terminal so that it catches the said X11 key combination, then start the game, navigate the menus and stuff and only start the music when the map gets loaded. If I want to get back to the menu, I just stop it with the same key combination. Works like a charm and you do not need to have the CD in (I have not CD drive) not even virtually!

Have fun! It should work everywhere with every app!
