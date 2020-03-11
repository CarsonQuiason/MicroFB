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
    int count;
};

int hashFunction(char * name)
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


void insertToHash(char * name) {
    int hashIndex = hashFunction(name);
    Person * FL = malloc(sizeof(Person));
    FL->next = NULL;
    FL->name = NULL;
    hashTable[hashIndex].head = FL;
}

void addFriend(char * name1, char * name2){
    Person * newFriend = malloc(sizeof(Person));
    newFriend->name = name1;
    newFriend->next = NULL;
    Person * newFriend2 = malloc(sizeof(Person));
    newFriend2->name = name2;
    newFriend2->next = NULL;

    int hashIndex1 = hashFunction(name1);
    int hashIndex2 = hashFunction(name2);

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

void removeFriend(char * name1, char * name2){
    int hashIndex1 = hashFunction(name1);
    int hashIndex2 = hashFunction(name2);
    Person * temp = hashTable[hashIndex1].head;

    while(strcmp(temp->next->name,name2) != 0){
        printf("%s %s",temp->next->name,name2);
        temp = temp->next;
    }
    temp->next = temp->next->next;
    free(temp->next);
    Person * temp2 = hashTable[hashIndex2].head;
    while(strcmp(temp2->next->name,name1) != 0){
        temp2 = temp2->next;
    }
    temp2->next = temp2->next->next;
    free(temp2->next);
}

void printAllFriends(char * name) {
    int hashIndex = hashFunction(name);
    Person * temp = hashTable[hashIndex].head->next;
    while(temp != NULL){
        printf("%s ",temp->name);
        temp = temp->next;
    }
}

char * checkFriends(char * name1, char * name2){
    static char flag[3 + 1];
    int hashIndex1 = hashFunction(name1);
    Person * temp = hashTable[hashIndex1].head;
    temp
    while(){

    }
    return flag;
}



int main() {

    int n = 1000;
    eleCount = n;
    hashTable = (struct hash *)calloc(n, sizeof(struct hash));
    insertToHash("Carson");
    insertToHash("Collin");
    insertToHash("Joe");
    addFriend("Carson", "Collin");
    addFriend("Collin", "Joe");
    addFriend("Carson", "Joe");
    printAllFriends("Carson");
    removeFriend("Carson", "Joe");
    removeFriend("Carson", "Collin");
    printf("\n\n--------");
    printAllFriends("Carson");
    }
