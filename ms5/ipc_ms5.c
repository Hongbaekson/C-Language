


#include <stdio.h>




struct Item {
    double price;
    int sku;
    int isTaxed;
    int quantity;
    int minQuantity;
    char name[21];
};




/********************************************************************
 Milestones 1 to 4  prototypes, definitions and etc...*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void clrKyb(void);
int pause(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

int yes(void);  // ms2
void GrocInvSys(void);  // ms2
int menu(void);  // ms2


double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);


void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);








/*End of milestone 1 to 4 stuff
 *********************************************************************/
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

# define MAX_QTY 999
# define SKU_MAX 999
# define SKU_MIN 100

const double TAX = 0.13;









/********************************************************************
 Milestone 5 prototypes*/


#define MAX_ITEM_NO 500
#define DATAFILE "ipc_ms5_short.txt"

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
 *********************************************************************/




/**************************************************************************
 TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR
 TT       EE         SS             TT       EE          RR     RR
 TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
 TT       EE               SS       TT       EE          RR  RR
 TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
 ***************************************************************************
 Tester for saveItem, loadItem, saveItems and loadItems:
 uncomment this to test your functions prior to putting all the code together by adding a * and / here:
 void prnFile() {
 FILE* tp = fopen("test.txt", "r");
 char ch;
 if (tp) {
     for (; fscanf(tp,"%c", &ch) == 1; putch(ch));
 fclose(tp);
 }
 else {
 printf("text.txt not found\n");
 }
 }
 int main(void) {
 int i, n;
 struct Item GI[3] = {
 { 4.4,275,0,10,2,"Royal Gala Apples" },
 { 5.99,386,0,20,4,"Honeydew Melon" },
 { 3.99,240,0,30,5,"Blueberries" },
 };
 struct Item I;
 struct Item IN[3];
 printf("***********Testing saveItem:\n");
 printf("Your saveItem saved the following in test.txt: \n");
 FILE* tp = fopen("test.txt", "w");
 if (tp) {
 for (i = 0; i < 3; i++) saveItem(GI[i], tp);
 fclose(tp);
 prnFile();
 }
 printf("*******************************\nThey have to match the following:\n");
 printf("275,10,2,4.40,0,Royal Gala Apples\n");
 printf("386,20,4,5.99,0,Honeydew Melon\n");
 printf("240,30,5,3.99,0,Blueberries\n");
 printf("***********END Testing saveItem!\n\n\n");
 pause();
 printf("***********Testing loadItem:\n");
 printf("Your loadItem loaded the following from test.txt: \n");
 tp = fopen("test.txt", "r");
 if (tp) {
 for (i = 0; i < 3; i++) {
 loadItem(&I, tp);
 dspItem(I, LINEAR);
 }
 fclose(tp);
 tp = fopen("test.txt", "w");
 fclose(tp);
 }
 printf("*******************************\nThey have to match the following:\n");
 printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
 printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
 printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
 printf("***********END Testing loadItem!\n\n\n");
 pause();
 printf("***********Testing saveItems:\n");
 printf("Your saveItems saved the following in test.txt: \n");
 saveItems(GI, "test.txt", 3);
 prnFile();
 printf("*******************************\nThey have to match the following:\n");
 printf("275,10,2,4.40,0,Royal Gala Apples\n");
 printf("386,20,4,5.99,0,Honeydew Melon\n");
 printf("240,30,5,3.99,0,Blueberries\n");
 printf("***********END Testing saveItems!\n\n\n");
 pause();
 printf("***********Testing loadItems:\n");
 printf("Your loadItems loaded the following from test.txt: \n");
 loadItems(IN, "test.txt", &n);
 for (i = 0; i < n; i++) {
 dspItem(IN[i], LINEAR);
 }
 printf("*******************************\nThey have to match the following:\n");
 printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
 printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
 printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
 printf("***********END Testing loadItems!\n\n\n");
 pause();
 printf("Done!\n");
 return 0;
 }
 /End MS5 functions' tester
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************
 ***************************************************************************/


