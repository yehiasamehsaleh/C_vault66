#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car
{
    char code[20], color[20], brand[20];
    int engineVolume, price;
};

struct Node
{
    struct Car *car;
    struct Node *next;
};

// ------------------------ functions prototypes ------------------------
void printCarList(struct Node *head);
struct Node *getCarData();
void addCar(struct Node **head);
void searchAndRent(struct Node *head, char brandName[]);
void removeCar(struct Node **head, char code[]);
void removeAboveAverageCar(struct Node **head, char brand[]);
void saveToFile(struct Node *head);

// ------------------------ main ------------------------
int main()
{
    struct Node *head = NULL;
    char rentBrand[20], removeAboveAvgBrand[20], deleteCarCode[20], tmp;
    int choice = -1;

    while (choice != 7)
    {
        printf("1- Add Car\n");
        printf("2- Remove Car\n");
        printf("3- Print List\n");
        printf("4- Rent\n");
        printf("5- Remove Above Average Cars\n");
        printf("6- Save to File\n");
        printf("7- Quit\nPlease enter your choice: ");
        scanf("%d", &choice);
        scanf("%c", &tmp);
        switch (choice)
        {
        case 1:
            addCar(&head);
            break;
        case 2:
            printf("Enter code of car: ");
            gets(deleteCarCode);
            removeCar(&head, deleteCarCode);
            break;
        case 3:
            printCarList(head);
            break;
        case 4:
            printf("Enter brand name: ");
            gets(rentBrand);
            searchAndRent(head, rentBrand);
            break;
        case 5:
            printf("Enter brand name: ");
            gets(removeAboveAvgBrand);
            removeAboveAverageCar(&head, removeAboveAvgBrand);
            break;
        case 6:
            saveToFile(head);
            printf("Saved to file.\n");
            break;
        case 7:
        default:                         
            continue;
            break;
        }
    }

    printf("Successfully terminated.\n");
    return 0;
}

// ------------------------ functions ------------------------
void printCarList(struct Node *head)
{
    struct Node *temp = head;
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    printf("%20s%20s%20s%12s%12s\n", "Code", "Brand", "Color", "Engine", "Price");
    while (temp != NULL)
    {
        printf("%20s%20s%20s%12d%12d\n", temp->car->code, temp->car->brand, temp->car->color, temp->car->engineVolume, temp->car->price);
        temp = temp->next;
    }
}

struct Node *getCarData()
{
    char tempChar;
    struct Node *n;
    n = (struct Node *)malloc(sizeof(struct Node));
    n->car = (struct Car *)malloc(sizeof(struct Car));
    printf("Enter car code: ");
    gets(n->car->code);
    printf("Enter car color: ");
    gets(n->car->color);
    printf("Enter car brand: ");
    gets(n->car->brand);
    printf("Enter car engine volume: ");
    scanf("%d", &n->car->engineVolume);
    printf("Enter car price: ");
    scanf("%d", &n->car->price);
    scanf("%c", &tempChar);
    n->next = NULL;
    return n;
}

void addCar(struct Node **head)
{
    if (*head == NULL)
        *head = getCarData();
    else
    {
        struct Node *newNode = getCarData();
        struct Node *temp;

        if (*head == NULL || strcmp(newNode->car->brand, (*head)->car->brand) <= 0)
        {
            newNode->next = *head;
            *head = newNode;
        }
        else
        {
            temp = *head;
            while (temp->next != NULL && strcmp(temp->next->car->brand, newNode->car->brand) <= 0)
            {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
}

void searchAndRent(struct Node *head, char brandName[])
{
    struct Node *temp = head;
    if (head == NULL)
    {
        printf("List is empty\n");
        return;
    }
    printf("%20s%20s%20s%12s%12s%12s\n", "Code", "Brand", "Color", "Engine", "Price", "Rent");
    while (temp != NULL)
    {
        if (strcmp(brandName, temp->car->brand) == 0)
        {
            printf("%20s%20s%20s%12d%12d%12.2f\n", temp->car->code, temp->car->brand, temp->car->color, temp->car->engineVolume, temp->car->price, (float)temp->car->price * 0.05);
        }
        temp = temp->next;
    }
}

void removeCar(struct Node **head, char code[])
{
    struct Node *temp = *head, *preNode;
    if (temp != NULL && strcmp(temp->car->code, code) == 0)
    {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && strcmp(temp->car->code, code) != 0)
    {
        preNode = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    preNode->next = temp->next;
    free(temp->car);
    free(temp);
}

void removeAboveAverageCar(struct Node **head, char brand[])
{
    int sum = 0, count = 0;
    double average;
    struct Node *temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->car->brand, brand) == 0)
        {
            sum += temp->car->price;
            count += 1;
        }
        temp = temp->next;
    }
    if (count == 0)
        return;
    average = (double)sum / count;
    temp = *head;
    while (temp != NULL)
    {
        if (strcmp(temp->car->brand, brand) == 0)
        {
            if (temp->car->price > (int)average)
            {
                removeCar(&*head, temp->car->code); // pointer to node next to deleted node
                temp = *head;
                continue;
            }
        }
        temp = temp->next;
    }
}

void saveToFile(struct Node *head)
{
    FILE *fptr;
    struct Node *temp = head;
    fptr = fopen("output.txt", "w");
    if (head == NULL)
    {
        return;
    }
    fprintf(fptr, "%20s%20s%20s%12s%12s\n", "Code", "Brand", "Color", "Engine", "Price");
    while (temp != NULL)
    {
        fprintf(fptr, "%20s%20s%20s%12d%12d\n", temp->car->code, temp->car->brand, temp->car->color, temp->car->engineVolume, temp->car->price);
        temp = temp->next;
    }
    fclose(fptr);
}
