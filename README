#Description
A simple C library to convert Lambert Coordinates to GPS WGS84 coordinates based on the [IGN alorithms and methods](http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NTG_71.pdf)

# Install

## Windows/Raw import

Add `lambert.h` and `lambert.c` into your project

## Unix/static library

Inside the source folders :

	mkdir build && cd build
	cmake ..
	make install

# Usage

	//Declares origin point and translated point
	YGPoint pointOrg = {994272.661,113467.422,0};
	YGPoint pointDest;

	//Converts pointOrg in Lambert Zone 1 to WGS84
	//pointDest coordinates are expressed in radian
	lambert_to_wgs84(&pointOrg,&pointDest,LAMBERT_I);

	//Convert pointOrg in Lambert Zone 2 to WGS84
	//pointDest coordinates are expressed in degree
	lambert_to_wgs84_deg(&pointOrg,&pointDest,LAMBERT_II);

#License
Copyright (c) 2013 Yannick Heinrich - Released under the GPLv2 License.

