#include <stdio.h>
#include <stdlib.h>
#include<pthread.h>
#include <sys/time.h>
#include <string.h>

struct timeval stop, start;
int **A;
int **B;
int **C;
int rowA;
int colA;
int rowB;
int colB;
//counters for number of threads
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
char *matA_file;
char *matB_file;
char *matOut_file;
char file_name[40];
FILE *fout;

void readMatrix(FILE *fp, int **arr, int row, int col) {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int number;
            fscanf(fp, "%d", &number);
            arr[i][j] = number;
        }
    }
}

void readFile1() {
    strcpy(file_name, "");
    strcat(file_name, matA_file);
    strcat(file_name, ".txt");
	// printf("%s\n", file_name);
    FILE *fp1;
    fp1 = fopen(file_name, "r");
    if (fp1 == NULL) {
        perror("Error in opening the file.\n");
        exit(EXIT_FAILURE);
    } else {
        fscanf(fp1, "row=%d col=%d", &rowA, &colA);
        //memory allocation of  first matrix
        A = (int **) malloc(rowA * sizeof(int *));
        for (int i = 0; i < rowA; i++) {
            A[i] = (int *) malloc(colA * sizeof(int));
        }
        readMatrix(fp1, A, rowA, colA);
        fclose(fp1);
    }
}

void readFile2() {
    strcpy(file_name, "");
    strcat(file_name, matB_file);
    strcat(file_name, ".txt");

    FILE *fp2;
    fp2 = fopen(file_name, "r");
    if (fp2 == NULL) {
        perror("Error in opening the file.\n");
        exit(EXIT_FAILURE);
    } else {
        fscanf(fp2, "row=%d col=%d", &rowB, &colB);
        B = (int **) malloc(rowB * sizeof(int *));
        for (int i = 0; i < rowB; i++) {
            B[i] = (int *) malloc(colB * sizeof(int));
        }
        readMatrix(fp2, B, rowB, colB);
        fclose(fp2);
    }
}


void outputMatrix(int s) {
    strcpy(file_name, "");
    strcat(file_name, matOut_file);

    if (s == 1) {
        strcat(file_name, "_per_matrix.txt");
        fout = fopen(file_name, "w");
        if (fout == NULL) {
            perror("Can't open the file");
        }
        fprintf(fout, "%s", "--------------------Thread per Matrix--------------------\n");
        fprintf(fout, "row = %d     col=%d\n", rowA, colB);
    } else if (s == 2) {
        strcat(file_name, "_per_row.txt");
        fout = fopen(file_name, "w");
        if (fout == NULL) {
            perror("Can't open the file");
        }
        fprintf(fout, "%s", "--------------------Thread per row--------------------\n");
        fprintf(fout, "row = %d     col=%d\n", rowA, colB);
    } else if (s == 3) {
        strcat(file_name, "_per_element.txt");
        fout = fopen(file_name, "w");
        if (fout == NULL) {
            perror("Can't open the file");
        }

        fprintf(fout, "%s", "--------------------Thread per element--------------------\n");
        fprintf(fout, "row = %d     col=%d\n", rowA, colB);
    }
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            fprintf(fout, "%d\t", C[i][j]);
        }
        fprintf(fout, "\n");
    }
}

void clearOutputMatrix() {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            C[i][j] = 0;
        }
    }
}

struct parameters {
    int row_A;
    int col_B;
};

void* threadPerElement(void *para) {
    struct parameters *data = (struct parameters *) para;
    int i = data->row_A;
    int j = data->col_B;
    int sum = 0;
    for (int k = 0; k < rowB; k++) {
        sum += A[i][k] * B[k][j];
    }
    C[i][j] = sum;
    //kill the thread
    pthread_exit(NULL);

}

void method_3() {
    gettimeofday(&start, NULL);
    pthread_t t[rowA][colB];
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            struct parameters *thread_data = malloc(sizeof(struct parameters));
            thread_data->row_A = i;
            thread_data->col_B = j;
            //create thread per element and pass the column and row
            int rc = pthread_create(&t[i][j], NULL, &threadPerElement, (void *) thread_data);
            if (rc) {
                perror("failed to create thread");
                exit(0);
            }
            cnt3++;
        }
    }
    //for loop for joining thread
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            pthread_join(t[i][j], NULL);
        }
    }
    gettimeofday(&stop, NULL); //end checking time
    printf("--------------------Thread per element--------------------\n");
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu ms\n", stop.tv_usec - start.tv_usec);
    printf("number of threads of thread per element = %d\n", cnt3);
    outputMatrix(3);
    fclose(fout);
    clearOutputMatrix();
}


void* threadPerRow(void *rowNum) {
    long i = (long) rowNum;
    for (int j = 0; j < colB; j++) {
        int sum = 0;
        for (int k = 0; k < rowB; k++) {
            sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
    }
    //kill the thread
    pthread_exit(NULL);
}

void method_2() {
    // thread per row
    gettimeofday(&start, NULL); //start checking time
    pthread_t t[rowA];
    //creating thread
    for (long i = 0; i < rowA; ++i) {
        int row = pthread_create(&t[i], NULL, &threadPerRow, (void *) i);
        if (row) {
            perror("failed to create thread");
            exit(0);
        }
        cnt2++;
    }
    //joining its threads
    for (int i = 0; i < rowA; ++i) {
        if (pthread_join(t[i], NULL) != 0) {
            perror("failed joint thread");
        }
    }
    gettimeofday(&stop, NULL); //end checking time
    printf("--------------------Thread per row--------------------\n");
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu ms\n", stop.tv_usec - start.tv_usec);
    printf("number of threads of thread per row = %d\n", cnt2);
    outputMatrix(2);
    fclose(fout);
    clearOutputMatrix();


}

void singleThread() {
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colB; j++) {
            int sum = 0;
            for (int k = 0; k < rowB; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    cnt1++;
}

void method_1() {
    gettimeofday(&start, NULL); //start checking time
    singleThread();
    gettimeofday(&stop, NULL); //end checking time
    printf("--------------------Thread per matrix--------------------\n");
    printf("Seconds taken %lu\n", stop.tv_sec - start.tv_sec);
    printf("Microseconds taken: %lu ms\n", stop.tv_usec - start.tv_usec);
    printf("number of threads of thread per matrix = %d\n", cnt1);
    //write in the output
    outputMatrix(1);
    fclose(fout);
    clearOutputMatrix();
}


int main(int argc, char **argv) {

    if (argc == 4) {
        matA_file = argv[1];
        matB_file = argv[2];
        matOut_file = argv[3];
    } else {
        //default
        matA_file = "test1/a";
        matB_file = "test1/b";
        matOut_file = "test1/c";
    }

    readFile1();
    readFile2();
    //condition of multiplication
    if (colA != rowB) {
        perror("Not suitable for multiplication");
        exit(0);
    }
    //memory location for output
    C = (int **) malloc(rowA * sizeof(int *));
    for (int i = 0; i < rowA; i++) {
        C[i] = (int *) malloc(colB * sizeof(int));
    }
    method_1();
    method_2();
    method_3();

    //de allocation
    free(A);
    free(B);
    free(C);

    return 0;
}

