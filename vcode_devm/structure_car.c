#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 9. Design a structure named "Car" to store details like car ID, model, and rental rate per day. Write a C program to input data for three cars, calculate the total rental cost for a specified number of days, and display the result




typedef struct _vehicle {
    int Car_ID;
    char model[30];
    int rent_per_day;
} vehicle;


int car_rental(vehicle car[],int id,int days){

int carno = id - 1;

int rent_perday = car[carno].rent_per_day * days;


return rent_perday;


}

int main(){



    vehicle car[3];


car[0].Car_ID = 1;
// car[0].model = "model1";
strcpy(car[0].model,"model1");
car[0].rent_per_day = 500;


car[1].Car_ID = 2;
// car[0].model = "model1";
strcpy(car[1].model,"model2");
car[1].rent_per_day = 1000;



car[2].Car_ID = 3;
// car[0].model = "model1";
strcpy(car[2].model,"model3");
car[2].rent_per_day = 1500;


printf("Welcome to Car Rental Service\nWe have Following Cars for Rent\n\n");



for(int i = 0 ; i < 3 ; i++){

printf("Car ID: %d\n",car[i].Car_ID);
printf("Car model: %s\n",car[i].model);
printf("Car Rent per day: %d\n",car[i].rent_per_day);


printf("\n*************************************************\n");


}

printf("which car would you want to rent,Please tell us the car ID: ");
int rentid;
int rentday;
scanf("%d",&rentid);
printf("please Enter the number of days you want to rent the car for: ");
scanf("%d",&rentday);


int total_rent = car_rental(car,rentid,rentday);


printf("your rent has become %d\n",total_rent);

}