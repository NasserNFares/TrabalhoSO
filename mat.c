#include <stdio.h>
#include <stdlib.h>

int main() {
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            printf("%d ", rand() % 100);
        }
        printf("\n");
    }
    return 0;
}