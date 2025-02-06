
#include "headers.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawArray : W3D_PRIMITIVE_LINES user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ArrayLines(
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

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Array]: ", P_LINES);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	register uint32 argb = 0xFFCCCCCC;
	int max = (w>h ? h>>1 : w>>1)-4;
	for (int i = 4; i<max; i+=16) {
		// top edge (tests left to right)
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c;
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c;
		// right edge (tests top to bottom)
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c;
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c;
		// bottom edge (tests right to left)
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c;
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c;
		// left edge (tests bottom to top)
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c;
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_LINES, 0, (g-geometry));
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			F_ARRAY, P_LINES
		)) {
			checkedPrimitives |= RES_V4_ARRAY_LINES_PASSED;
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
//  W3D_DrawArray : W3D_PRIMITIVE_LINELOOP user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ArrayLineLoop(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Array]: ", P_LINELOOP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		int max = (w>h ? h>>1 : w>>1)-4;
		color[3].argb32 = color[2].argb32 = color[1].argb32 = color[0].argb32 = 0xFFCCCCCC;
		for (int i = 4; i<max; i+=16) {
			geometry[0].x = i+0.5f;
			geometry[0].y = i+0.5f;
			geometry[1].x = (w-i)+0.5f;
			geometry[1].y = i+0.5f;
			geometry[2].x = (w-i)+0.5f;
			geometry[2].y = (h-i)+0.5f;
			geometry[3].x = i+0.5f;
			geometry[3].y = (h-i)+0.5f;
			IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_LINELOOP, 0, 4);
		}

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			F_ARRAY, P_LINELOOP
		)) {
			checkedPrimitives |= RES_V4_ARRAY_LINELOOP_PASSED;
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
//  W3D_DrawArray : W3D_PRIMITIVE_LINESTRIP user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ArrayLineStrip(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Array]: ", P_LINESTRIP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		int max = (w>h ? h>>1 : w>>1)-4;
		color[4].argb32 = color[3].argb32 = color[2].argb32 = color[1].argb32 = color[0].argb32 = 0xFFCCCCCC;
		for (int i = 4; i<max; i+=16) {
			geometry[0].x = i+0.5f;
			geometry[0].y = i+0.5f;
			geometry[1].x = (w-i)+0.5f;
			geometry[1].y = i+0.5f;
			geometry[2].x = (w-i)+0.5f;
			geometry[2].y = (h-i)+0.5f;
			geometry[3].x = i+0.5f;
			geometry[3].y = (h-i)+0.5f;
			geometry[4].x = i+0.5f;
			geometry[4].y = i+0.5f;
			IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_LINESTRIP, 0, 5);
		}

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			F_ARRAY, P_LINESTRIP
		)) {
			checkedPrimitives |= RES_V4_ARRAY_LINESTRIP_PASSED;
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
//  W3D_DrawElements : W3D_PRIMITIVE_LINES user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ElementLines(
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

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_LINES);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	int max = (w>h ? h>>1 : w>>1)-4;

	// set of 8-bit indexed entries
	uint8*  indexU8  = vertexBuffer->getIndexU8();
	uint32  index    = 0;
	uint32  vIndex   = 0;
	uint32  argb     = 0xFF0000CC;
	for (int i = 36; i<max; i+=48) {
		// top edge (tests left to right)
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		// right edge (tests top to bottom)
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		// bottom edge (tests right to left)
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		// left edge (tests bottom to top)
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[index++] = vIndex++;
	}
	uint32 count8 = index;

	// set of 16-bit indexed entries
	index            = (index+3) & ~3UL;
	uint16* indexU16 = (uint16*)(indexU8 + index);
	index            = 0;
	argb             = 0xFF00CC00;
	for (int i = 20; i<max; i+=48) {
		// top edge (tests left to right)
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		// right edge (tests top to bottom)
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		// bottom edge (tests right to left)
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		// left edge (tests bottom to top)
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[index++] = vIndex++;
	}
	uint32 count16 = index;

	// set of 32-bit indexed entries
	index            = (index+1) & ~1UL;
	uint32* indexU32 = (uint32*)(indexU16 + index);
	index            = 0;
	argb             = 0xFFCC0000;
	for (int i = 4; i<max; i+=48) {
		// top edge (tests left to right)
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		// right edge (tests top to bottom)
		g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		// bottom edge (tests right to left)
		g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		// left edge (tests bottom to top)
		g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
		g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[index++] = vIndex++;
	}
	uint32 count32 = index;

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINES, W3D_INDEX_UBYTE, count8,  indexU8);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINES, W3D_INDEX_UWORD, count16, indexU16);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINES, W3D_INDEX_ULONG, count32, indexU32);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a nested set of red (32-bit index), green (16-bit index)\n"
			"and blue (8-bit index) wireframe rectangles ?",
			testNum, testCount,
			F_ELEMS, P_LINES
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_LINES_PASSED;
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
//  W3D_DrawElements : W3D_PRIMITIVE_LINELOOP user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ElementLineLoop(
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

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_LINELOOP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	int max = (w>h ? h>>1 : w>>1)-4;

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		// set of 8-bit indexed entries
		uint8*  indexU8  = vertexBuffer->getIndexU8();
		uint32  vIndex   = 0;
		uint32  argb     = 0xFF0000CC;
		for (int i = 36; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[3] = vIndex++;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINELOOP, W3D_INDEX_UBYTE, 4, indexU8);
		}

		// set of 16-bit indexed entries
		uint16* indexU16 = vertexBuffer->getIndexU16();
		argb             = 0xFF00CC00;
		for (int i = 20; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[3] = vIndex++;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINELOOP, W3D_INDEX_UWORD, 4, indexU16);
		}

		// set of 32-bit indexed entries
		uint32* indexU32 = vertexBuffer->getIndexU32();
		argb             = 0xFFCC0000;
		for (int i = 4; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[3] = vIndex++;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINELOOP, W3D_INDEX_ULONG, 4, indexU16);
		}

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s loop render result.\n\n"
			"Do you see a nested set of red (32-bit index), green (16-bit index)\n"
			"and blue (8-bit index) wireframe rectangles ?",
			testNum, testCount,
			F_ELEMS, P_LINELOOP
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_LINELOOP_PASSED;
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
//  W3D_DrawElements : W3D_PRIMITIVE_LINESTRIP user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ElementLineStrip(
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

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_LINESTRIP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	int max = (w>h ? h>>1 : w>>1)-4;

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		// set of 8-bit indexed entries
		uint8*  indexU8  = vertexBuffer->getIndexU8();
		uint32  vIndex   = 0;
		uint32  argb     = 0xFF0000CC;
		for (int i = 36; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU8[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU8[3] = vIndex++;
			indexU8[4] = vIndex-4;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINESTRIP, W3D_INDEX_UBYTE, 5, indexU8);
		}

		// set of 16-bit indexed entries
		uint16* indexU16 = vertexBuffer->getIndexU16();
		argb             = 0xFF00CC00;
		for (int i = 20; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU16[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU16[3] = vIndex++;
			indexU16[4] = vIndex-4;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINESTRIP, W3D_INDEX_UWORD, 5, indexU16);
		}

		// set of 32-bit indexed entries
		uint32* indexU32 = vertexBuffer->getIndexU32();
		argb             = 0xFFCC0000;
		for (int i = 4; i<max; i+=48) {
			g->x = i+0.5f;     g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[0] = vIndex++;
			g->x = (w-i)+0.5f; g->y = i+0.5f;     c->argb32 = argb; ++g; ++c; indexU32[1] = vIndex++;
			g->x = (w-i)+0.5f; g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[2] = vIndex++;
			g->x = i+0.5f;     g->y = (h-i)+0.5f; c->argb32 = argb; ++g; ++c; indexU32[3] = vIndex++;
			indexU32[4] = vIndex-4;
			IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_LINESTRIP, W3D_INDEX_ULONG, 5, indexU16);
		}

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array line render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a nested set of red (32-bit index), green (16-bit index)\n"
			"and blue (8-bit index) wireframe rectangles ?",
			testNum, testCount,
			F_ELEMS, P_LINESTRIP
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_LINESTRIP_PASSED;
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

