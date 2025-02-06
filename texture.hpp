#ifndef _W3DTEST_TEXTURE_HPP_
#	define _W3DTEST_TEXTURE_HPP_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Texture {

	public:
		W3D_Texture* getTexture()        { return w3DTexture; }
		int          getWidth()    const { return width; }
		int          getHeight()   const { return height; }
		int          getBPP()      const { return bpp; }
		int          getFormat()   const { return format; }
		size_t       getDataSize() const { return size; }

		void         bindToContext(W3D_Context*);

		~Texture();

		static Texture* loadTexture(const char* fileName);

	private:
		Texture() : w3DContext(0), w3DTexture(0), data(0), size(0), width(0), height(0), bpp(0), format(0) { }

	private:
		W3D_Context* w3DContext;
		W3D_Texture* w3DTexture;
		void*        data;
		size_t       size;
		int16        width;
		int16        height;
		int16        bpp;
		int16        format;

};

#endif
