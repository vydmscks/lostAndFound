#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char dates[100][14];
char names[100][100];
char pick_places[100][100];
char store_places[100][100];
int count=0;

void append();
void view();
void search();
void collect();
void menu();
int check_ctrl_d(char text[]);
int read_line(char text[], size_t size);
void clear() // 콘솔창 비우는 함수
{
    printf("\033[2J\033[H");
}
int check_ctrl_d(char text[]) // 입력 중 Ctrl+D를 누르면 메인 메뉴로 돌아가는 함수 => 최윤우
{
    if(strchr(text, 4) != NULL)
    {
        clear();
        menu();
        return 1;
    }
    return 0;
}
int read_line(char text[], size_t size) //습득물 등록할때 문자열이 정해진 형식에 맞게 들어왔는지 검사하는 함수 => 최윤우
{
    if (fgets(text, size, stdin) == NULL)   //문자열 입력받고, 만약 오류로 입력 안되면 0 반환
    {
        return 0;
    }

    if (strchr(text, '\n') != NULL) //입력받고 뒤에 '\n'있으면 NULL값으로 바꾸고 정상적인 반환이라는 뜻으로 1반환
    {
        text[strcspn(text, "\n")] = '\0';
        return 1;
    }

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)   //너무 길어서 배열에 다 들어가지 못하면 너무 길다는 뜻으로 -1 반환하고, 버퍼 비움
    {
    }
    return -1;
}
void readfile() //파일을 읽는 함수 => 표은찬
{
    count = 0;
    // 파일 선언
    FILE* file;
    file = fopen("list.txt", "r");

    // 습득날짜, 물품명, 습득장소, 보관장소를 각 배열에 저장
    char str[200]; // 한 줄을 임시로 저장하는 변수
    while (fgets(str, sizeof(str), file)) // 각 줄 불러오기
    {
    sscanf(str,
            "날짜: %13s | 물품명: %99s | 습득장소: %99s | 보관장소: %99s",
            dates[count],
            names[count],
            pick_places[count],
            store_places[count]); // 형식화된 데이터를 불러오기 위해 sscanf 사용

    count++; // 습득물 목록 반복문에서 사용하기 위한 변수
    }
}
int main()  //함수 실행하는 main 함수
{
    clear();
    menu();
    return 0;
}

