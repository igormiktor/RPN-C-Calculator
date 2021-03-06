EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "RPN Calculator"
Date "2021-02-27"
Rev "1"
Comp "Igor M-T"
Comment1 ""
Comment2 "See:  https://github.com/igormiktor/RPN-C-Calculator"
Comment3 "with a 4x4 button keypad and a 2x16 character LCD display."
Comment4 "Schematic for an RPN calculator based on an ATmega328P"
$EndDescr
Connection ~ 9200 4900
Wire Wire Line
	8250 3450 8250 4200
Connection ~ 8250 3450
Wire Wire Line
	8000 3450 8250 3450
Wire Wire Line
	8250 2900 8250 3450
Wire Wire Line
	8000 2900 8250 2900
Connection ~ 7200 3300
Wire Wire Line
	7200 3450 7700 3450
Wire Wire Line
	7200 3300 7200 3450
Connection ~ 7200 3000
Wire Wire Line
	7200 2900 7700 2900
Wire Wire Line
	7200 3000 7200 2900
Wire Wire Line
	5150 3300 7200 3300
Wire Wire Line
	5150 2850 5150 3300
Wire Wire Line
	5250 3000 7200 3000
Wire Wire Line
	5250 2850 5250 3000
Wire Wire Line
	8100 4900 9200 4900
Connection ~ 4950 5250
Connection ~ 4550 5400
Wire Wire Line
	4550 5400 5550 5400
Connection ~ 4550 6050
Wire Wire Line
	4550 6050 5650 6050
Wire Wire Line
	4550 6800 5750 6800
Connection ~ 4550 7550
Wire Wire Line
	7800 4200 8250 4200
Connection ~ 7800 4200
Wire Wire Line
	7800 4500 7800 4200
Wire Wire Line
	6500 4200 7800 4200
NoConn ~ 7600 4500
NoConn ~ 7500 4500
NoConn ~ 7400 4500
NoConn ~ 7300 4500
$Comp
L Device:Crystal Oscillator
U 1 1 6141B845
P 7200 3150
F 0 "Oscillator" V 7246 3019 50  0000 R CNN
F 1 "16 MHz" V 7155 3019 50  0000 R CNN
F 2 "" H 7200 3150 50  0001 C CNN
F 3 "~" H 7200 3150 50  0001 C CNN
	1    7200 3150
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C2
U 1 1 6148BE17
P 7850 2900
F 0 "C2" V 8102 2900 50  0000 C CNN
F 1 "22pF" V 8011 2900 50  0000 C CNN
F 2 "" H 7888 2750 50  0001 C CNN
F 3 "~" H 7850 2900 50  0001 C CNN
	1    7850 2900
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C3
U 1 1 6148CA3A
P 7850 3450
F 0 "C3" V 8102 3450 50  0000 C CNN
F 1 "22pF" V 8011 3450 50  0000 C CNN
F 2 "" H 7888 3300 50  0001 C CNN
F 3 "~" H 7850 3450 50  0001 C CNN
	1    7850 3450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4950 3700 4950 2850
Wire Wire Line
	7200 3700 4950 3700
Wire Wire Line
	7200 4500 7200 3700
Wire Wire Line
	4850 3750 4850 2850
Wire Wire Line
	7100 3750 4850 3750
Wire Wire Line
	7100 4500 7100 3750
Wire Wire Line
	4750 3800 4750 2850
Wire Wire Line
	7000 3800 4750 3800
Wire Wire Line
	7000 4500 7000 3800
Wire Wire Line
	4650 3850 4650 2850
Wire Wire Line
	6900 3850 4650 3850
Wire Wire Line
	6900 4500 6900 3850
Wire Wire Line
	4550 3900 4550 2850
Wire Wire Line
	7700 3900 4550 3900
Wire Wire Line
	7700 4500 7700 3900
Wire Wire Line
	4450 3950 4450 2850
Wire Wire Line
	7900 3950 4450 3950
Wire Wire Line
	7900 4500 7900 3950
Wire Wire Line
	9200 5600 9200 4900
Wire Wire Line
	8400 5600 9200 5600
Wire Wire Line
	6500 4900 6500 4200
Connection ~ 6500 4900
Wire Wire Line
	6700 4900 6500 4900
Wire Wire Line
	6500 5400 6500 4900
Wire Wire Line
	7200 5400 6500 5400
Wire Wire Line
	7200 5300 7200 5400
Wire Wire Line
	7100 5600 8100 5600
Wire Wire Line
	7100 5300 7100 5600
