#include <stdio.h>
int num=0;

int possible(int arr[], int n)
{
        int i;
        for (i = n-1; i > 0; i--)
                if (arr[i] > arr[i-1])
                        return 1;
        return 0;
}

void print(int fact,int arr[], int n,int combi[][fact],int count)
{
        int i;
        for (i = 0; i < n; i++)
            {   combi[i][count]=arr[i]-1;
            }
        
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    int j;

    for ( j = low; j <= high- 1; j++)
    {

        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {

        int pi = partition(arr, low, high);


        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void nextNumber(int arr[], int n)
{
        int i, j;
        int currentMin = 1000000;
        int index;
        int temp;
        for ( i = n-1; i > 0; i--) {
                if (arr[i] > arr[i-1])  {
                        for ( j = i; j < n; j++) {
                                if (arr[i-1] < arr[j] && currentMin > arr[j]) {
                                        currentMin = arr[j];
                                        index = j;
                                }
                        }
                        temp = arr[i-1];
                        arr[i-1] = arr[index];
                        arr[index] = temp;
                        quickSort(arr,i,n-1);
                        break;
                }
        }

        return;
}

int check(int m,int rem_need[][m],int alloc[][m],int cur_work[],int finish[],int seq[],int n,int index,int status,int num,int cnt,int safe[][120])
{   
    int ck=0;
    if(num<n)
    {
    for(int i=0;i<m;i++)
    {
     if(rem_need[index][i]>cur_work[i])
     {  
         ck=1;
     }
    }


    if(ck==0)
    {
        for(int i=0;i<m;i++)
        {
          cur_work[i]=cur_work[i]+alloc[index][i];
        }
        num++;
        status=1;
        check(m,rem_need,alloc,cur_work,finish,seq,n,seq[num],status,num,cnt,safe);
        
    }

    else if(ck==1)
    {
        status=0;
    }

    

    }

    else if(num==n)
    {   
            cnt=1;

    }

 if(cnt==1)
 {
 return 1;
 }
}


int main()
{   int m,n,fact=1,i,j;  

    FILE *input;
    input=fopen("input.txt","r");                  // change inputbankers to input later

    // number of resources
  fscanf(input,"%d",&m);

    // number of processes
  fscanf(input,"%d",&n);

  int max_req[n][m];
  int alloc[n][m];
  int cur_work[m];
  int rem_need[n][m];
  int total[m];

  for(i=0;i<m;i++)
  {
      fscanf(input,"%d",&total[i]);
  }

  for(i=0;i<n;i++)
  { for(j=0;j<m;j++)
    {
        fscanf(input,"%d",&max_req[i][j]);
    }

  }

  for(i=0;i<n;i++)
  { for(j=0;j<m;j++)
    {
        fscanf(input,"%d",&alloc[i][j]);
    }

  }


 for(i=0;i<n;i++)              //getting remaining need matrix
  { for(j=0;j<m;j++)
    {
       rem_need[i][j]=max_req[i][j]-alloc[i][j];
    }
  }

int sum;

  for(i=0;i<m;i++)          //calculating current work
  { sum=0;      
    for(j=0; j<n; j++)
    {
       sum=sum+alloc[j][i];
    }
    cur_work[i]=total[i]-sum;
  }

    for (i = 1; i <= n; ++i) 
    {
        fact *= i;
    }


        int num;
        int tmp;
        int len = 0;
        int arr[n];
        int combi[n][fact];
    
    for(i=0;i<n;i++)
    {
        arr[i]=i+1;
    }
    len=n;
    int count=0;

    quickSort(arr,0,len-1);
        while(1) {
                print(fact,arr,len,combi,count);
                count++;
                if(possible(arr,len)) {
                        nextNumber(arr,len);
                } else {
                        
                        break;
                }
        }


    int index,num1,num2,status,cnt=0;
    int safe[n][fact];
    int seq[n];
    int finish[n];
    int temp[m];
    int val;
    int curindex=0;

    for(i=0;i<m;i++)
    {
        temp[i]=cur_work[i];
    }

    for(i=0;i<fact;i++)
    {   
        status=1;
        num=0;
        for(j=0;j<n;j++)
        { 
            seq[j]=combi[j][i];        
        }


        val=check(m,rem_need,alloc,cur_work,finish,seq,n,seq[0],status,num,cnt,safe);
        if(val==1)
        {
            for(int j=0;j<n;j++)
            {
            safe[j][curindex]=seq[j];
            }
            cnt++;
            curindex++;
        }
    

        for(j=0;j<m;j++)
        {
         cur_work[j]=temp[j];
        }


    }

    printf("%d\n",curindex);

for(i=0;i<curindex;i++)
    {
    for(int j=0;j<n;j++)
        {
         printf("%d ",safe[j][i]);
        }
        printf("\n");

    }


        return 0;
}

