#include "ui.h"
#include "service.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Ui createUi(Service *s) {
    Ui ui;
    ui.service = s;
    return ui;
}

void printMenu() {
    printf("1:Add estate\n");
    printf("2:Delete estate\n");
    printf("3:Update estate\n");
    printf("4:Display all estates whose address contains a given string,sorted ascending/(bonus)descending by their price\n");
    printf("5:Display all estates of a given type, having the surface greater than a user provided value\n");
    printf("6:(bonus)Display all estates with a price smaller then a user provided value,sorted descending by their surface\n");
    printf("7:Undo\n");
    printf("8:Redo\n");
    printf("9:Exit\n");
}

void ui_add_estate(Ui *ui) {
    char type[30], address[50];
    int surface,price;
    char x[20],y[20];

    //read type
    printf("Enter type of estate:");
    scanf("%s", type);

    //validate type
    while (!validate_type(type)) {
        printf("invalid type\n try again \n");
        printf("Enter type of estate:");
        scanf("%s", type);
    }

    //read address
    while (getchar() != '\n');
    printf("Enter address of estate:");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';

    //read and validate surface
    printf("Enter surface of estate:");
    scanf("%s", x);

    while (atoi(x)==0) {
        printf("Surface must be an integer\n");
        printf("Enter surface of estate:");
        scanf("%s", x);
    }
    surface=atoi(x);

    //read and validate price
    printf("Enter price of estate:");
    scanf("%s", y);
    while (atoi(y)==0) {
        printf("Price must be an integer\n");
        printf("Enter price of estate:");
        scanf("%s", y);
    }
    price=atoi(y);

    savecurrent(ui->service);
    //add estate
    add_estate_services(ui->service, type, address, surface, price);
    printf("Estate added\n");
}

void ui_delete_estate(Ui *ui) {
    char address[50];
    //read address
    while (getchar() != '\n');
    printf("Enter address of estate:");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    //verify if the address exists
    if (find_estate(ui->service, address) == 0) {
        printf("Address not found\n");
        return;
    }
    else {
        savecurrent(ui->service);
        //delete estate
        delete_estate_service(ui->service, address);
        printf("Address successfully deleted\n");
    }
}

void ui_update_estate(Ui *ui) {
    char address[50], type[30];
    int surface,price;
    char x[20],y[20];
    int opt;
    //read address
    while (getchar() != '\n');
    printf("Enter address of estate:");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';
    //verify if the address exists
    if (find_estate(ui->service, address) == 0) {
        printf("Address not found\n");
        return;
    }
    else {
        printf("What you want to update?\n");
        printf("1:type of estate\n");
        printf("2:price of estate\n");
        printf("3:surface of estate\n");
        printf(">>>");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                //read new type
                printf("Enter type of estate:");
                scanf("%s", type);
                //validate type
                while (!validate_type(type)) {
                    printf("invalid type\n try again \n");
                    printf("Enter type of estate:");
                    scanf("%s", type);
                }
                savecurrent(ui->service);
                //update estate
                update_type_services(ui->service, type, address);
                printf("Estate updated\n");
                break;
            case 2:
                //read and validate price
                printf("Enter price of estate: ");
                scanf("%s", x);
                while (atoi(x)==0) {
                    printf("Price must be an integer");
                    printf("Enter price of estate:");
                        scanf("%s", x);
                }
                price=atoi(x);
                savecurrent(ui->service);
                //update estate
                update_price_services(ui->service, price, address);
                printf("Estate updated\n");
                break;
            case 3:
                //read and validate surface
                    printf("Enter surface of estate:");
                scanf("%s", y);
                while (atoi(y)==0) {
                    printf("Surface must be an integer");
                    printf("Enter surface of estate:");
                    scanf("%s", y);
                }
                surface=atoi(y);
                savecurrent(ui->service);
                //update estate
                update_surface_services(ui->service, surface, address);
                printf("Estate updated\n");
                break;
        }
    }
}

