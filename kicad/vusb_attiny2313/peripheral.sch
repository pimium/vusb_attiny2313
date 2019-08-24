EESchema Schematic File Version 4
LIBS:vusb_attiny2313-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:GND #PWR0101
U 1 1 5A3FDADE
P 6850 3350
F 0 "#PWR0101" H 6850 3100 50  0001 C CNN
F 1 "GND" H 6855 3177 50  0000 C CNN
F 2 "" H 6850 3350 50  0001 C CNN
F 3 "" H 6850 3350 50  0001 C CNN
	1    6850 3350
	1    0    0    -1  
$EndComp
Text Label 4400 4000 0    50   ~ 0
DATA_Q
Text Label 4400 4200 0    50   ~ 0
DATA_SCK
Text Label 4400 4500 0    50   ~ 0
DATA_CS
$Comp
L Memory_EPROM:27C256 U5
U 1 1 5D263362
P 6850 2100
F 0 "U5" H 6850 2250 50  0000 C CNN
F 1 "27C256" H 6850 2100 50  0000 C CNN
F 2 "modules:DIP_Socket-28pin_in_32_W11.9_W12.7_W15.24_W17.78_W18.5_3M_232-1285-00-0602J" H 6850 2100 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc0014.pdf" H 6850 2100 50  0001 C CNN
	1    6850 2100
	1    0    0    -1  
$EndComp
Entry Wire Line
	7450 1200 7550 1300
Entry Wire Line
	7450 1300 7550 1400
Entry Wire Line
	7450 1400 7550 1500
Entry Wire Line
	7450 1500 7550 1600
Entry Wire Line
	7450 1600 7550 1700
Entry Wire Line
	7450 1700 7550 1800
Entry Wire Line
	7450 1800 7550 1900
Entry Wire Line
	7450 1900 7550 2000
Wire Wire Line
	7250 1200 7450 1200
Wire Wire Line
	7250 1300 7450 1300
Wire Wire Line
	7250 1400 7450 1400
Wire Wire Line
	7250 1500 7450 1500
Wire Wire Line
	7250 1600 7450 1600
Wire Wire Line
	7250 1700 7450 1700
Wire Wire Line
	7250 1800 7450 1800
Wire Wire Line
	7250 1900 7450 1900
Text Label 7300 1200 0    50   ~ 0
D0
Text Label 7300 1300 0    50   ~ 0
D1
Text Label 7300 1400 0    50   ~ 0
D2
Text Label 7300 1500 0    50   ~ 0
D3
Text Label 7300 1600 0    50   ~ 0
D4
Text Label 7300 1700 0    50   ~ 0
D5
Text Label 7300 1800 0    50   ~ 0
D6
Text Label 7300 1900 0    50   ~ 0
D7
Text Label 7550 1000 3    50   ~ 0
D[0..7]
$Comp
L 74xx:74HC595 U1
U 1 1 5D28DFBE
P 5300 1600
F 0 "U1" H 5300 1550 50  0000 C CNN
F 1 "74HC595" H 5300 1300 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket_LongPads" H 5300 1600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5300 1600 50  0001 C CNN
	1    5300 1600
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC595 U3
U 1 1 5D298E2B
P 5300 4400
F 0 "U3" H 5300 4400 50  0000 C CNN
F 1 "74HC595" H 5300 4100 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket_LongPads" H 5300 4400 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5300 4400 50  0001 C CNN
	1    5300 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D2A7937
P 5300 2400
F 0 "#PWR0102" H 5300 2150 50  0001 C CNN
F 1 "GND" H 5305 2227 50  0000 C CNN
F 2 "" H 5300 2400 50  0001 C CNN
F 3 "" H 5300 2400 50  0001 C CNN
	1    5300 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 2400 5300 2300
$Comp
L power:VCC #PWR0103
U 1 1 5D2ABE10
P 6850 850
F 0 "#PWR0103" H 6850 700 50  0001 C CNN
F 1 "VCC" H 6867 1023 50  0000 C CNN
F 2 "" H 6850 850 50  0001 C CNN
F 3 "" H 6850 850 50  0001 C CNN
	1    6850 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 4000 4900 4000
