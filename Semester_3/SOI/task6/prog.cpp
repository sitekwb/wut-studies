#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>


#define DEFAULT_DISK 	    ".x"
#define FREE_BLOCK 		    0
#define FILE_TYPE		    1
#define DEFAULT_CAPACITY    256
#define MIN_HEADER_SIZE     32*32

using namespace std;

bool isset(const char *fileName){
	ifstream f;
	f.open( fileName );
	return f.good();
}

struct Disk{
	int capacity, headerSize, blocksNum;
	fstream disk;
	string name;

	int fileHeaderAddress, fileAddress, fileSize;


	Disk(const char *diskName, bool existing){
        name = diskName;
		bool exists = isset(diskName);
		if( (existing && !exists) || (!existing && exists) ){
			throw std::runtime_error("");
		}

		if(existing) {
            disk.open(diskName, fstream::in | fstream::out | fstream::binary);
            (*this)>>capacity;
            (*this)>>headerSize;
            (*this)>>blocksNum;
        }
        else {
            disk.open(diskName, fstream::out | fstream::binary | fstream::trunc | fstream::in);
        }
	}

    ostream &operator<<(int num) {
        /*auto *wr= reinterpret_cast<const char *>(&num);
        for(auto *c = wr+sizeof(num)-1; c>=wr; --c){
            operator<<(*c);
        }
        return disk;*/
        disk.write(reinterpret_cast<const char *>(&num), sizeof(num));
        return disk;
    }

    ostream &operator<<(char c) {
        return disk<<c;
    }

    istream &operator>>(int &num) {
        disk.read(reinterpret_cast<char *>(&num), sizeof(num));
        return disk;
    }

    istream &operator>>(char &c) {
        return disk>>c;
    }

    //12B of disk header; 32B of info: address(int)0; size(int)4; type(char)8; name(char[23])9
	int searchFile(const char *fileName){
		disk.seekg(12);
		for(int i = 0; i < blocksNum; disk.seekg(12+(++i)*32)){
			char type, name[23];
			int ad, s;
            (*this)>>ad;
            (*this)>>s;
            (*this)>>type;
			disk.read(name, 23);

			if(strcmp(name, fileName) == 0 && type == FILE_TYPE){
				fileHeaderAddress = 12+32*i;
				fileAddress = ad;
				fileSize = s;
				return 0;
			}
		}
		return 1;
	}

	int defragmentate(){
		int addressTab[2][blocksNum], sizeTab[2][blocksNum], oldAddressTab[blocksNum];
		char typeTab[2][blocksNum], nameTab[2][blocksNum][23];

		int block = 0;
		int address = 12+headerSize;
		//get block information
		disk.seekg(12);
		for(int i = 0; i < blocksNum; disk.seekg(12+(++i)*32)){
            (*this)>>addressTab[0][i];
            (*this)>>sizeTab[0][i];
            (*this)>>typeTab[0][i];
			disk.read(nameTab[0][i], 23);

			if(typeTab[0][i] == FILE_TYPE  &&  sizeTab[0][i] != 0 ){
				oldAddressTab[block] = addressTab[0][i];
				addressTab[1][block] = address;
				sizeTab[1][block] = sizeTab[0][i];
				address += sizeTab[0][i];
				typeTab[1][block] = FILE_TYPE;
				strcpy(nameTab[1][block], nameTab[0][i]);
				++block;
			}
		}
		//last free block
		addressTab[1][block] = address;
		sizeTab[1][block] = capacity - (address - 12 - headerSize);
		typeTab[1][block] = FREE_BLOCK;
		nameTab[1][block][0] = '\0';

		blocksNum = ++block;
		//create new file
		string tempName = name;

		while(isset(tempName.c_str())){
			tempName+='x';
		}

		Disk temp(tempName.c_str(), false);

		temp<<capacity;
		temp<<headerSize;
		temp<<blocksNum;
		for(int i=0; i<blocksNum; ++i){
			temp<<addressTab[1][i];
			temp<<sizeTab[1][i];
			temp<<typeTab[1][i];
			temp.disk.write(nameTab[1][i], 23);
		}
		for(int i=blocksNum*32; i<headerSize; ++i){
			temp<<'0';
		}
		//write content
		for(int i=0; i<blocksNum; ++i){
			disk.seekg(oldAddressTab[i]);
			for(int j=0; j<sizeTab[1][i]; ++j){
				char a;
                (*this)>>a;
				temp<<a;
			}
		}

		for(int i=temp.disk.tellp(); i<12+headerSize+capacity; ++i){
		    temp<<(char)'\0';
		}

		close();
		temp.close();

		remove(name.c_str());
		rename(tempName.c_str(), name.c_str());

		disk.open(name.c_str(), fstream::in | fstream::out | fstream::binary);

		return 0;
	}

