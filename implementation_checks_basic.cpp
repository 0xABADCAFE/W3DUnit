
#include "headers.hpp"

void Testing::setMinimalRenderState(ContextFacade* contextFacade)
{
	W3D_Context* w3DContext = contextFacade->getW3DContext();
	if (contextFacade->haveZBuffer()) {
		setStateLogged(w3DContext, W3D_ZBUFFER,       W3D_DISABLE);
		setStateLogged(w3DContext, W3D_ZBUFFERUPDATE, W3D_DISABLE);
	}
	setStateLogged(w3DContext, W3D_BLENDING,   W3D_DISABLE);
	setStateLogged(w3DContext, W3D_ALPHATEST,  W3D_DISABLE);
	setStateLogged(w3DContext, W3D_TEXMAPPING, W3D_DISABLE);
	setStateLogged(w3DContext, W3D_DITHERING,  W3D_DISABLE);
	//setStateLogged(w3DContext, W3D_GOURAUD,    W3D_ENABLE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_ClearDrawRegion / colour conversion user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirm2DFills(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	contextFacade->clear(0);
	contextFacade->refresh();
	contextFacade->setTitle("W3DUnit : 2D Fills");
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Block Filling Test\n\n"
		"W3DUnit will test 2D block fill operation.\n"
		"The area defined by the current scissor region will filled with with a solid colour\n"
		"a number of times, which you will be asked to confirm. This test will confirm that\n"
		"the driver correctly translates 32-bit ARGB values into the current display format.\n"
		"Skipping these tests will tell W3DUnit to assume 2D block filling is correctly implemented\n"
		"by your driver."
	)) {
		Log::write("\nSkipped block filling tests\n");
		checkedMisc |= RES_MISC_BLOCK_FILL_RED_PASSED|RES_MISC_BLOCK_FILL_GREEN_PASSED|RES_MISC_BLOCK_FILL_BLUE_PASSED;
		return;
	}

	W3D_Context* w3DContext = contextFacade->getW3DContext();

	uint32 colours[3] = {
		0xFFCC0000,
		0xFF00CC00,
		0xFF0000CC,
	};
	const char* names[3] = {
		"red",
		"green",
		"blue",
	};
	const char* query =
		"This is the block fill test result %d/%d.\n"
		"The ARGB value used was 0x%08X.\n\n"
		"Is the display area filled with %s?";

	int max = (int) ( sizeof(colours)/sizeof(uint32) );

	Log::write("\nPerforming block fill tests\n");

	setMinimalRenderState(contextFacade);

	for (int i=0; i<max; i++) {
		Log::write("\tBlock fill test %d/%d 0x%08X : ", (i+1), max, (unsigned) colours[i]);

		if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
 			IWarp3D->W3D_ClearDrawRegion(w3DContext, colours[i]);
			IWarp3D->W3D_UnLockHardware(w3DContext);
			contextFacade->refresh();

			if (contextFacade->showDialogue(
				Dialogue::TITLE_QUERY,
				Dialogue::OPTS_YES_NO,
				query, i+1, max,
				(unsigned)colours[i],
				names[i]
			)) {
				Log::write("%s\n", TEST_PASS);
				checkedMisc |= 1<<i;
			}
			else {
				Log::write("%s\n", TEST_FAIL);
			}

		}
		else {
			Log::write("failed to lock hardware\n");
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_GORAUD user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmShadeModes(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	const char*  gouraud = W3DEnums::getW3DStateFlagName(W3D_GOURAUD);
	int32        w                 = contextFacade->getWidth();
	int32        h                 = contextFacade->getHeight();
	W3D_Context* w3DContext        = contextFacade->getW3DContext();

	contextFacade->clear(0);
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Shading Tests\n\n"
		"W3DUnit will test the supported shading modes of your driver.\n"
		"The first test will render a triangle with %s enabled. If your driver properly\n"
		"supports this shading method you should see a smoothly shaded triangle with the\n"
		"bottom-left corner shaded red, the top corner shaded green and the bottom-right\n"
		"corner shaded blue rendered against a black background.\n"
		"The second test will render the same triangle with %s disabled. If your driver\n"
		"properly supports this shading method, you should see a solid light grey triangle\n"
		"rendered against a black background.\n\n"
		"Skipping these tests will tell W3DUnit to assume both are correctly implemented\n"
		"by your driver.",
		gouraud,
		gouraud
	)) {
		Log::write("\nSkipped shading tests\n");
		checkedMisc |= RES_MISC_GOURAUD_SHADING_PASSED|RES_MISC_FLAT_SHADING_PASSED;
		return;
	}
	else {

		W3D_Triangle tri = { NVTX3(1.0f, 0.0f, 0.0f), NVTX3(0.0f, 1.0f, 0.0f), NVTX3(0.0f, 0.0f, 1.0f), 0, 0 };
		Log::write("\nPerforming block fill tests\n");

		tri.v1.x = 4;     tri.v1.y = h-4;
		tri.v2.x = 0.5*w; tri.v2.y = 4;
		tri.v3.x = w-4;   tri.v3.y = h-4;

		setMinimalRenderState(contextFacade);

		setStateLogged(w3DContext, W3D_GOURAUD, W3D_ENABLE);

		Log::write("\t%s %-14s : ", gouraud, "[enabled]");

		if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
			IWarp3D->W3D_DrawTriangle(w3DContext, &tri);
			IWarp3D->W3D_FlushFrame(w3DContext);
			IWarp3D->W3D_UnLockHardware(w3DContext);
			contextFacade->refresh();

			if (contextFacade->showDialogue(
				Dialogue::TITLE_QUERY,
				Dialogue::OPTS_YES_NO,
				"Warp3D Shading Tests 1/2\n\n"
				"This is the %s enabled render result.\n\n"
				"Do you see a smoothly shaded triangle with the bottom-left corner shaded\n"
				"red, the top corder shaded green and the botton-right corner shaded blue\n"
				"against a black background?",
				gouraud
			)) {
				checkedMisc |= RES_MISC_GOURAUD_SHADING_PASSED;
				Log::write("%s\n", TEST_PASS);
			}
			else {
				Log::write("%s\n", TEST_FAIL);
			}
		}
		else {
			Log::write("failed to lock hardware\n");
		}

		contextFacade->clear(0);

		contextFacade->setFlatShadeColor(0xFFCCCCCC);
		setStateLogged(w3DContext, W3D_GOURAUD, W3D_DISABLE);

		Log::write("\t%s %-14s : ", gouraud, "[disabled]");

		if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
			IWarp3D->W3D_DrawTriangle(w3DContext, &tri);
			IWarp3D->W3D_FlushFrame(w3DContext);
			IWarp3D->W3D_UnLockHardware(w3DContext);
			contextFacade->refresh();

			if (contextFacade->showDialogue(
				Dialogue::TITLE_QUERY,
				Dialogue::OPTS_YES_NO,
				"Warp3D Shading Tests 2/2\n\n"
				"This is the %s disabled render result.\n\n"
				"Do you see a solid light grey triangle against a black background?",
				gouraud
			)) {
				checkedMisc |= RES_MISC_FLAT_SHADING_PASSED;
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
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  W3D_ZBUFFER user acceptance test
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace {

	typedef struct {
		float64     clear;
		uint32      testMode;
		uint32      flag;
		const char* description;
		const char* logInfo;
	} ZTest;

	ZTest zTestTab1[] = {{
			0.0, W3D_Z_NEVER,   Testing::RES_Z_CMP_N_PASSED,
			"only the red triangle",
			""
		},{
			0.0, W3D_Z_ALWAYS,  Testing::RES_Z_CMP_A_PASSED,
			"the blue triangle infront of the red triangle",
			""
		},{
			1.0, W3D_Z_LESS,    Testing::RES_Z_CMP_LT_PASSED,
			"the blue triangle intersecting the red triangle such that the lower\n"
			"portion of the blue triangle is infront of the red triangle and the upper portion\n"
			"of the red triangle is infront of blue triangle",
			""
		},{
			1.0, W3D_Z_LEQUAL,    Testing::RES_Z_CMP_LE_PASSED,
			"the blue triangle intersecting the red triangle such that the lower\n"
			"portion of the blue triangle is infront of the red triangle and the upper portion\n"
			"of the red triangle is infront of blue triangle",
			"[less-than component test]"
		},{
			0.0, W3D_Z_GREATER, Testing::RES_Z_CMP_GT_PASSED,
			"the blue triangle intersecting the red triangle such that the upper\n"
			"portion of the blue triangle is infront of the red triangle and the lower portion\n"
			"of the red triangle is infront of the blue triangle",
			""
		},{
			0.0, W3D_Z_GEQUAL, Testing::RES_Z_CMP_GE_PASSED,
			"the blue triangle intersecting the red triangle such that the upper\n"
			"portion of the blue triangle is infront of the red triangle and the lower portion\n"
			"of the red triangle is infront of the blue triangle",
			"[greater-than component test]"
		},
	};

	ZTest zTestTab2[] = {{
			1.0, W3D_Z_LEQUAL,   ~Testing::RES_Z_CMP_LE_PASSED,
			"the blue triangle infront of the red triangle",
			"[equality component test]"
		},{
			0.0, W3D_Z_GEQUAL,   ~Testing::RES_Z_CMP_GE_PASSED,
			"the blue triangle infront of the red triangle",
			"[equality component test]"
		},{
			0.0, W3D_Z_EQUAL,    ~Testing::RES_Z_CMP_EQ_PASSED,
			"only the overlapping area of the blue triangle in front of"
			"the red triangle but not anywhere else (vertices missing)",
			""
		},{
			0.0, W3D_Z_NOTEQUAL, ~Testing::RES_Z_CMP_NE_PASSED,
			"the blue triangle behind the red triangle",
			""
		},
	};

}

void Testing::confirmZBuffer(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	int32        w                 = contextFacade->getWidth();
	int32        h                 = contextFacade->getHeight();
	W3D_Context* w3DContext        = contextFacade->getW3DContext();

	contextFacade->clear(0);
	if (!contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_RUN_SKIP,
		"Warp3D Z buffer tests\n\n"
		"W3DUnit will test the supported Z comparison modes of your driver.\n"
		"In each case, a red triangle will be rendered in which the bottom vertices have Z-values\n"
		"approaching 1.0 and the top vertex approaching to 0.0. Then, a Z comparison function will\n"
		"be enabled and an inverted blue triangle rendered, in which the top vertices have Z-values\n"
		"approaching 1.0 and the bottom vertex approaching 0.0. In each test, the desired outcome\n"
		"will be described and you will be asked to confirm whether or not the rendered output\n"
		"matches the description.\n"
		"The tests are split into two parts since comparisons that include equality need a separate test\n"
		"to verify the equality part of their comparison.\n"
		"Skipping these tests will tell W3DUnit to assume all are correctly implemented by your driver."
	)) {
		Log::write("\nSkipped Z buffer tests\n");
		checkedZOperations |= RES_Z_CMP_N_PASSED|RES_Z_CMP_A_PASSED|RES_Z_CMP_LT_PASSED|RES_Z_CMP_GT_PASSED;
	}
	else {
		W3D_Triangle tri1 = { NVTX3(1.0f, 0.0f, 0.0f), NVTX3(1.0f, 0.0f, 0.0f), NVTX3(1.0f, 0.0f, 0.0f), 0, 0 };
		W3D_Triangle tri2 = { NVTX3(0.0f, 0.0f, 1.0f), NVTX3(0.0f, 0.0f, 1.0f), NVTX3(0.0f, 0.0f, 1.0f), 0, 0 };
		tri1.v1.x = 36;    tri1.v1.y = h-36; tri1.v1.z = 0.9;
		tri1.v2.x = 0.5*w; tri1.v2.y = 4;    tri1.v2.z = 0.1;
		tri1.v3.x = w-36;  tri1.v3.y = h-36; tri1.v3.z = 0.9;
		tri2.v1.x = 36;    tri2.v1.y = 36;   tri2.v1.z = 0.9;
		tri2.v2.x = 0.5*w; tri2.v2.y = h-4;  tri2.v2.z = 0.1;
		tri2.v3.x = w-36;  tri2.v3.y = 36;   tri2.v3.z = 0.9;

		Log::write("\nPerforming Z buffer tests, part 1\n");
		setMinimalRenderState(contextFacade);
		setStateLogged(w3DContext, W3D_GOURAUD, W3D_ENABLE);
		setStateLogged(w3DContext, W3D_ZBUFFER, W3D_ENABLE);
		setStateLogged(w3DContext, W3D_ZBUFFERUPDATE, W3D_ENABLE);

		int num = (sizeof(zTestTab1)/sizeof(ZTest));
		for(int i=0; i<num; i++) {
			const char* testName = W3DEnums::getW3DZTestName(zTestTab1[i].testMode);
			Log::write("\t%-26s : ", testName);
			if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
				IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
				IWarp3D->W3D_ClearZBuffer(w3DContext, &zTestTab1[i].clear);
				IWarp3D->W3D_SetZCompareMode(w3DContext, W3D_Z_ALWAYS);
				IWarp3D->W3D_DrawTriangle(w3DContext, &tri1);
				IWarp3D->W3D_SetZCompareMode(w3DContext, zTestTab1[i].testMode);
				IWarp3D->W3D_DrawTriangle(w3DContext, &tri2);
				IWarp3D->W3D_FlushFrame(w3DContext);
				IWarp3D->W3D_UnLockHardware(w3DContext);
				contextFacade->refresh();
				if (contextFacade->showDialogue(
					Dialogue::TITLE_QUERY,
					Dialogue::OPTS_YES_NO,
					"Warp3D Z buffer test part 1 %d/%d\n\n"
					"This is the %s comparison render result.\n\n"
					"Do you see %s?",
					i+1, num,
					testName,
					zTestTab1[i].description
				)) {
					checkedZOperations |= zTestTab1[i].flag;
					Log::write("%s %s\n", TEST_PASS, zTestTab1[i].logInfo);
				}
				else {
					Log::write("%s %s\n", TEST_FAIL, zTestTab1[i].logInfo);
				}
			}
			else {
				Log::write("failed to lock hardware\n");
			}
		}

		tri1.v1.z = 0.5;
		tri1.v2.z = 0.5;
		tri1.v3.z = 0.5;
		tri2.v1.z = 0.5;
		tri2.v2.z = 0.5;
		tri2.v3.z = 0.5;

		Log::write("\nPerforming Z buffer tests, part 2\n");

		// these will be cleared on failure
		checkedZOperations |= RES_Z_CMP_EQ_PASSED|RES_Z_CMP_NE_PASSED;

		num = (sizeof(zTestTab2)/sizeof(ZTest));
		for(int i=0; i<num; i++) {
			const char* testName = W3DEnums::getW3DZTestName(zTestTab2[i].testMode);
			Log::write("\t%-26s : ", testName);
			if (IWarp3D->W3D_LockHardware(w3DContext)==W3D_SUCCESS) {
				IWarp3D->W3D_ClearDrawRegion(w3DContext, 0x0000000);
				IWarp3D->W3D_ClearZBuffer(w3DContext, &zTestTab2[i].clear);
				IWarp3D->W3D_SetZCompareMode(w3DContext, W3D_Z_ALWAYS);
				IWarp3D->W3D_DrawTriangle(w3DContext, &tri1);
				IWarp3D->W3D_SetZCompareMode(w3DContext, zTestTab2[i].testMode);
				IWarp3D->W3D_DrawTriangle(w3DContext, &tri2);
				IWarp3D->W3D_FlushFrame(w3DContext);
				IWarp3D->W3D_UnLockHardware(w3DContext);
				contextFacade->refresh();
				if (contextFacade->showDialogue(
					Dialogue::TITLE_QUERY,
					Dialogue::OPTS_YES_NO,
					"Warp3D Z buffer test part 2 %d/%d\n\n"
					"This is the %s comparison render result.\n\n"
					"Do you see %s?",
					i+1, num,
					testName,
					zTestTab2[i].description
				)) {
					Log::write("%s %s\n", TEST_PASS, zTestTab2[i].logInfo);
				}
				else {
					Log::write("%s %s\n", TEST_FAIL, zTestTab2[i].logInfo);
					checkedZOperations &= ~(zTestTab2[i].flag);
				}
			}
			else {
				Log::write("failed to lock hardware\n");
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::confirmVertexTextureFormats(Vertex::Buffer* v, ContextFacade* f)
{

}

