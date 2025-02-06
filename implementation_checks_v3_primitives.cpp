
#include "headers.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawPoint user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV3Points(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	const char* OLD_FUNC_POINT = "W3D_DrawPoint()";

	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Legacy Point Render Test");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Legacy Point Render Test\n\n"
		"W3DUnit will test if point rendering using the %s method is supported.\n"
		"If your driver supports this call you should see a grid of light grey pixels against a\n"
		"black background.\n"
		"Skipping this test will tell W3DUnit to assume that legacy point rendering\n"
		"is fully supported.",
		OLD_FUNC_POINT
	)) {
		Log::write("\nSkipped legacy point render tests\n");
		checkedPrimitives |= RES_V3_POINT_PASSED;
		return;
	}
	Log::write("\nPerforming legacy point render tests\n");
	W3D_Point    point      = { NVTX(0.8f), 0, 1.0f };
	int32        w          = contextFacade->getWidth();
	int32        h          = contextFacade->getHeight();
	W3D_Context* w3DContext = contextFacade->getW3DContext();

	setMinimalRenderState(contextFacade);
	setStateLogged(w3DContext, W3D_GOURAUD, W3D_ENABLE);
	Log::write("\t%-26s : ", OLD_FUNC_POINT);
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
		for (int32 y=4; y<h-4; y+=32) {
			for (int32 x=4; x<w-4; x+=32) {
				// damn this function must be bloody slow compared to
				// just writing a point in software ;)
				point.v1.x = x+0.5;
				point.v1.y = y+0.5;
				IWarp3D->W3D_DrawPoint(w3DContext, &point);
			}
		}
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Point Render Test\n\n"
			"This is the %s render result.\n\n"
			"Do you see a grid of light grey pixels against a black background?",
			OLD_FUNC_POINT
		)) {
			checkedPrimitives |= RES_V3_POINT_PASSED;
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
//  Line user acceptance tests
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV3Lines(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Legacy Line Render Tests");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Legacy Line Render Tests\n\n"
		"W3DUnit will test if line rendering using Warp3D legacy (W3D_Vertex) drawing methods\n"
		"is supported in the current driver.\n"
		"There are three legacy line rendering methods that will be tested. Each test will attempt\n"
		"to render a nested set of light grey rectangles using the specific drawing function.\n"
		"Skipping these tests will tell W3DUnit to assume that all thre line rendering\n"
		"methods are fully and correctly supported."
	)) {
		Log::write("\nSkipped all legacy line render tests\n");
		checkedPrimitives |= RES_V3_LINE_PASSED|RES_V3_LINELOOP_PASSED|RES_V3_LINESTRIP_PASSED;
		return;
	}
	Log::write("\nPerforming legacy line render tests\n");
	setMinimalRenderState(contextFacade);
	setStateLogged(contextFacade->getW3DContext(), W3D_GOURAUD, W3D_ENABLE);
	confirmW3DDrawLine(contextFacade, 1, 3);
	confirmW3DDrawLineStrip(contextFacade, 2, 3);
	confirmW3DDrawLineLoop(contextFacade, 3, 3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawLine user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawLine(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Line     line          = { NVTX(0.8f), NVTX(0.8f), 0, 1.0f, W3D_FALSE, 0, 0 };
	const char*  OLD_FUNC_LINE = "W3D_DrawLine()";
	int32        w             = contextFacade->getWidth();
	int32        h             = contextFacade->getHeight();
	W3D_Context* w3DContext    = contextFacade->getW3DContext();
	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_LINE);
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		int max = (w>h ? h>>1 : w>>1)-4;
		for (int i = 4; i<max; i+=16) {
			// top edge (tests left to right)
			line.v1.x = i+0.5f;
			line.v1.y = i+0.5f;
			line.v2.x = (w-i)+0.5f;
			line.v2.y = i+0.5f;
			IWarp3D->W3D_DrawLine(w3DContext, &line);
			// right edge (tests top to bottom)
			line.v1.x = (w-i)+0.5f;
			line.v1.y = i+0.5f;
			line.v2.x = (w-i)+0.5f;
			line.v2.y = (h-i)+0.5f;
			IWarp3D->W3D_DrawLine(w3DContext, &line);
			// bottom edge (tests right to left)
			line.v1.x = (w-i)+0.5f;
			line.v1.y = (h-i)+0.5f;
			line.v2.x = i+0.5f;
			line.v2.y = (h-i)+0.5f;
			IWarp3D->W3D_DrawLine(w3DContext, &line);
			// left edge (tests bottom to top)
			line.v1.x = i+0.5f;
			line.v1.y = (h-i)+0.5f;
			line.v2.x = i+0.5f;
			line.v2.y = i+0.5f;
			IWarp3D->W3D_DrawLine(w3DContext, &line);
		}
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Line Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			OLD_FUNC_LINE
		)) {
			checkedPrimitives |= RES_V3_LINE_PASSED;
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
//  W3D_DrawLineStrip user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawLineStrip(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex   rectangle[5]       = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f) };
	W3D_Lines    lines              = { 5, rectangle, 0, 1.0f, W3D_FALSE, 0, 0 };
	const char*  OLD_FUNC_LINESTRIP = "W3D_DrawLineStrip()";
	int32        w                  = contextFacade->getWidth();
	int32        h                  = contextFacade->getHeight();
	W3D_Context* w3DContext         = contextFacade->getW3DContext();
	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_LINESTRIP);
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		int max = (w>h ? h>>1 : w>>1)-4;
		for (int i = 4; i<max; i+=16) {
			// top left
			rectangle[0].x = i+0.5f;
			rectangle[0].y = i+0.5f;
			// top right
			rectangle[1].x = w-i+0.5f;
			rectangle[1].y = i+0.5f;
			// bottom right
			rectangle[2].x = w-i+0.5f;
			rectangle[2].y = h-i+0.5f;
			// bottom left
			rectangle[3].x = i+0.5f;
			rectangle[3].y = h-i+0.5f;
			// top left
			rectangle[4].x = i+0.5f;
			rectangle[4].y = i+0.5f;
			IWarp3D->W3D_DrawLineStrip(w3DContext, &lines);
		}
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Line Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			OLD_FUNC_LINESTRIP
		)) {
			checkedPrimitives |= RES_V3_LINESTRIP_PASSED;
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
//  W3D_DrawLineLoop user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawLineLoop(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex   rectangle[4]      = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f) };
	W3D_Lines    lines             = { 4, rectangle, 0, 1.0f, W3D_FALSE, 0, 0 };
	const char*  OLD_FUNC_LINELOOP = "W3D_DrawLineLoop()";
	int32        w                 = contextFacade->getWidth();
	int32        h                 = contextFacade->getHeight();
	W3D_Context* w3DContext        = contextFacade->getW3DContext();
	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_LINELOOP);
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		int max = (w>h ? h>>1 : w>>1)-4;
		for (int i = 4; i<max; i+=16) {
			// top left
			rectangle[0].x = i+0.5f;
			rectangle[0].y = i+0.5f;
			// top right
			rectangle[1].x = w-i+0.5f;
			rectangle[1].y = i+0.5f;
			// bottom right
			rectangle[2].x = w-i+0.5f;
			rectangle[2].y = h-i+0.5f;
			// bottom left
			rectangle[3].x = i+0.5f;
			rectangle[3].y = h-i+0.5f;
			IWarp3D->W3D_DrawLineLoop(w3DContext, &lines);
		}
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Line Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a nested set of light grey wireframe rectangles ?",
			testNum, testCount,
			OLD_FUNC_LINELOOP
		)) {
			checkedPrimitives |= RES_V3_LINELOOP_PASSED;
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
//  Triangle user acceptance tests
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmV3Tris(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Legacy Triangle Render Tests");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Legacy Triangle Render Test\n\n"
		"W3DUnit will test triangle rendering using Warp3D legacy W3D_Vertex based\n"
		"drawing.\n"
		"There are six triangle rendering methods that will be tested.\n"
		"Skipping these tests will tell W3DUnit to assume that all six triangle rendering\n"
		"methods are fully and correctly supported."
	)) {
		Log::write("\nSkipped V1-3 triangle render tests\n");
		checkedPrimitives |= RES_V3_TRIANGLE_PASSED|RES_V3_TRIFAN_PASSED|RES_V3_TRISTRIP_PASSED|
											   RES_V3_TRIANGLEV_PASSED|RES_V3_TRIFANV_PASSED|RES_V3_TRISTRIPV_PASSED;
		return;
	}
	Log::write("\nPerforming legacy triangle render tests\n");
	setMinimalRenderState(contextFacade);
	setStateLogged(contextFacade->getW3DContext(), W3D_GOURAUD, W3D_ENABLE);
	confirmW3DDrawTriangle(contextFacade,  1, 6);
	confirmW3DDrawTriangleV(contextFacade, 2, 6);
	confirmW3DDrawTriFan(contextFacade,    3, 6);
	confirmW3DDrawTriFanV(contextFacade,   4, 6);
	confirmW3DDrawTriStrip(contextFacade,  5, 6);
	confirmW3DDrawTriStripV(contextFacade, 6, 6);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_DrawTriangle user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriangle(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Triangle tri               = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), 0, 0 };
	const char*  OLD_FUNC_TRIANGLE = "W3D_DrawTriangle()";
	int32        w                 = contextFacade->getWidth();
	int32        h                 = contextFacade->getHeight();
	W3D_Context* w3DContext        = contextFacade->getW3DContext();

	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_TRIANGLE);
	tri.v1.x = 4;     tri.v1.y = h-4;
	tri.v2.x = 0.5*w; tri.v2.y = 4;
	tri.v3.x = w-4;   tri.v3.y = h-4;
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriangle(w3DContext, &tri);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey triangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRIANGLE
		)) {
			checkedPrimitives |= RES_V3_TRIANGLE_PASSED;
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
//  W3D_DrawTriangleV user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriangleV(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex    vtx[3]             = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f) };
	W3D_TriangleV tri                = { &vtx[0], &vtx[1], &vtx[2], 0, 0 };
	const char*   OLD_FUNC_TRIANGLEV = "W3D_DrawTriangleV()";
	int32         w                  = contextFacade->getWidth();
	int32         h                  = contextFacade->getHeight();
	W3D_Context*  w3DContext         = contextFacade->getW3DContext();
	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_TRIANGLEV);
	vtx[0].x = 4;     vtx[0].y = h-4;
	vtx[1].x = 0.5*w; vtx[1].y = 4;
	vtx[2].x = w-4;   vtx[2].y = h-4;
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriangleV(w3DContext, &tri);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey triangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRIANGLEV
		)) {
			checkedPrimitives |= RES_V3_TRIANGLEV_PASSED;
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
//  W3D_DrawTriFan user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriFan(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex    vtx[6]          = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f) };
	W3D_Triangles tris            = { 6, vtx, 0, 0 };
	const char*   OLD_FUNC_TRIFAN = "W3D_DrawTriFan()";
	int32         w               = contextFacade->getWidth();
	int32         h               = contextFacade->getHeight();
	W3D_Context*  w3DContext      = contextFacade->getW3DContext();

	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_TRIFAN);

	//  Test Vertex configuration
	// 	1/5--2
	//   |\ /|
	//   | 0 |
	//   |/ \|
	//   4---3

	vtx[0].x = 0.5*w; vtx[0].y = 0.5*h;
	vtx[1].x = 32;    vtx[1].y = 32;
	vtx[2].x = w-32;  vtx[2].y = 32;
	vtx[3].x = w-32;  vtx[3].y = h-32;
	vtx[4].x = 32;    vtx[4].y = h-32;
	vtx[5].x = 32;    vtx[5].y = 32;
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriFan(w3DContext, &tris);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey rectangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRIFAN
		)) {
			checkedPrimitives |= RES_V3_TRIFAN_PASSED;
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
//  W3D_DrawTriFanV user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriFanV(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex     vtx[5]           = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f)/*, NVTX(0.8f) */ };
	W3D_Vertex*    ptr[6]           = { &vtx[0],    &vtx[1],    &vtx[2],    &vtx[3],  &vtx[4],    &vtx[1] };
	W3D_TrianglesV tris             = { 6, ptr, 0, 0 };
	const char*    OLD_FUNC_TRIFANV = "W3D_DrawTriFanV()";
	int32          w                = contextFacade->getWidth();
	int32          h                = contextFacade->getHeight();
	W3D_Context*   w3DContext       = contextFacade->getW3DContext();

	contextFacade->clear(0);

	Log::write("\t%-26s : ", OLD_FUNC_TRIFANV);

	//  Test Vertex configuration
	//
	// 1/5--2
	//  |\ /|
	//  | 0 |
	//  |/ \|
	//  4---3

	vtx[0].x = 0.5*w; vtx[0].y = 0.5*h;
	vtx[1].x = 32;    vtx[1].y = 32;
	vtx[2].x = w-32;  vtx[2].y = 32;
	vtx[3].x = w-32;  vtx[3].y = h-32;
	vtx[4].x = 32;    vtx[4].y = h-32;
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriFanV(w3DContext, &tris);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey rectangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRIFANV
		)) {
			checkedPrimitives |= RES_V3_TRIFANV_PASSED;
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
//  W3D_DrawTriStrip user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriStrip(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex    vtx[6]            = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f)};
	W3D_Triangles tris              = { 6, vtx, 0, 0 };
	const char*   OLD_FUNC_TRISTRIP = "W3D_DrawTriStrip()";
	int32         w                 = contextFacade->getWidth();
	int32         h                 = contextFacade->getHeight();
	W3D_Context*  w3DContext        = contextFacade->getW3DContext();

	Log::write("\t%-26s : ", OLD_FUNC_TRISTRIP);

	//  Test Vertex configuration
	//
	//  0--2--4
	//  | /| /|
	//  |/ |/ |
	//  1--3--5

	vtx[0].x = 32;    vtx[0].y = 32;
	vtx[1].x = 32;    vtx[1].y = h-32;
	vtx[2].x = 0.5*w; vtx[2].y = 32;
	vtx[3].x = 0.5*w; vtx[3].y = h-32;
	vtx[4].x = w-32;  vtx[4].y = 32;
	vtx[5].x = w-32;  vtx[5].y = h-32;

	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriStrip(w3DContext, &tris);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey rectangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRISTRIP
		)) {
			checkedPrimitives |= RES_V3_TRISTRIP_PASSED;
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
//  W3D_DrawTriStripV user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmW3DDrawTriStripV(ContextFacade* contextFacade, int testNum, int testCount)
{
	W3D_Vertex     vtx[6]             = { NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f), NVTX(0.8f) };
	W3D_Vertex*    ptr[6]             = { &vtx[0],    &vtx[1],    &vtx[2],    &vtx[3],    &vtx[4],    &vtx[5] };
	W3D_TrianglesV tris               = { 6, ptr, 0, 0 };
	const char*    OLD_FUNC_TRISTRIPV = "W3D_DrawTriStripV()";
	int32          w                  = contextFacade->getWidth();
	int32          h                  = contextFacade->getHeight();
	W3D_Context*   w3DContext         = contextFacade->getW3DContext();

	contextFacade->clear(0);
	Log::write("\t%-26s : ", OLD_FUNC_TRISTRIPV);

	//  Test Vertex configuration
	//
	//  0--2--4
	//  | /| /|
	//  |/ |/ |
	//  1--3--5

	vtx[0].x = 32;    vtx[0].y = 32;
	vtx[1].x = 32;    vtx[1].y = h-32;
	vtx[2].x = 0.5*w; vtx[2].y = 32;
	vtx[3].x = 0.5*w; vtx[3].y = h-32;
	vtx[4].x = w-32;  vtx[4].y = 32;
	vtx[5].x = w-32;  vtx[5].y = h-32;
	if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
		IWarp3D->W3D_DrawTriStripV(w3DContext, &tris);
		IWarp3D->W3D_FlushFrame(w3DContext);
		IWarp3D->W3D_UnLockHardware(w3DContext);
		contextFacade->refresh();
		if (contextFacade->showDialogue(
			Dialogue::TITLE_QUERY,
			Dialogue::OPTS_YES_NO,
			"Warp3D Legacy Triangle Render Test %d/%d\n\n"
			"This is the %s render result.\n\n"
			"Do you see a solid light grey rectangle against a black background?",
			testNum, testCount,
			OLD_FUNC_TRISTRIPV
		)) {
			checkedPrimitives |= RES_V3_TRISTRIPV_PASSED;
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
