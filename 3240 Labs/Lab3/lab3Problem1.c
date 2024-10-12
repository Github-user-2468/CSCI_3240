#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, *arr, i;
    //getting the size of array
    scanf("%d", &n);
    arr = (int*) malloc(n * sizeof(int));

    //getting the element of the array
    for(i = 0; i < n; i++) {
        scanf("%d", arr + i);
    }

    //TODO: Write the logic to reverse the array "arr" here  
    int left = 0;
    int right = n - 1;
    while (left < right) {
        // Swap elements at left and right indices
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        // Move index towards the center
        left++;
        right--;
    }

    
    //END TODO
      
    // Printing the resulting reversed array
    for(i = 0; i < n; i++)
        printf("%d ", *(arr + i));
    printf("\n");
    return 0;
}