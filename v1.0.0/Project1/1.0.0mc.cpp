#include <iostream>
#include <conio.h>
#include <windows.h> // 用于Sleep()函数
#include <vector>
#include <cstdlib> // 用于rand()和srand()

// 定义游戏世界的大小
const int WORLD_WIDTH = 20;
const int WORLD_HEIGHT = 20;

// 游戏世界，使用二维数组表示
char world[WORLD_WIDTH][WORLD_HEIGHT];

// 玩家的初始位置
int playerX = WORLD_WIDTH / 2;
int playerY = WORLD_HEIGHT / 2;

// 初始化世界，创建一个简单的地形
void initializeWorld() {
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            if (x == 0 || x == WORLD_WIDTH - 1 || y == 0 || y == WORLD_HEIGHT - 1) {
                world[x][y] = '#'; // 边界
            }
            else {
                world[x][y] = ' '; // 空地
            }
        }
    }
    // 添加一些随机生成的障碍物
    srand(time(0)); // 随机数种子
    for (int i = 0; i < 10; ++i) {
        int x = rand() % WORLD_WIDTH;
        int y = rand() % WORLD_HEIGHT;
        if (x != playerX || y != playerY) { // 确保不在玩家位置
            world[x][y] = '#';
        }
    }
}

void renderWorld() {
    system("cls"); // 清屏
    for (int y = 0; y < WORLD_HEIGHT; ++y) {
        for (int x = 0; x < WORLD_WIDTH; ++x) {
            std::cout << world[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "Player position: (" << playerX << ", " << playerY << ")" << std::endl;
}

void handleInput() {
    char input = _getch(); // 读取一个字符，无需按回车
    switch (input) {
    case 'w': // 向上移动
        if (playerY > 0 && world[playerX][playerY - 1] == ' ') playerY--;
        break;
    case 's': // 向下移动
        if (playerY < WORLD_HEIGHT - 1 && world[playerX][playerY + 1] == ' ') playerY++;
        break;
    case 'a': // 向左移动
        if (playerX > 0 && world[playerX - 1][playerY] == ' ') playerX--;
        break;
    case 'd': // 向右移动
        if (playerX < WORLD_WIDTH - 1 && world[playerX + 1][playerY] == ' ') playerX++;
        break;
    default:
        break;
    }
}

int main() {
    initializeWorld(); // 初始化世界
    renderWorld(); // 渲染初始世界

    bool isRunning = true;
    while (isRunning) {
        handleInput();
        renderWorld();

        if (_kbhit()) { // 检查是否有按键按下
            char key = _getch();
            if (key == 'q') {
                isRunning = false; // 按 'q' 退出游戏
            }
        }
        Sleep(100); // 降低循环速度，以便看到渲染效果
    }
    return 0;
}