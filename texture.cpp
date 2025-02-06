#include "headers.hpp"

#include <cstdio>
#include <cstring>
#include <memory>

Texture* Texture::loadTexture(const char* fileName)
{

	Texture*      res  = 0;
	void*         data = 0;
	std::FILE*    file = 0;
	size_t        dataSize   = 0;
	int16         info[4]    = {0};
	char          header[12] = {0};

	if (!fileName) {
		Log::write("No filename given\n");
		return 0;
	}
	if (!(file=std::fopen(fileName, "rb"))) {
		Log::write("File '%s' could not be opened\n", fileName);
		return 0;
	}
	if (std::fread(header, 1, 8, file)!=8 || std::strcmp(header, "teximage")!=0) {
		Log::write("File '%s' doesn't seem to be a texture file\n", fileName);
		goto bugger;
	}
	if (std::fread(info, 2, 4, file)!=4) {
		Log::write("File '%s' texture info invalid\n", fileName);
		goto bugger;
	}

	if (info[0]<4 || info[0]>512) {
		Log::write("File '%s' texture info gave screwy width\n", fileName);
		goto bugger;
	}
	if (info[1]<4 || info[1]>512) {
		Log::write("File '%s' texture info gave screwy height\n", fileName);
		goto bugger;
	}

	if (info[2]<1 || info[2]>4) {
		Log::write("File '%s' texture info gave screwy bytes per pixel\n", fileName);
		goto bugger;
	}

	dataSize = info[0]*info[1]*info[2];

	if (!(res = new(std::nothrow)Texture)) {
		Log::write("Couldn't instantiate Texture instance\n");
		goto bugger;
	}

	if (!(data = IExec->AllocVec(dataSize, MEMF_FAST|MEMF_CLEAR))) {
		Log::write("Couldn't allocate %lu bytes for texel data\n", (uint32)dataSize);
		goto bugger;
	}

	if (dataSize!=(std::fread(data, 1, dataSize, file))) {
		Log::write("File '%s' ended unexpectedly\n", fileName);
		goto bugger;
	}

	res->data   = data;
	res->size 	= dataSize;
	res->width	= info[0];
	res->height = info[1];
	res->bpp		= info[2];
	res->format = info[3];
	std::fclose(file);

	return res;

bugger:
	if (file) {
		std::fclose(file);
	}
	if (data) {
		IExec->FreeVec(data);
	}
	if (res) {
		delete res;
	}
	return 0;
}

Texture::~Texture()
{
	if (w3DTexture) {
		IWarp3D->W3D_FreeTexObj(w3DContext, w3DTexture);
	}
	if (data) {
		IExec->FreeVec(data);
	}
}

void Texture::bindToContext(W3D_Context*)
{

}

