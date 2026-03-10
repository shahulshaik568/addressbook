#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    if (sortCriteria == 1) // Sort by name
    {
        //Bubble sort logic
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name) >0 )// Comparing two names
                {
                     addressBook->temp[0] = addressBook->contacts[j];
                     addressBook->contacts[j] = addressBook->contacts[j+1];
                     addressBook->contacts[j+1] = addressBook->temp[0];
                }
            }
        }
        printf("   Name                 phone                 email \n");
        printf("---------------------------------------------------------------\n");
        printf("\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%-20s %10s        %-s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("\n \n");
        }
        printf("---------------------------------------------------------------\n");
    }

    if(sortCriteria == 2) // Sort by phone
    {
        //Bubble sort logic
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone) >0 )// Comparing two phone numbers
                {
                     addressBook->temp[0] = addressBook->contacts[j];
                     addressBook->contacts[j] = addressBook->contacts[j+1];
                     addressBook->contacts[j+1] = addressBook->temp[0];
                }
            }
        }
        printf("   Name                 phone                 email \n");
        printf("---------------------------------------------------------------\n");
        printf("\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%-20s %10s        %-s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("\n \n");
        }
        printf("---------------------------------------------------------------\n");
    }

    if(sortCriteria == 3) // Sort by email
    {
        //Bubble sort logic
        for(int i=0;i<addressBook->contactCount-1;i++)
        {
            for(int j=0;j<addressBook->contactCount-i-1;j++)
            {
                if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email) >0 )// Comparing two emails
                {
                     addressBook->temp[0] = addressBook->contacts[j];
                     addressBook->contacts[j] = addressBook->contacts[j+1];
                     addressBook->contacts[j+1] = addressBook->temp[0];

                }
            }
        }
        printf("   Name                 phone                 email \n");
        printf("---------------------------------------------------------------\n");
        printf("\n");
        for(int i=0;i<addressBook->contactCount;i++)
        {
            printf("%-20s %10s        %-s",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            printf("\n \n");
        }
        printf("---------------------------------------------------------------\n");
    }
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    Contact *ss=&addressBook->contacts[addressBook->contactCount];
	/* Define the logic to create a Contacts */
    validate_name(ss->name);//validating for name
    
    validate_phone(addressBook,ss->phone);//validating for phone
    
    validate_email(addressBook,ss->email);//validating for email
    addressBook->contactCount++;
}

void validate_name(char* ss)
{
    int digit;
    do
    {
        digit=0;
        printf("Name\n");
        scanf("%s",ss);
        printf("%s",ss);
        for(int i=0;ss[i]!='\0';i++)
        {
            if(!isalpha(ss[i]))//checking of digit
            {
                digit=1;//digit found
                break;
            }
        }
        if(digit)//digit found invalid
        {
            printf("\ninvalid\n");
        }
    }while(digit);//digit not found it is valid
    printf("\nValid name\n");
}
void validate_phone(AddressBook* addressBook, char* ph)
{
    int num,len,flag;
    do
    {   flag=0;
        num=0;
        printf("Phone\n");
        scanf("%s",ph);
        len=strlen(ph);
        if(len!=10)//length of phone digit is not equal to 10
        {
            printf("\nInvalid\n");
        }
        if(len==10)// it is equal to len 
        {
            for(int i=0;ph[i]!='\0';i++)
            {
                if(isdigit(ph[i]))//checking of digit
                {
                    num++;
                }
            }
        }
        if(num!=10)
        {
            printf("\nInvalid phoneNumber\n");
        }
        //phone number should be unique.
        for(int j=0;j<addressBook->contactCount;j++)
        {
            if(strcmp(addressBook->contacts[j].phone,ph)==0)
            {
                flag=1;
            }
        }
        if(flag)
        {
            printf("duplicate phone numbers!contact already exits.\n");
        }
        
        
    } while (len!=10 || num!=10||flag);
    printf("\nValid coontact\n");
    
}

