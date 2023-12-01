#pragma once

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

template <class T> struct node_type_traits {
public:
  using leaf_type = typename T::leaf_type;
  using data_type = typename T::data_type;
};

/*
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
*/

template <class NodeType> class node {
public:
  using value_type = NodeType;
  using leaf_type = typename node_type_traits<NodeType>::leaf_type;
  using data_type = typename node_type_traits<NodeType>::data_type;

private:
  std::shared_ptr<value_type> m_data;

protected:
public:
  node() { m_data.reset(new value_type); }
  node(node const &) = default;
  node(node &&) = default;

  auto leaf_value() const noexcept -> leaf_type & { return m_data->leaf; }
  auto data_value() const noexcept -> data_type & { return m_data->data; }
};

/*
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
*/

template <class Key, class T> struct struct_node_type {
public:
  using leaf_type = std::unordered_map<Key, node<struct_node_type<Key, T>>>;
  using data_type = T;

  leaf_type leaf;
  data_type data;
};

/*
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
*/

template <class Key, class T> class b_tree {
public:
  using key_type = typename std::vector<Key>;
  using value_type = node<struct_node_type<Key, T>>;
  using pointer = node<struct_node_type<Key, T>> *;
  using reference = node<struct_node_type<Key, T>> &;

private:
  value_type m_root;

protected:
  auto static nocheck_find(key_type const &keys, pointer current) noexcept
      -> pointer {
    for (Key key : keys) {
      if (auto ite = current->leaf_value().find(key);
          ite == current->leaf_value().end()) {
        return nullptr;
      } else {
        current = &(ite->second);
      }
    }
    return current;
  }

public:
  auto static find(key_type const &keys, pointer current) noexcept -> pointer {
    if (!current) {
      return current;
    }
    return nocheck_find(keys, current);
  }
  auto find(key_type const &keys) noexcept -> pointer {
    return nocheck_find(keys, &m_root);
  }

  auto try_insert(key_type keys, pointer current,
                  value_type const value = value_type()) noexcept -> pointer {
    Key target = keys.back();
    keys.pop_back();
    if (pointer buf_ptr = find(keys, current); buf_ptr) {
      auto inserted_pair = buf_ptr->leaf_value().try_emplace(target, value);
      if (inserted_pair.second) {
        return &(inserted_pair.first->second);
      }
    }
    return nullptr;
  }
  auto try_insert(key_type keys, value_type const value = value_type()) noexcept
      -> pointer {
    return try_insert(keys, &m_root, value);
  }

  auto erase(key_type keys, pointer current) noexcept -> size_t {
    Key target = keys.back();
    keys.pop_back();
    if (pointer buf_ptr = find(keys, current); buf_ptr) {
      return buf_ptr->leaf_value().erase(target);
    }
    return 0;
  }
  auto erase(key_type keys) noexcept -> size_t {
    return erase(keys, &m_root);
  }
};