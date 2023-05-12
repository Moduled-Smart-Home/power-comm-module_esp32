(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: Alignment Drills_3_edit_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Wednesday, 26 April 2023 at 23:01)

(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 3.125)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 25.0)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -2.5)

(Tools Offset: )
(Tool: 1 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 1.0)

(Z Toolchange: 15 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 0.5 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)

(X range:   -1.5625 ...    1.5625  mm)
(Y range:  -59.5625 ...   59.5625  mm)

(Spindle Speed: 1200 RPM)
G21
G90
G94

G01 F25.00

M5
G00 Z15.0000
T1
G00 X0.0000 Y0.0000                
M6
(MSG, Change to Tool Dia = 3.1250 ||| Total drills for tool T1 = 2)
M0
G00 Z15.0000

G01 F25.00
M03 S1200
G00 X0.0000 Y58.0000
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X0.0000 Y-58.0000
G01 Z-2.5000
G01 Z0
G00 Z1.0000
M05
G00 Z0.50

