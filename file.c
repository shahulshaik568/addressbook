#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    if(addressBook==NULL || addressBook->contactCount==0)
    {
        printf("AddressBook has no Contacts\n");
        return;
    }

    FILE* fptr=fopen("contacts.csv","w+");//to open file in read and write mode
    if(fptr==NULL)
    {
        printf("file opening fail");
        return;
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);//to close file
  
}

void loadContactsFromFile(AddressBook *addressBook) {

    FILE* fptr=fopen("contacts.csv","r");//open file in read mode
    if(fptr==NULL)
    {
        printf("file opening fail");
        return;
    }
    while(fscanf(fptr,"%[^,],%[^,],%[^\n]",addressBook->contacts[addressBook->contactCount].name,
        addressBook->contacts[addressBook->contactCount].phone,
        addressBook->contacts[addressBook->contactCount].email)==3)
        {
            addressBook->contactCount++;
            if(addressBook->contactCount>=100)
            {
                break;
            }
        }
        fclose(fptr);
    
}
