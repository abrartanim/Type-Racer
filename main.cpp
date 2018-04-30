/* Project Title	:	Type Racer
 * Built By		:	Medam Sai Sirisha
 * This project is used for testing the typing speed of users and producing results on the basis of the performance.
 * The user has three levels having different time limits.The timer works based on the key events.
 * User's scores are displayed as a graph and he can check his performance or growth using statistics options.
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
#include"tutor.h"

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


/*Function to print header*/
void print_layout()
{
    printf("\n------------------------------------------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t   TYPE RACER");
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
}

/*Function to set cursor position*/
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

void tips()
{
  print_layout();

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

  char ch;
  printf("\n1.KEEP YOUR EYES ON THE MONITOR\n\t You will learn the key position faster if you don't look at keyboard while typing.");
  printf("\n2.KEEP WRISTS UP\n\tKeep your wrists up and straight when typing.\n\tResting your wrist on the wrist rest or the desk will make it difficult to move your hands.");
  printf("\n3.FOCUS ON ACCURACY\n4.RELAXED POSTURE\n5.TAKE BREAKS");

  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
  printf("\n\nPress Esc./Enter to continue...");
  fflush(stdin);
  scanf("%c",&ch);
  if(ch==27||ch==10)
    menu();
}

void print_user()
{
    print_layout();
    printf("\n\t\t\t\t\t  >>>>TEST YOUR SPEED %s<<<<",user1->username);
}

/*Load screen*/
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
            fileread = fopen("testlesson1h.txt", "r");
            break;

        default :
            menu();
        }
        break;

    case 2:
        printf("\nEnter level :");
        scanf(" %c", &choice);
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
        scanf(" %c", &choice);
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

    /*Check whether file opened successfully or not*/
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
        user1->time_limit = 60;
    }

    test_lesson();

}

