/* Project Title	:	Type Racer
 * Built By		:	Medam Sai Sirisha
 * This project is used for testing the typing speed of users and producing results on the basis of the performance.
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct user
{
    char username[50];
    int test_lesson;
    char test_level;
    int score;
    char accuracy[8];
    int time_limit;
    char words_per_m[6];
    char end_time[26];
    char time_start[26];
} user;

typedef struct rec
{
    char user_name[50];
    int score;
    char  accuracy[8];
    char words_per_m[6];
    char time[26];
} rec;

FILE *fileread, *filewrite,*fp;
user *user1;
int num ;
char str[8]="RESULTS";

void fetch_score(int);
void fetch_data();
void gotoxy(int, int);
void load_screen(char *);
void menu();
void print_layout();
int save_data();
void view_instruction();
void test_speed();
void test_lesson();
int take_input();
void view_ranker();


void print_layout()
{
    printf("\n------------------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t   TYPE RACER");
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
}

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void box(int x1, int y1, int x2, int y2)
{
    int i;
    for (i = x1; i < x2; i++)
    {
        gotoxy(i, y1);
        printf("%c", 205);
        gotoxy(i, y2);
        printf("%c", 205);
    }

    for (i = y1; i < y2; i++)
    {
        gotoxy(x1, i);
        printf("%c", 186);
        gotoxy(x2, i);
        printf("%c", 186);
    }

    gotoxy(x1, y1);
    printf("%c", 201);
    gotoxy(x1, y2);
    printf("%c", 200);
    gotoxy(x2, y1);
    printf("%c", 187);
    gotoxy(x2, y2);
    printf("%c", 188);
}

void print_user()
{
    print_layout();
    printf("\n\t\t\t\t\t  >>>>TEST YOUR SPEED %s<<<<",user1->username);
}

void load_screen(char *str)
{
    int  j,i;
    system("cls");
    gotoxy(5, 5);
    printf("\n\t\t\t\t   LOADING %s.....",str);
    gotoxy(40, 8);
    for (i = 1; i <= 15; i++)
    {
        for (j = 0; j <= 100000000; j++);
        printf("%c", 177);
    }
}
void print_lesson()
{
    char choice;
    int ch;
    fflush(stdin);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\nLESSONS FOR THE GAME");
    printf("\n1.Lesson 1(Consists of words)");
    printf("\n\ta) Easy : 120 seconds");
    printf("\n\tb) Medium : 90 seconds");
    printf("\n\tc) Hard : 60 seconds");
    printf("\n2.Lesson 2(Basic sentences)");
    printf("\n\ta) Easy : 120 seconds");
    printf("\n\tb) Medium : 90 seconds");
    printf("\n\tc) Hard : 60 seconds");
    printf("\n3.Lesson 3(Paragraphs)");
    printf("\n\ta) Easy : 120 seconds");
    printf("\n\tb) Medium : 90 seconds");
    printf("\n\tc) Hard : 60 seconds");
    printf("\n4.Back to Menu");

    printf("\nEnter your choice of lesson :");
    fflush(stdin);
    scanf("%d", &ch);

    switch(ch)
    {
    case 1:
        printf("\nEnter level:");
        scanf(" %c", &choice);
        switch(choice)
        {
        case 'a':
        case 'A':
            fileread=fopen("testlesson1e.txt", "r");
            break;

        case 'b':
        case 'B':
            fileread = fopen("testlesson1m.txt", "r");
            break;

        case 'c':
        case 'C':
            fileread = fopen("testlesson1e.txt", "r");
            break;

        default :
            menu();
        }
        break;

    case 2:
        printf("\nEnter level :");
        scanf("%c", &choice);
        switch (choice)
        {
        case 'a':
        case 'A':
            fileread = fopen("testlesson2e.txt", "r");
            break;

        case 'b':
        case 'B':
            fileread = fopen("testlesson2m.txt", "r");
            break;

        case 'c':
        case 'C':
            fileread = fopen("testlesson2h.txt", "r");
            break;

        default:
            menu();
        }
        break;

    case 3:
        printf("\nEnter level :");
        scanf("%c", &choice);
        switch (choice)
        {
        case 'a':
        case 'A':
            fileread = fopen("testlesson3e.txt", "r");
            break;

        case 'b':
        case 'B':
            fileread = fopen("testlesson3m.txt", "r");
            break;

        case 'c':
        case 'C':
            fileread = fopen("testlesson3h.txt", "r");
            break;

        default:
            menu();
        }
        break;

    case 4:
        menu();
    }

    if (fileread == NULL)
    {
        printf("\nError occurred !!!\nMake sure you enter a valid option\nTry again later!!!!\n");
        exit(0);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    user1->test_level = choice;
    user1->test_lesson = ch;
    if (user1->test_level == 'a' || user1->test_level == 'A')
    {
        user1->time_limit = 120;
    }
    else if (user1->test_level == 'b' || user1->test_level == 'B')
    {
        user1->time_limit = 90;
    }
    else
    {
        user1->time_limit = 10;
    }

    test_lesson();

}
int take_input()
{
    DWORD        mode;          /* Preserved console mode */
    INPUT_RECORD event;         /* Input event */
    BOOL         done = FALSE;  /* Program termination flag */

    /* File used to store input given by the user */
    fp = fopen("temp.txt", "w");


    /* Get the console input handle */
    HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );

    /* Preserve the original console mode */
    GetConsoleMode( hstdin, &mode );

    /* Set to no line-buffering, no echo, no special-key-processing */
    SetConsoleMode( hstdin, 0 );

    /* Give the user instructions */
    fprintf(fp,"\n");

    char szBuffer;
    DWORD dwCount;
    int charsToDelete = 1, typed_char = 0, flag = 0;
    off_t position;
    time_t end_time=time(NULL);
    time(&end_time);
    end_time+=user1->time_limit;
    time_t currtime=time(NULL);
    time(&currtime);

    while (!done)
    {
        if (WaitForSingleObject( hstdin, 0 ) == WAIT_OBJECT_0)  /* if kbhit */
        {
            time(&currtime);
            if(currtime<end_time)
            {
                if(GetAsyncKeyState(VK_END)||GetAsyncKeyState(VK_LBUTTON)||GetAsyncKeyState(VK_LCONTROL)||GetAsyncKeyState(VK_RCONTROL))
                {
                    done=TRUE;
                    flag = 1;
                }
                else if(GetAsyncKeyState(VK_RETURN))
                {
                    printf("\n");
                    fprintf(fp,"%c",'\n');
                }
                else if(GetAsyncKeyState(VK_BACK))
                {
                    fseeko64(fp,-charsToDelete,SEEK_END);
                    position = ftell(fp);
                    ftruncate(fileno(fp), position);
                }
                else
                {
                    ReadConsole( hstdin,&szBuffer, sizeof(szBuffer), &dwCount, NULL);
                    fprintf( fp, "%c",szBuffer);
                    printf( "%c",szBuffer);
                    typed_char++;
                }
            }
            else
            {
                done=TRUE;
                printf("\a");
                break;
            }
        }
    }

    /* Denotes input was terminated by pressing END followed by some character*/
    if(flag == 1)
    {
        fseeko64(fp,-charsToDelete,SEEK_END);
        position = ftell(fp);
        ftruncate(fileno(fp), position);
        return typed_char-1;
    }
    else
    {
        return typed_char;
    }
}

