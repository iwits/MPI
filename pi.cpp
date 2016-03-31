#include<mpi.h>
#include<cstdio>
#include<math.h>
#include<iostream>

using namespace std;

int main(int argc,char * argv[])
{

    int myid,num_procs;
    int i,n=0;
    double sum,width,local,mypi,pi;
    double start=0,stop=0;
    int proc_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc,&argv);//初始化环境
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);//获取并行的进程数
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);//当前进程在所有进程中的序号
    MPI_Get_processor_name(processor_name,&proc_len);//获取总的处理机数和各个处理机的名字

    cout<<"Processor "<<myid<<" of "<<num_procs<<" on "<<processor_name<<endl;
    if(myid==0)
    {
        cout<<"please give n=";
        cin>>n;
        cout<<endl;
        start=MPI_Wtime(); //MPI计时
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);//把n广播给所有通信环境中的额所有进程
    width=1.0/n;
    sum=0;
    for(i=myid;i<n;i+=num_procs)
    {
        local=width*((double)i+0.5);
        sum+=4.0/(1.0+local*local);
    }
    mypi=width*sum;
    MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);//由进程0进行归约，把每个进程计算出来的mypi进行相加（MPI_SUM）,赋给pi

    if(myid==0){
        printf("PI is %.20f\n",pi);
        stop=MPI_Wtime();
        printf("Time: %f\n",stop-start);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;


}
