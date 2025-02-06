
#include "headers.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV4ArrayTris(
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

	Log::write("\t%-26s [Array]: ", P_TRIS);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	// 0/3--4
	//  |\  |
	//  | \ |
	//  |  \|
	//  2--1/5

	geometry[0].x = 32;   geometry[0].y = 32;
	geometry[1].x = w-32; geometry[1].y = h-32;
	geometry[2].x = 32;   geometry[2].y = h-32;
	geometry[3].x = 32;   geometry[3].y = 32;
	geometry[4].x = w-32; geometry[4].y = 32;
	geometry[5].x = w-32; geometry[5].y = h-32;

	for (int i=0; i<6; i++) {
		color[i].argb32 = 0xFFCCCCCC;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_TRIANGLES, 0, 6);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a solid light grey rectangle ?",
			testNum, testCount,
			F_ARRAY, P_TRIS
		)) {
			checkedPrimitives |= RES_V4_ARRAY_TRIS_PASSED;
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

void Testing::confirmV4ArrayTriStrip(
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

	Log::write("\t%-26s [Array]: ", P_TRISTRIP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	//  0--2--4
	//  | /| /|
	//  |/ |/ |
	//  1--3--5

	geometry[0].x = 32;     geometry[0].y = 32;
	geometry[1].x = 32;     geometry[1].y = h-32;
	geometry[2].x = 0.5f*w; geometry[2].y = 32;
	geometry[3].x = 0.5f*w; geometry[3].y = h-32;
	geometry[4].x = w-32;   geometry[4].y = 32;
	geometry[5].x = w-32;   geometry[5].y = h-32;

	for (int i=0; i<6; i++) {
		color[i].argb32 = 0xFFCCCCCC;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_TRISTRIP, 0, 6);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a solid light grey rectangle ?",
			testNum, testCount,
			F_ARRAY, P_TRISTRIP
		)) {
			checkedPrimitives |= RES_V4_ARRAY_TRISTRIP_PASSED;
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

void Testing::confirmV4ArrayTriFan(
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

	Log::write("\t%-26s [Array]: ", P_TRIFAN);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	// 1/5--2
	//  |\ /|
	//  | 0 |
	//  |/ \|
	//  4---3

	geometry[0].x = 0.5f*w; geometry[0].y = 0.5f*h;
	geometry[1].x = 32;     geometry[1].y = 32;
	geometry[2].x = w-32;   geometry[2].y = 32;
	geometry[3].x = w-32;   geometry[3].y = h-32;
	geometry[4].x = 32;     geometry[4].y = h-32;
	geometry[5].x = 32;     geometry[5].y = 32;

	for (int i=0; i<6; i++) {
		color[i].argb32 = 0xFFCCCCCC;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_TRIFAN, 0, 6);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see a solid light grey rectangle ?",
			testNum, testCount,
			F_ARRAY, P_TRIFAN
		)) {
			checkedPrimitives |= RES_V4_ARRAY_TRIFAN_PASSED;
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

void Testing::confirmV4ElementTris(
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

	Log::write("\t%-26s [Elems]: ", P_TRIS);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	//  0---1
	//  |\  |
	//  | \ |
	//  |  \|
	//  3---2

	float32 y = (h-64)/3.0f;

	uint32 indexU32[6] = { 0,  2,  3, 0, 1,  2 };
	uint16 indexU16[6] = { 4,  6,  7, 4, 5,  6 };
	uint8  indexU8[6]  = { 8, 10, 11, 8, 9, 10 };

	geometry[0].x  = 32;   geometry[0].y  = 32;
	geometry[1].x  = w-32; geometry[1].y  = 32;
	geometry[2].x  = w-32; geometry[2].y  = y+32;
	geometry[3].x  = 32;   geometry[3].y  = y+32;

	geometry[4].x  = 32;   geometry[4].y  = y+32;
	geometry[5].x  = w-32; geometry[5].y  = y+32;
	geometry[6].x  = w-32; geometry[6].y  = 2.0f*y+32;
	geometry[7].x  = 32;   geometry[7].y  = 2.0f*y+32;

	geometry[8].x  = 32;   geometry[8].y  = 2.0f*y+32;
	geometry[9].x  = w-32; geometry[9].y  = 2.0f*y+32;
	geometry[10].x = w-32; geometry[10].y = h-32;
	geometry[11].x = 32;   geometry[11].y = h-32;

	for (int i=0; i<4; i++) {
		color[i].argb32   = 0xFFCC0000;
		color[i+4].argb32 = 0xFF00CC00;
		color[i+8].argb32 = 0xFF0000CC;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIANGLES, W3D_INDEX_UBYTE, 6,  indexU8);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIANGLES, W3D_INDEX_UWORD, 6, indexU16);
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIANGLES, W3D_INDEX_ULONG, 6, indexU32);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see, from top to bottom, a horizontal red (32-bit index),\n"
			"green (16-bit index) and blue (8-bit index) rectangle ?",
			testNum, testCount,
			F_ELEMS, P_TRIS
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_TRIS_PASSED;
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

void Testing::confirmV4ElementTriStrip(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();

	Vertex::Geometry::FFF* g = geometry;

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_TRISTRIP);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	//  0--1--2
	//  | /| /| Red Strip
	//  |/ |/ | (32-bit indexed)
	//  3--4--5
  //  | /| /| Green Strip
  //  |/ |/ | (16-bit indexed)
  //  6--7--8
  //  | /| /| Blue Strip
  //  |/ |/ | (8-bit indexed)
	//  9-10-11

	float32 yStep = (h-64)/3.0f;
	float32 xStep = (w-64)/2.0f;

	uint32 indexU32[6] = { 0, 3, 1,  4, 2,  5 };
	uint16 indexU16[6] = { 3, 6, 4,  7, 5,  8 };
	uint8  indexU8[6]  = { 6, 9, 7, 10, 8, 11 };

	float32 y=32;
	for (int iy=0; iy<4; iy++) {
		float32 x=32;
		for (int ix=0; ix<3; ix++) {
			g->x = x;
			g->y = y;
			++g;
			x += xStep;
		}
		y += yStep;
	}

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		for (int i=6; i<12; i++) {
			color[i].argb32   = 0xFF0000CC;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRISTRIP, W3D_INDEX_UBYTE, 6,  indexU8);

		for (int i=3; i<9; i++) {
			color[i].argb32   = 0xFF00CC00;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRISTRIP, W3D_INDEX_UWORD, 6, indexU16);

		for (int i=0; i<6; i++) {
			color[i].argb32   = 0xFFCC0000;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRISTRIP, W3D_INDEX_ULONG, 6, indexU32);

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see, from top to bottom, a horizontal red (32-bit index),\n"
			"green (16-bit index) and blue (8-bit index) rectangle ?",
			testNum, testCount,
			F_ELEMS, P_TRISTRIP
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_TRISTRIP_PASSED;
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

void Testing::confirmV4ElementTriFan(
	Vertex::Buffer* vertexBuffer,
	ContextFacade* contextFacade,
	int testNum,
	int testCount)
{
	Vertex::Geometry::FFF* geometry   = vertexBuffer->getGeometryFFF();
	Vertex::Color::U*      color      = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
	W3D_Context*           w3DContext = contextFacade->getW3DContext();

	Vertex::Geometry::FFF* g = geometry;

	int32 w = contextFacade->getWidth();
	int32 h = contextFacade->getHeight();

	Log::write("\t%-26s [Elems]: ", P_TRIFAN);

	contextFacade->setVertexColorArray(color, Vertex::Color::CLR_UARGB, Vertex::Color::CT_NORMAL);
	contextFacade->setVertexGeometryArray(geometry);

	//  Test Vertex configuration
	//
	//  0---1
	//  |\ /| Red Fan
	//  | 2 | (32-bit indexed)
	//  |/ \|
	//  3---4
  //  |\ /| Green Fan
  //  | 5 | (16-bit indexed)
  //  |/ \|
  //  6---7
  //  |\ /| Blue Fan
  //  | 8 | (8-bit indexed)
  //  |/ \|
  //  9--10

	float32 yStep = (h-64)/3.0f;
	float32 y     = 32;
	for (int i=0; i<4; i++) {
		g->x = 32;     g->y = y; g++;
		g->x = w-32;   g->y = y; g++;
		g->x = 0.5f*w; g->y = y+(0.5f*yStep); g++;
		y += yStep;
	}

	uint32 indexU32[6] = { 2, 0, 1,  4, 3, 0 };
	uint16 indexU16[6] = { 5, 3, 4,  7, 6, 3 };
	uint8  indexU8[6]  = { 8, 6, 7, 10, 9, 6 };

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);

		for (int i=6; i<11; i++) {
			color[i].argb32 = 0xFF0000CC;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIFAN, W3D_INDEX_UBYTE, 6,  indexU8);

		for (int i=3; i<8; i++) {
			color[i].argb32 = 0xFF00CC00;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIFAN, W3D_INDEX_UWORD, 6, indexU16);

		for (int i=0; i<5; i++) {
			color[i].argb32 = 0xFFCC0000;
		}
		IWarp3D->W3D_DrawElements(w3DContext, W3D_PRIMITIVE_TRIFAN, W3D_INDEX_ULONG, 6, indexU32);

		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();

		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D array triangle render test result %d/%d\n\n"
			"This is the %s/%s render result.\n\n"
			"Do you see, from top to bottom, a horizontal red (32-bit index),\n"
			"green (16-bit index) and blue (8-bit index) rectangle ?",
			testNum, testCount,
			F_ELEMS, P_TRIFAN
		)) {
			checkedPrimitives |= RES_V4_ELEMENT_TRIFAN_PASSED;
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
