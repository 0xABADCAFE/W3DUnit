#ifndef _W3DTEST_CONTEXT_HPP_
#	define _W3DTEST_CONTEXT_HPP_

namespace Dialogue {
	extern const char* TITLE_ERROR;
	extern const char* TITLE_INFO;
	extern const char* TITLE_QUERY;
	extern const char* OPTS_YES_NO;
	extern const char* OPTS_PROCEED;
	extern const char* OPTS_CANCEL;
};

class ContextFacade {

	public:
		typedef enum {
			WINDOWED      = 0,
			FULLSCREEN_SB = 1,
			FULLSCREEN_DB = 2,
			FULLSCREEN_TB = 3
		} DisplayType;

		enum {
			LOCKF_NO_TASKSWITCH = 1,
			LOCKF_NO_INTERRUPT  = 2
		};

		// factory - a returned context should be fully constructed
		// at least as far as having an open display, allocated and configured W3D_Context
		static ContextFacade* create(const char* name, int w, int h, int d, DisplayType type);
		static void           destroy(ContextFacade* c);
		~ContextFacade();

		const char*  getChipName()        const { return W3DEnums::getW3DChipType(chipType); }
		size_t       getVRAMSize()        const { return vramSize; }
		int16        getWidth()           const { return width; }
		int16        getHeight()          const { return height; }
		int16        getHWWidth()         const { return hwWidth; }
		int16        getHWWeight()        const { return hwHeight; }
		int16        getBytesPerPix()     const { return bytesPerPix; }
		int32        getPixelFormat()     const { return pixFormat; }
		int32        getNumTMU()          const { return numTMU; }

		bool         haveZBuffer()        const { return (flags & AC_FLAG_GOTZBUFFER) ? true : false; }
		bool         haveStencilBuffer()  const { return (flags & AC_FLAG_GOTSTENCILBUFFER) ? true : false; }


		void         logContextInfo();
		void         logCapabilities();
		void         logContextState();

		// mutators
		void         setTitle(const char* title, ...);
		void         setFlatShadeColor(uint32 colour);
		void         clear(uint32 colour);
		void*        lockDisplay(uint32 lockingFlags);
		void         unlockDisplay();
		void         refresh();

		void setVertexGeometryArray(void* g, Vertex::Geometry::Format f);
		void setVertexColorArray(void* c, Vertex::Color::Format f, Vertex::Color::Type t);
		void setVertexTextureArray(void* t, Vertex::TFormat f, int tmu);

		void setVertexGeometryArray(Vertex::Geometry::FFF* g)
		{
			IWarp3D->W3D_VertexPointer(context, g, sizeof(Vertex::Geometry::FFF), W3D_VERTEX_F_F_F, 0);
		}

		void setVertexGeometryArray(Vertex::Geometry::FFD* g)
		{
			IWarp3D->W3D_VertexPointer(context, g, sizeof(Vertex::Geometry::FFD), W3D_VERTEX_F_F_D, 0);
		}

		void setVertexGeometryArray(Vertex::Geometry::DDD* g)
		{
			IWarp3D->W3D_VertexPointer(context, g, sizeof(Vertex::Geometry::FFF), W3D_VERTEX_D_D_D, 0);
		}

/*
		void setVertexGeometryArray(Vertex::Geometry* g, Vertex::VFormat f);
		void setVertexColourArray(Vertex::Color* c, Vertex::CFormat f, Vertex::CType t);
		void setVertexTextureArray(Vertex::Texture* t, Vertex::TFormat f, int tmu);
*/
		W3D_Context* getW3DContext()         { return context; }

		// open an intuition requester
		int32        showDialogue(const char* title, const char* opts, const char* fmt, ...);

	private:

		enum {
			AC_LOCK_NO_TASKSWITCH    = LOCKF_NO_TASKSWITCH,
			AC_LOCK_NO_INTERRUPT     = LOCKF_NO_INTERRUPT,
			AC_LOCK_MASK             = LOCKF_NO_TASKSWITCH|LOCKF_NO_INTERRUPT,
			AC_FLAG_GOT_DISPLAY      = 0x0000004,
			AC_FLAG_WINDOWED         = 0x0000008,
			AC_FLAG_GOTZBUFFER       = 0x0000010,
			AC_FLAG_GOTSTENCILBUFFER = 0x0000020,
		};

		ContextFacade();

		bool openWindowed();
		void closeWindowed();
		bool open(int buffers);
		void close();


		bool createWarp3DContext();
		void destroyWarp3DContext();

	private: // data
		Timer   timer;
		// display
		Screen*	screen;
		Window*	window;
		union {
			struct ScreenBuffer* screen[2];	// fullscreen only
			struct {
				struct RastPort*	rastPort;
				struct BitMap*		bitMap;
			} window;												// windowed only
		} buffer;
		void*         lockAddress;
		void*         gfxAddress;
		uint32        chipType;
		uint32        flags;
		uint32        error;
		uint32        bgColour;
		uint32        vramSize;

		// warp3d stuff
		W3D_Context*  context;
		W3D_Scissor   clip;
		W3D_Color     currentColor;
		uint32        numTMU;

		// requested properties
		int16         width;
		int16         height;
		int16         depth;

		// post initialisation values
		int16         pixFormat;
		int16         hwWidth;
		int16         hwHeight;
		int16         bytesPerPix;
		int16         modulus;

		char          textBuffer[8192];
		char          titleBuffer[1024];

		struct Capability {
			enum {
				EX_UNKNOWN = 0,
				EX_ENUM    = 1,
				EX_UINT32  = 2
			};
			const char* name;
			uint16      code;
			uint16      expect;
		};


		static const Capability warp3DCapabilities[];
		static size_t           numCapabilities;
};


#endif
