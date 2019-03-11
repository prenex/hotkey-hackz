#!/bin/bash

# The stop.sh shuts us down so this can be an endless loop
while true; do
	# Run OST from youtube (needs internet)
	mpv --no-video --loop "https://www.youtube.com/watch?v=l6yM2AZ-W-Q"

	# Run local downloaded mp3 OST
	#mpv --no-video --loop "./mp3/aok_ost.mp3"
done
