(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)

(Name: AlignmentSlots_Back_mill_slot_cnc)
(Type: G-code from Geometry)
(Units: MM)

(Created on Sunday, 30 April 2023 at 10:34)

(This preprocessor is used with a motion controller loaded with GRBL firmware.)
(It is configured to be compatible with almost any version of GRBL firmware.)

(TOOL DIAMETER: 1.2 mm)
(Feedrate_XY: 15.0 mm/min)
(Feedrate_Z: 15.0 mm/min)
(Feedrate rapids 1500.0 mm/min)

(Z_Cut: -2.5 mm)
(Z_Move: 1.0 mm)
(Z Start: None mm)
(Z End: 5.0 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Steps per circle: 64)
(Preprocessor Geometry: GRBL_11_no_M6)

(X range:   -8.1251 ...   58.1251  mm)
(Y range:   -4.3578 ...    4.3578  mm)

(Spindle Speed: 1000.0 RPM)
G21
G90
G17
G94


G01 F15.00

M5             
G00 Z5.0000
G00 X0.0000 Y0.0000                
T1
(MSG, Change to Tool Dia = 1.2000)
M0
G00 Z5.0000
        
M03 S1000.0
G01 F15.00
G00 X-8.1251 Y3.2327
G01 F15.00
G01 Z-2.5000
G01 F15.00
G01 X-8.1248 Y3.2603 F15.00
G01 X-8.1237 Y3.2879 F15.00
G01 X-8.1221 Y3.3154 F15.00
G01 X-8.1197 Y3.3429 F15.00
G01 X-8.1166 Y3.3704 F15.00
G01 X-8.1129 Y3.3977 F15.00
G01 X-8.1085 Y3.4250 F15.00
G01 X-8.1035 Y3.4522 F15.00
G01 X-8.0978 Y3.4792 F15.00
G01 X-8.0914 Y3.5060 F15.00
G01 X-8.0843 Y3.5327 F15.00
G01 X-8.0767 Y3.5593 F15.00
G01 X-8.0683 Y3.5856 F15.00
G01 X-8.0593 Y3.6117 F15.00
G01 X-8.0497 Y3.6376 F15.00
G01 X-8.0395 Y3.6632 F15.00
G01 X-8.0286 Y3.6886 F15.00
G01 X-8.0171 Y3.7137 F15.00
G01 X-8.0050 Y3.7385 F15.00
G01 X-7.9922 Y3.7630 F15.00
G01 X-7.9789 Y3.7872 F15.00
G01 X-7.9650 Y3.8111 F15.00
G01 X-7.9505 Y3.8346 F15.00
G01 X-7.9355 Y3.8577 F15.00
G01 X-7.9199 Y3.8805 F15.00
G01 X-7.9037 Y3.9029 F15.00
G01 X-7.8870 Y3.9249 F15.00
G01 X-7.8697 Y3.9464 F15.00
G01 X-7.8519 Y3.9675 F15.00
G01 X-7.8336 Y3.9882 F15.00
G01 X-7.8149 Y4.0085 F15.00
G01 X-7.7956 Y4.0282 F15.00
G01 X-7.7758 Y4.0475 F15.00
G01 X-7.7556 Y4.0663 F15.00
G01 X-7.7349 Y4.0846 F15.00
G01 X-7.7138 Y4.1024 F15.00
G01 X-7.6922 Y4.1196 F15.00
G01 X-7.6702 Y4.1363 F15.00
G01 X-7.6478 Y4.1525 F15.00
G01 X-7.6251 Y4.1681 F15.00
G01 X-7.6019 Y4.1832 F15.00
G01 X-7.5784 Y4.1977 F15.00
G01 X-7.5546 Y4.2116 F15.00
G01 X-7.5304 Y4.2249 F15.00
G01 X-7.5059 Y4.2376 F15.00
G01 X-7.4810 Y4.2497 F15.00
G01 X-7.4559 Y4.2612 F15.00
G01 X-7.4306 Y4.2721 F15.00
G01 X-7.4049 Y4.2824 F15.00
G01 X-7.3790 Y4.2920 F15.00
G01 X-7.3529 Y4.3010 F15.00
G01 X-7.3266 Y4.3093 F15.00
G01 X-7.3001 Y4.3170 F15.00
G01 X-7.2734 Y4.3240 F15.00
G01 X-7.2465 Y4.3304 F15.00
G01 X-7.2195 Y4.3361 F15.00
G01 X-7.1923 Y4.3412 F15.00
G01 X-7.1651 Y4.3456 F15.00
G01 X-7.1377 Y4.3493 F15.00
G01 X-7.1103 Y4.3523 F15.00
G01 X-7.0828 Y4.3547 F15.00
G01 X-7.0552 Y4.3564 F15.00
G01 X-7.0276 Y4.3574 F15.00
G01 X-7.0000 Y4.3578 F15.00
G01 X-6.9724 Y4.3574 F15.00
G01 X-6.9448 Y4.3564 F15.00
G01 X-6.9172 Y4.3547 F15.00
G01 X-6.8897 Y4.3523 F15.00
G01 X-6.8623 Y4.3493 F15.00
G01 X-6.8349 Y4.3456 F15.00
G01 X-6.8077 Y4.3412 F15.00
G01 X-6.7805 Y4.3361 F15.00
G01 X-6.7535 Y4.3304 F15.00
G01 X-6.7266 Y4.3240 F15.00
G01 X-6.6999 Y4.3170 F15.00
G01 X-6.6734 Y4.3093 F15.00
G01 X-6.6471 Y4.3010 F15.00
G01 X-6.6210 Y4.2920 F15.00
G01 X-6.5951 Y4.2824 F15.00
G01 X-6.5694 Y4.2721 F15.00
G01 X-6.5441 Y4.2612 F15.00
G01 X-6.5190 Y4.2497 F15.00
G01 X-6.4941 Y4.2376 F15.00
G01 X-6.4696 Y4.2249 F15.00
G01 X-6.4454 Y4.2116 F15.00
G01 X-6.4216 Y4.1977 F15.00
G01 X-6.3981 Y4.1832 F15.00
G01 X-6.3749 Y4.1681 F15.00
G01 X-6.3522 Y4.1525 F15.00
G01 X-6.3298 Y4.1363 F15.00
G01 X-6.3078 Y4.1196 F15.00
G01 X-6.2862 Y4.1024 F15.00
G01 X-6.2651 Y4.0846 F15.00
G01 X-6.2444 Y4.0663 F15.00
G01 X-6.2242 Y4.0475 F15.00
G01 X-6.2044 Y4.0282 F15.00
G01 X-6.1851 Y4.0085 F15.00
G01 X-6.1664 Y3.9882 F15.00
G01 X-6.1481 Y3.9675 F15.00
G01 X-6.1303 Y3.9464 F15.00
G01 X-6.1130 Y3.9249 F15.00
G01 X-6.0963 Y3.9029 F15.00
G01 X-6.0801 Y3.8805 F15.00
G01 X-6.0645 Y3.8577 F15.00
G01 X-6.0495 Y3.8346 F15.00
G01 X-6.0350 Y3.8111 F15.00
G01 X-6.0211 Y3.7872 F15.00
G01 X-6.0078 Y3.7630 F15.00
G01 X-5.9950 Y3.7385 F15.00
G01 X-5.9829 Y3.7137 F15.00
G01 X-5.9714 Y3.6886 F15.00
G01 X-5.9605 Y3.6632 F15.00
G01 X-5.9503 Y3.6376 F15.00
G01 X-5.9407 Y3.6117 F15.00
G01 X-5.9317 Y3.5856 F15.00
G01 X-5.9233 Y3.5593 F15.00
G01 X-5.9157 Y3.5327 F15.00
G01 X-5.9086 Y3.5060 F15.00
G01 X-5.9022 Y3.4792 F15.00
G01 X-5.8965 Y3.4522 F15.00
G01 X-5.8915 Y3.4250 F15.00
G01 X-5.8871 Y3.3977 F15.00
G01 X-5.8834 Y3.3704 F15.00
G01 X-5.8803 Y3.3429 F15.00
G01 X-5.8779 Y3.3154 F15.00
G01 X-5.8763 Y3.2879 F15.00
G01 X-5.8752 Y3.2603 F15.00
G01 X-5.8749 Y3.2327 F15.00
G01 X-5.8749 Y-3.2327 F15.00
G01 X-5.8752 Y-3.2603 F15.00
G01 X-5.8763 Y-3.2879 F15.00
G01 X-5.8779 Y-3.3154 F15.00
G01 X-5.8803 Y-3.3429 F15.00
G01 X-5.8834 Y-3.3704 F15.00
G01 X-5.8871 Y-3.3977 F15.00
G01 X-5.8915 Y-3.4250 F15.00
G01 X-5.8965 Y-3.4522 F15.00
G01 X-5.9022 Y-3.4792 F15.00
G01 X-5.9086 Y-3.5060 F15.00
G01 X-5.9157 Y-3.5327 F15.00
G01 X-5.9233 Y-3.5593 F15.00
G01 X-5.9317 Y-3.5856 F15.00
G01 X-5.9407 Y-3.6117 F15.00
G01 X-5.9503 Y-3.6376 F15.00
G01 X-5.9605 Y-3.6632 F15.00
G01 X-5.9714 Y-3.6886 F15.00
G01 X-5.9829 Y-3.7137 F15.00
G01 X-5.9950 Y-3.7385 F15.00
G01 X-6.0078 Y-3.7630 F15.00
G01 X-6.0211 Y-3.7872 F15.00
G01 X-6.0350 Y-3.8111 F15.00
G01 X-6.0495 Y-3.8346 F15.00
G01 X-6.0645 Y-3.8577 F15.00
G01 X-6.0801 Y-3.8805 F15.00
G01 X-6.0963 Y-3.9029 F15.00
G01 X-6.1130 Y-3.9249 F15.00
G01 X-6.1303 Y-3.9464 F15.00
G01 X-6.1481 Y-3.9675 F15.00
G01 X-6.1664 Y-3.9882 F15.00
G01 X-6.1851 Y-4.0085 F15.00
G01 X-6.2044 Y-4.0282 F15.00
G01 X-6.2242 Y-4.0475 F15.00
G01 X-6.2444 Y-4.0663 F15.00
G01 X-6.2651 Y-4.0846 F15.00
G01 X-6.2862 Y-4.1024 F15.00
G01 X-6.3078 Y-4.1196 F15.00
G01 X-6.3298 Y-4.1363 F15.00
G01 X-6.3522 Y-4.1525 F15.00
G01 X-6.3749 Y-4.1681 F15.00
G01 X-6.3981 Y-4.1832 F15.00
G01 X-6.4216 Y-4.1977 F15.00
G01 X-6.4454 Y-4.2116 F15.00
G01 X-6.4696 Y-4.2249 F15.00
G01 X-6.4941 Y-4.2376 F15.00
G01 X-6.5190 Y-4.2497 F15.00
G01 X-6.5441 Y-4.2612 F15.00
G01 X-6.5694 Y-4.2721 F15.00
G01 X-6.5951 Y-4.2824 F15.00
G01 X-6.6210 Y-4.2920 F15.00
G01 X-6.6471 Y-4.3010 F15.00
G01 X-6.6734 Y-4.3093 F15.00
G01 X-6.6999 Y-4.3170 F15.00
G01 X-6.7266 Y-4.3240 F15.00
G01 X-6.7535 Y-4.3304 F15.00
G01 X-6.7805 Y-4.3361 F15.00
G01 X-6.8077 Y-4.3412 F15.00
G01 X-6.8349 Y-4.3456 F15.00
G01 X-6.8623 Y-4.3493 F15.00
G01 X-6.8897 Y-4.3523 F15.00
G01 X-6.9172 Y-4.3547 F15.00
G01 X-6.9448 Y-4.3564 F15.00
G01 X-6.9724 Y-4.3574 F15.00
G01 X-7.0000 Y-4.3578 F15.00
G01 X-7.0276 Y-4.3574 F15.00
G01 X-7.0552 Y-4.3564 F15.00
G01 X-7.0828 Y-4.3547 F15.00
G01 X-7.1103 Y-4.3523 F15.00
G01 X-7.1377 Y-4.3493 F15.00
G01 X-7.1651 Y-4.3456 F15.00
G01 X-7.1923 Y-4.3412 F15.00
G01 X-7.2195 Y-4.3361 F15.00
G01 X-7.2465 Y-4.3304 F15.00
G01 X-7.2734 Y-4.3240 F15.00
G01 X-7.3001 Y-4.3170 F15.00
G01 X-7.3266 Y-4.3093 F15.00
G01 X-7.3529 Y-4.3010 F15.00
G01 X-7.3790 Y-4.2920 F15.00
G01 X-7.4049 Y-4.2824 F15.00
G01 X-7.4306 Y-4.2721 F15.00
G01 X-7.4559 Y-4.2612 F15.00
G01 X-7.4810 Y-4.2497 F15.00
G01 X-7.5059 Y-4.2376 F15.00
G01 X-7.5304 Y-4.2249 F15.00
G01 X-7.5546 Y-4.2116 F15.00
G01 X-7.5784 Y-4.1977 F15.00
G01 X-7.6019 Y-4.1832 F15.00
G01 X-7.6251 Y-4.1681 F15.00
G01 X-7.6478 Y-4.1525 F15.00
G01 X-7.6702 Y-4.1363 F15.00
G01 X-7.6922 Y-4.1196 F15.00
G01 X-7.7138 Y-4.1024 F15.00
G01 X-7.7349 Y-4.0846 F15.00
G01 X-7.7556 Y-4.0663 F15.00
G01 X-7.7758 Y-4.0475 F15.00
G01 X-7.7956 Y-4.0282 F15.00
G01 X-7.8149 Y-4.0085 F15.00
G01 X-7.8336 Y-3.9882 F15.00
G01 X-7.8519 Y-3.9675 F15.00
G01 X-7.8697 Y-3.9464 F15.00
G01 X-7.8870 Y-3.9249 F15.00
G01 X-7.9037 Y-3.9029 F15.00
G01 X-7.9199 Y-3.8805 F15.00
G01 X-7.9355 Y-3.8577 F15.00
G01 X-7.9505 Y-3.8346 F15.00
G01 X-7.9650 Y-3.8111 F15.00
G01 X-7.9789 Y-3.7872 F15.00
G01 X-7.9922 Y-3.7630 F15.00
G01 X-8.0050 Y-3.7385 F15.00
G01 X-8.0171 Y-3.7137 F15.00
G01 X-8.0286 Y-3.6886 F15.00
G01 X-8.0395 Y-3.6632 F15.00
G01 X-8.0497 Y-3.6376 F15.00
G01 X-8.0593 Y-3.6117 F15.00
G01 X-8.0683 Y-3.5856 F15.00
G01 X-8.0767 Y-3.5593 F15.00
G01 X-8.0843 Y-3.5327 F15.00
G01 X-8.0914 Y-3.5060 F15.00
G01 X-8.0978 Y-3.4792 F15.00
G01 X-8.1035 Y-3.4522 F15.00
G01 X-8.1085 Y-3.4250 F15.00
G01 X-8.1129 Y-3.3977 F15.00
G01 X-8.1166 Y-3.3704 F15.00
G01 X-8.1197 Y-3.3429 F15.00
G01 X-8.1221 Y-3.3154 F15.00
G01 X-8.1237 Y-3.2879 F15.00
G01 X-8.1248 Y-3.2603 F15.00
G01 X-8.1251 Y-3.2327 F15.00
G01 X-8.1251 Y3.2327 F15.00
G00 Z1.0000
G00 X55.8749 Y3.2327
G01 F15.00
G01 Z-2.5000
G01 F15.00
G01 X55.8752 Y3.2603 F15.00
G01 X55.8763 Y3.2879 F15.00
G01 X55.8779 Y3.3154 F15.00
G01 X55.8803 Y3.3429 F15.00
G01 X55.8834 Y3.3704 F15.00
G01 X55.8871 Y3.3977 F15.00
G01 X55.8915 Y3.4250 F15.00
G01 X55.8965 Y3.4522 F15.00
G01 X55.9022 Y3.4792 F15.00
G01 X55.9086 Y3.5060 F15.00
G01 X55.9157 Y3.5327 F15.00
G01 X55.9233 Y3.5593 F15.00
G01 X55.9317 Y3.5856 F15.00
G01 X55.9407 Y3.6117 F15.00
G01 X55.9503 Y3.6376 F15.00
G01 X55.9605 Y3.6632 F15.00
G01 X55.9714 Y3.6886 F15.00
G01 X55.9829 Y3.7137 F15.00
G01 X55.9950 Y3.7385 F15.00
G01 X56.0078 Y3.7630 F15.00
G01 X56.0211 Y3.7872 F15.00
G01 X56.0350 Y3.8111 F15.00
G01 X56.0495 Y3.8346 F15.00
G01 X56.0645 Y3.8577 F15.00
G01 X56.0801 Y3.8805 F15.00
G01 X56.0963 Y3.9029 F15.00
G01 X56.1130 Y3.9249 F15.00
G01 X56.1303 Y3.9464 F15.00
G01 X56.1481 Y3.9675 F15.00
G01 X56.1664 Y3.9882 F15.00
G01 X56.1851 Y4.0085 F15.00
G01 X56.2044 Y4.0282 F15.00
G01 X56.2242 Y4.0475 F15.00
G01 X56.2444 Y4.0663 F15.00
G01 X56.2651 Y4.0846 F15.00
G01 X56.2862 Y4.1024 F15.00
G01 X56.3078 Y4.1196 F15.00
G01 X56.3298 Y4.1363 F15.00
G01 X56.3522 Y4.1525 F15.00
G01 X56.3749 Y4.1681 F15.00
G01 X56.3981 Y4.1832 F15.00
G01 X56.4216 Y4.1977 F15.00
G01 X56.4454 Y4.2116 F15.00
G01 X56.4696 Y4.2249 F15.00
G01 X56.4941 Y4.2376 F15.00
G01 X56.5190 Y4.2497 F15.00
G01 X56.5441 Y4.2612 F15.00
G01 X56.5694 Y4.2721 F15.00
G01 X56.5951 Y4.2824 F15.00
G01 X56.6210 Y4.2920 F15.00
G01 X56.6471 Y4.3010 F15.00
G01 X56.6734 Y4.3093 F15.00
G01 X56.6999 Y4.3170 F15.00
G01 X56.7266 Y4.3240 F15.00
G01 X56.7535 Y4.3304 F15.00
G01 X56.7805 Y4.3361 F15.00
G01 X56.8077 Y4.3412 F15.00
G01 X56.8349 Y4.3456 F15.00
G01 X56.8623 Y4.3493 F15.00
G01 X56.8897 Y4.3523 F15.00
G01 X56.9172 Y4.3547 F15.00
G01 X56.9448 Y4.3564 F15.00
G01 X56.9724 Y4.3574 F15.00
G01 X57.0000 Y4.3578 F15.00
G01 X57.0276 Y4.3574 F15.00
G01 X57.0552 Y4.3564 F15.00
G01 X57.0828 Y4.3547 F15.00
G01 X57.1103 Y4.3523 F15.00
G01 X57.1377 Y4.3493 F15.00
G01 X57.1651 Y4.3456 F15.00
G01 X57.1923 Y4.3412 F15.00
G01 X57.2195 Y4.3361 F15.00
G01 X57.2465 Y4.3304 F15.00
G01 X57.2734 Y4.3240 F15.00
G01 X57.3001 Y4.3170 F15.00
G01 X57.3266 Y4.3093 F15.00
G01 X57.3529 Y4.3010 F15.00
G01 X57.3790 Y4.2920 F15.00
G01 X57.4049 Y4.2824 F15.00
G01 X57.4306 Y4.2721 F15.00
G01 X57.4559 Y4.2612 F15.00
G01 X57.4810 Y4.2497 F15.00
G01 X57.5059 Y4.2376 F15.00
G01 X57.5304 Y4.2249 F15.00
G01 X57.5546 Y4.2116 F15.00
G01 X57.5784 Y4.1977 F15.00
G01 X57.6019 Y4.1832 F15.00
G01 X57.6251 Y4.1681 F15.00
G01 X57.6478 Y4.1525 F15.00
G01 X57.6702 Y4.1363 F15.00
G01 X57.6922 Y4.1196 F15.00
G01 X57.7138 Y4.1024 F15.00
G01 X57.7349 Y4.0846 F15.00
G01 X57.7556 Y4.0663 F15.00
G01 X57.7758 Y4.0475 F15.00
G01 X57.7956 Y4.0282 F15.00
G01 X57.8149 Y4.0085 F15.00
G01 X57.8336 Y3.9882 F15.00
G01 X57.8519 Y3.9675 F15.00
G01 X57.8697 Y3.9464 F15.00
G01 X57.8870 Y3.9249 F15.00
G01 X57.9037 Y3.9029 F15.00
G01 X57.9199 Y3.8805 F15.00
G01 X57.9355 Y3.8577 F15.00
G01 X57.9505 Y3.8346 F15.00
G01 X57.9650 Y3.8111 F15.00
G01 X57.9789 Y3.7872 F15.00
G01 X57.9922 Y3.7630 F15.00
G01 X58.0050 Y3.7385 F15.00
G01 X58.0171 Y3.7137 F15.00
G01 X58.0286 Y3.6886 F15.00
G01 X58.0395 Y3.6632 F15.00
G01 X58.0497 Y3.6376 F15.00
G01 X58.0593 Y3.6117 F15.00
G01 X58.0683 Y3.5856 F15.00
G01 X58.0767 Y3.5593 F15.00
G01 X58.0843 Y3.5327 F15.00
G01 X58.0914 Y3.5060 F15.00
G01 X58.0978 Y3.4792 F15.00
G01 X58.1035 Y3.4522 F15.00
G01 X58.1085 Y3.4250 F15.00
G01 X58.1129 Y3.3977 F15.00
G01 X58.1166 Y3.3704 F15.00
G01 X58.1197 Y3.3429 F15.00
G01 X58.1221 Y3.3154 F15.00
G01 X58.1237 Y3.2879 F15.00
G01 X58.1248 Y3.2603 F15.00
G01 X58.1251 Y3.2327 F15.00
G01 X58.1251 Y-3.2327 F15.00
G01 X58.1248 Y-3.2603 F15.00
G01 X58.1237 Y-3.2879 F15.00
G01 X58.1221 Y-3.3154 F15.00
G01 X58.1197 Y-3.3429 F15.00
G01 X58.1166 Y-3.3704 F15.00
G01 X58.1129 Y-3.3977 F15.00
G01 X58.1085 Y-3.4250 F15.00
G01 X58.1035 Y-3.4522 F15.00
G01 X58.0978 Y-3.4792 F15.00
G01 X58.0914 Y-3.5060 F15.00
G01 X58.0843 Y-3.5327 F15.00
G01 X58.0767 Y-3.5593 F15.00
G01 X58.0683 Y-3.5856 F15.00
G01 X58.0593 Y-3.6117 F15.00
G01 X58.0497 Y-3.6376 F15.00
G01 X58.0395 Y-3.6632 F15.00
G01 X58.0286 Y-3.6886 F15.00
G01 X58.0171 Y-3.7137 F15.00
G01 X58.0050 Y-3.7385 F15.00
G01 X57.9922 Y-3.7630 F15.00
G01 X57.9789 Y-3.7872 F15.00
G01 X57.9650 Y-3.8111 F15.00
G01 X57.9505 Y-3.8346 F15.00
G01 X57.9355 Y-3.8577 F15.00
G01 X57.9199 Y-3.8805 F15.00
G01 X57.9037 Y-3.9029 F15.00
G01 X57.8870 Y-3.9249 F15.00
G01 X57.8697 Y-3.9464 F15.00
G01 X57.8519 Y-3.9675 F15.00
G01 X57.8336 Y-3.9882 F15.00
G01 X57.8149 Y-4.0085 F15.00
G01 X57.7956 Y-4.0282 F15.00
G01 X57.7758 Y-4.0475 F15.00
G01 X57.7556 Y-4.0663 F15.00
G01 X57.7349 Y-4.0846 F15.00
G01 X57.7138 Y-4.1024 F15.00
G01 X57.6922 Y-4.1196 F15.00
G01 X57.6702 Y-4.1363 F15.00
G01 X57.6478 Y-4.1525 F15.00
G01 X57.6251 Y-4.1681 F15.00
G01 X57.6019 Y-4.1832 F15.00
G01 X57.5784 Y-4.1977 F15.00
G01 X57.5546 Y-4.2116 F15.00
G01 X57.5304 Y-4.2249 F15.00
G01 X57.5059 Y-4.2376 F15.00
G01 X57.4810 Y-4.2497 F15.00
G01 X57.4559 Y-4.2612 F15.00
G01 X57.4306 Y-4.2721 F15.00
G01 X57.4049 Y-4.2824 F15.00
G01 X57.3790 Y-4.2920 F15.00
G01 X57.3529 Y-4.3010 F15.00
G01 X57.3266 Y-4.3093 F15.00
G01 X57.3001 Y-4.3170 F15.00
G01 X57.2734 Y-4.3240 F15.00
G01 X57.2465 Y-4.3304 F15.00
G01 X57.2195 Y-4.3361 F15.00
G01 X57.1923 Y-4.3412 F15.00
G01 X57.1651 Y-4.3456 F15.00
G01 X57.1377 Y-4.3493 F15.00
G01 X57.1103 Y-4.3523 F15.00
G01 X57.0828 Y-4.3547 F15.00
G01 X57.0552 Y-4.3564 F15.00
G01 X57.0276 Y-4.3574 F15.00
G01 X57.0000 Y-4.3578 F15.00
G01 X56.9724 Y-4.3574 F15.00
G01 X56.9448 Y-4.3564 F15.00
G01 X56.9172 Y-4.3547 F15.00
G01 X56.8897 Y-4.3523 F15.00
G01 X56.8623 Y-4.3493 F15.00
G01 X56.8349 Y-4.3456 F15.00
G01 X56.8077 Y-4.3412 F15.00
G01 X56.7805 Y-4.3361 F15.00
G01 X56.7535 Y-4.3304 F15.00
G01 X56.7266 Y-4.3240 F15.00
G01 X56.6999 Y-4.3170 F15.00
G01 X56.6734 Y-4.3093 F15.00
G01 X56.6471 Y-4.3010 F15.00
G01 X56.6210 Y-4.2920 F15.00
G01 X56.5951 Y-4.2824 F15.00
G01 X56.5694 Y-4.2721 F15.00
G01 X56.5441 Y-4.2612 F15.00
G01 X56.5190 Y-4.2497 F15.00
G01 X56.4941 Y-4.2376 F15.00
G01 X56.4696 Y-4.2249 F15.00
G01 X56.4454 Y-4.2116 F15.00
G01 X56.4216 Y-4.1977 F15.00
G01 X56.3981 Y-4.1832 F15.00
G01 X56.3749 Y-4.1681 F15.00
G01 X56.3522 Y-4.1525 F15.00
G01 X56.3298 Y-4.1363 F15.00
G01 X56.3078 Y-4.1196 F15.00
G01 X56.2862 Y-4.1024 F15.00
G01 X56.2651 Y-4.0846 F15.00
G01 X56.2444 Y-4.0663 F15.00
G01 X56.2242 Y-4.0475 F15.00
G01 X56.2044 Y-4.0282 F15.00
G01 X56.1851 Y-4.0085 F15.00
G01 X56.1664 Y-3.9882 F15.00
G01 X56.1481 Y-3.9675 F15.00
G01 X56.1303 Y-3.9464 F15.00
G01 X56.1130 Y-3.9249 F15.00
G01 X56.0963 Y-3.9029 F15.00
G01 X56.0801 Y-3.8805 F15.00
G01 X56.0645 Y-3.8577 F15.00
G01 X56.0495 Y-3.8346 F15.00
G01 X56.0350 Y-3.8111 F15.00
G01 X56.0211 Y-3.7872 F15.00
G01 X56.0078 Y-3.7630 F15.00
G01 X55.9950 Y-3.7385 F15.00
G01 X55.9829 Y-3.7137 F15.00
G01 X55.9714 Y-3.6886 F15.00
G01 X55.9605 Y-3.6632 F15.00
G01 X55.9503 Y-3.6376 F15.00
G01 X55.9407 Y-3.6117 F15.00
G01 X55.9317 Y-3.5856 F15.00
G01 X55.9233 Y-3.5593 F15.00
G01 X55.9157 Y-3.5327 F15.00
G01 X55.9086 Y-3.5060 F15.00
G01 X55.9022 Y-3.4792 F15.00
G01 X55.8965 Y-3.4522 F15.00
G01 X55.8915 Y-3.4250 F15.00
G01 X55.8871 Y-3.3977 F15.00
G01 X55.8834 Y-3.3704 F15.00
G01 X55.8803 Y-3.3429 F15.00
G01 X55.8779 Y-3.3154 F15.00
G01 X55.8763 Y-3.2879 F15.00
G01 X55.8752 Y-3.2603 F15.00
G01 X55.8749 Y-3.2327 F15.00
G01 X55.8749 Y3.2327 F15.00
G00 Z1.0000
M05
G00 Z1.0000
G00 Z5.00

