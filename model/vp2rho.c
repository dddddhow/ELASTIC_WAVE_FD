#include <stdio.h>
#include <malloc.h>
#include <math.h>

int main()
{
    int nx=10001;
    int nz=1200;
    int i,j;
    FILE *fi,*fo;
    float *data;

    data=(float *)malloc(sizeof(float)*nz);
    fi=fopen("vp2d.dat","rb");
    if(fi==NULL)
    {
        printf("err in vp2d.dat\n");
    }
    fo=fopen("rho2d.dat","wb");
    if(fo==NULL)
    {
        printf("err in rho2d.dat\n");
    }

    for(i=0;i<nx;i++)
    {
        fread(data,sizeof(float),nz,fi);
        for(j=0;j<nz;j++)
        {
            data[j]=0.31*sqrt(sqrt(data[j]));
        }
        fwrite(data,sizeof(float),nz,fo);
    }

    free(data);
    fclose(fi);
    fclose(fo);
    return 0;
}