Wire Wire Line
	4400 4200 4900 4200
$Comp
L power:GND #PWR0104
U 1 1 5D2B426C
P 4800 2400
F 0 "#PWR0104" H 4800 2150 50  0001 C CNN
F 1 "GND" H 4805 2227 50  0000 C CNN
F 2 "" H 4800 2400 50  0001 C CNN
F 3 "" H 4800 2400 50  0001 C CNN
	1    4800 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2400 4800 1800
Wire Wire Line
	4800 1800 4900 1800
Wire Wire Line
	4400 4500 4900 4500
$Comp
L power:VCC #PWR0105
U 1 1 5D2BD428
P 5300 850
F 0 "#PWR0105" H 5300 700 50  0001 C CNN
F 1 "VCC" H 5317 1023 50  0000 C CNN
F 2 "" H 5300 850 50  0001 C CNN
F 3 "" H 5300 850 50  0001 C CNN
	1    5300 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1200 4900 1200
Wire Wire Line
	4400 1400 4900 1400
Wire Wire Line
	4400 1700 4900 1700
$Comp
L power:GND #PWR0106
U 1 1 5D2C206A
P 5300 5200
F 0 "#PWR0106" H 5300 4950 50  0001 C CNN
F 1 "GND" H 5305 5027 50  0000 C CNN
F 2 "" H 5300 5200 50  0001 C CNN
F 3 "" H 5300 5200 50  0001 C CNN
	1    5300 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5200 5300 5100
$Comp
L power:GND #PWR0107
U 1 1 5D2C2071
P 4800 5200
F 0 "#PWR0107" H 4800 4950 50  0001 C CNN
F 1 "GND" H 4805 5027 50  0000 C CNN
F 2 "" H 4800 5200 50  0001 C CNN
F 3 "" H 4800 5200 50  0001 C CNN
	1    4800 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5200 4800 4600
Wire Wire Line
	4900 4600 4800 4600
Text Label 6050 2100 2    50   ~ 0
DATA_Q
Wire Wire Line
	5700 2100 6050 2100
Wire Wire Line
	5700 1200 6450 1200
Wire Wire Line
	6200 2000 6450 2000
Wire Wire Line
	6200 2100 6450 2100
Wire Wire Line
	6200 2200 6450 2200
Wire Wire Line
	6200 2300 6450 2300
Wire Wire Line
	6200 2400 6450 2400
Wire Wire Line
	6200 2500 6450 2500
Wire Wire Line
	6200 2600 6450 2600
Wire Wire Line
	5700 1300 6450 1300
Wire Wire Line
	5700 1400 6450 1400
Wire Wire Line
	5700 1500 6450 1500
Wire Wire Line
	5700 1600 6450 1600
Wire Wire Line
	5700 1700 6450 1700
Wire Wire Line
	5700 1800 6450 1800
Wire Wire Line
	5700 1900 6450 1900
Text Label 6200 2000 0    50   ~ 0
A8
Text Label 6200 2200 0    50   ~ 0
A10
Text Label 6200 2300 0    50   ~ 0
A11
Text Label 6200 2400 0    50   ~ 0
A12
Text Label 6200 2500 0    50   ~ 0
A13
Text Label 6200 2600 0    50   ~ 0
A14
Text Label 6050 4000 2    50   ~ 0
A8
Text Label 6600 4100 2    50   ~ 0
A9
Text Label 6050 4200 2    50   ~ 0
A10
Text Label 6050 4300 2    50   ~ 0
A11
Text Label 6050 4400 2    50   ~ 0
A12
Text Label 6050 4500 2    50   ~ 0
A13
Text Label 6050 4600 2    50   ~ 0
A14
Wire Wire Line
	5700 4000 6050 4000
Wire Wire Line
	5700 4200 6050 4200
Wire Wire Line
	5700 4300 6050 4300
Wire Wire Line
	5700 4400 6050 4400
Wire Wire Line
	5700 4500 6050 4500
Wire Wire Line
	5700 4600 6050 4600
Wire Wire Line
	5300 850  5300 1000
