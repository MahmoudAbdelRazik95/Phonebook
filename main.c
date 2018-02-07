#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void Print();
void say(char s[]);
void Add();
void Save();
void Sort();
void Modify();
void Search();
void Delete();
void Check();
int CheckDuplicate(char x[],char y[],char z[]);
int checknum(char c[]);
typedef struct
{
    char FN[20];
    char LN[20];
    char address[30];
    char city[20];
    char tel[15];
} contact;
contact s[1000];
int c=0;
int main()
{
    Load();
    while(1)
    {
        system("COLOR 17");
        int Choice;
        printf("================================================================================");
        say("\t\t\t\t   PhoneBook\n");
        printf("================================================================================");
        say("1]Add Contact\n");
        say("2]Delete Contact\n");
        say("3]Search For Contact\n");
        say("4]Modify Contact\n");
        say("5]Print Directory\n");
        say("6]Save Directory to an External file\n");
        say("7]Exit Without saving\n");

        say("Please Enter The number of the Action You Want to Do\n");
        Choice=0;
        scanf("%d",&Choice);
k:
        switch(Choice)
        {
        case 1 :
            Add();
            break;
        case 2:
            Delete();
            break;
        case 3:
            Search();
            break;
        case 4:
            Modify();
            break;
        case 5:
            Print();
            break;
        case 6:
            Save();
            break;
        case 7:
            exit(main);
        default:
            system("COLOR 40");
            say("\a\a\a\a\aUNEXPECTED ENTRY!!\n");
            Sleep(300);
            system("COLOR 17");
            say("Please Enter The number of the Action You Want to Do\n");
            getchar();
            scanf("%d",&Choice);
            goto k;

        }

    }



}
void Check()
{
    char d[20];
    say("Press Any Key To Continue...");
    getchar();
    gets(d);
    system("cls");

}
void Add()
{
    int i,z;
    if(c==1000)
    {
        system("COLOR 40");
        say("\a\a\aMEMORY FULL!!\n");
        Sleep(300);
        system("COLOR 17");
    }


    char temp1[20],temp2[20],temp3[20],temp4[30],temp5[20];
    say("Enter The Contact's First Name: ");
    getchar();
    scanf("%[^\n]",temp1);
    getchar();
    say("Enter The Contact's Last Name: ");
    scanf("%[^\n]",temp2);
    getchar();
    say("Enter The Contact's Address: ");
    scanf("%[^\n]",temp4);
    getchar();
    say("Enter The Contact's City: ");
    scanf("%[^\n]",temp5);
k:
    say("Enter The Contact's Number: ");
    scanf("%s",temp3);
    i=checknum(temp3);
    if(i==-1)
    {
        system("COLOR 40");
        say("\a\a\aYOU ENTERED A LETTER IN THE TELEPHONE NUMBER !!\n");
        Sleep(300);
        system("COLOR 17");
        goto k;
    }
    z=CheckDuplicate(temp1,temp2,temp3);
    if(z==-1)
    {
        system("COLOR 40");
        say("\a\a\aCONTACT WITH SAME DATA ALREADY FOUND !!\n");
        Sleep(300);
        system("COLOR 17");
    }
    else if(z==0)
    {
        strcpy(s[c].FN,temp1);
        strcpy(s[c].LN,temp2);
        strcpy(s[c].tel,temp3);
        strcpy(s[c].city,temp5);
        strcpy(s[c].address,temp4);
        printf("Contact %s %s Successfully Added!!\n",s[c].FN,s[c].LN);
        c++;
        system("COLOR 20");
        Sleep(300);
        system("COLOR 17");
    }


    Check();
}
void say(char s[])
{
    int i = 0;
    while (s[i] != '\0')
    {
        putchar(s[i]);
        usleep(10000);
        i++;
    }
}
void Sort()
{
    contact temp;
    int i,j;
    for(j=0; j<c; j++)
        for(i=0; i<c; i++)
        {
            if(strcmpi(s[i].LN,s[j].LN)>0)
            {
                temp=s[i];
                s[i]=s[j];
                s[j]=temp;
            }
            else if(strcmpi(s[i].LN,s[j].LN)==0)
            {
                if(strcmpi(s[i].FN,s[j].FN)>0)
                {
                    temp=s[i];
                    s[i]=s[j];
                    s[j]=temp;

                }
                else if(strcmp(s[i].tel,s[j].tel)>0)
                {
                    temp=s[i];
                    s[i]=s[j];
                    s[j]=temp;
                }
            }

        }
}
void Print()
{
    Sort();
    char l;
    int i,j;
    for(i=0; i<c; i++)
    {
        printf("\tLAST NAME :%s            FIRST NAME: %s \nADDRESS:%s             CITY:%s        TEL:%s\n",s[i].LN,s[i].FN,s[i].address,s[i].city,s[i].tel);
        printf("________________________________________________________________________________\n");
    }
    Check();
}
void Save()
{
    Sort();
    FILE *f;
    int i;
    f=fopen("TrueCaller.txt","w");
    for(i=0; i<c; i++)
    {
        fprintf(f,"%s,%s,%s,%s,%s",s[i].LN,s[i].FN,s[i].address,s[i].city,s[i].tel);
        fprintf(f,"\n");
    }
    fclose(f);
    system("COLOR 20");
    printf("FILE SUCCESSFULLY SAVED !!\n");
    Sleep(300);
    system("COLOR 17");

    Check();


}
void Load()
{

    FILE *f;
    f=fopen("TrueCaller.txt","r");
    if(f!=NULL)
    {
        while(!feof(f))
        {
            fscanf(f,"%[^,],%[^,],%[^,],%[^,],%s",s[c].LN,s[c].FN,s[c].address,s[c].city,s[c].tel);
            fscanf(f,"\n");
            c++;
        }
        fclose(f);
        printf("\t\t\tDIRECTORY SUCCESSFULLY LOADED !!\n");
    }
    else
    {
        printf("\t\t\a\a\a\a\aDirectory Not Found !!,Forming a New Directory\n");
        system("COLOR 40");
        Sleep(300);
        system("COLOR 17");



    }
    system("COLOR 20");
    Sleep(300);
    system("COLOR 17");



}
void Search()
{
    int i=0,flag=0;
    char Search[20];
    say("Enter the Last Name of the contact: ");
    scanf("%s",Search);
    for(i=0; i<c; i++)
    {
        if (strcmp(Search,s[i].LN)==0)
        {
            printf("\tLAST NAME :%s            FIRST NAME: %s \nADDRESS:%s             CITY:%s        TEL:%s\n",s[i].LN,s[i].FN,s[i].address,s[i].city,s[i].tel);
            printf("________________________________________________________________________________\n");
            flag++;
        }
    }
    if (flag==0)
    {
        system("COLOR 40");
        say("\a\a\a\a\aCONTACT NOT FOUND!!\n");
        Sleep(500);
        system("COLOR 17");

    }
    Check();
}
void Delete()
{
    int flag=0 ,i,j,l=0,x=1,k=0,z,n[20],o=0,Temp3;
    char Temp[20],Temp2[20];
    say("Enter the last name of the contact you want to Delete : ");
    getchar();
    scanf("%[^\n]",Temp);
    for(i=0; i<c; i++)
    {
        if(strcmpi(Temp,s[i].LN)==0)
        {
            printf("\tLAST NAME :%s            FIRST NAME: %s \nADDRESS:%s             CITY:%s        TEL:%s\n",s[i].LN,s[i].FN,s[i].address,s[i].city,s[i].tel);
            printf("________________________________________________________________________________\n");
            k++;
        }



    }
    if(k==0)
    {
        goto ef;
    }


    say("Please Choose a Contact By Typing His/Her First Name :");
    getchar();
    scanf("%[^\n]",Temp2);
    for (i=0; i<c; i++)
    {
        if (strcmpi(Temp, s[i].LN) == 0&&strcmpi(Temp2, s[i].FN) == 0)
        {
            n[o]=i;
            o++;
            l++;

        }
    }
    if(l>1)
    {
        say("\a\a\a\a\aCONTACT WITH SAME FULL NAME FOUND \n Please Choose one by typing its number:\n");
        for(i=0; i<o; i++)
            printf(" %d .First Name: %s    Last Name : %s   Tel: %s \n",i+1,s[n[i]].FN,s[n[i]].LN,s[n[i]].tel);
        getchar();
        scanf("%d",&Temp3);
        x=2;
    }


    for (i=0; i<c; i++)
    {
        if(x!=2)
            Temp3=i+1;
        if (strcmpi(Temp, s[i].LN) == 0&&strcmpi(Temp2, s[i].FN) == 0&&i+1==Temp3)
        {

            for(j=i; j<c-1; j++)
            {
                s[j]=s[j+1];
            }
            system("COLOR 20");
            say("CONTACT DELETED !!\n");
            Sleep(300);
            system("COLOR 17");

            c--;
            flag++;
        }



    }



ef:
    if (flag==0)
    {
        system("COLOR 47");

        say("\a\a\a\a\aCONTACT NOT FOUND!!\n");
        Sleep(300);
        system("COLOR 17");


    }
    Check();
}
void Modify()
{
    int flag=0 ,i,j,x,l=0,a=1,d=0,k=0,p,m;
    char Temp[20],Temp2[20];
    int o[20],Temp3;
    say("Enter the last name of the contact you want to Modify : ");
    getchar();
    scanf("%[^\n]",Temp);
    for(i=0; i<c; i++)
    {
        if(strcmpi(Temp,s[i].LN)==0)
        {
            printf("\tLAST NAME :%s            FIRST NAME: %s \nADDRESS:%s             CITY:%s        TEL:%s\n",s[i].LN,s[i].FN,s[i].address,s[i].city,s[i].tel);
            printf("________________________________________________________________________________\n");
            flag++;
        }

    }
    if(flag==0)
        goto ef;
    say("Please Choose a Contact By Typing His/Her First Name :");
    getchar();
    scanf("%[^\n]",Temp2);
    for(i=0; i<c; i++)
    {
        if(strcmpi(Temp,s[i].LN)==0&&strcmpi(Temp2,s[i].FN)==0)
        {
            l++;
            o[k]=i;
            k++;
        }
    }
    if(l>1)
    {
        printf("%d ",k);
        say("\a\a\a\a\aCONTACTS WITH SAME FULL NAME FOUND \n Please Enter the Number of contact to specify:\n");
        for (i=0; i<k; i++)
        {
            printf(" %d .First Name: %s    Last Name : %s   Tel: %s \n",i+1,s[o[i]].FN,s[o[i]].LN,s[o[i]].tel);

        }
        getchar();
        scanf("%d",&Temp3);
        a=2;

    }


    for(i=0; i<c; i++)
    {
        if(a!=2)
            Temp3=i+1;

label:
        if(strcmpi(Temp,s[i].LN)==0&&strcmpi(Temp2,s[i].FN)==0&&i+1==Temp3)

        {

ok:
            say("1]Modify Last Name\n2]Modify First Name\n3]Modify Address\n4]Modify City\n5]Modify Telephone Number\n6]End Modification\n");
            say("Enter the Number of The Data You want to Modify: ");
            scanf("%d",&x);
            system("COLOR 17");
k:
            switch(x)
            {
            case 1:
                say("Enter The New Last Name:");
                getchar();
                scanf("%[^\n]",s[i].LN);
                system("COLOR 20");
                say("CONTACT MODIFIED\n");
                Sleep(300);
                system("COLOR 17");

                break;
            case 2:
                say("Enter The New First Name:");
                getchar();
                scanf("%[^\n]",s[i].FN);
                system("COLOR 20");
                say("CONTACT MODIFIED\n");
                Sleep(300);
                system("COLOR 17");

                break;
            case 3:
                say("Enter The New Address:");
                getchar();
                scanf("%[^\n]",s[i].address);
                system("COLOR 20");
                say("CONTACT MODIFIED\n");
                Sleep(300);
                system("COLOR 17");

                break;
            case 4:
                say("Enter The New City:");
                getchar();
                scanf("%[^\n]",s[i].city);
                system("COLOR 20");
                say("CONTACT MODIFIED\n");
                Sleep(300);
                system("COLOR 17");

                break;
            case 5:
po:
                say("Enter The New Telephone Number:");
                getchar();
                scanf("%[^\n]",s[i].tel);
                m=checknum(s[i].tel);
                if(m==-1)
                {
                    system("COLOR 40");
                    say("\a\a\aYOU ENTERED A LETTER IN THE TELEPHONE NUMBER !!\n");
                    Sleep(300);
                    system("COLOR 17");
                    goto po;
                }
                system("COLOR 20");
                say("CONTACT MODIFIED\n");
                Sleep(300);
                system("COLOR 17");

                break;
            case 6:
                goto el;
            default:
                system("COLOR 40");
                say("\a\a\a\a\aUNEXPECTED ENTRY!\n");
                Sleep(300);
                system("COLOR 17");
                say("Enter the Number of The Data You want to Modify: ");
                getchar();
                getchar();
                scanf("%d",&x);
                goto k;



            }
            say("Do You Want To Modify Another Thing in This Contact??\n1]Yes\n2]No\n Please enter the number of action you want to do : ");
            scanf("%d",&p);
            if(p==1)
                goto ok;
            else
                goto el;


        }
    }


    if (d==0)
ef:
    {
        system("COLOR 40");
        say("\a\a\a\a\aCONTACT NOT FOUND!!\n");
        Sleep(300);
        system("COLOR 17");

    }

el:
    Check();


}
int checknum(char c[])
{
    int a[20];
    int i=0,n=0;
    while(c[i]!='\0')
    {
        a[i]=c[i];
        i++;
        n++;
    }
    for(i=0; i<n; i++)
    {
        if(a[i]<48||a[i]>57)
            return -1;
    }
    return 1;

}
int CheckDuplicate(char x[],char y[],char z[])
{
    int i;
    for(i=0; i<=c; i++)
    {
        if(strcmpi(x,s[i].FN)==0&&strcmpi(y,s[i].LN)==0&&strcmpi(z,s[i].tel)==0)
            return -1;
    }
    return 0;
}
