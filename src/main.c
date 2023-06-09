#include "myhead.h"

int main()
{

    /**
     *��������
     */
    char choice;                            //����ѡ��
    char adminName[N] = "admin";            //����Ա����
    char adminPassword[N] = "123456";       //����Ա����
    char buildingName[N] = "δ����";        //¥������
    FILE * adminFile = NULL;                //����Ա��Ϣ�ļ�����
    FILE * roomFile = NULL;                 //�����ļ�����
    FILE * stuFile = NULL;                  //ѧ���ļ�����
    FILE * historyFile = NULL;              //������¼�ļ�����
    Student * stuHead = NULL;               //ѧ������ͷ
    Room * roomHead = NULL;                 //��������ͷ

    //�ļ���
    adminFile = fopen("����Ա��Ϣ.txt", "r");
    historyFile = fopen("������¼.txt", "w+");
    if(historyFile==NULL)
    {
        printf("\t �ļ�����ʧ�ܣ�\n");
        //�ļ��ر�
        fclose(adminFile);
        exit(0);
    }
    //����Ƿ���ʹ�ü�¼
    if(adminFile == NULL)
    {
        printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        fprintf(historyFile, "\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        Sleep(50);
        adminFile = fopen("����Ա��Ϣ.txt", "w");
        changeAdmin(buildingName, adminName, adminPassword, adminFile, historyFile);
        system("cls");
        printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        printf("\t �Ƿ�����������Ϣ����1. ��\t0. ��\n");
        fprintf(historyFile, "\t �Ƿ�����������Ϣ����1. ��\t0. ��\n");
        printf("\t ");
        fprintf(historyFile, "\t ");
        do
        {
            char c;
            choice = getchar();
            while((c=getchar())!=EOF&&c!='\n');
            if(choice!='0'&&choice!='1')
            {
                printf("\t ����������������루1 / 0��\n\t ");
                fprintf(historyFile, "%c\n", choice);
                fprintf(historyFile, "\t ����������������루1 / 0��\n\t ");
            }
        }while(choice!='0'&&choice!='1');
        fprintf(historyFile, "%c\n", choice);
        if(choice == '1')
        {
            resetRoom(&roomHead, &stuHead);
        }
        system("cls");
    }
    else
    {
        //��ȡ��Ϣ
        fgets(buildingName, N, adminFile);
        buildingName[strlen(buildingName)-1] = '\0';
        fgets(adminName, N, adminFile);
        adminName[strlen(adminName)-1] = '\0';
        fgets(adminPassword, N, adminFile);
        adminPassword[strlen(adminPassword)-1] = '\0';
        fclose(adminFile);
        //ϵͳ��½
        printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        fprintf(historyFile, "\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        printf("\t ����Ա������֤\n");
        fprintf(historyFile, "\t ����Ա������֤\n");
        while(!(checkPassword(adminPassword, historyFile)))
        {
            system("cls");
            printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
            printf("\t ������������� QAQ \n");
            fprintf(historyFile, "\t ������������� QAQ \n");
            Sleep(50);
        }
        //��������
        roomFile = fopen("������Ϣ.txt", "r");
        stuFile = fopen("ѧ����Ϣ.txt", "r");
        if(roomFile!=NULL && stuFile!=NULL)
        {
            importData(roomFile, stuFile, &roomHead, &stuHead);
        }
    }

    //�������ֲʵ�
    /**

    if(strcmp(adminPassword, "20000713")==0)
    {
        PlaySound("bgm.wav", NULL, SND_LOOP|SND_ASYNC);
    }
    */
    /**
     *����ѭ��
     */
    do
    {
        printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        fprintf(historyFile, "\n\n");
        printMenu();
        Sleep(50);
        printf("\t ��ѡ��");
        do
        {
            char c;
            choice = getchar();
            while((c=getchar())!=EOF&&c!='\n');
            if(choice<'0'||choice>'9')
            {
                system("cls");
                printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
                printMenu();
                printf("\t ����ȷ����\n\t ");
            }
        }while(choice<'0'||choice>'9');
        if(choice == '0')
        {
            printf("\t ��ӭ�´�ʹ�ã�\tHave a good day!\n");
            break;
        }
        if(choice != '9')
        {
            fprintf(historyFile, "\t ѡ���˹��ܣ�%c\n\n", choice);
        }
        system("cls");
        printf("\t******¥�᣺%-20s����Ա��%-20s******\n\n", buildingName, adminName);
        switch(choice)
        {
            case '1'://������Ϣ�鿴
                viewMainInfo(roomHead);
                fprintf(historyFile, "\t �鿴�˷�����Ϣ�������ԣ�\n");
                break;
            case '2'://ѧ����Ϣ��ѯ���޸���ɾ��
                searchStu(roomHead, &stuHead, historyFile);
                break;
            case '3'://ѧ����Ϣ¼��
                addStudent(roomHead, &stuHead, historyFile);
                break;
            case '4'://ѧ����Ϣ����
                sortStudent(stuHead);
                fprintf(historyFile, "\t ������ѧ����Ϣ���������ԣ�\n");
                break;
            case '5'://������Ϣ�޸�
                changeRoom(&roomHead, stuHead, historyFile);
                break;
            case '6'://����Ա��Ϣ�޸�
                fprintf(historyFile, "\t ���Թ���Ա��Ϣ�޸�\n");
                while(!(checkPassword(adminPassword, historyFile)))
                {
                    printf("\t ������������� QAQ \n");
                    fprintf(historyFile, "\t ������������� QAQ \n");
                    Sleep(50);
                }
                adminFile = fopen("����Ա��Ϣ.txt", "w");
                changeAdmin(buildingName, adminName, adminPassword, adminFile, historyFile);
                /**�ʵ�����
                if(strcmp(adminPassword, "20000713")==0)
                {
                    PlaySound("bgm.wav", NULL, SND_LOOP|SND_ASYNC);
                }
                else
                {
                    PlaySound(NULL, NULL, SND_LOOP|SND_ASYNC);
                }
                */
                printf("\t �޸ĳɹ�\n");
                break;
            case '7'://�����ļ���ѧ����Ϣ��
                roomFile = fopen("������Ϣ.txt", "w");
                stuFile = fopen("ѧ����Ϣ.txt", "w");
                resetFile(roomFile, stuFile, roomHead, stuHead);
                printf("\t ���³ɹ�\n");
                fprintf(historyFile, "\t ��������Ϣ�ļ�\n");
                break;
            case '8'://��ʼ��¥����Ϣ
                resetRoom(&roomHead, &stuHead);
                printf("\t ��ʼ���ɹ�\n");
                fprintf(historyFile, "\t ��ʼ���˷�����Ϣ\n");
                break;
            case '9'://������¼�鿴
                printf("\n\n\t ��ʷ��\n");
                printHistory(historyFile);
                fprintf(historyFile, "\t ѡ���˹��ܣ�9\n");
                fprintf(historyFile, "\t �鿴��ʷ����������ʡ�ԣ�\n\n");
                break;
        }
        printf("\n\t ��������ز˵�");
        getchar();
        system("cls");
    }while(choice != 0);

    //�ļ��ر�
    fclose(adminFile);
    fclose(roomFile);
    fclose(stuFile);
    fclose(historyFile);
    return 0;
}
