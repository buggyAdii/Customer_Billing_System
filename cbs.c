/**
*  A menu-driven program for customer data management
*  @author: Aditya Prakash, Aftab Mustafa & Kingshuk Nath
*  @language: C
*  This program uses file handling in Binary mode
**/

#include<stdio.h>		//for input output functions like printf, scanf
#include<stdlib.h>
#include<windows.h>
#include<string.h>		//string operations

void input();		//funtion for taking userinputs
void writefile();	//function to store data in a file
void search();		//function to search customer account
void display();		//function to display customer details
void update();		//function to update payment details

/* Structue for payment data */
struct date {
	   int month;
	   int day;
	   int year;
	   };

/* Structure holding details of customer*/
struct account {
	int number;
	char name[100];
	int acc_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float newbal;
	float payment;
	struct date lastpayment;

	}customer;

int tl, sl, ts;			//variables to store pointer locations
int main()
	{
	  int i, n;
	  char ch;
	  fflush(stdin);		//empty the buffer
	  printf("\n\n    CUSTOMER BILLING SYSTEM:");
	  puts("\n-----------------------------\n");
	  printf(" ===============================\n");
	  printf("| 1-> Add Account in List       |\n");
	  printf("| 2-> Search Customer Account   |\n");
	  printf("| 3-> Update Payment Details    |\n");
	  printf("| 4-> Exit                      |");
	  printf("\n ===============================\n");

	  do{
	       printf("\nPlease Provide an Input\n(DONT'T Press Enter Here): ");
	       ch = getche();													//function to take input without pressing enter
	  }while(ch <= '0' || ch > '4');

	  switch(ch){

		case '1':
			printf("\nHow Many Customer Accounts You Wish To Add? ");
			scanf("%d", &n);
			for(i = 0; i < n; i++){
				input();
				writefile();
				}
				main();
			break;

		case '2':
			puts("\n-------------------------");
			printf("\nPlease Choose An Input. ");
			puts("\n------------------------");
			printf("\n1.Enter Customer Number");
			printf("\n2.Enter Customer Name: Case Sensitive\n");
			search();
			main();
			break;

		case '3':
			printf("\nUpdate Bill\n");
			update();
			main();
			break;

		case '4':
			puts("\n\n\tClosing Program:");
			printf("\n\t");
			i=0;
			while(i<8){
				printf("* ");
				usleep(200000);
				i++;
			}
			printf("\n-------------------------------------------\n");
			printf("    A PROJECT By Aditya, Aftab, Kingshuk");
			printf("\n-------------------------------------------\n");
			exit(0);
	  }
 }


   void input()
	{
	  FILE *fp = fopen("cbs.dat", "r+");
	  fseek (fp, 0, SEEK_END);				//move file pointer at the last position of file
	  tl = ftell(fp);						//fetch the location of pointer
	  sl = sizeof(customer);				//fetch the size of structure
	  ts = tl / sl;							//fetch the number of customer currently stored in database
	  fseek(fp, (ts-1)*sl, SEEK_SET);		//sets the pointer to the last entry
	  fread(&customer, sl, 1, fp);			//reads info from the database file

	  printf("\nCustomer no:%d\n", ++customer.number);
	  fclose(fp);
	  printf("Account number: %d", customer.number);
	  customer.acc_no = customer.number;
	  fflush(stdin);						//empty the buffer

	  printf("\n       Name: ");
	  gets(customer.name);
	  printf("\n       Mobile no: ");
	  scanf("%f", &customer.mobile_no);
	  fflush(stdin);
	  printf("         Street: ");
	  gets(customer.street);
	  fflush(stdin);
	  printf("         City: ");
	  gets(customer.city);
	  printf("         Previous Due Balance: ");
	  scanf("%f", &customer.newbal);
	  int key;
	  			payment:{
			    puts("\n1.Purchase?\t2.Due Payment");
			    scanf("%d",&key);
			    if(key == 1){
			    	fflush(stdin);
				printf(" \n        Current Purchase Amount: ");
				scanf("%f", &customer.payment);
					fflush(stdin);
				printf("\n         Purchase date(dd/mm/yyyy): ");
				scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
							customer.newbal = customer.newbal + customer.payment;			//Updates Balance
				}
				else if(key==2){
					fflush(stdin);
					printf("Enter Payment amount:");
					scanf("%f",&customer.payment);
					fflush(stdin);
					printf("\n         Payment date(dd/mm/yyyy): ");
				scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
							customer.newbal = customer.newbal - customer.payment;
				}
				else{
					fflush(stdin);
					puts("Enter valid choice\nTry Again");
					goto payment;
				}
				}
	  return;
   }

   void writefile()
   {
	  int c;
	  FILE *fp;
	  fp = fopen("cbs.dat", "ab");						//opens file in append mode
	  fflush(stdin);									//empty the buffer
	  c = fwrite(&customer, sizeof(customer), 1, fp);	//updates file & checks for returned value
				  			if(c == 1)
				  			puts("\tRecord Update SUCCEESSFULLY");
				  			else
				  			puts("\tRecord Update FAILED");
	  fclose(fp);										//closes the file

	  return;
   }

