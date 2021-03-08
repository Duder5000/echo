// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Alex Soames
// St.# : 301 292 784
// Email: asoames@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include "cmpt_error.h"    // These are the only permitted includes!
#include "Chatbot.h"       //
#include <iostream>        // Don't include anything else.
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <ctime>     
#include <cassert>

using namespace std;

class Mirror_bot: public Chatbot{ //#01
    
  public:
      std::string name() const{
        return myName;
      }

      void tell(const string& s){
        //from my reading this does nothing for Q 01, 
        //but I'm guessing based on 'converse' I need 
        //it to change my 'currentWords' variable
        currentWords = s;
      }

      std::string get_reply(){
        if(currentWords == ""){
          currentWords = first_reply;
        }
        return currentWords;      
      } 

      Mirror_bot(std::string n, std::string fr){
        myName = n;
        first_reply = fr;
      }

      ~Mirror_bot(){}

  private:
    std::string myName = "";
    std::string currentWords = "";
    std::string first_reply = "";

};

class Random_bot: public Chatbot{ //#02
    
  public:
    std::string name() const{
        return myName;
      }

      void tell(const string& s){
        //from my reading this does nothing for Q 02
        cout << s;
      }

      std::string get_reply(){
        int max = randReplies.size() -1;
        int min = 0;
        int randNum = rand() % max + min;

        return randReplies[randNum];
      } 

      Random_bot(std::string n, vector<std::string>  r){
        myName = n;
        if(r.empty()){
          cmpt::error("empty vector given to Random_bot\n");
        }else{
          randReplies = r;
        }
      }

      vector<std::string> getLines(std::string fileName){
        vector<std::string> vecOfLines;

          std::ifstream in(fileName.c_str());

          if(!in){
            cmpt::error("no such file for Random_bot");
          }else{
            std::string str;

            while(std::getline(in, str)){            
                if(str != ""){
                  vecOfLines.push_back(str);
                }
            }     
          }
        return vecOfLines;
      }

      Random_bot(std::string n, std::string fileName){
        myName = n;
        randReplies = getLines(fileName);
        

      }

      ~Random_bot(){}
      
  private:
    std::string myName = "";
    vector<std::string> randReplies;

};

class User_bot: public Chatbot{ //#03
    
  public:
    std::string name() const{
        return myName;
      }

      void tell(const string& s){
        cout << s;
      }

      std::string get_reply(){
        return "stuff!";
      } 

      User_bot(std::string n){
        myName = n;
      }

      ~User_bot(){}
      
  private:
    std::string myName = "";

};

class Datetime_bot: public Chatbot{ //#04
    
  public:
    std::string name() const{
        return myName;
      }

      void tell(const string& s){
        cout << s;
      }

      std::string get_reply(){
        return "stuff!";
      } 

      Datetime_bot(std::string n){
        myName = n;
      }

      ~Datetime_bot(){}
      
  private:
    std::string myName = "";

};

class Turning_bot: public Chatbot{ //#05
    
  public:
    std::string name() const{
        return myName;
      }

      void tell(const string& s){
        cout << s;
      }

      std::string get_reply(){
        return "stuff!";
      } 

      Turning_bot(std::string n){
        myName = n;
      }

      ~Turning_bot(){}
      
  private:
    std::string myName = "";

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// converse is a helper function that you can use if you like. You are free to
// modify it in any way.
void converse(Chatbot* a, Chatbot* b, int max_turns = 50) {
  for(int turn = 1; turn <= max_turns; turn++) {
    string a_msg = a->get_reply();
    cout << "(" << turn << ") " << a->name() << ": " << a_msg << "\n";
    
    turn++;
    if (turn > max_turns) return;

    b->tell(a_msg);
    string b_msg = b->get_reply();

    cout << "(" << turn << ") " << b->name() << ": " << b_msg << "\n";
    a->tell(b_msg);
  } // for
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
  cout << "CMPT 135 - A03 | Alex Soames\n";
  
  Mirror_bot mb1("mb-one", "first reply");
  Mirror_bot mb2("mb-two", "first reply");
  
  vector<std::string> strVec1 = {"AAA","BBB","CCC"};  
  const std::string TEST_FILE = "words6.txt";
  Random_bot rb1("rb-one", strVec1);
  Random_bot rb2("re-two", strVec1);
  Random_bot rb3("re-two", TEST_FILE);
  Random_bot rb4("re-two", TEST_FILE);
  cout << rb1.get_reply() << "\n";
  cout << rb2.get_reply() << "\n";
  cout << rb3.get_reply() << "\n";
  cout << rb4.get_reply() << "\n";





  // int max_turns  = 5;
  // for(int turn = 1; turn <= max_turns; turn++) {
  //   string mb1_msg = mb1.get_reply();
  //   cout << "(" << turn << ") " << mb1.name() << ": " << mb1_msg << "\n";
    
  //   turn++;
  //   if (turn > max_turns){
  //     cout << "end!\n";
  //     break;
  //   }

  //   mb2.tell(mb1_msg);
  //   string mb2_msg = mb2.get_reply();

  //   cout << "(" << turn << ") " << mb2.name() << ": " << mb2_msg << "\n";
  //   mb1.tell(mb2_msg);
  // }

}
