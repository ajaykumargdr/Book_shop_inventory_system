#include <iostream>
#include <fstream>

using namespace std;
void mainmenu();
void EntryNewBook();
void EditBook();
void BuyBook();
void EditGST();
void ToStringArray();
void GstFileHandle();
void SearchBook();
void RemoveBook();
int FoundAt();

string input[500];
int GST=0;
int check=0;
int i=0;//Global variable for looping
        //I declared it as global for reusing

int main(){
    system("cls"); system("color 7D");

//th    is will executed only once
if(check!=1) {GstFileHandle();}

ToStringArray();
mainmenu();

}

void mainmenu(){
    int choose;
    cout<<"\tMain Menu:-\n"
        <<"\t-----------\n\n"
    <<"\t1) Entry For New Book\n"
    <<"\t2) Edit Book Details\n"
    <<"\t3) Buy Book\n"
    <<"\t4) Edit GST\n"
    <<"\t5) Search for book\n"
    <<"\t6) List All Books\n"
    <<"\t7) Remove Book from the Stack\n"
    <<"\t8) Exit\n\n"
    <<"\t-----------------------"
    <<"\tEnter Your Choice : ";  cin.sync();cin>>choose;
    cout<<endl;

    switch(choose){
    case 1: EntryNewBook();cout<<"Entry SuccessFull:)\n";sleep(3);
            main();
    case 2: EditBook();sleep(3);main();
    case 3: BuyBook();main();
    case 4: EditGST();main();
    case 5: SearchBook();main();
    case 6: i=0;while(input[i]!="eof"){cout<<input[i++]<<endl;}
            system("pause");main();
    case 7: RemoveBook();
            cout<<"Book Successfully Removed from the stack:)\n";
            sleep(3);main();
    case 8 : cout<<endl<<"Thank You"<<endl;exit(0);
    default : cout<<"\aYou Entered Wrong Key!\n";sleep(4);main();
    }

}

void EntryNewBook(){

    ToStringArray();
   string author,title,publisher,stackpos;
   int price;

   cout<<"Enter Author Name : "; cin.sync();getline(cin,author);
   cout<<"Enter Title Name : ";getline(cin,title);
   cout<<"Enter Bublisher Name : ";getline(cin,publisher);
   cout<<"Enter Price : ";cin>>price;
   cout<<"Enter Stack Position : ";cin>>stackpos;

   fstream out("Books.txt",ios::app); out.sync();

   if(input[0].length()!=0) {out<<endl;}

   out<<"Author Name : "<<author<<"\n";
   out<<"Title Name : "<<title<<"\n";
   out<<"Publisher Name : "<<publisher<<"\n";
   out<<"Price : "<<price<<"\n";
   out<<"Stack Position : "<<stackpos<<"\n";
   out.close();

}

void EditBook(){
RemoveBook();
EntryNewBook();
cout<<"Inventory SuccessFully Edited :)\n";
}

void BuyBook(){

int foundAt=FoundAt();

i=1;//will reuse for Number Of book

string price=input[foundAt+3];
int MRP=atoi(&price[8]);

cout<<"Enter How Many Books You Want : ";
cin.sync(); cin>>i;//i taken as number of books

cout<<"Total Price (include GST) : "<<(i*MRP)+GST<<endl;
sleep(3);
}

void EditGST(){
    char YesOrNo;
    cout<<"Current GST : "<<GST<<endl
    <<"\aAre You Conform For Changing GST!\n"
    <<"Enter Y-(YES) OR N-(NO) : "; cin>>YesOrNo;

    if(YesOrNo=='y'||YesOrNo=='Y'){
    cout<<"Enter New GST : ";cin>>GST;
    ofstream out("GST.txt");out<<GST;out.close();
    cout<<"GST Successfully changed :)\n";
    sleep(3);}

     else if (YesOrNo=='n'||YesOrNo=='N'){
            cout<<"Editing GST terminated!\n";sleep(3);}

    else {cout<<"\aPlease Enter Only Y/y or N/n !\n";sleep(3);EditGST();}

}

void SearchBook(){

int foundAt=FoundAt();
while(i<5){
    cout<<input[foundAt+i]<<endl;i++;
}i=0;system("pause");
}

void ToStringArray(){
    i=0;
    fstream in("Books.txt",ios::in);
    while(!in.eof()){
        getline(in,input[i++]);} input[i]="eof"; i=0;
    in.close();
}

void GstFileHandle(){
  ifstream in("GST.txt");
  in>>GST;
  in.close();
check=2;
}

int FoundAt(){

string title,author;
cout<<"Enter Title of Book : ";cin.sync(); getline(cin,title);
cout<<"Enter Author of the Book : ";getline(cin,author);

author="Author Name : "+author;
title="Title Name : "+title;

bool flag=0;int foundAt=0;
while(input[i]!="eof"){
if(author==input[i]&& title==input[i+1]){flag=1;foundAt=i;break;}i++;}
i=0;

if(flag==1)cout<<"Book Found In the Stack\n";
else {cout<<"\aBook Not Found In the Stack\n";sleep(3);main();}
cout<<endl;

return foundAt;
}

void RemoveBook(){

int foundAt=FoundAt();

fstream fileBook("Books.txt",ios::trunc);fileBook.clear();fileBook.close();

fstream file_("Books.txt",ios::out);
i=0;
while(input[i]!="eof"){
   if(i!=foundAt) {
    if(input[i+1]=="eof")break;
    if(i+1==foundAt&&input[i+1+6]=="eof")break;

   file_<<input[i++]<<endl;}
        if(i==foundAt)
            {i+=6;}
}file_.close();
}

//eof