Connection ~ 6350 2250
Connection ~ 3850 5400
Wire Wire Line
	4550 5400 4550 5250
Connection ~ 3150 5400
Wire Wire Line
	3850 5400 3850 5250
Wire Wire Line
	3150 5400 3150 5250
Wire Wire Line
	2450 5250 2450 5400
Connection ~ 3850 6050
Wire Wire Line
	4550 6050 4550 5900
Connection ~ 3150 6050
Wire Wire Line
	3850 6050 3850 5900
Wire Wire Line
	3150 6050 3150 5900
Wire Wire Line
	2450 5900 2450 6050
Wire Wire Line
	4550 6800 4550 6650
Connection ~ 3150 6800
Wire Wire Line
	3850 6800 3850 6650
Wire Wire Line
	3150 6800 3150 6650
Wire Wire Line
	2450 6650 2450 6800
Connection ~ 2850 6650
Connection ~ 2850 5900
Connection ~ 3550 5900
Connection ~ 3550 6650
Connection ~ 4950 6650
Connection ~ 4950 5900
Connection ~ 4250 5900
Connection ~ 3850 7550
Wire Wire Line
	4550 7550 4550 7350
Wire Wire Line
	3850 7550 4550 7550
Connection ~ 3150 7550
Wire Wire Line
	3850 7550 3850 7350
Wire Wire Line
	3150 7550 3850 7550
Wire Wire Line
	3150 7550 3150 7350
Wire Wire Line
	2450 7550 3150 7550
Wire Wire Line
	2450 7350 2450 7550
Wire Wire Line
	4950 6650 4950 7350
Wire Wire Line
	4950 5900 4950 6650
Wire Wire Line
	4950 5250 4950 5900
Wire Wire Line
	2600 3600 4350 3600
Connection ~ 2600 3600
Wire Wire Line
	2600 3200 2600 3600
Wire Wire Line
	4350 3600 4350 2850
Wire Wire Line
	2500 3600 2600 3600
Wire Wire Line
	2050 3600 2100 3600
Wire Wire Line
	2600 2250 2900 2250
Connection ~ 2600 2250
Connection ~ 3150 2250
Wire Wire Line
	2900 2250 2900 1000
$Comp
L Device:R_US R0
U 1 1 614C2B22
P 2600 3050
F 0 "R0" H 2668 3096 50  0000 L CNN
F 1 "10k Ohm" H 2668 3005 50  0000 L CNN
F 2 "" V 2640 3040 50  0001 C CNN
F 3 "~" H 2600 3050 50  0001 C CNN
	1    2600 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 614C0D81
P 8250 5600
F 0 "R3" V 8045 5600 50  0000 C CNN
F 1 "220 Ohm" V 8136 5600 50  0000 C CNN
F 2 "" V 8290 5590 50  0001 C CNN
F 3 "~" H 8250 5600 50  0001 C CNN
	1    8250 5600
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 61487C16
P 5550 1400
F 0 "C1" V 5298 1400 50  0000 C CNN
F 1 "100nF" V 5389 1400 50  0000 C CNN
F 2 "" H 5588 1250 50  0001 C CNN
F 3 "~" H 5550 1400 50  0001 C CNN
	1    5550 1400
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push Btn_R
U 1 1 61455D7B
P 2300 3600
F 0 "Btn_R" H 2300 3885 50  0000 C CNN
F 1 "CPU Reset" H 2300 3794 50  0000 C CNN
F 2 "" H 2300 3800 50  0001 C CNN
F 3 "~" H 2300 3800 50  0001 C CNN
	1    2300 3600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_4-4
U 1 1 6144C67B
P 4750 7350
F 0 "Btn_4-4" H 4750 7635 50  0000 C CNN
F 1 "\"+\"" H 4750 7544 50  0000 C CNN
F 2 "" H 4750 7550 50  0001 C CNN
F 3 "~" H 4750 7550 50  0001 C CNN
	1    4750 7350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_3-4
U 1 1 6144C671
P 4750 6650
F 0 "Btn_3-4" H 4750 6935 50  0000 C CNN
F 1 "\"-\"" H 4750 6844 50  0000 C CNN
F 2 "" H 4750 6850 50  0001 C CNN
F 3 "~" H 4750 6850 50  0001 C CNN
	1    4750 6650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_2-4
U 1 1 6144C667
P 4750 5900
F 0 "Btn_2-4" H 4750 6185 50  0000 C CNN
F 1 "\"x\"" H 4750 6094 50  0000 C CNN
F 2 "" H 4750 6100 50  0001 C CNN
F 3 "~" H 4750 6100 50  0001 C CNN
	1    4750 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_1-?4
