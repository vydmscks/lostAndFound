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
void clear() // 콘솔창 비우는 함수
{
    printf("\033[2J\033[H");
}
void readfile()
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
int main()
{
    clear();
    menu();
    return 0;
}

void menu()
{
    readfile();
    // 메인 메뉴
    printf("분실물 관리 시스템\n\n");
    printf("메인 메뉴\n");
    printf("1. 습득물 등록\n"); // 완료 - 표은찬
    printf("2. 습득물 목록\n"); // 완료 - 표은찬
    printf("3. 분실물 정보 조회\n"); // TODO - 홍길동
    printf("4. 수령 처리\n"); // TODO - 홍길동
    printf("0. 프로그램 종료\n\n");
    printf("이동할 메뉴 번호 입력: ");
    int menu;
    scanf("%d", &menu);
    clear();
    switch (menu)
    {
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
        break;

    default:
        break;
    }
}
void append()
{
    FILE* file;
    file = fopen("list.txt", "a");

    printf("분실물 관리 시스템\n\n");
    printf("습득물 등록\n");
    printf("습득 날짜를 입력하세요 (YYYY-MM-DD): ");
    char date[11]; scanf(" %s", date);
    printf("물품 이름을 입력하세요 (공백없이): ");
    char name[100]; scanf(" %s", name);
    printf("습득 장소를 입력하세요 (공백없이): ");
    char pplace[100]; scanf(" %s", pplace);
    printf("보관 장소를 입력하세요 (공백없이): ");
    char splace[100]; scanf(" %s", splace);
    fprintf(file, "날짜: %s | 물품명: %s | 습득장소: %s | 보관장소: %s\n", date, name, pplace, splace);
    printf("등록이 완료되었습니다. Enter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();getchar();
    fclose(file);
    clear();
    menu();
}
void view()
{
    printf("분실물 관리 시스템\n\n");
    printf("분실물 목록\n");
    for(int i=0;i<count;i++)
    {
        printf("%d. %s\n", i+1, names[i]);
    }
    printf("조회가 완료되었습니다. 오래된 정보는 표시되지 않을 수 있습니다.\nEnter 키를 눌러 메인 메뉴로 이동합니다.");
    getchar();getchar();
    clear();
    menu();
}
void search() //
{

}
void collect()
{

}