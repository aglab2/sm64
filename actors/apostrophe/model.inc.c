ALIGNED8 static const u8 apostrophe__18_rgba16[] = {
	0x94, 0xA5, 
};

ALIGNED8 static const u8 apostrophe__17_rgba16[] = {
	0xFF, 0xFF, 
};

const Gfx mat_apostrophe__18_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, apostrophe__18_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 0, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 0, 0, 0, 0),
	gsSPEndDisplayList(),
};


const Gfx mat_apostrophe__17_f3d[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, apostrophe__17_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPLoadSync(),
	gsDPLoadTile(7, 0, 0, 0, 0),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 0, 0),
	gsDPSetTileSize(0, 0, 0, 0, 0),
	gsSPEndDisplayList(),
};


static const Vtx apostrophe_apostrophe_50__mesh_vtx[] = {
	{{{23, -1, 44},0, {0x4, 0x10},{0x0, 0x81, 0x0, 0xFF}}},
	{{{12, -1, 68},0, {0xFFFB, 0xFFFB},{0x0, 0x81, 0x0, 0xFF}}},
	{{{0, -1, 67},0, {0xFFF0, 0xFFFB},{0x0, 0x81, 0x0, 0xFF}}},
	{{{20, -1, 59},0, {0x2, 0x2},{0x0, 0x81, 0x0, 0xFF}}},
	{{{35, -1, 87},0, {0xF, 0xFFEA},{0x0, 0x81, 0x0, 0xFF}}},
	{{{44, -1, 85},0, {0x17, 0xFFEC},{0x0, 0x81, 0x0, 0xFF}}},
	{{{36, -1, 120},0, {0x10, 0xFFCD},{0x0, 0x81, 0x0, 0xFF}}},
	{{{45, -1, 125},0, {0x18, 0xFFC8},{0x0, 0x81, 0x0, 0xFF}}},
	{{{29, -1, 123},0, {0x9, 0xFFCA},{0x0, 0x81, 0x0, 0xFF}}},
	{{{20, -1, 137},0, {0x1, 0xFFBE},{0x0, 0x81, 0x0, 0xFF}}},
	{{{29, -1, 90},0, {0x9, 0xFFE8},{0x0, 0x81, 0x0, 0xFF}}},
	{{{20, -1, 93},0, {0x1, 0xFFE5},{0x0, 0x81, 0x0, 0xFF}}},
	{{{20, -1, 59},0, {0x2, 0x2},{0x0, 0x81, 0x0, 0xFF}}},
	{{{29, -1, 90},0, {0x9, 0xFFE8},{0x0, 0x81, 0x0, 0xFF}}},
	{{{12, -1, 68},0, {0xFFFB, 0xFFFB},{0x0, 0x81, 0x0, 0xFF}}},
	{{{35, -1, 87},0, {0xF, 0xFFEA},{0x0, 0x81, 0x0, 0xFF}}},
	{{{29, -1, 123},0, {0x9, 0xFFCA},{0x0, 0x81, 0x0, 0xFF}}},
	{{{36, -1, 120},0, {0x10, 0xFFCD},{0x0, 0x81, 0x0, 0xFF}}},
};

const Gfx apostrophe_apostrophe_50__mesh_tri_0[] = {
	gsSPVertex(apostrophe_apostrophe_50__mesh_vtx + 0, 12, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 0, 3, 0),
	gsSP1Triangle(3, 0, 4, 0),
	gsSP1Triangle(4, 0, 5, 0),
	gsSP1Triangle(4, 5, 6, 0),
	gsSP1Triangle(7, 6, 5, 0),
	gsSP1Triangle(7, 8, 6, 0),
	gsSP1Triangle(9, 8, 7, 0),
	gsSP1Triangle(9, 10, 8, 0),
	gsSP1Triangle(11, 10, 9, 0),
	gsSP1Triangle(11, 1, 10, 0),
	gsSP1Triangle(1, 11, 2, 0),
	gsSPEndDisplayList(),
};

const Gfx apostrophe_apostrophe_50__mesh_tri_1[] = {
	gsSPVertex(apostrophe_apostrophe_50__mesh_vtx + 12, 6, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(1, 0, 3, 0),
	gsSP1Triangle(1, 3, 4, 0),
	gsSP1Triangle(4, 3, 5, 0),
	gsSPEndDisplayList(),
};

const Gfx apostrophe_apostrophe_50__mesh[] = {
	gsSPDisplayList(mat_apostrophe__18_f3d),
	gsSPDisplayList(apostrophe_apostrophe_50__mesh_tri_0),
	gsSPDisplayList(mat_apostrophe__17_f3d),
	gsSPDisplayList(apostrophe_apostrophe_50__mesh_tri_1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};



