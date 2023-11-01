#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a task
typedef struct Task {
    int id;
    char description[100];
    int priority;  // Priority field
    struct Task* prev;
    struct Task* next;
} Task;

// Function to create a new task
Task* createTask(int id, const char* description, int priority) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    if (newTask == NULL) {
        perror("Memory allocation error");
        exit(1);
    }
    newTask->id = id;
    strncpy(newTask->description, description, sizeof(newTask->description));
    newTask->priority = priority;
    newTask->prev = NULL;
    newTask->next = NULL;
    return newTask;
}
void addTask(Task** head, Task* newTask) {
    if (*head == NULL) {
        *head = newTask;
    } else {
        Task* current = *head;
        while (current != NULL && newTask->priority >= current->priority) {
            current = current->next;
        }

        if (current == *head) {
            newTask->next = *head;
            (*head)->prev = newTask;
            *head = newTask;
        } else if (current == NULL) {
            Task* last = *head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = newTask;
            newTask->prev = last;
        } else {
            newTask->next = current;
            newTask->prev = current->prev;
            current->prev->next = newTask;
            current->prev = newTask;
        }
    }
}
void displayTasks(Task* head) {
    Task* current = head;
    while (current != NULL) {
        printf("Task %d (Priority %d): %s\n", current->id, current->priority, current->description);
        current = current->next;
    }
}

int main() {
    Task* taskList = NULL; 
    int len,prio;
    char st[26];
    scanf("%d", &len);
    for(int i=1;i<len;i++) {
        printf("holla! boss please enter task u want to perform");
        scanf("%s",st);
        printf("holla! boss please enter %s's priority",st);
        scanf("%d",prio);
        addTask(&taskList, createTask(i, st, prio));

    }
    printf("List of tasks:\n");
    displayTasks(taskList);
    Task* current = taskList;
    while (current != NULL) {
        Task* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
