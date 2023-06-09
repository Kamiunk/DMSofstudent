#ifndef _MYHEAD_H_
#define _MYHEAD_H_

/**
 *ͷ�ļ�����
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //�ַ���
#include <ctype.h>      //�ַ��ж�
#include <conio.h>      //�������
#include <Windows.h>    //system("cls") && Sleep() && PlaySound()
#include <mmsystem.h>   //playsound()
//#pragma comment(lib, "winmm.lib")//playsound()

/**
 *�궨��
*/
#define N 13
#define M 101


/**
 *�ṹ������
*/
//������Ϣ
typedef struct room
{
    char flood[N];			//¥��
    char name[N];           //�����
    int maxNumb;		    //�����ס����
    int preNumb;			//��ǰ��ס����
    struct room * next;		//�ڵ�����
} Room;
//ѧ��������Ϣ
typedef struct basic_info
{
    char numb[N];		    //ѧ��
    char name[N];		    //����
    char flood[N];			//¥��
    char room[N];           //�����
    char position[N];       //����ְλ
} Basicf;
//ѧ����ϸ��Ϣ
typedef struct detail_info
{
    char tel[N];            //�绰
    char recordate[N];	    //��סʱ��
    char birthday[N];       //����
    char province[N];       //ʡ�ݻ�ֱϽ��
    char Address[M];      //��ϸ��ַ
} Detailf;
//ѧ����Ϣ
typedef struct student
{
    Basicf basic_info;	        //������Ϣ
    Detailf detail_info;        //��ϸ��Ϣ
    struct student * next;		//�ڵ�����
} Student;


/**
 *������������
*/
//���ܲ˵���ӡ
void printMenu();
//������
int checkPassword(const char password[], FILE * historyFile);
//���ݵ���
void importData(FILE * roomFile, FILE * stuFile, Room ** roomHead, Student ** stuHead);

/**
 *���ܺ�������
 */

//1. ������Ϣ�鿴
void viewMainInfo(Room * roomHead);
//2. ѧ����Ϣ��ѯ���޸���ɾ��
void searchStu(Room * roomHead, Student ** stuHead, FILE * historyFile);
//3. ѧ����Ϣ¼��
void addStudent(Room * roomHead, Student ** stuHead, FILE * historyFile);
//4. ѧ����Ϣ����
void sortStudent(Student * stuHead);
//5. ������Ϣ�޸�
void changeRoom(Room ** roomHead, Student * stuHead, FILE * historyFile);
//6. ����Ա��Ϣ�޸�
void changeAdmin(char buildingName[], char adminName[], char adminPassword[], FILE * adminFile, FILE * historyFile);
//7. �����ļ�������Ա��ѧ����Ϣ��
void resetFile(FILE * roomFile, FILE * stuFile, Room * roomHead, Student * stuHead);
//8. ��ʼ��������Ϣ
void resetRoom(Room ** roomHead, Student ** stuHead);
//9. ������¼�鿴
void printHistory(FILE * historyFile);

/**С����*/
//���ҷ���
Room * searchRoom(char flood[], char roomName[], Room * roomHead);
//ѧ�Ų���
Student * checkNumb(char stuNumb[], Student * stuHead);
//ѧ����Ϣ�޸�
void changeStu(Room * roomHead, Student * stuHead, Student * Sp, FILE * historyFile);
//ѧ������ͳ��
int studentCount(Student * stuHead);
//��������
void sortBySomeway(Student ** sortStart, int n, int (* someWay)(Student * a, Student * b));
//ѧ������
int sortByNumb(Student * a, Student * b);
//��������
int sortByName(Student * a, Student * b);
//��������
int sortByRoom(Student * a, Student * b);
//ʡ�ݣ�ֱϽ�У�����
int sortByProvince(Student * a, Student * b);



/**
 *������������
*/
//���ܲ˵���ӡ
void printMenu()
{
    printf("\t 1. ������Ϣ�鿴\n");
    Sleep(50);
    printf("\t 2. ѧ����Ϣ��ѯ���޸���ɾ��\n");
    Sleep(50);
    printf("\t 3. ѧ����Ϣ¼��\n");
    Sleep(50);
    printf("\t 4. ѧ����Ϣ����\n");
    Sleep(50);
    printf("\t 5. ������Ϣ�޸�\n");
    Sleep(50);
    printf("\t 6. ����Ա��Ϣ�޸�\n");
    Sleep(50);
    printf("\t 7. �����ļ�������Ա��ѧ����Ϣ��\n");
    Sleep(50);
    printf("\t 8. ��ʼ��¥����Ϣ\n");
    Sleep(50);
    printf("\t 9. ������¼�鿴\n");
    Sleep(50);
    printf("\t 0. �˳�\n");
    Sleep(50);
    printf("\t******************************************************************\n\n");
}

//������
int checkPassword(const char password[], FILE * historyFile)
{
    int i;
    char c;
    char tempPassword[N];
    printf("\t ���������Ա���룺");
    fprintf(historyFile, "\t ���������Ա���룺");
    for(i=0; i<N; i++)
    {
        c = getch();
        if(i == N-1)
        {
            tempPassword[N-1] = '\0';
            break;
        }
        else if(isalnum(c))
        {
            tempPassword[i] = c;
            putchar('*');
        }
        else if(c == '\n'||c == '\r')
        {
            if(i==0)
            {
                system("cls");
                return 0;
            }
            tempPassword[i] = '\0';
            printf("\n");
            break;
        }
        else if(c == '\b')
        {
            if(i>0)
            {
                i -= 2;
                printf("\b");
            }
        }
        else
        {
            i--;
        }
    }
    system("cls");
    if(strcmp(password,tempPassword) == 0)
    {
        fprintf(historyFile, "�����벻�ɼ���\n\n");
        return 1;
    }
    else
    {
        fprintf(historyFile, "%s\n", tempPassword);
        return 0;
    }

}
//���ݵ���
void importData(FILE * roomFile, FILE * stuFile, Room ** roomHead, Student ** stuHead)
{
    Room * Rp = NULL;
    Student * Sp = NULL;
    //�����ļ�����
    fgetc(roomFile);
    if(feof(roomFile))
    {
        *roomHead = NULL;
        return;
    }
    else
    {
        rewind(roomFile);
        *roomHead = (Room *)malloc(sizeof(Room));
        if(*roomHead == NULL)
        {
            printf("\t �ڴ治�㣡\n");
            exit(0);
        }
        //��ȡ������Ϣ
        Rp = *roomHead;
        while(!feof(roomFile))
        {
            //��ȡ��Ϣ
            fread(Rp, sizeof(Room), 1, roomFile);
            fgetc(roomFile);
            if(feof(roomFile))
            {
                Rp->next = NULL;
                break;
            }
            else//������һ������ڵ�
            {
                fseek(roomFile, -1, 1);
                Rp->next = (Room *)malloc(sizeof(Room));
                Rp = Rp->next;
                if(Rp == NULL)
                {
                    printf("\t �ڴ治�㣡\n");
                    exit(0);
                }
            }
        }
    }
    //ѧ���ļ�����
    fgetc(stuFile);
    if(feof(stuFile))
    {
        *stuHead = NULL;
    }
    else
    {
        rewind(stuFile);
        *stuHead = (Student *)malloc(sizeof(Student));
        if(*stuHead == NULL)
        {
            printf("\t �ڴ治�㣡\n");
            exit(0);
        }
        //��ȡѧ����Ϣ
        Sp = *stuHead;
        while(!feof(stuFile))
        {
            fread(Sp, sizeof(Student), 1, stuFile);
            fgetc(stuFile);
            if(feof(stuFile))
            {
                Sp->next = NULL;
                break;
            }
            else//������һ��ѧ���ڵ�
            {
                fseek(stuFile, -1, 1);
                Sp->next = (Student *)malloc(sizeof(Student));
                Sp = Sp->next;
                if(Sp == NULL)
                {
                    printf("\t �ڴ治�㣡\n");
                    exit(0);
                }
            }
        }
    }
    //�ر��ļ�
    fclose(roomFile);
    fclose(stuFile);
}


