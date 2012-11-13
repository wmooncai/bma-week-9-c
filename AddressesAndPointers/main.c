//
//  main.c
//  AddressesAndPointers
//
//  Created by Wally on 11/12/12.
//  Copyright (c) 2012 W M. All rights reserved.
//

#include <stdio.h>
#include <math.h>

void cartesianToPolar(double x, double y, double *rPtr, double *thetaPtr)
{
    // Store the radius in teh supplied address
    *rPtr = sqrt(x * x + y * y);
    
    // Calcs theta
    float theta;
    if (x == 0.0) {
        if (y == 0.0 ) {
            theta = 0.0; // technically considered undef
            
        } else if (y > 0) {
            theta = M_PI_2;
        } else if (y < 0){
            theta = -M_PI_2;
        } else {
            theta = atan(y/x);
        }
    }
    // Store theta in the supplied address
    *thetaPtr = theta;
}


int main(int argc, const char * argv[])
{

    printf("Pointers lecture examples by James\n\n");
    
    // Part A
    int i = 17;
    printf("Part A: i stores its value at: %p\n\n", &i);
    
    // Part B - since main() is a func and in memory, we can see its address
    printf("Part B: this function starts at: %p\n\n", main);
    
    // Part C
    int *addressOfI = &i; // DON'T FORGET THE '*'
    printf("part C: addressOfI (points to i) stores its value at: %p\n\n"
           , addressOfI);
    
    // Part D
    printf("Part D: the int stored at the addressOfI is %d\n\n", *addressOfI);
    
    // Part E
    *addressOfI = 89;
    printf("Part E: Now i is %d\n\n", i);
    
    // Part F - Sizes
    printf("Part F:\nAn int is %zu bytes\n", sizeof(int));
    printf("A pointer is %zu bytes\n", sizeof(int *));

    printf("An int i is %zu bytes\n", sizeof(i));
    printf("A pointer is %zu bytes\n", sizeof(addressOfI));
    
    printf("\n==========================\n\n");
    
    printf("modf() lecture example of splitting Pi by James\n");
    
    double pi = 3.14;
    double integerPart;
    double fractionPart;
    
    // Pass the address of the integerPart as an argument
    fractionPart = modf(pi, &integerPart);
    
    // Find the value
    printf("modf():\nintegerPart = %.0f, fractionPart = %.2f\n"
           , integerPart, fractionPart);
    
    printf("\n==========================\n\n");

    printf("Rectangular to Polar conversion lecture example by James");
    printf("- see book\nContinued from previous modf() example\n");
    printf("Use pi vars above\n");
    
    double x = 3.0;
    double y = 4.0;
    double radius;
    double angle;
    
    cartesianToPolar(x, y, &radius, &angle);
    printf("%.2f, %.2f becomes (%.2f radians, %.2f)\n", x, y, radius, angle);
    
    return 0;
}

