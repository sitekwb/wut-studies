#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    char inputPath[64], outputPath[64], *text;
    char codes[32*256], tab[8*512];
    int d_tab[2*512];
    //encode
    void encode(FILE *inputFile_, char *tab_, FILE *outputFile_, char *codes_);
    void decode(FILE *inputFile_, int *tab_, FILE *outputFile_, char *codes_);
    void test();
    void d_test();
    //void createCodes(char *tab_, char *codes_);
    //void writeHeader(char *tab_, char *codes_);
    //void write(FILE *inputFile_, FILE *outputFile_, char *tab_, char *codes_);
#ifdef __cplusplus
}
#endif

void d_test(){
        //d_test [0ch(4B)][1ch(4B)]
        printf("sign---0ch---1ch\n");
	for(int i=0; i<512; ++i){
		if(d_tab[2*i] || d_tab[2*i+1]){
			int a = (d_tab[2*i]!=0)?( (int *)d_tab[2*i] - d_tab ):-2;
			int b = (d_tab[2*i+1]!=0)?( (int *)d_tab[2*i] - d_tab ):-2;
        		printf("%4d---%3d--%3d\n", i, a, b); 
		}
	}
}

void test(){
        //test [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
        printf("code---count--parent--flag--bit---code\n");
	for(int i=0; i<512; ++i){
		if(tab[8*i]){
        		printf("%4d---%5d--%6hd--%4d--%3d---", i, tab[8*i], tab[8*i+4], tab[8*i+6], tab[8*i+7]); 
			if(i<256){
				for(int j=0; j<32; j++){
					printf("%2x", codes[32*i+j]);
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
       	encode(inputFile, tab, outputFile, codes);
    }
    else{
	decode(inputFile, d_tab, outputFile, codes);	    
    }
    
  return 0;
}
