#ifndef __NTF_RG93_H
#define __NTF_RG93_H

#include "lambert.h"

YGPoint intpol_gsb(YGPoint ntf_point);

void rgf93_to_ntf(YGPoint rgf_point);

void printParameters();

#endif