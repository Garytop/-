#ifndef SUAN_PNG_H_
#define SUAN_PNG_H_

#include <png.h>
#include "pxl.h"

struct PNG {
    struct PXL *image;
    int width;
    int height;
};

void init_PNG(struct PNG *p);
void delete_PNG(struct PNG *p);
int load(struct PNG *p, const char *file_name);
int save(struct PNG *p, const char *file_name);
struct PXL *get_PXL(struct PNG *p, int x, int y);

#endif
