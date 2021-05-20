#include <stdio.h>

// define statements go here
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0


/* ms1 prototypes*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
int pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
/* ipc_ms2 prototype*/
int yes(void);  // ms2


struct Item {
    double price;
    int sku;
    int isTaxed;
    int quantity;
    int minQuantity;
    char name[21];
};


/* ms3 prototypes*/

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);




/* Constant double TAX value */

const double TAX = 0.13;




double totalAfterTax(struct Item item){
    
    double total = 0;
    
    if (item.isTaxed == 0) {
        
        total = item.price * item.quantity;
    }
    
    else if (item.isTaxed ==1){
        
        total = item.price * item.quantity + (item.price * item.quantity * TAX);
    }
    
    
    return total;
    
}

int isLowQty(struct Item item){
    
    
    if(item.quantity<item.minQuantity){
        return 1;
    }
    
    else{
        return 0;
    }
    
}
struct Item itemEntry(int sku){
    
    struct Item item;
    
    item.sku = sku;
    printf("        SKU: %d\n",sku);
    printf("       Name: ");
    scanf("%20[^\n]",item.name);
    printf("      Price: ");
    item.price = getDbl();
    printf("   Quantity: ");
    item.quantity =getInt();
    printf("Minimum Qty: ");
    item.minQuantity =getInt();
    printf("   Is Taxed: ");
    item.isTaxed = yes();
    
    return item;
}

void dspItem(struct Item item, int linear)
{
    double total;
    total =totalAfterTax(item);
    
    if (linear == 1){
        printf("|%3d",item.sku);
        printf("|%-20s",item.name);
        printf("|%8.2f",item.price);
        if(item.isTaxed ==0){
            
            printf("|   No");
        }
        else{
            printf("|  Yes");
        }
        
        printf("| %3d ",item.quantity);
        printf("| %3d ",item.minQuantity);
        printf("|%12.2lf|",total);
        
        if(item.quantity<item.minQuantity){
            printf("***\n");
            
        }
        
        else
        {
            printf("\n");
        }
    }
    
    
    else if(linear ==0){
        printf("        SKU: %d\n",item.sku);
        printf("       Name: %s\n",item.name);
        printf("      Price: %.2f\n",item.price);
        printf("   Quantity: %d\n",item.quantity);
        printf("Minimum Qty: %d\n",item.minQuantity);
        if(item.isTaxed ==1){
            
            printf("   Is Taxed: Yes\n");
        }
        else{
            printf("   Is Taxed: No\n");
        }
        if(item.quantity<item.minQuantity){
            
            printf("WARNING: Quantity low, please order ASAP!!!\n");
            
        }
    }
}

void listItems(const struct Item item[], int NoOfItems)
{
    int counter=0;
    double grandtotal=0.0;
    prnTitle();
    while(counter<NoOfItems){
        printf("%-4d",counter+1);
        dspItem(item[counter], LINEAR);
        grandtotal += totalAfterTax(item[counter]);
        counter ++;
    }
    prnFooter(grandtotal);
    
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index)
{
    
    for (*index= 0 ; *index < NoOfRecs; (*index)++){
        
        if (item[*index].sku == sku){
            return 1;
        }
        
    }
    
    return 0 ;
}








