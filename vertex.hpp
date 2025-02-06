
#ifndef _W3DTEST_VERTEX_HPP_
#	define _W3DTEST_VERTEX_HPP_

namespace Vertex {

	typedef enum {
		TEX_UVW = 0,
		TEX_STW,
		_TEX_NUM
	} TFormat;

	namespace Geometry {

		typedef enum {
			// type wrapper for W3D geometry layout
			XYZ_FFF	= W3D_VERTEX_F_F_F,
			XYZ_FFD = W3D_VERTEX_F_F_D,
			XYZ_DDD = W3D_VERTEX_D_D_D,
			_XYZ_NUM = 3
		} Format;

		struct FFF {
			float32 x, y, z;
		};
		struct FFD {
			float32 x, y;
			float64 z;
		};
		struct DDD {
			float64 x, y, z;
		};
	};

	namespace Color {
		enum {
			// offsets
			RGB_R = 0,
			RGB_G = 1,
			RGB_B = 2,

			BGR_R = 2,
			BGR_G = 1,
			BGR_B = 0,

			RGBA_R = 0,
			RGBA_G = 1,
			RGBA_B = 2,
			RGBA_A = 3,

			ARGB_R = 1,
			ARGB_G = 2,
			ARGB_B = 3,
			ARGB_A = 0,

			BGRA_R = 2,
			BGRA_G = 1,
			BGRA_B = 0,
			BGRA_A = 3
		};

		typedef enum {
			// type wrapper for W3D geometry layout
			CLR_URGB   = W3D_COLOR_UBYTE|W3D_CMODE_RGB,
			CLR_UBGR   = W3D_COLOR_UBYTE|W3D_CMODE_BGR,
			CLR_URGBA  = W3D_COLOR_UBYTE|W3D_CMODE_RGBA,
			CLR_UARGB  = W3D_COLOR_UBYTE|W3D_CMODE_ARGB,
			CLR_UBGRA  = W3D_COLOR_UBYTE|W3D_CMODE_BGRA,
			CLR_FRGB   = W3D_COLOR_FLOAT|W3D_CMODE_RGB,
			CLR_FBGR   = W3D_COLOR_FLOAT|W3D_CMODE_BGR,
			CLR_FRGBA  = W3D_COLOR_FLOAT|W3D_CMODE_RGBA,
			CLR_FARGB  = W3D_COLOR_FLOAT|W3D_CMODE_ARGB,
			CLR_FBGRA  = W3D_COLOR_FLOAT|W3D_CMODE_BGRA,
			_CLR_NUM   = 10
		} Format;

		typedef enum {
			CT_NORMAL   = 0,
			CT_SPECULAR = 1
		} Type;

		union U {
			uint32 rgba32;
			uint32 argb32;
			uint32 bgra32;

			struct { uint8   r, g, b, _pad; } rgb;
			struct { uint8   b, g, r, _pad; } bgr;
			struct { uint8   r, g, b, a; }    rgba;
			struct { uint8   a, r, g, b; }    argb;
			struct { uint8   b, g, r, a; }    bgra;
		};

		union F {
			struct { float32 r, g, b; }       rgb;
			struct { float32 b, g, r; }       bgr;
			struct { float32 r, g, b, a; }    rgba;
			struct { float32 a, r, g, b; }    argb;
			struct { float32 b, g, r, a; }    bgra;
		};
	};

	union Texture {
		struct { float32 u, v, w; } uvw;
		struct { float32 s, t, w; } stw;
	};

	class Buffer {
		public:
			Buffer(size_t numVerts, int32 tmu);
			~Buffer();

			size_t         getBufferSize()      { return numVerts; }

			Geometry::FFF* getGeometryFFF()     { return (Geometry::FFF*)geometry; }
			Geometry::FFD* getGeometryFFD()     { return (Geometry::FFD*)geometry; }
			Geometry::DDD* getGeometryDDD()     { return (Geometry::DDD*)geometry; }
			void*          getGeometryRaw()     { return geometry; }

			Color::U*      getColorU(Color::Type t)   { return (Color::U*)color[t]; }
			Color::F*      getColorF(Color::Type t)   { return (Color::F*)color[t]; }
			void*          getColorRaw(Color::Type t) { return color[t]; }

			float32*       getFogF()            { return (float32*)fog; }
			float64*       getFogD()            { return (float64*)fog; }

			uint8*         getIndexU8()         { return (uint8*)indexes; }
			uint16*        getIndexU16()        { return (uint16*)indexes; }
			uint32*        getIndexU32()        { return (uint32*)indexes; }


			Texture*     getTexture(int32 i);

		private:
			void*     geometry;
			void*     color[2];
			void*     texture[W3D_MAX_TMU];
			void*     fog;
			void*     indexes;
			size_t    numVerts;
			int32     numTMU;
	};

};

#endif
