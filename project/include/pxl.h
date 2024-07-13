#ifndef PXL_H_
#define PXL_H_
#include <stdint.h>

struct PXL {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

void init_pxl1(struct PXL *p);
void init_pxl2(struct PXL *p, uint8_t red_, uint8_t green_, uint8_t blue_, uint8_t alpha_);

#endif