void test_lesson()
{
    system("cls");
    print_user();
    printf("\nTEST LESSON : %d\nLEVEL : %c)\n\n", user1->test_lesson, user1->test_level);
    char ch;

    printf("\nPress any alphabet to start(Esc to reselect the option)\n\nPress END key followed by any alphabet to stop giving input :)");
    printf("\n\nDon't use backspace\n");

    fflush(stdin);
    ch = _getch();

    if (ch == 27)
        print_lesson();
    else
    {
        time_t start_time = time(NULL);
        strcpy(user1->time_start, ctime(&start_time));
        user1->time_start[25] = '\0';
        printf("\nStarted time: %s\n", user1->time_start);
        printf("\nTime limit: %d\n",user1->time_limit);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    while ((ch = fgetc(fileread)) != EOF)
    {
        printf("%c", ch);

    }
    printf("\n\n\nStart!!!\n\n");
    fflush(stdin);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    int typed_char = take_input();

    fflush(stdin);
    time_t end_time = time(NULL);
    strcpy(user1->end_time, ctime(&end_time));
    user1->end_time[25] = '\0';

    printf("\nEnded time: %s\n", user1->end_time);
    fclose(fp);
    fflush(stdin);
    fetch_score(typed_char);
}

void fetch_score(int typed_char)
{
    char actual_char,typ_char,ch;
    int num_of_errors = 0;
    float words_per_m = 0;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    fp = fopen("temp.txt", "r");

    fseek(fileread, 0, SEEK_SET);

    user1->score = 0;
    typ_char = fgetc(fp);
    typ_char = fgetc(fp);
    typ_char = fgetc(fp);
    actual_char = fgetc(fileread);

    while (typ_char != EOF && actual_char != EOF)
    {
        if (typ_char == ' ')
        {
            words_per_m++;
        }
        if (typ_char == actual_char)
        {
            user1->score += 2;
        }
        else if(typ_char!=actual_char)
        {
            user1->score -= 1;
            num_of_errors++;
            printf("\nError -> Actual character %c , Entered character %c", actual_char, typ_char);
        }
        if (typ_char == '\n'||typ_char == '\r')
        {
            actual_char = fgetc(fileread);
        }
        typ_char = fgetc(fp);
        actual_char = fgetc(fileread);
    }
    fclose(fileread);
    fclose(fp);

    float accuracy = (float)(typed_char-num_of_errors)/ typed_char*100;

    if (user1->time_limit == 120)
        words_per_m/= 2;
    else if (user1->time_limit == 90)
        words_per_m/= 1.5;

    _gcvt(accuracy, 5, user1->accuracy);
    _gcvt(words_per_m, 4, user1->words_per_m);

    user1->accuracy[6]=45;
    user1->accuracy[7]='\0';
    user1->words_per_m[5]='\0';

    Sleep(2000);
    fflush(stdin);

    printf("\nPress Esc./Enter to continue......");
    ch = getchar();
    if (ch == 27 ||ch == '\r' || ch == '\n'||!feof(stdin))
        load_screen(str);

    system("cls");
    ch = '\0';

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    print_layout();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    printf("\n\t\t\t\t\t     >>>SCORE CARD<<< ");
    printf("\nUSERNAME : %s\nTEST TIME : %s\nTEST LESSON : %d\nTEST LEVEL : %c\n\n", user1->username, user1->time_start,user1->test_lesson,user1->test_level);
    printf("\nNUMBER OF ERRORS : %d\nSCORE : %d\nACCURACY : %s\nWORDS PER MINUTE : %s", num_of_errors, user1->score,user1->accuracy,user1->words_per_m);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    int res=save_data();

    if (res == 0)
        printf("\n\nRESULTS STORED SUCCESSFULLY");
    else
        printf("\nRESULTS WERE NOT STORED SUCCESSFULLY");

    printf("\nPress Esc./Enter to continue......");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    ch = _getch();

    if (ch == 27 || ch == 10)
        menu();
}

int save_data()
{
    filewrite = fopen("users.txt", "a");
    char counter[5],ch;
    int index=0;

    if (filewrite == NULL)
    {
        return -1;
    }
    else
    {
        fprintf(filewrite, "\n%s%c%d%c%s%c%s%c%s%c", user1->username,',',user1->score,',',user1->accuracy,',',user1->words_per_m,',',user1->time_start,'$');
        fclose(filewrite);
        return 0;
    }
    fclose(filewrite);
}

void test_speed()
{
    fflush(stdin);

    print_layout();

    user1 = (user*)malloc(sizeof(user) * 1);
    if (user1 == NULL)
    {
        printf("NO MEMORY ALLOCATED\n");
        exit(0);
    }

    printf("\nEnter the username (maximum 50 characters without space minimum 8 characters):\n");
    fflush(stdin);
    scanf("%s", user1->username);

    system("cls");
    print_user();
    print_lesson();
}

void fetch_data()
{
    rec record;

    int index=0;
    char ch,score[5];

    while((ch=fgetc(fileread))!=EOF)
    {
        index=0;
        if(ch=='$')
        {
            ch=fgetc(fileread);
        }
        while((ch=fgetc(fileread))!=',')
        {
            record.user_name[index]=ch;
            index++;
        }
        record.user_name[index]='\0';

        printf("\n%s",record.user_name);
        index=0;

        while((ch=fgetc(fileread))!=',')
        {
            score[index]=ch;
            index++;
        }
        score[index]='\0';
        record.score=atoi(score);
        printf("\t\t%d",record.score);
        index=0;

        while((ch=fgetc(fileread))!=',')
        {
            record.accuracy[index]=ch;
            index++;
        }
        record.accuracy[index]='\0';

        printf("\t%s",record.accuracy);
        index=0;

        while((ch=fgetc(fileread))!=',')
        {
            record.words_per_m[index]=ch;
            index++;
        }
        record.words_per_m[index]='\0';
        printf("\t\t %s \t",record.words_per_m);
        index=0;

        while((ch=fgetc(fileread))!= '$')
        {
            record.time[index]=ch;
            index++;
        }
        record.time[25]='\0';
        puts(record.time);

    }

}

void view_ranker()
{
    system("cls");
    print_layout();

    char ch;

    fileread = fopen("users.txt", "r");
    if (fileread == NULL)
    {
        printf("\nError opening file!!");
        menu();
    }

    printf("\n\nUSERNAME\t\tSCORE   ACCURACY\t W_P_M\t\tTIME");

    fetch_data();

    fflush(stdin);
    printf("\nPress Esc./Enter to continue......");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    ch = getchar();
    if (ch == 27 || ch == 10)
        menu();
}

void view_instruction()
{
    char ch;
    print_layout();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    printf("\nINSTRUCTIONS FOR THE GAME");
    printf("\n1.User is required to select a level before the test starts.");
    printf("\n2.Each test level has a time limit.");
    printf("\n\t Easy : 120 seconds");
    printf("\n\t Medium : 90 seconds");
    printf("\n\t Hard : 60 seconds");
    printf("\n3.User should use same username for further tests as well.");
    printf("\n4.User cannot retype the text once typed else score is reduced.");
    printf("\n5.User can quit the game any time by pressing END\n  followed by any alphabet.");
    printf("\n6.You can quit the test by choosing the quit option.\n");
    printf("\nPress Enter to continue......");
    fflush(stdin);

    ch = getchar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    if(ch==27||ch=='\r'||ch=='\n')
        menu();
}

void menu()
{
    char ch;

    do
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        system("cls");
        print_layout();
        printf("\n\n");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        box(35,5,80,20);

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
        gotoxy(10,5);

        printf("\n\n\t\t\t\t\t\t    MAIN MENU\n");
        printf("\n\t\t\t\t\t\t1.Test your speed");
        printf("\n\t\t\t\t\t\t2.Instructions");
        printf("\n\t\t\t\t\t\t3.View Statistics");
        printf("\n\t\t\t\t\t\t4.View All Records");
        printf("\n\t\t\t\t\t\t5.Exit/Quit");

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        printf("\n\n\n\n\t\t\t\t\tEnter choice:");

        fflush(stdin);
        scanf("%c", &ch);
        switch (ch)
        {
        case '1':
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            test_speed();
            system("cls");
            break;

        case '2':
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            view_instruction();
            system("cls");
            break;

        case '3':
            break;

        case '4':
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            view_ranker();
            system("cls");
            break;

        case '5':
            printf("\n\n");
            exit(0);
        }

    }
    while (ch != '5');
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    menu();
    return 0;
}
