#include <stdio.h>
#include <stdlib.h>
#define N 6

int main(){
    int S[N] = {5, 10, 12, 13, 15, 18};
    int k = 30;
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
    int elements_taken = N; // pertains to R in (N taken R)
    int i, j, offset, sum = 0, obtained_weight=0, remaining_weight=0;

    for (int i = 0; i < N; i++) sum+=S[i];
    remaining_weight = sum;

	//Create a triangular matrix using option[][] and initalize nopts[]
	for (int i = 0; i < N+2; i++){
        nopts[i] = N+1-i;
        for (int j = 0; j < N+2; j++){
            if (i+j <= N+1 && i!=0 && j!=0) option[i][j] = S[N-j];
            else option[i][j] = 0;
        }
	}
    printf("For N=%d:", N); printf("\n==============================\n");
	for (int i = 0; i < N+2; i++){
        for (int j = 0; j < N+2; j++) if (i+j <= N+1 && i!=0 && j!=0) printf("%d ", option[i][j]);
        printf("\n");
	}

    //List all combinations
    i=1;
    while (nopts[1]>0){
        if (obtained_weight + option[i][nopts[i]] > k){

            remaining_weight-=option[i][nopts[i]--];
                        printf("A OW%d RW%d\n", obtained_weight + option[i][nopts[i]], remaining_weight);

        } else if (obtained_weight + remaining_weight < k){
            obtained_weight -= option[i-1][nopts[i-1]];
            nopts[i-1]--;
            remaining_weight = 0;
            for (j=1; j <= nopts[i-1];j++) remaining_weight += option[i-1][j];
            for (j=i; j<N; j++) nopts[j] = nopts[j-1]-1;
            i--;
              printf("B OW%d RW%d\n", obtained_weight, remaining_weight);
        } else if (obtained_weight == k){ //solution found
            printf("C %d\n", obtained_weight);
            for(j=1; j < i;j++) printf("%2i ", option[j][nopts[j]]);
            printf("\n");
            obtained_weight-=option[i-1][nopts[i-1]];
                i--; // works only for sorted arrays!!
        } else{
            obtained_weight += option[i][nopts[i]];
            remaining_weight -= option[i][nopts[i]];
                            printf("D OW%d RW%d\n", obtained_weight, remaining_weight);
            i++;
        }

    }
}



