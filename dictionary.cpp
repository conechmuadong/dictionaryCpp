#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<string.h>
#include <stdlib.h>
using namespace std;

typedef struct dictionary
{
    string eng;
    string viet;
}dictionary;

vector<dictionary> vietEngDic;

string normalizeInput(string input)
{
    char *temp = new char[input.length()+1];
    strcpy(temp,input.c_str());
    for (int i=0;i<strlen(temp);i++)
    {
        if (*(temp+i)<=90&&*(temp+i)>=65)
            *(temp+i)+=32;
    }
    input = temp;
    delete temp;
    return input;
}

void loadData()
{
    fstream data;
    data.open("dataDictionary.txt",ios_base::in);
    if(data.fail())
    {
        cout<<"Data file not found, program will creat a new empty file";
        data.open("dataDictionary.txt",ios_base::out);
        data<<("dictionary information/Tu dien Anh - Viet English - Vietnamese Dictionary Developed by NDH and Tran Hong Quan\n");
        //data.open("dataDictionary.txt",ios_base::in); //Dont do that, oke
    }
    vietEngDic.clear();
    dictionary*tempdic=new dictionary;
    while (!data.eof())
    {
        char *temp = new char[100];
        data.getline(temp,100,'/');
        tempdic->eng = temp;
        data.getline(temp,100);
        tempdic->viet = temp;
        vietEngDic.push_back(*tempdic);
        delete temp;
    }
    data.close();
    delete(tempdic);
}
void addWord()
{
    dictionary*tempDic=new dictionary;
    cout<<endl<<"Word must not have space " "";
    cout<<"\nInput English word: ";
    getline(cin,tempDic->eng);
    tempDic->eng=normalizeInput(tempDic->eng);
    cout<<"Input Vietnamese meaning: ";
    getline(cin,tempDic->viet);
    tempDic->viet=normalizeInput(tempDic->viet);
    vietEngDic.push_back(*tempDic);
    ofstream data;
    data.open("dataDictionary.txt",ios_base::app|ios_base::out);
    data<<tempDic->eng<<"/"<<tempDic->viet<<"\n";
    data.close();
    delete(tempDic);
    system("cls");
    loadData();
}

void searchWordinEnglish()
{
    cout<<"\n*****Type 0 to go to Menu*****";
    next:
    string find;
    cout<<"\nSearch: ";
    getline(cin,find);
    find=normalizeInput(find);
    if(find=="0")
    {
        system("cls");
        return;
    }
    bool cantfind=true;
    for(int i=0;i<vietEngDic.size();i++)
    {
        if(find==vietEngDic[i].eng)
        {
            cout<<endl<<"\tEng: "<<find<<"\tViet: "<<vietEngDic[i].viet<<endl;
            cantfind=false;
        }
    }
    if(cantfind)
        cout<<endl<<"\tNot found\n";
    goto next;
}
void deleteWord()
{
    string find;
    cout<<"Input English word to delete: ";
    getline(cin,find);
    find=normalizeInput(find);
    for(int i=0;i<vietEngDic.size();i++)
    {
        if(find==vietEngDic[i].eng)
        {
            cout<<"\n\tDelete "<<vietEngDic[i].eng<<" with meaning is "<<vietEngDic[i].viet<<" sucessfully\n";
            vietEngDic.erase(vietEngDic.begin()+i);
            ofstream data;
            data.open("dataDictionary.txt",ios_base::trunc|ios_base::out);
            for(int i=0;i<vietEngDic.size();i++)
            {
                data<<vietEngDic[i].eng<<"/"<<vietEngDic[i].viet<<"\n";
            }
            data.close();
            cout<<"\nPress any key to continue\n";
            cin.ignore();
            system("cls");
            return;
        }
    }
    cout<<endl<<"\tNot found\n";
    cout<<"\tPress any key to continue";
    cin.ignore();
    system("cls");
}
void searchWordinVietnamese()
{
    cout<<"\n*****Type 0 to go to Menu*****";
    next:
    string find;
    cout<<"\nSearch: ";
    getline(cin,find);
    find=normalizeInput(find);
    if(find=="0")
    {
        system("cls");
        return;
    }
    bool cantfind=true;
    for(int i=0;i<vietEngDic.size();i++)
    {
        if(find==vietEngDic[i].viet)
        {
            cout<<endl<<"\tViet: "<<find<<"\t Eng: "<<vietEngDic[i].eng<<endl;
            cantfind=false;
        }
    }
    if(cantfind)
        cout<<endl<<"\tNot found\n";
    goto next;
}

int main()
{
    loadData();
    int in=0;
    next:
    cout<<"\n\t===============================MENU================================\n\t 1.Search in English 2. Search in Vietnamse 3.Add word 4.Delete word\n\t\t\t    5.App Information 0.Exit \n\t===================================================================\nInput function: ";
    cin>>in;
    char ch;
    while ((ch = getchar()) != '\n' && ch !=EOF);
    switch (in)
    {
        case 1:
            searchWordinEnglish();
            break;
        case 2:
            searchWordinVietnamese();
            break;
        case 3:
            addWord();
            break;
        case 4:
            deleteWord();
            break;
        case 5:
            system("cls");
            cout<<"\n\tEnglish-Vietnamese dictionary using C/C++\n\tDeveloped by msfroggy and Tran Hong Quan";
            cout<<"\n\tPress any key to continue...";
            cin.ignore();
            system("cls");
            break; 
        case 0:
            cout<<"Exit";
            return 0;
        default:
            break;
    }
    goto next;
    return 0;
}