    int close(){
	    disk.close();
	    return 0;
	}

    int rm(){
        //it's assumed that file is found
        disk.seekp(fileHeaderAddress+8);//char type after two ints
        (*this)<<(char)FREE_BLOCK;
        return 0;
    }

    void setBlocksNum(int x){
	    blocksNum = x;
	    disk.seekp(8);
        (*this)<<blocksNum;
	}

};



int mkdisk(int capacity, const char *diskName){
    Disk d(diskName, false);
	char type = FREE_BLOCK;
	d.blocksNum = 1;
	d.headerSize = (capacity / 4096);
	d.headerSize -= d.headerSize%32; //align to infoBlock-size
	d.headerSize = max(MIN_HEADER_SIZE, d.headerSize);
	d.capacity = capacity;
	d<<d.capacity;
	d<<d.headerSize;
	d<<d.blocksNum;
    int address = 12+d.headerSize;
	//adres (int), rozmiar (int), typ obszaru (plik/wolny blok)(char), nazwa pliku (dla plików)(char[23])
	d<<address;
	d<<d.capacity;
	d<<type;
    for(int i=d.disk.tellp(); i<12+d.headerSize+d.capacity; ++i){
        d<<(char)'\0';
    }
	return 0;
}



int rm(const char *fileName, const char *diskName){
	Disk disk(diskName, true);

	if(disk.searchFile(fileName)){
		throw runtime_error("");
	}

	return disk.rm();
}

int put(const char *filePath, const char *targetName="", const char *diskName=DEFAULT_DISK){
    Disk d(diskName, true);
    fstream file;

    if(!isset(filePath)){
        return 1;
    }

    file.open(filePath, fstream::in | fstream::binary);

	if(strcmp(targetName, "") == 0){
		targetName = filePath;
	}

	if(!d.searchFile(targetName)) {//found
        d.rm();
    }

	file.seekg(0, file.end);
	int fileSize = file.tellg();
	//worst fit
	fstream &disk = d.disk;

	disk.seekg(12);

	int address=0, i, freeBlockSize=0, index=0;
	do{
		for(i = 0; i < d.blocksNum; disk.seekg(12+(++i)*32)){
			char type;
			int ad, s;
			d>>ad;
			d>>s;
			d>>type;
			if(type == FREE_BLOCK && s > fileSize && s > freeBlockSize){
				address = ad;
				freeBlockSize = s;
				index = i;
			}
		}
		if(freeBlockSize == 0){//free block not found
			if(d.defragmentate()){//if gave error
				return 1;
			}
			continue;
		}
		break;
	}while(true);

	if(32*d.blocksNum == d.headerSize){
	    return 1;//too much files
	}

	int freeBlockSize2 = freeBlockSize-fileSize;
	int freeBlockAddress2 = address+fileSize;

	disk.seekp(12+32*index);
	//write header of new file
	d<<address;
	d<<fileSize;
	d<<(char)FILE_TYPE;
	disk.write(targetName, 23);
	//set input after header file
	int oldAd, oldSize;
	char oldType, oldName[23];

    disk.seekg(12+32*(index+1));
    d>>oldAd;
    d>>oldSize;
    d>>oldType;
    disk.read(oldName, 23);

    disk.seekp(12+32*(index+1));
    d<<freeBlockAddress2;
    d<<freeBlockSize2;
    d<<(char)FREE_BLOCK;
    disk.write(oldName, 23);//something, doesn't matter what


    int ad, s;
    char t, n[23];
    //rewrite all other blocks
	for(int i = index+2; i<d.blocksNum; ++i){
	    disk.seekg(12+32*i);
	    d>>ad;
	    d>>s;
	    d>>t;
        disk.read(n, 23);

        swap(ad, oldAd);
        swap(s, oldSize);
        swap(t, oldType);
        swap(n, oldName);

        disk.seekp(12+32*i);
        d<<ad;
        d<<s;
        d<<t;
        disk.write(n, 23);//something, doesn't matter what
    }
    disk.seekp(12+32*(d.blocksNum+1));
    d<<oldAd;
	d<<oldSize;
	d<<oldType;
    disk.write(oldName, 23);//something, doesn't matter what

    //copy content of file
    disk.seekp(address);
    file.seekg(0);
    while(!file.eof()){
        char c;
        file>>c;
        disk<<c;
    }

    d.setBlocksNum(d.blocksNum+1);

    file.close();
    d.close();

    return 0;
}

