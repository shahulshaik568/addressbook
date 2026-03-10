#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    Contact temp[10];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook, int sortCriteria);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);
void swap(AddressBook* addressBook,int i,int j);//swap in listcontact
void validate_name(char*);//create contact.name
void validate_phone(AddressBook*,char*);//create contact.phone
void validate_email(AddressBook*,char*);//create contact.email
void searchfind(AddressBook* addressBook,int i);

#endif
