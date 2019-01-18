#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#define DEFAULT_DISK 	".x" 
#define INFO_SIZE	256

using namespace std;

bool isset(const char *fileName){
	ifstream f;
	f.open( fileName );
	return f.good();
}

int mkdisk(unsigned int capacity, const char *diskName){
	if( isset(diskName) ){
		return 1;
	}
	fstream disk;
	disk.open(diskName, fstream::out | fstream::binary );
	char x = 0;
	int xInt = 0, blocksNum = 1, infoSize = (capacity / 4096);
	disk<<capacity<<infoSize<<blocksNum;
	//adres (int), rozmiar (int), typ obszaru (plik/wolny blok)(char), nazwa pliku (dla plików)(char[23]) 
	disk<<xInt<<capacity<<x;
	for(int i = 0; i < 23; ++i){
		disk<<x;
	}
	unsigned int max = capacity+(infoSize-1)*INFO_SIZE;
	for(unsigned int i = 0; i < max; ++i){
		disk << x;
	}
	return 0;
}

int put(const char *filePath, const char *targetName="", const char *diskName=DEFAULT_DISK){
	fstream file, disk;
	if(!isset(filePath) || !isset(diskName)){
		return 1;
	}
	file.open(filePath, fstream::in | fstream::binary);
	disk.open(diskName, fstream::in | fstream::out | fstream::binary);
	
	int capacity, headerSize, blocksNum;
	disk>>capacity>>headerSize>>blocksNum;
	disk.seekg(21);//header+gotoName
	
	if(strcmp(targetName, "") == 0){
		targetName = filePath;
	}
	char name[23];
	//adres (int), rozmiar (int), typ obszaru (plik/wolny blok)(char), nazwa pliku (dla plików)(char[23]) 
	for(int i = 0; i < blocksNum; disk.seekg(21+(++i)*32) ){
		disk.read(name, 23);
		if(strcmp(name, targetName) == 0){
			rm(targetName, diskName);
			break;
		}
	}
	
	
	file.seekg(0, file.end);
	int size = file.tellg();
	//worst fit
	disk.seekg(12);
	int address, i, freeBlockSize=0;
	do{
		for(i = 0; i < blocksNum; disk.seekg(12+(++i)*32)){
			char type;
			int ad, s;
			disk>>ad>>s>>type;
			if(type == FREE_BLOCK && s > size && s > freeBlockSize){
				address = ad;
				freeBlockSize = s;
			}
		}
		if(freeBlockSize == 0){//free block not found
			if(fragmentate()){//if gave error
				return 1;
			}
			continue;
		}
		break;
	}while(true)	
	
	newBlockSize = freeBlockSize-size;
	
	
}

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
