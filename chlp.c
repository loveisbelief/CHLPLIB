#include<stdio.h>
void print_GB2312()
{
    FILE *outFile;
    unsigned char i,j;
    outFile=fopen("gb2312-80.txt","wt");
    for(i=161; i<255; i++)
    {
        for(j=161; j<255; j++)
        {
            fprintf(outFile,"%c%c,%d,%d\n",i,j,i,j);
        }
    }
    fclose(outFile);
}
