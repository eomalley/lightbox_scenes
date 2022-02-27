# lightbox_scenes
quick and dirty application to drive an arduino controlling LEDs from a raspberry pi. 

Application expects a few things: on the pi side 4 buttons, mp3 files for accompanying sound, and a connection to the arduino via usb.  For the arduino: LEDs compatible with FastLED and accurate number of LEDs, and the LEDs to be connected in a specific order (sort of like an S sideways).

Current setup loads a gradual sunrise theme that will continue to 100% brightness. At any time this can be stopped by pressing a button to select a new theme. 

Each button corresponds to a set of themes: Sunsets, Day, Storms, and Night. If the .mp3 files are found they will play with each theme. The last of the storm themes also includes lightning flashes that occur psuedo randomly (after 6 missed strikes a strike is guaranteed.

While the arduino file can accept custom, non-hard coded patterns, this is only accessible when sending specific codes directly to the arduino outside the app. I would like to create a front end in the future to easily create & send custom themes on the fly.

