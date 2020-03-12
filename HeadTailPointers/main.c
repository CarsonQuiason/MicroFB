/*
 * Carson Rottinghaus
 * Cqrqfd
 * 16265777
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hash *hashTable = NULL;
int eleCount = 0;

typedef struct Person {
    char * name;
    struct Person *next;
}Person;

struct hash {
    struct Person * head;
};

int hashFunction(const char * name);
void insertToHash(char * name);
void addFriend(char * name1, char * name2);
void removeFriend(char * name1, char * name2);
void printAllFriends(char * name);
int checkFriends(char * name1, char * name2);

/*
 * Creates a hash based on 128 multiplier, element count and letters of string
 */
int hashFunction(const char * name)
{
    int i = 0;
    int hashIndex = 0;
    while (i < 100 && name[i] != '\0')
    {
        hashIndex = (hashIndex * 128) % eleCount;
        hashIndex = (hashIndex + (name[i] % 128)) % eleCount;
        i++;
    }
    return hashIndex;
}

/*
 * Inserts a user into the database
 * Attaches a head node to their respected index
 */
void insertToHash(char * name) {
    int hashIndex = hashFunction(name);
    printf("Users hash index: %d\n",hashIndex);
    Person * FL = malloc(sizeof(Person));
    if(FL == NULL){
        printf("Error");
        return;
    }
    FL->next = NULL;
    FL->name = "User";
    hashTable[hashIndex].head = FL;
}
/*
 * Adds two users to each other's friends list
 */
void addFriend(char * name1,char * name2){
    Person * newFriend2 = malloc(sizeof(Person));
    if(newFriend2 == NULL){
        printf("Error");
        return;
    }
    Person * newFriend = malloc(sizeof(Person));
    if(newFriend == NULL){
        printf("Error");
        return;
    }

    newFriend2->name = name2;
    newFriend2->next = NULL;
    newFriend->name = name1;
    newFriend->next = NULL;

    int hashIndex1 = hashFunction(name1);
    if(hashTable[hashIndex1].head == NULL){
        return;
    }
    int hashIndex2 = hashFunction(name2);
    if(hashTable[hashIndex2].head == NULL){
        return;
    }

    Person * temp = hashTable[hashIndex1].head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newFriend2;


    Person * temp2 = hashTable[hashIndex2].head;
    while(temp2->next != NULL){
        temp2 = temp2->next;
    }
    temp2->next = newFriend;
}

/*
 * Removes two users from each other's friendslist
 */
void removeFriend(char * name1, char * name2){
    int friends = checkFriends(name1, name2);
    if(friends == 0){
        return;
    }
    int hashIndex1 = hashFunction(name1);
    int hashIndex2 = hashFunction(name2);
    Person * temp = hashTable[hashIndex1].head;

    while(strcmp(temp->next->name,name2) != 0){
        temp = temp->next;
    }
    temp->next = temp->next->next;
    Person * temp2 = hashTable[hashIndex2].head;
    while(strcmp(temp2->next->name,name1) != 0){
        temp2 = temp2->next;
    }
    temp2->next = temp2->next->next;
}
/*
 * Prints all the friends of a given user
 * Tells user if they don't have any friends
 */
void printAllFriends(char * name) {
    int hashIndex = hashFunction(name);
    printf("printing all friends of %s\n using hash index: %d\n",name,hashIndex);
    Person * temp = hashTable[hashIndex].head->next;
    if(temp == NULL){
        printf("User has no friends\n");
        return;
    }
    while(temp != NULL){
        printf("%s ",temp->name);
        temp = temp->next;
    }
    printf("\n");
}
/*
 * Checks if two users are friends
 * Returns 1 on success
 * Returns 0 on failure
 */
int checkFriends(char * name1, char * name2){
    int hashIndex1 = hashFunction(name1);
    Person * temp = hashTable[hashIndex1].head;
    while(temp->next != NULL){
        if(strcmp(temp->next->name,name2) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int main() {
    int n = 100;
    eleCount = n;
    hashTable = (struct hash *) calloc(n, sizeof(struct hash));
    char input[100];
    char name1[10];
    char name2[10];
    if (hashTable == NULL) {
        printf("Error");
        exit(-1);
    }
    insertToHash("Carson");
    insertToHash("Collin");
    insertToHash("Joe");
    addFriend("Carson","Collin");
    addFriend("Joe","Collin");
    addFriend("Carson","Joe");
    printAllFriends("Carson");
    printAllFriends("Joe");
    printAllFriends("Collin");
    removeFriend("Carson","Joe");
    printAllFriends("Carson");
    char command[100];
    fgets(command,100,stdin);
    sscanf(command,"%s %s %s",input,name1,name2);
    while (strcmp(input,"X") != 0) {
        if (strcmp(input, "P") == 0) {
            insertToHash(name1);
        }
        if (strcmp(input, "F") == 0) {
            addFriend(name1, name2);
        }
        if (strcmp(input, "U") == 0) {
            removeFriend(name1, name2);
        }
        if (strcmp(input, "L") == 0) {
            printAllFriends(name1);
        }
        if (strcmp(input, "Q") == 0) {
            int bool = checkFriends(name1, name2);
            if (bool == 1) {
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
        }
        fgets(command,50,stdin);
        sscanf(command,"%s %s %s",input,name1,name2);
    }
    return 0;
}


