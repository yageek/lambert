#ifndef __NTV2_H
#define __NTV2_H
#include "lambert.h"

YGTransform __YGTransformNTFToRGF93(YGPoint pt);
YGTransform __YGTransformRGF93ToNTF(YGPoint pt);

YGPoint YGPointConvertRGF93_NTF(YGPoint point);

YGPoint YGPointConvertNTF_RGF93(YGPoint point);



#endif