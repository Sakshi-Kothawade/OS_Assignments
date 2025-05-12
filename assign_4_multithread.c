// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include<unistd.h>

// void* display(void* arg);

// int main()
// {
//     pthread_t tid;
//     char*msg="Hello";
//     pthread_create(&tid, NULL, display, (void*)msg);
//     usleep(5000);

//     return 0;
// }

// void* display(void* arg)

// {
//     char*N=(char*)arg;
//     printf("Message is=%s\n",N);
//     return NULL;
// }

// *****************************************************

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include<unistd.h>

// void* display(void* arg);

// int main()
// {
//     pthread_t tid1;
//     pthread_t tid2;
//     char*msg="Hello";
//     char*world="World";
//     pthread_create(&tid1, NULL, display, (void*)msg);
//     usleep(5000);
//     pthread_create(&tid2, NULL, display, (void*)world);
//     usleep(5000);

//     return 0;
// }

// void* display(void* arg)

// {
//     char*N=(char*)arg;
//     printf("Message is=%s\n",N);
//     return NULL;
// }

// *****************************************************

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>

// void* display(void* arg) {
//     int *N = (int*) arg;
//     printf("Message: %d\n", *N);
//     return NULL;
// }

// int main(){
//     pthread_t tid;
//     int nums[] = {1,2,3,4,5};

//     for(int i=0; i<5; i++){
//         pthread_create(&tid, NULL, display, (void*) &nums[i]);
//     }
    
//     usleep(5000);
//     return 0;
// }

// **************************************************************

// #include <stdio.h>
// #include <pthread.h>
// #include <stdlib.h>
// #include <unistd.h>

// typedef struct{
//     int m;
//     int n;
// }NUM;

// void* add(void* arg) {
//     NUM *M = (NUM*) arg;
//     int sum;
//     sum = M->m + M->n;
//     printf("Sum of %d + %d: %d\n", M->m, M->n, sum);
//     return NULL;
// }

// int main(){
//     pthread_t tid;
//     int a = 5;
//     int b = 6;
    
//     NUM N;
//     N.m = a;
//     N.n = b;

//     pthread_create(&tid, NULL, add, (void*) &N);
//     // usleep(5000);
//     return 0;
// }

// **************************************************************

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int m;
    int n;
} NUM;

void* add(void* arg) {
    NUM *M = (NUM*) arg;
    int sum = M->m + M->n;
    printf("Sum of %d + %d: %d\n", M->m, M->n, sum);
    return NULL;
}

void* subtract(void* arg) {
    NUM *M = (NUM*) arg;
    int diff = M->m - M->n;
    printf("Difference of %d - %d: %d\n", M->m, M->n, diff);
    return NULL;
}

void* multiply(void* arg) {
    NUM *M = (NUM*) arg;
    int product = M->m * M->n;
    printf("Product of %d * %d: %d\n", M->m, M->n, product);
    return NULL;
}

void* divide(void* arg) {
    NUM *M = (NUM*) arg;
    if (M->n != 0) {
        float quotient = (float) M->m / M->n;
        printf("Quotient of %d / %d: %.2f\n", M->m, M->n, quotient);
    } else {
        printf("Division by zero is not allowed!\n");
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2, tid3, tid4;
    int a = 10, b = 2;

    NUM N;
    N.m = a;
    N.n = b;

    pthread_create(&tid1, NULL, add, (void*) &N);
    pthread_create(&tid2, NULL, subtract, (void*) &N);
    pthread_create(&tid3, NULL, multiply, (void*) &N);
    pthread_create(&tid4, NULL, divide, (void*) &N);

    // Wait for threads to complete execution
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    return 0;
}
