#include "cpp/bind.h"

BIND_PROXY(mill, DynamicLetters, Draw)
const GeoLayout letter_geo[] = {
   GEO_CULLING_RADIUS(0x7fff),
   GEO_OPEN_NODE(),
   GEO_ASM(0, BINDED_FN(mill, DynamicLetters, Draw)),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
