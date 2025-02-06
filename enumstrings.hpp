#ifndef _W3DTEST_ENUMSTRINGS_HPP_
#	define _W3DTEST_ENUMSTRINGS_HPP_

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class P96Enums {
	public:
		static const char* getP96PixelFormatName(int32 format);

	private:
		static const char* p96PixelModeNames[];
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class W3DEnums {
	public:
		static const char* getW3DChipType(uint32 val);
		static const char* getW3DStatusName(uint32 val);
		static const char* getW3DQueryEnumName(uint32 val);
		static const char* getW3DStateStatusName(uint32 state);
		static const char* getW3DStateFlagName(uint32 val);
		static const char* getW3DStateBitName(uint32 val);

		static const char* getW3DBlendModeName(uint32 val);
		static const char* getW3DTextureFilterName(uint32 val);
		static const char* getW3DFogModeName(uint32 val);
		static const char* getW3DTextureEnvName(uint32 val);
		static const char* getW3DTextureWrapName(uint32 val);
		static const char* getW3DAlphaTestName(uint32 val);
		static const char* getW3DZTestName(uint32 val);
		static const char* getW3DLogicOpName(uint32 val);
		static const char* getW3DStencilTestName(uint32 val);
		static const char* getW3DStencilUpdateName(uint32 val);
		static const char* getW3DChromaTestName(uint32 val);

	private:
		static const char* warp3DChipNames[];
		static const char* warp3DStatusItems[];
		static const char* warp3DStateStatusEnumItems[];
		static const char* warp3DQueryResultEnumItems[];
		static const char* warp3DStateFlagNames[];
		static const char* warp3DBlendModeNames[];
		static const char* warp3DTextureFilterNames[];
		static const char* warp3DFogModeNames[];
		static const char* warp3DTextureEnvNames[];
		static const char* warp3DTextureWrapNames[];
		static const char* warp3DAlphaTestNames[];
		static const char* warp3DZTestNames[];
		static const char* warp3DLogicOpNames[];
		static const char* warp3DStencilTestNames[];
		static const char* warp3DStencilUpdateNames[];
		static const char* warp3DChromaTestNames[];
};

#endif