U 1 1 6144C65D
P 4750 5250
F 0 "Btn_1-?4" H 4750 5535 50  0000 C CNN
F 1 "\"/\"" H 4750 5444 50  0000 C CNN
F 2 "" H 4750 5450 50  0001 C CNN
F 3 "~" H 4750 5450 50  0001 C CNN
	1    4750 5250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_4-3
U 1 1 6144C653
P 4050 7350
F 0 "Btn_4-3" H 4050 7635 50  0000 C CNN
F 1 "\"Enter\"" H 4050 7544 50  0000 C CNN
F 2 "" H 4050 7550 50  0001 C CNN
F 3 "~" H 4050 7550 50  0001 C CNN
	1    4050 7350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_3-3
U 1 1 6144C649
P 4050 6650
F 0 "Btn_3-3" H 4050 6935 50  0000 C CNN
F 1 "\"9\"" H 4050 6844 50  0000 C CNN
F 2 "" H 4050 6850 50  0001 C CNN
F 3 "~" H 4050 6850 50  0001 C CNN
	1    4050 6650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_2-3
U 1 1 6144C63F
P 4050 5900
F 0 "Btn_2-3" H 4050 6185 50  0000 C CNN
F 1 "\"6\"" H 4050 6094 50  0000 C CNN
F 2 "" H 4050 6100 50  0001 C CNN
F 3 "~" H 4050 6100 50  0001 C CNN
	1    4050 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_1-3
U 1 1 6144C635
P 4050 5250
F 0 "Btn_1-3" H 4050 5535 50  0000 C CNN
F 1 "\"3\"" H 4050 5444 50  0000 C CNN
F 2 "" H 4050 5450 50  0001 C CNN
F 3 "~" H 4050 5450 50  0001 C CNN
	1    4050 5250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_4-2
U 1 1 61441E0B
P 3350 7350
F 0 "Btn_4-2" H 3350 7635 50  0000 C CNN
F 1 "\"0\"" H 3350 7544 50  0000 C CNN
F 2 "" H 3350 7550 50  0001 C CNN
F 3 "~" H 3350 7550 50  0001 C CNN
	1    3350 7350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_3-2
U 1 1 61441E01
P 3350 6650
F 0 "Btn_3-2" H 3350 6935 50  0000 C CNN
F 1 "\"8\"" H 3350 6844 50  0000 C CNN
F 2 "" H 3350 6850 50  0001 C CNN
F 3 "~" H 3350 6850 50  0001 C CNN
	1    3350 6650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_2-2
U 1 1 61441DF7
P 3350 5900
F 0 "Btn_2-2" H 3350 6185 50  0000 C CNN
F 1 "\"5\"" H 3350 6094 50  0000 C CNN
F 2 "" H 3350 6100 50  0001 C CNN
F 3 "~" H 3350 6100 50  0001 C CNN
	1    3350 5900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_1-2
U 1 1 61441DED
P 3350 5250
F 0 "Btn_1-2" H 3350 5535 50  0000 C CNN
F 1 "\"2\"" H 3350 5444 50  0000 C CNN
F 2 "" H 3350 5450 50  0001 C CNN
F 3 "~" H 3350 5450 50  0001 C CNN
	1    3350 5250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_4-1
U 1 1 61422106
P 2650 7350
F 0 "Btn_4-1" H 2650 7635 50  0000 C CNN
F 1 "\"+/-\"" H 2650 7544 50  0000 C CNN
F 2 "" H 2650 7550 50  0001 C CNN
F 3 "~" H 2650 7550 50  0001 C CNN
	1    2650 7350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_3-1
U 1 1 614217CE
P 2650 6650
F 0 "Btn_3-1" H 2650 6935 50  0000 C CNN
F 1 "\"7\"" H 2650 6844 50  0000 C CNN
F 2 "" H 2650 6850 50  0001 C CNN
F 3 "~" H 2650 6850 50  0001 C CNN
	1    2650 6650
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push Btn_2-1
U 1 1 61420E5D
P 2650 5900
F 0 "Btn_2-1" H 2650 6185 50  0000 C CNN
F 1 "\"4\"" H 2650 6094 50  0000 C CNN
F 2 "" H 2650 6100 50  0001 C CNN
F 3 "~" H 2650 6100 50  0001 C CNN
	1    2650 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM_US POT
