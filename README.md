# bpmcounter3
 * Arduino UNO BPM counter
 * 
 * Small utility to display BPM on a 16x2 I2C LED display with a Arduino
 * Written for DIN Sync devices like the TR-606, with no speed display.  
 * Counts clock pulses/s, so it needs a fast clock (24ppq DIN sync or faster), 
 * if you want to determine BPM from a slow clock, like a click track or drum 
 * trigger, use my bpmcounter2 utility (which calculates speed from the timing  
 * between each pair of clicks)
 * 
 * Connect the (TTL level) clock signal to pin 2 (and ground to GND) - e.g. 
 * DIN Sync Pin 3 to Arduino Uno Pin 2, DIN Pin 2 to any GND terminal on the Uno 
 * 
 * Copyright 2018 Sevo Stille <mailto:sevo@radiox.de>
 * @license GPL-3.0+ <http://www.gnu.org/licenses/gpl.html>
