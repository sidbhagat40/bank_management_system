#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>


void chkblnc();
void search();
void search_acc();
void search_name();
void view();
void user_deposit(int ver_account);
void chkblnc_user(char*id);
void user_withdrawl(int ver_account);
void user_chkblnc(int ver_account);
void user_panel();
void menu();
void option();
void menuexit();
void user_login();
int check (int*user_id,int*tempID);
void add();
void edit();
void del();
void about();
void admin();
void login();
void user_menu();
void print_transaction_history(int ver_account);
void option_user();
void user_transaction();
void user_name_search(int ver_account);
char id[20], password[15],input[15],loan_input[15];
int user_id[10],loan_id[10];
char user_pass[20];
int ver_account =  0;
int tempID[10],temp_loanID[10];


int verify();
int chkacc();

COORD coord = {0, 0};
int m, r; 



struct transaction
{
    char type[15]; 
    double amount;
    char date[20]; 
};

struct record
{
    char name[25];
    int account;
    char phone[15];
    char address[25];
    char email[35];
    char citiz[20];
    double blnc;
    char UserID[20];
    char pass_word[40];
    struct transaction transactions[10];
    int transaction_index;
} rec;



void set_pos(int a, int b)
{
    coord.X = a;
    coord.Y = b;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
    system("CLS");
    system("color 02");
    set_pos(43, 4);
    printf(" WELCOME TO IITJ BANKING SYSTEM ");
    set_pos(50, 8);
    printf("ACCOUNT TYPE");
    set_pos(44, 10);
    printf("[1] . ADMINISTRATOR ");
    set_pos(44, 11);
    printf("[2] . USER ");
    set_pos(44, 14);
    printf("Enter Your Choice .... ");
    scanf("%d", &m);
    system("CLS");

    if (m == 1)
        admin();
    else if (m == 2)
        user_panel();
    else
        main();

    return 0;
}

void admin()
{
    char i ;
    system("color 02");
    set_pos(43, 4);
    printf(" WELCOME TO IITJ BANKING SYSTEM ");
    login();
    if (verify() == 1)
    {
        if (m == 1)
            menu();
        else
            main();
    }
    else if (verify() == 0)
    {
        system("CLS");
        set_pos(43, 16);
        printf("Incorrect Username / Password !!!!");
        set_pos(43,18);
        printf("[0] ---> Return, [Any key] ---> Retry");

        i = getch();
        switch(i)
        {
            case '0':
                system("CLS");
                main();
            default:
                system("CLS");
                admin();

        }
        
    }
}
void user_panel()
{
    int i;
    system("CLS");
    set_pos(43, 4);
    printf(" WELCOME TO IITJ BANKING SYSTEM ");
    user_login(); 
    if (verify() == 1)
    {
        if (m == 2)
        {                
            user_menu(); 
            return;      
        }
        else
        {
            main(); 
            return; 
        }
    }
    if(verify() == 0)
    {
        system("CLS");
        printf("User does not exist\n");
        printf("Enter 0 to Exit or 1 to relogin ");
        i = getch();
        if(i==13)
        main();
        else 
        user_panel();

        
    }
}

void login()
{
    int i = 0;
    set_pos(44, 10);
    printf("Enter The UserID : ");
    scanf(" %[^\n]",id);
    set_pos(44, 12);
    printf("Enter The Password : ");
    scanf(" %[^\n]", password);
}


