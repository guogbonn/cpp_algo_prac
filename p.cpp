
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


namespace dec_11_2021 {

  void recur_list(int n, const vector<int> &input,const vector<vector<char>> &input_list, unordered_map<int,char> & discovered, string res, bool start){
    if (n == input.size()){
      cout << res <<"\n";
      return;
    }
    if( discovered.find( input[n] - 1) != discovered.end() ){
      string temp = res + discovered[ input[n] - 1];
      recur_list(n+1, input, input_list,discovered,temp, false);
      return;
    }

    for(int i = 0; i < input_list[ input[n] - 1 ].size(); i++){
      if(start){
        discovered.clear();
      }

      discovered[ input[n] - 1 ] = input_list[ input[n] - 1][i];
      string temp = res + discovered[ input[n] - 1];
      recur_list(n+1, input, input_list,discovered,temp, false);
    }

  }

  void list_poss_comb(){
    vector< vector<char> > input_list = {
                                   { 'A', 'B', 'C', 'D' },
                                   { 'E', 'F', 'G', 'H', 'I', 'J', 'K' },
                                   { 'L', 'M', 'N', 'O', 'P', 'Q' },
                                   { 'R', 'S', 'T' },
                                   { 'U', 'V', 'W', 'X', 'Y', 'Z' }
                                 };
    vector<int> input = {1,3,1};

    unordered_map<int,char> discovered;

    string res = "";
    bool start = true;

    recur_list(0,input, input_list, discovered, res, start);
  }

  void main(){
      list_poss_comb();
  }
};


namespace dec_19_2021 {

  class Trie{
  public:
    bool is_leaf = false;
    unordered_map< char, Trie *> children;

    Trie(){

    }

    void insert(string word){
      Trie * curr = this;
      for(auto & alpha: word){
        if(curr->children.find(alpha) == curr->children.end()){
          curr->children[alpha] = new Trie();
        }
        curr = curr->children[alpha];
      }
      curr->is_leaf = true;
    }

    void search(string word){
      cout << "\n";
      Trie * curr = this;
      for(auto & alpha: word){
        if( curr->children.find(alpha) == curr->children.end()){
          cout << "word does not exist in trie: " << word;
          return;
        }else{
          curr = curr->children[alpha];
        }
      }
      if(curr->is_leaf){
        cout << "Found: " << word;
        return;
      }
      cout << "word does not exist in trie: " << word;

    }

  };

  class Trie_{
  public:
    vector<Trie_ *> children;
    string word;
    bool is_leaf = false;
    Trie_(){
      for(int i = 0; i < 27; i++){
        this->children.push_back(nullptr);
      }
    }

    void insert(string word){
      Trie_ * curr = this;
      for(auto & alpha: word){
        int key = (int)alpha - (int)'a';
        if( curr->children[key] == nullptr ){
          curr->children[key] = new Trie_();
        }
        curr = curr->children[key];
      }
      curr->is_leaf = true;
      curr->word = word;
    }

    void search(string word){
      Trie_ * curr = this;
      for( auto & alpha: word){
        int key = (int)alpha - (int)'a';
        if( curr->children[key] == nullptr ){
          cout << "word not in trie: " << word;
          return;
        }
        curr = curr->children[key];
      }

      if (curr->is_leaf){
        cout << "Found: " << curr->word;
      }

    }
  };

  void main(){
    Trie_ * head = new Trie_();
    vector <string> words =   {
        "lexicographic", "sorting", "of", "a", "set", "of", "keys", "can",
        "be", "accomplished", "with", "a", "simple", "trie", "based",
        "algorithm", "we", "insert", "all", "keys", "in", "a", "trie",
        "output", "all", "keys", "in", "the", "trie", "by", "means", "of",
        "preorder", "traversal", "which", "results", "in", "output", "that",
        "is", "in", "lexicographically", "increasing", "order", "preorder",
        "traversal", "is", "a", "kind", "of", "depth", "first", "traversal"
    };
    for (auto & wrd: words){
      head->insert(wrd);
    }
    head->search("kind");

  }
};

