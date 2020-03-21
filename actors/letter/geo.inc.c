// 0x0D00038C
extern void mill_letter_Draw();
const GeoLayout letter_geo[] = {
   GEO_CULLING_RADIUS(0x7fff),
   GEO_OPEN_NODE(),
   GEO_ASM(0, mill_letter_Draw),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
