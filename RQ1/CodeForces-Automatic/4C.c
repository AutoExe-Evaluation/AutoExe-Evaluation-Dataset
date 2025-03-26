#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_USERS 100005
#define MAX_NAME_LENGTH 35

typedef struct {
    char name[MAX_NAME_LENGTH];
    int count;
} User;

User users[MAX_USERS];
int userCount = 0;

int findUser(char* name) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addUser(char* name) {
    strcpy(users[userCount].name, name);
    users[userCount].count = 0;
    userCount++;
}

int main() {
    int n;
    scanf("%d", &n);
    
    assert(n >= 1 && n <= 100000); // PRE: number of users must be in range [1, 100000]
    
    for (int i = 0; i < n; ++i) {
        char s[MAX_NAME_LENGTH];
        scanf("%s", s);
        
        assert(strlen(s) > 0 && strlen(s) < 32); // PRE: name length must be > 0 and < 32
        
        int idx = findUser(s);
        if (idx == -1) {
            addUser(s);
            printf("OK\n");
        } else {
            users[idx].count++;
            char newName[MAX_NAME_LENGTH];
            sprintf(newName, "%s%d", s, users[idx].count);
            addUser(newName);
            printf("%s\n", newName);
        }
    }
    
    assert(userCount <= 100005); // POST: total number of users must not exceed MAX_USERS
    return 0;
}