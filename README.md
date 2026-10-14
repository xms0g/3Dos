# 3DOS

3DOS is a low-poly old-school software renderer written in Turbo C and x86 assembly for PC DOS, running in mode 13h (320x200) colors.
You can download the `EXE` file from [itch.io](https://xms0g.itch.io/3dos).

<img src="IMG/cube.gif" alt="image" width="700" height="auto">
<img src="IMG/ico.gif" alt="image" width="700" height="auto">
<img src="IMG/tree.gif" alt="image" width="700" height="auto">
<img src="IMG/f22.gif" alt="image" width="700" height="auto">
<img src="IMG/f22_slow.gif" alt="image" width="700" height="auto">

## Features
- Triangle rasterization
- 3D vertex transformations
- Perspective projection
- Backface culling
- Bresenham's line algorithm
- Ordered Dithering using 4x4 Bayer Matrix
- Double buffering

## Controls
| Key  | Description |
|------|-------------|
|`WASD`|Move         |
|`↑ ↓` |Fly up/down  |
|`ESC` |Exit         |
|`1/2/3/4`| Cube/Ico/Tree/F22|

## Building
If you want to build `3Dos` from source, you'll need Turbo C++ and the related [build tools](https://github.com/ms0g/breakout/tree/main/TOOLS/tcpp). 

## License
This project is licensed under the BSD 3-Clause License. See the LICENSE file for details.
