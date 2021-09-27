#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<regex.h>
#define EMP_FILE "empdata.txt"
#define TMP_FILE "tmpdata.txt"

struct Login
{
        char name[30];
        char pass[20];
        char desg[20];
	char id[10];
};

struct Account
{
	char name[30];
	char address[100];
	char phone[11];
	char id[10];
	char bg[10];
	char desig[10];
	char mail[30];
	char dob[10];
	float salary;
	float hours;
};

typedef struct Login log;
typedef struct Account acc;


int main();
void passc(char [10]);

void admin_menu(char [10]);

void add_employee();
void edit_employee();
void delete_employee();
void search_employee();
void add_admin();

void Employee(char [10]);
void show_employee(char [10]);
int validate_employee(char [5]);

void Accountant();

void print_report();
void print_slip();



void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}


void Login (char name[], char pass[])
{
        int flag=0;
        FILE *fp;
        log l;
        fp = fopen("Account.txt","r");
        while( !feof(fp) )
        {
                fscanf(fp, "%s %s %s %s",l.name, l.pass, l.desg, l.id);
                if(strcmp(pass,l.pass) == 0 && strcmp(name,l.name) == 0)
                {
                        flag = 1;
                        break;
                }
        }
        if(flag==1)
        {
                gotoxy(20,13);
                printf("Logged in as %s",name);
                gotoxy(20,14);
                char option = l.desg[0];
                switch(option)
                {
                        case 'A':system("clear");
				 printf("You have admin Privileges!");
				 admin_menu(l.id);
				 break;
                        case 'E':system("clear");
				 gotoxy(25,15);
				 printf("Welcome!!");
				 Employee(l.id);
				 break;
                }
        }
        else
        {
                system("clear");
                gotoxy(20,17);
                printf("Name or Password is incorrect\n");
        }
        fclose(fp);
}

void reg()
{
        log l,l1,l2;
	char *pass1;
	char *pass2;
        system("clear");
        FILE *fp;
        fp=fopen("Account.txt","a+");
        if(fp==NULL)
        {
                gotoxy(20,10);
                fputs("Error at opening File!\n",stderr);
                exit(1);
        }
	gotoxy(20,10);
        printf("Welcome for registration");
        gotoxy(25,12);
	printf("Enter Your ID      :");
	scanf("%s",l.id);
	gotoxy(25,13);	
        printf("Enter Your mail ID : ");
        scanf("%s",l.name);
	change:gotoxy(25,14);
	       printf("Enter a password   : ");
	       pass1 = getpass("");
       	       strcpy(l1.pass, pass1);
       	       gotoxy(20,17);
	       printf("                                 ");
       	       gotoxy(25,15);
	       printf("Confirm Password   : ");
   	       pass1 = getpass("");
	       strcpy(l2.pass,pass1);
	       if(strcmp(l2.pass,l1.pass)==0)
	       {
		       strcpy(l.pass,l1.pass);
	       }
	       else
	       {
		       gotoxy(20,17);
		       printf("Password does not match");
		       goto change;
	       }
        strcpy(l.desg,"Employee");
        fprintf(fp, "%s %s %s %s\n",l.name,l.pass,l.desg,l.id);
        system("clear");
        gotoxy(20,8);
        printf("Registrartion successful!!");
        fclose(fp);
}

int validate_employee(char valid_id[10])
{
	acc a;
        FILE *fp;
        int r=2;
        fp=fopen(EMP_FILE,"r");
        do
        {
                fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);
                if(feof(fp))
                {
                        break;
                }
                if(strcmp(a.id,valid_id) == 0)
                {
                        r = 1;
                        break;
                }
                else
                {
                        r = 2;
                }
        }
        while(!(feof(fp)));
        fclose(fp);
        return r;
}

