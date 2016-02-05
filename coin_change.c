#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 10000
#define MIN(x, y) ((x) < (y) ? (x) : (y))

void fillArray(char* inputFile, int line, int);
int numLinesInFile(char* inputFile);
void getLineInFile(char* inputFile, int target_line, char* string);
int numElementsInLine (char* inputFile, int line );
void nullTermLine (char* string);
int elementsInString(char* string);
void fillNewArray(char* inputFile, int line, int* array, int numElements);
int changeAmount(char* inputFile, int target_line);
void nullTermLine(char* string);
void outOfRange(int amount);

int test_bruteForce(int amount, int coins[], int numElements, char *inputFile);
int test_bruteForce_aux(int amount, int coins[], int numElements, int *C);

void test_alg2_greedy(int *array, int numElements, int amount, char *inputFile);
void alg2_greedy(int *array, int numElements, int amount);
void test_changedP(int *V, int size, int A, char *inputFile);
void changedP(int *V, int size, int A);
int changeslow(int amount, int coins[], int numElements, int C[]);

int main(int argc, char *argv[]){

    printf("\nProject 2: Evaluation of Coin Change Algorithms\n");
	
    if(argc != 2){
        printf("Usage: executablename filename\n");
        return 1;
    } 
        
    FILE *fp;               //check to see if file exists before continuing
    fp = fopen(argv[1], "r");   

    if(fp == NULL){
        printf("Cannot open file or file does not exist\n");
        return 1;
    }
    fclose(fp);

    int i;
    int numElements = 0;
    char *inputFile = argv[1];  //input file from commandline

    int numLines = numLinesInFile(inputFile);   //check number of lines in file //currently displays an extra line*******

    int numProblems = numLines / 2; //number of problems to run algorithm 

    if ((numLines % 2) == 1){
        numProblems++;  //increment numproblems if odd number of lines is detected
    }

    int coinArray = 0;  //array containing coin value
    int amountLine = 0;    //line in file containing amount
    int amount = 0; //amount for problem
    clock_t timer;
    srand (time(NULL));

    //Loop through each problem in file to run algorithm
    for(i = 0; i < numProblems; i++){
        coinArray = (2 * i);    //every other line is the coin array, ex. 0, 2, 4...
        numElements = numElementsInLine(inputFile, coinArray);  //get number of elements in coin array

        int* array = (int*)malloc(numElements * (sizeof(int))); //allocate array

        fillNewArray(inputFile, coinArray, array, numElements);

        amountLine = coinArray + 1;
        

        amount = changeAmount(inputFile, amountLine);   //get the amount in the line of the file
        
        printf("\nRunning Algorithm 1: Brute Force\n");
        int correct = test_bruteForce(amount, array, numElements, inputFile);
        if ( correct == 0){
            printf("Algorithm 1: Results written to file\n");
        }
        
        printf("\n\nRunning Algorithm 2: GreedyP\n");
		//Compare algs for accuracy, write to file 
		test_alg2_greedy(array, numElements, amount, inputFile); //start algorithm
		printf("Algorithm 2: Results written to file\n");

        printf("\nRunning Algorithm 3: changedP\n");
        test_changedP(array, numElements, amount, inputFile);  //Coin array, coin array size, int to change
        printf("Algorithm 3: Results written to file\n");

        free(array);
	}
	
	
////////////////////////////////////////////////////
//
//
///////////////////////////////////////////////////

//Start generating test data

    int algNum, A = 2010;
    int V[5] = {1, 5, 10, 25, 50};
    int sizeArr = 5;
    int B = 5;
    int t, tot;

    printf("\n\nPress any key to run Algorithms for Question 4 Experimental Analysis: Brute ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nB:\n");
    while(B <= 60){
        int *C = (int*)malloc((sizeArr) * sizeof(int));
        for(t = 0; t < sizeArr; t++){
            C[t] = 0;
        }
        timer = clock();
        int tot = changeslow(B, V, sizeArr, C);
        timer = clock() - timer; 
        printf("count: %d\tamt: %d\t\ttime: %f sec\n", tot, B, (float)timer / (float)CLOCKS_PER_SEC);
        B += 3;
    }    
       

    printf("\n\nPress any key to run Algorithms for Question 4 Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nA:\n");
    while(A <= 2200){
        timer = clock();
        alg2_greedy(V, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A, (float)timer / (float)CLOCKS_PER_SEC);
        A += 5;
    }    

    printf("\nPress any key to run Algorithms for Question 4 Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2010;
    while(A <= 2200){
        
        timer = clock();
        changedP(V, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A, (float)timer / (float)CLOCKS_PER_SEC);
        A += 5;
    }

    int V1[7] = {1, 2, 6, 12, 24, 48, 60};
    sizeArr = 7;
    B = 5;
    
    printf("\n\nPress any key to run Algorithms for Question 5a Experimental Analysis: Brute ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nB:\n");
    while(B <= 35){
        printf("Amount: %d ", B);
        int *C = (int*)malloc((sizeArr) * sizeof(int));
        for(t = 0; t < sizeArr; t++){
            C[t] = 0;
        }
        timer = clock();
        tot =  changeslow(B, V1, sizeArr, C);
        timer = clock() - timer; 
        printf("count: %d\tamt: %d\t\ttime: %f sec\n", tot, B, (float)timer / (float)CLOCKS_PER_SEC);

        B += 2;
    }  
    
    
    
    printf("\nPress any key to run Algorithms for Question 5a Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    while(A <= 2200){    
        timer = clock();
        alg2_greedy(V1, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A, (float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }
    
    printf("\nPress any key to run Algorithms for Question 5a Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    while(A <= 2200){
        timer = clock();
        changedP(V1, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A, (float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }

    int V2[5] = {1, 6, 13, 37, 150};
    sizeArr = 5;     
    B = 5;


    printf("\n\nPress any key to run Algorithms for Question 5b Experimental Analysis: Brute ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nB:\n");
    while(B <= 35){
        int *C = (int*)malloc((sizeArr) * sizeof(int));
        for(t = 0; t < sizeArr; t++){
            C[t] = 0;
        }
        timer = clock();
        tot = changeslow(B, V2, sizeArr, C);
        timer = clock() - timer; 
        printf("count: %d\tamt: %d\t\ttime: %f sec\n", tot, B, (float)timer / (float)CLOCKS_PER_SEC);
        B += 2;
    }  
    

    printf("\nPress any key to run Algorithms for Question 5b Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    while(A <= 2200){
        timer = clock();
        alg2_greedy(V2, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A,(float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }
    
    printf("\nPress any key to run Algorithms for Question 5b Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    while(A <= 2200){
        timer = clock();
        changedP(V2, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A,(float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }
    
    int V6[16] = {1,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};  
    sizeArr = 16;
    B=0;
    printf("\n\nPress any key to run Algorithms for Question 6 Experimental Analysis: Brute ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nB:\n");
    while(B <= 22){
        int *C = (int*)malloc((sizeArr) * sizeof(int));
        for(t = 0; t < sizeArr; t++){
            C[t] = 0;
        }
        timer = clock();
        tot = changeslow(B, V6, sizeArr, C);
        timer = clock() - timer; 
        printf("count: %d\tamt: %d\t\ttime: %f sec\n", tot, B, (float)timer / (float)CLOCKS_PER_SEC);
        B += 2;
    }
    
    
    printf("\n\nPress any key to run Algorithms for Question 6 Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    sizeArr = 16;    
    while(A <= 2200){
        timer = clock();
        alg2_greedy(V6, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n", A,(float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }
    
    printf("\n\nPress any key to run Algorithms for Question 6 Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 2000;
    while(A <= 2200){
        timer = clock();
        changedP(V6, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);
        A++;
    }

    int V7[16] = {1,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};    
    printf("\n\nPress any key to run Algorithms for Question 7 Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 10000;
    sizeArr = 16;    
    while(A <= 500000){
        timer = clock();
        alg2_greedy(V7, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);
        A += 10000;
    }

    printf("\n\nPress any key to run Algorithms for Question 7 Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    A = 10000;
    sizeArr = 16;    
    while(A <= 500000){
        timer = clock();
        changedP(V7, sizeArr, A);
        timer = clock() - timer; 
        printf("\tamt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);
        A += 10000;
    }
    
    int VA[3] = {1, 3, 5};
    int VB[5] = {1, 3, 5, 7, 9};
    int VC[10] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int VD[15] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
    int VE[20] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39};
    int VF[25] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49};
    int VG[30] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59};
    int VH[35] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69};  
    int VI[40] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79};
    int VJ[45] = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,73,75,77,79,81,83,85,87,89};

    printf("\n\nPress any key to run Algorithms for Question 8 Experimental Analysis: Greedy  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\nA = 500000");
    printf("\nV = 3\n");
    
    A = 500000;
    sizeArr = 3;    
    timer = clock();
    alg2_greedy(VA, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 5\n");
    sizeArr = 5;    
    timer = clock();
    alg2_greedy(VB, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 10\n");
    sizeArr = 10;    
    timer = clock();
    alg2_greedy(VC, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 15\n");
    sizeArr = 15;    
    timer = clock();
    alg2_greedy(VD, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 20\n");
    sizeArr = 20;    
    timer = clock();
    alg2_greedy(VE, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 25\n");
    sizeArr = 25;    
    timer = clock();
    alg2_greedy(VF, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 30\n");
    sizeArr = 30;    
    timer = clock();
    alg2_greedy(VG, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 35\n");    
    sizeArr = 35;    
    timer = clock();
    alg2_greedy(VH, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 40\n");
    sizeArr = 40;    
    timer = clock();
    alg2_greedy(VI, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\nV = 45\n");
    sizeArr = 45;    
    timer = clock();
    alg2_greedy(VJ, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    printf("\n\nPress any key to run Algorithms for Question 8 Experimental Analysis: Brute ");
    scanf("%d", &algNum);
    algNum = getchar();

    B = 30;
    sizeArr = 3;
    printf("\nB: 30\n");
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    int* C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    tot = changeslow(B, VA, sizeArr, C);
    timer = clock() - timer; 
    printf("count: %d\tamt: %d\t\ttime: %f sec\n", tot, B, (float)timer / (float)CLOCKS_PER_SEC);

    free(C);
    
    sizeArr = 5;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VB, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 10;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VC, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 15;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VD, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 20;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VE, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 25;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VF, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 30;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VG, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 35;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VH, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    sizeArr = 40;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VI, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    
    sizeArr = 45;
    printf("Amount: %d\tArray Size:%d", B, sizeArr);
    C = (int*)malloc((sizeArr) * sizeof(int));

    for(t = 0; t < sizeArr; t++){
        C[t] = 0;
    }
    timer = clock();
    changeslow(B, VJ, sizeArr, C);
    timer = clock() - timer; 
    printf("\ttime: %f sec\n", (float)timer / (float)CLOCKS_PER_SEC);
    free(C);

    printf("\n\nPress any key to run Algorithms for Question 8 Experimental Analysis: Dynamic Programming  ");
    scanf("%d", &algNum);
    algNum = getchar();

    printf("\n");
    printf("\nA = 500000");
    printf("\nV = 3\n");
    
    A = 500000;
    sizeArr = 3;    
    timer = clock();
    changedP(VA, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 5\n");
    sizeArr = 5;    
    timer = clock();
    changedP(VB, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 10\n");
    sizeArr = 10;    
    timer = clock();
    changedP(VC, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 15\n");
    sizeArr = 15;    
    timer = clock();
    changedP(VD, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 20\n");
    sizeArr = 20;    
    timer = clock();
    changedP(VE, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 25\n");
    sizeArr = 25;    
    timer = clock();
    changedP(VF, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 30\n");
    sizeArr = 30;    
    timer = clock();
    changedP(VG, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 35\n");    
    sizeArr = 35;    
    timer = clock();
    changedP(VH, sizeArr, A);
    timer = clock() - timer; 
    printf("\tamt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 40\n");
    sizeArr = 40;    
    timer = clock();
    changedP(VI, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);


    printf("\nV = 45\n");
    sizeArr = 45;    
    timer = clock();
    changedP(VJ, sizeArr, A);
    timer = clock() - timer; 
    printf("\namt: %d\ttime: %f sec\n",A, (float)timer / (float)CLOCKS_PER_SEC);

    
    return 0;

}

int test_bruteForce(int amount, int coins[], int numElements, char *inputFile){  //Amount = A, coins[] = V, C[] = num coins
    int i;

    
    int *C = (int*)malloc((numElements) * sizeof(int));
    for(i = 0; i < numElements; i++){
        C[i] = 0;
    }
    
    if (amount > 70){
        outOfRange(amount);
        
        char new_filename[MAX_SIZE];    //create a new filename
        strncpy(new_filename, inputFile, MAX_SIZE-1);   //copy filename
        //const char extension = ".txt";


        //check that filename 
        if(strstr(new_filename, ".txt") != NULL){
        new_filename[strlen(new_filename) - 4] = '\0'; //null term filename
        }


        char outputFilename[MAX_SIZE-1];    //create output file
        strncpy(outputFilename, new_filename, MAX_SIZE-1);  //copy filename
        strncat(outputFilename, "change.txt", MAX_SIZE-1);  //cat new filename change.txt
        
        FILE* outputResults = fopen(outputFilename, "a");   //open and append to file
        
        fprintf(outputResults, "%s", "Brute Force Algorithm was unable to run in a reasonable amount of time.\n\n\n");
        
        fclose(outputResults);  
        free(C);
        return 1;
        
    }
    
    int result = test_bruteForce_aux(amount, coins, numElements, C);  //Run recursion
    
    char new_filename[MAX_SIZE];    //create a new filename
    strncpy(new_filename, inputFile, MAX_SIZE-1);   //copy filename
    //const char extension = ".txt";


    //check that filename 
    if(strstr(new_filename, ".txt") != NULL){
        new_filename[strlen(new_filename) - 4] = '\0'; //null term filename
    }


    char outputFilename[MAX_SIZE-1];    //create output file
    strncpy(outputFilename, new_filename, MAX_SIZE-1);  //copy filename
    strncat(outputFilename, "change.txt", MAX_SIZE-1);  //cat new filename change.txt

    FILE* outputResults = fopen(outputFilename, "a");   //open and append to file

    //Output results to new file
    fprintf(outputResults, "%s", "Brute Force\n");
    fprintf(outputResults, "%c", '[');

    for(i = 0; i < numElements; i++){
        if(i != 0){
            fprintf(outputResults, "%s", ", ");
        }
        fprintf(outputResults, "%d", C[i]);
    }

    fprintf(outputResults, "%c%c", ']', '\n');
    fprintf(outputResults, "%d\n", result);

    fclose(outputResults);  
    free(C);
    return 0;
}

void outOfRange(int amount){
    printf("Warning: amount %d is too much for brute force to handle.\n", amount);
    printf("Therefore, we'll move on to the next algorithm");

    
}

int test_bruteForce_aux(int V, int coins[], int m, int C[]){  //Amount = A, coins[] = V, C[] = num coins
// base case
    
    if (V == 0){
        return 0;
    }
    // Initialize result
    int result = INT_MAX;
    
    // Try every coin that has smaller value than V
    for (int i=0; i<m; i++)
    {
        if (coins[i] <= V)
        {
            for (int k = 0; k < m; k++){
                C[k] = 0;
            }
            int sub_result = test_bruteForce_aux(V - coins[i], coins, m, C);
            C[i] = C[i] + 1;
            
            // Check for INT_MAX to avoid overflow and see if
            // result can minimized
            if (sub_result != INT_MAX && sub_result + 1 < result)
                result = sub_result + 1;
        }
    }
    return result;

}

int changeslow(int V, int coins[], int m, int C[]){
    // base case
    
    if (V == 0){
        return 0;
    }
    // Initialize result
    int res = INT_MAX;
    
    // Try every coin that has smaller value than V
    for (int i=0; i<m; i++)
    {
        if (coins[i] <= V)
        {
            for (int k = 0; k < m; k++){
                C[k] = 0;
            }
            int sub_res = test_bruteForce_aux(V - coins[i], coins, m, C);
            C[i] = C[i] + 1;
            
            // Check for INT_MAX to avoid overflow and see if
            // result can minimized
            if (sub_res != INT_MAX && sub_res + 1 < res)
                res = sub_res + 1;
        }
    }
    return res;
    
    
    
}


void test_alg2_greedy(int *array, int numElements, int amount, char *inputFile){
    //Start at last element of array (largest value coin possible)
    //Subtract value of this coin from amount
    //Repeat
    int i;
    int min_coins = 0;

    int* result = (int*)malloc(numElements * sizeof(int));
    for(i = 0; i < numElements; i++){
        result[i] = 0;  //initialize array and set to 0
    }

    int last_element = numElements - 1; //last element in array
    for(i = last_element; i >= 0; i--){
        
        while(array[i] <= amount){
            amount = amount - array[i]; //subtract value of this coin from amount of change to be made
            result[i]++;
            min_coins++;

            if(amount <= 0){
                break;      //break out if amount is zero
            }
        }

        if(amount <= 0){
            break;      //break out if amount is zero or less
        }
    }

    char new_filename[MAX_SIZE];    //create a new filename
    strncpy(new_filename, inputFile, MAX_SIZE-1);   //copy filename
    //const char extension = ".txt";


    //check that filename 
    if(strstr(new_filename, ".txt") != NULL){
        new_filename[strlen(new_filename) - 4] = '\0'; //null term filename
    }


    char outputFilename[MAX_SIZE-1];    //create output file
    strncpy(outputFilename, new_filename, MAX_SIZE-1);  //copy filename
    strncat(outputFilename, "change.txt", MAX_SIZE-1);  //cat new filename change.txt

    FILE* outputResults = fopen(outputFilename, "a");   //open and append to file

    //Output results to new file
    fprintf(outputResults, "%s", "Change Greedy\n");
    fprintf(outputResults, "%c", '[');

    for(i = 0; i < numElements; i++){
        if(i != 0){
            fprintf(outputResults, "%s", ", ");
        }
        fprintf(outputResults, "%d", result[i]);
    }

    fprintf(outputResults, "%c%c", ']', '\n');
    fprintf(outputResults, "%d\n", min_coins);

    fclose(outputResults);  

    free(result);

}


void test_changedP(int *V, int size, int A, char * inputFile){
    int i, j, value = 0, count = 0;
	int **minValTbl;	//Allocate memory for temp table
	int *C = (int*)malloc((size) * sizeof(int));
        for(i = 0; i < size; i++){
            C[i] = 0;
    	}

	minValTbl = (int**)malloc(size * sizeof(int *));
	for(i = 0; i < size; i++){
		minValTbl[i] = (int *)malloc((A + 1) * sizeof(int));
	}

	for(i = 0; i < size; i++){	//i is coin val; No coins in column 0
		minValTbl[i][0] = 0;	//i is number of coins
	}

	for(j = 1; j <= A; j++){	//j is coin val; No coins in column 0
		minValTbl[0][j] = j;	//Tot coins = 1 * number of coins = number of coins
	}

	for(i = 1; i < size; i++){	//Coin val
        for(j = 1; j <= A; j++){	//i is number of coins from 1 up to A
			if(V[i] > j){	//Coin size greater than change amount
				minValTbl[i][j] = minValTbl[i - 1][j];  //Choose prev row
			}else if(V[i] == j){	//Coin size denom of change amount
				minValTbl[i][j] = 1;  //Only need 1 coin
             }else if(V[i] < j){ //Coin size smaller than change amount
				minValTbl[i][j] = MIN((minValTbl[i - 1][j]), (minValTbl[i][j - V[i]] + 1)); //Move back to prev denom and add 1, choose min
            }
        }
	}

    j = A;
    i = size - 1;
    while((j > 0) && (i > 0)){ //Not the last coin
        if(minValTbl[i][j] == minValTbl[i - 1][j]){
            i--;    //Prev row and eval prev coin size
        }else{
            C[i]++;  //Coin is in solution
            value += V[i];
            count++; //Add to total number of coins
            j -= V[i];
        }
    }

    C[0] = A - value;   //The rest are 1
    count += C[0];
    
    
    char new_filename[MAX_SIZE];    //create a new filename
    strncpy(new_filename, inputFile, MAX_SIZE-1);   //copy filename
    //const char extension = ".txt";


    //check that filename 
    if(strstr(new_filename, ".txt") != NULL){
        new_filename[strlen(new_filename) - 4] = '\0'; //null term filename
    }

     char outputFilename[MAX_SIZE-1];    //create output file
    strncpy(outputFilename, new_filename, MAX_SIZE-1);  //copy filename
    strncat(outputFilename, "change.txt", MAX_SIZE-1);  //cat new filename change.txt

    FILE* outputResults = fopen(outputFilename, "a");   //open and append to file

    //Output results to new file
    fprintf(outputResults, "%s", "Dynamic Programming\n");
    fprintf(outputResults, "%c", '[');
    for(i = 0; i < size; i++){
        if(i != 0){
            fprintf(outputResults, "%s", ", ");
        }

        fprintf(outputResults, "%d", C[i]);
    }

    fprintf(outputResults, "%c%c", ']' ,'\n');
    fprintf(outputResults, "%d\n\n", count);

    fclose(outputResults);

	free(C);
    for(i = 0; i < size; i++){
		free(minValTbl[i]);
	}
	free(minValTbl);
}

void alg2_greedy(int *array, int numElements, int amount){
    //Start at last element of array (largest value coin possible)
    //Subtract value of this coin from amount
    //Repeat
    int i;
    int min_coins = 0;
    int val = amount;

    int* result = (int*)malloc(numElements * sizeof(int));
    for(i = 0; i < numElements; i++){
        result[i] = 0;  //initialize array and set to 0
    }

    int last_element = numElements - 1; //last element in array
    for(i = last_element; i >= 0; i--){
        
        while(array[i] <= amount){
            amount = amount - array[i]; //subtract value of this coin from amount of change to be made
            result[i]++;
            min_coins++;

            if(amount <= 0){
                break;      //break out if amount is zero
            }
        }

        if(amount <= 0){
            break;      //break out if amount is zero or less
        }
    }
	printf("count: %d\t", min_coins);
    printf("%c", '[');

    for(i = 0; i < numElements; i++){
        if(i != 0){
            printf("%s", ",");
        }
        printf("%d", result[i]);
    }
    printf("%c", ']');

    free(result);
}

void changedP(int *V, int size, int A){
    int i, j, value = 0, count = 0;
	int **minValTbl;	//Allocate memory for temp table
	int *C = (int*)malloc((size) * sizeof(int));
        for(i = 0; i < size; i++){
            C[i] = 0;
    	}

	minValTbl = (int**)malloc(size * sizeof(int *));
	for(i = 0; i < size; i++){
		minValTbl[i] = (int *)malloc((A + 1) * sizeof(int));
	}

	for(i = 0; i < size; i++){	//i is coin val; No coins in column 0
		minValTbl[i][0] = 0;	//i is number of coins
	}

	for(j = 1; j <= A; j++){	//j is coin val; No coins in column 0
		minValTbl[0][j] = j;	//Tot coins = 1 * number of coins = number of coins
	}

	for(i = 1; i < size; i++){	//Coin val
        for(j = 1; j <= A; j++){	//i is number of coins from 1 up to A
			if(V[i] > j){	//Coin size greater than change amount
				minValTbl[i][j] = minValTbl[i - 1][j];  //Choose prev row
			}else if(V[i] == j){	//Coin size denom of change amount
				minValTbl[i][j] = 1;  //Only need 1 coin
             }else if(V[i] < j){ //Coin size smaller than change amount
				minValTbl[i][j] = MIN((minValTbl[i - 1][j]), (minValTbl[i][j - V[i]] + 1)); //Move back to prev denom and add 1, choose min
            }
        }
	}

    j = A;
    i = size - 1;
    while((j > 0) && (i > 0)){ //Not the last coin
        if(minValTbl[i][j] == minValTbl[i - 1][j]){
            i--;    //Prev row and eval prev coin size
        }else{
            C[i]++;  //Coin is in solution
            value += V[i];
            count++; //Add to total number of coins
            j -= V[i];
        }
    }

    C[0] = A - value;   //The rest are 1
    count += C[0];

	printf("count: %d\t", count);
	printf("[");
	for(i = 0; i < size - 1; i++){printf("%d,", C[i]);}
	printf("%d]", C[size - 1]);

	free(C);
	free(minValTbl);
	minValTbl = NULL;
}

//get number of lines in file
int numLinesInFile(char *inputFile){
    int ch = 0;
    int numLines = 0, numChar = 0;

    FILE *fp;
    fp = fopen(inputFile, "r");
    if(fp == NULL){
        printf("The file %s could not be opened\n", inputFile);
    }
    while(!feof(fp)){
        ch = fgetc(fp);
         if((ch == '\n') && (numChar > 0)){
            numLines++;
            numChar = 0;    //Reset for next line
        }else if(ch == '\n'){
            numChar = 0; 
        }else{
           numChar++;   //Non return character
        }
    }
    fclose(fp);

    return numLines;
}

//get number of elements in line of file
int numElementsInLine(char* inputFile, int target_line){
    int line_num = 0;

    FILE *fp;
    fp = fopen(inputFile, "r");

    if(fp == NULL){
        printf("The file %s could not be opened\n", inputFile);
    }

    char line[MAX_SIZE]; //stores line read

    while(fgets(line, sizeof(line), fp) != NULL){
        if (line_num == target_line){
            break;
        }
        line_num++;
    }

    nullTermLine(line);

    int numElements = 0;
    numElements = elementsInString(line);

   return numElements;
}

//get amount in line of file
int changeAmount(char* inputFile, int target_line){
    int amount = 0;
    int line_num = 0;

    FILE *fp;
    fp = fopen(inputFile, "r");

    if(fp == NULL){
        printf("The file %s could not be opened\n", inputFile);
    }

    char line[MAX_SIZE];

    while(fgets(line, sizeof(line), fp) != NULL){
        if(line_num == target_line){
            break;
        }
        line_num++;
    }

    nullTermLine(line);
    sscanf(line, "%d", &amount);
    fclose(fp);

    return amount;      //return amount in line of file

}

//null terminate string
void nullTermLine(char* string){
    size_t length = strlen(string) - 1;
    if(string[length] == '\n'){
        string[length] = '\0';
    }
}

int elementsInString(char* string){
    int i = 0;
    int comma_count = 0;
    int length = strlen(string);

    for(i = 0; i < length; i++){
        if(string[i] == ','){
            comma_count++;
        }
    }

    if(comma_count == 0){
        return 1;   //number of elements is 1
    } else {
        return (comma_count + 1);
    }
}

void fillNewArray(char* inputFile, int line, int* array, int numElements){
    int i = 0;

    //initialize array
    for(i = 0; i < numElements; i++){
        array[i] = 0;
    }

    char string[MAX_SIZE];
    getLineInFile(inputFile, line, string);

    char* token;
    token = strtok(string, "[,]");
    int currentIdx = 0;
    int current;

    while(token != NULL){

        sscanf(token, "%d", &current);
        if(currentIdx >= numElements){
            break;
        }

        array[currentIdx++] = current;

        //Continue with next token
        token = strtok(NULL, "[,]");
    }


}

void getLineInFile(char *input, int target_line, char* string){
    FILE *fp;
    fp = fopen(input, "r");

    if(fp == NULL){
        perror("Can't open file");
    }  else {
        int line_num = 0;
        char line[MAX_SIZE];

        while(fgets(line, (sizeof(line)), fp) != NULL){
            if(line_num == target_line){
                break;
            }
            line_num++;

        }
    }
}