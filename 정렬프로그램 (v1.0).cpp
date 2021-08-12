#include <iostream>
#include <Windows.h>
#include <random>
#include <time.h>
#define BAR_SIZE 25

using namespace std;

int num[BAR_SIZE] = { 0 };

double result = NULL;

int main();

void SetConsoleView() {
	system("mode con:cols=110 lines=28");
	system("title 정렬 프로그램 (v 1.0)");
}

void CursorView() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 20; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = TRUE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void CursorHide() {
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y) {
	//x, y 좌표 설정
	COORD pos = { x,y };
	//커서 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int random_return() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(1, BAR_SIZE);

	return dis(gen);
}

void mix_num() {
	for (int i = 0;i < BAR_SIZE;++i) {
		num[i] = random_return();
	}
}

void start() {
	int x = 81, y = 4;
	gotoxy(x, y);
	cout << "------------------------\n";
	gotoxy(x, y + 1);
	cout << "|  정렬 프로그램 (v1.0) |\n";
	gotoxy(x, y + 2);
	cout << "------------------------\n";
	gotoxy(x, y + 4);
	cout << "      1. 버블정렬       \n";
	gotoxy(x, y + 6);
	cout << "      2. 선택정렬       \n";
	gotoxy(x, y + 8);
	cout << "      3. 삽입정렬       \n";
	gotoxy(x, y + 10);
	cout << "      4. 숫자섞기       \n";
	gotoxy(x, y + 12);
	cout << "      0. 종료           \n";
	gotoxy(x + 4, y + 14);
	cout << "입력 \n";
	gotoxy(x + 4, y + 17);
	printf("걸린시간 %.2lfs\n", result);
	gotoxy(x + 9, y + 14);
}

void DrawBar() {
	cout << "\n";
	for (int i = 0;i < BAR_SIZE;++i) {
		cout << "   ";
		for (int j = 0; j < BAR_SIZE; j++) {
			if (num[j] + i >= BAR_SIZE) {
				cout << "■ ";
			}
			else {
				cout << "   ";
			}
		}
		cout << "\n";
	}
}

void bubbleSort() {
	clock_t st, en;
	int tmp = NULL;

	system("cls");
	st = clock();
	for (int i = 0; i < BAR_SIZE - 1; i++) {
		for (int j = 0; j < BAR_SIZE - 1; j++) {
			if (num[j] > num[j + 1]) {
				tmp = num[j];
				num[j] = num[j + 1];
				num[j + 1] = tmp;
				tmp = NULL;
				CursorHide();
				DrawBar();
				start();
				Sleep(60);
				system("cls");
			}
		}
	}
	en = clock();
	result = (double)(en - st) / 1000;

	CursorHide();
	DrawBar();
	start();
	Sleep(2500);
	system("cls");
	main();
}

void selectionSort() {
	clock_t st, en;
	int tmp = NULL;

	system("cls");
	st = clock();
	for (int i = 0; i < BAR_SIZE; i++) {
		for (int j = 0; j < BAR_SIZE; j++) {
			if (num[i] < num[j]) {
				tmp = num[j];
				num[j] = num[i];
				num[i] = tmp;
				tmp = NULL;
				CursorHide();
				DrawBar();
				start();
				Sleep(60);
				system("cls");
			}
		}
	}
	en = clock();
	result = (double)(en - st) / 1000;

	CursorHide();
	DrawBar();
	start();
	Sleep(2500);
	system("cls");
	main();
}

void insertionSort() {
	clock_t st, en;
	int tmp = NULL, value;

	system("cls");
	st = clock();
	for (int i = 1; i < BAR_SIZE; i++) {
		value = num[i];
		int j = i - 1;
		for (; j > -1 && num[j] > value; j--) {
			num[j + 1] = num[j];
			CursorHide();
			DrawBar();
			start();
			Sleep(60);
			system("cls");
		}
		num[j + 1] = value;
	}
	en = clock();
	result = (double)(en - st) / 1000;

	CursorHide();
	DrawBar();
	start();
	Sleep(2500);
	system("cls");
	main();
}

int main() {
	int n = NULL;
	result = NULL;
	system("cls");
	SetConsoleView();
	mix_num();
	CursorHide();
	DrawBar();
	start();
	CursorView();
	cin >> n;
	if (n == 0) {
		cout << "\n\n\n\n\n";
		return 0;
	}
	else if (n == 1) {
		bubbleSort();
	}
	else if (n == 2) {
		selectionSort();
	}
	else if (n == 3) {
		insertionSort();
	}
	else if (n == 4) {
		main();
	}
	else {
		cout << "\n\n\n\n\n";
		return 0;
	}
}