void add_employee()
{
	acc a;
        char t,e;
	FILE *fp;
        fp = fopen(EMP_FILE, "a+");
	do
        {
		fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);

 		if(feof(fp))
               	{
                	break;
               	}
	}
        while(!(feof(fp)));
        system("clear");
        gotoxy(20,10);

        printf("Name\t\t\t: ");
        scanf("%c",&t);
        scanf("%[^\n]",a.name);
        gotoxy(20,11);

        printf("ID\t\t\t: ");
        scanf("%s",a.id);
        gotoxy(20,12);
	int Avail=validate_employee(a.id);
        if(Avail == 2)
	{
        	printf("Mail ID\t\t: ");
        	scanf("%s",a.mail);
        	gotoxy(20,13);

       	 	printf("Address\t\t: ");
        	scanf("%c",&e);
        	scanf("%[^\n]",a.address);
Again:		gotoxy(20,14);
		printf("                                       ");
		gotoxy(20,14);
        	printf("Phone\t\t: ");
        	scanf("%s",a.phone);
		gotoxy(18,8);
		printf("                             ");
		if(strlen(a.phone) == 10)
		{
			goto Next;
		}
		else
		{
			gotoxy(18,8);
			printf("Invalid Phone Number");
			goto Again;
		}
Next:		gotoxy(20,15);

		printf("Blood_Group\t\t: ");
        	scanf("%s",a.bg);
        	gotoxy(20,16);

		printf("DOB[DD-MM-YYYY]\t: ");
        	scanf("%s",a.dob);
        	gotoxy(20,17);
	
        	printf("Department\t\t: ");
        	scanf("%s",a.desig);
        	gotoxy(20,18);

        	printf("Salary\t\t: ");
        	scanf("%f", &a.salary);
        	gotoxy(20,19);

        	printf("Hours\t\t: ");
        	scanf("%f", &a.hours);
        	fprintf(fp, "%s/%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, a.salary, a.hours);

        	fclose(fp);
        	system("clear");
        	gotoxy(20,10);
        	printf("Employee details added\n");
	}
	else
	{
		system("clear");
		gotoxy(25,15);
		printf("Emplyee Already Exists!");
	}
}

void edit_employee()
{
	char idEdit[5];
	acc a;
        int choice;
        FILE *fp1;
        FILE *fp2;
        fp1 = fopen(EMP_FILE, "r+");
        fp2 = fopen(TMP_FILE, "w+");
        system("clear");
        gotoxy(20,10);
        printf("Enter Employee ID to Edit : ");
        fflush(stdin);
        scanf("%s",idEdit);
        int Avail = validate_employee(idEdit);
        if(Avail==1)
        {
                do
                {
                       	fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);
                        if(feof(fp1))
                        {
                                break;
                        }
                        if(strcmp(a.id, idEdit) == 0)
                        {
                                 gotoxy(25,12);
                                 printf("Editing Employee %s",a.id);
                                 gotoxy(25,14);
                                 printf("Enter new basic salary : ");
                                 fflush(stdin);
                                 scanf("%f", &a.salary);
                                 gotoxy(25,15);
                                 printf("Enter the new number of hours worked : ");
                                 fflush(stdin);
                                 scanf("%f", &a.hours);
                        }
			fprintf(fp2, "%s/%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, a.salary, a.hours);
                }
                while(!(feof(fp1)));
                fflush(fp2);
                fclose(fp1);
                fclose(fp2);
                remove(EMP_FILE);
                rename(TMP_FILE, EMP_FILE);
                system("clear");
                gotoxy(20,10);
                printf("Editing completed");
                fflush(stdin);
        }
        else if(Avail==2)
        {
                gotoxy(25,15);
                printf("Employee not found");
                fclose(fp1);
                fclose(fp2);
                remove(TMP_FILE);
        }
}

void delete_employee()
{
	acc a;
	char idDel[5];
        FILE *fp1;
        FILE *fp2;
        fp1 = fopen(EMP_FILE, "r");
        fp2 = fopen(TMP_FILE, "w");
        system("clear");
        gotoxy(20,10);
        printf("Enter Employee ID to Delete : ");
        fflush(stdin);
        scanf("%s",idDel);
        int Avail = validate_employee(idDel);
	if(Avail==1)
        {
                do
                {

                   fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);
                   if(feof(fp1))
                   {
                           break;
                   }
                   if(strcmp(a.id, idDel) != 0)
                   {
			   fprintf(fp2, "%s/%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, a.salary, a.hours);
                   }
		}
		while(!(feof(fp1)));
		fflush(fp2);
		fclose(fp1);
		fclose(fp2);
                remove(EMP_FILE);
                rename(TMP_FILE, EMP_FILE);
                gotoxy(25,12);
                printf("Employee-%s Details deleted",idDel);
                fflush(stdin);
        }
        else if(Avail==2)
        {
                gotoxy(25,15);
                printf("Employee not found");
                fclose(fp1);
                fclose(fp2);
                remove(TMP_FILE);
        }

}

void search_employee(char idShow[10])
{
	acc a;
        FILE *fp;
        fp = fopen(EMP_FILE, "r");
        system("clear");
        int Avail = validate_employee(idShow);
        if(Avail==1)
        {
                do
                {
			fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);
                   	if(feof(fp))
                   	{
			   	break;
                   	}
                   	if((strcmp(a.id, idShow)) == 0)
                   	{
			   	system("clear");
			   	gotoxy(25,13);
			   	printf("Name        : %s", a.name);
			   	gotoxy(25,14);
			   	printf("ID          : %s", a.id);
			   	gotoxy(25,15);
			   	printf("Mail ID     : %s", a.mail);
			   	gotoxy(25,16);
			   	printf("Address     : %s", a.address);
			   	gotoxy(25,17);
			   	printf("Phone       : %s", a.phone);
			   	gotoxy(25,18);
			   	printf("Blood_Group : %s", a.bg);
			   	gotoxy(25,19);
			   	printf("DOB         : %s", a.dob);
			   	gotoxy(25,20);
			   	printf("Designation : %s", a.desig);      
			   	gotoxy(25,21);
			   	printf("Salary      : %.2f", a.salary);
			   	gotoxy(25,22);
			   	printf("Hours       : %.2f", a.hours);
		   	}
		}
		while(!(feof(fp)));
		fclose(fp);
        }
        else if(Avail==2)
        {
                gotoxy(25,15);
                printf("Employee not found");
        }
}

