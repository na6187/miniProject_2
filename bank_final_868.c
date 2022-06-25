#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int acc_count=1;
struct account
{
    long long int dob, acc_num, aadhar_num;
    int pin;
    float balance;
    char name[100];
};
void init(struct account *accs)
{
    accs->dob=0;
    accs->acc_num=1010101010101010;
    accs->aadhar_num=0;
    accs->balance=10000000;
    accs->pin=9999;
    strcpy(accs->name,"Bank");
}
int verification(struct account *accs)
{
    long long int t_acc_num;
    int flag=0,pos,t_pin;
    printf("Enter your account number\n");
    scanf("%lld",&t_acc_num);
    for(int i=1;i<acc_count;i++)
    {
        if((accs+i)->acc_num == t_acc_num)
        {
            pos=i;
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("Account number does not exist in database\n");
        return -1;
    }
    printf("Enter your pin number for verification : \n");
    scanf("%d",&t_pin);
    if(t_pin == (accs+pos)->pin)
    {
        return pos;
    }
    else
    {
        printf("Incorrect pin number\n");
        return -1;
    }
}
void modify(struct account *accs)
{
    int pos,choice;
    int verify = verification(accs);
    if(verify == -1)
    {
        return;
    }
    else
    {
        pos = verify;
    }
    while(1)
    {
        printf("Choose data to edit: \n");
        printf("1. Name\n");
        printf("2. Date of birth\n");
        printf("3. Pin\n");
        printf("4. Confirm and save account details\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("Enter new name\n");
                char t_name[100];
                scanf(" %[^\n]",t_name);
                strcpy((accs+pos)->name,t_name);
                printf("Name changed to : ");
                for(int i=0;i<strlen((accs+pos)->name);i++)
                {
                    printf("%c",(accs+pos)->name[i]);
                }
                printf("\n");
                break;
            case 2:
                printf("Enter new date of birth in YYYYMMDD format\n");
                memset(&((accs+pos)->dob),0,sizeof(long long int));
                scanf("%lld",&((accs+pos)->dob));
                printf("Date of birth changed to : %lld \n",(accs+pos)->dob);
                break;
            case 3:
                printf("Enter new four digit pin\n");
                memset(&((accs+pos)->pin),0,sizeof(int));
                scanf("%d",&((accs+pos)->pin));
                printf("Pin changed to : %d \n",(accs+pos)->pin);
                break;
            case 4:
                printf("New account details :\n");
                printf("Name : ");
                for(int i=0;i<strlen((accs+acc_count-1)->name);i++)
                {
                    printf("%c",(accs+acc_count-1)->name[i]);
                }
                printf("\n");
                printf("Date of birth : %lld\n",(accs+acc_count-1)->dob);
                printf("Account number : %lld\n",(accs+acc_count-1)->acc_num);
                printf("Aadhar number : %lld\n",(accs+acc_count-1)->aadhar_num);
                printf("Pin number : %lld\n",(accs+acc_count-1)->pin);
                printf("Balance : %lld\n",(accs+acc_count-1)->balance);
                return;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
void balance(struct account *accs)
{
    int pos;
    int verify = verification(accs);
    if(verify == -1)
    {
        return;
    }
    else
    {
        pos = verify;
    }
    printf("Current account balance : %0.2f\n", (accs+pos)->balance);
}
void transaction(struct account *accs)
{
    int pos;
    int verify = verification(accs);
    if(verify == -1)
    {
        return;
    }
    else
    {
        pos = verify;
    }
    printf("Choose the type of transaction : \n");
    printf("1. Withdraw\n");
    printf("2. Deposit\n");
    printf("3. Send money to beneficiary\n");
    int choice;
    scanf("%d",&choice);
    float amount;
    switch(choice)
    {
        case 1:
            printf("Enter amount to withdraw\n");
            scanf("%f",&amount);
            if(amount > ((accs+pos)->balance))
            {
                printf("Not enough balance in accout\n");
                break;
            }
            else
            {
                (accs+pos)->balance-=amount;
                printf("%0.2f withdrawn from account\n",amount);
                printf("Remaining account balance : %0.2f\n", (accs+pos)->balance);
            }
            break;
        case 2:
            printf("Enter amount to deposit\n");
            scanf("%f",&amount);
            (accs+pos)->balance+=amount;
            printf("%0.2f deposited to account\n",amount);
            printf("Current account balance : %0.2f\n", (accs+pos)->balance);
            break;
        case 3:
            printf("Enter the account number of the beneficiary\n");
            long long int beneficiary;
            int dest_flag=0,dest_pos;
            scanf("%lld",&beneficiary);
            for(int j=0;j<acc_count;j++)
            {
                if(j==pos)
                {
                    continue;
                }
                else
                {
                    if(beneficiary == (accs+j)->acc_num)
                    {
                        dest_flag=1;
                        dest_pos=j;
                        //printf("Beneficiary found at pos %d\n",dest_pos);
                        printf("Enter the amount to send to beneficiary\n");
                        scanf("%f",&amount);
                        if(amount > ((accs+pos)->balance))
                        {
                            printf("Not enough balance in accout\n");
                            break;
                        }
                        else
                        {
                            (accs+pos)->balance-=amount;
                            (accs+dest_pos)->balance+=amount;
                            printf("%0.2f sent to beneficiary\n",amount);
                            printf("Remaining account balance : %0.2f\n", (accs+pos)->balance);
                        }
                        break;
                    }
               }
            }
            if(dest_flag==0)
            {
                printf("Beneficiary account doesnt exist\n");
            }
            break;
        default:
            printf("Invalid choice");
            return;
    }   
}
void open_acc(struct account *accs)
{
    acc_count++;
    if(acc_count==2)
    {
        acc_count+=2;
    }
    accs = (struct account *)realloc(accs,acc_count);
    memset(&((accs+acc_count-1)->pin),0,sizeof(int));
    memset(&((accs+acc_count-1)->dob),0,sizeof(long long int));
    memset(&((accs+acc_count-1)->acc_num),0,sizeof(long long int));
    memset(&((accs+acc_count-1)->aadhar_num),0,sizeof(long long int));
    memset(&((accs+acc_count-1)->balance),0,sizeof(float));
    memset(&((accs+acc_count-1)->name),'\0',sizeof(long long int)); 
    struct account temp;
    printf("Enter your date of birth in YYYYMMDD format\n");
    scanf("%lld",&temp.dob);
    printf("Enter your name\n");
    char t_name[100];
    scanf(" %[^\n]",temp.name);
    strcpy((accs+acc_count-1)->name,temp.name);
    printf("Enter your aadhar number\n");
    scanf("%lld",&temp.aadhar_num);
    printf("Set your four digit pin number\n");
    scanf("%d",&temp.pin);
    (accs+acc_count-1)->pin=temp.pin;
    (accs+acc_count-1)->aadhar_num=temp.aadhar_num;
    (accs+acc_count-1)->dob=temp.dob;
    (accs+acc_count-1)->balance=0;
    (accs+acc_count-1)->acc_num=rand();
    printf("Congratulations, your account has been opened. Account details:\n");
    printf("Name : ");
    for(int i=0;i<strlen((accs+acc_count-1)->name);i++)
    {
        printf("%c",(accs+acc_count-1)->name[i]);
    }
    printf("\n");
    printf("Date of birth : %lld\n",(accs+acc_count-1)->dob);
    printf("Account number : %lld\n",(accs+acc_count-1)->acc_num);
    printf("Aadhar number : %lld\n",(accs+acc_count-1)->aadhar_num);
    printf("Pin number : %lld\n",(accs+acc_count-1)->pin);
    printf("Balance : %lld\n",(accs+acc_count-1)->balance);
}
void display()
{
    printf("Enter your choice of operation\n");
    printf("1. Open new account\n");
    printf("2. Make transaction\n");
    printf("3. Check account balance\n");
    printf("4. Modify account details\n");
    printf("5. Exit\n");
    printf("Choose your operation 1 to 5\n");
}
void menu(struct account *accs)
{
    
    while(1)
    {
        int choice;
        display();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                open_acc(accs);
                break;
            case 2:
                transaction(accs);
                break;
            case 3:
                balance(accs);
                break;
            case 4:
                modify(accs);
                break;
            case 5:
                printf("Thank you for transacting with us");
                return;
            default:
                printf("Invalid choice");             
                break;
        }
    }
}
int main()
{
    srand(time(0));
    struct account *accs;
    accs = (struct account *)calloc(acc_count, sizeof(struct account));
    init(accs);
    menu(accs);
    return 0;
}