void menu() //메인 메뉴 여는 함수 + 분실물 어떻게 할건지 결정(등록, 목록, 정보 조회, 수령 처리) => 표은찬
{
    readfile();
    // 메인 메뉴
    printf("분실물 관리 시스템\n\n");
    printf("메인 메뉴\n");
    printf("1. 습득물 등록\n"); // 완료 - 표은찬
    printf("2. 습득물 목록 조회\n"); // 완료 - 표은찬
    printf("3. 분실물 정보 조회\n"); // 완료 - 최윤우
    printf("4. 수령 처리\n"); // 완료 - 최승빈
    printf("0. 프로그램 종료\n\n");
    printf("이동할 메뉴 번호 입력: ");
    int men;
    scanf("%d", &men);
    getchar(); // 메뉴 번호 입력 후 남아 있는 Enter 키 제거
    clear();


    switch (men)
    {
    case 0:
        break;
    
    case 1:
        append();
        break;
    
    case 2:
        view();
        break;

    case 3:
        search();
        break;

    case 4:
        collect();

    default:
        printf("잘못된 메뉴 번호입니다. 다시 입력해 주세요.\n");
        printf("Enter 키를 눌러 메인 메뉴로 이동합니다.");
        getchar();
        clear();
        menu();
        
    }
}
void append()   //습득물 등록 함수 => 표은찬
{
    FILE* file;
    file = fopen("list.txt", "a");

    printf("분실물 관리 시스템\n\n");
    printf("습득물 등록\n");
    char date[12];
    while (1)
    {
        printf("습득 날짜를 입력하세요 (YYYY-MM-DD): ");
        int result = read_line(date, sizeof(date)); //-1,0,1 상태에 따라 3개중 1개 반환 

        if (result == 0)
        {
            fclose(file);
            return;
        }
        if (result == 1 && strlen(date) == 10 && date[4] == '-' && date[7] == '-') //정상적 입력 형식인지 확인
        {
            break;
        }

        printf("잘못된 형식입니다. YYYY-MM-DD 형식으로 다시 입력하세요.\n");
    }
    if(check_ctrl_d(date))
    {
        fclose(file);
        return;
    }

    char name[100];
    while (1)
    {
        printf("물품 이름을 입력하세요 (공백없이): ");
        int result = read_line(name, sizeof(name));
        if (result == 0)
        {
            fclose(file);
            return;
        }
        if (result == 1 && name[0] != '\0')
        {
            break;
        }
        printf("입력이 너무 길거나 비어 있습니다. 다시 입력하세요.\n");
    }
    if(check_ctrl_d(name))
    {
        fclose(file);
        return;
    }

    char pplace[100];
    while (1)
    {
        printf("습득 장소를 입력하세요 (공백없이): ");
        int result = read_line(pplace, sizeof(pplace));
        if (result == 0)
        {
            fclose(file);
            return;
        }
        if (result == 1 && pplace[0] != '\0')
        {
            break;
        }
        printf("입력이 너무 길거나 비어 있습니다. 다시 입력하세요.\n");
    }
    if(check_ctrl_d(pplace))
    {
        fclose(file);
        return;
    }

    char splace[100];
    while (1)
    {
        printf("보관 장소를 입력하세요 (공백없이): ");
        int result = read_line(splace, sizeof(splace));
        if (result == 0)
        {
            fclose(file);
            return;
        }
        if (result == 1 && splace[0] != '\0')
        {
            break;
        }
        printf("입력이 너무 길거나 비어 있습니다. 다시 입력하세요.\n");
    }
    if(check_ctrl_d(splace))
    {
        fclose(file);
        return;
    }
    fprintf(file, "날짜: %s | 물품명: %s | 습득장소: %s | 보관장소: %s\n", date, name, pplace, splace);
    printf("등록이 완료되었습니다. Enter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();
    fclose(file);
    clear();
    menu();
}
void view()     //등록된 분실물 목록 확인 => 표은찬
{
    printf("분실물 관리 시스템\n\n");
    printf("습득물 목록 조회\n");
    for(int i=0;i<count;i++)
    {
        printf("%d. %s\n", i+1, names[i]);
    }
    printf("전체 목록 조회가 완료되었습니다. 오래된 정보는 표시되지 않을 수 있습니다.\nEnter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();
    clear();
    menu();
}
void search()   //분실물 정보 조회 => 최윤우
{
    // 분실물 정보 조회 화면 출력
    printf("분실물 관리 시스템\n\n");
    printf("분실물 정보 조회\n");

    // 등록된 분실물 목록을 번호와 함께 출력
    for(int i=0;i<count;i++)
    {
        printf("%d. %s\n", i+1, names[i]);
    }

    // 사용자가 조회할 분실물 번호 입력
    printf("\n조회할 분실물 번호 입력: ");
    char input[100];
    scanf(" %s", input);
    if(check_ctrl_d(input))
    {
        return;
    }
    int num;
    sscanf(input, "%d", &num);

    if(num < 1 || num > count)
    {
        printf("잘못된 번호입니다. Enter 키를 눌러 메인 메뉴로 이동합니다.\n");
        getchar();
        getchar();
        clear();
        menu();
        return;
    }

    // 입력받은 번호에 해당하는 분실물 정보 출력
    clear();
    printf("분실물 관리 시스템\n\n");
    printf("분실물 정보 조회 결과\n");
    printf("습득 날짜: %s\n", dates[num-1]);
    printf("물품 이름: %s\n", names[num-1]);
    printf("습득 장소: %s\n", pick_places[num-1]);
    printf("보관 장소: %s\n", store_places[num-1]);

    // Enter 키를 누르면 메인 메뉴로 이동
    printf("\nEnter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();getchar(); //앞에 scanf받을때 enter 키 한번 빼고 enter 한번 더 받음
    clear();
    menu();
}
void collect()  //수령 처리 함수 => 최승빈
{
    printf("분실물 관리 시스템\n\n");
    printf("수령 처리\n");

    for(int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, names[i]);
    }

    printf("\n수령 완료된 물품 번호를 입력하세요: ");
    char input[100];
    scanf(" %s", input);
    if(check_ctrl_d(input))
    {
        return;
    }
    int num;
    sscanf(input, "%d", &num);

    if(num < 1 || num > count)
    {
        printf("잘못된 번호입니다. Enter 키를 눌러 메인 메뉴로 이동합니다.\n");
        getchar();
        getchar();
        clear();
        menu();
        return;
    }

    FILE *file = fopen("list.txt", "w");

    for(int i = 0; i < count; i++)
    {
        if(i != num - 1)
        {
            fprintf(file,
                    "날짜: %s | 물품명: %s | 습득장소: %s | 보관장소: %s\n",
                    dates[i],
                    names[i],
                    pick_places[i],
                    store_places[i]);
        }
    }

    fclose(file);

    printf("수령 처리가 완료되었습니다.\n");
    printf("Enter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();
    getchar();

    clear();
    menu();
}
