#include <stdio.h>
#include <malloc.h>
#include <math.h>

int main()
{
    int Nx=10001;
    int Nt=1200;
    int i,j;
    FILE *fin,*fou;

    float *x;
    float p;

    x =(float *)malloc(sizeof(float )*Nt );
    fin=fopen("vp2d.dat","rb");
    if(fin==NULL)
    {
        printf("err=1\n");
    }
    fou=fopen("topo2d.dat","wb");
    if(fou==NULL)
    {
        printf("err=2\n");
    }
    for(i=0;i<Nx;i++)
    {
        fread(x,4,Nt,fin);
        for(j=0;j<Nt;j++)
        {
            if(fabs(x[j]-x[j-1])>100)
            {
                p=5.0*(j);
                //p=j;
                if(i==10000)
                    printf("%f\n",p);
                break;
            }
        }
        fwrite(&p,1,4,fou);
    }

    free(x);
    fclose(fin);
    fclose(fou);

    return 0;
}








