#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
    char inputPath[64], outputPath[64], *text;
    char codes[32*256], tab[8*512];
    //encode
    void count(FILE *inputFile_, char *tab_);
    void huffman(FILE *inputFile_, char *tab_);
    void createCodes(char *tab_, char *codes_);
    void writeHeader(char *tab_, char *codes_);
    void write(FILE *inputFile_, FILE *outputFile_, char *tab_, char *codes_);
#ifdef __cplusplus
}
#endif

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
        void count(inputFile, tab);
        //test [count(4B)][parent(2B)][flag(1B)][bitCountInCode(1B)]
        printf("count--parent--flag--bit");
        for(int i=0; i<256; ++i){
            printf("%5d--%6hd--%4d--%3d\n", 
        }
        //void huffman(inputFile, tab);
        //void createCodes(tab, codes);
        //void writeHeader(tab, codes);
        //void write(inputFile, outputFile, tab, codes);
    }
    else{
        //TODO decoding
    }
    fclose(inputFile);
    fclose(outputFile);
    
  return 0;
}
