#include "pxl.h"

void init_pxl1(struct PXL *p) {
    p->red = 255;
    p->green = 255;
    p->blue = 255;
    p->alpha = 255;
}
void init_pxl2(struct PXL *p, uint8_t red_, uint8_t green_, uint8_t blue_, uint8_t alpha_) {
    p->red = red_;
    p->green = green_;
    p->blue = blue_;
    p->alpha = alpha_;
}