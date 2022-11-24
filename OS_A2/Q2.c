#include <linux/export.h>

#include <linux/slab.h>

#include <linux/uaccess.h>

#include <linux/kernel.h>

#include <linux/syscalls.h>

asmlinkage long sys_memcpy_2d(float **dest, float **src, int rows, int cols)
{
    int i, j;
    float **dest_kernel = (float **)kmalloc(sizeof(float *) * rows, GFP_KERNEL);
    float **src_kernel = (float **)kmalloc(sizeof(float *) * rows, GFP_KERNEL);
    int err = 0;
    err = copy_from_user(dest_kernel, dest, sizeof(float *) * rows);
    if (err)
        return -EFAULT;
    err = copy_from_user(src_kernel, src, sizeof(float *) * rows);
    if (err)
        return -EFAULT;
    for (i = 0; i < rows; i++)
    {
        err = copy_from_user(dest_kernel[i], src_kernel[i], sizeof(float) * cols);
        if (err)
            return -EFAULT;
    }
    err = copy_to_user(dest, dest_kernel, sizeof(float *) * rows);
    if (err)
        return -EFAULT;
    kfree(dest_kernel);
    kfree(src_kernel);
    return 0;
}
EXPORT_SYMBOL(sys_memcpy_2d);
/*       float **dest,       float **src,       int rows,       int cols)       */
int insmod_test(void)
{
    int rows = 3;
    int cols = 3;
    float **dest = (float **)kmalloc(sizeof(float *) * rows, GFP_KERNEL);
    float **src = (float **)kmalloc(sizeof(float *) * rows, GFP_KERNEL);
    int i, j;
    for (i = 0; i < rows; i++)
    {
        dest[i] = (float *)kmalloc(sizeof(float) * cols, GFP_KERNEL);
        src[i] = (float *)kmalloc(sizeof(float) * cols, GFP_KERNEL);
        for (j = 0; j < cols; j++)
        {
            src[i][j] = i + j;
        }
    }
    sys_memcpy_2d(dest, src, rows, cols);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printk(KERN_INFO "i=%d j=%d dest[i][j]=%f\n", i, j, dest[i][j]);
        }
    }
    return 0;
}
module_init(insmod_test);

// #include <stdio.h>
// #include <sys/syscall.h>
// #include <unistd.h>

// #define sys_kernel_2d_memcpy 448


// int main(int argc, char const *argv[])
// {
//         float arr[4][3];
//         float c=1.5;
//         for (int i = 0; i < 4; i++)
//         {
//                 for (int j = 0; j < 3; j++)
//                 {
//                         arr[i][j]=c++;
//                 }
//         }
//         printf("original array\n");
//         for (int i = 0; i < 4; i++)
//         {
//                 for (int j = 0; j < 3; j++)
//                 {
//                         printf("%f ", arr[i][j]);
//                 }printf("\n");
//         }

//         float arr2[4][3]; // new array
        
//         long res = syscall(sys_kernel_2d_memcpy, arr2, arr, 4, 3);
//         if(res!=0)
//         {
//                 printf("error in kernel\n");
//                 return 1;
//         }
//         printf("\ncopied array\n");
//         for (int i = 0; i < 4; i++)
//         {
//                 for (int j = 0; j < 3; j++)
//                 {
//                         printf("%f ", arr2[i][j]);
//                 }printf("\n");
//         }
// }
