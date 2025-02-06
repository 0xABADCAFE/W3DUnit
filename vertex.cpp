
#include "headers.hpp"

Vertex::Buffer::Buffer(size_t num, int32 tmu) : geometry(0)
{
	// make a single allocationm large enough for everything
	if (tmu<1 || tmu>W3D_MAX_TMU || num<6) {
		throw new Error::InvalidValue();
	}

	numVerts = num;

	size_t allocSize = numVerts*(sizeof(Geometry::DDD) + 2*sizeof(Color::F) + tmu*sizeof(Texture) + sizeof(float64) + sizeof(uint32));

	uint8* buffer = (uint8*)IExec->AllocVec(allocSize, MEMF_PRIVATE|MEMF_CLEAR);
	if (buffer) {
		Log::write(
			"\nVertex::Buffer allocation...\n"
			"\t%" PF_UINT32 " vertices allocated\n"
			"\t%" PF_UINT32 " bytes for %" PF_INT32 " Geometry coordinate array(s)\n"
			"\t%" PF_UINT32 " bytes for %" PF_INT32 " Color coordinate array(s)\n"
			"\t%" PF_UINT32 " bytes for %" PF_INT32 " Fog coordinate array(s)\n"
			"\t%" PF_UINT32 " bytes for %" PF_INT32 " Texture coordinate array(s)\n"
			"\t%" PF_UINT32 " bytes for %" PF_INT32 " Index buffer(s)\n"
			"\t%" PF_UINT32 " bytes total\n",
			(uint32)numVerts,
			(uint32)(numVerts*sizeof(Geometry::DDD)), 1,
			(uint32)(numVerts*2*sizeof(Color::F)), 2,
			(uint32)(numVerts*sizeof(float64)), 1,
			(uint32)(numVerts*tmu*sizeof(Texture)), tmu,
			(uint32)(numVerts*sizeof(uint32)), 1,
			(uint32)allocSize
		);

		numTMU   = tmu;
		geometry = buffer; buffer += numVerts*sizeof(Geometry::DDD);
		color[0] = buffer; buffer += numVerts*sizeof(Color::F);
		color[1] = buffer; buffer += numVerts*sizeof(Color::F);
		fog      = buffer; buffer += numVerts*sizeof(float64);
		for (int32 i=0; i<tmu; i++) {
			texture[i] = buffer; buffer += numVerts*sizeof(Texture);
		}
		for (int32 i=tmu; i<W3D_MAX_TMU; i++) {
			texture[i] = 0;
		}
		indexes = buffer;
	}
	else {
		throw new Error::ResourceUnavailable("Vertex::Buffer");
	}
}

Vertex::Buffer::~Buffer()
{
	if (geometry) {
		IExec->FreeVec(geometry);
	}
}

Vertex::Texture* Vertex::Buffer::getTexture(int32 i)
{
	if (i<0 || i>=numTMU) {
		throw new Error::InvalidValue();
	}
	return (Texture*)texture[i];
}
