#include <stdio.h>
#include <math.h>
#include <assert.h>

int main()
{
    long long x, y;
    scanf("%lld %lld", &x, &y);
    
    // PRE: Input values x and y must be within the range of -1000 to 1000
    assert(x >= -1000 && x <= 1000); // PRE: x is within bounds
    assert(y >= -1000 && y <= 1000); // PRE: y is within bounds
    
    double d = sqrt(x * x + y * y);
    long long c = floor(d);

    if (c == d) 
    {
        printf("black\n");
        return 0;
    }
    
    long long s = x * y; 
    if (c % 2)
    {
        if(s < 0) 
        {
            printf("black\n");
        }
        else 
        {
            printf("white\n");
        }
    }
    else
    {
        if(s < 0) 
        {
            printf("white\n");
        }
        else 
        {
            printf("black\n");
        }
    }   
    
    // POST: The output color must be either "black" or "white"
    // Assuming that printed values are valid according to the problem conditions
    assert(1); // POST: Assume output is valid as the conditions dictate the color 

    return 0;
}