void ui_display_estates_string(Ui *ui) {
    char string[30];
    //read string
    printf("Give string: ");
    while (getchar() != '\n');
    fgets(string, sizeof(string), stdin);
    string[strcspn(string, "\n")] = '\0';

    char sort;
    printf("Sort estates by price\n");
    printf("a:ascending\n");
    printf("d:descending\n");
    printf(">>>");
    scanf("%s", &sort);
    while (sort!='a'&& sort!='d') {
        printf("invalid input\n try again");
        printf(">>>");
        scanf("%s", &sort);
    }
    DynamicRepo *estates=ui->service->repo;
    estates = search_estates_wstring(estates,string,sort);
    if (estates->length == 0)
        printf("No estate found\n");
    else {
        for (int i = 0; i < estates->length; i++) {
            printf("Estate %2d: ", i);
            printf("address:%30s, ", estates->estates[i]->address);
            printf("type:%15s ", estates->estates[i]->type);
            printf(",surface:%4d ", estates->estates[i]->surface);
            printf(",price:%10d ", estates->estates[i]->price);
            printf("\n");
        }
        printf("\n");
    }
    destroyDynamicRepo(estates);
}
void ui_display_estates_type(Ui *ui) {
    char type[30];
    //read type
    printf("Enter type of estate:");
    scanf("%s", type);

    //validate type
    while (!validate_type(type)) {
        printf("invalid type\n try again \n");
        printf("Enter type of estate:");
        scanf("%s", type);
    }

    int surface;
    char x[20];
    //read minimum surface
    printf("Enter minimum surface of estate:");
    scanf("%s", x);
    while (atoi(x)==0) {
        printf("Surface must be an integer");
        printf("Enter minimum surface of estate:");
        scanf("%s", x);
    }
    surface=atoi(x);
    DynamicRepo *estates;
    estates=search_estates_wtype(ui->service->repo,type,surface);
    if (estates->length == 0)
        printf("No estate found\n");
    else {
        for (int i = 0; i < estates->length; i++) {
            printf("Estate %2d: ", i);
            printf("address:%30s, ", estates->estates[i]->address);
            printf("type:%15s ", estates->estates[i]->type);
            printf(",surface:%4d ", estates->estates[i]->surface);
            printf(",price:%10d ", estates->estates[i]->price);
            printf("\n");
        }
        printf("\n");
    }
    destroyDynamicRepo(estates);
}

void ui_display_estates_price(Ui *ui) {
    int price;
    char x[20];
    printf("Enter price of estate:");
    scanf("%s", x);
    while (atoi(x)==0) {
        printf("Price must be an integer");
        printf("Enter price of estate:");
        scanf("%s", x);
    }
    price=atoi(x);
    DynamicRepo *estates;
    DynamicRepo *(*ftpr)(DynamicRepo*,int);
    ftpr=&search_estates_wprice;
    estates=ftpr(ui->service->repo,price);
    if (estates->length == 0)
        printf("No estate found\n");
    else {
        for (int i = 0; i < estates->length; i++) {
            printf("Estate %2d: ", i);
            printf("address:%30s, ", estates->estates[i]->address);
            printf("type:%15s ", estates->estates[i]->type);
            printf(",surface:%4d ", estates->estates[i]->surface);
            printf(",price:%10d ", estates->estates[i]->price);
            printf("\n");
        }
        printf("\n");
    }
    destroyDynamicRepo(estates);
}

void initial_estates(Ui *ui) {
    add_estate_services(ui->service, "house", "Str Luceafarului nr 5-7", 40, 500);
    add_estate_services(ui->service, "apartment", "Str Lunii nr 10", 23, 200);
    add_estate_services(ui->service, "house", "Str Soimului nr 90", 60, 750);
    add_estate_services(ui->service, "penthouse", "Str Paunului nr 1", 10, 100);
    add_estate_services(ui->service, "apartment", "Str Soarelui nr 48", 35, 150);
    add_estate_services(ui->service, "penthouse", "Str Decebal nr 9", 1000, 2500);
    add_estate_services(ui->service, "house", "Str Orzului nr 10", 15, 75);
    add_estate_services(ui->service, "apartment", "Str Canalul Morii nr 3", 34, 400);
    add_estate_services(ui->service, "apartment", "Str Valea Seaca nr 134", 300, 1320);
    add_estate_services(ui->service,"house","Str Mioarei nr 6",70,900);
    add_estate_services(ui->service,"penthouse","Str Morii nr 60",100,1000);
}

void start(Ui *ui) {
    initial_estates(ui);
    int opt;
    while (1) {
        printMenu();
        printf("Select an option:");
        scanf("%d", &opt);
        switch (opt) {
            case 1:
                ui_add_estate(ui);
                break;
            case 2:
                ui_delete_estate(ui);
                break;
            case 3:
                ui_update_estate(ui);
                break;
            case 4:
                ui_display_estates_string(ui);
                break;
            case 5:
                ui_display_estates_type(ui);
                break;
            case 6:
                ui_display_estates_price(ui);
                break;
            case 7:
                if (undo(ui->service)==0)printf("No more undos\n");
                else printf("undid successfully\n");
                break;
            case 8:
                if (redo(ui->service)==0)printf("No more redos\n");
                else printf("redid successfully\n");
                break;
            case 9:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid option\n");
                break;
        }
    }
}
void destroyUi(Ui *ui) {
    destroyService(ui->service);
}