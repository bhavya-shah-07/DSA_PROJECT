#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//queue declare
typedef struct node{
int id;
char name[50];
int priority;
struct node *next;
}node;

node* head = NULL;
node* vipRear = NULL;
node* regRear = NULL;
//enqueue
void addticket(){
    int id,priority;
    char name[50];

    printf("enter customer id:");
    scanf("%d",&id);

    while (getchar() != '\n');
    printf("enter customer Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name,"\n")] = '\0';

    printf("enter priority level(1 for VIP,2 for regular):");
    scanf("%d", &priority);

    if(priority !=1&&priority !=2){
        printf("invalid priority");
        return;
    }

    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("memory allocation failed");
        return;
    }

    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->priority = priority;
    newNode->next = NULL;

    if(priority == 1){
        if(head == NULL){
            head = newNode;
            vipRear = newNode;
            regRear = newNode;
        }
        else if(vipRear== NULL){
            newNode->next = head;
            head = newNode;
            vipRear = newNode;
        }
        else{
            newNode->next = vipRear->next;
            vipRear->next = newNode;
            vipRear = newNode;
        }
    }
    else{
        if(head == NULL){
            head = newNode;
            regRear = newNode;
        }
        else{
            regRear->next = newNode;
            regRear = newNode;
        }
    }
}
//dequeue
void process(){
    if(head == NULL){
        printf("no ticket to process");
        return;
    }
    node* temp = head;

    if (temp == vipRear) {
        vipRear = NULL;
    }

    if (temp == regRear) {
        regRear = NULL;
    }
    head = head->next;
    free(temp);
}

//display queue
void displayQueue()
{
    if(head == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    node *temp = head;
    int wait = 0;

    printf("\nID\tName\tPriority\tWaiting position\n");

    while(temp != NULL)
    {
        printf("%d\t%s\t",temp->id,temp->name);

        if(temp->priority == 1){
            printf("VIP\t");
        }
        else
            printf("Regular\t");

        printf("\t%d\n",wait+1);

        wait++;
        temp = temp->next;
    }
}
//check ticket status
void checkTicketStatus()
{
    int id;
    int wait = 0;

    printf("Enter Ticket ID: ");
    scanf("%d",&id);

    node *temp = head;

    while(temp != NULL)
    {
        if(temp->id == id)
        {
            printf("\nTicket Found\n");
            printf("ID: %d\n",temp->id);
            printf("Name: %s\n",temp->name);

            if(temp->priority == 1)
                printf("Priority: VIP\n");
            else
                printf("Priority: Regular\n");

            if(wait == 0)
                printf("Status: Next in line!\n");
            else
                printf("Status: Waiting (%d people ahead)\n",wait);

            return;
        }

        wait++;
        temp = temp->next;
    }

    printf("Ticket not found\n");
}

int main()
{
    int choice;

    do
    {
        printf("\nCUSTOMER SERVICE QUEUE\n");
        printf("1. Add Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Queue\n");
        printf("4. Check Ticket Status\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                addticket();
                break;

            case 2:
                process();
                break;

            case 3:
                displayQueue();
                break;

            case 4:
                checkTicketStatus();
                break;

            case 5:
                printf("Program ended\n");
                break;

            default:
                printf("Invalid choice\n");
        }

    }while(choice != 5);

    return 0;
}

