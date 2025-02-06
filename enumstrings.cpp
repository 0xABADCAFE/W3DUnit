
#include "headers.hpp"

const char* INVALID_VALUE = "(INVALID_VALUE)";

const char* P96Enums::p96PixelModeNames[] = {
	"RGBFB_NONE",       /* no valid RGB format (should not happen) */
	"RGBFB_CLUT",       /* palette mode, set colors when opening screen using tags or use SetRGB32/LoadRGB32(...) */
	"RGBFB_R8G8B8",     /* TrueColor RGB (8 bit each) */
	"RGBFB_B8G8R8",     /* TrueColor BGR (8 bit each) */
	"RGBFB_R5G6B5PC",   /* HiColor16 (5 bit R, 6 bit G, 5 bit B), format: gggbbbbbrrrrrggg */
	"RGBFB_R5G5B5PC",   /* HiColor15 (5 bit each), format: gggbbbbb0rrrrrgg */
	"RGBFB_A8R8G8B8",   /* 4 Byte TrueColor ARGB (A unused alpha channel) */
	"RGBFB_A8B8G8R8",   /* 4 Byte TrueColor ABGR (A unused alpha channel) */
	"RGBFB_R8G8B8A8",   /* 4 Byte TrueColor RGBA (A unused alpha channel) */
	"RGBFB_B8G8R8A8",   /* 4 Byte TrueColor BGRA (A unused alpha channel) */
	"RGBFB_R5G6B5",     /* HiColor16 (5 bit R, 6 bit G, 5 bit B), format: rrrrrggggggbbbbb */
	"RGBFB_R5G5B5",     /* HiColor15 (5 bit each), format: 0rrrrrgggggbbbbb */
	"RGBFB_B5G6R5PC",   /* HiColor16 (5 bit R, 6 bit G, 5 bit B), format: gggrrrrrbbbbbggg */
	"RGBFB_B5G5R5PC",   /* HiColor15 (5 bit each), format: gggrrrrr0bbbbbbgg */

	// these are device specific formats
	"RGBFB_YUV422CGX",
	"RGBFB_YUV411",
	"RGBFB_YUV422PA",
	"RGBFB_YUV422",
	"RGBFB_YUV422PC",
	"RGBFB_YUV420P",
	"RGBFB_YUV410P",
	"RGBFB_ALPHA8",
	""
};