//12B of disk header; 32B of info: address(int)0; size(int)4; type(char)8; name(char[23])9
int get(const char *diskFileName, const char *targetPath, const char *diskName){
    Disk d(diskName, true);
    fstream &disk = d.disk;

    if(d.searchFile(diskFileName)){//if searching gave error
        return 1;
    }

    if(isset(targetPath)){
        remove(targetPath);
    }

    fstream file;
    file.open(targetPath, fstream::binary | fstream::trunc | fstream::out);

    //copy content of file
    int diskFileEnd = d.fileAddress+d.fileSize;
    file.seekp(0);
    disk.seekg(d.fileAddress);
    while(disk.tellg() != diskFileEnd){
        char c;
        disk>>c;
        file<<c;
    }

    return 0;
}

int lsdisk(const char *diskName){
    Disk d(diskName, true);
    fstream &disk = d.disk;

    disk.seekg(12);
    cout<<"Size   |---|Name"<<endl;
    for(int i = 0; i < d.blocksNum; disk.seekg(12+(++i)*32)){
        char type, name[23];
        int ad, s;
        d>>ad;
        d>>s;
        d>>type;
        disk.read(name, 23);

        if(type == FILE_TYPE){
            cout<<setw(7)<<s<<"|---|"<<name<<endl;
        }
    }
    return 0;
}

int rmdisk(const char *diskName){
    Disk d(diskName, true);//checks if exists
    remove(diskName);
    return 0;
}

int info(const char *diskName){
    Disk d(diskName, true);
    fstream &disk = d.disk;

    cout<<"Capacity   = "<<d.capacity<<endl;
    cout<<"HeaderSize = "<<d.headerSize<<endl;
    cout<<"BlocksNum  = "<<d.blocksNum<<endl;

    disk.seekg(12);
    cout<<"Num|---|Address|---|Size   |---|Type|---|Name"<<endl;
    for(int i = 0; i < d.blocksNum; disk.seekg(12+(++i)*32)){
        char type, name[23];
        int ad, s;
        d>>ad;
        d>>s;
        d>>type;
        disk.read(name, 23);

        cout<<setw(3)<<i+1<<"|---|"<<setw(7)<<ad<<"|---|"<<setw(7)<<s<<"|---|"<<setw(4)<<((type==FREE_BLOCK)?"----":"FILE")<<"|---|"<<((type==FREE_BLOCK)?"":name)<<endl;

    }
    return 0;
}

int defragmentate(const char *diskName){
    Disk disk(diskName, true);
    disk.defragmentate();
    return 0;
}

int main(int argc, const char *argv[]){
	if(argc < 2){
		return 1;
	}
	try {
        switch (atoi(argv[1])) {
            case 0:
                return mkdisk((argc > 2)?atoi(argv[2]):DEFAULT_CAPACITY, (argc == 4) ? argv[3] : DEFAULT_DISK);
            case 1:
                switch (argc) {
                    case 3:
                        return put(argv[2]);
                    case 4:
                        return put(argv[2], argv[3]);
                    case 5:
                        return put(argv[2], argv[3], argv[4]);
                    default:
                        return 1;
                }
            case 2:
                if (argc < 4) {
                    return 1;
                }
                return get(argv[2], argv[3], (argc == 5) ? argv[4] : DEFAULT_DISK);
            case 3:
                return lsdisk((argc == 3) ? argv[2] : DEFAULT_DISK);
            case 4:
                if (argc < 3) {
                    return 1;
                }
                return rm(argv[2], (argc == 4) ? argv[3] : DEFAULT_DISK);
            case 5:
                return rmdisk((argc == 3) ? argv[2] : DEFAULT_DISK);
            case 6:
                return info((argc == 3) ? argv[2] : DEFAULT_DISK);
            case 7:
                return defragmentate((argc == 3) ? argv[2] : DEFAULT_DISK);
        }
    }
    catch(...){
        return 1;
    }
	return 0;
}
