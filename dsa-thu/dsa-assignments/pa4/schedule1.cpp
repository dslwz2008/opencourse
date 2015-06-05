//// schedule.cpp : Defines the entry point for the console application.
////
//
//#include <cstdio>
//#include "heap.h"
//#include <cstring>
//#include "limits.h"
//
////const int SZ = 1<<20;
////struct fastio{
////    char inbuf[SZ];
////    char outbuf[SZ];
////    fastio(){
////        setvbuf(stdin,inbuf,_IOFBF,SZ);
////        setvbuf(stdout,outbuf,_IOFBF,SZ);
////    }
////}io;
//
//struct Job
//{
//	unsigned int _id;
//	char a[9];
//
//	bool operator < (const Job &job)
//	{
//		if(_id<job._id)
//			return true;
//		if(_id == job._id)
//		{
//			if(strcmp(a,job.a)<0)
//				return true;
//			else
//				return false;
//		}
//		return false;
//	}
//};
//
//
//int main(int argc,char* argv[])
//{
//	#ifndef _OJ_
//		freopen("input_schedule.txt", "r", stdin);
//		//freopen("output_lh.txt", "w", stdout);
//	#endif
//
//	int m, n;
//	scanf("%d %d",&n, &m);
//	//getchar();
//	Job* jobs = new Job[n];
//	for(int i=0;i<n;++i)
//	{
//		scanf("%u %s",&jobs[i]._id,jobs[i].a);
//		//getchar();
//	}
//	Heap<Job> *heap = new Heap<Job>(jobs,n);
//	delete[]jobs;
//	jobs = 0;
//	for(int i=0;i<m;++i)
//	{
//		if(heap->empty())
//			break;
//		Job job = heap->delTop();
//		printf("%s\n",job.a);
//		if(job._id  <= UINT_MAX/2)
//		{
//			Job newJob;
//			newJob._id = job._id * 2;
//			strcpy(newJob.a,job.a);
//			heap->insert(newJob);
//		}
//	}
//	return 0;
//}
//
