# quill

## Texture pack renderer

Progress
 - [x] Draw a plane
 - [x] Orbit camera
 - [x] Draw test cube(unique faces)
 - [x] Use from and to for cube corners
 - [ ] Only draw 2 faces if the defined element is flat
 - [ ] Scale UV coords
 - [ ] GUI

Rendering scheme

```
  v5 ----------- v4
  /|            /|      Axis orientation    North orientation
 / |           / |
v6 --------- v7  |      y
|  |         |   |      |                       
|  v2 -------|-- v3     +--- x                 /
| /          |  /      /                      /
|/           | /      z                     North
v1 --------- v0


Triangle primitives must be drawn in a anticlockwise order when looking from the outside

(0,0) v1 --------- v0 (1,0)
	  |          / |
	  |        /   |
	  |      /     |
	  |    /       |						^
	  |  /	       |						|
(0,1) v2 --------- v3 (1,1)				Texture Up

JSON Order:
	down
	up
	north
	south
	west
	east

Vertex draw order: 
	0, 1, 2,    0, 2, 3,	// Down -Y
	4, 5, 6, 	4, 6, 7,	// Up +Y
	5, 4, 3, 	5, 3, 2,	// North -Z
	7, 6, 1, 	7, 1, 0,	// South +Z
	6, 5, 2, 	6, 2, 1,	// West -X
	4, 7, 0, 	4, 0, 3		// East +X
```

VBO and EBO
```
mVertices[120] = {
			// Down -Y
			 0.5f, -0.5f,  0.5f, 1.0f, 0.0f,    // 0
			-0.5f, -0.5f,  0.5f, 0.0f, 0.0f,    // 1
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,    // 2
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,    // 3
			// Up +Y
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,    // 4
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,    // 5
			-0.5f,  0.5f,  0.5f, 0.0f, 1.0f,    // 6
			 0.5f,  0.5f,  0.5f, 1.0f, 1.0f,    // 7
			// North -Z
			-0.5f,  0.5f, -0.5f, 1.0f, 0.0f,    // 5
			 0.5f,  0.5f, -0.5f, 0.0f, 0.0f,    // 4
			 0.5f, -0.5f, -0.5f, 0.0f, 1.0f,    // 3
			-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,    // 2
			// South +Z
			 0.5f,  0.5f,  0.5f, 1.0f, 0.0f,    // 7
			-0.5f,  0.5f,  0.5f, 0.0f, 0.0f,    // 6
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,    // 1
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,    // 0
			// West -X
			-0.5f,  0.5f,  0.5f, 1.0f, 0.0f,    // 6
			-0.5f,  0.5f, -0.5f, 0.0f, 0.0f,    // 5
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,    // 2
			-0.5f, -0.5f,  0.5f, 1.0f, 1.0f,    // 1
			// East +X
			 0.5f,  0.5f, -0.5f, 1.0f, 0.0f,    // 4
			 0.5f,  0.5f,  0.5f, 0.0f, 0.0f,    // 7
			 0.5f, -0.5f,  0.5f, 0.0f, 1.0f,    // 0
			 0.5f, -0.5f, -0.5f, 1.0f, 1.0f,    // 3
		}
		
mIndices[36] = {
			0, 1, 2,    	0, 2, 3,	// Down -Y
			4, 5, 6, 		4, 6, 7,	// Up +Y
			8, 9, 10, 		8, 10, 11,	// North -Z
			12, 13, 14, 	12, 14, 15,	// South +Z
			16, 17, 18, 	16, 18, 19,	// West -X
			20, 21, 22, 	20, 22, 23	// East +X
		};
```

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
https://github.com/DethRaid/minecraft-texture-viewer/blob/master/src/render/camera.h
https://github.com/yocover/start-learning-opengl

VAO VBO to merge into one model/element class
https://github.com/VictorGordan/opengl-tutorials

Shader.cpp for shader as a shader program
https://github.com/amanshenoy/mesh-viewer