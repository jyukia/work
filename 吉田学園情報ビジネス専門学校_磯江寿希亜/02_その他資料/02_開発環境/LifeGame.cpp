//============================================
//
//作者　磯江寿希亜
// LifeGame
//
//============================================

#include<stdio.h>
#include<stdlib.h>

#include<conio.h>

#define FIELD_WIDTH 24
#define FIELD_HEIGHI 24

int cells[2][FIELD_HEIGHI][FIELD_WIDTH];	//フィールド検索生きているか死んでいるかの確認変数
int current;

int cursorX, cursorY;	//カーソル変数

//隣接する生きている生物のカウントを取得する関数
int getAdjacentLiveCount(int _x, int _y) {
	int count = 0;
	//x,yの相対座標	座標を求めるために使用
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++) {
			if ((x == 0) && (y == 0))	//原点をチェックしない
				continue;
			int x2 = (FIELD_WIDTH + _x + x) % FIELD_WIDTH;	//カーソルの座標受け X	　% <- 余りを受け付けて画面外を画面内に収める
			int y2 = (FIELD_HEIGHI + _y + y) % FIELD_HEIGHI;	//カーソルの座標受け Y
			count += cells[current][y2][x2];
		
		}

	return count;
}

//メイン関数
int main() {
	while (1) {
		system("cls");	//カーソルちらつきをキャンセルのため
		for (int y = 0; y < FIELD_HEIGHI; y++) {
			for (int x = 0; x < FIELD_WIDTH; x++)
				if ((x == cursorX) && (y == cursorY))	//マス目 カーソルの座標がカーソルの座標と一致したら
					printf("J");	//カーソル位置
				else
					printf("%s", cells[current][y][x] ? "■" : "・");
			//=============================================================
					//if((x == cursorX) && (y == cursorY))				//デバック使用
							//	printf("@");
							//else
							//	printf("%d", getAdjacentLiveCount(x,y));
			//=============================================================
			printf("\n");
		}	//for end

		//入力受付
		switch (_getch()) {
			//上下
		case 'w':	cursorY--; break;
		case 's':	cursorY++; break;
			//左右
		case 'a':	cursorX--; break;
		case 'd':	cursorX++; break;
			//space
		case ' ':	cells[current][cursorY][cursorX] ^= 1; break;

		case 0x1d:	//エスケープキーが押されたら
			for (int y = 0; y < FIELD_HEIGHI; y++)
				for (int x = 0; x < FIELD_WIDTH; x++) {
					cells[current][y][x] = 0;
				}
			break;
			//Enter	時間を進める
		case '\r':
			for (int y = 0; y < FIELD_HEIGHI; y++)
				for (int x = 0; x < FIELD_WIDTH; x++) {
					int n = getAdjacentLiveCount(x, y);	//生きているセル
					int next = cells[current][y][x];	//次のセルの状態は今のセルの状態で保存しておく
					if (cells[current][y][x]) {//生きていたら
						if ((n <= 1) || (n >= 4))
						{
							next = 0;
						}
					}
					else {//死んでいたら

						if (n == 3)
							next = 1;
					}
					cells[current ^ 1][y][x] = next;	//次の世代のセルに書き込む
				}
			current ^= 1;
			break;
		}
	}
}