#ifndef __ORCS_H__
#define __ORCS_H__

#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

void into_orcish(char* src) {
	int len = strlen(src);
	if (len > 5) {
		src[0] = 'W';
		for (int i = 1; i < len - 4; ++i){
			src[i] = 'A';
		}
		src[len - 4] = 'G';
		src[len - 3] = 'H';
		src[len - 2] = '!';
		src[len - 1] = '\n';
	} else {
		memset(src, 0, BUF_SIZE);
		strcpy(src, "Unknown pattern\n");
	}		 
}


#endif