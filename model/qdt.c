#include <stdio.h>
#include <malloc.h>


int main()
{
    int Nx=10001;
    int Nt=1200;
    int i,j;
    FILE *fin,*fou;

    float *tr;
    float *x;

    x =(float *)malloc(sizeof(float )*Nt );
    tr=(float *)malloc(sizeof(float )*240);
    fin=fopen("model.su","rb");
    if(fin==NULL)
    {
        printf("err=1\n");
    }
    fou=fopen("vp2d.dat","wb");
    if(fou==NULL)
    {
        printf("err=2\n");
    }
    for(i=0;i<Nx;i++)
    {
        fread(tr,1,240,fin);
        fread(x,4,Nt,fin);
        for(j=0;j<Nt;j++)
        {
            if(x[j]<20)
            {
                x[j]=0.0;
            }
        }
        fwrite(x,4,Nt,fou);
    }

    free(x);
    free(tr);
    fclose(fin);
    fclose(fou);

    return 0;
}








