# Technics_SL-DZ1200_new_life
 Technics, creating a new motherboard and display module.

This is a project to bring back to life the Technics SL-DZ1200 DJ player.

A new motherboard has been developed, based on the STM32F429 microcontroller. A new display module based on two OLED displays with a high frame refresh rate.

Added support for large capacity SD cards (64GB tested), support for playlists imported from Rekordbox, playback of wav files 16bit 44.1kHz only.

Display static and dynamic waveform, 8 hotspots, loop, slip loop, beat jump.

Digital SPDIF output is supported.

In addition to replacing the motherboard, it is necessary to modify the control panel boards and replace the display module.


Technics SL-DZ1200 new life. Comparison of sound and construction with the original deck:

https://youtu.be/YNCWHuYRNV8?si=jEZ1Wb_wVn2iVH1T

Other videos:

https://youtube.com/shorts/xwd6WtisLp0?si=1c5YiPtq2MnMOLq1

https://youtube.com/shorts/Ao05V8m91X4?si=t5FqrDS9XYP-LJhe

https://youtube.com/shorts/iWsxXxv2L6M?si=lasyaPYv3nFeNMoB

https://youtube.com/shorts/TOsjFpwztxs?si=jLOTwwjx0vi9ndan



//	ver. 0.10
//		- 64MB SDRAM
//		- 2 OLED displays
// 		- added scratch track
//	ver. 0.21
//		- project ported to new pcb
//		- configured to work with the new DAC and SPDIF transmitter
//		- most peripherals initialized
//	ver. 0.23
//		- most peripherals initialized
//	ver. 0.25
//		- TIM8 bug fixed. Missing a line: HAL_TIM_OnePulse_Init(&htim8, TIM_OPMODE_SINGLE) != HAL_OK)
//	ver. 0.26
//		- minor fixes
//	ver. 0.27
//		- split into separate *.h files
//		- oled driver optimization
//	ver. 0.31
//		- added uart
//		- added rgb leds function
//		- added HD74HC164P LEDs
//		- oled driver optimization
//		- unused libraries cleaned up
//	ver. 0.32
//		- added adc process
//		- TIM1 change config 333Hz->10KHz
//	ver. 0.33
//		- changed OLDEs configuration
//		- added uart commands
//		- LEDS_LOAD prc for HD74HC164P moved to audio handler 
//	ver. 0.34
//		- TIM1 change config 10KHz->3333Hz
//		- added buttons prc
//	ver. 0.35
//		- minor fixes
//	ver. 0.36
//		- change motor GPIO initial state
//	ver. 0.37
//		- minor fixes
//	ver. 0.38
//		- add WFORMDYNAMIC reading prc
//	ver. 0.41
//		- minor fixes
//	ver. 0.42
//		- added rekordbox parser
//	ver. 0.43
//		-	add blinking pads
//	ver. 0.44
//		- minor fixes
//	ver. 0.47
//		-	added test sdram
//		-	added uart status messages
//	ver. 0.49
//		-	added support use_lfn in fatfs
//		- minor fixes
//	ver. 0.51
//		- improved SDRAM test
//		-	added fw version register to main.c
//	ver. 0.53
//		- minor fixes
//		-	changed the size of the heap and stack by 2X. Now Stack_Size 0x1000; Heap_Size 0x800;
//	ver. 0.57
//		-	improved OLED library
//		- rekordbox parser optimized
//	ver. 0.61
//		-	improved OLED library
//		-	improved track loading process
//	ver. 0.63
//		-	added optimization waveforms with color coefficient
//	ver. 0.67
//		- rekordbox parser improved
//	ver. 0.68
//		-	fixed drawing of static waveform
//	ver. 0.69
//		- minor fixes
//	ver. 0.70
//		- CDJ900 font added
//		- minor fixes
//		- added pitch calculation
//	ver. 0.71
//		- added gui_generation.h
//	ver. 0.74
//		- minor fixes
//	ver. 0.77
//		-	improved DrawMinuteMarkers()
//		- added ShowTempo()
//	ver. 0.81
//		- removed initialization of SDRAM area from the scatter file, which significantly speeded up system startup
//		-	added mini sdram test
//		- added ShowBPM()
//	ver. 0.85
//		- changed SDRAM parameter SdramTiming.WriteRecoveryTime = 4;			//2	//4 
//		- changed adc pitch aproximation
//		- added adc pitch hysteresis 
//		- added DDM speed regulation
//		- changed audio resampling coeff: optimal 32x, 4-point, 3rd-order optimal
//		- improved and optimized audio resampling algorithm
//	ver. 0.87
//		- regenerated code in CubeMX
//		- added encoder and timecode handlers
//	ver. 0.89
//		-	added timecode encoder in code handler
//	ver. 0.90
//		- minor fixes
//	ver. 0.92
//		- fixed oled ram select
//	ver. 0.93
//		-	added ROOT DISPLAY
//	ver. 0.97
//		- improved BORWSER functions
//	ver. 0.98
//		-	added SD cars remove-insert handler
//	ver. 0.99 
//		-	improved OLED_Putc function for outputting cut characters
//	ver. 1.00 
//		- fixed gui bug
//	ver. 1.03 
//		- fixed gui bug (increased size Stack_Size 0x1000, Heap_Size 0x800)
//		- improved waveform code
//	ver. 1.05
//		-	FontCDJ900 minor fixes
//		-	improved gui
//		-	added SD card symbol 
//	ver. 1.07
//		-	added beatjump with calculate jump distantion
//		-	added hot cues a, b, c
//	ver. 1.11
//		-	improved gui 
//		-	add browser animation
//		-	add 8 HOT CUES and PADS color from *.EXT file
