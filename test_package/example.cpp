#include <iostream>

extern "C"{
    #include "lambert.h"
}


int main() {
    //Declares origin point and translated point
    YGPoint point = YGMeterPoint(994272.661, 113467.422, 0);

    //Converts point in Lambert Zone 1 to WGS84
    point = YGPointConvertWGS84(point, LAMBERT_I);

    //Convert to Degree
    point = YGPointToDegree(point);

    std::cout << "Lat:" << point.y << "Lon:" << point.x;
}
