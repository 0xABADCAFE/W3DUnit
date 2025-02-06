
#include "headers.hpp"

int main(int argn, char** argv)
{
	int32 retval = 10;
	W3DUnitApp* app = W3DUnitApp::getInstance();
	if (app) {
		retval = app->run();
	}
	W3DUnitApp::destroyInstance();
	return retval;
}
