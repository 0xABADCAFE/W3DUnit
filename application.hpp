
#ifndef _W3DTEST_APP_HPP_
#	define _W3DTEST_APP_HPP_

class W3DUnitApp : private Param::ItemDefaulter {

	public:
		// singleton. Always call destroyInstance() as it performs additional cleanup
		static W3DUnitApp*   getInstance();
		static void          destroyInstance();
		const  Param::Item*  getParam(Param::PNum p) const
		{
			if (p < Param::_MAX_PARAMS) {
				return &params[p];
			}
			return 0;
		}

		int32 run();

		~W3DUnitApp();

	private:
		// these are called outside the instantiation of the singleton to
		// ensure that all the required libraries are open before we do
		// anything that might need them
		static bool openLibraries();
		static void closeLibraries();
		void        parseParams();

		void        logLibraryInfo();
		void        logCPUInfo();
		void        logDriverInfo();

	private:
		// singleton
		W3DUnitApp();
		static W3DUnitApp* instance;
		Param::Item        params[Param::_MAX_PARAMS];
		ContextFacade*     contextFacade;
		Vertex::Buffer*    vertexBuffer;
};

#endif
