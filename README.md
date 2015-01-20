DEX UI
---

![DEX UI Full Screenshot](http://i.imgur.com/2rjIbFa.png)

**The project source code is hosted here for reference.**

**I am currently working on cleaning this up, will likely be more stable by the end of the week.**

The code is a serious mess as I never intended to make this code public. But since so many people are interested, here it is. For the time being I'll just be cleaning up the code and writing documentation, I won't be trying to make this work on other people machines - that part's up to you.

If you look at this before I have cleaned it up, please forgive me. See [Stag](https://github.com/seenaburns/stag) for much better code quality!

What's included
===

This is the code for an [openFrameworks](http://www.openframeworks.cc/) project. First step is to get openFrameworks, try it out and see how some of the graphics examples work. Then the code provided here is the source files and shaders needed. However, things like fonts and images are not included, so if you are here to get this running on your own computer you have A LOT of work cut out for you right now.

What's happening
===

Real desktops revolve around windows, but most sci fi interfaces have these integrated desktops with all sort of animations and no apparent windows. Dex UI aimed to create the illusion of a desktop environment without windows while in reality still operating with windows (in X Windowing System).

To do this, the interface is a single openFrameworks program that handles all the animations. By modifying BSPWM I added a window mode to allow the interface to sit fullscreen beneath any other window. After the introduction animation occurs, a terminal (URXVT) is created above the interface and its size is constrained to the outline drawn in the interface. Because the windows have no borders or shadows, visually this looks like one integrated interface.

**Why openFrameworks?**
I needed something capable of creating lots of dynamic animations. This could be Processing, pure OpenGL, openFrameworks, etc. Originally my prototypes were in Processing, but for performance reasons I switched to openFrameworks. From what I've learned, many movie interfaces are put together in AfterEffects, so if you wanted to create an interface that did not respond to input, this is also an option.

**Why BSPWM?**
BSPWM was what I was working with, but it took some effort to make a window persistently stay fullscreen. The choice of window manager isn't a huge deal, just find something to make the illusion work.

