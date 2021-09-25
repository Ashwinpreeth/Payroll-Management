#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>   
#define EMP_FILE "empdata.txt"
#define TMP_FILE "tmpdata.txt"
#define EPF_RATE 0.18
#define ETF_RATE 0.03
#define GEN_TIME (8*20)

int main();
void passc(char [30]);

void admin_menu(char [30]);

void add_employee();
void edit_employee();
void delete_employee();
void search_employee();
void add_admin();

void Employee(char [30]);
void show_employee(char [30]);


void Accountant();

void print_report();
void print_slip();


void gotoxy(int x,int y)
{
printf("%c[%d;%df",0x1B,y,x);
}

struct Account
{
	char name[30];
    	char pass[20];
    	char desg[20];
};

int validate_employee(char valid_id[10])
{
	FILE *fp1;
	int a;
	char name[50],address[100],phone[11],id[5],BG[5],Desig[20],mail[30];
	float salary,hours;
	fp1=fopen(EMP_FILE,"r");
	do
	{
		fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);
		if(feof(fp1))
		{
			break;
		}
		if((strcmp(id,valid_id))==0)
		{
			a = 1;
			break;
		}
		else
		{
			a = 2;
		}
	}
	while(!(feof(fp1)));
	fclose(fp1);
	return a;
}

void Login (char name[], char pass[])
{
	int flag=0;
	FILE *sc;
	char auth[20],option;
    	struct Account acc;
       	sc = fopen("Account.txt","r");
	while( !feof(sc) )
	{
		fscanf(sc, "%s %s %s",acc.name, acc.pass, auth);
    		if(strcmp(pass,acc.pass) == 0 && strcmp(name,acc.name) == 0) 
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
		option = auth[0];
		switch(option)
		{
			case 'A':system("clear");printf("You have admin Privileges!");admin_menu(name);break;
			case 'E':system("clear");Employee(name);break;
		}
	}
	else
	{
		system("clear");
		gotoxy(20,17);
		printf("Name or Password is incorrect\n");
	}
    	fclose(sc);
}

void reg()
{
	char *pass;
	system("clear");
        char name[30];
        FILE *sc;

        sc=fopen("Account.txt","a+");
        if(sc==NULL)
        {
        	gotoxy(20,10);
                fputs("Error at opening File!\n",stderr);
                exit(1);
        }

        struct Account acc;
        gotoxy(20,10);
        printf("Welcome for registration");
        gotoxy(25,12);
        printf("Enter Your mail ID : ");
        scanf("%s",acc.name);
        gotoxy(25,13);
        printf("Enter a Password : ");
        pass = getpass("");
        strcpy(acc.pass,pass);
        strcpy(acc.desg,"Employee");
        fprintf(sc, "%s %s %s\n",acc.name,acc.pass,acc.desg);
        system("clear");
        gotoxy(20,8);
        printf("Registrartion successful!!");
        fclose(sc);
}

void add_employee(void)

{
	char t,e;
        char name[50],address[100],phone[11],id[10],BG[5],Desig[20],mail[50];
        float salary,hours;
        FILE *fp;
        fp = fopen(EMP_FILE, "a+");
        do
       	{
               fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);
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
      	scanf("%[^\n]",name);
	gotoxy(20,11);

	printf("ID\t\t\t: ");
      	fflush(stdin);
      	scanf("%s",id);
      	gotoxy(20,12);
      	int Avail=validate_employee(id);
      	if(Avail == 2)
      	{
	      	printf("Mail ID\t\t: ");
	      	fflush(stdin);
	      	scanf("%s",mail);
	      	gotoxy(20,13);
	      	
	      	printf("Address\t\t: ");
	      	scanf("%c",&e);
	      	scanf("%[^\n]",address);
		gotoxy(20,14);

	      	printf("Phone\t\t: ");
		fflush(stdin);
	     	scanf("%s",&phone);
		gotoxy(20,15);

	      	printf("Blood_Group\t\t: ");
	      	fflush(stdin);
	      	scanf("%s",BG);
	      	gotoxy(20,16);
	      	
	      	printf("Designation\t\t: ");
	      	fflush(stdin);
	      	scanf("%s",Desig);
	      	gotoxy(20,17);

		printf("Salary\t\t: ");
	      	fflush(stdin);
	      	scanf("%f", &salary);
	      	gotoxy(20,18);
		
		printf("Hours\t\t: ");
	      	fflush(stdin);
	      	scanf("%f", &hours);
	      	fprintf(fp, "%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", name, id, mail, address, phone, BG, Desig, salary, hours);

	      	fflush(fp);
	      	fclose(fp);
	      	system("clear");
		gotoxy(20,10);
	      	printf("Employee details added\n");
	}
	else
	{
		system("clear");
		gotoxy(25,15);
		printf("Employee already Exists!");
	}
}


void edit_employee(void)

