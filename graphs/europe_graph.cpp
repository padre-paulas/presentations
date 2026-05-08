#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> bfs(const Graph& graph, const std::string& start, const std::string& target) {
  if (start == target) return {start};
  if (!graph.count(start) || !graph.count(target)) return {};

  std::queue<std::string> q;
  std::unordered_set<std::string> visited;
  std::unordered_map<std::string, std::string> parent;

  q.push(start);
  visited.insert(start);

  while (!q.empty()) {
    std::string current = q.front();
    q.pop();

    for (const auto& next : graph.at(current)) {
      if (visited.count(next)) continue;
      visited.insert(next);
      parent[next] = current;
      if (next == target) {
        std::vector<std::string> path;
        for (std::string node = target;; node = parent[node]) {
          path.push_back(node);
          if (node == start) break;
        }
        std::reverse(path.begin(), path.end());
        return path;
      }
      q.push(next);
    }
  }

  return {};
}

int main() {
  Graph graph = {
      {"Portugal", {"Spain"}},
      {"Spain", {"Portugal", "France"}},
      {"France", {"Spain", "Belgium", "Germany", "Italy"}},
      {"Belgium", {"France", "Germany", "Netherlands"}},
      {"Netherlands", {"Belgium", "Germany"}},
      {"Germany", {"Netherlands", "Belgium", "France", "Poland", "Czech Republic"}},
      {"Czech Republic", {"Germany", "Poland", "Austria"}},
      {"Austria", {"Czech Republic", "Italy"}},
      {"Italy", {"France", "Austria"}},
      {"Poland", {"Germany", "Czech Republic"}}
  };

  std::string from = "Portugal";
  std::string to = "Poland";
  auto path = bfs(graph, from, to);

  if (path.empty()) {
    std::cout << "No path found from " << from << " to " << to << '\n';
    return 0;
  }

  std::cout << "Shortest path from " << from << " to " << to << ":\n";
  for (std::size_t i = 0; i < path.size(); ++i) {
    std::cout << path[i];
    if (i + 1 < path.size()) std::cout << " -> ";
  }
  std::cout << '\n';
  return 0;
}
