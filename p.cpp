
#include<iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <set>

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

namespace dec_7_2021{
  class Node{
  public:
    int key;
    Node * next;
    Node(int key_, Node * next_){
      key = key_;
      next = next_;
    }
  };

  void link_out(Node * root){
    cout << "\n";
    Node * curr = root;
    while(curr){
      cout << curr->key << " ";
      curr = curr->next;
    }
    cout << "\n";
  }

  Node *  iter_rev(Node * root){
    Node * curr = root;
    Node * prev = nullptr;
    while(curr){
      Node * next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
    }
    link_out(prev);
    return prev;
  }

  Node * stack_rev(Node * head, Node * headref){
    Node * first = head;
    Node * rest = head->next;
    if(rest == nullptr){
      headref = first;
      return headref;
    }
    headref = stack_rev(rest, headref);
    rest->next = first;
    first->next = nullptr;
    return headref;
  }

  Node * reverse_k(Node * root, int k){
    if( root == nullptr){
      return nullptr;
    }
    Node * curr = root;
    Node * prev = nullptr;
    int count = k;
    while(curr && count){
      Node * next = curr->next;
      curr->next = prev;
      prev = curr;
      curr = next;
      count--;
    }
    root->next = reverse_k(curr,k);
    return prev;
  }

  bool check_if_pal(Node * curr, Node * * headref ){
    if(curr == nullptr){
      return true;
    }
    bool prev = check_if_pal(curr->next,headref);
    if( !prev ){
      return false;
    }
    bool res = curr->key == (*headref)->key;
    *headref = (*headref)->next;
    return res;

  }

  void main(){
    int N = 5;
    Node * root = nullptr;
    int arr[] = {1, 3, 5, 3, 1};
    for(int i = 0; i < N; i++ ){
      root = new Node(arr[i],root);
    }
    link_out( root);
    root = iter_rev(root);
    root = stack_rev(root, root);
    link_out(root);
    cout << check_if_pal(root,&root);
    root = reverse_k(root,3);
    link_out(root);

  }

};

namespace dec_8_2021{

  void find_pal(string wrd, string * pal_ptr, int low, int high){
    while(low >= 0  && high < wrd.length() && wrd[low] == wrd[high] ){

      low--;
      high++;

    }
    low++;
    *pal_ptr = wrd.substr(low, high -low);



  }

  void pal_finder(){
    string wrd = "AA";
    string longest_pal = "";
    for(int i = 0; i < wrd.length(); i++){
      string pal;
      find_pal(wrd, &pal, i,i);
      if( pal.length() > longest_pal.length()){
        longest_pal = pal;
      }
      pal = "";

      find_pal(wrd, &pal, i,i+1);
      if(pal.length() > longest_pal.length()){
        longest_pal = pal;
      }
      pal = "";

    }
    cout << longest_pal;
  }

  void cir_string(){
    string X = "ABCD";
    string Y = "DABC";
    int rot_count = 0;
    for(int i = 0; i < X.length(); i++){
      string front = X.substr(0,1);
      string rest = X.substr(1);
      rot_count++; // increment rotations
      X = rest + front;
      if(Y == X){
        cout << "both strings match";
        return;
      }
    }
  }

  void convert_to_exel(){
    string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result = "";
    int n= 27;

    while( n > 0){
      int index = (n-1) % 26;
      result = char( index + 'A') + result;
      n = (n-1) /26;
    }
    cout << result;
  }

  void anagram(){
    string X =  "listen";
    string Y = "silent";
    string sort_X;
    string sort_Y;
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());
    if (X ==  Y){
      cout << "anagram";
    }
  }

  void recur_wild(int n, string input){

    if (n == input.length()){
      cout << input << "\n";
      return;
    }
    if(input[n] == '?'){
      if (n == 0){


        string back = input.substr(1);
        char front = '1';
        string temp = front + back;
        recur_wild(n+1,temp);
        back = input.substr(1);
        front = '0';
        temp = front + back;
        recur_wild(n+1,temp);

      }else if (n == input.length() -1){
        string front = input.substr(0,input.length()-1);
        char back = '1';
        string temp = front + back;
        recur_wild(n+1,temp);
        front = input.substr(0,input.length()-1);
        back = '0';
        temp = front + back;
        recur_wild(n+1,temp);
      }else{
        string front = input.substr(0,n);
        string back = input.substr(n+1);
        string temp = front + '1' + back;
        recur_wild(n+1,temp);
        front = input.substr(0,n);
        back = input.substr(n+1);
        temp = front + '0' + back;
        recur_wild(n+1,temp);
      }

    }else{
      recur_wild(n+1,input);
    }
  }

  void wildcard(){
    string input = "1?11?00?1?";
    recur_wild(0,input);
  }

  void main(){
    wildcard();
  }

};

namespace dec_9_2021{

  void recur_interleave(string X, string Y, string res, int ln_c, set<string> & res_set){
    if(res.length() == ln_c ){
      cout << res;
      cout << "\n";
      res_set.insert(res);
      return;
    }
    if(X.length()){
      string temp_x = res + X.substr(0,1);
      recur_interleave(X.substr(1),Y,temp_x,ln_c,res_set);
    }
    if(Y.length()){
      string temp_y = res + Y.substr(0,1);
      recur_interleave(X,Y.substr(1),temp_y,ln_c,res_set);
    }
  }

  void interleave(){
    string X = "ABC";
    string Y = "ACB";
    string res = "";
    set<string> res_set = {};
    set<string>::iterator itr;
    int ln_c = X.length() + Y.length();
    recur_interleave(X,Y,res,ln_c,res_set);
    for(itr = res_set.begin(); itr != res_set.end(); itr++){
      cout << *itr << " ";
    }
  }

  void isomorph(){
    unordered_map<char, char> X_dict;
    unordered_map<char, char> Y_dict;
    string X = "ACAB";
    string Y = "XCXY";
    for(int i = 0; i < X.length(); i++){
      //check if curr letter exist in map
      // chack if curr letter maps to complemnt
          //else
          //false
      if(X_dict.find(X[i]) == X_dict.end()){
        X_dict[X[i]] = Y[i];
      }else if(X_dict[X[i]] != Y[i]){
        cout << "not isomorphic \n";
        return;
      }

      if(Y_dict.find(Y[i]) == Y_dict.end()){
        Y_dict[Y[i]] = X[i];
      }else if(Y_dict[Y[i]] != X[i]){
        cout << "not isomorphic \n";
        return;
      }

    }
    cout <<"isomorphic strings";
  }

  void recur_keypad(int n, vector<int> input, unordered_map<int, string> keypad_dict, string res ){
    if (n == input.size()){
      cout << res << "\n";
      return;
    }
    for (int i = 0; i < keypad_dict[input[n]].length(); i++){
      recur_keypad(n+1,input,keypad_dict,res + keypad_dict[input[n]].substr(i,1));
    }
  }

  void keypad(){
    unordered_map< int, string> keypad_dict;
    keypad_dict[2] = "ABC";
    keypad_dict[3] = "DEF";
    keypad_dict[4] = "GHI";
    vector<int> input = {2,3,4};
    string res = "";
    recur_keypad(0,input,keypad_dict,res);
  }

  void main(){
      keypad();
  }
};


int main(int argc, char const *argv[]) {
  /* code */

  dec_9_2021::main();
  return 0;
}
