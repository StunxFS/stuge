<div align="center">

# Stuge

![CI](https://github.com/StunxFS/stuge/actions/workflows/build.yml/badge.svg)
![License](https://img.shields.io/github/license/StunxFS/stuge?style=flat-square)
![Issues](https://img.shields.io/github/issues/StunxFS/stuge?style=flat-square)
![Stars](https://img.shields.io/github/stars/StunxFS/stuge?style=flat-square)

</div>

Stuge (**Stu**nxFS's **G**ame **E**ngine) is a 2D top-down game
engine (for GTA-style games) developed in C, using
[raylib](https://github.com/raysan5/raylib) as a base.

The goal of the project is to have a base on which to develop a
2D top-down game easily.

**Important note**: The engine is not ready for production yet.

## Structure

Stuge is arranged in a way that makes it easy to know what you
want to modify:

* `assets/`: The assets used by the project are housed in this
    folder, such as language files, maps, scripts, graphics, etc.
    These are embedded in the binary.

* `bin/`: The compiled binary will appear in this folder.

* `src/`: The engine code, the heart of Stuge.

* `thirdparty/`: Third-party libraries that are useful for development.

* `tools/`: Useful scripts that can be used to make development easier.

## Dependencies

Stuge obviously requires a C compiler.

You also need [`raylib`](https://www.raylib.com/), which is the base library
that powers the engine.

These are also other engine dependencies:

### On Linux

```bash
liblua5.3-dev libxml2-dev libglfw3-dev libglfw3 libasound2-dev mesa-common-dev
libx11-dev libxrandr-dev libxi-dev xorg-dev libgl1-mesa-dev libglu1-mesa-dev
```

They can be installed with `apt install` on Ubuntu (in other distros they may have
other names).

### Asset Dependencies

[Tiled](http://mapeditor.org) is used for maps and tilesets. For graphics, scripts,
langs, sounds and musics you can use any editor of your choice.

## Building

Just run `python3 tools/make.py`.

## Acknowledgments

* [raysan5](https://github.com/raysan5) by **raylib** and **raygui**.
* [cktan](https://github.com/cktan) by **tomlc99**.
* [baylej](https://github.com/baylej) by **tmx**.
* [RobLoach](https://github.com/RobLoach) by **raylib-tmx**.
* [DaveGamble](https://github.com/DaveGamble) by **cJSON**.
* [goldsborough](https://github.com/goldsborough) by **vector**.

* * *

<div align="center">

© 2022 **StunxFS**

</div>
