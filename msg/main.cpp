#include "Message.h"
#include "Topic.h"
#include "Reply.h"

using namespace std;

int main() {
    
    string author = "Misha";
    string subject = "To all haters";
    string body = "HEHAHOHAHE";
    unsigned id = 1;
    
    vector<Message *> messageList;
    getline(cin,subject);
    Topic temptopic (author, subject, body, id);
    //Reply reply1 (author, subject, body, id);
    
    
    messageList.push_back(&temptopic);
  //  messageList.push_back(&reply1);
    
    messageList.at(0)->print(2);
    
    cout<<"end"<<endl;
    
    
    
    
    
    
    
    
    
    
    
    return 0;
}