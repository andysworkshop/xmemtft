#!/bin/sh

for i in *.png ; do ../../utility/bm2rgbi/bm2rgbi/bin/Release/bm2rgbi.exe $i "${i%.*}.lzg" mc2pa8201 262 -c ; done