Wire Wire Line
	6850 850  6850 1000
NoConn ~ 5700 4700
Text Label 6050 4900 2    50   ~ 0
DATA_R
Wire Wire Line
	5700 4900 6050 4900
$Comp
L power:VCC #PWR0108
U 1 1 5D31F014
P 5300 3700
F 0 "#PWR0108" H 5300 3550 50  0001 C CNN
F 1 "VCC" H 5317 3873 50  0000 C CNN
F 2 "" H 5300 3700 50  0001 C CNN
F 3 "" H 5300 3700 50  0001 C CNN
	1    5300 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3700 5300 3800
Text Label 4400 6300 0    50   ~ 0
DATA_SCK
Text Label 4400 6600 0    50   ~ 0
DATA_CS
$Comp
L 74xx:74HC595 U4
U 1 1 5D326A1E
P 5300 6500
F 0 "U4" H 5300 6500 50  0000 C CNN
F 1 "74HC595" H 5300 6200 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm_Socket_LongPads" H 5300 6500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5300 6500 50  0001 C CNN
	1    5300 6500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6100 4900 6100
Wire Wire Line
	4400 6300 4900 6300
Wire Wire Line
	4400 6600 4900 6600
$Comp
L power:GND #PWR0109
U 1 1 5D326A28
P 5300 7350
F 0 "#PWR0109" H 5300 7100 50  0001 C CNN
F 1 "GND" H 5305 7177 50  0000 C CNN
F 2 "" H 5300 7350 50  0001 C CNN
F 3 "" H 5300 7350 50  0001 C CNN
	1    5300 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 7350 5300 7200
$Comp
L power:GND #PWR0110
U 1 1 5D326A2F
P 4800 7350
F 0 "#PWR0110" H 4800 7100 50  0001 C CNN
F 1 "GND" H 4805 7177 50  0000 C CNN
F 2 "" H 4800 7350 50  0001 C CNN
F 3 "" H 4800 7350 50  0001 C CNN
	1    4800 7350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 7350 4800 6700
Wire Wire Line
	4900 6700 4800 6700
Wire Wire Line
	5700 6100 6050 6100
Wire Wire Line
	5700 6200 6050 6200
Wire Wire Line
	5700 6300 6050 6300
NoConn ~ 5700 6800
Text Label 4400 6100 0    50   ~ 0
DATA_R
$Comp
L power:VCC #PWR0111
U 1 1 5D326A4A
P 5300 5800
F 0 "#PWR0111" H 5300 5650 50  0001 C CNN
F 1 "VCC" H 5317 5973 50  0000 C CNN
F 2 "" H 5300 5800 50  0001 C CNN
F 3 "" H 5300 5800 50  0001 C CNN
	1    5300 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5800 5300 5900
Wire Wire Line
	6850 3350 6850 3200
Wire Wire Line
	6200 2900 6450 2900
Wire Wire Line
	6200 3000 6450 3000
Text Label 6200 3000 0    50   ~ 0
~OE
Text Label 6050 6200 2    50   ~ 0
~OE
Text Label 6050 6100 2    50   ~ 0
~VPP
Text Label 6200 2800 0    50   ~ 0
VPP
NoConn ~ 5700 6500
NoConn ~ 5700 6600
NoConn ~ 5700 6700
Text HLabel 4400 1200 0    50   Input ~ 0
DATA_IN
Text HLabel 4400 1400 0    50   Input ~ 0
DATA_SCK
Text HLabel 6200 2900 0    50   Input ~ 0
DATA_CLR
Text HLabel 4400 1700 0    50   Input ~ 0
DATA_CS
Text Label 4400 1200 0    50   ~ 0
DATA_IN
Text Label 4400 1400 0    50   ~ 0
DATA_SCK
Text Label 4400 1700 0    50   ~ 0
DATA_CS
Text HLabel 7550 1000 1    50   Input ~ 0
D[0..7]
$Comp
L Transistor_BJT:2N3904 Q3
U 1 1 5D4607C7
P 2150 2200
F 0 "Q3" H 2341 2246 50  0000 L CNN
F 1 "2N3904" H 1900 2400 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2350 2125 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 2150 2200 50  0001 L CNN
	1    2150 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R10
