#include "Topic.h"
#include "Message.h"

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

Topic::Topic () : Message () {
    author = "no author";
    subject = "no subject";
    body = "no body";
    id = 0;
    //childList;
}

Topic::Topic (const string &athr, const string &sbjct, const string &body, 
unsigned id) : Message (athr, sbjct, body, id) {
    this->author = athr;
    this->subject = sbjct;
    this->body = body;
    this->id = id;
    //childList;
}

bool Topic::isReply () const {
    return false;
}

string Topic::toFormattedString () const {
    stringstream temp;
    temp << "<begin_topic>\n:id: " << id << "\n:subject: " << subject;
    temp << "\n:from: " << author;
    if (childList.size() > 0) {
        temp << "\n:children: ";
        for (unsigned i = 0; i < childList.size(); ++i) {
            temp << childList[1] << " ";
        }
    }
    temp << "\n:body: " << body;
    temp << "\n<end>\n";
    return temp.str();
}