#pragma once
#include "Paint.h"
#include "Libs.h"
#include "Process.h"


/* Vẽ phần lựa chọn
   k là lựa chọn, 1 là người, 2 là máy, 3 là thoát */
void Luachon(int k) {

	//Đổi màu chữ
	SetColor(11);
	DrawCaRo(5, 50); //Vẽ chữ CARO
	Gotoxy(12, 48); 
	if (k == 1) SetColor(10);
	else        SetColor(15);
	cout << "1. Player1 vs Player2";
	Gotoxy(14, 48);
	if (k == 2) SetColor(10);
	else        SetColor(15);
	cout << "2. Player vs Computer";
	Gotoxy(16, 48);
	if (k == 3) SetColor(10);
	else        SetColor(15);
	cout << "3. Exit";
	
	SetColor(14);
	Gotoxy(20, 38);
	cout << ">> Arrow to up and down, Enter to choose <<";

	/* ---------------------------------- */

	//Nhập từ bàn phím vô ch
	int ch = _getch();
	switch (ch)
	{
		case 224: 
			ch = _getch();
			if (ch == 72) Luachon((k + 1) % 3 + 1); //Mũi tên lên, trừ k
			else
				if (ch == 80) Luachon((k % 3 + 1)); //Mũi tên xuống, cộng k
				else Luachon(k); //Mũi tên qua lại thì k giữ nguyên
			break;
		case 13:
			if (k == 1) PlayerWithPlayer(); //Người chơi
			else if (k == 2) PlayerWithCom(); //Máy chơi
			break;
		default: Luachon(k); break; //Nhập ký tự khác thì k giữ nguyên
	}
}

//tạo dòng chữ chớp nháy
void flashstring(char dongchu[], int x, int y)
{
	while (!_kbhit())
	{
		Gotoxy(x, y);
		cout << dongchu;
		Sleep(300);
		Gotoxy(x, y);
		cout << "                             ";
		Sleep(300);
	}
}

/* Xuất kết quả bằng biến res, 3 là hòa,
   1 là người thứ nhất, 2 là người thứ 2 */
void XuatKQ(int Res) {
	SetColor(13);
	/* ---------------------------------- */
	switch (Res) {
		case 1:
			flashstring("   PLAYER1 IS THE WINNER", 17, 90);
			break;
		case 2:
			flashstring("   PLAYER2 IS THE WINNER", 17, 90);
			break;
		case 3:
			flashstring("      DRAW!", 17, 90);
			break;
	}

	//Chờ người chơi Enter
	char c;
	do {
		c = _getch();
	} while (c != 13);

	//Rồi gọi lại hàm Luachon
	system("cls");
	Luachon(1);
}

/* Xuất kết quả bằng biến res, 3 là hòa,
1 là người chơi thắng, 2 là máy thắng*/
void XuatKQ_com(int Res) {
	SetColor(13);
	/* ---------------------------------- */
	switch (Res) {
	case 1:
		flashstring("    PLAYER IS THE WINNER", 17, 90);
		break;
	case 2: 
		flashstring("  COMPUTER IS THE WINNER", 17, 90); 
		break;
	case 3:
		flashstring("      DRAW!", 17, 90);
		break;
	}

	//Chờ người chơi Enter
	char c;
	do {
		c = _getch();
	} while (c != 13);

	//Rồi gọi lại hàm Luachon
	system("cls");
	Luachon(1);
}

/* Đây là mấy thứ liên quan tới bàn cờ */
#pragma region Bancothings

//Vẽ chữ CARO to tướng ấy
void DrawCaRo(int offsetX, int offsetY) {
	int C[MaxN] = { 32, 219, 220, 223, 222, 221 };
	int Caro[MaxN][MaxN] = {
		{ 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0 },
		{ 1, 0, 0, 1, 0, 4, 0, 5, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 2, 1, 0, 1, 2, 5, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 3, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 3, 3, 0 }
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 20; j++) {
			if (Caro[i][j]) {
				Gotoxy(i + offsetX, j + offsetY);
				cout <<char(C[Caro[i][j]]);
			}
		}
	}
}

//Vẽ bàn cờ
void Vebanco(int N, int M) {
	system("cls");
	SetColor(88);

	//vẽ dòng đầu
	cout << char(201) << char(205) << char(205) << char(205);
	for (int j = 1; j < M-1; j++) cout << char(203) << char(205) << char(205) << char(205);
	cout << char(203) << char(205) << char(205) << char(205) << char(187) << endl;
	//mấy dòng giữa
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < M; j++) cout << char(186) << "   ";
		cout << char(186) << endl;

		cout << char(204) << char(205) << char(205) << char(205);
		for (int j = 1; j < M-1; j++) cout << char(206) << char(205) << char(205) << char(205);
		cout << char(206) << char(205) << char(205) << char(205) << char(185) << endl;
	}
	//vẽ dòng cuối
	for (int j = 0; j < M; j++) cout << char(186) << "   ";
	cout << char(186) << endl;
	cout << char(200) << char(205) << char(205) << char(205);
	for (int j = 1; j < M - 1; j++) cout << char(202) << char(205) << char(205) << char(205);
	cout << char(202) << char(205) << char(205) << char(205) << char(188) << endl;
}

#pragma endregion

/* Mấy thứ liên quan tới di chuyển của người chơi */
#pragma region Move
void Up(int &x, int y) {
	if (x > 0) x--;
	else x = Row - 1;
}

void Down(int &x, int y) {
	if (x < Row - 1) x++;
	else x = 0;
}

void Left(int x, int &y) {
	if (y > 0) y--;
	else y = Column - 1;
}

void Right(int x, int &y) {
	if (y < Column - 1) y++;
	else y = 0;
}

//Mỗi lần di chuyển qua chỗ khác thì phải vẽ lại cái ô ngay đó
void ReDraw(int PlayerCom[MaxN][MaxN], int x, int y) {
	Gotoxy(x * 2 + 1, y * 4 + 2);
	if (PlayerCom[x][y] == 0) cout << ' ';
	if (PlayerCom[x][y] == 1) {
		SetColor(10);
		cout << 'X';
	}
	if (PlayerCom[x][y] == 2) {
		SetColor(12);
		cout << 'O';
	}
}

//Quản lý di chuyển và đánh của người chơi
bool Move(int PlayerCom[MaxN][MaxN], int &x, int &y, int color) {

	//Đến ô [x][y], vẽ ra con trỏ
	Gotoxy(x * 2 + 1, y * 4 + 2);
	cout << char(219);

	//Chờ người chơi 
	int c = _getch();
	/* ---------------------------------- */
	/* Người chơi đã nhập, thì vẽ lại cái ô 
	   đó trước khi làm việc khác */
	ReDraw(PlayerCom, x, y);
	SetColor(color);
	/* ---------------------------------- */
	switch (c) {
	case 13: 
		//Bấm Enter, nếu ô đó chưa có cờ thì đánh
		return PlayerCom[x][y] == 0? true : Move(PlayerCom, x, y, color); 
		break;
	case 224: 
		//224 là phím di chuyển
		c = _getch();
		if (c == 72) Up(x, y); 
		else if (c == 80) Down(x, y); 
		else if (c == 75) Left(x, y); 
		else if (c == 77) Right(x, y); 
		break;
	}

	//Nếu ko đánh mà là di chuyển thì gọi lại tiếp
	return Move(PlayerCom, x, y, color);
}
#pragma endregion
