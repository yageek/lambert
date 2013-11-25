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

```c
//Declares origin point and translated point
YGPoint point = YGMeterPoint(994272.661,113467.422);

//Converts point in Lambert Zone 1 to WGS84
point = YGPointConvertWGS84(point,LAMBERT_I)

//Convert to Degree
point = YGPointToDegree(point);

printf("Lat:%.9f - Lon:%.9f",point.y,point.x);
```

#License
Copyright (c) 2013 Yannick Heinrich - Released under the GPLv2 License.

