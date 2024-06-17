#include <iostream>
#include <iomanip>
using namespace std;
#define MAXROW 10
#define MAXCOL 25
#define DEAD 0
#define ALIVE 1
int map[MAXROW][MAXCOL], newmap[MAXROW][MAXCOL];
int Generation;

// 函數原型宣告
void init();
int Neighbor(int, int);
void outputmap();
void Copymap();

int main()
{
    int row, col;
    char ans;

    init(); /*起始map*/
    outputmap();
    do
    {
        /*計算每一個(row,col)之cell的鄰居個數依此個數計算下一代的生死
        將下一代的map*/
        for (row = 0; row < MAXROW; row++)
            for (col = 0; col < MAXCOL; col++)
                switch (Neighbor(row, col))
                {
                case 0: /*孤單死*/
                case 1:
                case 4: /*擁擠死*/
                case 5:
                case 6:
                case 7:
                case 8:
                    newmap[row][col] = DEAD;
                    break;
                case 2:
                    newmap[row][col] = map[row][col];
                    break;
                case 3:
                    newmap[row][col] = ALIVE;
                    break;
                }

        Copymap(); /*將newmap copy to map*/
        do
        {
            cout << "\nContinue next Generation (y/n)?";
            ans = toupper(getchar()); // 避免大小寫衝突
            while (getchar() != '\n')
                continue;
            if (ans == 'Y' || ans == 'N')
                break;
        } while (1);

        if (ans == 'Y')
            outputmap();

    } while (ans == 'Y'); // 實作bug(輸入成小寫y導致不會繼續

    cout << "\n";
    return 0;
}

void init()
{
    int row, col;
    for (row = 0; row < MAXROW; row++)
        for (col = 0; col < MAXCOL; col++)
            map[row][col] = DEAD;

    cout << "Game of life Program\n";
    cout << "Enter(x,y)to select where(x,y) is a living cells";
    cout << "0 <= x <= " << MAXROW - 1 << ", 0 <= y <=" << MAXCOL - 1 << "\n";
    cout << "Terminate with (x,y)=(-1,-1)\n";
    /*輸入活細胞位置,以(-1,-1)結束輸入*/
    do
    {
        cout << "請輸入 x,y 座標點";
        cin >> row;
        cin >> col;
        while (getchar() != '\n')
            continue;
        if (0 <= row && row < MAXROW && 0 <= col && col < MAXCOL)
            map[row][col] = ALIVE;
        else
            cout << "(x,y)exceeds map ranage!\n";
    } while ((row != -1 || col != -1));
}

int Neighbor(int row, int col)
{
    int count = 0, c, r;
    /*計算每一個cell的鄰居個數,因為cell本身也被當作鄰居計算,故最後還需調整*/
    for (r = row - 1; r <= row + 1; r++)
        for (c = col - 1; c <= col + 1; c++)
        {
            if (r < 0 || r >= MAXROW || c < 0 || c >= MAXCOL)
                continue;
            if (map[r][c] == ALIVE)
                count++;
        }
    // 調整鄰居個數
    if (map[row][col] == ALIVE)
        count--;
    return count;
}

// 顯示目前細胞狀態
void outputmap()
{
    int row, col;
    cout << "\n\n"
         << setw(0) << ' ' << "Game of life cell status\n";
    cout << setw(20) << ' ' << "------Generation " << ++Generation << "-------\n";
    for (row = 0; row < MAXROW; row++)
    {
        cout << "\n"
             << setw(20) << ' ';
        for (col = 0; col < MAXCOL; col++)
            if (map[row][col] == ALIVE)
                putchar('@');
            else
                putchar('-');
    }
}

// 將newmap copy to map
void Copymap()
{
    int row, col;
    for (row = 0; row < MAXROW; row++)
        for (col = 0; col < MAXCOL; col++)
            map[row][col] = newmap[row][col];
}