#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define arr_size1 1000000
#define MAXSIEZ 100000000
#define sort_method_number 8
int arr_size;
int show_orige_arr;//是否输出排序前的数组，1输出
int show_result_arr;//是否输出排序后的数组，1输出
int create_arr_method;//设置数组初始化方式，1为随机，2为顺序，3为逆序。

int orige_arr[arr_size1];
int sort_arr[arr_size1];

long long compare_list[sort_method_number];
long long swap_list[sort_method_number];
double time_list[sort_method_number];
char show_sort_list[sort_method_number][30]={"insert_sort","bubble_sort","choose_sort","shell_sort","quick_sort","merge_sort","haepify_sort","count_sort"};
int method_index;
double total_time;
clock_t start_time,end_time;//计时


void show_result()
{
    int k=0;
    FILE *fp=fopen("sort.txt","a+");
    fseek(fp,0,SEEK_END);
    fprintf(fp,"数组大小为:%d\n",arr_size);
    switch (create_arr_method)
    {
    case 1:
        fprintf(fp,"数组的初始化方式为:随机生成\n");
        break;
    case 2:
        fprintf(fp,"数组的初始化方式为:顺序生成\n");
        break;
    case 3:
        fprintf(fp,"数组的初始化方式为:逆序生成\n");
        break;
    default:
        break;
    }

    for(k=0;k<sort_method_number;k++)
    {
        fprintf(fp,"%s\t的时间为:%f\t交换的次数为%lld\t比较的次数为:%lld\n",show_sort_list[k],time_list[k],swap_list[k],compare_list[k]);
        printf("%s\t的时间为:%f\t交换的次数为%lld\t比较的次数为:%lld",show_sort_list[k],time_list[k],swap_list[k],compare_list[k]);
        printf("\n");
    }
}
void swap(int *a,int *b,int method_index)
{
    int temp=*a;
    *a=*b;
    *b=temp;
    swap_list[method_index]++;
}
void move(int *a,int *b,int method_index)
{  
    *a=*b;
    swap_list[method_index]++;
}
int compare(int a,int b,int method_index)
{
    compare_list[method_index]++;
    if(a<b)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//初始化数组
void create1_arr()
{
    int i;
    srand(time(NULL));
    for(i=0;i<arr_size;i++)
    {
        orige_arr[i]=rand()%arr_size;
    }
}
void create2_arr()
{
    int i;
    for(i=0;i<arr_size;i++)
    {
        orige_arr[i]=i;
    }
}
void create3_arr()
{
    int i;
    for(i=0;i<arr_size;i++)
    {
        orige_arr[i]=arr_size-i;
    }
}
//打印数组
void show_arr(int *a)
{
    int i;
    int k;
    for(i=0;i<arr_size;i++)
    {
        k=i+1;
        printf("%d ",a[i]);
        if(k%10==0)
        {
            printf("\n");
        }
    }
    printf("\n");
}
//将原数组存入临时数组
void exchange_arr()
{
    int i;
    for(i=0;i<arr_size;i++)
    {
        sort_arr[i]=orige_arr[i];
    }
}

void operate(void(*sort)(int),int method_index)
{
    double sort_times;
    exchange_arr();
    start_time=clock();
    sort(method_index);
    end_time=clock();
    sort_times=((double)(end_time - start_time) / CLOCKS_PER_SEC)*1000;

    time_list[method_index]=sort_times;
    if(show_result_arr!=0)
    {
        show_arr(sort_arr);
    }
}
//插入排序
void insert_sort(int method_index)
{
    int i,j;
    int temp;
    for(i=1;i<arr_size;i++)
    {
        temp=sort_arr[i];
        j=i-1;
        while(j>=0)
        {
            if(compare(temp,sort_arr[j],method_index))
            {
                swap(&sort_arr[j+1],&sort_arr[j],method_index);
                j--;
            }
            else
            {
                break;
            }
        }
        swap(&sort_arr[j+1],&temp,method_index);
    }
}

//冒泡排序算法
void bubble_sort(int method_index)
{
    int i,j;
    int flag=0;
    for(i=0;i<arr_size-1;i++)
    {
        flag=0;
        for(j=0;j<arr_size-1-i;j++)
        {
            if(compare(sort_arr[j+1],sort_arr[j],method_index))
            {
                swap(&sort_arr[j+1],&sort_arr[j],method_index);
                flag=1;
            }
        }
        if(flag==0)
        {
            break;
        }
    }
}

//选择排序算法
void choose_sort(int method_index)
{
    int i,j;
    int min_index;
    for(i=0;i<arr_size;i++)
    {
        min_index=i;
        for(j=i+1;j<arr_size;j++)
        {
            if(compare(sort_arr[j],sort_arr[min_index],method_index))
            {
                min_index=j;
            }
        }
        swap(&sort_arr[i],&sort_arr[min_index],method_index);
    }
}

//希尔排序算法
void shell_sort(int method_index)
{
    int i,j;
    int gap;//步长 
    int temp;
    int b;
    for(gap=arr_size/2;gap>0;gap=gap/2)
    {
        for(i=0;i<gap;i++)
        {
            for(j=i+gap;j<arr_size;j+=gap)
            {
                temp=sort_arr[j];
                b=j-gap;
                while(b>=0)
                {
                    if(compare(temp,sort_arr[b],method_index))
                    {
                        swap(&sort_arr[b+gap],&sort_arr[b],method_index);
                        b-=gap;
                    }
                    else
                    {
                        break;
                    }

                }
                sort_arr[b+gap]=temp;
            }
        }
    }
}


//快速排序算法(通过栈来实现)
void quick_sort(int method_index)
{
    int stack[arr_size];
    int top=-1;
    int left,right;
    left=0,right=arr_size-1;
    stack[++top]=left;
    stack[++top]=right;
    while(top>-1)//只要栈内还有边界元素就循环执行
    {
        right=stack[top--];
        left=stack[top--];
        int i,j;
        int among=sort_arr[(left+right)/2];
        i=left,j=right;
        while(i<=j)
        {
            while(compare(sort_arr[i],among,method_index))
            {
                i++;
            }
            while(compare(among,sort_arr[j],method_index))
            {
                j--;
            }
            if(i<=j)
            {
                swap(&sort_arr[i],&sort_arr[j],method_index);
                i++;
                j--;
            }
        }
        //将左半边边界入栈
        if(compare(left,j,method_index))
        {
            stack[++top]=left;
            stack[++top]=j;
        }
        //将右半边边界入栈
        if(compare(i,right,method_index))
        {
            stack[++top]=i;
            stack[++top]=right;
        }
    }
}

//归并排序算法
void merge(int arr[], int left, int mid, int right, int temp[],int method_index) {
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (compare(arr[i],arr[j],method_index))
            move(&temp[k++],&arr[i++],method_index);
        else
            move(&temp[k++],&arr[j++],method_index);

    }
    while (i <= mid)
        move(&temp[k++],&arr[i++],method_index);
    while (j <= right)
        move(&temp[k++],&arr[j++],method_index);
    for (i = 0; i < k; ++i)
        arr[left + i] = temp[i];
}
void merge_sort_recursive(int arr[],int temp_arr[],int left, int right, int method_index) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    merge_sort_recursive(arr, temp_arr,left, mid,method_index);
    merge_sort_recursive(arr, temp_arr,mid + 1, right,method_index);
    merge(arr, left, mid, right,temp_arr,method_index);
}
void merge_sort(int method_index) {
    int temp_arr[arr_size];
    merge_sort_recursive(sort_arr, temp_arr, 0, arr_size - 1,method_index);
}