void show_all()
{
	acc a;
        system("clear");
        int i=10,j=10,n=0;
        FILE *fp;
        fp = fopen(EMP_FILE, "r");
        fflush(stdin);
        do
        {
           	fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", a.name, a.id, a.mail, a.address, a.phone, a.bg, a.dob, a.desig, &a.salary, &a.hours);
           	if(feof(fp))
           	{
                   	break;
           	}
                gotoxy(j,i);i++;
                printf("======================================");
                gotoxy(j,i);i++;
                printf("Name        : %s", a.name);
                gotoxy(j,i);i++;
                printf("ID          : %s", a.id);
                gotoxy(j,i);i++;
                printf("Mail ID     : %s", a.mail);
                gotoxy(j,i);i++;
                printf("Address     : %s", a.address);
                gotoxy(j,i);i++;
                printf("Phone       : %s", a.phone);
                gotoxy(j,i);i++;
                printf("Blood_Group : %s", a.bg);
                gotoxy(j,i);i++;
                printf("DOB         : %s", a.dob);
                gotoxy(j,i);i++;
                printf("Designation : %s", a.desig);
                gotoxy(j,i);i++;
                printf("Salary      : %.2f", a.salary);
                gotoxy(j,i);i++;
		printf("Hours       : %.2f", a.hours);
                gotoxy(j,i);i++;
                printf("======================================");
                i+=1;
                n++;
                if(n==3)
                {
			j+=45;
			i=10;
			n=0;
                }
	}
        while(!(feof(fp)));
        fclose(fp);
}

void passc(char id[10])
{
        log l,l1,l2;
        char *pass1;
        FILE *fp1;
        FILE *fp2;
        fp1=fopen("Account.txt","r+");
        fp2=fopen("Temp.txt","w+");
        do
        {
                fscanf(fp1, "%s %s %s %s",l.name, l.pass, l.desg, l.id);
                if(feof(fp1))
                {
                        break;
                }
                if((strcmp(id, l.id)) == 0)
                {
                  change:gotoxy(25,12);
                         printf("Changing Password for %s",l.name);
                         gotoxy(25,14);
                         printf("Enter new password : ");
                         pass1 = getpass("");
                         strcpy(l1.pass, pass1);
			 gotoxy(20,17);
			 printf("                                 ");
                         gotoxy(25,15);
                         printf("Confirm Password   : ");
                         fflush(stdin);
                         pass1 = getpass("");
                         strcpy(l2.pass,pass1);
                         if(strcmp(l2.pass,l1.pass)==0)
                         {
                                strcpy(l.pass,l1.pass);
                         }
                         else
                         {
                                gotoxy(20,17);
                                printf("Password does not match");
                                goto change;
                         }
                }
		fprintf(fp2,"%s %s %s %s\n",l.name,l.pass,l.desg,l.id);
        }
        while(!(feof(fp1)));
        fflush(fp2);
        fclose(fp1);
        fclose(fp2);
        remove("Account.txt");
        rename("Temp.txt", "Account.txt");
        system("clear");
        gotoxy(20,10);
        printf("Password Changed");
        fflush(stdin);
}

