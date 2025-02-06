
#ifndef _W3DTEST_ERROR_HPP_
#	define _W3DTEST_ERROR_HPP_


namespace Error {
	class Runtime;
	class Resource;
	class ResourceUnavailable;
	class InvalidValue;
/*
	class NullPointer  : public Runtime {};
	class ZeroDivide;
	class IllegalAddress;
	class BadAlignment;
	class Range;
	class ObjectModified;
	class ObjectDestroyed;
	class ObjectStateViolation;
	class Resource;
	class ResourceInvalid;
	class ResourceExhausted;
	class ResourceUnavailable;
	class ResourceLocked;
	class ResourceVersion;
*/
};

class Error::Runtime { public: virtual const char* getClass() const; };

class Error::InvalidValue : public Error::Runtime {};


class Error::Resource : public Error::Runtime {
	private:
		const char* resName;
	public:
		const char* getName() const { return resName; }
		Resource(const char* name) : resName(name) {}
};

class Error::ResourceUnavailable : public Error::Resource { public: ResourceUnavailable(const char* name) : Resource(name) {} };


#endif
