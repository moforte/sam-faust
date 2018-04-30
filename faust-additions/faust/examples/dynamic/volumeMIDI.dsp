declare name 		"volume";
declare version 	"1.0";
declare author 		"Analog Devices";
declare license 	"BSD";
declare copyright 	"(c)Analog Devices 2018";

//-----------------------------------------------
// 			Volume control in dB
//-----------------------------------------------

import("stdfaust.lib");

gain		= vslider("Volume[midi:ctrl 7]" , 0, -70, +4, 0.1) : ba.db2linear : si.smoo;

process		= *(gain);
