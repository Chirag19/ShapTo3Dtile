#include <cstdio>
#include <string>
#include "help.h"

#include <boost/filesystem.hpp>

//using namespace boost::filesystem;
static fstream ofs;

bool write_file(string filename, const char* buf, unsigned long buf_len) {

	FILE* f = fopen(filename.c_str(), "wb");
	if (!f) return false;
	fwrite(buf, 1, buf_len, f);
	fclose(f);

	/*ofs.open(filename.c_str(), std::ios::app);
	if (!ofs)
	{
		std::cerr << "Could not open " << filename << "." << std::endl;
		exit(1);
	}

	ofs << buf << endl;

	ofs.close();*/
	return true;

	
}

void log_error(const char* msg) {

}