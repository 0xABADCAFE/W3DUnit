
#ifndef _W3DTEST_TEST_HPP_
#	define _W3DTEST_TEST_HPP_

namespace Dialogue {
	extern const char* OPTS_RUN_SKIP;
	extern const char* OPTS_YES_NO_OTHER;
};

class Testing {

	public:
		enum {
			RES_FAILED = 0,
		};
		#include "test_vertex_result_enum.hpp"
		#include "test_primitives_result_enum.hpp"
		#include "test_misc_result_enum.hpp"
		#include "test_z_result_enum.hpp"

		enum {
			CHECK_VERTEX_FORMATS,
			CHECK_COLOR_FORMATS,
			MAX_TESTS
		};

		//typedef void (*Test)(Vertex::Buffer* v, ContextFacade* f);

		static void runImplementationChecks(Vertex::Buffer* v, ContextFacade* f);

	private:
		enum {
			_RES_VERTEX_GEOMETRY_OFFSET = 0,
			_RES_VERTEX_COLOR_OFFSET    = 4
		};

		static const char* HWLOCK_FAIL;
		static const char* TEST_PASS;
		static const char* TEST_FAIL;
		static const char* P_POINTS;
		static const char* P_LINES;
		static const char* P_LINELOOP;
		static const char* P_LINESTRIP;
		static const char* P_TRIS;
		static const char* P_TRISTRIP;
		static const char* P_TRIFAN;
		static const char* F_ARRAY;
		static const char* F_ELEMS;

		enum {
			RESULT_YES     = 1,
			RESULT_OTHER   = 2,
			RESULT_NO      = 0
		};


		static void confirm2DFills(Vertex::Buffer* v, ContextFacade* f);

		static void confirmV3Points(Vertex::Buffer* v, ContextFacade* f);
		static void confirmV3Lines(Vertex::Buffer* v, ContextFacade* f);
		static void confirmV3Tris(Vertex::Buffer* v, ContextFacade* f);

		static void confirmV4Points(Vertex::Buffer* v, ContextFacade* f);
		static void confirmV4Lines(Vertex::Buffer* v, ContextFacade* f);
		static void confirmV4Tris(Vertex::Buffer* v, ContextFacade* f);

		static void confirmShadeModes(Vertex::Buffer* v, ContextFacade* f);
		static void confirmZBuffer(Vertex::Buffer* v, ContextFacade* f);

		static void confirmVertexGeometryFormats(Vertex::Buffer* v, ContextFacade* f);
		static void confirmVertexColorFormats(Vertex::Buffer* v, ContextFacade* f);
		static void confirmVertexTextureFormats(Vertex::Buffer* v, ContextFacade* f);


		static void confirmV4ArrayPoints(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayLines(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayLineLoop(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayLineStrip(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayTris(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayTriStrip(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ArrayTriFan(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementPoints(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementLines(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementLineLoop(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementLineStrip(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementTris(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementTriStrip(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);
		static void confirmV4ElementTriFan(Vertex::Buffer* v, ContextFacade* f, int testNum, int testCount);


		static void confirmW3DDrawLine(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawLineStrip(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawLineLoop(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriangle(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriangleV(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriFan(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriFanV(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriStrip(ContextFacade* f, int testNum, int testCount);
		static void confirmW3DDrawTriStripV(ContextFacade* f, int testNum, int testCount);


		static void setMinimalRenderState(ContextFacade* f);

		static uint32 checkedVertexLayout;
		static uint32 checkedPrimitives;
		static uint32 checkedZOperations;
		static uint32 checkedStencilOperations;
		static uint32 checkedTexelFormats;
		static uint32 checkedMisc;

		static uint32 setStateLogged(W3D_Context*, uint32 property, uint32 state);

};

#define NRGBA(x)        { x, x, x, 1.0f }
#define NRGBA3(r, g, b) { r, g, b, 1.0f }
#define NRGB            { 0.0f, 0.0f, 0.0f }
#define NVTX(x)         { 0.0f, 0.0f, 0.0,  0.0f, 0.0f, 0.0f, 0.0f,  NRGBA(x), NRGB,  0.0 }
#define NVTX3(r,g,b)    { 0.0f, 0.0f, 0.0,  0.0f, 0.0f, 0.0f, 0.0f,  NRGBA3(r, g, b), NRGB,  0.0 }


#endif
