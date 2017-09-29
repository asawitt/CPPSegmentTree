#include "SegmentTree.h"


int max(int e1,int e2){
   if (e1>=e2) return e1;
      return e2;
}
int min(int e1,int e2){
   if (e1<=e2) return e1;
   return e2; 
}
std::string substring(std::string c1, std::string c2){
   return c1 + c2;
}
int main(){
   std::vector<int> x = {6,3,5,2,8};
   SegmentTree<int> st = SegmentTree<int>(&max, x);
   std::cout << st.query(1,3) << std::endl; // Prints 5
   st = SegmentTree<int>(&min, x);
   std::cout << st.query(1,3) << std::endl; // Prints 2
   
   std::vector<std::string> s = {"xab", "xf", "hel", "lo", " world", "abra"};
   SegmentTree<std::string> st2 = SegmentTree<std::string>(&substring, s);
   std::cout << st2.query(2,4) << std::endl; // Prints Hello World
   return 0;
}