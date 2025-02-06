
#include "headers.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Dialogue {
	const char* TITLE_ERROR   = "Error";
	const char* TITLE_INFO    = "Information";
	const char* TITLE_QUERY   = "Query";
	const char* OPTS_YES_NO   = "Yes|No";
	const char* OPTS_PROCEED  = "Proceed";
	const char* OPTS_CANCEL   = "Cancel";
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define QI(name, expect) { #name, name, ContextFacade::Capability::expect }

const ContextFacade::Capability ContextFacade::warp3DCapabilities[] = {
	QI(W3D_Q_DRAW_POINT, EX_ENUM),
	QI(W3D_Q_DRAW_LINE, EX_ENUM),
	QI(W3D_Q_DRAW_TRIANGLE, EX_ENUM),
	QI(W3D_Q_DRAW_POINT_X, EX_ENUM),
	QI(W3D_Q_DRAW_LINE_X, EX_ENUM),
	QI(W3D_Q_DRAW_LINE_ST, EX_ENUM),
	QI(W3D_Q_DRAW_POLY_ST, EX_ENUM),
	QI(W3D_Q_DRAW_POINT_FX, EX_ENUM),
	QI(W3D_Q_DRAW_LINE_FX, EX_ENUM),

	QI(W3D_Q_TEXMAPPING, EX_ENUM),
	QI(W3D_Q_MIPMAPPING, EX_ENUM),
	QI(W3D_Q_BILINEARFILTER, EX_ENUM),
	QI(W3D_Q_MMFILTER, EX_ENUM),
	QI(W3D_Q_LINEAR_REPEAT, EX_ENUM),
	QI(W3D_Q_LINEAR_CLAMP, EX_ENUM),
	QI(W3D_Q_PERSPECTIVE, EX_ENUM),
	QI(W3D_Q_PERSP_REPEAT, EX_ENUM),
	QI(W3D_Q_PERSP_CLAMP, EX_ENUM),
	QI(W3D_Q_ENV_REPLACE, EX_ENUM),
	QI(W3D_Q_ENV_DECAL, EX_ENUM),
	QI(W3D_Q_ENV_MODULATE, EX_ENUM),
	QI(W3D_Q_ENV_BLEND, EX_ENUM),
	QI(W3D_Q_WRAP_ASYM, EX_ENUM),
	QI(W3D_Q_SPECULAR, EX_ENUM),
	QI(W3D_Q_BLEND_DECAL_FOG, EX_ENUM),
	QI(W3D_Q_TEXMAPPING3D, EX_ENUM),
	QI(W3D_Q_CHROMATEST, EX_ENUM),

	QI(W3D_Q_FLATSHADING, EX_ENUM),
	QI(W3D_Q_GOURAUDSHADING, EX_ENUM),

	QI(W3D_Q_ZBUFFER, EX_ENUM),
	QI(W3D_Q_ZBUFFERUPDATE, EX_ENUM),
	QI(W3D_Q_ZCOMPAREMODES, EX_ENUM),

	QI(W3D_Q_ALPHATEST, EX_ENUM),
	QI(W3D_Q_ALPHATESTMODES, EX_ENUM),

	QI(W3D_Q_BLENDING, EX_ENUM),
	QI(W3D_Q_SRCFACTORS, EX_ENUM),
	QI(W3D_Q_DESTFACTORS, EX_ENUM),
	QI(W3D_Q_ONE_ONE, EX_ENUM),

	QI(W3D_Q_FOGGING, EX_ENUM),
	QI(W3D_Q_LINEAR, EX_ENUM),
	QI(W3D_Q_EXPONENTIAL, EX_ENUM),
	QI(W3D_Q_S_EXPONENTIAL, EX_ENUM),
	QI(W3D_Q_INTERPOLATED, EX_ENUM),

	QI(W3D_Q_ANTIALIASING, EX_ENUM),
	QI(W3D_Q_ANTI_POINT, EX_ENUM),
	QI(W3D_Q_ANTI_LINE, EX_ENUM),
	QI(W3D_Q_ANTI_POLYGON, EX_ENUM),
	QI(W3D_Q_ANTI_FULLSCREEN, EX_ENUM),

	QI(W3D_Q_DITHERING, EX_ENUM),
	QI(W3D_Q_PALETTECONV, EX_ENUM),

	QI(W3D_Q_SCISSOR, EX_ENUM),

	QI(W3D_Q_MAXTEXWIDTH, EX_UINT32),
	QI(W3D_Q_MAXTEXHEIGHT, EX_UINT32),
	QI(W3D_Q_MAXTEXWIDTH_P, EX_UINT32),
	QI(W3D_Q_MAXTEXHEIGHT_P, EX_UINT32),
	QI(W3D_Q_RECTTEXTURES, EX_ENUM),

	QI(W3D_Q_LOGICOP, EX_ENUM),

	QI(W3D_Q_MASKING, EX_ENUM),

	QI(W3D_Q_STENCILBUFFER, EX_ENUM),
	QI(W3D_Q_STENCIL_MASK, EX_ENUM),
	QI(W3D_Q_STENCIL_FUNC, EX_UINT32),
	QI(W3D_Q_STENCIL_SFAIL, EX_UINT32),
	QI(W3D_Q_STENCIL_DPFAIL, EX_UINT32),
	QI(W3D_Q_STENCIL_DPPASS, EX_UINT32),
	QI(W3D_Q_STENCIL_WRMASK, EX_ENUM),

	QI(W3D_Q_DRAW_POINT_TEX, EX_ENUM),
	QI(W3D_Q_DRAW_LINE_TEX, EX_ENUM),

	QI(W3D_Q_CULLFACE, EX_ENUM),

	QI(W3D_Q_NUM_TMU, EX_UINT32),
	QI(W3D_Q_NUM_BLEND, EX_UINT32),
	QI(W3D_Q_ENV_COMBINE, EX_ENUM),
	QI(W3D_Q_ENV_ADD, EX_ENUM),
	QI(W3D_Q_ENV_SUB, EX_ENUM),
	QI(W3D_Q_ENV_CROSSBAR, EX_ENUM),
	QI(W3D_Q_STIPPLE_LINE, EX_ENUM),
	QI(W3D_Q_STIPPLE_POLYGON, EX_ENUM),

};

size_t ContextFacade::numCapabilities = sizeof(ContextFacade::warp3DCapabilities) / sizeof(ContextFacade::Capability);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

