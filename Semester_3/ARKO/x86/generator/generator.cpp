#include <fstream>

using namespace std;

int main(){
	fstream str;
	str.open("a", fstream::out);
	for(char c = 0; c < 3; ++c){
		for(char i=-1; i<c; ++i) str << c;
	}
	str.close();
	return 0;
}
