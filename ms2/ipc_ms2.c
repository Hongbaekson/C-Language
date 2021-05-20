#include <stdio.h>
void clrKyb(void);
void pause(void);
int getInt(void);
int yes(void);  // ms2
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void);
void GrocInvSys(void);  // ms2
int menu(void);  // ms2
/*
int main(void) {
    GrocInvSys();
    
    return 0;
}
*/
// implmement MS2 fucntions here

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
    welcome();
    
    while(!DONE){
        SEL=menu();
        
        if(SEL==1){
            printf("List Items!\n");
            pause();
        }
        else if(SEL==2){
            printf("Search Items!\n");
            pause();
        }
        else if(SEL ==3){
            printf("Checkout Item!\n");
            pause();
        }
        else if(SEL==4){
            printf("Stock Item!\n");
            pause();
        }
        else if(SEL==5){
            printf("Add/Update Item!\n");
            pause();
        }
        else if(SEL==6){
            printf("Delete Item!\n");
            pause();
        }
        else if(SEL==7){
            printf("Search by name!\n");
            pause();
        }
        else if(SEL==0){
            printf("Exit the program? (Y)es/(N)o : ");
            DONE=yes();
            
        }
        else {
            menu();
        }
        
    }
    
}















int menu(void)
{
    int mn;
    printf("1- List all items\n");
    printf("2- Search by SKU\n");
    printf("3- Checkout an item\n");
    printf("4- Stock an item\n");
    printf("5- Add new item or update item\n");
    printf("6- delete item\n");
    printf("7- Search by name\n");
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




// copy MS1 functions here

void clrKyb(void) {
    char input;
    do {
        scanf("%c", &input);
    } while (input != '\n');
}

void pause(void) {
    printf ("Press <ENTER> to continue...");
    clrKyb();
}

int getInt(void) {
    char NL= 'x';
    int value = 0;
    
    while(NL != '\n') {
        printf("> ");
        scanf("%d%c", &value, &NL);
        if(NL != '\n') {
            clrKyb();
            int getIntLimited();
            printf("Invalid integer, please try again: ");
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

void welcome(void) {
    printf("---=== Grocery Inventory System ===---\n\n");
}
