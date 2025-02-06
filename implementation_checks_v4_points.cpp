
#include "headers.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawArray : W3D_PRIMITIVE_POINTS user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ArrayPoints(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();
	Vertex::Geometry::FFF* g = geometry;
	Vertex::Color::U*      c = color;
	int32                  w = contextFacade->getWidth();
	int32                  h = contextFacade->getHeight();

	Log::write("\t%-26s [Array]: ", P_POINTS);

	for (int32 y=4; y<h-4; y+=32) {
		for (int32 x=4; x<w-4; x+=32) {
			g->x   = x+0.5f;
			g->y   = y+0.5f;
 			c->argb32 = 0xFFCCCCCC;
			g++;
			c++;
		}
	}

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_POINTS, 0, (g-geometry));
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array point render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a regular grid of light grey pixels against a black background?",
			testNum, testCount,
			F_ARRAY, P_POINTS
		)) {
			checkedPrimitives |= RES_V4_ARRAY_POINTS_PASSED;
			Log::write("%s\n", TEST_PASS);
		}
		else {
			Log::write("%s\n", TEST_FAIL);
		}
	}
	else {
		Log::write("failed to lock hardware\n");
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawElements : W3D_PRIMITIVE_POINTS user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ElementPoints(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount
)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();

	Vertex::Geometry::FFF*     g = geometry;
	Vertex::Color::U*          c = color;

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_POINTS);

	// set of 8-bit indexed entries
	uint8* indexU8 = vertexBuffer->getIndexU8();
	uint32 index   = 0;
	uint32 vIndex  = 0;
	uint32 argb    = 0xFF0000FF;
	for (int32 y=68; y<h-4; y+=96) {
		for (int32 x=4; x<w-4; x+=32) {
			g->x      = x+0.5f;
			g->y      = y+0.5f;
 			c->argb32 = argb;
			++g;
			++c;
			indexU8[index++] = vIndex++;
		}
	}
	uint32 count8 = index;

	// set of 16-bit indexed entries
	index            = (index+3) & ~3UL;
	uint16* indexU16 = (uint16*)(indexU8 + index);
	index            = 0;
	argb             = 0xFF00CC00;
	for (int32 y=36; y<h-4; y+=96) {
		for (int32 x=4; x<w-4; x+=32) {
			g->x      = x+0.5f;
			g->y      = y+0.5f;
 			c->argb32 = argb;
			++g;
			++c;
			indexU16[index++] = vIndex++;
		}
	}
	uint32 count16 = index;

	// set of 32-bit indexed entries
	index            = (index+1) & ~1UL;
	uint32* indexU32 = (uint32*)(indexU16 + index);
	index            = 0;
	argb             = 0xFFFF0000;
	for (int32 y=4; y<h-4; y+=96) {
		for (int32 x=4; x<w-4; x+=32) {
			g->x      = x+0.5f;
			g->y      = y+0.5f;
 			c->argb32 = argb;
			++g;
			++c;
			indexU32[index++] = vIndex++;
		}
	}
	uint32 count32 = index;

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_POINTS, W3D_INDEX_UBYTE, count8,  indexU8);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_POINTS, W3D_INDEX_UWORD, count16, indexU16);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_POINTS, W3D_INDEX_ULONG, count32, indexU32);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array point render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a regular grid of pixels arranged as rows of red (32-bit index),\n"
			"green (16-bit index) and blue (8-bit index), against a black background?\n"
			"(Note that no more than 256 distinct blue points will be rendered due to\n"
			"the limit imposed by the 8-bit index size, this may cut short blue rows)",
			testNum, testCount,
			F_ELEMS, P_POINTS
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_POINTS_PASSED;
			Log::write("%s\n", TEST_PASS);
		}
		else {
			Log::write("%s\n", TEST_FAIL);
		}
	}
	else {
		Log::write("failed to lock hardware\n");
	}
}
