
#include<iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

namespace dec_5_2021{
  class Node{
  public:
    int key;
    Node * next;
    Node(int key_ = -1,Node * next_ = nullptr){
      key = key_;
      next = next_;
    }
    ~Node(){
      cout << "delete me: " << key << "\n";
    }
  };
  void link_out(Node * root){
    Node * curr = root;
    while (curr){
      cout << curr->key << " ";
      curr = curr->next;
    }
    cout << "\n";
  }

  void pop(Node * root){
    Node * dummy = new Node();
    Node * curr = dummy;
    curr->next = root;
    Node * prev = curr;
    while( curr->next != nullptr){
      prev = curr;
      curr = curr->next;
    }
    Node * temp = prev->next;
    prev->next = nullptr;
    delete (temp);
    link_out( dummy->next);
  }

  void insert(Node * root, int val){
    Node * dummy = new Node();
    Node * curr = dummy;
    curr->next = root;
    while(curr->next != nullptr && val < curr->next->key){
      curr = curr->next;
    }
    Node * newNode = new Node(val,curr->next);
    curr->next = newNode;
    link_out(dummy->next);
  }

   Node * sorter_link(Node * res, Node * head){
     Node * dummy = new Node();
     Node * curr = dummy;
     curr->next = res;
     while(curr->next != nullptr && head->key > curr->next->key){
      curr = curr->next;
     }
      head->next = curr->next;
      curr->next = head;
      Node * temp = dummy->next;
      delete(dummy);
      return temp;
   }

  Node * sort_link(Node * root){
    Node * curr = root;
    Node * result = nullptr;
    while(curr){
      Node * next = curr->next;
      result = sorter_link(result, curr);
      curr = next;
    }
    link_out(result);
    return result;
  }

  Node * move_evens(Node * root){
    Node * dummy = new Node();
    Node * curr = dummy;
    curr->next = root;
    Node * evens = nullptr;
    Node * temp = nullptr;
    while(curr->next != nullptr){
      if(curr->next->key % 2 == 0 ){
        Node * newNode = new Node(curr->next->key,evens);
        evens = newNode;
        temp = curr->next;
        curr->next = curr->next->next;
        delete(temp);
      }else{
        curr = curr->next;
      }
    }
    curr->next = evens;
    temp = dummy->next;
    delete(dummy);
    link_out(temp);
    return temp;
  }

  Node * merge_link(Node * a, Node * b){
    if(a == nullptr){
      return b;
    }
    if(b == nullptr){
      return a;
    }
    Node * result;
    if(a->key < b->key){
      result = a;
      result->next = merge_link(a->next, b);
    }else{
      result = b;
      result->next = merge_link(a, b->next);
    }
    return result;
  }

  void split(Node * root, Node * &a, Node * &b){
    if(root == nullptr || root->next == nullptr){
      a = root;
      b = nullptr;
      return;
    }
    Node * fast = root->next;
    Node * slow = root;
    while(fast){
      fast = fast->next;
      if(fast){
        fast = fast->next;
        slow = slow->next;
      }
    }
    a = root;
    b = slow->next;
    slow->next = nullptr;
  }

  Node * merge_sort(Node * root){
    if(root == nullptr || root->next == nullptr){
        return root;
      }
      Node * a;
      Node * b;
      split(root,a,b);
      a = merge_sort(a);
      b = merge_sort(b);
      return merge_link(a,b);

  }

  int main(){
    int N = 42;
    Node * root = nullptr;
    for(int i = 0; i < N; i++ ){
      root = new Node(i,root);
    }
    link_out( root);
    pop(root);
    insert( root, 0);
    root = sort_link(root);
    root = move_evens(root);
    root = merge_sort(root);
    cout << "\nresult: ";
    link_out(root);
    return 0;
  }
};


int main(int argc, char const *argv[]) {
  /* code */

  dec_5_2021::main();
  return 0;
}
