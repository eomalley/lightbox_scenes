# lightbox_scenes
quick and dirty application to drive an arduino controlling LEDs from a raspberry pi. 

Application expects a few things: on the pi side 4 buttons, mp3 files for accompanying sound, and a connection to the arduino via usb.  For the arduino: LEDs compatible with FastLED, an accurate number of LEDs, and the LEDs to be connected in a specific order (sort of like an S sideways). Since the strips in my light box wrap, the code needs to reverse the pattern every row because the strips are continuous and connect to each other at the shortest point.

Current start up loads a gradual sunrise theme that will continue to 100% brightness. At any time this can be stopped by pressing a button to select a new theme. I have this set to a smart plug with an alexa routine to mimic an actual sunrise inside my blacked out room.

Each button corresponds to a set of themes: Sunsets, Day, Storms, and Night. If the .mp3 files are found they will play with each theme. The last of the storm themes also includes lightning flashes that occur psuedo randomly (after 6 missed strikes a strike is guaranteed.

While the arduino file can accept custom, non-hard coded patterns, this is only accessible when sending specific codes directly to the arduino outside the app. I would like to create a front end in the future to easily create & send custom themes on the fly.