U 1 1 5D460A1E
P 2250 1750
F 0 "R10" H 2309 1796 50  0000 L CNN
F 1 "47k" H 2309 1705 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2250 1750 50  0001 C CNN
F 3 "~" H 2250 1750 50  0001 C CNN
	1    2250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 6400 6050 6400
Text Label 6050 6300 2    50   ~ 0
A9_
Wire Wire Line
	6450 4100 6600 4100
Text Label 6200 2100 0    50   ~ 0
A9
$Comp
L Device:Q_PNP_CBE Q5
U 1 1 5D4608FE
P 2550 2500
F 0 "Q5" H 2741 2546 50  0000 L CNN
F 1 "2N3906" H 2741 2455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2750 2600 50  0001 C CNN
F 3 "~" H 2550 2500 50  0001 C CNN
	1    2550 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 1400 2650 1550
Wire Wire Line
	2250 1550 2650 1550
Connection ~ 2650 1550
Wire Wire Line
	2650 1550 2650 2300
Wire Wire Line
	2250 1550 2250 1650
Wire Wire Line
	2250 1850 2250 2000
Wire Wire Line
	2250 2400 2250 2500
Wire Wire Line
	2250 2500 2350 2500
Text Label 1450 4450 0    50   ~ 0
A9_
$Comp
L Transistor_BJT:2N3904 Q4
U 1 1 5D40637D
P 2150 4450
F 0 "Q4" H 2341 4496 50  0000 L CNN
F 1 "2N3904" H 1900 4650 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2350 4375 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 2150 4450 50  0001 L CNN
	1    2150 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R11
U 1 1 5D406384
P 2250 4000
F 0 "R11" H 2309 4046 50  0000 L CNN
F 1 "47k" H 2309 3955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2250 4000 50  0001 C CNN
F 3 "~" H 2250 4000 50  0001 C CNN
	1    2250 4000
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0113
U 1 1 5D40638B
P 2650 3650
F 0 "#PWR0113" H 2650 3500 50  0001 C CNN
F 1 "+12V" H 2665 3823 50  0000 C CNN
F 2 "" H 2650 3650 50  0001 C CNN
F 3 "" H 2650 3650 50  0001 C CNN
	1    2650 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4450 1950 4450
$Comp
L Device:Q_PNP_CBE Q6
U 1 1 5D406392
P 2550 4750
F 0 "Q6" H 2741 4796 50  0000 L CNN
F 1 "2N3906" H 2741 4705 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 2750 4850 50  0001 C CNN
F 3 "~" H 2550 4750 50  0001 C CNN
	1    2550 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3650 2650 3800
Wire Wire Line
	2250 3800 2650 3800
Connection ~ 2650 3800
Wire Wire Line
	2650 3800 2650 4550
Wire Wire Line
	2250 3800 2250 3900
Wire Wire Line
	2250 4100 2250 4250
Wire Wire Line
	2250 4650 2250 4750
Wire Wire Line
	2250 4750 2350 4750
Text Label 2650 5100 1    50   ~ 0
A9
Wire Wire Line
	2650 4950 2650 5100
$Comp
L power:VCC #PWR0114
U 1 1 5D41B347
P 3400 1400
F 0 "#PWR0114" H 3400 1250 50  0001 C CNN
F 1 "VCC" H 3417 1573 50  0000 C CNN
F 2 "" H 3400 1400 50  0001 C CNN
F 3 "" H 3400 1400 50  0001 C CNN
	1    3400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 2800 2650 2700
Wire Wire Line
	2650 2800 3400 2800
Text Label 3950 2800 2    50   ~ 0
VPP
Wire Wire Line
	1600 2200 1950 2200
Wire Wire Line
	3400 2600 3400 2800
Connection ~ 3400 2800
Wire Wire Line
	3400 1400 3400 2400
Wire Wire Line
	3400 2800 6450 2800
