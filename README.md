# B_tree

* c++ 20 ~
* using std library.
  * vector.
  * pair
  * unordered_map
  * sheard_ptr
* not have iterator.


## How to use (and other)
Key is separated by std::vector(\<Key>).</br>
so, you need casting to std::vector value.

node is separated by std::unordered_map(\<Key,NodeType>) in internally.</br>
so, you can more unlimited leaf nodes. (As much as environment allows.)

|member functions||
|----|----|
|find(Key_list, Pointer\<option>)|Find node.</br> Return is pointer match "Key_list".</br> If not match "Key_list", when return nullptr.</br>"Pointer" is current position set.|
|try_insert(Key_list, Value\<option>)|Insert node.</br> Return is pointer of inserting data.</br>If couldn't inserting, when return nullptr.</br>"Value" is initialize value.|
|try_insert(Key_list, Pointer, Value\<option>)|Same as try_insert(Key_list, Value\<option>).</br>"Pointer" is current position set.|
|erase(Key_list)|Erase node.</br>Return is size_t of delete node count(only 0 or 1).|
|erase(Key_list, Pointer)|Same as erase(Key_list).</br>"Pointer" is current position set.|
|||

