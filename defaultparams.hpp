
#ifndef _W3DTEST_ARGUMENTS_HPP_
#	define _W3DTEST_ARGUMENTS_HPP_

namespace Param {

	// Parameter item order
	typedef enum {
		PARAM_LOG_TO = 0,
		PARAM_WIDTH  = 1,
		PARAM_HEIGHT = 2,
		_MAX_PARAMS
	} PNum;

	// Default values
	enum {
		DEFAULT_WIDTH  = 640,
		DEFAULT_HEIGHT = 480
	};
	extern const char* DEFAULT_LOGFILE;
	extern const char* DEFAULT_TEMPLATE;

	// Parameter instance (wrapper for ReadArgs output)
	typedef union {
		public:
			int32       getInteger() const  { return *pInteger; }
			bool        getSwitch()  const  { return integer!=0; }
			const char* getString()  const  { return pString; }

		private:
			int32        integer;
			int32*       pInteger;
			const char*  pString;
			friend class ItemDefaulter;
	} Item;

	class ItemDefaulter {
		private:
			RDArgs* rdArgs;
		protected:
			void setParamString(Item& item, const char* strVal) { item.pString = strVal; }
			void setParamInteger(Item& item, int32& intVal)     { item.pInteger = &intVal; }
			void readParams(Item* items, const char* tmpl);

			ItemDefaulter() : rdArgs(0) {}

		public:
			~ItemDefaulter();
	};
}

#endif