/**
 *���ܺ�������
 */
//1. ������Ϣ�鿴
void viewMainInfo(Room * roomHead)
{
    int i;
    char flood[N];
    Room * Rp;
    if(roomHead == NULL)
    {
        printf("\t ��ǰ�޷������ݣ��뽨����鿴��\n");
        return;
    }
    Rp = roomHead;
    i = -1;
    strcpy(flood, Rp->flood);
    printf("\n\t %s  ¥��\n", flood);
    Sleep(50);
    while(Rp!=NULL)
    {
        if(strcmp(flood, Rp->flood)!=0)
        {
            i = 0;
            strcpy(flood, Rp->flood);
            printf("\n\n\t %s  ¥��\n", flood);
            Sleep(50);
            printf("\n\t\t ");
        }
        else
        {
            i++;
            if(i%4 == 0)
            {
                printf("\n\t\t ");
                Sleep(50);
            }
            else
            {
                printf("\t");
            }
        }
        printf("%s(%d/%d)", Rp->name, Rp->preNumb, Rp->maxNumb);
        Rp = Rp->next;
    }
    printf("\n");
}
//2. ѧ����Ϣ��ѯ���޸���ɾ��
void searchStu(Room * roomHead, Student ** stuHead, FILE * historyFile)
{
    int findFlag;
    char c;
    char Fchoice, Schoice, Tchoice, Mchoice;
    char searchStr[N];
    Room * Rp = NULL;
    Student * Sp =NULL;
    Student * Spr = NULL;

    if(*stuHead==NULL)
    {
        printf("\t ��ǰ��ѧ����Ϣ\n");
        fprintf(historyFile, "\t ��ǰ��ѧ����Ϣ\n");
        return ;
    }
    do
    {
        Sleep(1000);
        system("cls");
        printf("\t******************************************************************\n\n");
        Sleep(50);
        printf("\t ѡ���ܣ���1. ��ѯ  0. �˳���\n\t ");
        Sleep(50);
        do
        {
            Fchoice = getchar();
            while((c=getchar())!=EOF&&c!='\n');
            if(Fchoice!='1'&&Fchoice!='0')
            {
                system("cls");
                printf("\t******************************************************************\n\n");
                Sleep(50);
                printf("\t ����ȷ����\n");
                Sleep(50);
                printf("\t ѡ���ܣ���1. ��ѯ  0. �˳���\n\t ");
                Sleep(50);
            }
        }while(Fchoice!='1'&&Fchoice!='0');
        fprintf(historyFile, "\t ѡ���ܣ���1. ��ѯ  0. �˳���\n\t %c\n", Fchoice);
        if(Fchoice=='1')
        {
            do
            {
                printf("\t ѡ���ѯ��ʽ����1. ѧ��  2. ����  3. �绰  4. ����ţ�\n\t ");
                Sleep(50);
                Schoice = getchar();
                while((c=getchar())!=EOF&&c!='\n');
                if(Schoice<'1'||Schoice>'4')
                {
                    printf("\t ����ȷ����\n\t ");
                }
            }while(Schoice<'1'||Schoice>'4');
            fprintf(historyFile, "\t ѡ���ѯ��ʽ����1. ѧ��  2. ����  3. �绰  4. ����ţ�\n\t %c\n", Schoice);
            printf("\t �����������Ϣ��");
            Sleep(50);
            fgets(searchStr, N, stdin);
            if(searchStr[0]=='\n')
            {
                printf("\t ��������\n");
                continue;
            }
            else if(searchStr[strlen(searchStr)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                searchStr[strlen(searchStr)-1] = '\0';
            }
            fprintf(historyFile, "\t �����������Ϣ��%s\n", searchStr);
            if(Schoice=='2'||Schoice=='4')//ѡ���޸�
            {
                do
                {
                    printf("\t ѡ����Ϣ��ӡ��ʽ����1. ��  2. ��ϸ��\n\t ");
                    Sleep(50);
                    Tchoice = getchar();
                    while((c=getchar())!=EOF&&c!='\n');
                    if(Tchoice!='1'&&Tchoice!='2')
                    {
                        printf("\t �������\n");
                    }
                }while(Tchoice!='1'&&Tchoice!='2');
                fprintf(historyFile, "\t ѡ����Ϣ��ӡ��ʽ����1. ��  2. ��ϸ��\n\t %c\n", Tchoice);
                if(Tchoice=='1')
                {
                    printf("\t %-14s%-14s%-14s%-14s%-14s\n\n",
                            "����", "ѧ��", "¥��", "�����", "ְλ");
                    Sleep(50);
                    fprintf(historyFile, "\t %-14s%-14s%-14s%-14s%-14s\n\n",
                            "����", "ѧ��", "¥��", "�����", "ְλ");
                }
                else
                {
                    printf("\t %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n\n",
                            "����", "ѧ��", "¥��", "�����", "ְλ",
                            "�绰", "��סʱ��", "����", "ʡ��", "��ϸ��ַ");
                    Sleep(50);
                    fprintf(historyFile, "\t %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n\n",
                            "����", "ѧ��", "¥��", "�����", "ְλ",
                            "�绰", "��סʱ��", "����", "ʡ��", "��ϸ��ַ");
                }
                Sp = *stuHead;
                Spr = Sp;
                findFlag = 0;
                while(Sp!=NULL)
                {
                    if(Schoice=='2')
                    {
                        if(strcmp(Sp->basic_info.name, searchStr)==0)
                        {
                            findFlag = 1;
                        }
                        else
                        {
                            findFlag = 0;

                        }
                    }
                    else if(Schoice=='4')
                    {
                        if(strcmp(Sp->basic_info.room, searchStr)==0)
                        {
                            findFlag = 1;
                        }
                        else
                        {
                            findFlag = 0;
                        }
                    }
                    //��ѯ�������
                    if(findFlag==1)
                    {
                        if(Tchoice=='1')
                        {
                            printf("\t %-14s%-14s%-14s%-14s%-14s\n",
                                    Sp->basic_info.name,
                                    Sp->basic_info.numb,
                                    Sp->basic_info.flood,
                                    Sp->basic_info.room,
                                    Sp->basic_info.position);
                            Sleep(50);
                            fprintf(historyFile, "\t %-14s%-14s%-14s%-14s%-14s\n",
                                    Sp->basic_info.name,
                                    Sp->basic_info.numb,
                                    Sp->basic_info.flood,
                                    Sp->basic_info.room,
                                    Sp->basic_info.position);
                        }
                        else if(Tchoice=='2')
                        {
                            printf("\t %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n",
                                    Sp->basic_info.name,
                                    Sp->basic_info.numb,
                                    Sp->basic_info.flood,
                                    Sp->basic_info.room,
                                    Sp->basic_info.position,
                                    Sp->detail_info.tel,
                                    Sp->detail_info.recordate,
                                    Sp->detail_info.birthday,
                                    Sp->detail_info.province,
                                    Sp->detail_info.Address);
                            Sleep(50);
                            fprintf(historyFile, "\t %-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%-12s%s\n\n",
                                    Sp->basic_info.name,
                                    Sp->basic_info.numb,
                                    Sp->basic_info.flood,
                                    Sp->basic_info.room,
                                    Sp->basic_info.position,
                                    Sp->detail_info.tel,
                                    Sp->detail_info.recordate,
                                    Sp->detail_info.birthday,
                                    Sp->detail_info.province,
                                    Sp->detail_info.Address);
                        }
                        do
                        {
                            printf("\t ����ѡ�񣺣�1. �޸�  2. ɾ��  3. ������һ��  0. �˳���\n\t ");
                            Sleep(50);
                            Mchoice = getchar();
                            if(Mchoice<'0'||Mchoice>'3')
                            {
                                printf("\t �������룬 ����������\n");
                            }
                        }while(Mchoice<'0'||Mchoice>'3');
                        fprintf(historyFile, "\t ����ѡ�񣺣�1. �޸�  2. ɾ��  3. ������һ��  0. �˳���\n\t %c\n", Mchoice);
                        if(Mchoice=='0')
                        {
                            return ;
                        }
                        else if(Mchoice=='3')
                        {
                            Spr = Sp;
                            Sp = Sp->next;
                            continue;
                        }
                        else if(Mchoice=='1')
                        {
                            changeStu(roomHead, *stuHead, Sp, historyFile);
                            break;
                        }
                        else if(Mchoice=='2')
                        {
                            //���·�����Ϣ
                            Rp = searchRoom(Sp->basic_info.flood, Sp->basic_info.room, roomHead);
                            Rp->preNumb -= 1;
                            //��������
                            if(Sp==(*stuHead))
                            {
                                Spr = *stuHead;
                                *stuHead = (*stuHead)->next;
                                free(Spr);
                            }
                            else
                            {
                                Spr->next = Sp->next;
                                free(Sp);
                            }
                            printf("\t ɾ���ɹ�\n\n");
                            fprintf(historyFile, "\t ɾ���ɹ�\n\n");
                            break;
                        }
                    }
                    else
                    {
                        Spr = Sp;
                        Sp = Sp->next;
                    }

                }//����ѭ��
                if(Sp==NULL)
                {
                    printf("\t δ�ҵ�\n\n");
                    fprintf(historyFile, "\t δ�ҵ�\n\n");
                    getchar();
                    continue;
                }
            }//�������
            else if(Schoice=='1'||Schoice=='3')//Ψһ�޸�
            {
                Sp = *stuHead;
                findFlag = 0;
                while(Sp!=NULL)
                {
                    if(Schoice=='1')//ѧ��
                    {
                        if(strcmp(Sp->basic_info.numb, searchStr)==0)
                        {
                            findFlag = 1;
                            break;
                        }
                        else
                        {
                            findFlag = 0;
                            Spr = Sp;
                            Sp = Sp->next;
                        }
                    }
                    else if(Schoice=='3')//�绰
                    {
                        if(strcmp(Sp->detail_info.tel, searchStr)==0)
                        {
                            findFlag = 1;
                            break;
                        }
                        else
                        {
                            findFlag = 0;
                            Spr = Sp;
                            Sp = Sp->next;
                        }
                    }
                }
                if(findFlag==1)
                {
                    printf("\t �ҵ�����������ѧ��\n");
                    Sleep(50);
                    fprintf(historyFile, "\t �ҵ��˷���������ѧ��\n");
                    printf("\t ������Ϣ��\n\t\t ������%s\n\t\t ѧ�ţ�%s\n\t\t ¥�㣺%s\n\t\t ����ţ�%s\n\t\t ְλ��%s\n",
                            Sp->basic_info.name, Sp->basic_info.numb, Sp->basic_info.flood,
                            Sp->basic_info.room, Sp->basic_info.position);
                    Sleep(100);
                    printf("\t ��ϸ��Ϣ��\n\t\t �绰��%s\n\t\t ���գ�%s\n\t\t ��סʱ�䣺%s\n\t\t ʡ�ݣ�ֱϽ�У���%s\n\t\t ��ϸ��ַ��%s\n\n",
                            Sp->detail_info.tel, Sp->detail_info.birthday, Sp->detail_info.recordate,
                            Sp->detail_info.province, Sp->detail_info.Address);
                    Sleep(100);
                    do
                    {
                        printf("\t ѡ���ܣ���1. �޸�  2. ɾ��  0. �˳���\n\t ");
                        Sleep(50);
                        Mchoice = getchar();
                        while((c=getchar())!=EOF&&c!='\n');
                        if(Mchoice<'0'||Mchoice>'2')
                        {
                            printf("\t �������룬������ѡ��\n");
                        }
                    }while(Mchoice<'0'||Mchoice>'2');
                    fprintf(historyFile, "\t ѡ���ܣ���1. �޸�  2. ɾ��  0. �˳���\n\t %c", Mchoice);
                    if(Mchoice=='0')
                    {
                        return;
                    }
                    else if(Mchoice=='1')
                    {
                        changeStu(roomHead, *stuHead, Sp, historyFile);
                        continue;
                    }
                    else if(Mchoice=='2')
                    {
                        //���·�����Ϣ
                        Rp = searchRoom(Sp->basic_info.flood, Sp->basic_info.room, roomHead);
                        Rp->preNumb -= 1;
                        //��������
                        if(Sp==(*stuHead))
                        {
                            Spr = *stuHead;
                            *stuHead = (*stuHead)->next;
                            free(Spr);
                        }
                        else
                        {
                            Spr->next = Sp->next;
                            free(Sp);
                        }
                        printf("\t ɾ���ɹ�\n\n");
                        fprintf(historyFile, "\t ɾ���ɹ�\n\n");
                        break;
                    }
                }
                else
                {
                    printf("\t δ�ҵ�\n\n");
                    fprintf(historyFile, "\t δ�ҵ�\n\n");
                    continue;
                }
            }
        }
        else
        {
            break;
        }
    }while(Fchoice=='1');
}
//3. ѧ����Ϣ¼��
void addStudent(Room * roomHead, Student ** stuHead, FILE * historyFile)
{
    char c;
    char Fchoice, Schoice;
    char flood[N];
    char roomName[N];
    Room * Rp = NULL;
    Student * Sp = NULL;
    Student * Spr = NULL;
    Student tempMemb;

    do
    {
        /**����ѡ��*/
        do
        {
            printf("\t ����ѡ�񣺣�1. ¼��  0. �˳���\n\t ");
            Sleep(50);
            Fchoice = getchar();
            while((c=getchar())!=EOF&&c!='\n');
            if(Fchoice!='1'&&Fchoice!='0')
            {
                system("cls");
                printf("\t******************************************************************\n\n");
                Sleep(50);
                printf("\t ����ȷ����\n");
                Sleep(50);
            }
        }while(Fchoice!='1'&&Fchoice!='0');
        fprintf(historyFile, "\t ����ѡ�񣺣�1. ¼��  0. �˳���\n\t %c\n", Fchoice);
        if(Fchoice=='1')
        {
            RoomChange:
            printf("\t ������Ŀ�귿��¥�㣺");
            Sleep(50);
            fgets(flood, N, stdin);
            if(flood[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(flood[strlen(flood)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                flood[strlen(flood)-1] = '\0';
            }
            fprintf(historyFile, "\t ������Ŀ�귿��¥�㣺%s\n", flood);
            printf("\t ������Ŀ�귿��ţ�");
            Sleep(50);
            fgets(roomName, N, stdin);
            if(roomName[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(roomName[strlen(roomName)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                roomName[strlen(roomName)-1] = '\0';
            }
            fprintf(historyFile, "\t ������Ŀ�귿��ţ�%s\n", roomName);
            Rp = searchRoom(flood, roomName, roomHead);
            if(Rp==NULL)
            {
                printf(" \t δ�ҵ�ƥ�䷿�䣬���������\n");
                Sleep(50);
                fprintf(historyFile, " \t δ�ҵ�ƥ�䷿�䣬���������\n");
                continue;
            }
            if(Rp->preNumb == Rp->maxNumb)
            {
                printf("\t ��ǰ������������ѡ���µķ���\n");
                Sleep(50);
                fprintf(historyFile, "\t ��ǰ������������ѡ���µķ���\n");
                continue;
            }
            else
            {
                do//ͬ��������
                {
                    printf("\t ����ѧ����Ϣ��\n");
                    Sleep(50);
                    fprintf(historyFile, "\t ����ѧ����Ϣ��\n");
                    do
                    {
                        printf("\t ѧ�ţ�");
                        Sleep(50);
                        fgets(tempMemb.basic_info.numb, N, stdin);
                        if(tempMemb.basic_info.numb[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.basic_info.numb[strlen(tempMemb.basic_info.numb)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.basic_info.numb[strlen(tempMemb.basic_info.numb)-1] = '\0';
                        }
                        //ѧ�Ų���
                        Sp = checkNumb(tempMemb.basic_info.numb, *stuHead);
                        if(Sp!=NULL)
                        {
                            printf("\t ��ѧ��ѧ���Ѵ���\n");
                            Sleep(50);
                            printf("\t ������Ϣ��\n\t\t ������%s\n\t\t ѧ�ţ�%s\n\t\t ¥�㣺%s\n\t\t ����ţ�%s\n\t\t ְλ��%s\n",
                                    Sp->basic_info.name, Sp->basic_info.numb, Sp->basic_info.flood,
                                    Sp->basic_info.room, Sp->basic_info.position);
                            Sleep(100);
                            printf("\t ��ϸ��Ϣ��\n\t\t �绰��%s\n\t\t ���գ�%s\n\t\t ��סʱ�䣺%s\n\t\t ʡ�ݣ�ֱϽ�У���%s\n\t\t ��ϸ��ַ��%s\n\n",
                                    Sp->detail_info.tel, Sp->detail_info.birthday, Sp->detail_info.recordate,
                                    Sp->detail_info.province, Sp->detail_info.Address);
                            Sleep(100);
                            break;
                        }
                        printf("\t ������");
                        Sleep(50);
                        fgets(tempMemb.basic_info.name, N, stdin);
                        if(tempMemb.basic_info.name[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.basic_info.name[strlen(tempMemb.basic_info.name)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.basic_info.name[strlen(tempMemb.basic_info.name)-1] = '\0';
                        }
                        printf("\t ����ְλ��");
                        Sleep(50);
                        fgets(tempMemb.basic_info.position , N, stdin);
                        if(tempMemb.basic_info.position[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.basic_info.position[strlen(tempMemb.basic_info.position)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.basic_info.position[strlen(tempMemb.basic_info.position)-1] = '\0';
                        }
                        printf("\t �绰��");
                        Sleep(50);
                        fgets(tempMemb.detail_info.tel, N, stdin);
                        if(tempMemb.detail_info.tel[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.detail_info.tel[strlen(tempMemb.detail_info.tel)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.detail_info.tel[strlen(tempMemb.detail_info.tel)-1] = '\0';
                        }
                        printf("\t ��סʱ�䣺");
                        Sleep(50);
                        fgets(tempMemb.detail_info.recordate, N, stdin);
                        if(tempMemb.detail_info.recordate[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.detail_info.recordate[strlen(tempMemb.detail_info.recordate)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.detail_info.recordate[strlen(tempMemb.detail_info.recordate)-1] = '\0';
                        }
                        printf("\t ���գ�");
                        Sleep(50);
                        fgets(tempMemb.detail_info.birthday, N, stdin);
                        if(tempMemb.detail_info.birthday[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.detail_info.birthday[strlen(tempMemb.detail_info.birthday)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.detail_info.birthday[strlen(tempMemb.detail_info.birthday)-1] = '\0';
                        }
                        printf("\t ʡ�ݣ�ֱϽ�У���");
                        Sleep(50);
                        fgets(tempMemb.detail_info.province, N, stdin);
                        if(tempMemb.detail_info.province[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.detail_info.province[strlen(tempMemb.detail_info.province)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.detail_info.province[strlen(tempMemb.detail_info.province)-1] = '\0';
                        }
                        printf("\t ��ϸ��ַ��");
                        Sleep(50);
                        fgets(tempMemb.detail_info.Address, M, stdin);
                        if(tempMemb.detail_info.Address[0] == '\n')
                        {
                            system("cls");
                            printf("\t******************************************************************\n\n");
                            Sleep(50);
                            printf("\t ��������������룺\n");
                            Sleep(50);
                            printf("\t ����ѧ����Ϣ��\n");
                            Sleep(50);
                            continue;
                        }
                        else if(tempMemb.detail_info.Address[strlen(tempMemb.detail_info.Address)-1]!='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            tempMemb.detail_info.Address[strlen(tempMemb.detail_info.Address)-1] = '\0';
                        }
                        Spr = malloc(sizeof(Student));
                        if(Spr==NULL)
                        {
                            printf("\t �ڴ治��\n");
                            exit(0);
                        }
                        else
                        {
                            strcpy(tempMemb.basic_info.flood, flood);
                            strcpy(tempMemb.basic_info.room, roomName);
                            tempMemb.next = NULL;
                            *Spr = tempMemb;
                            Spr->next = *stuHead;
                            *stuHead = Spr;
                            Rp->preNumb += 1;
                            printf("\t �Ǽǳɹ�\n\n");
                            Sleep(50);
                            fprintf(historyFile, "\t �Ǽ���ѧ��Ϊ��%s��ѧ��\n\n", Spr->basic_info.numb);
                        }
                    }while(Sp!=NULL);
                    printf("\t ����ת��ѡ�񣺣�1. ��ǰ������� 2. ѡ�����·��� 0. �˳���\n\t ");
                    Sleep(50);
                    fprintf(historyFile, "\t ����ת��ѡ�񣺣�1. ��ǰ������� 2. ѡ�����·��� 0. �˳���\n");
                    Schoice = getchar();
                    while((c=getchar())!=EOF&&c!='\n');
                    fprintf(historyFile, "\t %c\n", Schoice);
                    if(Schoice<'0'||Schoice>'2')
                    {
                        printf("\t ��������\n");
                        Sleep(50);
                        break;
                    }
                }while(Schoice=='1');
                if(Schoice=='2')
                {
                    goto RoomChange;
                }
                else if(Schoice=='0')
                {
                    return ;
                }
            }
        }
    }while(Fchoice=='1');
}
//4. ѧ����Ϣ����
void sortStudent(Student * stuHead)
{
    int i;
    int totalStu;
    char Fchoice, Schoice;
    char c;
    Student ** sortStart = NULL;
    Student * Sp = NULL;


    if(stuHead == NULL)
    {
        printf("\t ��ǰ��ѧ����Ϣ\n");
        Sleep(50);
        return ;
    }
    Sp = stuHead;
    totalStu = studentCount(stuHead);
    if(totalStu==1)
    {
        printf("\t ��ǰ����һλѧ��\n");
        Sleep(50);
        printf("\t %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n\n",
               "����", "ѧ��", "¥��", "�����", "ְλ",
               "�绰", "��סʱ��", "����", "ʡ��", "��ϸ��ַ");
        Sleep(50);
        printf("\t %-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n",
                Sp->basic_info.name,
                Sp->basic_info.numb,
                Sp->basic_info.flood,
                Sp->basic_info.room,
                Sp->basic_info.position,
                Sp->detail_info.tel,
                Sp->detail_info.recordate,
                Sp->detail_info.birthday,
                Sp->detail_info.province,
                Sp->detail_info.Address);
        Sleep(50);
        return;
    }
    sortStart = (Student **)calloc(totalStu, sizeof(Student *));
    for(i=0;i<totalStu&&Sp!=NULL;i++)
    {
        *(sortStart + i) = Sp;
        Sp = Sp->next;
    }
    if(i!=totalStu)
    {
        printf("\t ϵͳ����\n");
        Sleep(50);
        return ;
    }
    do
    {
        printf("\t ѡ��������������1. ѧ�� 2. ���� 3. ����� 4. ʡ�ݣ�\n\t ");
        Sleep(50);
        Fchoice = getchar();
        while((c=getchar())!=EOF&&c!='\n');
        if(Fchoice<'1'||Fchoice>'4')
        {
            printf("\t �������룬����ѡ��\n");
            Sleep(50);
        }
    }while(Fchoice<'1'||Fchoice>'4');
    do
    {
        printf("\t ѡ����Ϣ��ʾ��ʽ����1. �� 2. ��ϸ��\n\t ");
        Sleep(50);
        Schoice = getchar();
        while((c=getchar())!=EOF&&c!='\n');
        if(Schoice!='1'&&Schoice!='2')
        {
            printf("\t �������룬����ѡ��\n");
            Sleep(50);
        }
    }while(Schoice!='1'&&Schoice!='2');
    if(Fchoice=='1')
    {
        sortBySomeway(sortStart, totalStu, sortByNumb);
    }
    else if(Fchoice=='2')
    {
        sortBySomeway(sortStart, totalStu, sortByName);
    }
    else if(Fchoice=='3')
    {
        sortBySomeway(sortStart, totalStu, sortByRoom);
    }
    else if(Fchoice=='4')
    {
        sortBySomeway(sortStart, totalStu, sortByProvince);
    }
    //��ӡ��Ϣ
    system("cls");
    printf("\t******************************************************************\n\n");
    if(Schoice=='1')
    {
        printf("\t %-6s%-14s%-14s%-14s%-14s%-14s\n\n",
               "���", "����", "ѧ��", "¥��", "�����", "ְλ");
        Sleep(50);
    }
    else if(Schoice=='2')
    {
        printf("\t %-6s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n\n",
               "���", "����", "ѧ��", "¥��", "�����", "ְλ",
               "�绰", "��סʱ��", "����", "ʡ��", "��ϸ��ַ");
        Sleep(50);
    }
    for(i=0;i<totalStu;i++)
    {
        if(Schoice=='1')
        {
            printf("\t %-6d%-14s%-14s%-14s%-14s%-14s\n",
                    i+1,
                    (*(sortStart+i))->basic_info.name,
                    (*(sortStart+i))->basic_info.numb,
                    (*(sortStart+i))->basic_info.flood,
                    (*(sortStart+i))->basic_info.room,
                    (*(sortStart+i))->basic_info.position);
        }
        else if(Schoice=='2')
        {
            printf("\t %-6d%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%-14s%s\n",
                    i+1,
                    (*(sortStart+i))->basic_info.name,
                    (*(sortStart+i))->basic_info.numb,
                    (*(sortStart+i))->basic_info.flood,
                    (*(sortStart+i))->basic_info.room,
                    (*(sortStart+i))->basic_info.position,
                    (*(sortStart+i))->detail_info.tel,
                    (*(sortStart+i))->detail_info.recordate,
                    (*(sortStart+i))->detail_info.birthday,
                    (*(sortStart+i))->detail_info.province,
                    (*(sortStart+i))->detail_info.Address);
        }
    }
    free(sortStart);
}
//5. ������Ϣ�޸�
void changeRoom(Room ** roomHead, Student * stuHead, FILE * historyFile)
{
    char c;
    char Fchoice;
    char flood[N];
    char roomName[N];
    Room * Rp = NULL;
    Room * Rpr = NULL;
    Room * Rpm = NULL;
    Student * Sp = NULL;
    do
    {
        do
        {
            printf("\t ѡ���ܣ���1. �޸�  0. �������˵���\n\t ");
            Fchoice = getchar();
            while((c=getchar())!=EOF&&c!='\n');
            if(Fchoice!='0'&&Fchoice!='1')
            {
                system("cls");
                printf("\t******************************************************************\n\n");
                printf("\t ����ȷ����\n");
            }
        }while(Fchoice!='0'&&Fchoice!='1');
        fprintf(historyFile, "\t ѡ���ܣ���1. �޸�  0. �������˵���\n\t %c\n", Fchoice);
        if(Fchoice=='0')
        {
            return ;
        }
        else if(Fchoice=='1')//�޸�
        {
            printf("\t ������Ŀ�귿��¥�㣺");
            fprintf(historyFile, "\t ������Ŀ�귿��¥�㣺");
            fgets(flood, N, stdin);
            if(flood[0] == '\n')
            {
                printf("\t �������\n");
                continue;
            }
            else
            {
                if(flood[strlen(flood)-1]!='\n')
                {
                    while((c=getchar())!=EOF&&c!='\n');
                }
                else
                {
                    flood[strlen(flood)-1] = '\0';
                }
                fprintf(historyFile, "%s\n", flood);
                Rp = * roomHead;
                while(Rp!=NULL)
                {
                    if(strcmp(flood, Rp->flood)==0)
                    {
                        break;
                    }
                    else
                    {
                        Rp = Rp->next;
                    }
                }
                if(Rp==NULL)
                {
                    printf("\t δ�ҵ�\n");
                    fprintf(historyFile, "\t δ�ҵ�\n");
                    continue;
                }
                else
                {
                    Rpr = Rp;
                    printf("\t �����뷿��ţ�");
                    fprintf(historyFile, "\t �����뷿��ţ�");
                    fgets(roomName, N, stdin);
                    if(flood[0] == '\n')
                    {
                        printf("\t �������\n");
                        continue;
                    }
                    else//���Ҷ�Ӧ¥�����з���
                    {
                        if(roomName[strlen(roomName)-1] !='\n')
                        {
                            while((c=getchar())!=EOF&&c!='\n');
                        }
                        else
                        {
                            roomName[strlen(roomName)-1] = '\0';
                        }
                        fprintf(historyFile, "%s\n", roomName);
                        while(strcmp(Rpr->flood, flood)==0)
                        {
                            if(Rpr==NULL)
                            {
                                break;
                            }
                            else if(strcmp(Rpr->name, roomName)==0)
                            {
                                break;
                            }
                            else
                            {
                                Rpr = Rpr->next;
                                if(Rpr==NULL)
                                {
                                    break;
                                }
                            }
                        }
                        if(Rpr==NULL||strcmp(Rpr->flood, flood)!=0)
                        {
                            printf("\t δ�ҵ�\n");
                            fprintf(historyFile, "\t δ�ҵ�\n");
                            continue;
                        }
                        else//�ҵ���Ӧ����
                        {
                            char tempFchoice;
                            printf("\n\t ������Ϣ��\n");
                            fprintf(historyFile, "\n\t ������Ϣ��\n");
                            printf("\t\t ¥�㣺%s\n\t\t ����ţ�%s\n\t\t �����ס������%d\n\t\t ��ǰ��ס������%d\n\n",
                                    Rpr->flood, Rpr->name, Rpr->maxNumb, Rpr->preNumb);
                            fprintf(historyFile,
                                    "\t\t ¥�㣺%s\n\t\t ����ţ�%s\n\t\t �����ס������%d\n\t\t ��ǰ��ס������%d\n\n",
                                    Rpr->flood, Rpr->name, Rpr->maxNumb, Rpr->preNumb);
                            printf("\t ѡ����Ҫ�޸ĵ����ݣ���1. �����  2. �����ס������\n\t ");
                            fprintf(historyFile, "\t ѡ����Ҫ�޸ĵ����ݣ���1. �����  2. �����ס������\n\t ");
                            do
                            {
                                tempFchoice = getchar();
                                while((c=getchar())!=EOF&&c!='\n');
                                if(tempFchoice!='1'&&tempFchoice!='2')
                                {
                                    printf("\t �������룬�������룺");
                                }
                            }while(tempFchoice!='1'&&tempFchoice!='2');
                            fprintf(historyFile, "%c\n", tempFchoice);
                            if(tempFchoice=='1')
                            {
                                char tempName[N];
                                printf("\t �������µķ���ţ�");
                                fprintf(historyFile, "\t �������µķ���ţ�");
                                fgets(tempName, N, stdin);
                                if(tempName[0] == '\n')
                                {
                                    printf("\t ��������\n");
                                    fprintf(historyFile, "\t ��������\n");
                                    continue;
                                }
                                else if(tempName[strlen(tempName)-1]!='\n')
                                {
                                    while((c=getchar())!=EOF&&c!='\n');
                                }
                                else
                                {
                                    tempName[strlen(tempName)-1] = '\0';
                                }
                                fprintf(historyFile, "%s\n", tempName);
                                //�������ظ����
                                Rpm = Rp;
                                while(strcmp(Rp->flood, Rpm->flood)==0&&Rpm !=NULL)
                                {
                                    if(Rpm==Rpr)
                                    {
                                        Rpm = Rpm->next;
                                        continue;
                                    }
                                    else if(strcmp(tempName, Rpm->name)==0)
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        Rpm = Rpm->next;
                                    }
                                }
                                //�޸��ж�
                                if(Rpm==NULL||strcmp(Rp->flood, Rpm->flood)!=0)
                                {
                                    //ͬ���޸�ѧ����Ϣ
                                    if(Rpr->preNumb!=0)
                                    {
                                        Sp = stuHead;
                                        while(Sp!=NULL)
                                        {
                                            if(strcmp(Sp->basic_info.flood, Rpr->flood)==0)
                                            {
                                                if(strcmp(Sp->basic_info.room, Rpr->name)==0)
                                                {
                                                    strcpy(Sp->basic_info.room, tempName);
                                                }
                                                else
                                                {
                                                    Sp = Sp->next;
                                                }
                                            }
                                            else
                                            {
                                                Sp = Sp->next;
                                            }
                                        }
                                        printf("\t ѧ����Ϣͬ���޸ĳɹ�\n");
                                        fprintf(historyFile, "\t ѧ����Ϣͬ���޸ĳɹ�\n");
                                    }
                                    strcpy(Rpr->name, tempName);
                                    printf("\t ������޸ĳɹ�\n");
                                    fprintf(historyFile, "\t ������޸ĳɹ�\n");
                                }
                                else if(strcmp(tempName, Rpm->name)==0)
                                {
                                    printf("\t ������ͬ¥���Ѵ���\n");
                                    fprintf(historyFile, "\t ��������ͬ¥���Ѵ���\n");
                                }
                            }
                            else if(tempFchoice=='2')
                            {
                                char tempMax;
                                do
                                {
                                    printf("\t �����뷿���µ������ס������");
                                    tempMax = getchar();
                                    fprintf(historyFile, "\t �����뷿���µ������ס������%c\n", tempMax);
                                    while((c=getchar())!=EOF&&c!='\n');
                                    if(tempMax<'0'||tempMax>'8')
                                    {
                                        printf("\t ���������\n");
                                        fprintf(historyFile, "\t ���������\n");
                                    }
                                    else if((tempMax-'0')<Rpr->preNumb)
                                    {
                                        printf("\t ��ǰ�������� %c �ˣ���ɾ����Ա���޸�\n", Rpr->preNumb);
                                        fprintf(historyFile, "\t ��ǰ�������� %c �ˣ���ɾ����Ա���޸�\n", Rpr->preNumb);
                                        break;
                                    }
                                    else
                                    {
                                        Rpr->maxNumb = tempMax - '0';
                                        printf("\t �޸ĳɹ�\n");
                                        fprintf(historyFile, "\t �޸ĳɹ�\n");
                                        break;
                                    }
                                }while(tempMax<'0'||tempMax>'8');
                            }
                        }
                    }
                }
            }
        }
        printf("\n\t ���������");
        getchar();
        system("cls");
        printf("\t******************************************************************\n\n");
    }while(Fchoice=='1');
}
//6. ¥�ᡢ����Ա��Ϣ�޸�
void changeAdmin(char buildingName[], char adminName[], char adminPassword[], FILE * adminFile, FILE * historyFile)
{
    char c;
    int i;
    //��������¥��
    printf("\t ������¥�����ƣ�");
    Sleep(50);
    fprintf(historyFile, "\t ������¥�����ƣ�");
    fgets(buildingName,N,stdin);
    //δ����
    if(buildingName[0] == '\0'||buildingName[0] == '\n')
    {
        printf("\t δ���룬��ʼ��Ϊ��δ������\n");
        Sleep(50);
        strcpy(buildingName,"δ����");
    }
    else if(buildingName[strlen(buildingName)-1] != '\n')
    {
        while((c=getchar())!=EOF&&c!='\n');
    }
    else
    {
        buildingName[strlen(buildingName)-1] = '\0';
    }
    fprintf(historyFile, "%s\n", buildingName);
    //���ù���Ա����
    printf("\t �����ù���Ա������admin����");
    Sleep(50);
    fprintf(historyFile, "\t �����ù���Ա������admin����");
    fgets(adminName,N,stdin);
    //δ����
    if(adminName[0] == '\0'||adminName[0] == '\n')
    {
        printf("\t δ���룬��ʼ��Ϊ��admin��\n");
        Sleep(50);
        strcpy(adminName,"admin");
    }
    else if(adminName[strlen(adminName)-1] != '\n')
    {
        while((c=getchar())!=EOF&&c!='\n');
    }
    else
    {
        adminName[strlen(adminName)-1] = '\0';
    }
    fprintf(historyFile, "%s\n", adminName);
    //���ù���Ա����
    printf("\t �����ù���Ա��ʼ���루123456����");
    Sleep(50);
    fprintf(historyFile, "\t �����ù���Ա��ʼ���루123456���������벻�ɼ���\n");
    for(i=0; i<N; i++)
    {
        c = getch();
        if(i == N-1)
        {
            adminPassword[i] = '\0';
            break;
        }
        else if(isalnum(c))
        {
            adminPassword[i] = c;
            putchar('*');
        }
        else if(c == '\n'||c == '\r')
        {
            //δ����
            if(i==0)
            {
                printf("\t δ���룬��ʼ��Ϊ��123456��\n");
                Sleep(50);
                strcpy(adminPassword,"123456");
            }
            else
            {
                adminPassword[i] = '\0';
            }
            printf("\n");
            break;
        }
        else if(c == '\b')
        {
            if(i>0)
            {
                i -= 2;
                printf("\b");
            }
        }
        else
        {
            i--;
        }
    }
    //�����ļ�
    fprintf(adminFile, "%s\n", buildingName);
    fprintf(adminFile, "%s\n", adminName);
    fprintf(adminFile, "%s\n", adminPassword);
    fclose(adminFile);
}
//7. �����ļ�������Ա��ѧ����Ϣ��
void resetFile(FILE * roomFile, FILE * stuFile, Room * roomHead, Student * stuHead)
{
    Room * Rp;
    Student * Sp;
    Rp = roomHead;
    //д���ļ�
    while(Rp!=NULL)
    {
        fwrite(Rp, sizeof(Room), 1, roomFile);
        Rp = Rp->next;
    }
    fclose(roomFile);
    Sp = stuHead;
    //д���ļ�
    while(Sp!=NULL)
    {
        fwrite(Sp, sizeof(Student), 1, stuFile);
        Sp = Sp->next;
    }
    fclose(stuFile);
}
//8. ��ʼ��������Ϣ
void resetRoom(Room ** roomHead, Student ** stuHead)
{
    int i,j;
    int flood, room, numb;
    char c;
    Room * Rp, *Rpr;
    Student * Sp, *Spr;

    //�������
    Rp = *roomHead;
    while(Rp!=NULL)
    {
        Rpr = Rp;
        Rp = Rp->next;
        free(Rpr);
    }
    Sp = (*stuHead);
    while(Sp!=NULL)
    {
        Spr = Sp;
        Sp = Sp->next;
        free(Spr);

    }
    //������
    printf("\t ������¥������1-20������������1-50���뷿���������ޣ�1-8����������7 30 6��\n\t ");
    do
    {
        if(scanf("%d %d %d", &flood, &room, &numb)!=3)
        {
            while((c=getchar())!=EOF&&c!='\n');
            printf("\t ��������������룺");
            continue;
        }
        else if((flood<=0||flood>20)||(room<=0||room>50)||(numb<=0||numb>8))
        {
            while((c=getchar())!=EOF&&c!='\n');
            printf("\t �����������ֵ��");
            continue;
        }
        getchar();
    }
    while((flood<=0||flood>20)||(room<=0||room>50)||(numb<=0||numb>8));
    Rpr = NULL;
    //��ʼ��������Ϣ
    for(i=1; i<=flood; i++)
    {
        for(j=1; j<=room; j++)
        {
            Rp = (Room *)malloc(sizeof(Room));
            if(Rp == NULL)
            {
                printf("\t �ڴ治��\n");
                exit(0);
            }
            //¥��
            Rp->flood[0] = '0' + (i/10);
            Rp->flood[1] = '0' + (i%10);
            Rp->flood[2] = '\0';
            //�����
            Rp->name[0] = Rp->flood[0];
            Rp->name[1] = Rp->flood[1];
            Rp->name[2] = '0';
            Rp->name[3] = '0' + (j/10);
            Rp->name[4] = '0' + (j%10);
            Rp->name[5] = '\0';
            //����
            Rp->maxNumb = numb;
            Rp->preNumb = 0;
            Rp->next = NULL;
            if(i==1&&j==1)
            {
                *roomHead = Rp;
            }
            else
            {
                Rpr->next = Rp;
            }
            Rpr = Rp;
        }
    }
}
//9. ������¼�鿴
void printHistory(FILE * historyFile)
{
    char c;
    fseek(historyFile, 0, 0);       //�ƶ����
    while(!feof(historyFile))
    {
        c = fgetc(historyFile);
        if(c == '\n'||c == '\r')
        {
            Sleep(50);
        }
        putchar(c);
    }
}
//���ҷ���
Room * searchRoom(char flood[], char roomName[], Room * roomHead)
{
    Room * Rp = NULL;
    Rp = roomHead;
    while(Rp != NULL)
    {
        if(strcmp(Rp->flood, flood)==0)
        {
            if(strcmp(Rp->name, roomName)==0)
            {
                return Rp;
            }
            else
            {
                Rp = Rp->next;
            }
        }
        else
        {
            Rp = Rp->next;
        }
    }
    if(Rp==NULL)
    {
        return NULL;
    }
    return NULL;
}
//ѧ�Ų���
Student * checkNumb(char stuNumb[], Student * stuHead)
{
    Student * Sp = NULL;
    Sp = stuHead;
    while(Sp!=NULL)
    {
        if(strcmp(Sp->basic_info.numb, stuNumb)==0)
        {
            return Sp;
        }
        else
        {
            Sp = Sp->next;
        }
    }
    if(Sp==NULL)
    {
        return NULL;
    }
    return NULL;
}
//ѧ����Ϣ�޸�
void changeStu(Room * roomHead, Student * stuHead, Student * Sp, FILE * historyFile)
{
    char c;
    char Fchoice;
    char flood[N];
    char roomName[N];
    Room * Rp = NULL;

    do
    {
        printf("\t ѡ���޸ĵ����ݣ���1. ����  2. �绰  3. סַ��\n\t ");
        Sleep(50);
        Fchoice = getchar();
        while((c=getchar())!=EOF&&c!='\n');
        if(Fchoice<'1'||Fchoice>'3')
        {
            printf("\t �������룬����������\n");
            Sleep(50);
        }
    }while(Fchoice<'1'||Fchoice>'3');
    fprintf(historyFile, "\t ѡ���޸ĵ����ݣ���1. ����  2. �绰  3. סַ��\n\t %c\n", Fchoice);
    if(Fchoice=='1')
    {
        do
        {
            printf("\t ������Ŀ�귿��¥�㣺");
            Sleep(50);
            fgets(flood, N, stdin);
            if(flood[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(flood[strlen(flood)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                flood[strlen(flood)-1] = '\0';
            }
            printf("\t ������Ŀ�귿��ţ�");
            Sleep(50);
            fgets(roomName, N, stdin);
            if(roomName[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(roomName[strlen(roomName)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                roomName[strlen(roomName)-1] = '\0';
            }
            Rp = searchRoom(flood, roomName, roomHead);
            if(Rp==NULL)
            {
                printf("\t δ�ҵ���Ӧ����, ������ѡ��\n");
                Sleep(50);
                continue;
            }
        }while(Rp==NULL);
        fprintf(historyFile, "\t ������Ŀ�귿��¥�㣺%s\n", flood);
        fprintf(historyFile, "\t ������Ŀ�귿��ţ�%s\n", roomName);
        Rp->preNumb += 1;
        Rp = searchRoom(Sp->basic_info.flood, Sp->basic_info.room, roomHead);
        Rp->preNumb -= 1;
        strcpy(Sp->basic_info.flood, flood);
        strcpy(Sp->basic_info.room, roomName);
        printf("\t �޸ĳɹ�\n\n");
        Sleep(50);
        fprintf(historyFile, "\t �޸ĳɹ�\n\n");
    }
    else if(Fchoice=='2')
    {
        do
        {
            printf("\t �µĵ绰���룺");
            Sleep(50);
            fgets(Sp->detail_info.tel, N, stdin);
            if(Sp->detail_info.tel[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(Sp->detail_info.tel[strlen(Sp->detail_info.tel)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                Sp->detail_info.tel[strlen(Sp->detail_info.tel)-1] = '\0';
            }
        }while(Sp->detail_info.tel[0]=='\n');
        fprintf(historyFile, "\t �µĵ绰���룺%s\n", Sp->detail_info.tel);
        printf("\t �޸ĳɹ�\n\n");
        Sleep(50);
        fprintf(historyFile, "\t �޸ĳɹ�\n\n");
    }
    else if(Fchoice=='3')
    {
        do
        {
            printf("\t �µ�ʡ�ݣ�ֱϽ�У���");
            Sleep(50);
            fgets(Sp->detail_info.province, N, stdin);
            if(Sp->detail_info.province[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(Sp->detail_info.province[strlen(Sp->detail_info.province)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                Sp->detail_info.province[strlen(Sp->detail_info.province)-1] = '\0';
            }
        }while(Sp->detail_info.province[0]=='\n');
        do
        {
            printf("\t �µ���ϸ��ַ��");
            Sleep(50);
            fgets(Sp->detail_info.Address, N, stdin);
            if(Sp->detail_info.Address[0]=='\n')
            {
                printf("\t ��������\n");
                Sleep(50);
                continue;
            }
            else if(Sp->detail_info.Address[strlen(Sp->detail_info.Address)-1]!='\n')
            {
                while((c=getch())!=EOF&&c!='\n');
            }
            else
            {
                Sp->detail_info.Address[strlen(Sp->detail_info.Address)-1] = '\0';
            }
        }while(Sp->detail_info.Address[0]=='\n');
        fprintf(historyFile, "\t �µ�ʡ�ݣ�ֱϽ�У���%s\n", Sp->detail_info.province);
        fprintf(historyFile, "\t �µ���ϸ��ַ��%s\n", Sp->detail_info.Address);
        printf("\t �޸ĳɹ�\n\n");
        Sleep(50);
        fprintf(historyFile, "\t �޸ĳɹ�\n\n");
    }
}
//ѧ������ͳ��
int studentCount(Student * stuHead)
{
    int totalStu = 0;
    Student * Sp = NULL;
    Sp = stuHead;
    while(Sp!=NULL)
    {
        totalStu++;
        Sp = Sp->next;
    }
    return totalStu;
}
//��������
void sortBySomeway(Student ** sortStart, int n, int (* someWay)(Student * a, Student * b))
{
    int i, j;
    Student * changeSam = NULL;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(someWay(*(sortStart+j), *(sortStart+j+1))>0)
            {
                changeSam = *(sortStart+j);
                *(sortStart+j) = *(sortStart+j+1);
                *(sortStart+j+1) = changeSam;
            }
        }
    }
}
//ѧ������
int sortByNumb(Student * a, Student * b)
{
    return strcmp(a->basic_info.numb, b->basic_info.numb);
}
//��������
int sortByName(Student * a, Student * b)
{
    return strcmp(a->basic_info.name, b->basic_info.name);
}
//��������
int sortByRoom(Student * a, Student * b)
{
    return strcmp(a->basic_info.room, b->basic_info.room);
}
//ʡ�ݣ�ֱϽ�У�����
int sortByProvince(Student * a, Student * b)
{
    return strcmp(a->detail_info.province, b->detail_info.province);
}


#endif // _myhead_h_
