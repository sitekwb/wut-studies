#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    char inputPath[64], outputPath[64], *text;
    char codes[32*256], tab[8*512];
    //encode
    void count(FILE *inputFile_, char *tab_, FILE *outputFile_, char *codes_);
    void huffman(char *tab_);
    void test();
    //void createCodes(char *tab_, char *codes_);
    //void writeHeader(char *tab_, char *codes_);
    //void write(FILE *inputFile_, FILE *outputFile_, char *tab_, char *codes_);
#ifdef __cplusplus
}
#endif

void test(){
        //test [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
        printf("code---count--parent--flag--bit\n");
	for(int i=0; i<512; ++i){
		if(tab[8*i])
        		printf("%4d---%5d--%6hd--%4d--%3d\n", i, tab[8*i], tab[8*i+4], tab[8*i+6], tab[8*i+7]); 
        }
	printf("ind---code\n");
	for(int i=0; i<256; ++i){
		if(codes[32*i]){
			printf("%3d---", i);
			for(int j=0; j<32; j+=4){
				if(codes[32*i+j]){
					printf("%d", codes[32*i+j]);
				}
				else{
					break;
				}
			}
			printf("\n");
		}
	}	
}

int main(int argc, char** argv){
    //enter filenames prompt
    printf("Enter input file path: ");
    scanf("%s", inputPath);
    
    printf("Enter output file path: ");
    scanf("%s", outputPath);
    
    //take input
    FILE *inputFile = fopen(inputPath, "rb");
    FILE *outputFile = fopen(outputPath, "wb");
    
    //encoding/decoding decision
    printf("Do you want to decode(0) or encode(1) input file? Enter number: ");
    int encodeFlag;
    scanf("%d", &encodeFlag);
    if(encodeFlag){
       	count(inputFile, tab, outputFile, codes);
	//createCodes(tab, codes);
        //writeHeader(tab, codes);
        //write(inputFile, outputFile, tab, codes);
    }
    else{
        //TODO decoding
    }
    
  return 0;
}
