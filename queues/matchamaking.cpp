#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Player
{
  std::string name;
  int mmr;
  double waitTime;

  bool operator<(const Player &other) const
  {
    return mmr < other.mmr;
  }
};

class Matchmaker
{
private:
  std::priority_queue<Player> lobby;

public:
  void addPlayer(Player p)
  {
    lobby.push(p);
    std::cout << "Гравець " << p.name 
    << " увійшов у чергу (MMR: " << p.mmr << ")\n";
  }

  void findMatch()
  {
    if (lobby.size() >= 2)
    {
      Player p1 = lobby.top();
      lobby.pop();
      Player p2 = lobby.top();
      lobby.pop();

      std::cout << "--- МАТЧ ЗНАЙДЕНО ---\n";
      std::cout << p1.name << " VS " << p2.name << "\n";
      std::cout << "Різниця в MMR: " << abs(p1.mmr - p2.mmr) << "\n\n";
    }
    else
    {
      std::cout << "Недостатньо гравців для початку...\n";
    }
  }
};

int main()
{
  Matchmaker system;
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
  system.addPlayer({"CyberCat", 1500, 0.5});
  system.addPlayer({"NoobMaster99", 1200, 1.2});
  system.addPlayer({"ProGamer2026", 1550, 0.1});
  system.addPlayer({"Nazer0001", 1100, 0.4});

  system.findMatch();
  std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;

  return 0;
}

