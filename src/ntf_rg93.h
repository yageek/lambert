#ifndef __NTF_RG93_H
#define __NTF_RG93_H

#include "lambert.h"

YGLambertPoint intpol_gsb(YGLambertPoint ntf_point);

void rgf93_to_ntf(YGLambertPoint rgf_point);

void printParameters();

#endif