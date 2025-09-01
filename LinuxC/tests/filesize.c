#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE *fp = fopen(argv[1], "w");

    fseek(fp, 1024*1024*1024, SEEK_CUR);

    long size = ftell(fp);

    printf("%ld\n", size);

    fclose(fp);

    FILE *tmp = tmpfile();

    fputs(argv[1], tmp);
    fseek(tmp, 0, SEEK_SET);

    char buf[1024];
    fgets(buf, 1024, tmp);

    printf("%s\n",buf);

    fclose(tmp);
    return 0;
}