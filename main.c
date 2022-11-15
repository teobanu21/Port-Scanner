#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "tcp_connect.h"

void print_banner()
{
    // banner side
    FILE *infile;
    char *buffer;
    long numbytes;

    infile = fopen("_ascii_art.txt", "r");

    if (infile == NULL)
        return 1;

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    fseek(infile, 0L, SEEK_SET);
    buffer = (char *)calloc(numbytes, sizeof(char));

    if (buffer == NULL)
        return 1;

    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    printf("%s", buffer);

    free(buffer);

    printf("\n");
}

int main(int argc, char *argv[])
{
    

    // program side

    if (argc == 1)
    {
        print_banner();
        printf("\n\nPress any key to continue...");
        getchar();
        system("gnome-terminal");
    }
    else if (strcmp(argv[1], "--ports") == 0)
    {
        printf("./main --ports %s %d\n",argv[2], atoi(argv[3]));
        tcp_connect(argv[2], atoi(argv[3]));
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        print_banner();
    }

    return 0;
}