#include "data.hpp"

#include <iostream>
#include <string>
#include <vector>

std::string key_to_str(std::vector<std::string> const &key) {
  std::string buffer = {};
  for (auto const &key_bit : key) {
    buffer += key_bit + " ";
  }
  return buffer;
}

void create_node(b_tree<std::string, int> &a,
                 std::vector<std::string> const &key) {
  std::cout << "create node: ";
  std::cout << key_to_str(key) << std::endl;
  a.try_insert(key);
}
void create_node(b_tree<std::string, int> &a,
                 std::vector<std::string> const &key,
                 std::vector<std::string> const &link_key) {
  std::cout << "create node: ";
  std::cout << key_to_str(key) << "(linking: " << key_to_str(link_key) << ")"
            << std::endl;
  a.try_insert(key, *(a.find(link_key).first));
}

void assignment_value(b_tree<std::string, int> &a,
                      std::vector<std::string> const &key, int val) {
  std::cout << key_to_str(key) << "= " << val << std::endl;
  auto target = a.find(key);
  target.first->data_value() = val;
}

void show_value(b_tree<std::string, int> &a,
                std::vector<std::string> const &key) {
  auto target = a.find(key);
  std::cout << key_to_str(key);
  if (target.second == false) {
    std::cout << "has'nt value\n";
  } else {
    std::cout << "has value. "
              << "value is, " << target.first->data_value() << std::endl;
  }
}

int main(int argc, char const *argv[]) {
#ifdef _DEBUG
  std::cout << "debug mode.\n\n";
#else
  std::cout << "release mode.\n\n";
#endif

  b_tree<std::string, int> a;
  std::vector<std::string> key0, key1, key2;
  key0 = {"test"};
  key1 = {"test", "test2"};
  key2 = {"test0"};

  std::cout << "creating node...\n";
  create_node(a, key0);
  create_node(a, key1);
  create_node(a, key2, key1);
  std::cout << std::endl;

  std::cout << "assignment node...\n";
  assignment_value(a, key0, 10);
  assignment_value(a, key1, 20);
  std::cout << std::endl;

  std::cout << "show value...\n";
  show_value(a, key0);
  show_value(a, key1);
  std::cout << "-link value...\n  ";
  show_value(a, key2);
  std::cout << "-hasn't value...\n  ";
  show_value(a, {"non1", "non2"});
  std::cout << "  ";
  show_value(a, {"test", "non3"});
  std::cout << std::endl;

  std::cout << "assignment link node...\n";
  assignment_value(a, key2, 30);
  std::cout << std::endl;

  std::cout << "show value...\n";
  show_value(a, key0);
  show_value(a, key1);
  std::cout << "-link value...\n  ";
  show_value(a, key2);
  std::cout << "-hasn't value...\n  ";
  show_value(a, {"non1", "non2"});
  std::cout << "  ";
  show_value(a, {"test", "non3"});
  std::cout << std::endl;

  return 0;
}
