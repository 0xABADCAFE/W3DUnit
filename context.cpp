
#include "headers.hpp"
#include <cstdarg>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ContextFacade::ContextFacade() :
timer(),
screen(0), window(0), lockAddress(0), gfxAddress(0), chipType(0), flags(0), error(0), bgColour(0), vramSize(0), width(0), height(0), depth(0)
{
	buffer.screen[0] = 0;
	buffer.screen[1] = 0;
	titleBuffer[0]   = 0;
 	//Log::write("ContextFacade::Context()\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ContextFacade* ContextFacade::create(const char* name, int w, int h, int d, DisplayType type)
{
	// RAII
	ContextFacade* c  = new ContextFacade();
	bool opened = false;

	c->width  = w;
	c->height = h;
	c->depth  = d;

	if (type==WINDOWED) {
		opened = c->openWindowed();
	}
	else {
		opened = c->open(type);
	}
	if (opened) {
		c->setTitle(name);
	}
	else {
		throw Error::ResourceUnavailable("ContextFacade");
	}

	return c;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ContextFacade::~ContextFacade()
{
 	//Log::write("ContextFacade::~ContextFacade() : flags %08X\n", (unsigned)flags);

	if (flags & AC_FLAG_GOT_DISPLAY) {
		if (flags & AC_FLAG_WINDOWED) {
			closeWindowed();
		}
		else {
			close();
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::destroy(ContextFacade* c)
{
	delete c;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::logContextInfo()
{
	Log::write(
		"\nContext Information...\n"
		"\tDisplay Size  : %d x %d\n"
		"\tRender BitMap : %d x %d [modulus: %d] x %d [format: %s]\n"
		"\tChip Type     : %s\n"
		"\tScissor Rect  : %d, %d, %d, %d\n",
		(int)width,
		(int)height,
		(int)hwWidth,
		(int)hwHeight,
		(int)modulus,
		(int)depth,
		P96Enums::getP96PixelFormatName(pixFormat),
		getChipName(),
		clip.left,
		clip.top,
		clip.width,
		clip.height
	);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::logCapabilities()
{
	Log::write(
		"\nQuerying capabilities for current W3D_Context...\n"
	);

	size_t            num = numCapabilities;
	const Capability* cap = warp3DCapabilities;
	while (num--) {
		uint32 res = IWarp3D->W3D_Query(context, cap->code, (uint32)pixFormat);

		switch (cap->expect) {
			case Capability::EX_ENUM:
				Log::write(
					"\t%-21s : %s\n",
					cap->name,
					W3DEnums::getW3DQueryEnumName(res)
				);
				break;

			default:
				Log::write(
					"\t%-21s : %" PF_UINT32 "\n",
					cap->name,
					res
				);
				break;
		}
		++cap;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::logContextState()
{
	Log::write(
		"\nCurrent W3D_Context state...\n"
	);
	for (int i=1; i<32; i++) {
		uint32 flag = 1<<i;
		uint32 state = IWarp3D->W3D_GetState(context, flag);
		Log::write(
			"\t%-21s : %s\n",
			W3DEnums::getW3DStateBitName(i),
			W3DEnums::getW3DStateStatusName(state)
		);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::setTitle(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int num = vsnprintf(titleBuffer, sizeof(titleBuffer)-1, fmt, args);
	va_end(args);
	titleBuffer[num] = 0;
	if (flags & AC_FLAG_WINDOWED) {
		IIntuition->SetWindowTitles(window, titleBuffer, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int32 ContextFacade::showDialogue(const char* title, const char* opts, const char* fmt, ...)
{
	va_list argList;
	va_start(argList, fmt);
	vsnprintf(textBuffer, sizeof(textBuffer)-1, fmt, argList);
	va_end(argList);
	struct EasyStruct easy = {
		(uint32)sizeof(struct EasyStruct),
		0,
		title,
		textBuffer,
		opts,
		screen, // v50 struct Screen  *es_Screen
		0       // v50 struct TagItem *es_TagList
	};
	return IIntuition->EasyRequest(0, &easy, 0, argList);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::setFlatShadeColor(uint32 color)
{
	float32 f = 1.0/256.0;
	currentColor.r = f*((color & 0x00FF0000)>>16);
	currentColor.g = f*((color & 0x0000FF00)>>8);
	currentColor.b = f*((color & 0x000000FF));
	currentColor.a = f*((color & 0xFF000000)>>24);
	IWarp3D->W3D_SetCurrentColor(context, &currentColor);
}

void ContextFacade::clear(uint32 colour)
{
	if (flags & AC_FLAG_WINDOWED) {
		struct ViewPort* view = &(screen->ViewPort);
		uint32 pen;
		pen = IGraphics->ObtainBestPen(
			view->ColorMap,
			((colour&0x00FF0000)<<8),
			((colour&0x0000FF00)<<16),
			((colour&0x000000FF)<<24),
			OBP_Precision, PRECISION_EXACT,
			TAG_DONE
		);
		IGraphics->SetAPen(buffer.window.rastPort, pen);
		IGraphics->RectFill(buffer.window.rastPort, 0, 0, width-1,height-1);
		IGraphics->ReleasePen(view->ColorMap, pen);
		IGraphics->ClipBlit(
			buffer.window.rastPort, 0, 0,
			window->RPort,
			window->BorderLeft,
			window->BorderTop,
			width, height, 0xC0
		);
	}
}

void ContextFacade::refresh()
{
	if (flags & AC_FLAG_WINDOWED) {
		IGraphics->ClipBlit(
			buffer.window.rastPort, 0, 0,
			window->RPort,
			window->BorderLeft,
			window->BorderTop,
			width, height,
			0xC0
		);
	}
}

void* ContextFacade::lockDisplay(uint32 lockingFlags)
{
	if (lockingFlags & LOCKF_NO_INTERRUPT) {
		IExec->Disable();
		flags |= AC_LOCK_NO_INTERRUPT;
	}
	if (lockingFlags & LOCKF_NO_TASKSWITCH) {
		IExec->Forbid();
		flags |= AC_LOCK_NO_TASKSWITCH;
	}

	return context;
}

void ContextFacade::unlockDisplay()
{
	if (flags & LOCKF_NO_TASKSWITCH) {
		IExec->Permit();
		flags &= ~AC_LOCK_NO_TASKSWITCH;
	}

	if (flags & LOCKF_NO_INTERRUPT) {
		IExec->Enable();
		flags &= ~AC_LOCK_NO_INTERRUPT;
	}
}

void ContextFacade::setVertexGeometryArray(void* g, Vertex::Geometry::Format f)
{
/*
	IWarp3D->W3D_VertexPointer(context, g, VSTRIDE_GC, f, 0);
*/
	size_t stride = 0;
	switch(f) {
		case Vertex::Geometry::XYZ_FFF: stride = sizeof(Vertex::Geometry::FFF); break;
		case Vertex::Geometry::XYZ_FFD: stride = sizeof(Vertex::Geometry::FFD); break;
		case Vertex::Geometry::XYZ_DDD: stride = sizeof(Vertex::Geometry::DDD); break;
		default:
			throw Error::InvalidValue();
			break;
	}
	IWarp3D->W3D_VertexPointer(context, g, stride, f, 0);

}

void ContextFacade::setVertexColorArray(void* c, Vertex::Color::Format f, Vertex::Color::Type t)
{
	uint32 mode = f & (W3D_COLOR_FLOAT|W3D_COLOR_UBYTE);
	uint32 fmt  = f & (W3D_CMODE_RGB|W3D_CMODE_BGR|W3D_CMODE_RGBA|W3D_CMODE_ARGB|W3D_CMODE_BGRA);
	size_t stride = (mode & W3D_COLOR_UBYTE) ? sizeof(Vertex::Color::U) : sizeof(Vertex::Color::F);

	if (t==Vertex::Color::CT_NORMAL) {
		IWarp3D->W3D_ColorPointer(context, c, stride, mode, fmt, 0);
	}
	else {
		IWarp3D->W3D_SecondaryColorPointer(context, c, stride, mode, fmt, 0);
	}

/*
	uint32 mode = f & (W3D_COLOR_FLOAT|W3D_COLOR_UBYTE);
	uint32 fmt  = f & (W3D_CMODE_RGB|W3D_CMODE_BGR|W3D_CMODE_RGBA|W3D_CMODE_ARGB|W3D_CMODE_BGRA);

	if (t==Vertex::CT_NORMAL) {
		IWarp3D->W3D_ColorPointer(context, c, VSTRIDE_CC, mode, fmt, 0);
	}
	else {
		IWarp3D->W3D_SecondaryColorPointer(context, c, VSTRIDE_CC, mode, fmt, 0);
	}
*/
}

void ContextFacade::setVertexTextureArray(void* t, Vertex::TFormat f, int tmu)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  PRIVATE
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ContextFacade::createWarp3DContext()
{
	BitMap* w3dBitMap = flags & AC_FLAG_WINDOWED ? buffer.window.bitMap : buffer.screen[1]->sb_BitMap;
	uint32  error = 0;

	if (!(context = IWarp3D->W3D_CreateContextTags(
		&error,
		W3D_CC_BITMAP,     (uint32)w3dBitMap,
		W3D_CC_DRIVERTYPE, (uint32)W3D_DRIVER_BEST,
		W3D_CC_FAST,       (uint32)true,
		W3D_CC_YOFFSET,    (uint32)0
	))) {
		Log::write("W3D_CreateContext() failed to create a context [%" PF_UINT32 "]\n", error);
		return false;
	}
	clip.left   = 0;
	clip.top    = 0;
	clip.width  = width;
	clip.height = height;

	numTMU = IWarp3D->W3D_Query(context, W3D_Q_NUM_TMU, (uint32)pixFormat);

	IWarp3D->W3D_SetDrawRegion(context, w3dBitMap, 0, &clip);
	IWarp3D->W3D_SetScissor(context, &clip);
	IWarp3D->W3D_SetState(context, W3D_SCISSOR, W3D_ENABLE);
	IWarp3D->W3D_SetState(context, W3D_DITHERING, W3D_DISABLE);
	IWarp3D->W3D_SetState(context, W3D_GOURAUD, W3D_DISABLE);
	IWarp3D->W3D_SetState(context, W3D_TEXMAPPING, W3D_DISABLE);
	IWarp3D->W3D_SetState(context, W3D_BLENDING, W3D_DISABLE);
	IWarp3D->W3D_SetState(context, W3D_ZBUFFER, W3D_DISABLE);
	IWarp3D->W3D_SetState(context, W3D_GLOBALTEXENV, W3D_DISABLE);
	IWarp3D->W3D_SetBlendMode(context, W3D_SRC_ALPHA, W3D_ONE_MINUS_SRC_ALPHA);

	chipType = context->CurrentChip;

	if (chipType > W3D_CHIP_RADEON_R300) {
		chipType = W3D_CHIP_UNKNOWN;
	}

	if ((error = IWarp3D->W3D_AllocZBuffer(context))==W3D_SUCCESS) {
		flags |= AC_FLAG_GOTZBUFFER;
	}
	else {
		Log::write("W3D_AllocZBuffer() failed to create a z-buffer [%" PF_UINT32 "]\n", error);
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::destroyWarp3DContext()
{
	if (context) {
		//IWarp3D->W3D_FreeAllTexObj(context);
		if (flags & AC_FLAG_GOTZBUFFER) {
		IWarp3D->W3D_FreeZBuffer(context);
		}
		IWarp3D->W3D_DestroyContext(context);
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ContextFacade::openWindowed()
{
	struct Screen*    tmpScreen = 0;
	struct Window*    tmpWindow = 0;
	struct RastPort*  tmpRPort  = 0;
	struct BitMap*    tmpBitMap = 0;
	int32  lock = 0;

	struct RenderInfo renderInfo;

	int16 screenW, screenH, screenD, screenF, winX, winY;

 	//Log::write("ContextFacade::openWindowed()\n");


	if (!(tmpScreen = IIntuition->LockPubScreen(0))) {
		Log::write("LockPubScreen() failed to lock default public screen\n");
		goto failed;
	}
	if (!IP96->p96GetBitMapAttr(tmpScreen->RastPort.BitMap, P96BMA_ISP96)) {
		Log::write("Screen BitMap seems not to be Picasso96 compatible\n");
		goto failed;
	}

	screenW = IP96->p96GetBitMapAttr(tmpScreen->RastPort.BitMap, P96BMA_WIDTH);
	screenH = IP96->p96GetBitMapAttr(tmpScreen->RastPort.BitMap, P96BMA_HEIGHT);
	screenD = IP96->p96GetBitMapAttr(tmpScreen->RastPort.BitMap, P96BMA_BYTESPERPIXEL)<<3; // the real value
	screenF = IP96->p96GetBitMapAttr(tmpScreen->RastPort.BitMap, P96BMA_RGBFORMAT);

	// depth check
	if (screenD<depth) {
		Log::write(
			"Screen depth %" PF_INT16 " is less than requested depth of %" PF_INT16 "\n",
			screenD,
			depth
		);
		goto failed;
	}

	// size check
	if (screenW<width || screenH<height) {
		Log::write(
			"Screen size %" PF_INT16 "x%" PF_INT16 " is less than requested size of %" PF_INT16 "x%" PF_INT16 "\n",
			screenW, screenH,
			width, height
		);
		goto failed;
	}

	// get rastport
	if (!(tmpRPort = (struct RastPort*)IExec->AllocVec(sizeof(struct RastPort), MEMF_FAST))) {
		Log::write("Failed to allocate RastPort for windowed display\n");
		goto failed;
	}
	IGraphics->InitRastPort(tmpRPort);

 	//Log::write("Allocated RastPort at %p\n", tmpRPort);

	// allocate a BitMap for rendering

	if ( !(tmpBitMap = IGraphics->AllocBitMap(width, height, 8, BMF_DISPLAYABLE, tmpScreen->RastPort.BitMap)) ) {
		Log::write("Failed to allocate BitMap\n");
		goto failed;
	}
	tmpRPort->BitMap = tmpBitMap;

	// open window
	winX = (screenW-width)>>1;
	winY = (screenH-height)>>1;

	tmpWindow = IIntuition->OpenWindowTags(
		0,
		WA_PubScreen,   (uint32)tmpScreen,
		WA_InnerWidth,  (uint32)width,
		WA_InnerHeight, (uint32)height,
		WA_Left,        (uint32)winX,
		WA_Top,         (uint32)winY,
		WA_Title,       (uint32)titleBuffer,
		WA_DepthGadget, (uint32)true,
		WA_Flags,       WFLG_DRAGBAR|/*WFLG_REPORTMOUSE|WFLG_RMBTRAP|*/WFLG_ACTIVATE,
		TAG_DONE
	);

	if (!tmpWindow) {
		Log::write("Failed to open window\n");
		goto failed;
	}

	IIntuition->UnlockPubScreen(0, tmpScreen);

	// if we get here, all is well
	screen                 = tmpScreen;
  window                 = tmpWindow;
	depth                  = screenD;
	pixFormat              = screenF;
	buffer.window.rastPort = tmpRPort;
	buffer.window.bitMap   = tmpBitMap;

	// get the bitmap properties
/*
struct RenderInfo {
	APTR			Memory;
	WORD			BytesPerRow;
	WORD			pad;
	RGBFTYPE		RGBFormat;
};
*/

	if ( (lock = IP96->p96LockBitMap(tmpBitMap, (uint8*)&renderInfo, sizeof(struct RenderInfo))) ) {
		hwWidth                = IP96->p96GetBitMapAttr(tmpBitMap, P96BMA_WIDTH);
		hwHeight               = IP96->p96GetBitMapAttr(tmpBitMap, P96BMA_HEIGHT);
		bytesPerPix            = IP96->p96GetBitMapAttr(tmpBitMap, P96BMA_BYTESPERPIXEL);
		modulus                = (IP96->p96GetBitMapAttr(tmpBitMap, P96BMA_BYTESPERROW)/bytesPerPix)-width;
		IP96->p96UnlockBitMap(tmpBitMap, lock);
	}
	else {
	 	Log::write("Couldn't inspect BitMap at %p\n");
		goto failed;
	}

	flags = AC_FLAG_WINDOWED|AC_FLAG_GOT_DISPLAY;

	if (!createWarp3DContext()) {
		goto failed;
	}

	clear(0x00000000);
	refresh();

	return true;

failed:
	if (tmpBitMap) {
		IGraphics->FreeBitMap(tmpBitMap);
	}
	if (tmpRPort) {
		IExec->FreeVec(tmpRPort);
	}
	if (tmpWindow) {
		IIntuition->CloseWindow(tmpWindow);
	}
	if (tmpScreen) {
		IIntuition->UnlockPubScreen(0, tmpScreen);
	}

	flags                  = 0;
	screen                 = 0;
  window                 = 0;
	depth                  = 0;
	pixFormat              = 0;
	buffer.window.rastPort = 0;
	buffer.window.bitMap   = 0;

	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::closeWindowed()
{
 	//Log::write("ContextFacade::closeWindowed()\n");

	destroyWarp3DContext();

	if (buffer.window.bitMap) {
	 	//Log::write("Releasing BitMap at %p\n", buffer.window.bitMap);
		IGraphics->FreeBitMap(buffer.window.bitMap);
		buffer.window.bitMap = 0;
	}
	if (buffer.window.rastPort) {
	 	//Log::write("Releasing RastPort at %p\n", buffer.window.rastPort);
		IExec->FreeVec(buffer.window.rastPort);
		buffer.window.rastPort = 0;
	}
	if (window) {
	 	//Log::write("Closing Window at %p\n", window);
		IIntuition->CloseWindow(window);
		window = 0;
	}
	screen = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ContextFacade::open(int buffers)
{
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContextFacade::close()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