/*
int main() {
    struct Item I[21] = {
        { 4.4,275,0,10,2,"Royal Gala Apples" },
        { 5.99,386,0,20,4,"Honeydew Melon" },
        { 3.99,240,0,30,5,"Blueberries" },
        { 10.56,916,0,20,3,"Seedless Grapes" },
        { 2.5,385,0,5,2,"Pomegranate" },
        { 0.44,495,0,100,30,"Banana" },
        { 0.5,316,0,123,10,"Kiwifruit" },
        { 4.49,355,1,20,5,"Chicken Alfredo" },
        { 5.49,846,1,3,5,"Veal Parmigiana" },
        { 5.29,359,1,40,5,"Beffsteak Pie" },
        { 4.79,127,1,30,3,"Curry Checken" },
        { 16.99,238,1,10,2,"Tide Detergent" },
        { 10.49,324,1,40,5,"Tide Liq. Pods" },
        { 10.99,491,1,50,5,"Tide Powder Det." },
        { 3.69,538,1,1,5,"Lays Chips S&V" },
        { 3.29,649,1,15,5,"Joe Org Chips" },
        { 1.79,731,1,100,10,"Allen's Apple Juice" },
        { 6.69,984,1,30,3,"Coke 12 Pack" },
        { 7.29,350,1,50,5,"Nestea 12 Pack" },
        { 6.49,835,1,20,2,"7up 12 pack" }
    };
    double val;
    int ival;
    int searchIndex;
    val = totalAfterTax(I[0]);
    printf("totalAfterTax: yours=%lf, program's=44.000000\n", val);
    val = totalAfterTax(I[7]);
    printf("totalAfterTax: yours=%lf, program's=101.474000\n", val);
    ival = isLowQty(I[0]);
    printf("isLowQty: yours=%d, program's=0\n",ival);
    ival = isLowQty(I[14]);
    printf("isLowQty: yours=%d, program's=1\n",ival);
    pause();
    printf("itemEntry, enter the following values:\n");
    printf("        SKU: 999\n"
           "       Name: Red Apples\n"
           "      Price: 4.54\n"
           "   Quantity: 50\n"
           "Minimum Qty: 5\n"
           "   Is Taxed: n\n");
    printf("Enter the values:\n");
    I[20] = itemEntry(999);
    printf("dspItem, Linear:\nYours: ");
    dspItem(I[20], LINEAR);
    printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
    printf("dspItem, Form:\nYours:\n");
    dspItem(I[20], FORM);
    printf("Programs: \n");
    printf("        SKU: 999\n"
           "       Name: Red Apples\n"
           "      Price: 4.54\n"
           "   Quantity: 50\n"
           "Minimum Qty: 5\n"
           "   Is Taxed: No\n");
    I[20].quantity = 2;
    I[20].isTaxed = 1;
    pause();
    printf("dspItem, Linear with low value and taxed:\nYours: ");
    dspItem(I[20], LINEAR);
    printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
    printf("dspItem, Form with low value:\nYours:\n");
    dspItem(I[20], FORM);
    printf("Programs: \n");
    printf("        SKU: 999\n"
           "       Name: Red Apples\n"
           "      Price: 4.54\n"
           "   Quantity: 2\n"
           "Minimum Qty: 5\n"
           "   Is Taxed: Yes\n"
           "WARNING: Quantity low, please order ASAP!!!\n");
    pause();
    printf("Listing Items: \n");
    listItems(I, 21);
    pause();
    printf("Locate Item, successful search:\n");
    printf("program: Found the item 999 at index: 20\n");
    printf("  Yours: ");
    if (locateItem(I, 21, 999, &searchIndex)) {
        printf("Found the item 999 at index: %d\n", searchIndex);
    }
    else {
        printf("No item with the sku 999 is in the array!\n");
    }
    
    printf("Locae Item, unsuccessful search:\n");
    printf("Progam: No item with the sku 732 is in the array!\n");
    printf(" Yours: ");
    if (locateItem(I, 21, 732, &searchIndex)) {
        printf("Found the item at index: %d\n", searchIndex);
    }
    else {
        printf("No item with the sku 732 is in the array!\n");
    }
    return 0;
}

*/

/*   item entry output
 SKU: 999
 Name: Red Apples
 Price: 4.54
 Quantity: 50
 Minimum Qty: 5
 Is Taxed: n
 SKU: 999
 Name: Red Apples
 Price: 4.54
 Quantity: 50
 Minimum Qty: 5
 Is Taxed: No
 WARNING: Quantity low, please order ASAP!!!
 
 */

/*  dspItems
 |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|
 SKU: 999
 Name: Red Apples
 Price: 4.54
 Quantity: 50
 Minimum qty: 5
 Is Taxed: No
 */


/*ms1 and 2 functions: */
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

int pause(void) {
    printf("Press <ENTER> to continue...");
    clrKyb();
    return 0;
}

int getInt(void) {
    char NL = 'x';
    int value = 0;
    
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
    double value = 0.0;
    
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
int yes(void) {
    char CH;
    int RET = 0;
    
    
    while (1) {
        scanf("%c", &CH);
        clrKyb();
        
        if (CH == 'y' || CH == 'Y') {
            RET = 1;
            break;
        }
        else if (CH == 'n' || CH == 'N') {
            RET = 0;
            break;
        }
        else printf("Only (Y)es or (N)o are acceptable: ");
    }
    return RET;
}
