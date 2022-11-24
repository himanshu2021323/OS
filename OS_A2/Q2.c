#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define sys_kernel_2d_memcpy 448


int main(int argc, char const *argv[])
{
        float arr[4][3];
        float c=1.5;
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        arr[i][j]=c++;
                }
        }
        printf("original array\n");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        printf("%f ", arr[i][j]);
                }printf("\n");
        }

        float arr2[4][3]; // new array
        
        long res = syscall(sys_kernel_2d_memcpy, arr2, arr, 4, 3);
        if(res!=0)
        {
                printf("error in kernel\n");
                return 1;
        }
        printf("\ncopied array\n");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 3; j++)
                {
                        printf("%f ", arr2[i][j]);
                }printf("\n");
        }
}
