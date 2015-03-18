//#include <stdio.h>
//#include <stdlib.h>
//
//int main(){
//	#ifndef _OJ_
//		freopen("input_team.txt", "r", stdin);
//		//freopen("output_team.txt", "w", stdout);
//	#endif
//
//	int n = 0;
//	scanf("%d",&n);
//	int *team = new int[n];
//	int *a = new int[n];
//	int *b = new int[n];
//	int *c = new int[n];
//	int i = 0, j = 0, k = 0;;
//	for (i = 0; i < n; i++){
//		scanf("%d", &a[i]);
//		team[i] = 1;
//	}
//	for (i = 0; i < n; i++){
//		scanf("%d", &b[i]);
//	}
//	for (i = 0; i < n; i++){
//		scanf("%d", &c[i]);
//	}
//	int target = 0;
//	scanf("%d", &target);//target
//
//	i = 0;
//	int x = 0; char coach;
//	while (x < n){
//		while (i<n && team[a[i]-1] != 1) 
//			i++;
//		if (a[i] == target)	{// is target
//			coach = 'A';
//			break;
//		}else{
//			team[a[i++]-1] = 0; x++;//get
//		}		
//		if(x == n) break;
//
//		while (j<n && team[b[j]-1] != 1)
//			j++;
//		if (b[j] == target)	{// is target
//			coach = 'B';
//			break;
//		}else{
//			team[b[j++]-1] = 0; x++;//get
//		}		
//		if(x == n) break;
//
//		while (k<n && team[c[k]-1] != 1)
//			k++;
//		if (c[k] == target)	{// is target
//			coach = 'C';
//			break;
//		}else{
//			team[c[k++]-1] = 0; x++;//get
//		}		
//		if(x == n) break;
//	}
//	
//	printf("%c",coach);
//	//fclose(stdin);
//	//fclose(stdout);
//	return 0;
//}