namespace dec_20_2021{

  void find_pair(){
    vector<int> arr = {1,2,3,4,5,67,5};
    int target = 6;
    unordered_map<int,int> sum_dict;
    for(int i=0; i < arr.size(); i++){

      if( sum_dict.find(target - arr[i]) != sum_dict.end()){
        cout << "\n";
        printf(" target - arr[i]: %d, @ %d \n arr[i]: %d @ %d ",target - arr[i],sum_dict[target - arr[i]],arr[i],i);

      }
      sum_dict[arr[i]] = i;
    }
  }

  void check_sub_arr(){
    vector<int> arr = {  0, 0, 1, 0, 1, 0, 0 };
    int target = 0;
    unordered_map<int, int> sum_dict = {{0,-1}};
    int accum = 0;
    for(int i = 0; i < arr.size(); i++){
      accum += (arr[i]) ? arr[i] : -1 ;
      if(sum_dict.find(accum - target) != sum_dict.end()){
        int length = i - sum_dict[accum - target];
        int start = i - length + 1;
        int end = i;
        cout << "\n";
        for(int j = start; j <= end; j++){
          cout << arr[j] << " ";
        }
      }
      if (sum_dict.find(accum) == sum_dict.end()){
        sum_dict[accum] = i;
      }
    }
  }

  void swap(int arr[], int x, int y){
    int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
  }

  void dutch_flag(){
    int arr[] = {0,0,0,1,1,2,2,0,0,2,0,1};
    int length = sizeof(arr)/sizeof(arr[0]);
    int pivot = 1;
    int end = length - 1;
    int m = 0;
    int start = m;
    while (m <= end){
      if(arr[m] < pivot){
        swap(arr,m,start);
        m++;
        start++;
      }else if (arr[m] > pivot){
        swap(arr,m,end);
        end--;
      }else{
        m++;
      }
    }
    for(auto &i: arr){
      cout << i << " ";
    }
  }

  void merge_sorted_arr(){
    int X[] = { 1, 4, 7, 8, 10 };
    int Y[] = { 2, 3, 9 };
    int lenx = sizeof(X)/sizeof(X[0]);
    int leny = sizeof(Y)/sizeof(Y[0]);
    int val;
    int j;
    for(int i = 0; i < lenx; i++){

      if(X[i] > Y[0]){
        val = X[i];
        X[i] = Y[0];
        Y[0] = val;
        j = 1;
        while(j < leny && Y[j] < val){
          Y[j-1] = Y[j];
          j++;
        }
        Y[j-1] = val;
      }
    }
    for(auto & i: X){
      cout << i << " ";
    }
    cout << "\n";
    for(auto & i: Y){
      cout << i << " ";
    }
  }

  void sort_arrs(int X[], int Y[], int m, int n){
    int k = n + m + 1;
    while (n > -1 && m > -1 ){
      if(X[m] > Y[n]){
        X[k] = X[m];
        m--;
      }else{
        X[k] = Y[n];
        n--;
      }
      k--;
    }
    while ( n > -1){
      X[k] = Y[n];
      n--;
      k--;
    }
  }

  void merge_con_arr(){
    int X[] = { 0, 2, 0, 3, 0, 5, 6, 0, 0 };
    int Y[] = { 1, 8, 9, 10, 15 };
    int k = 0;
    int lenx = sizeof(X)/sizeof(X[0]);
    int leny = sizeof(Y)/sizeof(Y[0]);
    for(int i = 0; i < lenx; i++){
      if (X[i]){
        X[k] = X[i];
        k++;
      }
    }
    for(auto & i: X){
      cout << i << " ";
    }
    cout << " \n";

    sort_arrs(X,Y,k-1,leny-1);
    for(auto & i: X){
      cout << i << " ";
    }
    cout << " \n";

  }
  void main(){
      merge_con_arr();
  }
}