void max_heapify(int *a,int start,int end,int method_index)
{
    int dad=start;
    int son=dad*2+1;
    while(son<end)
    {
        if(son+1<end&&compare(a[son],a[son+1],method_index))
        {
            son++;
        }
        if(compare(a[son],a[dad],method_index))
        {
            return;
        }
        else
        {
            swap(&a[dad],&a[son],method_index);
            dad=son;
            son=dad*2+1;
        }
    }
}
//堆排序
void haepify_sort(int method_index)
{
    int i;
    for(i=arr_size/2-1;i>=0;i--)
    {
        max_heapify(sort_arr,i,arr_size,method_index);//将无序二叉树构建成大顶堆二叉树
    }
    for(i=arr_size-1;i>0;i--)
    {
        swap(&sort_arr[0],&sort_arr[i],method_index);
        max_heapify(sort_arr,0,i,method_index);
    }
}
//计数排序算法
//1.先找出最大值
// 2.开辟一个数组，大小为最大值
// 3.将排序数组的数值排到新数组里面
// 4.将新数组里面的数字取出
void count_sort(int method_index)
{
     int max_num=0;
    int i;
    int k=0;
    for(i=0;i<arr_size;i++)
    {
        if(compare(max_num,sort_arr[i],method_index))
        {
            max_num=sort_arr[i];
        }
    }
    int *temp_arr=NULL;
    temp_arr=(int *)malloc(max_num*sizeof(int));
    for(i=0;i<=max_num;i++)
    {
        temp_arr[i]=0;
    }
    for(i=0;i<arr_size;i++)
    {
        temp_arr[sort_arr[i]]++;
    }
    for(i=0;i<max_num+1;i++)
    {
        while(temp_arr[i]!=0)
        {
            sort_arr[k++]=i;
            temp_arr[i]--;
        }
    }
    // free(temp_arr);
}

