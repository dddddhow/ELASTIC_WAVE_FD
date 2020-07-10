#include <stdio.h>
#include <malloc.h>


int main()
{
    int Nx=10001;
    int Nt=1200;
    int i;
    FILE *fou;

    float *x;

    x =(float *)malloc(sizeof(float )*Nt );
    for(i=0;i<Nt;i++)
    {
        x[i]=0.0;
    }

    fou=fopen("vs2d.dat","wb");
    if(fou==NULL)
    {
        printf("err=2\n");
        exit(0);
    }
    for(i=0;i<Nx;i++)
    {
        fwrite(x,4,Nt,fou);
    }

    free(x);
    fclose(fou);

    return 0;
}