{
        char name[50],address[100],phone[11],id[5],idEdit[10],BG[5],Desig[20],mail[50];
        float salary,hours;
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
		       fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);

		        if(feof(fp1))
		        {
		                break;

		        }

		 	if((strcmp(id, idEdit)) == 0)
		 	{
				 gotoxy(25,12);
				 printf("Editing Employee %s",id);
				 gotoxy(25,14);
				 printf("Enter new basic salary : ");
				 fflush(stdin);
				 scanf("%f", &salary);
				 gotoxy(25,15);
				 printf("Enter the new number of hours worked : ");
				 fflush(stdin);
				 scanf("%f", &hours);
			}

	      		fprintf(fp2, "%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", name, id, mail, address, phone, BG, Desig, salary, hours);

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
	}
}


void delete_employee(void)

{
        char name[50],address[100],phone[11],id[5],idDel[10],BG[5],Desig[20],mail[50];
        float salary,hours;

        FILE *fp1;

        FILE *fp2;

        fp1 = fopen(EMP_FILE, "r");
        fp2 = fopen(TMP_FILE, "w");
        system("clear");
	gotoxy(20,10);
        printf("Enter Employee ID to Delete : ");
        fflush(stdin);
        scanf("%s",&idDel);
        int Avail = validate_employee(idDel);
        if(Avail==1)
        {
		do
		{

		   fscanf(fp1, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);

		   if(feof(fp1))
		   {
		           break;

		   }

		   if((strcmp(id, idDel)) != 0)

		   {

	      			fprintf(fp2, "%s/%s/%s/%s/%s/%s/%s/%.2f %.2f\n", name, id, mail, address, phone, BG, Desig, salary, hours);

		   }

		    }while(!(feof(fp1)));
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
	}
	
}


void search_employee(void)