void admin_menu(char id[10])
{
        int choice, ch;
	char idSearch[10];
        do
        {
                gotoxy(25,16);
                printf("1-> View my details");
                gotoxy(25,17);
                printf("2-> Add Employee");
                gotoxy(25,18);
                printf("3-> Delete Employee");
                gotoxy(25,19);
                printf("4-> Show all Employees");
                gotoxy(25,20);
                printf("5-> Search an Employee");
                gotoxy(25,21);
                printf("6-> Modify Employee Details");
                gotoxy(25,22);
                printf("7-> Add Admin");
                gotoxy(25,23);
                printf("8-> Change Password");
                gotoxy(25,24);
                printf("9-> Go to Login page");
                gotoxy(25,26);
                printf("Enter your choice : ");
                scanf("%d",&choice);
                switch(choice)
                {
                        case 2: add_employee();
                                break;
                        case 3: delete_employee();
                                break;
                        case 6: edit_employee();
                                break;
                        case 5: system("clear");
				gotoxy(20,10);
				printf("Enter Employee ID to search : ");
				scanf("%s",idSearch);
				search_employee(idSearch);
                                break;
                        case 1: gotoxy(20,10);
				printf("Your Deatils");
				gotoxy(20,11); printf("============");
                                search_employee(id);
                                gotoxy(20,24);
                                printf("Press 0 to go back to previous menu : ");
                                scanf("%d",&ch);
				if(ch==0)
                                        system("clear");
                                        admin_menu(id);
                                break;
                        case 8: system("clear");
                                passc(id);
                                break;
                        case 7: system("clear");
                                add_admin();
                                break;
                        case 9: system("clear");
                                main();
                                break;
                        case 4: show_all();
                                gotoxy(18,8);
                                printf("Press 0 to go back to previous menu : ");
                                scanf("%d",&ch);
                                if(ch==0)
                                        system("clear");
                                        admin_menu(id);
                                break;
                        gotoxy(20,24);
                        default: printf("Wrong option!!");
                }
                gotoxy(20,25);
                printf("Press 0 to go back to previous menu  : ");
                scanf("%d",&ch);
                system("clear");
        }
        while(ch!=0);
        admin_menu(id);
        system("clear");
}

void add_admin()
{
	log l;
	acc a;
        int choice;
        FILE *fp1;
        FILE *fp2;
        fp1 = fopen("Account.txt", "r+");
        fp2 = fopen("Temp.txt", "w+");
        system("clear");
        gotoxy(20,10);
        printf("Enter Email_ID of new admin : ");
        scanf("%s",a.mail);
        do
        {
                fscanf(fp1, "%s %s %s %s", l.name, l.pass, l.desg, l.id);
                if(feof(fp1))
                {
                        break;
                }
                if(strcmp(l.name, a.mail) == 0)
                {
                         strcpy(l.desg,"Admin");
                }
                fprintf(fp2, "%s %s %s %s\n", l.name, l.pass, l.desg, l.id);
        }
        while(!(feof(fp1)));
        fflush(fp2);
        fclose(fp1);
        fclose(fp2);
        remove("Account.txt");
        rename("Temp.txt", "Account.txt");
        system("clear");
        gotoxy(20,10);
        printf("%s is now an admin",a.mail);
        fflush(stdin);
}

void Employee(char id[10])
{
        int choice, ch=1;
        gotoxy(25,17);
        printf("1.View Details");
        gotoxy(25,18);
        printf("2.View Payslip");
        gotoxy(25,19);
        printf("3.Change Password");
        gotoxy(25,20);
        printf("4.Go to Login page");
        gotoxy(20,22);
        printf("Enter your choice[1-4] : ");
        scanf("%d",&choice);
        system("clear");
        switch(choice)
        {
                case 1: gotoxy(20,10); 
			printf("Your Deatils"); 
			gotoxy(20,11); printf("============");
                        search_employee(id);
                        gotoxy(20,24);
                        printf("Press 0 to go back to previous menu : ");
                        scanf("%d",&ch);
                        if(ch==0)
                                system("clear");
                                Employee(id);
                        break;
                case 2: gotoxy(20, 10); printf("Not Completed");
                        break;
                case 3: system("clear");
                        passc(id);
                        Employee(id);
                        break;
                case 4: main();break;
                default : gotoxy(20,24); 
			  printf("Invalid Choice");
        }
}

int main ()
{
        log l;
	char *pass;
        system("clear");
        int choice;
        do
        {
                gotoxy(18, 8);
                printf("WELCOME TO PAYROLL MANAGEMENT SYSTEM");
                gotoxy(18, 9);
                printf("====================================");
                gotoxy(20,11);
                printf("-> 1 For Login");
                gotoxy(20,12);
                printf("-> 2 For Register");
                gotoxy(20,13);
                printf("-> 3 For Exit");
                gotoxy(20,15);
                printf("Enter Your choice : ");
                scanf("%d",&choice);
                fflush(stdin);
                switch(choice)
                {
                        case 1 :  system("clear");
                                  gotoxy(20,10);
                                  printf("Enter your Mail_ID\t : ");
                                  scanf("%s",l.name);
                                  gotoxy(20,11);
                                  printf("Enter your Password\t: ");
                                  pass = getpass("");
				  strcpy(l.pass,pass);
                                  Login(l.name,l.pass);
                                  gotoxy(20,10);
                                  break;
                        case 2 :  reg();
                                  break;
                        case 3 :  system("clear");
                                  printf("Thank You!\n");
                                  exit(0);
                        default : gotoxy(20,17); 
				  printf("Invalid choice!");
                                  break;
                }
        }
        while(choice!=3);
        return 0;
}

