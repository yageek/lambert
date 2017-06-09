[![badge](https://img.shields.io/badge/conan.io-lambert%2F2.0.1-green.svg?logo=data:image/png;base64%2CiVBORw0KGgoAAAANSUhEUgAAAA4AAAAOCAMAAAAolt3jAAAA1VBMVEUAAABhlctjlstkl8tlmMtlmMxlmcxmmcxnmsxpnMxpnM1qnc1sn85voM91oM11oc1xotB2oc56pNF6pNJ2ptJ8ptJ8ptN9ptN8p9N5qNJ9p9N9p9R8qtOBqdSAqtOAqtR%2BrNSCrNJ/rdWDrNWCsNWCsNaJs9eLs9iRvNuVvdyVv9yXwd2Zwt6axN6dxt%2Bfx%2BChyeGiyuGjyuCjyuGly%2BGlzOKmzOGozuKoz%2BKqz%2BOq0OOv1OWw1OWw1eWx1eWy1uay1%2Baz1%2Baz1%2Bez2Oe02Oe12ee22ujUGwH3AAAAAXRSTlMAQObYZgAAAAFiS0dEAIgFHUgAAAAJcEhZcwAACxMAAAsTAQCanBgAAAAHdElNRQfgBQkREyOxFIh/AAAAiklEQVQI12NgAAMbOwY4sLZ2NtQ1coVKWNvoc/Eq8XDr2wB5Ig62ekza9vaOqpK2TpoMzOxaFtwqZua2Bm4makIM7OzMAjoaCqYuxooSUqJALjs7o4yVpbowvzSUy87KqSwmxQfnsrPISyFzWeWAXCkpMaBVIC4bmCsOdgiUKwh3JojLgAQ4ZCE0AMm2D29tZwe6AAAAAElFTkSuQmCC)](http://www.conan.io/source/lambert/2.0.1/yageek/stable)

# lambert
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

## Conan

````
[requires]
lambert/2.0.1@yageek/stable

[generators]
cmake
````
See: https://www.conan.io/source/lambert/2.0.1/yageek/stable

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

# Changelog
#### 2.0.1
* Fix bug when transforming coordinates from cartesian to geographic in non Lambert93.

#### 2.0.0
* Change API.

#### 1.0.1
* Fix bug in Lambert93 case.

#### 1.0.0
* First release.
