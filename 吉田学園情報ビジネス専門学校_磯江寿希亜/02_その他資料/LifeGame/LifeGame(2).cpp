//============================================
//
//��ҁ@��]����
// LifeGame
//
//============================================

#include<stdio.h>
#include<stdlib.h>

#include<conio.h>

#define FIELD_WIDTH 24
#define FIELD_HEIGHI 24

int cells[2][FIELD_HEIGHI][FIELD_WIDTH];	//�t�B�[���h���������Ă��邩����ł��邩�̊m�F�ϐ�
int current;

int cursorX, cursorY;	//�J�[�\���ϐ�

//�אڂ��鐶���Ă��鐶���̃J�E���g���擾����֐�
int getAdjacentLiveCount(int _x, int _y) {
	int count = 0;
	//x,y�̑��΍��W	���W�����߂邽�߂Ɏg�p
	for (int y = -1; y <= 1; y++)
		for (int x = -1; x <= 1; x++) {
			if ((x == 0) && (y == 0))	//���_���`�F�b�N���Ȃ�
				continue;
			int x2 = (FIELD_WIDTH + _x + x) % FIELD_WIDTH;	//�J�[�\���̍��W�� X	�@% <- �]����󂯕t���ĉ�ʊO����ʓ��Ɏ��߂�
			int y2 = (FIELD_HEIGHI + _y + y) % FIELD_HEIGHI;	//�J�[�\���̍��W�� Y
			count += cells[current][y2][x2];
		
		}

	return count;
}

//���C���֐�
int main() {
	while (1) {
		system("cls");	//�J�[�\����������L�����Z���̂���
		for (int y = 0; y < FIELD_HEIGHI; y++) {
			for (int x = 0; x < FIELD_WIDTH; x++)
				if ((x == cursorX) && (y == cursorY))	//�}�X�� �J�[�\���̍��W���J�[�\���̍��W�ƈ�v������
					printf("J");	//�J�[�\���ʒu
				else
					printf("%s", cells[current][y][x] ? "��" : "�E");
			//=============================================================
					//if((x == cursorX) && (y == cursorY))				//�f�o�b�N�g�p
							//	printf("@");
							//else
							//	printf("%d", getAdjacentLiveCount(x,y));
			//=============================================================
			printf("\n");
		}	//for end

		//���͎�t
		switch (_getch()) {
			//�㉺
		case 'w':	cursorY--; break;
		case 's':	cursorY++; break;
			//���E
		case 'a':	cursorX--; break;
		case 'd':	cursorX++; break;
			//space
		case ' ':	cells[current][cursorY][cursorX] ^= 1; break;

		case 0x1d:	//�G�X�P�[�v�L�[�������ꂽ��
			for (int y = 0; y < FIELD_HEIGHI; y++)
				for (int x = 0; x < FIELD_WIDTH; x++) {
					cells[current][y][x] = 0;
				}
			break;
			//Enter	���Ԃ�i�߂�
		case '\r':
			for (int y = 0; y < FIELD_HEIGHI; y++)
				for (int x = 0; x < FIELD_WIDTH; x++) {
					int n = getAdjacentLiveCount(x, y);	//�����Ă���Z��
					int next = cells[current][y][x];	//���̃Z���̏�Ԃ͍��̃Z���̏�Ԃŕۑ����Ă���
					if (cells[current][y][x]) {//�����Ă�����
						if ((n <= 1) || (n >= 4))
						{
							next = 0;
						}
					}
					else {//����ł�����

						if (n == 3)
							next = 1;
					}
					cells[current ^ 1][y][x] = next;	//���̐���̃Z���ɏ�������
				}
			current ^= 1;
			break;
		}
	}
}