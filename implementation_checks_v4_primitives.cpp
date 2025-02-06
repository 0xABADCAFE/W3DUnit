
#include "headers.hpp"

const char* Testing::F_ARRAY     = "W3D_DrawArray()";
const char* Testing::F_ELEMS     = "W3D_DrawElements()";
const char* Testing::P_POINTS    = "W3D_PRIMITIVE_POINTS";
const char* Testing::P_LINES     = "W3D_PRIMITIVE_LINES";
const char* Testing::P_LINELOOP  = "W3D_PRIMITIVE_LINELOOP";
const char* Testing::P_LINESTRIP = "W3D_PRIMITIVE_LINESTRIP";
const char* Testing::P_TRIS      = "W3D_PRIMITIVE_TRIANGLES";
const char* Testing::P_TRISTRIP  = "W3D_PRIMITIVE_TRISTRIP";
const char* Testing::P_TRIFAN    = "W3D_PRIMITIVE_TRIFAN";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4Points(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Point Render Tests");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Point Render Tests\n\n"
		"W3DUnit will test if point rendering using Warp3D Array/Element drawing methods\n"
		"is supported in the current driver.\n"
		"There are two point rendering methods that will be tested.\n"
		"Skipping these tests will tell W3DUnit to assume that both rendering methods\n"
		"are fully and correctly supported."
	)) {
		Log::write("\nSkipped all point render tests\n");
		checkedPrimitives |= RES_V4_ARRAY_POINTS_PASSED|RES_V4_ELEMENT_POINTS_PASSED;
		return;
	}
	Log::write("\nPerforming point render tests\n");
	setMinimalRenderState(contextFacade);
	setStateLogged(contextFacade->getW3DContext(), W3D_GOURAUD, W3D_ENABLE);
	confirmV4ArrayPoints(vertexBuffer,   contextFacade, 1, 2);
	confirmV4ElementPoints(vertexBuffer, contextFacade, 2, 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4Lines(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Line Render Tests");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Line Render Tests\n\n"
		"W3DUnit will test if line rendering using Warp3D Array/Element drawing methods\n"
		"is supported in the current driver.\n"
		"There are six line rendering methods that will be tested.\n"
		"Skipping these tests will tell W3DUnit to assume that all six line rendering\n"
		"methods are fully and correctly supported."
	)) {
		Log::write("\nSkipped all line render tests\n");
		checkedPrimitives |= RES_V4_ARRAY_LINES_PASSED|RES_V4_ELEMENT_LINES_PASSED|
										     RES_V4_ARRAY_LINELOOP_PASSED|RES_V4_ELEMENT_LINELOOP_PASSED|
										     RES_V4_ARRAY_LINESTRIP_PASSED|RES_V4_ELEMENT_LINESTRIP_PASSED;
		return;
	}

	Log::write("\nPerforming line render tests\n");
	setMinimalRenderState(contextFacade);
	setStateLogged(contextFacade->getW3DContext(), W3D_GOURAUD, W3D_ENABLE);
	confirmV4ArrayLines(vertexBuffer,       contextFacade, 1, 6);
	confirmV4ElementLines(vertexBuffer,     contextFacade, 2, 6);
	confirmV4ArrayLineLoop(vertexBuffer,    contextFacade, 3, 6);
	confirmV4ElementLineLoop(vertexBuffer,  contextFacade, 4, 6);
	confirmV4ArrayLineStrip(vertexBuffer,   contextFacade, 5, 6);
	confirmV4ElementLineStrip(vertexBuffer, contextFacade, 6, 6);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4Tris(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Triangle Render Tests");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Triangle Render Tests\n\n"
		"W3DUnit will test if triangle rendering using Warp3D Array/Element drawing methods\n"
		"is supported in the current driver.\n"
		"There are six triangle rendering methods that will be tested.\n"
		"Skipping these tests will tell W3DUnit to assume that all six triangle rendering\n"
		"methods are fully and correctly supported."
	)) {
		Log::write("\nSkipped all triangle render tests\n");
		checkedPrimitives |= RES_V4_ARRAY_TRIS_PASSED|RES_V4_ELEMENT_TRIS_PASSED|
										     RES_V4_ARRAY_TRIFAN_PASSED|RES_V4_ELEMENT_TRIFAN_PASSED|
										     RES_V4_ARRAY_TRISTRIP_PASSED|RES_V4_ELEMENT_TRISTRIP_PASSED;
		return;
	}
	Log::write("\nPerforming triangle render tests\n");
	setMinimalRenderState(contextFacade);
	setStateLogged(contextFacade->getW3DContext(), W3D_GOURAUD, W3D_ENABLE);
	confirmV4ArrayTris(vertexBuffer,       contextFacade, 1, 6);
	confirmV4ElementTris(vertexBuffer,     contextFacade, 2, 6);
	confirmV4ArrayTriStrip(vertexBuffer,   contextFacade, 3, 6);
	confirmV4ElementTriStrip(vertexBuffer, contextFacade, 4, 6);
	confirmV4ArrayTriFan(vertexBuffer,     contextFacade, 5, 6);
	confirmV4ElementTriFan(vertexBuffer,   contextFacade, 6, 6);
}

