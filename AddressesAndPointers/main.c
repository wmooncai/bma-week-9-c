//
//  main.c
//  AddressesAndPointers
//
//  Created by Wally on 11/12/12.
//  Copyright (c) 2012 W M. All rights reserved.
//

#include <stdio.h>
#include <math.h>

#define SUCCESS 0
#define FAIL -1

/* #############################################################################

 XCODE HW A:
 Use math library and add code to main.c displays sine of 1 radian
    to 3 decimal points.  Should = 0.841
 
 XCODE HW B:
 Program counts backwards from 99 to 0 by 3, printing each #.
 If # is divisible by 5, print "Found one!". Ex:
 
 - 99
 - 96
 - 93
 - 90
 - Found one!
 - 87
 - ...
 
 HW C:
 Write a program to show you how much memory a float consumes.
 
 HW D:
 Modify cartesianToPolar() to handle reverse conversion, using &ptrs with NULL
    as flags for direction.
 
 ############################################################################ */

int week8ClassPointerDemo()
{
    printf("#############################\n\n");
    printf("Week 8 Class Lecture by James\n");
    printf("\n#############################\n\n");
    
    printf("Pointers lecture examples by James\n\n");
    
    // Part A
    int i = 17;
    printf("Part A: i stores its value at: %p\n\n", &i);
    
    // Part B - since main() is a func and in memory, we can see its address
    printf("Part B: this function starts at: %p\n\n", week8ClassPointerDemo);
    
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
    
    return SUCCESS;
}

// *****************************************************************************

int week9HWPartA()
{
    printf("HW Part A:\n\nsin(1.0) = %.3f\n\n", sin(1.0));
    
    printf("----------------------------\n\n");
    
    return SUCCESS;
}

// *****************************************************************************

int week9HWPartB()
{
    printf("HW Part B:\n\nCountdown from 99 to 0\n\n");
    
    for (int i=99; i > -1; i = i - 3)
    {
        printf("- %d\n", i);
        if ( ( i % 5) == 0 ) printf("- Found one!\n");
    }

    printf("\n----------------------------\n\n");
    
    return SUCCESS;
}

// *****************************************************************************

int week9HWPartC()
{
    printf("HW Part C:\n\nThe size of a float is %ld bytes.\n\n"
           , sizeof(float));

    printf("----------------------------\n\n");

    return SUCCESS;
}

// *****************************************************************************

int xlateCartesianPolar(double *pX, double *pY, double *pRad, double *pThet)
{
    
    // Calculate theta
    // http://en.wikipedia.org/wiki/Polar_coordinate#Converting_between_polar_and_Cartesian_coordinates
    
    if ( (pX != NULL) & (pY != NULL) ) {
        
        // Store the radius in the supplied address
        // *pY = 0.0;
        // *pX = 0.0;
        *pRad = sqrt( (*pX * *pX) + (*pY * *pY) );
        
        if (*pX == 0.0) {
            
            if (*pY == 0.0 ) {
                *pThet = 0.0;          // technically considered undef
            } else if (*pY > 0.0) {
                *pThet = -M_PI_2/2;
            } else if (*pY < 0.0){
                *pThet = -M_PI_2;
            }
            
        } else if (*pX < 0.0) {
            
            if (*pY >= 0.0) {
                *pThet = atan( *pY / *pX ) + M_PI_2;
            } else *pThet = atan( *pY / *pX ) - M_PI_2;
            
        } else { // x > 0
            *pThet = atan( *pY / *pX );
        }
        
    } else if ( (pRad != NULL) && (pThet != NULL) ) {
        printf("radius: %.2f, theta: %.2f", *pRad, *pThet);
        *pX = *pRad * cos(*pThet);
        *pY = *pRad * sin(*pThet);
        
    } else {        // ERROR - at least one of the parameters is not set
        printf("ERROR: Improper parameters passed to xlateCartesianPolar().\n");
        return FAIL;
    }
    
    // Store theta in the supplied address
    // - Already done directly above.
    
    return SUCCESS;
}

// *****************************************************************************

int cartesianToPolar(double *pXcoord, double *pYcoord, double *pR, double *pT)
{
    /* This is a wrapper to maintain the original function name, as I felt that
        xlateCartesianPolar() made more sense given its new bi-directional
        nature.
     */
    
    return xlateCartesianPolar(pXcoord, pYcoord, pR, pT);
}


// *****************************************************************************

int week9HWPartD()
{
    printf("HW Part D:\n\nConversion between Cartesian and Polar coordinates.  ");
    printf("See book.\n\n");
    
    double x = 3.0;
    double *pX = &x;
    
    double y = 4.0;
    double *pY = &x;
    
    double radius = 0.0;
    double *pRadius = &radius;
    
    double angle = 0.0;
    double *pAngle = &angle;
    
    // Cartesian to Polar
    if(xlateCartesianPolar(pX, pY, pRadius, pAngle) == SUCCESS) {
        printf("Cartesian to Polar: (%.2f, %.2f) becomes (%.2f radians, %.2f degrees)\n\n"
               , *pX, y, radius, angle);
    } else printf("xlateCartesianPolar() failed.\n\n");
    
    // Polar to Cartesian
    // Use angle and radius from previous calculation
    
    if(xlateCartesianPolar(pX, pY, pRadius, pAngle) == SUCCESS)
        printf("Polar to Cart: (%.2f, %.2f) becomes (%.2f radians, %.2f degrees)\n\n"
               , *pX, y, radius, angle);
    else printf("xlateCartesianPolar() failed.\n\n");
    
    // Foobarred parameters passed to xlateCartesianPolar()
    pX = NULL;
    pAngle = NULL;
    if(xlateCartesianPolar(pX, pY, pRadius, pAngle) == SUCCESS)
        printf("fooBar: %.2f, %.2f becomes (%.2f radians, %.2f degrees)\n\n"
               , *pX, y, radius, angle);
    else printf("ERROR: xlateCartesianPolar() returned failure.\n\n");
    
    return SUCCESS;
}

// *****************************************************************************

int main(int argc, const char * argv[])
{

    week8ClassPointerDemo(); // Week 8 class pointer lecture examples
    
    printf("\n\n############################\n\n");
    printf("      Week 9 Homework\n");
    printf("\n############################\n\n");

    week9HWPartA(); // sin() calculation
    
    week9HWPartB(); // Countdown
    
    week9HWPartC(); // Size of float
    
    week9HWPartD(); // Cartesian - Polar Conversion

    return SUCCESS;
}