{
        char name[50],address[100],phone[11],id[5],idSearch[10],BG[5],Desig[20],mail[50];
        float salary,hours;



        FILE *fp;

        fp = fopen(EMP_FILE, "r");
        system("clear");
	gotoxy(20,10);
        printf("Enter the Employee ID to Search : ");
        fflush(stdin);
        scanf("%s",&idSearch);
        int Avail = validate_employee(idSearch);
        if(Avail==1)
        {
		do
		{

		   fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);

		   if(feof(fp))
		   {
		           break;
		   }

		   if((strcmp(id, idSearch)) == 0)
		   {

		         system("clear");
			 gotoxy(25,13);
		         printf("Name        : %s", name);
			 gotoxy(25,14);
			 printf("ID          : %s", id);
		         gotoxy(25,15);
		         printf("Mail ID     : %s", mail);
		         gotoxy(25,16);
		         printf("Address     : %s", address);
			 gotoxy(25,17);
		         printf("Phone       : %s", phone);
			 gotoxy(25,18);
		         printf("Blood_Group : %s", BG);
		         gotoxy(25,19);
		         printf("Designation : %s", Desig);
			 gotoxy(25,20);
		         printf("Salary      : %.2f", salary);
			 gotoxy(25,21);
		         printf("Hours       : %.2f", hours);
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

void show_employee(char Name[30])
{
	char name[50],address[100],phone[11],id[5],idSearch[5],BG[5],Desig[20],mail[50];
        float salary,hours;
        FILE *fp;

        fp = fopen(EMP_FILE, "r");
        fflush(stdin);
        do
        {

           fscanf(fp, "%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c%[^/]%*c %f %f%*c", name, id, mail, address, phone, BG, Desig, &salary, &hours);

           if(feof(fp))
           {
                   break;
           }
           gotoxy(30,20);
           //printf("%s.%s.",mail,Name);
           if((strcmp(mail, Name)) == 0)
           {

                 system("clear");
		 gotoxy(25,13);
                 printf("Name        : %s", name);
		 gotoxy(25,14);
		 printf("ID          : %s", id);
                 gotoxy(25,15);
                 printf("Mail ID     : %s", mail);
                 gotoxy(25,16);
                 printf("Address     : %s", address);
		 gotoxy(25,17);
                 printf("Phone       : %s", phone);
		 gotoxy(25,18);
                 printf("Blood_Group : %s", BG);
                 gotoxy(25,19);
                 printf("Designation : %s", Desig);
		 gotoxy(25,20);
                 printf("Salary      : %.2f", salary);
		 gotoxy(25,21);
                 printf("Hours       : %.2f", hours);
           }
          }
          while(!(feof(fp)));
          fclose(fp);
}

void passc(char Name[30])
{	
	struct Account acc;
	char *pass1;
	char *pass2;
	struct Account acc1,acc2;
	FILE *fp1;
	FILE *fp2;
	fp1=fopen("Account.txt","r+");
	fp2=fopen("Temp.txt","w+");

	do
	{
		fscanf(fp1, "%s %s %s",acc.name, acc.pass, acc.desg);
		if(feof(fp1))
                {
                        break;
                }
		if((strcmp(Name, acc.name)) == 0)
         	{
		  change:gotoxy(25,12);
			 printf("Changing Password for %s",Name);
			 gotoxy(25,14);
		         printf("Enter new password : ");
			 pass1 = getpass("");
			 strcpy(acc1.pass, pass1);
			 gotoxy(25,15);
                         printf("Confirm Password   : ");
                         fflush(stdin);
                         pass1 = getpass("");
                         strcpy(acc2.pass,pass1);
        		 if(strcmp(acc2.pass,acc1.pass)==0)
        		 {
        		 	strcpy(acc.pass,acc1.pass);
			 }
			 else
			 {
				gotoxy(20,17);
				printf("Password does not match");
				goto change;
			 }
		}
			fprintf(fp2,"%s %s %s\n",acc.name,acc.pass,acc.desg);
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

void admin_menu(char Name[30])
{
        int choice, ch;
	char option;
        do
	{
		//gotoxy(20,14);
		//printf("You have admin Privileges !");
		gotoxy(25,16);
        	printf("1.Add Employee");
		gotoxy(25,17);
		printf("2.Delete Employee");
		gotoxy(25,18);
		printf("3.Modify Employee Details");
		gotoxy(25,19);
		printf("4.Search an Employee");
		gotoxy(25,20);
		printf("5.View my details");
		gotoxy(25,21);
		printf("6.Change Password");
		gotoxy(25,22);
		printf("7.Add Admin");
		gotoxy(25,23);
		printf("8.Go to Login page");
		gotoxy(25,25);
        	printf("Enter your choice : ");
        	scanf("%d",&choice);
        	switch(choice)
        	{
                	case 1: add_employee();
                	        break;
                	case 2: delete_employee();
                	        break;
                	case 3: edit_employee();
                	        break;
                	case 4: search_employee();
                	        break;
                	case 5: gotoxy(20,10); printf("Your Deatils"); gotoxy(20,11); printf("============");
        			show_employee(Name);
        			gotoxy(20,23);
        			printf("Press 0 to go back to previous menu : ");
        			scanf("%d",&ch);
        			if(ch==0)
        				system("clear");
        				admin_menu(Name);
        			break;
			case 6: system("clear");
				passc(Name);
				break;
			case 7: system("clear");
				add_admin();
				break;
               	 	case 8: system("clear");
                        	main();
				break;
			gotoxy(20,24);
			default: printf("Wrong option!!");
        	}
		gotoxy(20,25);
        	printf("Press 0 to go back / 1 to Logout : ");
        	scanf("%s",&option);
		system("clear");
        }
	while(option!=0);
	system("clear");
}

void add_admin()
{
        char name[50],pass[20],desig[20],mail[30],Name[30];
        int choice;
        FILE *fp1;
        FILE *fp2;

        fp1 = fopen("Account.txt", "r+");
        fp2 = fopen("Temp.txt", "w+");
        system("clear");
	gotoxy(20,10);
        printf("Enter Email_ID of new admin : ");
        scanf("%s",mail);
        do
        {
                fscanf(fp1, "%s %s %s", name, pass, desig);
                if(feof(fp1))
                {
                        break;
                }

         	if((strcmp(name, mail)) == 0)
         	{
         		 strcpy(desig,"Admin");
         		 strcpy(Name,name);
        	}

      		fprintf(fp2, "%s %s %s\n", name, pass, desig);
        }
        while(!(feof(fp1)));
        fflush(fp2);

        fclose(fp1);
        fclose(fp2);
        remove("Account.txt");
        rename("Temp.txt", "Account.txt");
        system("clear");
	gotoxy(20,10);
	printf("%s is now an admin",Name);
        fflush(stdin);
}

void Employee(char Name[30])
{
        int choice, ch=1;
	gotoxy(20,15);
        printf("Welocome %s!",Name);
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
        	case 1: gotoxy(20,10); printf("Your Deatils"); gotoxy(20,11); printf("============");
        		show_employee(Name);
        		gotoxy(20,23);
        		printf("Press 0 to go back to previous menu : ");
        		scanf("%d",&ch);
        		if(ch==0)
        			system("clear");
        			Employee(Name);
        		break;
        	case 2: gotoxy(20, 10); printf("Not Completed");
        		break;
        	case 3: system("clear");
			passc(Name);
			break;
        	case 4: main();break;
        	default : gotoxy(20,24); printf("Invalid Choice");
        }
}

int main () 
{
	char *password;
	system("clear");
	struct Account log;
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
			case 1 :
				system("clear");
				gotoxy(20,10);
				printf("Enter your Mail_ID\t : ");
				scanf("%s",log.name);
				gotoxy(20,11);
				printf("Enter your Password\t: ");
				password = getpass("");
				strcpy(log.pass, password);
				Login(log.name,log.pass);
				gotoxy(20,10);
				break;
			case 2 :
				reg();
				break;
			case 3 :
				system("clear");
				printf("Thank You!\n");
				exit(0);
			default :
				gotoxy(20,17); printf("Invalid choice!");
				break;
		}
	}
	while(choice!=3);
	return 0;
}