U 1 1 6141EA10
P 8850 4200
F 0 "POT" V 8645 4200 50  0000 C CNN
F 1 "LCD Brightness" V 8736 4200 50  0000 C CNN
F 2 "" H 8850 4200 50  0001 C CNN
F 3 "~" H 8850 4200 50  0001 C CNN
	1    8850 4200
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push Btn_1-1
U 1 1 6141C77D
P 2650 5250
F 0 "Btn_1-1" H 2650 5535 50  0000 C CNN
F 1 "\"1\"" H 2650 5444 50  0000 C CNN
F 2 "" H 2650 5450 50  0001 C CNN
F 3 "~" H 2650 5450 50  0001 C CNN
	1    2650 5250
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:RC1602A LCD
U 1 1 61416CB0
P 7400 4900
F 0 "LCD" V 7450 4850 50  0000 L CNN
F 1 "2x16 Character" V 7350 4650 50  0000 L CNN
F 2 "Display:RC1602A" H 7500 4100 50  0001 C CNN
F 3 "http://www.raystar-optronics.com/down.php?ProID=18" H 7500 4800 50  0001 C CNN
	1    7400 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	6350 2250 6150 2250
Wire Wire Line
	2350 2250 2600 2250
Connection ~ 2050 2550
Wire Wire Line
	3150 2550 3150 2250
$Comp
L Device:Battery_Cell Battery
U 1 1 613DB353
P 950 2600
F 0 "Battery" H 1068 2696 50  0000 L CNN
F 1 "9V" H 1068 2605 50  0000 L CNN
F 2 "" V 950 2660 50  0001 C CNN
F 3 "~" V 950 2660 50  0001 C CNN
	1    950  2600
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7805 L7805
U 1 1 613F411B
P 2050 2250
F 0 "L7805" H 2050 2492 50  0000 C CNN
F 1 "5V Voltage Regulator" H 2050 2401 50  0000 C CNN
F 2 "" H 2075 2100 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 2050 2200 50  0001 C CNN
	1    2050 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C1
U 1 1 613F3558
P 1500 2550
F 0 "C1" H 1591 2596 50  0000 L CNN
F 1 "0.1 mF" H 1591 2505 50  0000 L CNN
F 2 "" H 1500 2550 50  0001 C CNN
F 3 "~" H 1500 2550 50  0001 C CNN
	1    1500 2550
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU CPU
U 1 1 613D29E2
P 4650 2250
F 0 "CPU" V 4300 2250 50  0000 C CNN
F 1 "ATmega328P-PU" V 4450 2250 50  0000 C CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 4650 2250 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4650 2250 50  0001 C CNN
	1    4650 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	2600 2250 2600 2900
Wire Wire Line
	2050 2550 3150 2550
Wire Wire Line
	3950 2850 3950 4050
Wire Wire Line
	3850 2850 3850 3950
Wire Wire Line
	2450 5400 3150 5400
Wire Wire Line
	2850 5250 2850 5900
Wire Wire Line
	2450 6050 3150 6050
Wire Wire Line
	2850 5900 2850 6650
Wire Wire Line
	2450 6800 3150 6800
Wire Wire Line
	2850 6650 2850 7350
Wire Wire Line
	3150 6800 3850 6800
Wire Wire Line
	3550 6650 3550 7350
Wire Wire Line
	3150 6050 3850 6050
Wire Wire Line
	3550 5900 3550 6650
Wire Wire Line
	3150 5400 3850 5400
Wire Wire Line
	3550 5250 3550 5900
Wire Wire Line
	3850 5400 4550 5400
Wire Wire Line
	4250 5250 4250 5900
Wire Wire Line
	3850 6050 4550 6050
Wire Wire Line
	4250 5900 4250 6650
Connection ~ 4550 6800
Connection ~ 3850 6800
Connection ~ 4250 6650
Wire Wire Line
	3850 6800 4550 6800
Wire Wire Line
	4250 6650 4250 7350
NoConn ~ 4150 2850
NoConn ~ 4050 2850
NoConn ~ 5350 2850
NoConn ~ 5450 2850
Wire Wire Line
	950  2400 950  2250
Wire Wire Line
	950  2250 1500 2250
Wire Wire Line
	1500 2450 1500 2250
Wire Wire Line
	950  2700 950  2900
Wire Wire Line
	950  2900 1500 2900
Wire Wire Line
	1500 2650 1500 2900
Wire Wire Line
	8250 4200 8700 4200
Connection ~ 8250 4200
Wire Wire Line
	9000 4200 9200 4200
Connection ~ 9200 4200
Wire Wire Line
	9200 4200 9200 4900
Wire Wire Line
	7600 5300 8850 5300
Wire Wire Line
	8850 5300 8850 4350
Wire Wire Line
	5400 1400 3150 1400
