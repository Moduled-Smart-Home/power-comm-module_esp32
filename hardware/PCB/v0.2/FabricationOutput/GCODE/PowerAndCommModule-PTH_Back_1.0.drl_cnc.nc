(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: PowerAndCommModule-PTH_Back.drl_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Saturday, 29 April 2023 at 23:35)

(This preprocessor is used with a motion controller loaded with GRBL firmware.)
(It is configured to be compatible with almost any version of GRBL firmware.)


(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 0.4)
(Tool: 2 -> Dia: 0.8)
(Tool: 3 -> Dia: 1.0)
(Tool: 4 -> Dia: 1.1)
(Tool: 5 -> Dia: 1.2)
(Tool: 6 -> Dia: 1.4)

(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 25.0)
(Tool: 2 -> Feedrate: 25.0)
(Tool: 3 -> Feedrate: 25.0)
(Tool: 4 -> Feedrate: 25.0)
(Tool: 5 -> Feedrate: 25.0)
(Tool: 6 -> Feedrate: 25.0)

(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)
(Tool: 2 -> Feedrate Rapids: 1500)
(Tool: 3 -> Feedrate Rapids: 1500)
(Tool: 4 -> Feedrate Rapids: 1500)
(Tool: 5 -> Feedrate Rapids: 1500)
(Tool: 6 -> Feedrate Rapids: 1500)

(Z_CUT: )
(Tool: 1 -> Z_Cut: -2.5)
(Tool: 2 -> Z_Cut: -2.5)
(Tool: 3 -> Z_Cut: -2.5)
(Tool: 4 -> Z_Cut: -2.5)
(Tool: 5 -> Z_Cut: -2.5)
(Tool: 6 -> Z_Cut: -2.5)

(Tools Offset: )
(Tool: 3 -> Offset Z: 0.0)
(Tool: 4 -> Offset Z: 0.0)
(Tool: 5 -> Offset Z: 0.0)

(Z_MOVE: )
(Tool: 1 -> Z_Move: 1.0)
(Tool: 2 -> Z_Move: 1.0)
(Tool: 3 -> Z_Move: 1.0)
(Tool: 4 -> Z_Move: 1.0)
(Tool: 5 -> Z_Move: 1.0)
(Tool: 6 -> Z_Move: 1.0)

(Z Toolchange: 15.0 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 0.5 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Steps per circle: 64)
(Preprocessor Excellon: GRBL_11_no_M6)

(X range:    6.4800 ...   42.9400  mm)
(Y range:  -22.2200 ...   25.2100  mm)

(Spindle Speed: 1000 RPM)
G21
G90
G17
G94


G01 F25.00

M5             
G00 Z15.0000
G00 X0.0000 Y0.0000                
T3
(MSG, Change to Tool Dia = 1.0000 ||| Total drills for tool T3 = 17)
M0
G00 Z15.0000
        
G01 F25.00
M03 S1000
G00 X12.0200 Y4.2200
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X12.0200 Y-0.7800
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X9.7400 Y-11.2600
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X17.3600 Y-11.2600
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X24.9800 Y-11.2600
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X27.5200 Y-11.2600
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X35.8900 Y-10.7900
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X35.8900 Y-15.2900
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X42.3900 Y-15.2900
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X42.3900 Y-10.7900
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X41.4200 Y-5.9800
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X41.4200 Y9.4200
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X38.1200 Y14.5500
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X38.1200 Y17.0900
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X38.1200 Y19.6300
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X38.1200 Y22.1700
G01 Z-2.5000
G01 Z0
G00 Z1.0000
G00 X38.1200 Y24.7100
G01 Z-2.5000
G01 Z0
G00 Z1.0000
M05
G00 Z0.50