void validate_email(AddressBook* addressBook, char* em)
{
    
    int str,atr,atr1,len,com,gap,unique;
    do
    {   
        str=0,atr=0,atr1=0,len,com=0,gap=0,unique=0;
        printf("Email\n");
        scanf("%s",em);
        len=strlen(em);
        for(int i=0;em[i]!='\0';i++)
        {
            if(isupper(em[i]))//cheacking for uppercase
            {
                str=1;
            }
            if('@'==em[i])//atr multiple times
            {
                atr++;
            }
            if('@'==em[0])//atr not start at starting point
            {
                atr1=1;
            }
            if(strcmp(&em[len-4],".com")!=0)//email end with .com
            {
                com=1;
            } 
            //atleast one character between '@' and '.com'.
            char* atr2=strchr(em,'@');
            char* dot=strstr(em,".com");
                if(!atr2||!dot||atr2>=dot-1)
                    {
                        gap=1;
                    }
            //email should be unique.
            for(int j=0;j<addressBook->contactCount;j++)
            {
                if(strcmp(addressBook->contacts[j].email,em)==0)
                {
                     unique=1;
                }

            }
        }
        
       
        if(str)
        {
            printf("\nInvalid:uppercase\n");
        }
        if(atr!=1)
        {
            printf("\nInvalid: multiple times\n");
        }
        if(atr1)
        {
            printf("\nInvalid: @ not at starting\n");
        }
        if(com)
        {
            ("\nInvalid: not ending with .com\n");
        }
        if(gap)
        {
            printf("Given atleast one character between '@' and '.com'\n");
        }
        if(unique)
        {
            printf("Duplicate email id! conatct already exits\n");
        }

        /* code */
    } while (str||atr!=1||atr1||com||gap||unique);
    printf("\nValid email\n");
    
}    /* code */

void searchContact(AddressBook *addressBook)
{
    int search;
    int found;
    char name[30];
    char phone[30];
    char email[30];
    do
    {   found=0;
        printf("\nSearch Contacts\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.email\n");
        printf("4.exit\n");
        printf("Enter the choice\n");
        scanf("%d",&search);
        //__fpurge(stdin);// to remove stdin buffer
        switch(search)
        {
            case 1://name
            printf("Enter the name:\n");
            scanf("%s",name);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasecmp(addressBook->contacts[i].name,name)==0)
                {
                    searchfind(addressBook,i);
                    found++;
                }
            }
            if(!found)
            printf("No Contacts Found\n");
            break;

            case 2://phone
            printf("Enter the phone:\n");
            scanf("%[^\n]",phone);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].phone,phone)==0)
                {
                    searchfind(addressBook,i);
                    found++;
                }
            }
            if(!found)
            printf("No Contacts Found\n");
            break;

            case 3://email
            printf("Enter the email:\n");
            scanf("%[^\n]",email);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(addressBook->contacts[i].email,email)==0)
                {
                    searchfind(addressBook,i);
                    found++;
                }
            }
            if(!found)
            printf("No Contacts Found\n");
            break;

            case 4:
            break;
            default:
            printf("Invalid search.try again later");

        }
    }
    while(search!=4);
}
void searchfind(AddressBook* addressBook,int i)
{
    printf("%d %s %s %s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
     int edit;
     int index;
     searchContact(addressBook);//search fun call to edit.
     do
     {
        printf("\nEdit contact:\n");
        printf("1.Name\n");
        printf("2.Phone\n");
        printf("3.email\n");
        printf("4.exit\n");
        printf("Enter the choice\n");
        scanf("%d",&edit);
        printf("Enter index\n");
        scanf("%d",&index);
        //__fpurge(stdin);
        if(index<0 || index>=addressBook->contactCount)
        {
            printf("Invalid index number\n");
        }
        switch(edit)
        {
            case 1:
            validate_name(addressBook->contacts[index].name);
            break;

            case 2:
            validate_phone(addressBook,addressBook->contacts[index].phone);
            break;

            case 3:
            validate_email(addressBook,addressBook->contacts[index].email);
            break;

            case 4:
            break;

            default:
            printf("Try again\n");
        
        }
        /* code */
    } while (edit!=4);
         
}

void deleteContact(AddressBook *addressBook)
{
    int index;
    searchContact(addressBook);//search fun call to delete 
    printf("Enter the index");
    scanf("%d",&index);
    if(index<0 || index>=addressBook->contactCount)
    {
        printf("try to print between 0 to 99\n");
    }
    for(int i=index;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
     addressBook->contactCount--;
    printf("contact deleted\n");
	/* Define the logic for deletecontact */
   
}
