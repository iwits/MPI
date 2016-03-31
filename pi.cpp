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

    MPI_Init(&argc,&argv);//��ʼ������
    MPI_Comm_size(MPI_COMM_WORLD,&num_procs);//��ȡ���еĽ�����
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);//��ǰ���������н����е����
    MPI_Get_processor_name(processor_name,&proc_len);//��ȡ�ܵĴ�������͸��������������

    cout<<"Processor "<<myid<<" of "<<num_procs<<" on "<<processor_name<<endl;
    if(myid==0)
    {
        cout<<"please give n=";
        cin>>n;
        cout<<endl;
        start=MPI_Wtime(); //MPI��ʱ
    }

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);//��n�㲥������ͨ�Ż����еĶ����н���
    width=1.0/n;
    sum=0;
    for(i=myid;i<n;i+=num_procs)
    {
        local=width*((double)i+0.5);
        sum+=4.0/(1.0+local*local);
    }
    mypi=width*sum;
    MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);//�ɽ���0���й�Լ����ÿ�����̼��������mypi������ӣ�MPI_SUM��,����pi

    if(myid==0){
        printf("PI is %.20f\n",pi);
        stop=MPI_Wtime();
        printf("Time: %f\n",stop-start);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;


}