void prepare()
{
    int i;
    for(i=0;i<sort_method_number;i++)
    {
        compare_list[i]=0;
        time_list[i]=0;
        swap_list[i]=0;
    }
}

void start(int show_orige_arr_prepare,int show_result_arr_prepare,int arr_size_prepare,int create_arr_method_prepare)
{
    show_orige_arr=show_orige_arr_prepare;
    show_result_arr=show_result_arr_prepare;
    arr_size=arr_size_prepare;
    create_arr_method=create_arr_method_prepare;
    printf("数组大小：%d\n",arr_size_prepare);
    printf("初始化方式:%d\n",create_arr_method);
    prepare();
    switch (create_arr_method)
    {
    case 1:
        create1_arr();
        break;
    case 2:
        create2_arr();
        break;
    case 3:
        create3_arr();
        break;
    default:
        printf("创建数组错误!");
        break;
    }
    if(show_orige_arr!=0)
    {
        show_arr(orige_arr);
    }
    operate(insert_sort,0);
    operate(bubble_sort,1);
    operate(choose_sort,2);
    operate(shell_sort,3);
    operate(quick_sort,4);
    operate(merge_sort,5);
    operate(haepify_sort,6);
    operate(count_sort,7);
    show_result();

}

int main()
{
    int show_orige_arr_prepare=0,show_result_arr_prepare=0,create_arr_method_prepare,arr_size_preparea;
    int i=0;
    for(i=0;i<10;i++)
    {
            printf("请输入数组大小(0-1000000):");
    scanf("%d",&arr_size_preparea);
    // printf("请输入是否显示原数组(0不显示,1显示):");
    // scanf("%d",&show_orige_arr_prepare);
    // putchar('\n');
    // printf("是否显示排序后的数组(0不显示,1显示):");
    // scanf("%d",&show_result_arr_prepare);
    // putchar('\n');
    printf("请选择创建数组的方式\n1:随机生成\n2:顺序生成\n3:倒序生成\n");
    scanf("%d",&create_arr_method_prepare);
    putchar('\n');
    start(show_orige_arr_prepare,show_result_arr_prepare,arr_size_preparea, create_arr_method_prepare);
    scanf("是否继续:0为继续,1为退出%d",&i);
    }
    return 0;

}