Wire Wire Line
	3150 1400 3150 2250
Wire Wire Line
	5700 1400 5850 1400
Connection ~ 5850 1400
Wire Wire Line
	5850 1400 5850 1650
Wire Wire Line
	5850 1000 2900 1000
Connection ~ 5850 1000
Wire Wire Line
	5850 1000 5850 1400
Wire Wire Line
	5850 1000 6350 1000
Wire Wire Line
	6350 1000 6350 2250
Wire Wire Line
	2050 2550 2050 2900
Wire Wire Line
	1500 2250 1750 2250
Connection ~ 1500 2250
Wire Wire Line
	1500 2900 2050 2900
Connection ~ 1500 2900
Connection ~ 2050 2900
Wire Wire Line
	2050 2900 2050 3600
Connection ~ 2050 3600
Connection ~ 6500 4200
Wire Wire Line
	2050 4200 2050 5300
Wire Wire Line
	1550 4850 1550 5450
Wire Wire Line
	1550 4550 1550 4050
Connection ~ 2050 4200
Wire Wire Line
	1050 4800 1050 5000
$Comp
L Device:LED Green
U 1 1 6141DA86
P 1050 4650
F 0 "Green" V 1089 4533 50  0000 R CNN
F 1 "LED" V 998 4533 50  0000 R CNN
F 2 "" H 1050 4650 50  0001 C CNN
F 3 "~" H 1050 4650 50  0001 C CNN
	1    1050 4650
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED Red
U 1 1 6141F0C0
P 1550 4700
F 0 "Red" V 1589 4583 50  0000 R CNN
F 1 "LED" V 1498 4583 50  0000 R CNN
F 2 "" H 1550 4700 50  0001 C CNN
F 3 "~" H 1550 4700 50  0001 C CNN
	1    1550 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 614BE387
P 1550 5600
F 0 "R1" H 1618 5646 50  0000 L CNN
F 1 "330 Ohm" H 1618 5555 50  0000 L CNN
F 2 "" V 1590 5590 50  0001 C CNN
F 3 "~" H 1550 5600 50  0001 C CNN
	1    1550 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 614C01BC
P 1050 5150
F 0 "R2" H 1118 5196 50  0000 L CNN
F 1 "330 Ohm" H 1118 5105 50  0000 L CNN
F 2 "" V 1090 5140 50  0001 C CNN
F 3 "~" H 1050 5150 50  0001 C CNN
	1    1050 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3600 2050 4200
Wire Wire Line
	2050 4200 6500 4200
Wire Wire Line
	3850 3950 1050 3950
Wire Wire Line
	1050 3950 1050 4500
Wire Wire Line
	3950 4050 1550 4050
Wire Wire Line
	2050 5750 1550 5750
Wire Wire Line
	1050 5300 2050 5300
Connection ~ 2050 5300
Wire Wire Line
	2050 5300 2050 5750
Wire Wire Line
	3550 2850 3550 5250
Connection ~ 3550 5250
Wire Wire Line
	3450 2850 3450 4800
Wire Wire Line
	3450 4800 2850 4800
Wire Wire Line
	2850 4800 2850 5250
Connection ~ 2850 5250
Wire Wire Line
	3650 2850 3650 4800
Wire Wire Line
	3650 4800 4250 4800
Wire Wire Line
	4250 4800 4250 5250
Connection ~ 4250 5250
Wire Wire Line
	3750 2850 3750 4750
Wire Wire Line
	3750 4750 4950 4750
Wire Wire Line
	4950 4750 4950 5250
Wire Wire Line
	5550 2850 5550 5400
Wire Wire Line
	5650 2850 5650 6050
Wire Wire Line
	5750 2850 5750 6800
Wire Wire Line
	5850 2850 5850 7550
Wire Wire Line
	5850 7550 4550 7550
Wire Notes Line
	5150 4600 5150 7700
Wire Notes Line
	5150 7700 2250 7700
Wire Notes Line
	2250 7700 2250 4600
Wire Notes Line
	15900 4600 15900 4650
Wire Notes Line
	2250 4600 5150 4600
Text Notes 1450 6800 0    50   ~ 0
4x4 Button Keypad
Wire Wire Line
	6150 2350 6350 2350
Wire Wire Line
	6350 2350 6350 2250
Wire Wire Line
	6350 1000 9200 1000
Wire Wire Line
	9200 1000 9200 4200
Connection ~ 6350 1000
Text Label 7600 950  0    50   ~ 0
5V_Power
Text Label 4500 4300 0    50   ~ 0
Ground
$EndSCHEMATC
