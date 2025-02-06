
#include "headers.hpp"
#include <new>
#include <cstdarg>
#include "libraryhelpers.hpp"

namespace {
	const char* execName = "exec.library";
	const char* dosName  = "dos.library";
	const char* intName  = "intuition.library";
	const char* gfxName  = "graphics.library";
  const char* w3dName  = "Warp3D.library";
	const char* p96Name  = "Picasso96API.library";
}

W3DUnitApp* W3DUnitApp::instance     = 0;

struct IntuitionBase*  IntuitionBase = 0;
struct IntuitionIFace* IIntuition    = 0;
struct GfxBase*        GfxBase       = 0;
struct GraphicsIFace*  IGraphics     = 0;
struct Library*        Warp3DBase    = 0;
struct Warp3DIFace*    IWarp3D       = 0;
struct Library*        P96Base       = 0;
struct P96IFace*       IP96          = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int32 W3DUnitApp::run()
{
	// log basic system information
	logLibraryInfo();
	logDriverInfo();
	logCPUInfo();

	// log current context properties and reported capabilities
	contextFacade->logContextInfo();
	contextFacade->logContextState();
	contextFacade->logCapabilities();

	contextFacade->showDialogue(
		Dialogue::TITLE_INFO,
		Dialogue::OPTS_PROCEED,
		"Welcome to W3DUnit\n\n"
		"This program will perform a series of tests of your Warp3D (tm)\n"
		"supported graphics card. Both the quality of implementation and\n"
		"performance of your driver/hardware combination will be tested.\n\n"
		"All results will be logged to the file '%s'\n\n"
		"W3DUnit has successfully initialised and determined your\n"
		"3D chip to be : %s\n",
		getParam(Param::PARAM_LOG_TO)->getString(),
		contextFacade->getChipName()
	);

	// perform the user-driven unit tests. These are invoked in order to
  // get human verification of reported capabilities such that the
	// automated test plan can be constructed

	Testing::runImplementationChecks(vertexBuffer, contextFacade);