/********************************************************************
 Main function to run the application
 uncomment this to test your functions after putting all the code together by adding a * and / here:*/
 int main(void) {
 GrocInvSys();
 return 0;
 }
  /*End Main function
 ********************************************************************/





/********************************************************************
 Milestone 5 functions*/

void saveItem(struct Item item, FILE* dataFile){

    if(dataFile != NULL){

        fprintf(dataFile,"%d,%d,%d,%.2lf,%d,%s",item.sku,item.quantity,item.minQuantity,item.price,item.isTaxed,item.name);
    
    }

    else{
    
        printf("Not Working");
    }

}

int loadItem(struct Item* item, FILE* dataFile){

    int RET = 0;
    
    if(fscanf(dataFile, "%d,%d,%d,%lf,%d,%20[^\n]s", &(*item).sku, &(*item).quantity, &(*item).minQuantity, &(*item).price, &(*item).isTaxed, (*item).name) == 6)
	{
        RET =1;
    }
    
    return RET;
}

int saveItems(struct Item* item, char fileName[], int NoOfRecs){

    FILE *fp = fopen(fileName,"w");

    int i = 0;
    
    if (fp == NULL){
        printf("Not working\n");
        return 0;
    }
    
    else {
        
        for (i = 0; i < NoOfRecs; i++){
        
            saveItem(item[i] ,fp);
    }
  
        
        fclose(fp);
        
        return 1;

    }

}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr){

    FILE *fp = NULL;
    fp = fopen(fileName, "r");
    
    int i =0;
    int target =0;
    
    if(fp == NULL){
        
        printf("Not working\n");
        return 0;
    }
    else
	{
        
        while(loadItem(item, fp)){
            target++;
        }
    
        *NoOfRecsPtr = target;
		rewind(fp);
       
        for (i =0; i < *NoOfRecsPtr; i++){
        
            loadItem(&item[i], fp);
        }
    
        fclose(fp);
        return 1;
    }


}






/*End of milestone 5 functions
 *********************************************************************/

