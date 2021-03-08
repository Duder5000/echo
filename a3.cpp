// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Alex Soames
// St.# : 301 292 784
// Email: asoames@sfu.ca
// Git link: https://github.com/Duder5000/echo.git
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
        //maybe I'm missing something obvious, but I have no idea what I'm supposed to so with 's'
        cout << "Passed in string: " << s << "\n";
        cout << "Reply string: " << replyStr << "\n";
      }

      std::string get_reply(){
        cout << "Enter a message: ";
        cin >> replyStr;

        return replyStr;
      } 

      User_bot(std::string n){
        myName = n;
      }

      ~User_bot(){}
      
  private:
    std::string myName = "";
    std::string replyStr = "";

};

class Datetime_bot: public Chatbot{ //#04
    
  public:
    std::string name() const{
        return myName;
      }

      void tell(const string& s){
        std::string str = s;
        std::locale loc;

        for (std::string::size_type i = 0; i < str.length(); i++){
          str[i] = std::tolower(str[i],loc);
        }       

        if(findDateTime(str)){
          cout << "Current time is: " << "\n";

          std::string monthString[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
          std::string dayString[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
          int year, month, day, hour, mins, secs, weekDay;

          getTm( year, month, day, hour, mins, secs, weekDay );
          cout << "Date: " << dayString[weekDay] << ", " << day << " " << monthString[month] << " " << year << " @ " << hour << ":" << mins << ":" << secs << "\n";
        }else{
          cout << default_message << "\n";
        }
      }

      bool findDateTime(std::string str){
        //source: http://www.cplusplus.com/reference/string/string/find/
        std::size_t found1 = str.find(DATE);
        std::size_t found2 = str.find(TIME);
        if (found1!=std::string::npos || found2!=std::string::npos){
          return true;
        }else{
          return false;
        }
      }

      std::string get_reply(){
        return "stuff!";
      } 

      void getTm( int &year, int &month, int &day, int &hour, int &mins, int &secs, int &weekDay){
        //source: http://cplusplus.com/forum/beginner/226899/
         time_t tt;
         time( &tt );
         tm TM = *localtime( &tt );

         year    = TM.tm_year + 1900;
         month   = TM.tm_mon ;
         day     = TM.tm_mday;
         hour    = TM.tm_hour;
         mins    = TM.tm_min ;
         secs    = TM.tm_sec ;
         weekDay = TM.tm_wday ;
      }

      Datetime_bot(std::string n, vector<std::string>  r){
        myName = n;
        Random_bot rb("tempRandomBot", r);
        default_message = rb.get_reply();
      }

      ~Datetime_bot(){}
      
  private:
    std::string myName = "";
    std::string default_message = "";
    const std::string DATE = "date";
    const std::string TIME = "time";

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
        cin >> lastReply;
        return lastReply;
      } 

      void askAns(){
        std::string ansStr;
        int questionCount = 0;

        cout << "Are you feeling sick?\nAnswer here: ";
        cin >> ansStr;
        ansLoop(ansStr);        
        questionCount++;

        if(checkYesNo(ansStr) == 'y'){
          cout << "Stay home - no exception.\n~Ending questions~\n";
        }else if(checkYesNo(ansStr) == 'n'){
          bubble();
        }
      }

      void bubble(){
        std::string ansStr;

        cout << "Can you keep your group limited to 2-6 people outside your bubble?\nAnswer here: ";
        cin >> ansStr;

        if(checkYesNo(ansStr) == 'y'){
          highRisk();
        }else if(checkYesNo(ansStr) == 'n'){
          meetOutside();
        }

      }

      void highRisk(){
        std::string ansStr;

        cout << "Is anyone in the group at higher risk for serious illness from COVID-19?\nAnswer here: ";
        cin >> ansStr;

        if(checkYesNo(ansStr) == 'y'){
          meetOutside();
        }else if(checkYesNo(ansStr) == 'n'){
          higherRiskBubble();
        }

      }

      void meetOutside(){
        cout << "Meet outside or in bigger spaces. Limit your time together. Stay 2m apart. No handshakes, air hugs only!\n~Ending questions~\n";
      }

      void higherRiskBubble(){
        
      }

      bool ansLoop(std::string ansStr){
        bool cont = true;
        bool r;
        while(cont){
          if(checkYesNo(ansStr) == 'y'){
            cont = false;
            r = true;
          }else if(checkYesNo(ansStr) == 'n'){
            cont = false;
            r = false;
          }else{
            cout << "Please answer again. I only really understand \'yes\' and \'no\'";
            cont = true;
            cin >> ansStr;
          }
        }
        return r;
      }

      char checkYesNo(std::string s){
        std::string str = s;
        std::locale loc;
        std::size_t yes = str.find("yes");
        std::size_t no = str.find("no");

        for (std::string::size_type i = 0; i < str.length(); i++){
          str[i] = std::tolower(str[i],loc);
        } 

        if (yes!=std::string::npos){
          return 'y';
        }else if(no!=std::string::npos){
          return 'n';
        }else{
          return 'e';
        }
      }

      Turning_bot(std::string n){
        myName = n;
      }

      ~Turning_bot(){}
      
  private:
    std::string myName = "";
    std::string lastReply = "";
    vector<std::string> ansLog;

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
  // cout << rb1.get_reply() << "\n";
  // cout << rb2.get_reply() << "\n";
  // cout << rb3.get_reply() << "\n";
  // cout << rb4.get_reply() << "\n";

  User_bot ub1("ub-one");
  // ub1.get_reply();
  // ub1.tell("stuff");

  Datetime_bot db1("db-one", strVec1);
  // db1.tell("appleDaTe");
  // db1.tell("orange");

  Turning_bot covid("covidBot");
  covid.askAns();



}
