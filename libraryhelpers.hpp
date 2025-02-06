
#ifndef _W3DTEST_LIBRARYHELPER_HPP_
#	define _W3DTEST_LIBRARYHELPER_HPP_

template<typename L, typename I>
inline bool openMainLibInterface(L*& library, I*& interface, const char* name, uint32 version)
{
	if ( (library = (L*)IExec->OpenLibrary(name, version)) ) {
		if ( (interface = (I*)IExec->GetInterface((Library*)library, "main", 1, NULL)) ) {
			return true;
		}
		else {
			std::fprintf(stderr, "Opened %s [%p] but failed to get main\n", name, library);
		}
	}
	else {
		std::fprintf(stderr, "Failed to open: %s\n", name);
	}
	return false;
}

template<typename L, typename I>
inline void closeMainLibInterface(L*& library, I*& interface)
{
	if (interface) {
		IExec->DropInterface((Interface*)interface);
		interface = 0;
	}
	if (library) {
		IExec->CloseLibrary((Library*)library);
		library = 0;
	}
}

#endif