void search()
   {
	 char ch;
	 char nam[100];
	 int n, i, m = 1;
	 FILE *fp;
	 fp = fopen("cbs.dat", "rb");						//open file in read binary mode

	 do{
		printf("\nEnter your choice: ");
		ch = getche();
	 }while(ch != '1' && ch != '2');

	 switch(ch){

	      case '1':
		    fseek(fp, 0, SEEK_END);					//sets pointer to the end of file
		    tl = ftell(fp);
		    sl = sizeof(customer);
		    ts = tl / sl;
		    do{
			printf("\nChoose Customer Number: ");
			scanf("%d", &n);
			if(n <= 0 || n > ts)
			printf("\nOpps!!! No Result Found\n");
			else{
			    fseek(fp, (n-1)*sl, SEEK_SET);		//sets pointer to the inputted customer account
			    fread(&customer, sl, 1, fp);		//reads the data from file
			    display();
			}
			printf("\n\nDo You Wish To Search Again?(y/n) ");
			ch = getche();
		    }while(ch == 'y');
		    fclose(fp);
		    break;

		  case '2':
		    fseek(fp, 0, SEEK_END);
		    tl = ftell(fp);
		    sl = sizeof(customer);
		    ts = tl / sl;
		    fseek(fp, (ts-1)*sl, SEEK_SET);
		    fread(&customer, sizeof(customer), 1, fp);
		    n = customer.number;
		    do{
			printf("\nEnter the name: ");
			fflush(stdin);
			gets(nam);
			fseek(fp, 0, SEEK_SET);
			for(i = 1; i <= n; i++)
			{
			     fread(&customer, sizeof(customer), 1, fp);
			     if(strcmp(customer.name, nam) == 0)
			     {
				display();
				m = 0;									//m=o, user found m!=0, user not found
				break;
			     }
			}
			if(m != 0)
			printf("\n\nSorry!!! DOESN'T Exist\n");
			printf("\nDo You Wish to search Again?(y/n) ");
			ch = getche();
		    }while(ch == 'y');
		    fclose(fp);
	      }

		  return;
	 }

void update()
{
	char ch;
	int n, c;
	FILE *fp = fopen("cbs.dat", "rb+");				//opens file in read+ binary mode
	  fseek (fp, 0, SEEK_END);						//sets pointer to the end
	  tl = ftell(fp);
	  sl = sizeof(customer);
	  ts = tl / sl;
			do{
			fread(&customer, ts, 1, fp);
			printf("\nEnter customer number: ");
			fflush(stdin);
			scanf("%d", &n);
			if(ts<1){								//condition to check if database have some data
			puts("Database Empty\nAdd Customer First.");
			main();
		}
			if(n <= 0 || n > ts)
			{
				printf("\nEnter correct\n");
				fflush(stdin);
				update();
			}
			else if(ts=0)
			puts("Record is Empty!");
			else{
			    fseek(fp, (n-1)*sl, SEEK_SET);		//sets pointer to the start of desired data
			    fread(&customer, sl, 1, fp);
			    printf("\tName:	%s\n", customer.name);
			    printf("\tPrevious Due Balance: %.2f\n", customer.newbal);
			    fflush(stdin);
			    int key;
			    puts("\n1.Purchase\t2.Due Payment");
			    scanf("%d",&key);
			    if(key == 1){
			    	fflush(stdin);
				printf(" \n        Current Purchase Amount: ");
				scanf("%f", &customer.payment);
					fflush(stdin);
				printf("\n         Purchase date(dd/mm/yyyy): ");
				scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
							customer.newbal = customer.newbal + customer.payment;			//Updates Balance
				}
				else if(key==2){
					fflush(stdin);
					printf("Enter Payment amount:");
					scanf("%f",&customer.payment);
					fflush(stdin);
					printf("\n         Payment date(dd/mm/yyyy): ");
				scanf("%d/%d/%d", &customer.lastpayment.day, &customer.lastpayment.month, &customer.lastpayment.year);
							customer.newbal = customer.newbal - customer.payment;
				}
				else{
					puts("Enter valid choice\nTry Again");
					return update();
				}

							fseek(fp, -sl, 1);
							c = fwrite(&customer, sizeof(customer), 1, fp);
				  			if(c == 1)
				  			puts("\tRecord Updated SUCCEESSFULLY");
				  			else
				  			puts("\tRecord Update FAILED");
				  			fclose(fp);
				  			display();
							main();
						}
						}while(n<=0 || n>ts);
}


   void display()
	 {
	   printf("\n\nCustomer no : %d\n",customer.number);
	   printf("    Name 	   : %s\n",customer.name);
	   printf("    Mobile no      : %.f\n",customer.mobile_no);
	   printf("    Account number : %d\n",customer.acc_no);
	   printf("    Street         : %s\n",customer.street);
	   printf("    City           : %s\n",customer.city);
	   printf("    Last Payment   : %.2f\n",customer.payment);
	   printf("    Due Balance    : %.2f\n",customer.newbal);
	   printf("    Payment date   : %d/%d/%d\n\n",customer.lastpayment.day,customer.lastpayment.month,customer.lastpayment.year);
		}
