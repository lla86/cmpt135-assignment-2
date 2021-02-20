// a2.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough detail
// so that someone can see the exact source and extent of the borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have not
// seen solutions from other students, tutors, websites, books, etc.
//
/////////////////////////////////////////////////////////////////////////

//
// These are the only permitted includes: don't include anything else.
//
#include "cmpt_error.h"
#include <iostream>
#include <string>
#include <algorithm>       
#include <cassert>

using namespace std;

class str_vec
{
private:
  string *arr_; // pointer to the underlying array
  int size_;    // # of elements from user's perspective
  int capacity_;

public:
  str_vec()
  {
    size_ = 0;
    capacity_ = 10;
    arr_ = new string[capacity_];
  }

  str_vec(int n, string s)
  {
    if (n < 0)
    {
      cmpt::error("invalid number");
    }
    size_ = n;
    capacity_ = size_;
    arr_ = new string[capacity_];
    for (int i = 0; i < size_; i++)
    {
      arr_[i] = s;
    }
  }
  //copy constructor
  str_vec(str_vec &other)
  {
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = new string[capacity_];
    for (int i = 0; i < size_; i++)
    {
      string temp = other.arr_[i];
      arr_[i] = temp;
    }
  }
  //destructor
  ~str_vec()
  {
    delete[] arr_;
  }
  //three getters
  int size() const
  {
    return size_;
  }

  int capacity() const
  {
    return capacity_;
  }

  double pct_used() const
  {
    return (double)size_ / capacity_;
  }
  //three non-mutating methods
  string to_str() const
  {
    if (size_ == 0)
    {
      return "[]";
    }

    string str = "[";
    for (int i = 0; i < size_; i++)
    {
      str = str + "\"" + arr_[i] + "\"";
      if (i < size_ - 1)
      {
        str = str + ", ";
      }
    }
    str = str + "]";
    return str;
  }
  void print() const
  {
    cout << to_str();
  }
  void println() const
  {
    cout << to_str() << endl;
  }
  //get (i)
  string get(int i)
  {
    if (i < 0 || i >= size_)
    {
      cmpt::error("invalid index");
    }
    return arr_[i];
  }
  //set(i,s)
  void set(int i, string s)
  {
    if (i < 0 || i >= size_)
    {
      cmpt::error("invalid index");
    }
    arr_[i] = s;
  }
  //append
  void append(string s)
  {
    if (size_ >= capacity_)
    {
      capacity_ *= 2;
      string *temp = new string[capacity_];
      for (int i = 0; i < size_; i++)
      {
        temp[i] = arr_[i];
      }
      delete[] arr_;
      arr_ = temp;
    }
    arr_[size_] = s;
    size_++;
  }
  void prepend(string s)
  {
    if (size_ < capacity_)
    {
      for (int i = size_ - 1; i > -1; i--)
      {
        arr_[i + 1] = arr_[i];
      }
      arr_[0] = s;
      size_++;
    }
    else
    {
      capacity_ *= 2;
      string *temp = new string[capacity_];
      for (int i = 0; i < size_; i++)
      {
        temp[i + 1] = arr_[i];
      }
      delete[] arr_;
      arr_ = temp;
      arr_[0] = s;
      size_++;
    }
  }
  //append (other)
  void append(str_vec &other)
  {
    int length = other.size_;
    for (int i = 0; i < length; i++)
    {
      append(other.arr_[i]);
    }
  }

  //reverse
  void reverse()
  {
    string *temp = new string[capacity_];
    for (int i = 0; i < size_; i++)
    {
      temp[i] = arr_[size_ - 1 - i];
    }
    delete[] arr_;
    arr_ = temp;
  }
  void sort()
  {
    for (int i = 0; i < size_; i++)
    {
      int front = i;
      for (int j = i + 1; j < size(); j++)
      {
        if (arr_[j].compare(arr_[front]) <= 0)
        {
          front = j;
        }
      }
      swap(arr_[front], arr_[i]);
    }
  }
  void clear()
  {
    size_ = 0;
  }

