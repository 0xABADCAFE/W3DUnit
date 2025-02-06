
#include "headers.hpp"

namespace {

	// Geometry tests
	void setFFF(Vertex::Buffer* vertexBuffer, int32 w, int32 h)
	{
		Vertex::Geometry::FFF* v = vertexBuffer->getGeometryFFF();
		v[0].x = 4;   v[0].y = h-4; v[0].z = 0;
		v[1].x = w/2; v[1].y = 4;   v[1].z = 0;
		v[2].x = w-4; v[2].y = h-4; v[2].z = 0;
	}

	void setFFD(Vertex::Buffer* vertexBuffer, int32 w, int32 h)
	{
		Vertex::Geometry::FFD* v = vertexBuffer->getGeometryFFD();
		v[0].x = 4;   v[0].y = h-4; v[0].z = 0;
		v[1].x = w/2; v[1].y = 4;   v[1].z = 0;
		v[2].x = w-4; v[2].y = h-4; v[2].z = 0;
	}

	void setDDD(Vertex::Buffer* vertexBuffer, int32 w, int32 h)
	{
		Vertex::Geometry::DDD* v = vertexBuffer->getGeometryDDD();
		v[0].x = 4;   v[0].y = h-4; v[0].z = 0;
		v[1].x = w/2; v[1].y = 4;   v[1].z = 0;
		v[2].x = w-4; v[2].y = h-4; v[2].z = 0;
	}

	// Colour tests
	void setURGB(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::U* v = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
		v[0].rgba32 = 0xFF000000;
		v[1].rgba32 = 0x00FF0000;
		v[2].rgba32 = 0x0000FF00;
	}

	void setUBGR(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::U* v = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
		v[0].bgra32 = 0x0000FF00;
		v[1].bgra32 = 0x00FF0000;
		v[2].bgra32 = 0xFF000000;
	}

	void setURGBA(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::U* v = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
		v[0].rgba32 = 0xFF0000FF;
		v[1].rgba32 = 0x00FF00FF;
		v[2].rgba32 = 0x0000FFFF;
	}

	void setUARGB(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::U* v = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
		v[0].argb32 = 0xFFFF0000;
		v[1].argb32 = 0xFF00FF00;
		v[2].argb32 = 0xFF0000FF;
	}

	void setUBGRA(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::U* v = vertexBuffer->getColorU(Vertex::Color::CT_NORMAL);
		v[0].bgra32 = 0x0000FFFF;
		v[1].bgra32 = 0x00FF00FF;
		v[2].bgra32 = 0xFF0000FF;
	}