	IDOS->Delay(25);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

W3DUnitApp* W3DUnitApp::getInstance()
{
	if (!instance) {
		// open the libraries and attempt to construct the application instance. Library opening will fail if any
		// single library or interface is not available.
		if (openLibraries()) {
			try {
				instance = new W3DUnitApp();
			}
			catch (...) {
				closeLibraries();
			}
		}
	}
	return instance;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void W3DUnitApp::destroyInstance()
{
	if (instance) {
		delete instance;
		instance = 0;
	}
	closeLibraries();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

W3DUnitApp::W3DUnitApp() : ItemDefaulter(), contextFacade(0), vertexBuffer(0)
{
	parseParams();
	if ( !Log::open(params[Param::PARAM_LOG_TO].getString()) ) {
		throw Error::ResourceUnavailable(params[Param::PARAM_LOG_TO].getString());
	}

	int32 width  = getParam(Param::PARAM_WIDTH)->getInteger();
	int32 height = getParam(Param::PARAM_HEIGHT)->getInteger();

	Log::write(
		"Opened log file '%s'\n"
		"Requested display size: %" PF_INT32 " x %" PF_INT32 "\n\n",
		getParam(Param::PARAM_LOG_TO)->getString(),
		width,
		height
	);

	contextFacade = ContextFacade::create("W3DUnit", width, height, 8, ContextFacade::WINDOWED);

	vertexBuffer  = new Vertex::Buffer(129*129, contextFacade->getNumTMU());

	//Log::write("Created ContextFacade at %p\n", contextFacade);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void W3DUnitApp::logLibraryInfo()
{
	Log::write(
		"\nLibrary versions...\n"
		"\t%s %" PF_UINT16 ".%" PF_UINT16 "\n"
		"\t%s %" PF_UINT16 ".%" PF_UINT16 "\n"
		"\t%s %" PF_UINT16 ".%" PF_UINT16 "\n"
		"\t%s %" PF_UINT16 ".%" PF_UINT16 "\n"
		"\t%s %" PF_UINT16 ".%" PF_UINT16 "\n\n",
		execName, ((Library*)SysBase)->lib_Version, ((Library*)SysBase)->lib_Revision,
		dosName, ((Library*)DOSBase)->lib_Version, ((Library*)DOSBase)->lib_Revision,
		intName, ((Library*)IntuitionBase)->lib_Version, ((Library*)IntuitionBase)->lib_Revision,
		gfxName, ((Library*)GfxBase)->lib_Version, ((Library*)GfxBase)->lib_Revision,
		p96Name, ((Library*)P96Base)->lib_Version, ((Library*)P96Base)->lib_Revision,
		w3dName, ((Library*)Warp3DBase)->lib_Version, ((Library*)Warp3DBase)->lib_Revision
	);
}

void W3DUnitApp::logCPUInfo()
{
	uint64      cpuSpeed;
	uint64      cpuFSBSpeed;
	const char* cpuName;
	const char* cpuVersion;
	const char* cpuVectorUnit;
	const char* cpuExtensions;
	uint32      level1Cache;
	uint32      level2Cache;
	uint32      level3Cache;
	uint32      cpuVectorType;

	IExec->GetCPUInfoTags(
		GCIT_ProcessorSpeed, (uint32)&cpuSpeed,
		GCIT_FrontsideSpeed, (uint32)&cpuFSBSpeed,
		GCIT_ModelString,    (uint32)&cpuName,
		GCIT_VersionString,  (uint32)&cpuVersion,
		GCIT_VectorUnit,     (uint32)&cpuVectorType,
		GCIT_Extensions,     (uint32)&cpuExtensions,
		GCIT_L1CacheSize,    (uint32)&level1Cache,
		GCIT_L2CacheSize,    (uint32)&level2Cache,
		GCIT_L3CacheSize,    (uint32)&level3Cache,
		TAG_DONE
	);

	switch (cpuVectorType) {
		case VECTORTYPE_NONE:
			cpuVectorUnit = "None";
			break;

		case VECTORTYPE_ALTIVEC:
			cpuVectorUnit = "AltiVec (tm)";
			break;

		case VECTORTYPE_VMX:
			cpuVectorUnit = "IBM VMX";
			break;

		default:
			cpuVectorUnit = "Unknown";
			break;
	}

	Log::write(
		"\nProcessor information...\n"
		"\tCPU Type        : %s (Version %s)\n"
		"\tCPU Vector Unit : %s\n"
		"\tCPU Extensions  : %s\n"
		"\tCPU Speed       : %" PF_UINT64 " Hz\n"
		"\tFSB SPeed       : %" PF_UINT64 " Hz\n"
		"\tCache Config    : L1 %" PF_UINT32 " bytes, L2 %" PF_UINT32 " bytes, L3 %" PF_UINT32 " bytes\n"
		"",
		cpuName, cpuVersion,
		cpuVectorUnit,
		cpuExtensions,
		cpuSpeed,
		cpuFSBSpeed,
		level1Cache, level2Cache, level3Cache
	);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void W3DUnitApp::logDriverInfo()
{
	W3D_Driver** driverList = IWarp3D->W3D_GetDrivers();
	W3D_Driver*  driver = 0;

	Log::write(
		"\nChecking drivers...\n"
	);
	while ((driver = *driverList++)) {
		Log::write(
			"\tFound: %s (%s)\n",
			W3DEnums::getW3DChipType(driver->ChipID),
			driver->swdriver ? "Software" : "Hardware"
		);
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

W3DUnitApp::~W3DUnitApp()
{
	delete vertexBuffer;
	ContextFacade::destroy(contextFacade);
	Log::close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool W3DUnitApp::openLibraries()
{
	return
		openMainLibInterface(DOSBase,       IDOS,       dosName, 0) &&
		openMainLibInterface(IntuitionBase, IIntuition, intName, 0) &&
		openMainLibInterface(GfxBase,       IGraphics,  gfxName, 0) &&
		openMainLibInterface(P96Base,       IP96,       p96Name, 0) &&
		openMainLibInterface(Warp3DBase,    IWarp3D,    w3dName, 0)
	;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void W3DUnitApp::closeLibraries()
{
	closeMainLibInterface(Warp3DBase,    IWarp3D);
	closeMainLibInterface(P96Base,       IP96);
	closeMainLibInterface(GfxBase,       IGraphics);
	closeMainLibInterface(IntuitionBase, IIntuition);
	closeMainLibInterface(DOSBase,       IDOS);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void W3DUnitApp::parseParams()
{
	// this is where we set up the initial CLI stuff
	static int32 defWidth                = Param::DEFAULT_WIDTH;
	static int32 defHeight               = Param::DEFAULT_HEIGHT;
	setParamString(params[Param::PARAM_LOG_TO], Param::DEFAULT_LOGFILE);
	setParamInteger(params[Param::PARAM_WIDTH], defWidth);
	setParamInteger(params[Param::PARAM_HEIGHT],defHeight);
	readParams(params, Param::DEFAULT_TEMPLATE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

