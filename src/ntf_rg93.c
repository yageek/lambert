#ifndef __LAMBERT_CONFIG_H
#define __LAMBERT_CONFIG_H

#include <stdio.h>
#include "ntf_rg93.h"
#include "config.h"

/**
* From : http://geodesie.ign.fr/contenu/fichiers/documentation/algorithmes/notice/NT111_V1_HARMEL_TransfoNTF-RGF93_FormatGrilleNTV2.pdf
*/

YGLambertPoint intpol_gsb(YGLambertPoint ntf_point)
{

	YGLambertPoint dest = {0,0,0};

	double longdd_NTF = ntf_point.x;
	double latdd_NTF = ntf_point.y;

	double lonw = -longdd_NTF*3600;
	double latn = latdd_NTF*3600;

	return dest;

}

void test_file()
{	
	sprintf("%s/%s",resource_file_path,"gr3df97a.txt");
	FILE *fd = fopen(resource_file_path)
	printf("Resource path : %s\n",resource_file_path);
}

#endif