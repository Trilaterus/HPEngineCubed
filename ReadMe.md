# HPEngineCubed
An engine/framework made with SFML to create 3 specific games (and hopefully more!)

The end result is to be able to create a side scrolling 2D fighting game (similar to Scott Pilgrim VS the World or Castle Crashers).

Although that'll take forever, so during the development as core features are being added I'll try to make a game with the few features it has.

Not only will this keep itching my need for designing and pushing out games, but it will also run my engine through a cycle of developing a game allowing me to identify issues in a low cost environment.

The first game planned is a Point and Click adventure/puzzle game, some of the features include (but are not limited to):
- Properly anchored UI elements to allow for support on multiple screen sizes
- A semi-stack like Screen system to efficiently change screens with transitions (and have overlays within screens!)
- Animations handled via both spritesheets and programmable movements (sin movement, shake movement etc.)
- UIElements working: UIImage, UIButton, UIButtonList, UIText (names subject to change)
- Basic audio manipulation... Having BG music and SFX implemented without memory leaks (using smart pointers probably!)
