#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>

#define sys_kernel_2d_memcpy 448

int main(int argc, char const *argv[])
{
        float real_arr[4][4];
        float c=1.25;
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        arr[i][j]=c++;
                }
        }
        printf("Real Array: ");
        printf("\n");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        printf("%f ", arr[i][j]);
                }
                printf("\n");
        }

        float exp_arr[4][4];
        
        long result = syscall(sys_kernel_2d_memcpy, exp_arr, real_arr, 4, 4);
        if(result!=0)
        {
                printf("Error in kernel.");
                printf("\n");
                return 1;
        }
        printf("\nCopied Array\n");
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < 4; j++)
                {
                        printf("%f ", exp_arr[i][j]);
                }
                printf("\n");
        }
}
