# 3DOS

3DOS is a low-poly old-school software renderer exploring 3D graphics under the constraints of classic DOS-era hardware and VGA graphics. Built around simple geometry, triangle rasterization, and a limited color palette, it brings low-poly 3D into a deliberately minimal environment.
You can download the `EXE` file from [itch.io](https://xms0g.itch.io/3dos).

## Features
- **Software rasterization** — render 3D geometry using a CPU-based pipeline.
- **Low-poly meshes** — hand-crafted models defined by vertices and triangular faces.
- **Backface culling** — skip faces pointing away from the camera.
- **VGA Mode 13h** — target the classic 320 × 200, 256-color graphics mode.
- **Palette-based rendering** — work within a fixed color palette.
- **Ordered dithering** — experiment with Bayer matrices for lighting and color quantization.
- **Double buffering**

## Controls
| Key  | Description |
|------|-------------|
|`WASD`|Move         |
|`↑ ↓` |Fly up/down  |
|`ESC` |Exit         |
|`1/2/3/4`| Cube/Ico/Tree/F22|

## Screenshots
<img src="IMG/cube.gif" alt="image" width="700" height="auto">
<img src="IMG/ico.gif" alt="image" width="700" height="auto">
<img src="IMG/tree.gif" alt="image" width="700" height="auto">
<img src="IMG/f22.gif" alt="image" width="700" height="auto">
<img src="IMG/f22_slow.gif" alt="image" width="700" height="auto">

## License
This project is licensed under the BSD 3-Clause License. See the LICENSE file for details.
