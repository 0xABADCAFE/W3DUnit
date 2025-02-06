
#include "headers.hpp"


namespace Dialogue {
	const char* OPTS_RUN_SKIP     = "Run|Skip";
	const char* OPTS_YES_NO_OTHER = "Yes|Not Exactly...|No";
};

const char* Testing::TEST_FAIL    = "failed";
const char* Testing::TEST_PASS    = "passed";
const char* Testing::HWLOCK_FAIL  = "failed to lock hardware\n";

//uint32 Testing::check = 0;

uint32 Testing::checkedVertexLayout      = 0;
uint32 Testing::checkedPrimitives        = 0;
uint32 Testing::checkedMisc              = 0;
uint32 Testing::checkedZOperations       = 0;
uint32 Testing::checkedStencilOperations = 0;
uint32 Testing::checkedTexelFormats      = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint32 Testing::setStateLogged(W3D_Context* w3dContext, uint32 property, uint32 state)
{
	uint32 result = IWarp3D->W3D_SetState(w3dContext, property, state);
	if (result!=W3D_SUCCESS) {
		Log::write(
			"\t[Set state %-21s : %-12s (%s)]\n",
			W3DEnums::getW3DStateFlagName(property),
			W3DEnums::getW3DStateStatusName(state),
			W3DEnums::getW3DStatusName(result)
		);
	}
	return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Testing::runImplementationChecks(Vertex::Buffer* vertexBuffer, ContextFacade* contextFacade)
{
	// basic 2D
	confirm2DFills(vertexBuffer, contextFacade);

	// old primitives
	confirmV3Points(vertexBuffer, contextFacade);
	confirmV3Lines(vertexBuffer, contextFacade);
	confirmV3Tris(vertexBuffer, contextFacade);

	// states
	confirmShadeModes(vertexBuffer, contextFacade);
	if (contextFacade->haveZBuffer()) {
		confirmZBuffer(vertexBuffer, contextFacade);
	}
	confirmVertexGeometryFormats(vertexBuffer, contextFacade);
	confirmVertexColorFormats(vertexBuffer, contextFacade);


	// vertex array primitives
	Testing::confirmV4Points(vertexBuffer, contextFacade);
	Testing::confirmV4Lines(vertexBuffer, contextFacade);
	Testing::confirmV4Tris(vertexBuffer, contextFacade);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

