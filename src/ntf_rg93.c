#include "ntf_rg93.h"

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