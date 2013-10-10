#ifndef __LAMBERT_CONFIG_H
#define __LAMBERT_CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "ntf_rg93.h"
#include "config.h"


#define MAX_LINE_BUFFER 1024
#define MAX_PATH_BUFFER 1024


/**
* From : http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NT111_V1_HARMEL_TransfoNTF-RGF93_FormatGrilleNTV2.pdf
*/

YGPoint intpol_gsb(YGPoint ntf_point)
{

	YGPoint dest = {0,0,0};

	double longdd_NTF = ntf_point.x;
	double latdd_NTF = ntf_point.y;

//	double lonw = -longdd_NTF*3600;
//	double latn = latdd_NTF*3600;

	return dest;

}
#endif