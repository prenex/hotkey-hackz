#!/bin/bash

# Stop the script first so that it does not keep on spawning more mpv processes.
killall start.sh
# We can safely kill every mpv as the game runs fullscreen anyways so ours is the only one likely.
killall mpv
