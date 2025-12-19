// #include <iostream>
// #include <termios.h>
// #include <unistd.h>
// #include <cstdio>
// #include <cstring>
// #include "console.h"
// using namespace std;
// // // stack test implement by array and linked list 
// // // different between linklist and array 
// // // push() of array best case O(1) 
// // // but worst case is O(n) because if the array allowcated a small space so if the array have no more capacity so it neet to 
// // // create a array with double capacity and copy data of old array to new array 
// // // pop() worst case is O(1)
// // //push() and pop() when implement by linked list is O(1)
// // struct stackNode
// // {
// //     int data;
// //     stackNode* next;
// // };
// // //intializedNode(int data)
// // stackNode* initializedNode(int Data){
// //     stackNode* p=new stackNode();
// //     p->data=Data;
// //     p->next=nullptr;
// //     return p;
// // }
// // //isEmpty()
// // bool isEmpty(stackNode* root){
// //     return !root;
// // }
// // //push()
// // void push(stackNode* &root,int data){
// //     stackNode* p=initializedNode(data);
// //     p->next=root;
// //     root=p;
// //     cout << data << " pushed to stack\n";
// // }
// // //top()
// // int top(stackNode* &root){
// //     if(isEmpty(root)){
// //         return -1;
// //     }
// //     return root->data;
// // }
// // //pop()
// // int pop(stackNode* &root){
// //     if(isEmpty(root)){
// //         return -1;
// //     }
// //     stackNode* tmp=root;
// //     root=root->next;
// //     int poped=tmp->data;
// //     delete(tmp);
// //     return poped;

// // }



// // int main(){
// //     clrscr();
// //     gotoxy(75,1);cout<<"======= HE QUAN LY SINH VIEN ======="<<endl;
// //     cout<<endl;
// // }

// // // int main()
// // // {
// // // int a[]={5,4,3,2,1};
// // // int *p[]={a,a+1,a+2,a+3,a+4 };
// // // int **ptr=p;//what does it really means
// // // cout<<a<<" "<<*a;/*prints the address of a, value of a[0] (i understand this line)*/
// // // cout<<endl<<p<<" "<<*p<<" "<<**p;/*prints the address of p, address of a, value of a[0]    (understands this line's logic too)*/
// // // cout<<endl<<ptr<<" "<<*ptr<<" "<<**ptr;
// // // return 0;
// // // }
// //Can not use sizeof pass to a function 
// int getNumOfSinhVien( char MaSV[]){
//     int length=strlen(MaSV);
//     int result=0;
//     for(int i=length-3;i<length;i++){
//         result=result*10+(MaSV[i]-'0');
//     }
//     return result;
// }

// int main() {
//     cout << "Nhan phim bat ky: ";
//     int c = getch();
//     cout << "\nBan nhan: " << (char)c << endl;
// }
#include <stdio.h>

#define MAX_FRAMES 50

int n, m, frames[MAX_FRAMES], pages[100], page_faults = 0;

void display()
{
    int i;
    printf("Frames: ");
    for (i = 0; i < m; i++)
        printf("%d ", frames[i]);
}

int find_optimal_page(int time[])
{
    int i, max = -1, optimal_page = 0;
    for (i = 0; i < m; i++)
    {
        if (time[frames[i]] > max)
        {
            max = time[frames[i]];
            optimal_page = i;
        }
    }
    return optimal_page;
}

int check_page_fault(int page)
{
    int i;
    for (i = 0; i < m; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

void demand_paging(int pages[], int n, int m)
{
    int time[100], i, j, optimal_page, flag;
    for (i = 0; i < n; i++)
    {
        flag = 0;
        if (!check_page_fault(pages[i]))
        {
            if (i < m)
                frames[i] = pages[i];
            else
            {
                for (j = 0; j < m; j++)
                    time[frames[j]] = 0;
                for (j = i + 1; j < n; j++)
                {
                    time[pages[j]]++;
                    if (time[pages[j]] > time[frames[optimal_page]])
                        optimal_page = find_optimal_page(time);
                }
                frames[optimal_page] = pages[i];
                page_faults++;
            }
            flag = 1;
        }
        display();
        if (flag)
            printf("\tPage Fault: %d", pages[i]);
        printf("\n");
    }
    printf("Total Page Faults: %d", page_faults);
}

int main()
{
    int i;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &m);
    demand_paging(pages, n, m);
    return 0;
}
