#include <iostream>
#include <conio.h>
#include <windows.h> // ����Sleep()����
#include <vector>
#include <cstdlib> // ����rand()��srand()

// ������Ϸ����Ĵ�С
const int WORLD_WIDTH = 20;
const int WORLD_HEIGHT = 20;

// ��Ϸ���磬ʹ�ö�ά�����ʾ
char world[WORLD_WIDTH][WORLD_HEIGHT];

// ��ҵĳ�ʼλ��
int playerX = WORLD_WIDTH / 2;
int playerY = WORLD_HEIGHT / 2;

// ��ʼ�����磬����һ���򵥵ĵ���
void initializeWorld() {
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            if (x == 0 || x == WORLD_WIDTH - 1 || y == 0 || y == WORLD_HEIGHT - 1) {
                world[x][y] = '#'; // �߽�
            }
            else {
                world[x][y] = ' '; // �յ�
            }
        }
    }
    // ���һЩ������ɵ��ϰ���
    srand(time(0)); // ���������
    for (int i = 0; i < 10; ++i) {
        int x = rand() % WORLD_WIDTH;
        int y = rand() % WORLD_HEIGHT;
        if (x != playerX || y != playerY) { // ȷ���������λ��
            world[x][y] = '#';
        }
    }
}

void renderWorld() {
    system("cls"); // ����
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            std::cout << world[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Player position: (" << playerX << ", " << playerY << ")" << std::endl;
}

void handleInput() {
    char input = _getch(); // ��ȡһ���ַ������谴�س�
    switch (input) {
    case 'w': // �����ƶ�
        if (playerY > 0 && world[playerX][playerY - 1] == ' ') playerY--;
        break;
    case 's': // �����ƶ�
        if (playerY < WORLD_HEIGHT - 1 && world[playerX][playerY + 1] == ' ') playerY++;
        break;
    case 'a': // �����ƶ�
        if (playerX > 0 && world[playerX - 1][playerY] == ' ') playerX--;
        break;
    case 'd': // �����ƶ�
        if (playerX < WORLD_WIDTH - 1 && world[playerX + 1][playerY] == ' ') playerX++;
        break;
    default:
        break;
    }
}

int main() {
    initializeWorld(); // ��ʼ������
    renderWorld(); // ��Ⱦ��ʼ����

    bool isRunning = true;
    while (isRunning) {
        handleInput();
        renderWorld();

        if (_kbhit()) { // ����Ƿ��а�������
            char key = _getch();
            if (key == 'q') {
                isRunning = false; // �� 'q' �˳���Ϸ
            }
        }
        Sleep(100); // ����ѭ���ٶȣ��Ա㿴����ȾЧ��
    }
    return 0;
}