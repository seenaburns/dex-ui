DEX UI
===

![DEX UI Full Screenshot](http://i.imgur.com/2rjIbFa.png)

*DEX UI is a handcrafted interface programmed in openFrameworks, running fullscreen underneath a functioning terminal, giving the experience of having a sci-fi computer.* [More.](http://nnkd.org/dexui/)

The project's source code is hosted here for reference. Included are the openFrameworks project source files and shaders, as well as the changes I made to BSPWM (more below). Not included are things like fonts and images.

Note: Dex UI was designed as an experiment or an art piece, not distributable software, so as a result, the code (though I've cleaned it up some) is not the easiest to sort through. Also, because it is no longer in development, I won't be trying to make this work on other people machines - that part's up to you.

Q&A
---

**What's Happening in the Video Demo**

Real desktops revolve around windows, but most sci-fi interfaces have these integrated desktops with all sort of animations and no apparent windows. Dex UI aimed to create the illusion of a desktop environment without windows while in reality still operating with windows (in X Windowing System).

To do this, the interface is a single openFrameworks program that handles all the animations. By modifying BSPWM, I added a window mode to allow the interface to sit fullscreen beneath any other window. After the introduction animation occurs, a terminal (URXVT) is created above the interface and its size is constrained to the outline drawn in the interface. In short it is two layered windows, but because the windows have no borders or shadows, visually this looks like one integrated interface.

**How do I run Dex UI**

The code here is for an [openFrameworks](http://www.openframeworks.cc/) project. The first step is to get openFrameworks, and get the graphics examples running to confirm it's really working. Then you can start a new project and add the files. Beyond that, fonts and images are not included here, which may be problematic as all of the type work is hard coded.

**How I contribute?**

This project is here for reference and not in active development, so it is very unlikely I will continue to make changes or respond to requests to make changes.

**Why openFrameworks?**

I needed something capable of creating lots of dynamic animations. This could be Processing, pure OpenGL, openFrameworks, etc. Originally my prototypes were in Processing, but for performance reasons I switched to openFrameworks. From what I've learned, many movie interfaces are put together in AfterEffects, so if you wanted to create an interface that did not respond to input, this is also an option.

**BSPWM?**

BSPWM was what I was working with, but it took some effort to make a window persistently stay fullscreen. The choice of window manager isn't a huge deal, just find something to make the illusion work.

I've also included a .diff file with the changes (to BSPWM commit c49bc92) I made to BSPWM to add what I (for no reason) named power mode. A window can be set to power mode making it stay fullscreen, beneath all other windows across multiple desktops. I've been told a similar effect can be achieved with wmutils, and this might be an easier route.

**Font?**

Inside the terminal we have Fira Mono, and the rest is United Sans Medium.

**Is this working with real data**

The keyboard contains some code to work using /dev/input, but the rest still needs to be hooked up to system data. Luckily this is straightforward and only requires replacing the generated data with sampled data.

**Why the onscreen Keyboard, does it work with touch screens?**

It's there because I think it looks cool. While it doesn't work with touch screens, it might be possible by making the project respond to mouse/touch input.
