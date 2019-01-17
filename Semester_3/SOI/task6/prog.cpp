#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define DEFAULT_DISK ".x" 

using namespace std;

bool isset(const char *fileName){
	ifstream f;
	f.open( fileName );
	return f.good();
}

int mkdisk(unsigned int capacity, const char *diskName);

int put(const char *filePath, const char *targetName="", const char *diskName=DEFAULT_DISK);

int get(const char *diskFileName, const char *targetPath, const char *diskName);

int ls();

int lsdisk(const char *diskName);

int rm(const char *fileName, const char *diskName);

int rmdisk(const char *diskName);

int info(const char *diskName);

int main(int argc, const char *argv[]){
	if(argc < 2){
		return -1;
	}
	switch( atoi(argv[1]) ){
		case 0:
			if( argc < 3){
				return -1;
			}
			return mkdisk( atoi(argv[2]), (argc == 4)?argv[3]:DEFAULT_DISK );
		case 1:
			switch( argc ){
				case 3:
					return put( argv[2] );
				case 4:
					return put( argv[2], argv[3] );
				case 5:
					return put( argv[2], argv[3], argv[4] );
				default:
					return -1;
			}
			break;
		case 2:
			if( argc < 4 ){
				return -1;
			}	
			return get( argv[2], argv[3], (argc == 5)?argv[4]:DEFAULT_DISK );
		case 3:
			return ls();
		case 4:
			return lsdisk( (argc == 3)?argv[2]:DEFAULT_DISK );
		case 5:
			if( argc < 3 ){
				return -1;
			}
			return rm( argv[2], (argc == 4)?argv[3]:DEFAULT_DISK );
		case 6:
			return rmdisk( (argc == 3)?argv[2]:DEFAULT_DISK );
		case 7:
			return info( (argc == 3)?argv[2]:DEFAULT_DISK );
	}
	return 0;
}
