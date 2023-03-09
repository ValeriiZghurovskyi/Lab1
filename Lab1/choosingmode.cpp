#include <iostream>
#include <string>


int mode(int argc, char* argv[]) {

	if (argc == 3 && (!strcmp(argv[1], "-mode"))) {
		if (!strcmp(argv[2], "FilePointer")) {
			return 1;
		}
		else if (!strcmp(argv[2], "FileStream")) {
			return 2;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}

}