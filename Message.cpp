#include "Message.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>
#include <cstdlib>

using namespace std;


Message::Message () {
    // author = "no author";
    // subject = "no subject";
    // body = "no body";
    // id = 0;
    //childList;
}

Message::Message (const string & athr, const string & sbjct, 
const string & body, unsigned id) {
    this->author = athr;
    this->subject = sbjct;
    this->body = body;
    this->id = id;
    //childList;
}

Message::~Message () {
    // for (unsigned i = 0; i < id; ++i) {
    //     delete childList [i];
    // }
}

void Message::print (unsigned indentation) const {
    string tempbody = body;
    string indentspace = "";
    
    for (unsigned i = 0; i < indentation; ++i) { 
        indentspace.append("  ");
    }
    if (isReply()) {
		cout << endl;
	}
    //for (unsigned i = 0; i < indentation; ++i) { cout << "  ";} //indentation
    cout << indentspace << "Message #" << id << ":" << subject <<endl;
    //for (unsigned i = 0; i < indentation; ++i) { cout << "  ";} //indentation
    cout << indentspace << "from " << author << ":";
    for (unsigned i = 0; i < tempbody.size(); ++i) {
        //cout << body.at(i);
        if (tempbody.at(i) == '\n') {
            //for (unsigned j = 0; j < indentation; ++j) { cout << "  ";} //indentation
            tempbody.insert(i + 1, indentspace);
        }
    }
    cout << tempbody <<endl;
        
    if (childList.size() > 0) {
        for (unsigned i = 0; i < childList.size(); ++i) { //indentation
            childList.at(i)->print(indentation + 1);
        }
        
    }
      //cout<<"HEHAHOHAHE"<<endl;
        // cout << "Message #" << id << ": " << subject <<endl;
        // cout << "from " << author << ": " << body <<endl;
}


const string & Message::getSubject () const {
    return subject;
}

unsigned Message::getID () const {
    return id;
}

void Message::addChild(Message *child) {
    childList.push_back(child);
}