/********************************************************************
 Milestones 1  to 4 functions*/
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
    clrKyb();
    while (value < lowerLimit || value > upperLimit) {
        
        printf("Invalid value, %lf<= value <= %lf: ", lowerLimit, upperLimit);
        scanf("%lf", &value);
        clrKyb();
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
void GrocInvSys(void){
   
    int DONE=0;
    int SEL;
   
    struct Item item[MAX_ITEM_NO];
    int i ;

    
    welcome();
   
    loadItems(item,DATAFILE,&i);
    
    if (!loadItems(item,DATAFILE,&i)){
       
        printf("Could not read from %s.\n",DATAFILE);
        return ;
    }
    
     while(!DONE){
        SEL=menu();
        
        if(SEL==1){
            listItems(item, i);
            pause();
        }
        else if(SEL==2){
            search(item, i);
            pause();
        }
        else if(SEL ==3){
            adjustQty(item,i,CHECKOUT);
            saveItems(item,DATAFILE,i);
            if(!saveItems(&item[i],DATAFILE,i))
                printf("could not update data file %s\n",DATAFILE);
               pause();
        }
        else if(SEL==4){
            adjustQty(item,i,STOCK);
            saveItems(item,DATAFILE,i);
            if(!saveItems(item,DATAFILE,i))
                printf("could not update data file %s\n",DATAFILE);
            pause();
        }
        else if(SEL==5){
            addOrUpdateItem(item, &i);
            saveItems(item, DATAFILE, i);
            if(!saveItems(item,DATAFILE,i))
            printf("could not update data file %s\n",DATAFILE);
            pause();
        }
         //else if(SEL==6){
         // printf("Not implemented!\n");
         // pause();
         // }
         //else if(SEL==7){
         //  printf("Not implemented!\n");
         // pause();
         //}

        else if(SEL==0){
            printf("Exit the program? (Y)es/(N)o): ");
            DONE=yes();
            
        }
        else {
            menu();
        }
        
    }
    
}
//else if(SEL==6){
// printf("Not implemented!\n");
// pause();
// }
//else if(SEL==7){
//  printf("Not implemented!\n");
// pause();
//}



int menu(void)
{
    int mn;
    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Add new item or update item\n");
    //printf("6- delete item\n");
    //printf("7- Search by name\n");
    printf("0- Exit program\n");
    printf("> ");
    do
    {
        scanf("%d", &mn);
        clrKyb();
        if (mn < 0 || mn > 7)
        {
            printf("Invalid value, 0 < value < 7: ");
        }
    } while (mn < 0 || mn > 7);
    
    return mn;
}


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
    item.price = getDblLimited(0.01, 1000.00);
    printf("   Quantity: ");
    item.quantity =getIntLimited(1, MAX_QTY);
    printf("Minimum Qty: ");
    item.minQuantity =getIntLimited(0, 100);
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
	double total;
	int counter=0;
    double grandtotal=0.0;
    prnTitle();
   
	while (counter < NoOfItems) {
		printf("%-4d", counter + 1);
		printf("|%3d", item[counter].sku);
		printf("|%-20s", item[counter].name);
		printf("|%8.2lf", item[counter].price);
		if (item[counter].isTaxed == 0) {
			printf("|   No");
		}
		else {
			printf("|  Yes");
		}
		printf("| %3d ", item[counter].quantity);
		printf("| %3d ", item[counter].minQuantity);

		total = totalAfterTax(item[counter]);
		printf("|%12.2lf|", total);
		if (item[counter].quantity <= item[counter].minQuantity) {
			printf("***\n");
		}
		else
		{
			printf("\n");
		}


        grandtotal += totalAfterTax(item[counter]);
		counter++;
	}
    prnFooter(grandtotal);
    
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index)
{
    
    for (*index= 0 ; *index < NoOfRecs; (*index)++)
	{
        if (item[*index].sku == sku){
            return 1;
        }
        
    }
    
    return 0 ;
}


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
    printf("Overwrite old dtat? (Y)es/(N)o: ");
    if(yes() == 1){
        printf("--== Update! ==--\n");
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
        printf("--== Stocked ==--\n");
    }
    else if(stock == CHECKOUT){
        item[index].quantity -= quantity;
        printf("--== Checked out! ==--\n");
    }
    
    if(isLowQty(item[index])){
        printf("Quantity is low, please reorder ASAP!!!\n");
        
        
    }
    
    
    
    
    
}






/*End of milestone 1 to 4 functions
 *********************************************************************/








/* ms5 Tester output
 ***********Testing saveItem:
 Your saveItem saved the following in test.txt:
 275,10,2,4.40,0,Royal Gala Apples
 386,20,4,5.99,0,Honeydew Melon
 240,30,5,3.99,0,Blueberries
 *******************************
 They have to match the following:
 275,10,2,4.40,0,Royal Gala Apples
 386,20,4,5.99,0,Honeydew Melon
 240,30,5,3.99,0,Blueberries
 ***********END Testing saveItem!
 Press <ENTER> to continue...
 ***********Testing loadItem:
 Your loadItem loaded the following from test.txt:
 |275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
 |386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
 |240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
 *******************************
 They have to match the following:
 |275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
 |386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
 |240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
 ***********END Testing loadItem!
 Press <ENTER> to continue...
 ***********Testing saveItems:
 Your saveItems saved the following in test.txt:
 275,10,2,4.40,0,Royal Gala Apples
 386,20,4,5.99,0,Honeydew Melon
 240,30,5,3.99,0,Blueberries
 *******************************
 They have to match the following:
 275,10,2,4.40,0,Royal Gala Apples
 386,20,4,5.99,0,Honeydew Melon
 240,30,5,3.99,0,Blueberries
 ***********END Testing saveItems!
 Press <ENTER> to continue...
 ***********Testing loadItems:
 Your loadItems loaded the following from test.txt:
 |275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
 |386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
 |240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
 *******************************
 They have to match the following:
 |275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
 |386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
 |240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
 ***********END Testing loadItems!
 Press <ENTER> to continue...
 Done!
 */