namespace dec_21_2021{
  bool is_consec(int arr[], int i , int j, int min_, int max_){
    if(j-i != max_ - min_){

      return false;
    }
    vector<bool> visited(j-i+1,false);
    for(int k = i; k <= j; k++){
      if(visited[max_ - arr[k]]){

        return false;
      }
      visited[max_ - arr[k]] = true;
    }
    return true;
  }



  void sub_con_arr(){
    int arr[] = {2, 0, 2, 1, 4, 3, 1, 0 };
    int lena = sizeof(arr)/sizeof(arr[0]);
    int min_;
    int max_;
    int largest = 0;
    int start = 0;
    int end = 0;

    for(int i = 0; i < lena-1; i++){
      min_ = arr[i];
      max_ = arr[i];
      for(int j = i+1; j < lena-1; j++){
        min_ = (arr[j] <= min_) ? arr[j] : min_;
        max_ = (arr[j] >= max_) ? arr[j] : max_;
        if(is_consec(arr,i,j,min_,max_) && j-i > largest){
          largest = j-i;
          start = i;
          end = j;
        }
      }
    }
    printf("start: %d, end: %d\n",start, end );
    for(int i = start; i <= end; i++){
      printf("%d ",arr[i]);
    }

  }

  void find_eq(){
    vector<int> left;
    int arr[] = {0, -3, 5, -4, -2, 3, 1, 0};
    int lena = sizeof(arr)/sizeof(arr[0]);
    int right = 0;
    for(auto & i: arr){
      left.push_back(0);
    }
    for(int i = 1; i < lena; i++){
      left[i] = arr[i-1] + left[i-1];
    }
    for(int i = lena - 1; i > -1; i--){

      if(left[i] == right){
        cout << i << " ";
      }
      right += arr[i];
    }
  }

  void find_max_diff(){
    int arr[] = {2, 7, 9, 5, 1, 3, 5};
    int m_diff = 0;
    int lena  = sizeof(arr)/sizeof(arr[0]);
    int max = arr[lena-1];
    for (int i = lena - 2; i > -1; i--){
      if( arr[i] > max){
        max = arr[i];
      }else{
        m_diff = (max - arr[i] > m_diff) ? max - arr[i] : m_diff;
      }
    }
    cout << m_diff;
  }

  void kadane(){
    int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int max_ending_here = arr[0];
    int max_so_far = arr[0];
    int lena = sizeof(arr)/sizeof(arr[0]);
    for(int i = 1; i < lena; i++){
      max_ending_here += arr[i];
      max_ending_here = (max_ending_here > arr[i]) ? max_ending_here : arr[i];
      max_so_far = (max_ending_here > max_so_far) ? max_ending_here : max_so_far;
    }
    cout << max_so_far;
  }

  void algokadane(){
    int arr[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    int beg = 0;
    int start = 0;
    int end = 0;
    int max_ending_here = 0;
    int max_so_far = 0;
    int lena = sizeof(arr)/sizeof(arr[0]);

    for(int i = 0; i < lena; i++){
      max_ending_here += arr[i];
      if (max_ending_here < arr[i]){
        beg = i;
        max_ending_here = arr[i];
      }
      if(max_ending_here > max_so_far){
        max_so_far = max_ending_here;
        start = beg;
        end = i;
      }
    }
    for(int i = start; i <= end; i++){
      cout << arr[i] << " ";
    }
  }

  void recur_dist_com(int arr[], int n , int k, int size, string res){
    if (k == 0 ){
      cout << res << "\n";
      return;
    }
    for(int i = n; i < size; i++ ){
      string curr_let = to_string(arr[i]);
      string temp = res + " " + curr_let;
      recur_dist_com(arr,i, k-1, size, temp);
    }

  }

  void distinct_com(){
    int arr[] = {1, 2, 3};
    int k = 2;
    int lena = sizeof(arr)/sizeof(arr[0]);
    string res = "";
    recur_dist_com(arr, 0, k, lena, res);
  }

  void main(){
    distinct_com();
  }
};


int main(int argc, char const *argv[]) {
  /* code */

  dec_21_2021::main();
  return 0;
}
