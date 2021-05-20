#include <stdio.h>

/***************************************************************
 Tester Function prototypes and information, DO NOT MODIFY */

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

struct Item {
    double price;
    int sku;
    int isTaxed;
    int quantity;
    int minQuantity;
    char name[21];
};

struct Item GI[21] = {
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
int GNoOfRecs = 20;

/**************************************************************/




/*************************************************************
 Student Milestone 3 definitions and prototypes go here:
 (Do not copy struct Item since it is already implimented above*/

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);














/*End of Student Milestone 3 definitions and prototypes
 *************************************************************/
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0


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




double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);
const double TAX = 0.13;





/*************************************************************
 Milestone 4 defintions and prototypes:*/
// write the define statements here:











// function prototypes in order of implementation:
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


/*End of Milestone 4 defintions and prototypes:
 ***************************************************************/

# define MAX_ITEM_NO 21
# define MAX_QTY 999
# define SKU_MAX 999
# define SKU_MIN 100


/*************************************************************
 Main tester */
//int main() {
  //  searchTest();
    //updateTest();
    //addTest();
    //addOrUpdateTest();
    //adjustQtyTest();
  // return 0;
//}

/*End of main tester
 ******************************************************************/


/***************************************************************
 Milestone 4 functions to be implemented */
void search(const struct Item item[], int NoOfRecs) {
    int sku ,index, search;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN,SKU_MAX);
    search = locateItem(item ,NoOfRecs , sku, &index);
    if(search == 1){
        dspItem(item[index], FORM);
    }
    else{
        printf("Item not found!\n");
    }
}

void updateItem(struct Item* itemptr) {
    struct Item item = *itemptr;
    printf("Enter new data:\n");
    item = itemEntry(item.sku);
    printf("Overwrite old data? (Y)es/(N)o: ");
    
    if(yes() == 1){
        printf("--== Updated! ==--\n");
        *itemptr =item;
    }
    else{
        printf("--== Aborted! ==--\n");
    }

}

void addItem(struct Item item[], int *NoOfRecs, int sku) {
    
    struct Item i;
   
    if(*NoOfRecs == MAX_ITEM_NO){
        printf("Can not add new item; Storage Full!\n");
    }
    else {
        i = itemEntry(sku);
        printf("Add Item? (Y)es/(N)o: ");
        if(yes() == 1){
            printf("--== Added! ==--\n");
            item[*NoOfRecs] = i;
            (*NoOfRecs)++;
        }
        else{
            printf("--== Aborted! ==--\n");
        }

    }
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) {
    int sku;
    int index;
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    
    if(locateItem(item, *NoOfRecs, sku, &index)){
        dspItem(item[index], FORM);
        printf("Item already exists, Update? (Y)es/(N)o: ");
        if (yes() == 1){
        updateItem(&item[index]);
        }
        else{
            printf("--== Aborted! ==--\n");

        }
    }
    
    else{
        addItem(item,NoOfRecs,sku);
    }


}

void adjustQty(struct Item item[], int NoOfRecs, int stock) {
    int sku , index;
    int maxquantity, quantity;
    
    printf("Please enter the SKU: ");
    sku = getIntLimited(SKU_MIN, SKU_MAX);
    
    if(locateItem(item, NoOfRecs, sku, &index) == 0 ){
        
        printf("SKU not found in storage!\n");
        return;
    }
    
    else{
        dspItem(item[index], FORM);
    }
    
    
    if(stock == STOCK){
        maxquantity = MAX_QTY - item[index].quantity;
        printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to stock",maxquantity);
        
    }
    else if(stock == CHECKOUT){
        maxquantity =  item[index].quantity;
        printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", "to checkout",maxquantity);
    }
    
    quantity = getIntLimited(0, maxquantity);
    
    if (quantity == 0 ){
        printf("--== Aborted! ==--\n");
        return;
    }
    if (stock == STOCK){
        item[index].quantity += quantity;
        printf("--== Stocked! ==--\n");
    }
    else if(stock == CHECKOUT){
        item[index].quantity -= quantity;
        printf("--== Checked out! ==--\n");
    }
    
    if(isLowQty(item[index])){
        printf("Quantity is low, please reorder ASAP!!!\n");
        
        
    }
    
    
    
    
    
}


/*End of Milestone 4 functions
 ******************************************************************/