int verify()
{
    FILE *f;
    char a,x;
    int num;
    
    int r;
    if (m == 1)
    {
        
        if ((strcmp(id, "admin") == 0 && strcmp(password, "admin") == 0))
        {
            
            return 1;
        }
        else
        {
            
            return 0;
        }
    }
    else if (m == 2)
    {
     
        f = fopen("data.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, f))
        {
            
            for (r = 0; r < 10; r++)
        {
            int x = rec.UserID[r];            
            tempID[r] = x;
                       
        }       
        if ( check(tempID,user_id) && strcmp(rec.pass_word, user_pass) == 0)
            {
             
                ver_account = rec.account;
                
                sleep(2);
                fclose(f);
                return 1;
            }
        }
       
        fclose(f);
        getch();
        return 0;
    }
    return 0;
}


void menu()
{
    while ((getchar()) != '\n');
    system("CLS");
    set_pos(48, 4);
    printf("WELCOME TO MAIN MENU");
    set_pos(44, 8);
    printf("[1] . View Customer Accounts");
    set_pos(44, 9);
    printf("[2] . Customer Account Registration");
    set_pos(44, 10);
    printf("[3] . Edit Customer Account");
    set_pos(44, 11);
    printf("[4] . Delete Customer Account");
    set_pos(44, 12);
    printf("[5] . Search Customer Account");
    set_pos(44, 13);
    
    printf("[6] . About US !!! ");
    set_pos(44, 14);
    printf("[7] . Log out ");
    set_pos(43, 20);
    printf("Please Enter Your Choice [1-7] : ");
    option();
}


void option()
{
    int i;
    scanf("%d", &i);
    system("CLS");
    switch (i)
    {
    case 1:
        view();
        break;
    case 2:
        add();
        break;
    case 3:
        edit();
        break;
    case 4:
        del();
        break;
    case 5:
        search();
    case 6:
        about();
        break;
    case 7:
        main();
        break;
    
    default:
        menu();
    }
}


void view()
{
    int i = 7;
    struct record rec;
    FILE *f;
    
    f = fopen("data.bin", "rb");
    set_pos(40, 3);
    printf("CUSTOMERS LIST");
    set_pos(5, 5);
    printf("A/C No.");
    set_pos(15, 5);
    printf("Account Name");
    set_pos(34, 5);
    printf("UserID");
    set_pos(49, 5);
    printf("Email Address");
    set_pos(85, 5);
    printf("Phone No.");
    set_pos(99, 5);
    printf("Balance");
    set_pos(5, 6);
   
    while (fread(&rec, sizeof(rec), 1, f))
    {
        set_pos(7, i);
        printf("%d", rec.account);
        set_pos(15, i);
        printf("%s", rec.name);
        set_pos(34, i);
        for (r = 0; r < 10; r++)
        {
            printf("%d", rec.UserID[r]);
        }
        set_pos(49, i);
        printf("%s", rec.email);
        set_pos(85, i);
        printf("%s", rec.phone);
        set_pos(99, i);
        printf("Rup. %.2lf", rec.blnc);
        i++;
    }
    
    fclose(f);
    int x;
    set_pos(42, i + 5);
    printf("Press [Enter] to return back to main menu. ");
    x = getch();
    
    if (x == 13)
    {
        menu();
    }
    else
        view();
}


void add()
{
    int a = 0;
    char c;
    struct record rec;
    FILE *f;
    
    f = fopen("data.bin", "ab");
    int i = 0, x;
    
    do
    {
        system("CLS");
        set_pos(24, 4);
        printf("\t\t\tCUSTOMER ACCOUNT REGISTRATION");
        set_pos(36, 8);
        printf("[1] . Enter Your Name           : ");
        scanf(" %[^\n]", rec.name);
        set_pos(36, 9);
        printf("[2] . Enter Your Account Number : ");
        scanf(" %d", &rec.account);
        set_pos(36, 10);
        printf("[3] . Enter Your Phone Number   : ");
        scanf(" %[^\n]", rec.phone);
        set_pos(36, 11);
        printf("[4] . Enter Your Address        : ");
        scanf(" %[^\n]", rec.address);
        set_pos(36, 12);
        printf("[5] . Enter Your E-mail         : ");
        scanf(" %[^\n]", rec.email);
        set_pos(36, 13);
        printf("[6] . Enter Your Aadhar No.     : ");
        scanf(" %[^\n]", rec.citiz);
        set_pos(36, 14);
        printf("[7] . Enter Amount To Deposit   : Rup. ");
        scanf(" %lf", &rec.blnc);
        srand(time(NULL));
        for (r = 0; r < 10; r++)
        {
            a=0;
            a = rand() % 10;
            rec.UserID[r] = a;
        }
            

        set_pos(36, 15);
        printf("[8] . Enter password            : ");
        scanf("%s", rec.pass_word);
        
        

        rec.transaction_index = 0;

        
        fwrite(&rec, sizeof(rec), 1, f);
        set_pos(38,17);
        printf("      UserId                    : ");
        for (r = 0; r < 10; r++)
        {
            printf("%d", rec.UserID[r]);
        }
        set_pos(38, 19);
        printf("REGISTRATION SUCCESSFULL");
        i++;
        set_pos(36, 20);
        printf("Do You Want To Add Another Account ? (Y/N) : ");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');
    fclose(f);
    set_pos(40, 22);
    printf("Press enter key to return back to main menu. ");
    char z = getch();
    if (z == 13)
    {
        menu();
    }
}


int chkacc(int a)
{
    FILE *f;
    f = fopen("data.bin", "rb");
    
    while (!feof(f))
    {
        fread(&rec, sizeof(rec), 1, f);

        if (a == rec.account)
        {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}


void edit()
{
    FILE *x, *y;
    int a, c;

re:
    set_pos(48, 4);
    printf(" EDIT CUSTOMER ACCOUNT ");
    set_pos(43, 7);
    printf("Enter Your Account Number To Edit : ");
    scanf("%d", &a);
    if (chkacc(a) == 1)
    {
        x = fopen("data.bin", "rb");
        y = fopen("new.bin", "wb");
        while (fread(&rec, sizeof(rec), 1, x))
        {
            if (rec.account != a)
                fwrite(&rec, sizeof(rec), 1, y);
            else if (rec.account == a)
            {
                set_pos(52, 21);
                printf("Account Number Matched. ");
                set_pos(51, 10);
                printf("Enter Your Details");
                set_pos(31, 12);
                printf("[1] . Enter Your Name           : ");
                scanf(" %[^\n]", rec.name);
                set_pos(31, 13);
                printf("[2] . Enter Your Account Number : ");
                scanf(" %d", &rec.account);
                set_pos(31, 14);
                printf("[3] . Enter Your Phone Number   : ");
                scanf(" %[^\n]", rec.phone);
                set_pos(31, 15);
                printf("[4] . Enter Your Address        : ");
                scanf(" %[^\n]", rec.address);
                set_pos(31, 16);
                printf("[5] . Enter Your E-mail         : ");
                scanf(" %[^\n]", rec.email);
                set_pos(31, 17);
                printf("[6] . Enter Your Aadhar No : ");
                scanf(" %[^\n]", rec.citiz);
                fwrite(&rec, sizeof(rec), 1, y);
            }
        }
        fclose(x);
        fclose(y);
    }
    if (chkacc(a) == 0)
    {
        system("CLS");
        set_pos(52, 21);
        printf("Account Doesn't Exist. ");
        set_pos(53,24);
        printf("Going back to menu");
        sleep(2);
        system("cls");
        menu();

    }
    remove("data.bin");
    rename("new.bin", "data.bin");
    set_pos(45, 21);
    printf("CUSTOMER ACCOUNT UPDATE SUCCESSFULL");
    set_pos(42, 24);
    printf("Press any key to return back to main menu . ");
    getch();
    menu();
}


void del()
{
    FILE *x, *y;
    int a, c;
re:
    set_pos(48, 4);
    printf(" DELETE CUSTOMER ACCOUNT ");
    set_pos(41, 9);
    printf("Enter Your Account Number To Delete : ");
    scanf("%d", &a);
    if (chkacc(a) == 1)
    {
        x = fopen("data.bin", "rb");
        y = fopen("new.bin", "wb");
        while (fread(&rec, sizeof(rec), 1, x))
        {
            if (rec.account != a)
                fwrite(&rec, sizeof(rec), 1, y);
        }
        fclose(x);
        fclose(y);
        x = fopen("data.bin", "wb");
        y = fopen("new.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, y))
            fwrite(&rec, sizeof(rec), 1, x);
        fclose(x);
        fclose(y);
    }
    else 
    {
        system("CLS");
        set_pos(51, 15);
        printf("Account Doesn't Exist");
        sleep(2);
        system("cls");
        menu();

    }
    set_pos(44, 15);
    printf("CUSTOMER ACCOUNT DELETED SUCCESSFULLY");
    set_pos(42, 18);
    printf("Press any key to return back to main menu. ");
    getch();
    
    menu();
}


void search()
{
    system("cls");
    int a;
    set_pos(55, 4);
    printf(" SEARCH MENU ");
    set_pos(49, 10);
    printf("[1] . Search By Account ");
    set_pos(49, 12);
    printf("[2] . Search By Name ");
    set_pos(47, 17);
    printf("Enter Your Choice [1-2] : ");
    scanf("%d", &a);
    system("cls");
    if (a == 1)
    {
        search_acc();
    }
    else if (a == 2)
    {
        search_name();
    }
    else
        menu();
}

void search_acc()
{
    FILE *f;
    int a, x, y;
re:
    system("CLS");
    set_pos(48, 4);
    printf(" SEARCH CUSTOMER ACCOUNT ");
    set_pos(43, 7);
    printf("Enter Your Account Number To Search : ");
    scanf("%d", &a);
    if (chkacc(a) == 1)
    {
        f = fopen("data.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, f))
        {
            if (rec.account == a)
            {
                set_pos(52, 21);
                printf("Account Number Matched. ");
                set_pos(45, 10);
                printf("Detail Information of %s", strupr(rec.name));
                set_pos(37, 12);
                printf("[1] . Account Number : %d", rec.account);
                set_pos(37, 13);
                printf("[2] . Name           : %s", rec.name);
                set_pos(37, 14);
                printf("[3] . UserID         : ");
                for (r = 0; r < 10; r++)
                {
                    printf("%d", rec.UserID[r]);
                }
                set_pos(37, 15);
                printf("[4] . Phone Number   : %s", rec.phone);
                set_pos(37, 16);
                printf("[5] . Address        : %s", rec.address);
                set_pos(37, 17);
                printf("[6] . E-mail         : %s", rec.email);
                set_pos(37, 18);
                printf("[7] . Aadhar No : %s", rec.citiz);
                set_pos(37, 19);
                printf("[8] . Current Balance: Rup. %.2lf", rec.blnc);
                break;
            }
        }
        fclose(f);
    }
    if (chkacc(a) == 0)
    {
        system("CLS");
        set_pos(52, 21);
        printf("Account Doesn't Exist.  ");
        set_pos(52, 24);
        printf("press anything ---> Retry, [2]---> Return Back, [3]---> Exit");

        y = getch();
        system("CLS");
        switch (y)
        {
            case '2':
                search();
                break;
            case '3':
                main();
                break;
            default:
                goto re;
        }


        
    }
    set_pos(42, 24);
    printf("Press [ENTER] to return back to main menu. ");
    char z = getch();
    if (z == 13)
        menu();
    else
        search();
}

void search_name()
{
    int i = 0, b, x;
    char nam[30];
    set_pos(48, 4);
    printf(" SEARCH CUSTOMER ACCOUNT ");
    set_pos(43, 7);
    printf("Enter Your Full Name To Search : ");
    scanf(" %[^\n]", nam);
    FILE *f;
    f = fopen("data.bin", "rb");
    while (fread(&rec, sizeof(rec), 1, f))
    {
        b = 0;
        strupr(rec.name);
        strupr(nam);
        if (strcmp(rec.name, nam) == 0)
        {
            set_pos(52, 21);
            printf("Account Number Matched. User is Active.");
            set_pos(45, 10);
            printf("Detail Information of %s", rec.name);
            set_pos(37, 12);
            printf("[1] . Account Number : %d", rec.account);
            set_pos(37, 13);
            printf("[2] . Name           : %s", rec.name);
            set_pos(37, 14);
            printf("[3] . UserID         : ");
            for (r = 0; r < 10; r++)
            {
                printf("%d", rec.UserID[r]);
            }
            set_pos(37, 15);
            printf("[4] . Phone Number   : %s", rec.phone);
            set_pos(37, 16);
            printf("[5] . Address        : %s", rec.address);
            set_pos(37, 17);
            printf("[6] . E-mail         : %s", rec.email);
            set_pos(37, 18);
            printf("[7] . Aadhar No : %s", rec.citiz);
            set_pos(37, 19);
            printf("[8] . Current Balance: Rup. %.2lf", rec.blnc);
            set_pos(37, 20);
            printf("[9] . Password: %s", rec.pass_word);
            break;
        }
        else
            b = 1;
    }
    fclose(f);
    if (b == 1)
    {
        system("cls");
        set_pos(52, 21);
        printf("Account Doesn't Exist. User is Inactive.");
        search_name();
    }
    set_pos(42, 24);
    printf("Press [ENTER] to return back to main menu. ");
    char z = getch();
    if (z == 13)
        menu();
    else
        search();
}
void chkblnc()
{
    FILE *f;
    int a;
    set_pos(48, 4);
    printf(" BALANCE INQUIRY ");
    set_pos(47, 12);
    printf("Enter Your Account Number : ");
    scanf("%d", &a);
    if (chkacc(a) == 1)
    {
        f = fopen("data.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, f))
        {
            if (rec.account == a)
            {
                set_pos(50, 15);
                printf("Your Balance is : Rup. %.2lf", rec.blnc);
            }
        }
        fclose(f);
    }
    if (chkacc(a) == 0)
    {
        system("cls");
        set_pos(52, 15);
        printf("Account Doesn't Exist.");
        chkblnc();
    }
    set_pos(46, 21);
    printf("Press any key to return back to main menu. ");
    getch();
    user_transaction();
    
}
void menuexit()
{
    system("cls");
    set_pos(48, 10);
    printf("!!! THANK YOU !!!");
    set_pos(50, 12);
    printf("USER :: %s", id);
    getch();
    set_pos(0, 26);
    exit(0);
}

void about()
{
    
    set_pos(48, 10);
    printf("!!!ABOUT US!!!");
    set_pos(32, 12);
    printf("This project has been created by Siddharth,Prayag,Yogendra,Sparsh.");
    set_pos(10, 13);
    printf("It is a Simple Bank Management System Project for our spring semester based on C language.");
    set_pos(40, 22);
    printf("Press enter key to return back to main menu. ");
    char z = getch();
    if (z == 13)
    {
        if(m==1)
        menu();
        else
        user_menu();
    }
}

void user_login()
{

    int i = 0,j;
    set_pos(44, 10);
    printf("Enter The UserID : ");
    while ((getchar()) != '\n');
    fgets(input, sizeof(input), stdin);
    
    if(strlen(input) != 11)
    {
        printf("Invalid input. Please enter a 10-digit number.\n");
        sleep(2);
        system("cls");
        set_pos(44,15);
        printf("[Any Key]---> Retry, [1]---> Menu");
        j = getchar();
        system("cls");
        switch (j)
        {
            
            case '1':
                main();
                break;
            default:
                user_login();
                
        }

    }

    input[strlen(input) - 1] = '\0';

    for (int i = 0; i < 10; i++) 
    {
        user_id[i] = input[i] - '0';
    }
     
    set_pos(44, 12);
    printf("Enter The Password : ");
    scanf(" %[^\n]", user_pass);
}

void user_menu()
{
    system("CLS");
    set_pos(48, 4);
    printf("WELCOME TO USER MENU");
    set_pos(44, 8);
    printf("[1] . View Account Details");
    set_pos(44, 9);
    printf("[2] . Transaction");
    set_pos(44, 10);
    printf("[3] . Check Balance");
    set_pos(44, 11);
    printf("[4] . Log Out !!! ");
    set_pos(44, 12);
    printf("[5] . About our group ");
    set_pos(43, 16);
    printf("Please Enter Your Choice [1-5] : ");
    option_user(); 
}
void option_user()
{
    int i;
    scanf("%d", &i);
    system("CLS");
    switch (i)
    {
    case 1:
        user_name_search(ver_account);
        break;
    case 2:
        user_transaction();
        break;
    case 3:
        user_chkblnc( ver_account);
        break;
    case 4:
        main();
        break;
    case 5:
        about();
        break;
    default:
        user_menu();
    }
}
void chkblnc_user(char*id)
{
    FILE *f;
    int a;
    set_pos(48, 4);
    printf(" BALANCE INQUIRY ");
    f = fopen("data.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, f))
        {
            if (rec.name == id)
            {
                set_pos(50, 15);
                printf("Your Balance is : Rup. %.2lf", rec.blnc);
            }
            
            
        }
        fclose(f);
        set_pos(46, 21);
    printf("Press any key to return back to main menu. ");
    getch();
    user_menu();


}
void print_transaction_history(int ver_account) {
    int h = 0;
    FILE *f;
    f = fopen("data.bin", "rb");
    if (f == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct record rec;
    int found = 0;
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == ver_account) 
        {
            found = 1;
            printf("Transaction History for Account Number %d:\n", rec.account);
            printf("--------------------------------------------------\n");
            printf("%-15s %-10s %-20s\n", "Type", "Amount", "Date");
            printf("--------------------------------------------------\n");
            int start_index = (rec.transaction_index > 10) ? rec.transaction_index - 10 : 0;
            for (int i = start_index; i < rec.transaction_index && i < start_index + 10 ; i++) {
                printf("\n\n%-15s Rup. %-9.2lf %-20s\n", rec.transactions[i].type, rec.transactions[i].amount, rec.transactions[i].date);
            }
            printf("--------------------------------------------------\n");
            fclose(f);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("Enter 1 to go back: ");
            scanf("%d", &h);
            if (h == 1)
                user_transaction();
            else
                print_transaction_history(ver_account);
        }
    }

    if (!found) {
        printf("Account number not found.\n");
        fclose(f);
        sleep(3);
        user_transaction();
    }
}

void user_name_search(int ver_account)
{
    int i = 0, b, x;
    FILE *f;
    f = fopen("data.bin", "rb");
    while (fread(&rec, sizeof(rec), 1, f))
    {
        b = 0;
        if (rec.account == ver_account)
        {
            
            set_pos(45, 10);
            printf("Bank Details of %s", rec.name);
            set_pos(37, 12);
            printf("[1] . UserID         : ");
            for (r = 0; r < 10; r++)
            {
                printf("%d", rec.UserID[r]);
            }
            set_pos(37, 13);
            printf("[2] . Name           : %s", rec.name);
            set_pos(37, 14);
            printf("[3] . Account no.    : %d",rec.account);            
            set_pos(37, 15);
            printf("[4] . Phone Number   : %s", rec.phone);
            set_pos(37, 16);
            printf("[5] . Address        : %s", rec.address);
            set_pos(37, 17);
            printf("[6] . E-mail         : %s", rec.email);
            set_pos(37, 18);
            printf("[7] . Aadhar No      : %s", rec.citiz);
            set_pos(37, 19);
            printf("[8] . Balance        : Rup. %.2lf", rec.blnc);
            set_pos(37, 20);
            //printf("[9] . Password     : %s", rec.pass_word);
            break;
        }
        else
            b = 1;
    }
    fclose(f);
    if (b == 1)
    {
        system("cls");
        set_pos(52, 21);
        printf("Account Doesn't Exist.");
        user_name_search(ver_account);
    }
    set_pos(42, 24);
    printf("Press [ENTER] to return back to user menu. ");
    char z = getch();
    if (z == 13)
        user_menu();
    else
        user_name_search(ver_account);
}
void user_transaction()
{
    system("CLS");
    set_pos(48, 4);
    printf(" TRANSACTION MENU ");
    
    if (m == 2)
    {
        set_pos(49, 9);
        printf("[1] . Balance Inquiry");
        set_pos(49, 10);
        printf("[2] . Cash Deposit");
        set_pos(49, 11);
        printf("[3] . Cash Withdrawal");
        set_pos(49, 12);
        printf("[4] . Main Menu");
    }
    else
    {
        set_pos(49, 13);
        printf("[4] . Exit");
    }

    set_pos(45, 17);
    printf("Please Enter Your Choice [1-4] : ");
    int a;
    scanf("%d", &a);
    switch (a)
    {
    case 1:
        system("cls");
        print_transaction_history(ver_account);
        break;
    case 2:
        system("cls");
        user_deposit(ver_account);
        break;
    case 3:
        system("cls");
        user_withdrawl(ver_account);
        break;
    
    case 4:
        system("cls");
        user_menu();
        break;
    
    default:
        user_transaction();
    }
}
void user_deposit(int ver_account)
{
    int a;
    double b;
    FILE *x, *y;
    int deposit_done = 0; 
    
    set_pos(54, 4);
    printf(" CASH DEPOSIT ");
    
    x = fopen("data.bin", "rb");
    if (x == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    y = fopen("new.bin", "wb");
    if (y == NULL) {
        printf("Error creating file!\n");
        fclose(x);
        return;
    }
    
    while (fread(&rec, sizeof(rec), 1, x))
    {
        if (rec.account == ver_account)
        {
            
            rec.name;
            rec.account;
            rec.phone;
            rec.address;
            rec.email;
            rec.citiz;
            set_pos(45, 13);
            printf("Enter amount : ");
            scanf("%lf", &b);
            rec.blnc += b;
            printf("CASH DEPOSIT SUCCESSFULL\n");
            
            strcpy(rec.transactions[rec.transaction_index].type, "Deposit");
            rec.transactions[rec.transaction_index].amount = b;
            time_t now;
            time(&now);
            strcpy(rec.transactions[rec.transaction_index].date, ctime(&now));
            rec.transaction_index++;
            
            deposit_done = 1;
        }
        
        fwrite(&rec, sizeof(rec), 1, y);
    }
    
    if (!deposit_done)
    {
       
        printf("User not found or deposit already made.\n");
    }
    
    fclose(x);
    fclose(y);
    
    x = fopen("data.bin", "wb");
    if (x == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    y = fopen("new.bin", "rb");
    if (y == NULL) {
        printf("Error opening file!\n");
        fclose(x);
        return;
    }
    
    while (fread(&rec, sizeof(rec), 1, y))
    {
        fwrite(&rec, sizeof(rec), 1, x);
    }
    
    fclose(x);
    fclose(y);
    
   
    set_pos(50, 24);
    printf("Press any key to return back...");
    getch();
    user_transaction();
}
void user_withdrawl(int ver_account)
{
    FILE *x, *y;
    int a;
    double b, z;
    set_pos(54, 4);
    printf(" CASH WITHDRAWAL ");

        x = fopen("data.bin", "rb");
        y = fopen("new.bin", "wb");
        set_pos(42, 13);
        printf("Enter The Amount To Withdraw : Rup.  ");
        scanf("%lf", &b);
        while (fread(&rec, sizeof(rec), 1, x))
        {
            if (rec.account != ver_account)
                fwrite(&rec, sizeof(rec), 1, y);
            else if (rec.account == ver_account)
            {
                rec.name;
                rec.account;
                rec.phone;
                rec.address;
                rec.email;
                rec.citiz;
                z = rec.blnc;
                if (b <= rec.blnc)
                {
                    rec.blnc -= b;
                    set_pos(44, 21);
                    printf("    CASH WITHDRAWAL SUCCESSFULL     ");
                }

                
                strcpy(rec.transactions[rec.transaction_index].type, "Withdrawal");
                rec.transactions[rec.transaction_index].amount = b;
                time_t now;
                time(&now);
                strcpy(rec.transactions[rec.transaction_index].date, ctime(&now));
                rec.transaction_index++;

                fwrite(&rec, sizeof(rec), 1, y);
            }
        
        fclose(x);
        fclose(y);
        remove("data.bin");
        rename("new.bin", "data.bin");
        if (z < b)
        {
            system("CLS");
            set_pos(48, 21);
            printf("Current Balance is Rup. %.2lf", z);
            set_pos(42, 24);
            printf("Entered amount exceeds current balance");
            user_withdrawl(ver_account);
        }
    }
    
    set_pos(42, 24);
    printf("     Press Any Key To Continue ....   ");
    getch();
    user_transaction();
}
void user_chkblnc(int ver_account)
{
    FILE *f;
    int a;
    set_pos(48, 4);
    printf(" BALANCE INQUIRY ");
    
        f = fopen("data.bin", "rb");
        while (fread(&rec, sizeof(rec), 1, f))
        {
            if (rec.account == ver_account)
            {
                set_pos(42, 15);
                printf("Your Balance is : Rup. %.2lf", rec.blnc);
            }
        }
        fclose(f);
    
    
    set_pos(40, 21);
    printf("Press any key to return back to main menu. ");
    getch();
    user_menu();
}

int check (int*user_id,int*tempID)
{
    
    for(int i=0;i<10;i++)
    {
        if(user_id[i]==tempID[i])
        {
            continue;
        }
        else if(user_id[i]!=tempID[i])
        {
            return 0;
        }
    }
    return 1;
}