  void squish()
  {

    if (size_ == capacity_)
    {
      return;
    }
    string *temp = new string[size_];
    for (int i = 0; i < size_; i++)
    {
      temp[i] = arr_[i];
    }
    delete[] arr_;
    arr_ = temp;
    capacity_ = size_;
  }
  // ...
}; // class str_vec
bool operator==(str_vec a, str_vec b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    if (a.get(i) != b.get(i))
    {
      return false;
    }
  }
  return true;
}

bool operator!=(str_vec a, str_vec b)
{
  return !(operator==(a, b));
}

//function tests

//default constructor test
void default_constructor_test()
{
  cout << "default_constructor_test start:"<<endl;
  str_vec v;
  assert(v.capacity() == 10);
  assert(v.size() == 0);
  cout << "default_constructor_test end"<<endl;
}

void constructor_test()
{
  cout << "constructor_test start:"<<endl;
  str_vec v(5, "cat");
  for (int i = 0; i < v.size(); i++)
  {
    assert(v.get(i) == "cat");
  }
  cout << "constructor_test end"<<endl;
}

void copy_constructor_test()
{
  cout << "copy_constructor_test start:"<<endl;
  str_vec v(5, "cat");
  str_vec v1(v);
  for (int i = 0; i < v1.size(); i++)
  {
    assert(v1.get(i) == v.get(i));
  }

  str_vec v2;
  v2.append("dude");
  v2.append("girl");
  str_vec v3(v2);
  assert(v3.get(0) == "dude");
  assert(v3.get(1) == "girl");
  cout << "copy_constructor_test end."<<endl;
}

void destructor_test()
{
  cout << "destructor_test start:"<<endl;
  str_vec v;
  str_vec v1(5, "cat");
  str_vec v2(v1);
  cout << "destructor_test end"<<endl;
}

//three getters' test
void size_test()
{
  cout << "size_test start:"<<endl;
  str_vec v;
  assert(v.size() == 0);
  str_vec v1(5, "cat");
  assert(v1.size() == 5);
  str_vec v2(15, "dude");
  assert(v2.size() == 15);
  cout << "size_test end"<<endl;
}

void capacity_test()
{
  cout << "capacity_test start:"<<endl;
  str_vec v;
  assert(v.capacity() == 10);
  str_vec v1(5, "cat");
  assert(v1.capacity() == 5);
  str_vec v2(15, "dude");
  assert(v2.capacity() == 15);
  cout << "capacity_test end"<<endl;
}

void pct_used_test()
{
  cout << "pct_used start:"<<endl;
  str_vec v;
  assert(v.pct_used() == 0);
  str_vec v1(5, "dog");
  assert(v1.pct_used() == (double)1);
  str_vec v2(10, "dog");
  assert(v2.pct_used() == (double)1);
  v2.append("cat");
  assert(v2.pct_used() == (double)11 / 20);
  cout << "pct_used end"<<endl;
}

void to_str_test()
{
  cout << "to_str start:"<<endl;
  str_vec v;
  assert(v.to_str() == "[]");
  str_vec v1(2, "dude");
  assert(v1.to_str() == "[\"dude\", \"dude\"]");
  v1.append("hello");
  assert(v1.to_str() == "[\"dude\", \"dude\", \"hello\"]");
  cout << "to_str end"<<endl;
}

void print_test()
{
  cout << "print_test start:"<<endl;
  str_vec v1(2, "dude");
  v1.print();
  cout << "print_test end"<<endl;
}

void println_test()
{
  cout << "println_test start:"<<endl;
  str_vec v1(2, "dude");
  v1.println();
  cout << "println_test end"<<endl;
}

void get_test()
{
  cout << "get_test start:"<<endl;
  str_vec v1(2, "dude");
  try
  {
    v1.get(-1);
  }
  catch (runtime_error &error)
  {
    assert(true);
  }
  assert(v1.get(0) == "dude");
  assert(v1.get(1) == "dude");
  v1.append("dog");
  assert(v1.get(2) == "dog");
  v1.append("cat");
  assert(v1.get(3) == "cat");
  cout << "get_test end"<<endl;
}

