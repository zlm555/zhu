#include <stdio.h>
#include <stdlib.h>

void count_sort(int *a,int len)
{
    int max=0;
    int i;
    int k=0;
    for(i=0;i<len;i++)
    {
        if(a[i]>max)
        {
            max=a[i];
        }
    }
    int *b=NULL;
    b=(int *)malloc((max+1)*sizeof(int));
    for(i=0;i<=max;i++)
    {
        b[i]=0;
    }
    for(i=0;i<len;i++)
    {
        b[a[i]]++;
    }
    for(i=0;i<=max;i++)
    {
        while (b[i])
        {          
            a[k++]=i;
            b[i]--;
        }
    }
    free(b);

}

int main()
{
    int a[5]={10,4,2,6,8};
    for(int i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
    count_sort(a,5);
    for(int i=0;i<5;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}