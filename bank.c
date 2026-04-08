#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------- CUSTOMER STRUCT -----------
struct Customer {
    int accNo;
    char name[50];
    float balance;
    struct Customer* next;
};

// Head pointer for linked list
struct Customer* head = NULL;

// ----------- STACK (Undo Delete) -----------
struct Stack {
    int accNo;
    char name[50];
    float balance;
    struct Stack* next;
};

struct Stack* top = NULL;

// Push into stack
void push(int accNo, char name[], float balance) {
    struct Stack* newNode = (struct Stack*)malloc(sizeof(struct Stack));
    newNode->accNo = accNo;
    strcpy(newNode->name, name);
    newNode->balance = balance;
    newNode->next = top;
    top = newNode;
}

// Pop from stack
void pop() {
    if (top == NULL) {
        printf("Nothing to undo!\n");
        return;
    }

    struct Customer* newCustomer = (struct Customer*)malloc(sizeof(struct Customer));
    newCustomer->accNo = top->accNo;
    strcpy(newCustomer->name, top->name);
    newCustomer->balance = top->balance;
    newCustomer->next = head;
    head = newCustomer;

    struct Stack* temp = top;
    top = top->next;
    free(temp);

    printf("Undo successful!\n");
}

// ----------- QUEUE -----------
struct Queue {
    int accNo;
    char name[50];
    float balance;
    struct Queue* next;
};

struct Queue *front = NULL, *rear = NULL;

// Enqueue
void enqueue(int accNo, char name[], float balance) {
    struct Queue* newNode = (struct Queue*)malloc(sizeof(struct Queue));
    newNode->accNo = accNo;
    strcpy(newNode->name, name);
    newNode->balance = balance;
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
        return;
    }

    rear->next = newNode;
    rear = newNode;
}

// Dequeue
void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }

    struct Queue* temp = front;
    front = front->next;

    if (front == NULL)
        rear = NULL;

    free(temp);
}

// ----------- LINKED LIST FUNCTIONS -----------

// Add Customer
void addCustomer() {
    struct Customer* newNode = (struct Customer*)malloc(sizeof(struct Customer));

    printf("Enter Account Number: ");
    scanf("%d", &newNode->accNo);
    printf("Enter Name: ");
    scanf("%s", &newNode->name);
    printf("Enter Balance: ");
    scanf("%f", &newNode->balance);

    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        struct Customer* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    printf("Customer Added Successfully!\n");
}

// Display Customers
void displayCustomers() {
    struct Customer* temp = head;

    if (temp == NULL) {
        printf("No Customers Found!\n");
        return;
    }

    while (temp != NULL) {
        printf("AccNo: %d | Name: %s | Balance: %.2f\n",
               temp->accNo, temp->name, temp->balance);
        temp = temp->next;
    }
}

// Search Customer
struct Customer* searchCustomer(int accNo) {
    struct Customer* temp = head;

    while (temp != NULL) {
        if (temp->accNo == accNo)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Modify Customer
void modifyCustomer() {
    int accNo;
    printf("Enter Account Number to Modify: ");
    scanf("%d", &accNo);

    struct Customer* c = searchCustomer(accNo);

    if (c != NULL) {
        printf("Enter New Name: ");
        scanf("%s", c->name);
        printf("Enter New Balance: ");
        scanf("%f", &c->balance);
        printf("Updated Successfully!\n");
    } else {
        printf("Customer Not Found!\n");
    }
}

// Delete Customer
void deleteCustomer() {
    int accNo;
    printf("Enter Account Number to Delete: ");
    scanf("%d", &accNo);

    struct Customer *temp = head, *prev = NULL;

    while (temp != NULL && temp->accNo != accNo) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Customer Not Found!\n");
        return;
    }

    // Push to stack for undo
    push(temp->accNo, temp->name, temp->balance);

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Deleted Successfully!\n");
}

// ----------- MAIN FUNCTION -----------
int main() {
    int choice;

    while (1) {
        printf("\n--- BANK MENU ---\n");
        printf("1. Add Customer\n");
        printf("2. Display Customers\n");
        printf("3. Modify Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Undo Delete\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: modifyCustomer(); break;
            case 4: deleteCustomer(); break;
            case 5: pop(); break;
            case 6: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}