void set_test()
{

  cout << "set_test start:"<<endl;
  str_vec v1(2, "cat");
  try
  {
    v1.set(-1, "cat");
  }
  catch (runtime_error &error)
  {
    assert(true);
  }
  v1.set(0, "dude");
  assert(v1.get(0) == "dude");
  v1.set(1, "dude");
  assert(v1.get(1) == "dude");
  cout << "set_test start:"<<endl;
}
void append_test()
{
  cout << "append_test start:"<<endl;
  str_vec v;
  v.append("girl");
  v.append("dude");

  assert(v.get(0) == "girl");
  assert(v.get(1) == "dude");
  cout << "append_test end:"<<endl;
}

void prepend_test()
{
  cout << "prepend_test start:"<<endl;
  str_vec v;
  v.prepend("girl");
  v.prepend("dude");
  assert(v.get(1) == "girl");
  assert(v.get(0) == "dude");
  cout << "prepend_test end:"<<endl;
}
void append_other_test()
{
  cout << "append_other_test start:"<<endl;
  str_vec v;
  v.append("girl");
  v.append("dude");
  str_vec v1(2, "cat");
  v1.append(v);
  assert(v1.get(2) == "girl");
  assert(v1.get(3) == "dude");
  cout << "append_other_test end:"<<endl;
}
void reverse_test()
{
  cout << "reverse_test start:"<<endl;
  str_vec arr;
  arr.append("d");
  arr.append("b");
  arr.append("a");
  arr.append("c");
  arr.reverse();
  assert(arr.get(0) == "c");
  assert(arr.get(1) == "a");
  assert(arr.get(2) == "b");
  assert(arr.get(3) == "d");
  cout << "reverse_test end:"<<endl;
}
void sort_test()
{
  cout << "sort_test start:"<<endl;
  str_vec arr;
  arr.append("d");
  arr.append("b");
  arr.append("a");
  arr.append("c");
  arr.sort();
  assert(arr.get(0) == "a");
  assert(arr.get(1) == "b");
  assert(arr.get(2) == "c");
  assert(arr.get(3) == "d");
  cout << "sort_test end:"<<endl;
}
void clear_test()
{
  cout << "clear_test start:"<<endl;
  str_vec arr;
  arr.append("d");
  arr.append("b");
  arr.append("a");
  arr.squish();
  arr.clear();
  assert(arr.size() == 0);
  assert(arr.capacity() == 3);
  cout << "clear_test end:"<<endl;
}
void squish_test()
{
  cout << "squish_test start:"<<endl;
  str_vec arr;
  arr.append("d");
  arr.append("b");
  arr.append("a");
  arr.squish();
  assert(arr.size() == 3);
  assert(arr.capacity() == 3);
  cout << "squish_test end:"<<endl;
}

void operator_equal_equal_test()
{
  cout << "operator_equal_equal_test end:"<<endl;
  str_vec v1(3, "cat");
  v1.append("dog");
  str_vec v2(v1);
  assert(operator==(v1, v2));
  v2.append("girl");
  assert(!operator==(v1, v2));
  cout << "operator_equal_equal_test end:"<<endl;
}

void operator_not_equal_test()
{
  cout << "operator_not_equal_test end:"<<endl;
  str_vec v1(3, "cat");
  v1.append("dog");
  str_vec v2(v1);
  assert(!operator!=(v1, v2));
  v2.append("girl");
  assert(operator!=(v1, v2));
  cout << "operator_not_equal_test end:"<<endl;
}

int main()
{
  cout << "Assignment 2 ... \n";

  //
  // ... put code that calls your functions here ...
  //
  default_constructor_test();
  constructor_test();
  copy_constructor_test();
  destructor_test();
  size_test();
  capacity_test();
  pct_used_test();
  to_str_test();
  print_test();
  println_test();
  get_test();
  set_test();
  append_test();
  prepend_test();
  append_other_test();
  reverse_test();
  sort_test();
  clear_test();
  squish_test();
  operator_equal_equal_test();
  operator_not_equal_test();
}
