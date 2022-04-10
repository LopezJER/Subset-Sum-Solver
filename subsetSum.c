#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void subsetSum (int * set, int cardinality, int target);
void printPrompt (int * set, int cardinality, int target);
int countSets(FILE * fp);
int getTarget(FILE * fp);
void getStringSet(char * stringSet, FILE * fp);
int getCardinality(char * stringSet);
int * getSet(char * stringSet, int cardinality);
int cmpfunc (const void * a, const void * b) ;


int main(){
    FILE* fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL) return 0;
    int sets = countSets(fp);

    char stringSet [255], temp [255];
    int i = 0, target, cardinality, *set;

    printf("\nSubset Sum Solver\n");
    for (i = 0; i < sets; i++){
        target = getTarget(fp);
        getStringSet(stringSet, fp);
        strcpy (temp, stringSet);
        cardinality = getCardinality(temp);
        int * set = getSet(stringSet, cardinality);
        qsort(set, cardinality, sizeof(int), cmpfunc);
        printPrompt(set, cardinality, target);
        subsetSum(set, cardinality, target);
        }
        fclose(fp);
    }



void subsetSum(int * S, int N, int k) {
	int nopts[N+2]; //array of top of stacks
	int option[N+2][N+2]; //array of stacks of options
    int i, j, sum = 0, obtained_weight=0, solution_found=0;

    for (int i = 0; i < N; i++) sum+=S[i];

	//Create a triangular matrix using option[][] and initalize nopts[]
	for (int i = 0; i < N+2; i++){
        nopts[i] = N+1-i;
        for (int j = 0; j < N+2; j++){
            if (i+j <= N+1 && i!=0 && j!=0) option[i][j] = S[N-j];
            else option[i][j] = 0;
        }
	}

    i=1;
    while (i>0 && i < N){
        if (obtained_weight + option[i][nopts[i]] >= k || nopts[i] ==0){
            if (obtained_weight + option[i][nopts[i]] == k){
                for(j=1; j <= i;j++)printf("%3i ", option[j][nopts[j]]); printf("\n");
                solution_found = 1;
            }
            obtained_weight-=option[i-1][nopts[i-1]];
            nopts[i-1]--;
            i--;
            if (nopts[i+1] <= nopts[i]) nopts[i+1] = nopts[i] -1;
        } else{
            obtained_weight += option[i][nopts[i]];
            i++;
        }
    }

    if (solution_found==0) printf(" No solutions found.\n");


}



int * getSet(char * stringSet, int cardinality){
    int* set = malloc (sizeof(int) * cardinality);
    char * token;

    token = strtok(stringSet, " ");
    for (int i = 0; i < cardinality; i++){
        set[i] = atoi(token);
        token = strtok(NULL, " ");
    }

    return set;
}

int countSets(FILE * fp){
    int sets = 0;
    int stringbuffer = 255;
    char line[stringbuffer];
    char temp[stringbuffer];
    char * token;

    fgets(line, stringbuffer, fp);
    line[strcspn(line, "\n")] = 0;
    token = strtok(line, " ");
    sets = atoi(token);

    return sets;
}

int getTarget(FILE * fp){
    int target = -1;
    int stringbuffer = 255;
    char line[stringbuffer];
    char * token;

    fgets(line, stringbuffer, fp);
    line[strcspn(line, "\n")] = 0;

    token = strtok(line, " ");
    target = atoi(token);

    return target;
}

int getCardinality(char * stringSet){
    int cardinality = 0;
    int stringbuffer = 255;
    char * token;
    token = strtok(stringSet, " ");

    do{
        token = strtok(NULL, " ");
        cardinality++;
    } while (token!=NULL);

    return cardinality;
}

void getStringSet(char * stringSet, FILE * fp){
    int stringbuffer = 255;
    char * token;

    fgets(stringSet, stringbuffer, fp);
    stringSet[strcspn(stringSet, "\n")] = 0;
}

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void printPrompt (int * set, int cardinality, int target){
    printf("\nFor S = {");
    int i;
    for (i = 0; i < cardinality-1; i++) printf("%d, ", set[i]);
    printf("%d}, k = %d\n", set[i], target);
    printf("Solutions:\n");
}