$Comp
L Device:D_Schottky_Small D7
U 1 1 5D452BBD
P 3400 2500
F 0 "D7" V 3446 2432 50  0000 R CNN
F 1 "SD 103BW" V 3355 2432 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" V 3400 2500 50  0001 C CNN
F 3 "~" V 3400 2500 50  0001 C CNN
	1    3400 2500
	0    -1   -1   0   
$EndComp
$Comp
L Device:D_Schottky_Small D8
U 1 1 5D45824B
P 6350 4100
F 0 "D8" H 6350 3895 50  0000 C CNN
F 1 "SD 103BW" H 6350 3986 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" V 6350 4100 50  0001 C CNN
F 3 "~" V 6350 4100 50  0001 C CNN
	1    6350 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 4100 6250 4100
NoConn ~ 5700 7000
Text Label 1600 2200 0    50   ~ 0
~VPP
$Comp
L power:+12V #PWR0112
U 1 1 5D46D86E
P 2650 1400
F 0 "#PWR0112" H 2650 1250 50  0001 C CNN
F 1 "+12V" H 2665 1573 50  0000 C CNN
F 2 "" H 2650 1400 50  0001 C CNN
F 3 "" H 2650 1400 50  0001 C CNN
	1    2650 1400
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D46DBF3
P 2250 1400
F 0 "#FLG0101" H 2250 1475 50  0001 C CNN
F 1 "PWR_FLAG" H 2250 1574 50  0000 C CNN
F 2 "" H 2250 1400 50  0001 C CNN
F 3 "~" H 2250 1400 50  0001 C CNN
	1    2250 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1400 2250 1550
Connection ~ 2250 1550
$Comp
L Device:R_Small R12
U 1 1 5D40DCB1
P 3800 1250
F 0 "R12" H 3859 1296 50  0000 L CNN
F 1 "1k" H 3859 1205 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3800 1250 50  0001 C CNN
F 3 "~" H 3800 1250 50  0001 C CNN
	1    3800 1250
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR0116
U 1 1 5D40DE3C
P 3800 850
F 0 "#PWR0116" H 3800 700 50  0001 C CNN
F 1 "VCC" H 3817 1023 50  0000 C CNN
F 2 "" H 3800 850 50  0001 C CNN
F 3 "" H 3800 850 50  0001 C CNN
	1    3800 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 850  3800 1150
Wire Wire Line
	3800 1350 3800 1500
Wire Wire Line
	3800 1500 4900 1500
NoConn ~ 6050 6400
$Comp
L Device:R_Small R14
U 1 1 5D41841B
P 4100 4050
F 0 "R14" H 4159 4096 50  0000 L CNN
F 1 "1k" H 4159 4005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4100 4050 50  0001 C CNN
F 3 "~" H 4100 4050 50  0001 C CNN
	1    4100 4050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR012
U 1 1 5D418422
P 4100 3650
F 0 "#PWR012" H 4100 3500 50  0001 C CNN
F 1 "VCC" H 4117 3823 50  0000 C CNN
F 2 "" H 4100 3650 50  0001 C CNN
F 3 "" H 4100 3650 50  0001 C CNN
	1    4100 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 3650 4100 3950
Wire Wire Line
	4100 4150 4100 4300
Wire Wire Line
	4100 4300 4900 4300
$Comp
L Device:R_Small R13
U 1 1 5D41DFAC
P 4050 6150
F 0 "R13" H 4109 6196 50  0000 L CNN
F 1 "1k" H 4109 6105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 6150 50  0001 C CNN
F 3 "~" H 4050 6150 50  0001 C CNN
	1    4050 6150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR05
U 1 1 5D41DFB3
P 4050 5750
F 0 "#PWR05" H 4050 5600 50  0001 C CNN
F 1 "VCC" H 4067 5923 50  0000 C CNN
F 2 "" H 4050 5750 50  0001 C CNN
F 3 "" H 4050 5750 50  0001 C CNN
	1    4050 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 5750 4050 6050
Wire Wire Line
	4050 6250 4050 6400
Wire Wire Line
	4050 6400 4900 6400
Wire Bus Line
	7550 1000 7550 2150
$EndSCHEMATC