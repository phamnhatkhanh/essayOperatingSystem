#include <iostream>
using namespace std;
#define N 5
#define M 3

// check if resource allocation request with need and avail table is valid.
bool isCompareResources(int need[N][M],int avail[],int indexProcess,int request[]){
  for ( int j=0 ; j < M; j++){
    if((request[j] > avail[j]) && (request[j]>need[indexProcess][j])){
      return false;
    }
  }
  return true;
}

//safe state check algorithm
// check the safe status of the system when have need,alloc and avail table 
bool isSafe(int need[N][M],int alloc[N][M],int avail[],int ans[],int m,int n){
  int y,k,j,i;
  // declare an array f to check if there are still unallocated processes.
  int f[n], ind = 0;
	for (k = 0; k < n; k++) {
		f[k] = 0;
    ans[k]=-1;
	}
  int availCopy[m];
  for ( j=0 ; j < m; j++){
      availCopy[j] = avail[j];
  }
  
  //find states Safe
	for (k = 0; k < 5; k++) {
		for (i = 0; i < n; i++) {
			if (f[i] == 0) {

				int flag = 0;
				for (j = 0; j < m; j++) {
					if (need[i][j] > avail[j]){
						flag = 1;
						break;
					}
				}
				if (flag == 0) {
					ans[ind++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					f[i] = 1;
				}
			}
		}
	}
  //
  for ( j=0 ; j < m; j++){
      avail[j] = availCopy[j];
  }
  // check the results table allocating enough resources to the processes
  for(i=0;i<n;i++){
    if(ans[i]==-1){
      return false;
    }
  }
  return true;
}

// resource allocation algorithm

void isRequest(int need[N][M],int alloc[N][M],int avail[],int indexProcess,int request[],int m,int n){
  // check value request WITH need,avail
  if(isCompareResources(need, avail, indexProcess, request)){

    int i,j;
    int respon[n];
    int updateAlloc[N][M];
    int updateNeed[N][M];
    int updateAvail[n];
    //alloc+request
    for ( i=0 ; i < n; i++){
      for ( j=0 ; j < m; j++){
        if(i==indexProcess){
          for ( j=0 ; j < m; j++){
            updateAlloc[i][j] = alloc[i][j]+request[j];
          }
        }
        updateAlloc[i][j] = alloc[i][j];
      }
    }
    //need-request
    for ( i=0 ; i < n; i++){
      for ( j=0 ; j < m; j++){
        if(i==indexProcess){
          for ( j=0 ; j < m; j++){
            updateNeed[i][j] = need[i][j]-request[j];
          }
        }
        updateNeed[i][j] = need[i][j];
      }
    }
    // avail-request
    for ( j=0 ; j < m; j++){
      updateAvail[j] = avail[j]-request[j];
    
    }


    if(isSafe(updateNeed, updateAlloc, updateAvail, respon,  m, n)){
      cout<<endl<<"Grant request accepted"<<endl;
      cout<<"Following is the SAFE Sequence"<<endl;
      for (i = 0; i < n - 1; i++){
        cout << " P" << respon[i] << " ->";
      }
      cout << " P" << respon[n - 1] <<endl;    
    }else{
      cout<<"Resource cannot be allocated";
    }
  }else{
      cout<<"Request exceeds resource allocation";
  }
}

int main()
{
	// P0, P1, P2, P3, P4 are the Process names here
	int n, m, i, j, k;
	n = 5; // Number of processes
	m = 3; // Number of resources
  int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
                  { 2, 0, 0 }, // P1
                  { 3, 0, 2 }, // P2
                  { 2, 1, 1 }, // P3
                  { 0, 0, 2 } }; // P4

/* deadlock
  int alloc[5][3] = { { 0, 1, 0 }, // P0 // Allocation Matrix
              { 0, 0, 0 }, // P1
              { 0, 0, 2 }, // P2
              { 2, 1, 1 }, // P3
              { 0, 0, 2 } }; // P4
*/
	int max[5][3] = { { 7, 5, 3 }, // P0 // MAX Matrix
					{ 3, 2, 2 }, // P1
					{ 9, 0, 2 }, // P2
					{ 2, 2, 2 }, // P3
					{ 4, 3, 3 } }; // P4

	int avail[3] = { 3, 3, 2 }; // Available Resources. Case: Request source not accept.
  //int avail[3] = { 3, 3, 4 }; //Case: Request source accept.
  
  int need[N][M];
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
	}
  
	int ans[n];



//resource allocation
if(isSafe(need, alloc, avail, ans,m, n)){
	cout << "Following is the SAFE Sequence" << endl;
	for (i = 0; i < n - 1; i++){
		cout << " P" << ans[i] << " ->";
  }
	  cout << " P" << ans[n - 1] <<endl;
    // request source.
   int requsetSource[3]={0,0,2};
  
    isRequest(need, alloc, avail, 0,requsetSource, m,  n);

  }else{
    cout<<"Can Not find is the SAFE Sequence";
  }

	return (0);
}