const char* P96Enums::getP96PixelFormatName(int32 fmt)
{
	if (fmt < RGBFB_NONE || fmt >= RGBFB_MaxFormats) {
		return "(Unknown format)";
	}
	return p96PixelModeNames[fmt];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const char* W3DEnums::warp3DChipNames[] = {
	"None",
	"Unknown",
	"Virge",
	"Permedia2",
	"Voodoo 1",
	"Obsolete #1 (Was: 3Dfx Voodoo 3/Compatible [Litte endian mode])",
	"Obsolere #2 (Was: 3Dfx Voodoo 3/Compatible [Big endian mode])",
	"Radeon",
	"Avenger (Voodoo 3)",
	"Napalm (Voodoo 4/5)",
	"Radeon R200",
	"Radeon R300"
};

const char* W3DEnums::getW3DChipType(uint32 val)
{
	if (val>W3D_CHIP_RADEON_R300) {
		val = W3D_CHIP_UNKNOWN;
	}
	return warp3DChipNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* W3DEnums::warp3DStatusItems[] = {
	"W3D_SUCCESS",             //   0 /* success */
	"W3D_BUSY",                //  -1 /* graphics hardware is busy */
	"W3D_ILLEGALINPUT",        //  -2 /* failure, illegal input */
	"W3D_NOMEMORY",            //  -3 /* no memory available */
	"W3D_NODRIVER",            //  -4 /* no hardware driver available */
	"W3D_NOTEXTURE",           //  -5 /* texture is missing */
	"W3D_TEXNOTRESIDENT",      //  -6 /* texture not resident */
	"W3D_NOMIPMAPS",           //  -7 /* mipmaps are not supported by this texture object */
	"W3D_NOGFXMEM",            //  -8 /* no graphics memory available */
	"W3D_NOTVISIBLE",          //  -9 /* drawing area not visible/ bitmap swapped out */
	"W3D_UNSUPPORTEDFILTER",   // -10 /* unsupported filter */
	"W3D_UNSUPPORTEDTEXENV",   // -11 /* unsupported filter */
	"W3D_UNSUPPORTEDWRAPMODE", // -12 /* unsupported wrap mode */
	"W3D_UNSUPPORTEDZCMP",     // -13 /* unsupported Z compare mode */
	"W3D_UNSUPPORTEDATEST",    // -14 /* unsupported alpha test */
	"W3D_UNSUPPORTEDBLEND",    // -15 /* unsupported blending function */
	"W3D_UNSUPPORTEDFOG",      // -16 /* unsupported fog mode */
	"W3D_UNSUPPORTEDSTATE",    // -17 /* can't enable/disable state */
	"W3D_UNSUPPORTEDFMT",      // -18 /* unsupported bitmap format */
	"W3D_UNSUPPORTEDTEXSIZE",  // -19 /* unsupported texture border size */
	"W3D_UNSUPPORTEDLOGICOP",  // -20 /* unsupported logical operation */
	"W3D_UNSUPPORTEDSTTEST",   // -21 /* unsupported stencil test */
	"W3D_ILLEGALBITMAP",       // -22 /* illegal bitmap */
	"W3D_NOZBUFFER",           // -23 /* Z buffer is missing/unavailable */
	"W3D_NOPALETTE",           // -24 /* Palette missing for chunky textures */
	"W3D_MASKNOTSUPPORTED",    // -25 /* color/index masking not supported */
	"W3D_NOSTENCILBUFFER",     // -26 /* Stencil buffer is missing/unavailable */
	"W3D_QUEUEFAILED",         // -27 /* The request can not be queued */
	"W3D_UNSUPPORTEDTEXFMT",   // -28 /* Texformat unsupported */
	"W3D_WARNING",             // -29 /* Parital success */
	"W3D_UNSUPPORTED"          // -30 /* Requested feature is unsupported */
};

const char* W3DEnums::getW3DStatusName(uint32 retVal)
{
	int32 status = ((int32)retVal);
	if (status>0 || status < W3D_UNSUPPORTED) {
		return "(UNKNOWN_STATUS)";
	}
	status = -status;
	return warp3DStatusItems[status];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* W3DEnums::warp3DStateStatusEnumItems[] = {
	INVALID_VALUE, // 0
	"W3D_ENABLED", // 1
	"W3D_DISABLED" // 2
};

const char* W3DEnums::getW3DStateStatusName(uint32 status)
{
	if (status>W3D_DISABLED) {
		status = 0;
	}
	return warp3DStateStatusEnumItems[status];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* W3DEnums::warp3DQueryResultEnumItems[] = {
	"W3D_FULLY_SUPPORTED",     // 3 /* completely supported */
	"W3D_PARTIALLY_SUPPORTED", // 4 /* partially supported */
	"W3D_NOT_SUPPORTED"        // 5 /* not supported */
};

const char* W3DEnums::getW3DQueryEnumName(uint32 val)
{
	if (val<W3D_FULLY_SUPPORTED || val>W3D_NOT_SUPPORTED) {
		return "(UNKNOWN_SUPPORT_ENUM)";
	}
	return warp3DQueryResultEnumItems[val-W3D_FULLY_SUPPORTED];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* W3DEnums::warp3DStateFlagNames[] = {
	INVALID_VALUE,
	"W3D_AUTOTEXMANAGEMENT",   // (1<<1)  /* automatic texture management */
	"W3D_SYNCHRON",            // (1<<2)  /* wait, until HW is idle */
	"W3D_INDIRECT",            // (1<<3)  /* drawing is queued until flushed */
	"W3D_GLOBALTEXENV",        // (1<<4)  /* SetTexEnv is global */
	"W3D_DOUBLEHEIGHT",        // (1<<5)  /* Drawing area is double height */
	"W3D_FAST",                // (1<<6)  /* Allow Warp3D to modify passed Triangles/Points/Lines */
	"W3D_AUTOCLIP",            // (1<<7)  /* clip to screen region */
	"W3D_TEXMAPPING",          // (1<<8)  /* texmapping state */
	"W3D_PERSPECTIVE",         // (1<<9)  /* perspective correction state */
	"W3D_GOURAUD",             // (1<<10) /* gouraud/flat shading */
	"W3D_ZBUFFER",             // (1<<11) /* Z-Buffer state */
	"W3D_ZBUFFERUPDATE",       // (1<<12) /* Z-Buffer update state */
	"W3D_BLENDING",            // (1<<13) /* Alpha blending state */
	"W3D_FOGGING",             // (1<<14) /* Fogging state */
	"W3D_ANTI_POINT",          // (1<<15) /* Point antialiasing state */
	"W3D_ANTI_LINE",           // (1<<16) /* Line antialiasing state */
	"W3D_ANTI_POLYGON",        // (1<<17) /* Polygon antialiasing state */
	"W3D_ANTI_FULLSCREEN",     // (1<<18) /* Fullscreen antialiasing state */
	"W3D_DITHERING",           // (1<<19) /* dithering state */
	"W3D_LOGICOP",             // (1<<20) /* logic operations */
	"W3D_STENCILBUFFER",       // (1<<21) /* stencil buffer/stencil test */
	"W3D_ALPHATEST",           // (1<<22) /* alpha test */
	"W3D_SPECULAR",            // (1<<23) /* Specular lighting */
	"W3D_TEXMAPPING3D",        // (1<<24) /* 3d textures */
	"W3D_SCISSOR",             // (1<<25) /* Scissor test enable */
	"W3D_CHROMATEST",          // (1<<26) /* Chroma test enable */
	"W3D_CULLFACE",            // (1<<27) /* Backface culling enable */
	"W3D_MULTITEXTURE",        // (1<<28) /* Enable multitexturing and separate blend functions */
	"W3D_FOG_COORD",           // (1<<29) /* Use separate fog coord array instead of first texture's w coordinates */
	"W3D_LINE_STIPPLE",        // (1<<30)
	"W3D_POLYGON_STIPPLE"      // (1<<31)
};

const char* W3DEnums::getW3DStateBitName(uint32 val)
{
	if (val > W3D_POLYGON_STIPPLE) {
		val = 0;
	}
	return warp3DStateFlagNames[val];
}

const char* W3DEnums::getW3DStateFlagName(uint32 val)
{
	if (!val) {
		return INVALID_VALUE;
	}
	int i=0;
	while ((val&1)==0 && i<31) {
		val>>=1;
		++i;
	}
	return warp3DStateFlagNames[i];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* W3DEnums::warp3DBlendModeNames[] = {
	INVALID_VALUE,
	"W3D_ZERO",                     //  1 /* source + dest */
	"W3D_ONE",                      //  2 /* source + dest */
	"W3D_SRC_COLOR",                //  3 /* dest only */
	"W3D_DST_COLOR",                //  4 /* source only */
	"W3D_ONE_MINUS_SRC_COLOR",      //  5 /* dest only */
	"W3D_ONE_MINUS_DST_COLOR",      //  6 /* source only */
	"W3D_SRC_ALPHA",                //  7 /* source + dest */
	"W3D_ONE_MINUS_SRC_ALPHA",      //  8 /* source + dest */
	"W3D_DST_ALPHA",                //  9 /* source + dest */
	"W3D_ONE_MINUS_DST_ALPHA",      // 10 /* source + dest */
	"W3D_SRC_ALPHA_SATURATE",       // 11 /* source only */
	"W3D_CONSTANT_COLOR",           // 12
	"W3D_ONE_MINUS_CONSTANT_COLOR", // 13
	"W3D_CONSTANT_ALPHA",           // 14
	"W3D_ONE_MINUS_CONSTANT_ALPHA"  // 15
};

const char* W3DEnums::getW3DBlendModeName(uint32 val)
{
	if (val>W3D_ONE_MINUS_CONSTANT_ALPHA) {
		val = 0;
	}
	return warp3DBlendModeNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/* texture filter. Only W3D_NEAREST and W3D_LINEAR can be used for
		magnification filters! */

const char* W3DEnums::warp3DTextureFilterNames[] = {
	INVALID_VALUE,
	"W3D_NEAREST",             // 1 /* no mipmapping, no filtering */
	"W3D_LINEAR",              // 2 /* no mipmapping, bilinear filtering */
	"W3D_NEAREST_MIP_NEAREST", // 3 /* mipmapping, no filtering */
	"W3D_NEAREST_MIP_LINEAR",  // 4 /* mipmapping, bilinear filtering */
	"W3D_LINEAR_MIP_NEAREST",  // 5 /* filtered mipmapping, no filtering */
	"W3D_LINEAR_MIP_LINEAR"    // 6 /* mipmapping, trilinear filtering */
};

const char* W3DEnums::getW3DTextureFilterName(uint32 val)
{
	if (val>W3D_LINEAR_MIP_LINEAR) {
		val = 0;
	}
	return warp3DTextureFilterNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* fog modes */

const char* W3DEnums::warp3DFogModeNames[] = {
	INVALID_VALUE,
	"W3D_FOG_LINEAR",      // 1 /* linear fogging */
	"W3D_FOG_EXP",         // 2 /* exponential fogging */
	"W3D_FOG_EXP_2",       // 3 /* square exponential fogging */
	"W3D_FOG_INTERPOLATED" // 4 /* interpolated fogging */
};


const char* W3DEnums::getW3DFogModeName(uint32 val)
{
	if (val>W3D_FOG_INTERPOLATED) {
		val = 0;
	}
	return warp3DFogModeNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* texture environment parameters */

const char* W3DEnums::warp3DTextureEnvNames[] = {
	INVALID_VALUE,
	"W3D_REPLACE",   // 1 /* unlit texturing */
	"W3D_DECAL",     // 2 /* RGB: same as W3D_REPLACE RGBA: use alpha to blend texture with primitive (lit-texturing) */
	"W3D_MODULATE",  // 3 /* lit-texturing by modulation */
	"W3D_BLEND",     // 4 /* blend with environment color */
	"W3D_ADD",       // 5 /* Add texture and other color (either other texture unit, or fragment color) */
	"W3D_SUB",       // 6 /* Subtract texture and other color) */
	"W3D_OFF",       // 7 /* Turn off a texture unit */
};

const char* W3DEnums::getW3DTextureEnvName(uint32 val)
{
	if (val>W3D_OFF) {
		val = 0;
	}
	return warp3DTextureEnvNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* texture environment parameters */
	/* texture wrapping parameters */

const char* W3DEnums::warp3DTextureWrapNames[] = {
	INVALID_VALUE,
	"W3D_REPEAT",  // 1 /* texture is repeated */
	"W3D_CLAMP"    // 2 /* texture is clamped */
};

const char* W3DEnums::getW3DTextureWrapName(uint32 val)
{
	if (val>W3D_CLAMP) {
		val = 0;
	}
	return warp3DTextureWrapNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/* alpha test compare modes */

const char* W3DEnums::warp3DAlphaTestNames[] = {
	INVALID_VALUE,
	"W3D_A_NEVER",    // 1 /* discard incoming pixel */
	"W3D_A_LESS",     // 2 /* draw, if value < refvalue */
	"W3D_A_GEQUAL",   // 3 /* draw, if value >= refvalue */
	"W3D_A_LEQUAL",   // 4 /* draw, if value <= refvalue */
	"W3D_A_GREATER",  // 5 /* draw, if value > refvalue */
	"W3D_A_NOTEQUAL", // 6 /* draw, if value != refvalue */
	"W3D_A_EQUAL",    // 7 /* draw, if value == refvalue */
	"W3D_A_ALWAYS"    // 8 /* always draw */
};

const char* W3DEnums::getW3DAlphaTestName(uint32 val)
{
	if (val>W3D_A_ALWAYS) {
		val = 0;
	}
	return warp3DAlphaTestNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* Z buffer compare modes */

const char* W3DEnums::warp3DZTestNames[] = {
	INVALID_VALUE,
	"W3D_Z_NEVER",    // 1 /* discard incoming pixel */
	"W3D_Z_LESS",     // 2 /* draw, if value < Z(Z_Buffer) */
	"W3D_Z_GEQUAL",   // 3 /* draw, if value >= Z(Z_Buffer) */
	"W3D_Z_LEQUAL",   // 4 /* draw, if value <= Z(Z_Buffer) */
	"W3D_Z_GREATER",  // 5 /* draw, if value > Z(Z_Buffer) */
	"W3D_Z_NOTEQUAL", // 6 /* draw, if value != Z(Z_Buffer) */
	"W3D_Z_EQUAL",    // 7 /* draw, if value == Z(Z_Buffer) */
	"W3D_Z_ALWAYS"    // 8 /* always draw */
};

const char* W3DEnums::getW3DZTestName(uint32 val)
{
	if (val>W3D_Z_ALWAYS) {
		val = 0;
	}
	return warp3DZTestNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* logical operation modes */

const char* W3DEnums::warp3DLogicOpNames[] = {
	INVALID_VALUE,
	"W3D_LO_CLEAR",         //  1 /* dest = 0 */
	"W3D_LO_AND",           //  2 /* dest = source & dest */
	"W3D_LO_AND_REVERSE",   //  3 /* dest = source & !dest */
	"W3D_LO_COPY",          //  4 /* dest = source */
	"W3D_LO_AND_INVERTED",  //  5 /* dest = !source & dest */
	"W3D_LO_NOOP",          //  6 /* dest = dest */
	"W3D_LO_XOR",           //  7 /* dest = source ^ dest */
	"W3D_LO_OR",            //  8 /* dest = source | dest */
	"W3D_LO_NOR",           //  9 /* dest = !(source | dest) */
	"W3D_LO_EQUIV",         // 10 /* dest = !(source ^ dest) */
	"W3D_LO_INVERT",        // 11 /* dest = !dest */
	"W3D_LO_OR_REVERSE",    // 12 /* dest = source | !dest */
	"W3D_LO_COPY_INVERTED", // 13 /* dest = !source */
	"W3D_LO_OR_INVERTED",   // 14 /* dest = !source | dest */
	"W3D_LO_NAND",          // 15 /* dest = !(source & dest) */
	"W3D_LO_SET"            // 16 /* dest = 1 */
};


const char* W3DEnums::getW3DLogicOpName(uint32 val)
{
	if (val>W3D_LO_SET) {
		val = 0;
	}
	return warp3DLogicOpNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* stencil test functions */

const char* W3DEnums::warp3DStencilTestNames[] = {
	INVALID_VALUE,
	"W3D_ST_NEVER",   // 1 /* don't draw pixel */
	"W3D_ST_ALWAYS",  // 2 /* draw always */
	"W3D_ST_LESS",    // 3 /* draw, if refvalue < ST */
	"W3D_ST_LEQUAL",  // 4 /* draw, if refvalue <= ST */
	"W3D_ST_EQUAL",   // 5 /* draw, if refvalue == ST */
	"W3D_ST_GEQUAL",  // 6 /* draw, if refvalue >= ST */
	"W3D_ST_GREATER", // 7 /* draw, if refvalue > ST */
	"W3D_ST_NOTEQUAL" // 8 /* draw, if refvalue != ST */
};
	/* Masks for query */
/*
	#define W3D_ST_NEVER_BIT		(1L << W3D_ST_NEVER)
	#define W3D_ST_ALWAYS_BIT		(1L << W3D_ST_ALWAYS)
	#define W3D_ST_LESS_BIT			(1L << W3D_ST_LESS)
	#define W3D_ST_LEQUAL_BIT		(1L << W3D_ST_LEQUAL)
	#define W3D_ST_EQUAL_BIT		(1L << W3D_ST_EQUAL)
	#define W3D_ST_GEQUAL_BIT		(1L << W3D_ST_GEQUAL)
	#define W3D_ST_GREATER_BIT		(1L << W3D_ST_GREATER)
	#define W3D_ST_NOTEQUAL_BIT		(1L << W3D_ST_NOTEQUAL)
*/

const char* W3DEnums::getW3DStencilTestName(uint32 val)
{
	if (val>W3D_ST_NOTEQUAL) {
		val = 0;
	}
	return warp3DStencilTestNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* stencil test operations */

const char* W3DEnums::warp3DStencilUpdateNames[] = {
	INVALID_VALUE,
	"W3D_ST_KEEP",      // 1 /* keep stencil buffer value */
	"W3D_ST_ZERO",      // 2 /* clear stencil buffer value */
	"W3D_ST_REPLACE",   // 3 /* replace by reference value */
	"W3D_ST_INCR",      // 4 /* increment */
	"W3D_ST_DECR",      // 5 /* decrement */
	"W3D_ST_INVERT",    // 6 /* invert bitwise */
	"W3D_ST_INCR_WRAP", // 7 /* increment with wrap */
	"W3D_ST_DECR_WRAP"  // 8 /* decrement with wrap */
};
	/* Masks for query */
/*
	#define W3D_ST_KEEP_BIT			(1L << W3D_ST_KEEP)
	#define W3D_ST_ZERO_BIT			(1L << W3D_ST_ZERO)
	#define W3D_ST_REPLACE_BIT		(1L << W3D_ST_REPLACE)
	#define W3D_ST_INCR_BIT			(1L << W3D_ST_INCR)
	#define W3D_ST_DECR_BIT			(1L << W3D_ST_DECR)
	#define W3D_ST_INVERT_BIT		(1L << W3D_ST_INVERT)
	#define W3D_ST_INCR_WRAP_BIT	(1L << W3D_ST_INCR_WRAP)
	#define W3D_ST_DECR_WRAP_BIT	(1L << W3D_ST_DECR_WRAP)
*/

const char* W3DEnums::getW3DStencilUpdateName(uint32 val)
{
	if (val>W3D_ST_DECR_WRAP) {
		val = 0;
	}
	return warp3DStencilUpdateNames[val];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/* chroma test modes */

const char* W3DEnums::warp3DChromaTestNames[] = {
	INVALID_VALUE,
	"W3D_CHROMATEST_NONE",      // 1  /* No chroma test */
	"W3D_CHROMATEST_INCLUSIVE", // 2  /* texels in the range pass the test */
	"W3D_CHROMATEST_EXCLUSIVE", // 3  /* texels in the range are rejected */
};


const char* W3DEnums::getW3DChromaTestName(uint32 val)
{
	if (val>W3D_CHROMATEST_EXCLUSIVE) {
		val = 0;
	}
	return warp3DChromaTestNames[val];
}