	void setFRGB(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].rgb.r = 1.0f; v[0].rgb.g = 0;    v[0].rgb.b = 0;
		v[1].rgb.r = 0;    v[1].rgb.g = 1.0f; v[1].rgb.b = 0;
		v[2].rgb.r = 0;    v[2].rgb.g = 0;    v[2].rgb.b = 1.0f;
	}

	void setFBGR(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].bgr.r = 1.0f; v[0].bgr.g = 0;    v[0].bgr.b = 0;
		v[1].bgr.r = 0;    v[1].bgr.g = 1.0f; v[1].bgr.b = 0;
		v[2].bgr.r = 0;    v[2].bgr.g = 0;    v[2].bgr.b = 1.0f;
	}

	void setFRGBA(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].rgba.r = 1.0f; v[0].rgba.g = 0;    v[0].rgba.b = 0;    v[0].rgba.a = 1.0f;
		v[1].rgba.r = 0;    v[1].rgba.g = 1.0f; v[1].rgba.b = 0;    v[1].rgba.a = 1.0f;
		v[2].rgba.r = 0;    v[2].rgba.g = 0;    v[2].rgba.b = 1.0f; v[2].rgba.a = 1.0f;
	}

	void setFARGB(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].argb.r = 1.0f; v[0].argb.g = 0;    v[0].argb.b = 0;    v[0].argb.a = 1.0f;
		v[1].argb.r = 0;    v[1].argb.g = 1.0f; v[1].argb.b = 0;    v[1].argb.a = 1.0f;
		v[2].argb.r = 0;    v[2].argb.g = 0;    v[2].argb.b = 1.0f; v[2].argb.a = 1.0f;
	}

	void setFBGRA(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].bgra.r = 1.0f; v[0].bgra.g = 0;    v[0].bgra.b = 0;    v[0].bgra.a = 0;
		v[1].bgra.r = 0;    v[1].bgra.g = 1.0f; v[1].bgra.b = 0;    v[1].bgra.a = 0;
		v[2].bgra.r = 0;    v[2].bgra.g = 0;    v[2].bgra.b = 1.0f; v[2].bgra.a = 0;
	}

	void setGeometryTestColor(Vertex::Buffer* vertexBuffer)
	{
		Vertex::Color::F* v = vertexBuffer->getColorF(Vertex::Color::CT_NORMAL);
		v[0].rgba.r = 0.8f; v[0].rgba.g = 0.8f; v[0].rgba.b = 0.8f; v[0].rgba.a = 1.0f;
		v[1].rgba.r = 0.8f; v[1].rgba.g = 0.8f; v[1].rgba.b = 0.8f; v[1].rgba.a = 1.0f;
		v[2].rgba.r = 0.8f; v[2].rgba.g = 0.8f; v[2].rgba.b = 0.8f; v[2].rgba.a = 1.0f;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	//  Types
	//
	////////////////////////////////////////////////////////////////////////////////

	typedef void (*TestVertex)(Vertex::Buffer* vertexBuffer, int32 w, int32 h);
	typedef void (*TestColour)(Vertex::Buffer* vertexBuffer);

	struct VTest {
		Vertex::Geometry::Format format;
		TestVertex               func;
		const char*              logName;
		const char*              name;
	};

	struct CTest {
		Vertex::Color::Format format;
		TestColour            func;
		const char*           logMode;
		int32                 logNameIdx;
		const char*           name;
	};

	VTest vTestTab[] = {
		{	Vertex::Geometry::XYZ_FFF, setFFF, "W3D_VERTEX_F_F_F", "float XYZ" },
		{	Vertex::Geometry::XYZ_FFD, setFFD, "W3D_VERTEX_F_F_D", "float XY, double Z" },
		{	Vertex::Geometry::XYZ_DDD, setDDD, "W3D_VERTEX_D_D_D", "double XYZ" },
	};


	CTest cTestTab[] = {
		{	Vertex::Color::CLR_URGB,  setURGB,  "\nW3D_COLOR_UBYTE\n", 0, "8-bit RGB" },
		{	Vertex::Color::CLR_UBGR,  setUBGR,  0, 1, "8-bit BGR" },
		{	Vertex::Color::CLR_URGBA, setURGBA, 0, 2, "8-bit RGBA" },
		{	Vertex::Color::CLR_UARGB, setUARGB, 0, 3, "8-bit ARGB" },
		{	Vertex::Color::CLR_UBGRA, setUBGRA, 0, 4, "8-bit BGRA" },
		{	Vertex::Color::CLR_FRGB,  setFRGB,  "\nW3D_COLOR_FLOAT\n", 0, "32-bit float RGB" },
		{	Vertex::Color::CLR_FBGR,  setFBGR,  0, 1, "32-bit float BGR" },
		{	Vertex::Color::CLR_FRGBA, setFRGBA, 0, 2, "32-bit float RGBA" },
		{	Vertex::Color::CLR_FARGB, setFARGB, 0, 3, "32-bit float ARGB" },
		{ Vertex::Color::CLR_FBGRA, setFBGRA, 0, 4, "32-bit float BGRA" }
	};

	const char* w3DCModeNames[] = {
		"W3D_CMODE_RGB",
		"W3D_CMODE_BGR",
		"W3D_CMODE_RGBA",
		"W3D_CMODE_ARGB",
		"W3D_CMODE_BGRA"
	};
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmVertexGeometryFormats(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Array Vertex Format Test");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D v4+ Array Vertex Format Test\n\n"
		"W3DUnit will test the 3 defined Warp3D v4 Vertex Array vertex formats.\n"
		"In each case, you should see a light grey triangle against a dark blue background.\n\n"
		"Skipping these tests will tell W3DUnit to assume all vertex formats are\n"
		"correctly implemented by your driver."
	)) {
		Log::write("\nSkipped supported array vertex format tests\n");
		checkedVertexLayout |= RES_VERTEX_GEOMETRY_STATUS;
		return;
	}

	W3D_Context*      w3DContext = contextFacade->getW3DContext();
	const char*       query =
		"This is the vertex format test result %d/3.\n\n"
		"The current geometry mode is %s.\n"
		"Do you see a light grey triangle?";


	Log::write("\nPerforming array vertex format tests\n");

	setMinimalRenderState(contextFacade);
	setStateLogged(w3DContext, W3D_GOURAUD,    W3D_ENABLE);

	contextFacade->setVertexColorArray(
		vertexBuffer->getColorF(Vertex::Color::CT_NORMAL),
		Vertex::Color::CLR_FRGBA,
		Vertex::Color::CT_NORMAL
	);
	setGeometryTestColor(vertexBuffer);

	//contextFacade->setFlatShadeColor(0xFFCCCCCC);

	for (int32 v=0; v<Vertex::Geometry::_XYZ_NUM; v++) {
		Log::write("\t%-26s : ", vTestTab[v].logName);

		vTestTab[v].func(
			vertexBuffer,
			contextFacade->getWidth(),
			contextFacade->getHeight()
		);

		contextFacade->setVertexGeometryArray(vertexBuffer->getGeometryRaw(), vTestTab[v].format);
		if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
			IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
			IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_TRIANGLES, 0, 3);
			IWarp3D->W3D_FlushFrame(w3DContext);
			IWarp3D->W3D_UnLockHardware(w3DContext);
			contextFacade->refresh();

			if (contextFacade->showDialogue(
				Dialogue::TITLE_QUERY,
				Dialogue::OPTS_YES_NO,
				query,
				v+1,
				vTestTab[v].name)==RESULT_YES
			) {
				checkedVertexLayout |= (RES_VERTEX_TEST_PASSED<<(v+_RES_VERTEX_GEOMETRY_OFFSET));
				Log::write("%s\n", TEST_PASS);
			}
			else {
				checkedVertexLayout &= ~(RES_VERTEX_TEST_PASSED<<(v+_RES_VERTEX_GEOMETRY_OFFSET));
				Log::write("%s\n", TEST_FAIL);
			}
		}
		else {
			Log::write("failed to lock hardware\n");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmVertexColorFormats(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : Array Colour Format Test");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D v4 Array Colour Format Test\n\n"
		"W3DUnit will test the 10 defined Warp3D Vertex Array colour formats.\n"
		"In each case, you should see a smoothly shaded triangle with the bottom-left corner\n"
		"coloured red, top corner coloured green and bottom-right corner coloured blue.\n"
		"When asked, if the triangle on screen does not conform to this exact\n"
		"layout, you should answer 'No'. If you answer 'No', you will be asked to pick from\n"
		"a list of options which best describes the problem you can see.\n\n"
		"Skipping these tests will tell W3DUnit to assume all colour formats are\n"
		"correctly implemented by your driver."
	)) {
		Log::write("Skipped colour format tests\n");
		checkedVertexLayout |= RES_VERTEX_COLOR_ALL_PASSED;
		return;
	}

	W3D_Context*      w3DContext = contextFacade->getW3DContext();
	const char*       query =
		"This is the colour format test result %d/10.\n\n"
		"The current mode is %s.\n"
		"Do you see a smoothly shaded triangle with the bottom-left corner\n"
		"coloured red, top corner coloured green and bottom-right corner coloured blue?";

	contextFacade->setFlatShadeColor(0xFFCCCCCC);
	setFFF(
		vertexBuffer,
		contextFacade->getWidth(),
		contextFacade->getHeight()
	);
	contextFacade->setVertexGeometryArray(vertexBuffer->getGeometryFFF());

	IWarp3D->W3D_SetState(w3DContext, W3D_GOURAUD, W3D_ENABLE);
	IWarp3D->W3D_SetState(w3DContext, W3D_DITHERING, W3D_ENABLE);
	IWarp3D->W3D_SetState(w3DContext, W3D_TEXMAPPING, W3D_DISABLE);

	for (int32 c=0; c<Vertex::Color::_CLR_NUM; c++) {
		if (cTestTab[c].logMode) {
			Log::write(cTestTab[c].logMode);
		}
		cTestTab[c].func(
			vertexBuffer
		);

		Log::write("\t%-26s : ", w3DCModeNames[cTestTab[c].logNameIdx]);

		contextFacade->setVertexColorArray(
			vertexBuffer->getColorRaw(Vertex::Color::CT_NORMAL),
			cTestTab[c].format,
			Vertex::Color::CT_NORMAL
		);
		if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
			IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x00000000);
			IWarp3D->W3D_DrawArray(w3DContext, W3D_PRIMITIVE_TRIANGLES, 0, 3);
			IWarp3D->W3D_FlushFrame(w3DContext);
			IWarp3D->W3D_UnLockHardware(w3DContext);
			contextFacade->refresh();

			int32 shift = (c<<1)+_RES_VERTEX_COLOR_OFFSET;

			if (contextFacade->showDialogue(
				Dialogue::TITLE_QUERY,
				Dialogue::OPTS_YES_NO,
				query, c+1,
				cTestTab[c].name
			)) {
				checkedVertexLayout |= RES_VERTEX_TEST_PASSED<<shift;
				Log::write("%s\n", TEST_PASS);
			}
			else {

				int32 res = contextFacade->showDialogue(
					Dialogue::TITLE_QUERY,
					"1|2|3|4|5",
					"Warp3D v4 Array Colour Format Test: Diagnostic\n\n"
					"You have indicated that the render output failed to meet the expected\n"
					"criteria (smoothly shaded triangle with the bottom-left corner coloured\n"
					"red, top corner coloured green and bottom-right corner coloured blue).\n\n"
					"Please choose the option that best describes the observed result:\n"
					"1. I can't see a triangle at all.\n"
					"2. I see an unshaded grey triangle.\n"
					"3. I see the shaded triangle but the corner colours appear random.\n"
					"4. I see the shaded triangle but the corner colours are not in the correct order.\n"
					"5. Actually, the triangle appears correctly rendered after all.\n"
				);

				checkedVertexLayout &= ~(Testing::RES_VERTEX_TEST_STATUS<<shift);

				switch (res) {
					case 1:
						Log::write("%s [observed no output]\n", TEST_FAIL);
						break;
					case 2:
						Log::write("%s [observed flat shade colour]\n", TEST_FAIL);
						break;
					case 3:
						Log::write("%s [observed random vertex shading]\n", TEST_FAIL);
						break;
					case 4:
						Log::write("%s [observed RGB transposition]\n", TEST_FAIL);
						checkedVertexLayout |= RES_VERTEX_TEST_PARTIAL<<shift;
						break;
					case 0:
					default:
						checkedVertexLayout |= RES_VERTEX_TEST_PASSED<<shift;
						Log::write("%s\n", TEST_PASS);
						break;
				}
			}
		}
		else {
			Log::write("failed to lock hardware\n");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


