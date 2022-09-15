
typedef struct Node {
  struct Node* next;
  char* str;
} Node;

Node* initStack();
void push(Node** top, char* str);
char* pop(Node** top);
char* peek(Node* top);
void removeStack(Node** top);
void printStack(Node* top);

