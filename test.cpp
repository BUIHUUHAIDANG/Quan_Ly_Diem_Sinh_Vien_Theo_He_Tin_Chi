#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "console.h"
using namespace std;
// stack test implement by array and linked list 
// different between linklist and array 
// push() of array best case O(1) 
// but worst case is O(n) because if the array allowcated a small space so if the array have no more capacity so it neet to 
// create a array with double capacity and copy data of old array to new array 
// pop() worst case is O(1)
//push() and pop() when implement by linked list is O(1)
struct stackNode
{
    int data;
    stackNode* next;
};
//intializedNode(int data)
stackNode* initializedNode(int Data){
    stackNode* p=new stackNode();
    p->data=Data;
    p->next=nullptr;
    return p;
}
//isEmpty()
bool isEmpty(stackNode* root){
    return !root;
}
//push()
void push(stackNode* &root,int data){
    stackNode* p=initializedNode(data);
    p->next=root;
    root=p;
    cout << data << " pushed to stack\n";
}
//top()
int top(stackNode* &root){
    if(isEmpty(root)){
        return -1;
    }
    return root->data;
}
//pop()
int pop(stackNode* &root){
    if(isEmpty(root)){
        return -1;
    }
    stackNode* tmp=root;
    root=root->next;
    int poped=tmp->data;
    delete(tmp);
    return poped;

}



int main(){
    clrscr();
    gotoxy(75,1);cout<<"======= HE QUAN LY SINH VIEN ======="<<endl;
    cout<<endl;
}

// int main()
// {
// int a[]={5,4,3,2,1};
// int *p[]={a,a+1,a+2,a+3,a+4 };
// int **ptr=p;//what does it really means
// cout<<a<<" "<<*a;/*prints the address of a, value of a[0] (i understand this line)*/
// cout<<endl<<p<<" "<<*p<<" "<<**p;/*prints the address of p, address of a, value of a[0]    (understands this line's logic too)*/
// cout<<endl<<ptr<<" "<<*ptr<<" "<<**ptr;
// return 0;
// }




