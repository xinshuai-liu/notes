#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void filechar(const char* source, const char* target) {
    FILE *sfp = fopen(source, "rb");
    if (sfp == NULL) {
        perror("source file fopen fail");
        return;
    }

    FILE *tfp = fopen(target, "wb");
    if (tfp == NULL) {
        perror("target file fopen fail");
        fclose(sfp);
        return;
    }

    int ch = 0;
    while (1)
    {
        ch = fgetc(sfp);
        if (ch == EOF) break;
        if (fputc(ch, tfp) == EOF) break;
    }
    
    fclose(sfp);
    fclose(tfp);
}

void filestring(const char* source, const char* target) {

    FILE *sfp = fopen(source, "rb");
    if (sfp == NULL) {
        perror("source file fopen fail");
        return;
    }

    FILE *tfp = fopen(target, "wb");
    if (tfp == NULL) {
        perror("target file fopen fail");
        fclose(sfp);
        return;
    }

    char buf[BUFFER_SIZE];
    while (fgets(buf, sizeof(buf), sfp) != NULL) {
        if (fputs(buf, tfp) == EOF) break;
    }
    
 }

 void filerdwr(const char* source, const char* target) {

    FILE *sfp = fopen(source, "rb");
    if (sfp == NULL) {
        perror("source file fopen fail");
        return;
    }

    FILE *tfp = fopen(target, "wb");
    if (tfp == NULL) {
        perror("target file fopen fail");
        fclose(sfp);
        return;
    }

    char buf[BUFFER_SIZE];
    size_t ret = 0;
    while ((ret = fread(buf, 1, sizeof(buf), sfp)) > 0) {
        if (fwrite(buf, ret, 1, tfp) <= 0) break;
    }

 }

 void filelinerdwr(const char* source, const char* target) {

    FILE *sfp = fopen(source, "rb");
    if (sfp == NULL) {
        perror("source file fopen fail");
        return;
    }

    FILE *tfp = fopen(target, "wb");
    if (tfp == NULL) {
        perror("target file fopen fail");
        fclose(sfp);
        return;
    }

    char *buf = NULL;
    size_t len = 0;
    size_t nread;
    while ((nread = getline(&buf, &len, sfp)) != -1) {
        if (fwrite(buf, nread, 1, tfp) <= 0) break;
    }
    
    free(buf);
 }

int main(int argc, char* argv[]) {

    if (argc < 3) {
        perror("正确格式 copy sourcefile targetfile");
        exit(1);
    }
     
    // filechar(argv[1],argv[2]);
    // filestring(argv[1],argv[2]);
    // filerdwr(argv[1],argv[2]);
    // filelinerdwr(argv[1],argv[2]);

    return 0;
}