int take_input(int *time_taken,int *sound)
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

    fprintf(fp,"\n");

    char szBuffer;
    DWORD dwCount;

    //Delete extra characters from end of file if the user has quit the program using END option.
    int charsToDelete = 2, typed_char = 0, flag = 0;
    off_t position;

    /*Sets the time limit for the user*/
    time_t start_time=time(NULL);
    time(&start_time);
    time_t end_time;
    end_time=start_time+user1->time_limit;
    time_t currtime=time(NULL);
    time(&currtime);

    while (!done)
    {
        if (WaitForSingleObject( hstdin, 0 ) == WAIT_OBJECT_0)  /* if kbhit */
        {
            //Measures the current time when keyboard is hit
            time(&currtime);

            if(*sound==1)
              {
                  Beep(3087,1*5);
              }
            if(currtime<end_time)
            {
                /*Disallow the user to copy the contents using Ctrl or Mouse left click button*/

                if(GetAsyncKeyState(VK_END)||GetAsyncKeyState(VK_LBUTTON)||GetAsyncKeyState(VK_LCONTROL)||GetAsyncKeyState(VK_RCONTROL))
                {
                    done=TRUE;
                    flag = 1;
                }
                else if(GetAsyncKeyState(VK_RETURN))//Check whether the enter key is pressed or not
                {
                    printf("\n");
                    fprintf(fp,"%c",'\n');
                }
                else if(GetAsyncKeyState(VK_BACK))
                {
                    fseeko64(fp,-charsToDelete,SEEK_CUR);
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

                /*Produces an audible alert when timer expires*/
                Beep(2450,1*1000);
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
        *time_taken = currtime-start_time;
        return typed_char-1;
    }
    else
    {
        *time_taken = user1->time_limit;
        return typed_char;
    }
}

void test_lesson()
{
    char ch;
    int sound=1;
    int time_taken=0;

    system("cls");
    print_user();
    printf("\nTEST LESSON : %d\nLEVEL : %c)\n\n", user1->test_lesson, user1->test_level);

    fflush(stdin);
    printf("Sound(ON[1]/OFF[2]):\n");
    scanf("%d",&sound);
    printf("\nPress any alphabet to start(Esc to reselect the option)\n\nPress END key followed by any alphabet to stop giving input :)\n");

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
    printf("\n\nStart!!!\n");
    fflush(stdin);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    int typed_char = take_input(&time_taken,&sound);

    fflush(stdin);
    time_t end_time = time(NULL);
    strcpy(user1->end_time, ctime(&end_time));
    user1->end_time[25] = '\0';

    printf("\nEnded time: %s\n\n", user1->end_time);
    fclose(fp);
    fflush(stdin);
    fetch_score(typed_char,time_taken);
}

void print_score(int num_of_errors,float accuracy,float wpm)
{
   int gd = DETECT, gm;
   char dest[]="X:\\TC\\BGI",title[]="SCORE CARD",msg[]="PRESS ANY KEY TO CLOSE",x[]="X",y[]="Y",o[]="O";
   initgraph(&gd, &gm,dest );

   outtext(msg);
   settextstyle(BOLD_FONT,HORIZ_DIR,2);
   outtextxy(510,20,title);

   setlinestyle(SOLID_LINE,0,2);
   /* Draw X and Y Axis */
   line(90,410,90,50);
   line(90,410,590,410);
   line(85,60,90,50);
   line(95,60,90,50);
   line(585,405,590,410);
   line(585,415,590,410);

   outtextxy(65,60,y);
   outtextxy(570,420,x);
   outtextxy(70,415,o);
   /* Draw bars on screen */
   setfillstyle(XHATCH_FILL, YELLOW);

   int maxy=getmaxy();
   char score[]="SCORE",err[]="ERRORS",acc[]="ACCURACY",w_p_m[]="W_P_M";

   bar(150,maxy-200-user1->score,200,410);
   outtextxy(145,410,score);
   bar(225,maxy-70-num_of_errors,275,410);
   outtextxy(220,410,err);
   bar(320,(maxy-70-(int)accuracy),370,410);
   outtextxy(300,410,acc);
   bar(420,(maxy-70-(int)wpm),470,410);
   outtextxy(415,410,w_p_m);

   getch();
   closegraph();
}

/*Fetch score depending on the number of characters typed and errors occurred*/
void fetch_score(int typed_char,int time_taken)
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
        else if(typ_char!=actual_char && typ_char!='\n' && typ_char!='\r')
        {
            user1->score -= 1;
            num_of_errors++;
            printf("\nError -> Actual character %c , Entered character %c", actual_char, typ_char);
        }
        if(typ_char=='\n'||typ_char=='\r')
        {
            actual_char=fgetc(fileread);
            typ_char=fgetc(fp);
            typ_char=fgetc(fp);
        }
        typ_char = fgetc(fp);
        actual_char = fgetc(fileread);
    }
    fclose(fileread);
    fclose(fp);

    float accuracy = (float)(typed_char-num_of_errors)/ typed_char*100;

    if (time_taken > 90 && time_taken <= 120)
        words_per_m/= 2;
    else if (time_taken > 60 && time_taken <= 90)
        words_per_m/= 1.5;

    /*Converts accuracy and words_per_minute into strings for storing in files*/
    _gcvt(accuracy, 5, user1->accuracy);
    _gcvt(words_per_m, 4, user1->words_per_m);

    user1->accuracy[6]=45;
    user1->accuracy[7]='\0';
    user1->words_per_m[5]='\0';

    Sleep(3000);
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
    printf("\nUSERNAME : %s\nTEST TIME : %s\nTIME TAKEN  :  %d seconds\n\nTEST LESSON : %d\nTEST LEVEL : %c\n\n", user1->username, user1->time_start,time_taken,user1->test_lesson,user1->test_level);
    printf("\nNUMBER OF ERRORS : %d\nSCORE : %d\nACCURACY : %s\nWORDS PER MINUTE : %s", num_of_errors, user1->score,user1->accuracy,user1->words_per_m);

    print_score(num_of_errors,accuracy,words_per_m);
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

/*Saves data to the users.txt file and in  case of failure returns -1*/
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

/*Fetch data of all users to display*/
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

void view_all_rec()
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

void print_keyboard()
{
   char msg[]="PRESS ANY KEY TO CLOSE";
   char fingerpos[]="FINGER POSITIONS";
   char text[]="In their basic position,your fingers rest on middle row of the keyboard - also called the 'home row'.";
   char text1[]="Now place your fingers on the home row :",text2[]="1.Put your left hand fingers on keys A S D F (as in pic)";
   char text3[]="2.Put your right hand fingers on keys J K L ;",text4[]="3.Let the thumbs rest on space bar",text5[]="4.Keep your wrists straight and fingers lightly curled.";
   char tip[]="Tip:The bumps on letter F and J help you find the home row without looking at hands";

   initwindow(1000,700,"FINGER POSITION");
   readimagefile("keyboard_finger.jpg",100,20,900,500);

   setcolor(LIGHTRED);
   outtext(msg);
   outtextxy(450,505,fingerpos);
   outtextxy(150,530,text);
   outtextxy(150,550,text1);
   outtextxy(170,570,text2);
   outtextxy(170,590,text3);
   outtextxy(170,610,text4);
   outtextxy(170,630,text5);
   outtextxy(150,670,tip);

   getch();
   closegraph();
   fflush(stdout);
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
    printf("\n3.User should use same user name for further tests as well.");
    printf("\n4.User can choose the SOUND ON/OFF option by using numbers 1/2 .");
    printf("\n5.User will be prompted with a beep sound when timer expires.Make sure your speakers are ON!!!:)");
    printf("\n6.User can quit the game any time by pressing END followed by any alphabet.\n");
    printf("\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    print_keyboard();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\nPress Enter to continue......");
    fflush(stdin);

    ch = getchar();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    if(ch==27||ch=='\r'||ch=='\n')
        menu();
}

/*Searches for the number of records of a particular user and returns -1 if not found*/
int search_user_name(char *name,int *arr,int *num)
{
    fileread=fopen("users.txt","r");
    char ch;
    if(fileread==NULL)
    {
        printf("\nError opening file");
        return -1;
    }
    else
    {
        //search for the user;
        char user[50],ch,score[5];
        int arr_ind=0;
        while((ch=fgetc(fileread))!=EOF)
        {
            int index=0;

            while((ch=fgetc(fileread))!=',')
            {
                user[index]=ch;
                index++;
            }
            user[index]='\0';

            if(strcmp(name,user)==0)
            {
                index=0;

                while((ch=fgetc(fileread))!=',')
                {
                    score[index]=ch;
                    index++;
                }
                score[index]='\0';

                arr[arr_ind]=atoi(score);
                arr_ind++;
                (*num)++;

                while((ch=fgetc(fileread))!='$');
            }
            else
            {
                while(fgetc(fileread)!='$');
            }
        }
        if(*num==0)
            return -1;
        else
            return 0;
    }
}

/*Prints graph of a particular user depending on the scores*/
void print_graph(int *arr,int *num)
{
    int gd = DETECT, gm;
    int maxx,maxy;
    int x1=30,y1=450,x2=100,y2=350;
    char location[]="C:\\TC\\BGI";
    char x_axis[]="TEST TAKEN";
    char name[]="SCORE",message[]="PRESS ANY KEY TO CLOSE THE GRAPH!!!!",x[]="X",y[]="y";

    initgraph(&gd, &gm,location);

    /* Sets the paint color to light blue */
    setcolor(LIGHTCYAN);

    /*Draws x axis and y axis*/
    line(0,450,600,450);
    line(30,590,30,30);
    line(25,40,30,30);
    line(35,40,30,30);
    line(600,445,605,450);
    line(600,455,605,450);

    maxx=getmaxx();
    maxy=getmaxy();
    settextstyle(SANS_SERIF_FONT,0,2);

    setcolor(LIGHTMAGENTA);

    outtextxy(15,35,y);
    outtextxy(590,460,x);
    outtextxy(maxx/2-30,460,x_axis);
    outtextxy(maxx-100,maxy-450,name);

    setcolor(LIGHTGREEN);

    int index=0;
    for(index=0; index<=*num; index++)
    {
        line(x1,y1,x2,y2);
        x1=x2;
        y1=y2;
        if(arr[index]<0)
        {
           y2=450;
           x2=x1+(100-(*num/10)*10);
        }
        else
        {
           y2=maxy-arr[index];
           x2=x1+(100-(*num/10)*10);
        }
    }

    setcolor(WHITE);
    outtext(message);
    getch();
    closegraph();
}

void view_records_by_name()
{
    print_layout();
    char ch;
    char search_user[50];
    int arr[100],num=0;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

    printf("\nEnter user name to be searched for:");
    scanf("%s",search_user);

    int res = search_user_name(search_user,arr,&num);

    if(res == -1)
    {
        printf("\nUSER NOT FOUND\n\n");
    }
    else
    {
        print_graph(arr,&num);
        float avg;

        int index=0,sum=0;
        for(index=0;index<num;index++)
        {
            sum=sum+arr[index];
        }
        avg=sum/num;

        if(avg<0)
        {
            printf("\nBADGE : ---");
        }
        else if(avg>=0&&avg<25)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            printf("\nBADGE : BRONZE");
        }
        else if(avg>=25&&avg<50)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            printf("\nBADGE : SILVER");
        }
        else if(avg>=50&&avg<75)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            printf("\nBADGE : GOLD");
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            printf("\nBADGE : PLATINUM");
        }
    }

    fflush(stdout);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\n\nPress Enter to continue......");
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
        printf("\n\t\t\t\t\t\t5.Learning Tips");
        printf("\n\t\t\t\t\t\t6.Exit/Quit");

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
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            view_records_by_name();
            system("cls");
            break;

        case '4':
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            view_all_rec();
            system("cls");
            break;

        case '5':
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
            tips();
            system("cls");
            break;

        case '6':
            printf("\n\n");
            exit(0);
        }

    }
    while (ch != '6');
}

int main()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    menu();
    return 0;
}
