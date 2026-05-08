#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Cell
{
  int x, y;
  int dist;
};

bool isInside(int x, int y)
{
  return (x >= 1 && x <= 8 && y >= 1 && y <= 8);
}

int minKnightMoves(int startX, int startY, int targetX, int targetY)
{
  int dx[] = {-2, -1, 1, 2, -2, -1, 1, 2};
  int dy[] = {-1, -2, -2, -1, 1, 2, 2, 1};

  queue<Cell> q;
  q.push({startX, startY, 0});

  bool visited[9][9] = {false};
  visited[startX][startY] = true;

  while (!q.empty())
  {
    Cell current = q.front();
    q.pop();

    if (current.x == targetX && current.y == targetY)
      return current.dist;

    for (int i = 0; i < 8; i++)
    {
      int nextX = current.x + dx[i];
      int nextY = current.y + dy[i];

      if (isInside(nextX, nextY) && !visited[nextX][nextY])
      {
        visited[nextX][nextY] = true;
        q.push({nextX, nextY, current.dist + 1});
      }
    }
  }
  return -1;
}

int main()
{
  int moves = minKnightMoves(1, 1, 8, 8);
  cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\nМінімальна кількість ходів коня: " << moves << endl << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
  return 0;
}

