#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

// global variables for the food categories
char indian [5][100] = {"Dal makhani","Roti/Naan","Butter chicken","aloo gobhi","fish curry"};
char chinese [5][100] = {"Egg fried rice","Haka noodles","Peeking Duck","Dumplings","Rice , miso soup"};
char italian [5][100] = {"Pizza","lasagne","pasta","risotto","arancini"};
char mexican [5][100] = {"Tacos","Burrito","Chilaquiles","Pozole","Enchiladas"};
char fastfood [5][100] = {"Cheese burger","French Fries","Hot dog","Fried chicken","Cold coffee"};

struct restaurant{
char name[100];
char type[100];
char (*food)[100];
int rate[5];
};

struct customer{
char id[100];
};
bool searchrestaurant(char []);

//searches the customer id
bool searchid(char name[]){
FILE *fptr;
struct customer cst;
if((fptr = fopen("customerinfo.bin","rb")) == NULL){
    printf("error opening file\n");
    exit(1);
}
while(fread(&cst,sizeof(struct customer),1,fptr)){
    int i = 0,found = 1;
    while(name[i] != '\0'){
        if(name[i] != cst.id[i]){
            found = 0;
            break;
        }
        i++;
    }
    if(found){
        fclose(fptr);
        return true;
    }
}
fclose(fptr);
return false;
}

//adds the customer id
void addid(struct customer cst){
FILE *fptr;
if((fptr = fopen("customerinfo.bin","ab")) == NULL){
    printf("error opening file\n");
    exit(1);
}

fwrite(&cst,sizeof(struct customer),1,fptr);
fclose(fptr);
}

//adds the restaurants
void addrestaurant(){
struct restaurant r;
while(true){
printf("ENTER RESTAURANT NAME : ");
gets(r.name);
if(searchrestaurant(r.name)){
    printf("THIS RESTAURANT ALREADY EXIST ENTER A NEW NAME\n");
}
else{
    break;
}
}
while(true){
printf("CHOOSE RESTAURANTS CATEGORY \n");
printf("1.INDIAN\n");
printf("2.CHINESE\n");
printf("3.ITALIAN\n");
printf("4.MEXICAN\n");
printf("5.FASTFOOD\n");
int choise;
scanf("%d",&choise);

if (choise  == 1){
    strcpy(r.type,"INDIAN");
    puts(r.type);
    r.food = indian;
    break;
}
else if(choise == 2){
    strcpy(r.type,"CHINESE");
    r.food = chinese;
    break;
}
else if(choise == 3){
    strcpy(r.type,"ITALIAN");
    r.food = italian;
    break;
}
else if(choise == 4){
    strcpy(r.type,"MEXICAN");
    r.food = mexican;
    break;
}
else if(choise == 5){
    strcpy(r.type,"FASTFOOD");
    r.food = fastfood;
    break;
}
else{
    printf("wrong choise enter again\n");
}
}
int i;
for(i = 0; i < 5; i++){
    printf("ENTER THE PRICE OF ");
    puts(r.food[i]);
    scanf("%d",&r.rate[i]);
}

FILE *fptr;
if((fptr = fopen("restaurants.bin","ab")) == NULL){
    printf("error opening file\n");
    exit(1);
}

fwrite(&r,sizeof(struct restaurant),1,fptr);
fclose(fptr);

}

//searches the restaurants
bool searchrestaurant(char name[]){
FILE *fptr;
struct restaurant rest;

if((fptr = fopen("restaurants.bin","rb")) == NULL){
    printf("error opening file\n");
    exit(1);
}
while(fread(&rest,sizeof(struct restaurant),1,fptr)){
    int i = 0,found = 1;
    while(name[i] != '\0'){
        if(name[i] != rest.name[i]){
            found = 0;
            break;
        }
        i++;
    }
    if(found){
        fclose(fptr);
        return true;
    }
}
fclose(fptr);
return false;
}

// gives the restaurants structure
struct restaurant giverestaurant(int n){
FILE *fptr;
struct restaurant rest;
if((fptr = fopen("restaurants.bin","rb")) == NULL){
    printf("error opening file\n");
    exit(1);
}
int i;
for(i = 1; i <= n; i++){
    fread(&rest,sizeof(struct restaurant),1,fptr);
}
fclose(fptr);
return rest;
}
//view restaurant and gives the index
int viewrestaurant(){
FILE *fptr;
struct restaurant rest;
if((fptr = fopen("restaurants.bin","rb")) == NULL){
    printf("error opening file\n");
    exit(1);
}
printf("sno\trestaurant\tcategory\n");
int i = 1;
while(fread(&rest,sizeof(struct restaurant),1,fptr)){
    printf("%d\t",i);
    printf("%s\t%s\n",rest.name,rest.type);
    i++;
}
fclose(fptr);
return i;
}

int menu(struct restaurant rest){
    int i;
    int total = 0;
    for(i = 0; i < 5; i++){
        printf("%d\t%s\t%d\n",i+1,rest.food[i],rest.rate[i]);
    }
    while(true){
    printf("SELECT THE FOOD NO. IF YOU WANT TO GO BACK TYPE -1\n");
    int choise;
    scanf("%d",&choise);
    if(choise >= 1 && choise <= 5){
        total += rest.rate[choise-1];
        printf("BILL = %d\n",total);
        printf("IF YOU WANT TO MORE CHECK OUT TYPE 1 OR PRESS 0 TO CONTINUE\n");
        int ch;
        scanf("%d",&ch);
        if(ch == 1){
            return total;
        }
    }
    else if (choise == -1){
        return -1;
    }
    else{
        printf("WRONG CHOISE TYPE AGAIN\n");
    }
    }
}
int main(){
while(true){
    int choise;
printf("========================FOOD DELIVERY MANAGEMENT========================\n");
printf("1.ORDER FOOD\n");
printf("2.ADD RESTAURANT\n");
printf("3.EXIT\n");
scanf("%d",&choise);
int bill = 0;
if(choise == 1){
    while(true){
    int total = viewrestaurant();
    printf("SELECT THE RESTAURANT :\n");
    int ch;
    scanf("%d",&ch);

    if(ch<=total){
        struct restaurant rest;
        rest = giverestaurant(ch);
        bill = menu(rest);
        if (bill > -1){
            printf("YOUR BILL IS %d\n",bill);
        }
        int more;

        printf("WANT TO ORDER MORE ? PRESS 1 OR PRESS 0\n");
        scanf("%d",&more);
        if(more == 0){
            break;
        }
    }
    else {
        printf("WRONG CHOISE CHOOSE AGAIN\n");
    }

    }
}
else if(choise == 2){
    addrestaurant();
}
else if(choise == 3){
    break;
}
else{
    printf("WORNG CHOISE \n");
}
}
}

