#!/bin/sh

for i in *.png ; do ../../stm32plus/utils/bm2rgbi/bm2rgbi/bin/Debug/bm2rgbi.exe $i "${i%.*}.lzg" mc2pa8201 262 -c ; done