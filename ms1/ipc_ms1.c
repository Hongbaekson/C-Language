// includes go here
#include<stdio.h>

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
void pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

/* 1- comment out the main when submitting milestone one
   2- Your final milestone one should run perfectly with the following tester program.

   To comment out the main() delete the next two characters after the arrow ->*/

/*int main(void) {
   int iVal;
   double dVal;
   welcome();

   // testing prnTitle()
   printf("listing header and footer with grand total:\n");
   prnTitle();



   // Testing prnFooter()
   prnFooter(1234.5678);
   printf("listing header and footer without grand total:\n");
   prnTitle();
   prnFooter(-1);


   // Testing Pause() and clrKyb()
   pause();


   // Testing getInt()
   printf("Enter an integer: ");
   iVal = getInt();
   printf("You entered: %d", iVal);


   // Testing Get Int Limited
   printf("Enter an integer between 10 an 20: ");
   iVal = getIntLimited(10, 20);
   printf("Your entered %d\n", iVal);


   // Testing Get Double
   printf("Enter a floating point number: ");
   dVal = getDbl();
   printf("You entered: %0.2lf\n", dVal);


   // Tesing Get Double Limited
   printf("Enter a floating point number between 10.00 an 20.00: ");
   dVal = getDblLimited(10.0, 20.0);
   printf("You entered: %0.2lf\n", dVal);



   printf("End of tester program for milestone one!\n");
   return 0;
}

/* End Commenting out the main out*/

// implement your functions for milestone one down here:



void welcome(void) {
    printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle(void) {
    printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n");
    printf("----+---+--------------------+--------+-----+-----+-----+------------|---\n");
}

void prnFooter(double gTotal) {
    printf("--------------------------------------------------------+----------------\n");
    if (gTotal > 0) {
        printf("                                           Grand Total: |%12.2lf\n", gTotal);
    }
}

void clrKyb(void) {
    char input;
    do {
        scanf("%c", &input);
    } while (input != '\n');
}

void pause(void) {
    printf("Press <ENTER> to continue...");
    clrKyb();
}

int getInt(void) {
    char NL = 'x';
    int value;
    
    while (NL != '\n') {
        
        scanf("%d%c", &value, &NL);
        
        if (NL != '\n') {
            clrKyb();
            printf("Invalid integer, please try again: ");
        }
    }
    return value;
}

double getDbl(void) {
    char NL = 'x';
    double value;
    
    while (NL != '\n') {
        
        scanf("%lf%c", &value, &NL);
        
        if (NL != '\n') {
            clrKyb();
            printf("Invalid number, please try again: ");
        }
    }
    return value;
}

int getIntLimited(int lowerLimit, int upperLimit) {
    int value;
    scanf("%d", &value);
    
    while (value < lowerLimit || value > upperLimit) {
        printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
        scanf("%d", &value);
    }
    return value;
}

double getDblLimited(double lowerLimit, double upperLimit) {
    double value;
    scanf("%lf", &value);

    while (value < lowerLimit || value > upperLimit) {
    
    printf("Invalid value, %.6lf< value < %.6lf: ", lowerLimit, upperLimit);
    scanf("%lf", &value);
    }
    return value;
}













/* output
 
 ---=== Grocery Inventory System ===---
 
 listing header and footer with grand total:
Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn
----+---+--------------------+--------+-----+-----+-----+------------|---
--------------------------------------------------------+----------------
Grand Total: |     1234.57
listing header and footer without grand total:
Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn
----+---+--------------------+--------+-----+-----+-----+------------|---
--------------------------------------------------------+----------------
Press <ENTER> to continue...
Enter an integer: abc
Invalid integer, please try again: 10abc
Invalid integer, please try again: 10
You entered: 10
Enter an integer between 10 and 20: 9
Invalid value, 10 < value < 20: 21
Invalid value, 10 < value < 20: 15
Your entered 15
Enter a floating point number: abc
Invalid number, please try again: 2.3abc
Invalid number, please try again: 2.3
You entered: 2.30
Enter a floating point number between 10.00 and 20.00: 9.99
Invalid value, 10.000000< value < 20.000000: 20.1
Invalid value, 10.000000< value < 20.000000: 15.05
You entered: 15.05
End of tester program for milestone one!

*/
