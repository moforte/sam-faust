declare name 		"volume";
declare version 	"1.0";
declare author 		"Analog Devices";
declare license 	"BSD";
declare copyright 	"(c)Analog Devices 2018";

//-----------------------------------------------
// 			Volume control in dB
//-----------------------------------------------

import("stdfaust.lib");

channel1		=  vslider("[1]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo;
channel2		=  vslider("[2]", 0, -70, +4, 0.1) : ba.db2linear : si.smoo;

//process		= _,_: *(channel1), *(channel2);
process		= *(channel1), *(channel2);
