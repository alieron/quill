# quill

Texture pack renderer

The 8 vertices will look like this:

```
  v5 ----------- v6
  /|            /|      Axis orientation    North orientation
 / |           / |
v4 --------- v7  |      y
|  |         |   |      |                       
|  v0 -------|-- v3     +--- x                 /
| /          |  /      /                      /
|/           | /      z                     North
v1 --------- v2


Triangle primitives must be drawn in a anticlockwise order

Vertex draw order: 0, 2, 1, 0, 3, 2, 4, 6, 5, 4, 7, 6, 3, 5, 6, 3, 0, 5, 1, 7, 4, 1, 2, 7, 0, 4, 5, 0, 1, 4, 2, 6, 7, 2, 3, 6    
```
Where v0, v4, v5, v1 is the top face

Good references:
 - https://github.com/jayanam/jgl_demos/tree/master - 3D scene renderer with property panel
 - https://github.com/Sarath18/Minecraft-Block-Viewer/tree/master - Minecraft block viewer
 - https://github.com/Toofifty/mc-modelr/blob/master/js/model.js - JSON parsing functions

Gui elements:
 - [ ] Textures / UV display
 - [ ] JSON editor
 - [ ] Minecraft GUI views
 - [ ] Hide elements, choose which ones to view
 - [ ] Block selector

General:
 - [ ] Texture pack importer
 - [ ] Default texture pack for parents that aren't included with the user texture pack
 - [ ] JSON parser
 - [ ] Renderer
 - [ ] Parent model / texture inheritance

Eventual:
 - [ ] How to update the default texture pack as the game updates

Reference for camera.h
https://github.com/yocover/start-learning-opengl

VAO VBO to merge into one model/element class
https://github.com/VictorGordan/opengl-tutorials

Shader.cpp for shader as a shader program
https://github.com/amanshenoy/mesh-viewer