/*****************************************************************
 Milestone 3 function implementations:
 Please copy your milestone 3 functions here: */







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
    
    
    if(item.quantity<=item.minQuantity){
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
    clrKyb();
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
        if(item.quantity<=item.minQuantity){
            
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

















/*End of Milestone 3 functions.
 *******************************************************************/

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
    clrKyb();
    
    while (value < lowerLimit || value > upperLimit) {
        printf("Invalid value, %d <= value <= %d: ", lowerLimit, upperLimit);
        scanf("%d", &value);
        clrKyb();
    }
    return value;
}

double getDblLimited(double lowerLimit, double upperLimit) {
    double value;
    scanf("%lf", &value);
    
    while (value < lowerLimit || value > upperLimit) {
        
        printf("Invalid value, %lf<= value <= %lf: ", lowerLimit, upperLimit);
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



/***************************************************************
 Tester Functions DO NOT MODIFY */

void searchTest() {
    printf("================Search Test:\n");
    printf("Enter 731: \n");
    search(GI, GNoOfRecs);
    printf("Enter 222: \n");
    search(GI, GNoOfRecs);
}
void updateTest() {
    struct Item I = { 11.11,111,1,11,1,"Ones!" };
    printf("================Update Test:\n");
    printf("Enter the follwoing: \n");
    printf(
           "         SKU: 111\n"
           "        Name: Grape\n"
           "      Price : 22.22\n"
           "   Quantity : 22\n"
           "Minimum Qty : 2\n"
           "   Is Taxed : y\n"
           "Overwrite old data? (Y)es/(N)o: n\n");
    updateItem(&I);
    printf("Unchanged Item Data:\n");
    dspItem(I, FORM);
    printf("Enter the follwoing: \n");
    printf(
           "         SKU: 111\n"
           "        Name: Grape\n"
           "      Price : 22.22\n"
           "   Quantity : 22\n"
           "Minimum Qty : 2\n"
           "   Is Taxed : y\n"
           "Overwrite old data? (Y)es/(N)o: y\n");
    updateItem(&I);
    printf("Updated Item: \n");
    dspItem(I, FORM);
}
void addTest() {
    printf("================Add Test:\n");
    printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
    printf("Enter the follwoing: \n");
    printf(
           "         SKU: 222\n"
           "        Name: Grape\n"
           "      Price : 22.22\n"
           "   Quantity : 22\n"
           "Minimum Qty : 2\n"
           "   Is Taxed : y\n"
           "Add Item? (Y)es/(N)o: n\n");
    addItem(GI, &GNoOfRecs, 222);
    printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
    dspItem(GI[GNoOfRecs], FORM);
    printf("Enter the follwoing: \n");
    printf(
           "         SKU: 222\n"
           "        Name: Grape\n"
           "      Price : 22.22\n"
           "   Quantity : 22\n"
           "Minimum Qty : 2\n"
           "   Is Taxed : y\n"
           "Add Item? (Y)es/(N)o: y\n");
    addItem(GI, &GNoOfRecs, 222); //y
    printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
    dspItem(GI[GNoOfRecs - 1], FORM);
    printf("Adding 333: \n");
    addItem(GI, &GNoOfRecs, 333);
}
void addOrUpdateTest() {
    GNoOfRecs = MAX_ITEM_NO;
    printf("================AddOrUpdate Test:\n");
    printf("Enter 731 and then \'n\':\n");
    addOrUpdateItem(GI, &GNoOfRecs); // n
    printf("Enter 731, \'y\' and then:\n"
           "       Name: Apple\n"
           "      Price: 1.80\n"
           "   Quantity: 101\n"
           "Minimum Qty: 11\n"
           "   Is Taxed: n\n"
           "Overwrite old data? (Y)es/(N)o: y\n");
    addOrUpdateItem(GI, &GNoOfRecs); // yes new data Yes
    printf("Updated Item: \n");
    dspItem(GI[16], FORM);
    printf("Enter 444: \n");
    addOrUpdateItem(GI, &GNoOfRecs); //n
}

void adjustQtyTest() {
    printf("================AdjustQty Test:\n");
    printf("Invalid SKU Test; Enter 444:\n");
    adjustQty(GI, GNoOfRecs, STOCK);
    printf("Aborting Entry test; Enter 731 and then 0:\n");
    adjustQty(GI, GNoOfRecs, CHECKOUT);
    printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
    adjustQty(GI, GNoOfRecs, CHECKOUT);
    printf("Stocking; Enter 731 and then 50:\n");
    adjustQty(GI, GNoOfRecs, STOCK);
    dspItem(GI[16], FORM);
}

/* End test functions
 *********************************************************************/
