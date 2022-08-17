<div align="center">

# Stuge

</div>

Stuge (**Stu**nxFS's **G**ame **E**ngine) is a 2D top-down game
engine (for GTA-style games) developed in C, using
[raylib](https://github.com/raysan5/raylib) as a base.

The goal of the project is to have a base on which to develop a
2D top-down game easily.

> **Important note**: The engine is not ready for production yet.

## Structure

Stuge is arranged in a way that makes it easy to know what you
want to modify:

* `assets/`: The assets used by the project are housed in this
    folder, such as language files, maps, scripts, graphics, sprites,
    etc. These are embedded in the binary.

* `src/`: The engine code, the heart of Stuge.

* `tools/`: Useful scripts that can be used to make development easier.

## Using Stuge for my own game

Simply modify the assets, and the engine code if necessary, to create
your own game.

## Dependencies

Stuge depends on:

* A C compiler.
* [**raylib**](https://www.raylib.com/).

### On Linux/Ubuntu

```bash
liblua5.3-dev libxml2-dev libglfw3-dev libglfw3 libasound2-dev mesa-common-dev
libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

They can be installed with `apt install`.

### Asset Dependencies

[Tiled](http://mapeditor.org) is used for maps and tilesets. For graphics, scripts,
langs and sounds you can use any editor of your choice.

## Building

Just run `python3 tools/make.py`, or from **Sted**, just click the `Build` button.

## Credits

* [raysan5](https://github.com/raysan5) by **raylib** and **raygui**.
* [cktan](https://github.com/cktan) by **tomlc99**.
* [baylej](https://github.com/baylej) by **tmx**.
* [RobLoach](https://github.com/RobLoach) by **raylib-tmx**.

* * *

<div align="center">

© 2022 **StunxFS**

</div>
