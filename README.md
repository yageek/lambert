=======
#Description
A simple C library to convert Lambert coordinates to GPS WGS84 coordinates based on the [IGN algorithms and methods](http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NTG_71.pdf)

# Install

## Windows/Raw import

Add `lambert.h` and `lambert.c` into your project

## Unix/static library

Inside the source folders :

	mkdir build && cd build
	cmake ..
	make install

## Debian package

 You can obtain `.deb` from [bintray](https://bintray.com/yageek/deb/liblambert)

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

#Changelog
#### 2.0.1
* Fix bug when transforming coordinates from cartesian to geographic in non Lambert93.

#### 2.0.0
* Change API.

#### 1.0.1
* Fix bug in Lambert93 case.

#### 1.0.0
* First release.
