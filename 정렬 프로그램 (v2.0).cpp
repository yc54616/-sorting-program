#include <Windows.h>
#include <iostream>
#include <random>
#include <conio.h>
#define BAR_SIZE 25

using namespace std;

int num[BAR_SIZE] = { 0 };
char str[BAR_SIZE] = { 0 };

double result = NULL;

static int g_nScreenIndex;
static HANDLE g_hScreen[2];

int main();

void ConsoleSetting() 
{
	system("mode con:cols=110 lines=28");
	system("title 정렬 프로그램 (v 2.0)");

    CONSOLE_CURSOR_INFO cci;

    //화면 버퍼 2개를 만든다.
    g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    //커서 숨기기
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(g_hScreen[0], &cci);
    SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void ScreenFlipping()
{
    SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
    g_nScreenIndex = !g_nScreenIndex;
}

void ScreenClear()
{
    COORD Coor = { 0,0 };
    DWORD dw;
    FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
}

void ScreenPrint(int x, int y, char* string)
{
    DWORD dw;
    COORD CursorPosition = { x, y };
    SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
    WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);

}

void ScreenRelease()
{
    CloseHandle(g_hScreen[0]);
    CloseHandle(g_hScreen[1]);
}

int random_return() 
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, BAR_SIZE);

    return dis(gen);
}

void mix_num() 
{
    for (int i = 0;i < BAR_SIZE;++i) {
        num[i] = random_return();
    }
}

void start() 
{
    int x = 81, y = 4;
    sprintf(str, "------------------------");
    ScreenPrint(x, y, str);
    sprintf(str, "|  정렬 프로그램 (v2.0) |");
    ScreenPrint(x, y + 1, str);
    sprintf(str, "------------------------");
    ScreenPrint(x, y + 2, str);
    sprintf(str, "1. 버블정렬");
    ScreenPrint(x + 4, y + 4, str);
    sprintf(str, "2. 선택정렬");
    ScreenPrint(x + 4, y + 6, str);
    sprintf(str, "3. 삽입정렬");
    ScreenPrint(x + 4, y + 8, str);
    sprintf(str, "4. 정렬초기화");
    ScreenPrint(x + 4, y + 10, str);
    sprintf(str, "0. 종료");
    ScreenPrint(x + 4, y + 12, str);
    sprintf(str, "걸린시간 %.2lfs", result);
    ScreenPrint(x + 4, y + 17, str);
}

void DrawBar() 
{
    for (int i = 0;i < BAR_SIZE;++i) {
        for (int j = 0; j < BAR_SIZE; j++) {
            if (num[j] + i >= BAR_SIZE) {
                sprintf(str, "■");
                ScreenPrint(j*3+3, i+1, str);
            }
            else {
                sprintf(str, "  ");
                ScreenPrint(j*3+3, i+1, str);
            }
        }
    }
}

void bubbleSort() {
    clock_t st, en;
    int tmp = NULL;

    ScreenClear();
    st = clock();
    for (int i = 0; i < BAR_SIZE - 1; i++) {
        for (int j = 0; j < BAR_SIZE - 1; j++) {
            if (num[j] > num[j + 1]) {
                tmp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = tmp;
                tmp = NULL;

                ScreenClear();

                DrawBar();
                start();

                ScreenFlipping();
                Sleep(60);
            }
        }
    }
    en = clock();
    result = (double)(en - st) / 1000;
}

void selectionSort() {
    clock_t st, en;
    int tmp = NULL;

    ScreenClear();
    st = clock();
    for (int i = 0; i < BAR_SIZE; i++) {
        for (int j = 0; j < BAR_SIZE; j++) {
            if (num[i] < num[j]) {
                tmp = num[j];
                num[j] = num[i];
                num[i] = tmp;
                tmp = NULL;

                ScreenClear();

                DrawBar();
                start();

                ScreenFlipping();
                Sleep(60);
            }
        }
    }
    en = clock();
    result = (double)(en - st) / 1000;
}

void insertionSort() {
    clock_t st, en;
    int tmp = NULL, value;

    ScreenClear();
    st = clock();
    for (int i = 1; i < BAR_SIZE; i++) {
        value = num[i];
        int j = i - 1;
        for (; j > -1 && num[j] > value; j--) {
            num[j + 1] = num[j];

            ScreenClear();

            DrawBar();
            start();

            ScreenFlipping();
            Sleep(60);
        }
        num[j + 1] = value;
    }
    en = clock();
    result = (double)(en - st) / 1000;
}

int main() 
{
    ConsoleSetting();
    mix_num();
    while (1) {
        fflush(stdin);
        if (_kbhit()){
            int nKey = _getch();
            if (nKey == '0') {
                break;
            }
            else if (nKey == '1') {
                bubbleSort();
                fflush(stdin);
            }
            else if (nKey == '2') {
                selectionSort();
                fflush(stdin);
            }
            else if (nKey == '3') {
                insertionSort();
                fflush(stdin);
            }
            else if (nKey == '4') {
                mix_num();
                result = NULL;
                fflush(stdin);
            }
            else {
                break;
            }
        }

        ScreenClear();

        DrawBar();
        start();

        ScreenFlipping();
        Sleep(60);
    }

    ScreenRelease();

    return 0;
}