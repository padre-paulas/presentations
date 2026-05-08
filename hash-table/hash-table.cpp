#include <iostream>
#include <string>
#include <vector>

struct Equipment {
  std::string name;
  std::string category;
  std::string material;
  double weight;
  double price;
};

class EquipmentHashTable {
public:
  explicit EquipmentHashTable(size_t size = 16);

  void insert(const Equipment &item);
  bool remove(const std::string &name);
  const Equipment *find(const std::string &name) const;
  void printAll() const;
  void printStats() const;

private:
  size_t tableSize;
  size_t count;
  std::vector<std::vector<Equipment>> buckets;

  size_t hash(const std::string &key) const;
  double loadFactor() const;
  void resize();
};

EquipmentHashTable::EquipmentHashTable(size_t size)
    : tableSize(size), count(0), buckets(size) {}

size_t EquipmentHashTable::hash(const std::string &key) const {
  size_t h = 5381;
  for (char c : key)
    h = h * 33 ^ static_cast<size_t>(c);
  return h % tableSize;
}

double EquipmentHashTable::loadFactor() const {
  return static_cast<double>(count) / tableSize;
}

void EquipmentHashTable::resize() {
  size_t newSize = tableSize * 2;
  std::vector<std::vector<Equipment>> newBuckets(newSize);
  for (const auto &bucket : buckets)
    for (const auto &item : bucket) {
      size_t h = 5381;
      for (char c : item.name)
        h = h * 33 ^ static_cast<size_t>(c);
      newBuckets[h % newSize].push_back(item);
    }
  tableSize = newSize;
  buckets = std::move(newBuckets);
  std::cout << "[Resized to " << tableSize << " buckets]\n";
}

void EquipmentHashTable::insert(const Equipment &item) {
  if (loadFactor() > 0.75)
    resize();
  size_t index = hash(item.name);
  for (auto &existing : buckets[index]) {
    if (existing.name == item.name) {
      existing = item;
      return;
    }
  }
  buckets[index].push_back(item);
  ++count;
}

bool EquipmentHashTable::remove(const std::string &name) {
  auto &bucket = buckets[hash(name)];
  for (size_t i = 0; i < bucket.size(); ++i) {
    if (bucket[i].name == name) {
      bucket.erase(bucket.begin() + i);
      --count;
      return true;
    }
  }
  return false;
}

const Equipment *EquipmentHashTable::find(const std::string &name) const {
  for (const auto &item : buckets[hash(name)])
    if (item.name == name)
      return &item;
  return nullptr;
}

void EquipmentHashTable::printAll() const {
  std::cout << "\n=== Sports Equipment Inventory ===\n";
  for (size_t i = 0; i < tableSize; ++i)
    for (const auto &item : buckets[i])
      std::cout << "[bucket " << i << "] "
                << item.name << " | " << item.category
                << " | " << item.material
                << " | " << item.weight << "kg"
                << " | $" << item.price << "\n";
  std::cout << "Total items: " << count << "\n";
}

void EquipmentHashTable::printStats() const {
  size_t usedBuckets = 0, maxChain = 0;
  for (const auto &bucket : buckets) {
    if (!bucket.empty())
      ++usedBuckets;
    if (bucket.size() > maxChain)
      maxChain = bucket.size();
  }
  std::cout << "\n=== Hash Table Stats ===\n"
            << "Capacity:      " << tableSize << "\n"
            << "Items:         " << count << "\n"
            << "Used buckets:  " << usedBuckets << "\n"
            << "Load factor:   " << loadFactor() << "\n"
            << "Longest chain: " << maxChain << "\n";
}

void printSearchResult(const std::string &name, const Equipment *result) {
  std::cout << "\nSearch: \"" << name << "\"\n";
  if (result)
    std::cout << "  Found: " << result->name << " | " << result->category
              << " | " << result->material << " | " << result->weight << "kg"
              << " | $" << result->price << "\n";
  else
    std::cout << "  Not found.\n";
}

int main() {
  EquipmentHashTable table;

  std::vector<Equipment> inventory = {
      {"Carbon Bike Helmet", "Cycling", "Carbon fiber", 0.25, 189.99},
      {"Pro Tennis Racket", "Tennis", "Graphite", 0.31, 229.00},
      {"Mountain Ski Boots", "Skiing", "Plastic/Foam", 1.80, 349.00},
      {"Climbing Harness", "Climbing", "Nylon", 0.45, 89.99},
      {"Swim Goggles Pro", "Swimming", "Silicone/PC", 0.08, 34.50},
      {"Kayak Paddle", "Kayaking", "Fiberglass", 0.90, 145.00},
      {"Trail Running Shoes", "Running", "Mesh/Rubber", 0.29, 129.99},
      {"Boxing Gloves 12oz", "Boxing", "Leather", 0.34, 59.99},
      {"Volleyball Net", "Volleyball", "Nylon", 2.10, 75.00},
      {"Archery Bow", "Archery", "Composite", 0.85, 299.00},
  };

  std::cout << "Inserting equipment...\n";
  for (const auto &item : inventory) {
    table.insert(item);
    std::cout << "  + " << item.name << "\n";
  }

  table.printAll();
  table.printStats();
  printSearchResult("Pro Tennis Racket", table.find("Pro Tennis Racket"));
  printSearchResult("Archery Bow", table.find("Archery Bow"));
  printSearchResult("Snowboard", table.find("Snowboard"));
  std::cout << "\nUpdating 'Boxing Gloves 12oz'...\n";
  table.insert({"Boxing Gloves 12oz", "Boxing", "Genuine Leather", 0.34, 74.99});
  printSearchResult("Boxing Gloves 12oz", table.find("Boxing Gloves 12oz"));
  std::cout << "\nRemoving 'Volleyball Net'...\n";
  table.remove("Volleyball Net")
      ? std::cout << "  Removed successfully.\n"
      : std::cout << "  Not found.\n";
  printSearchResult("Volleyball Net", table.find("Volleyball Net"));
  table.printStats();
  return 0;
}

