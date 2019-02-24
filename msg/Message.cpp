#include "Message.h"

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>
#include <cstdlib>

using namespace std;


Message::Message () {
    author = "no author";
    subject = "no subject";
    body = "no body";
    id = 0;
    //childList;
}

Message::Message (const string & athr, const string & sbjct, 
const string & body, unsigned id) {
    author = athr;
    subject = sbjct;
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
    if (childList.size() == 0) {
        for (unsigned i = 0; i < indentation; ++i) { cout << "  ";} //indentation
        cout << "Message #" << id << ": " << subject <<endl;
        for (unsigned i = 0; i < indentation; ++i) { cout << "  ";} //indentation
        cout << "from " << author << ": ";
        for (unsigned i = 0; i < body.size(); ++i) {
            cout << body.at(i);
            if (body.at(i) == '\n') {
                for (unsigned j = 0; j < indentation; ++j) { cout << "  ";} //indentation
            }
        }
        
    }
    if (childList.size() > 0) {
        for (unsigned i = 0; i < indentation; ++i) { //indentation
            cout << "  ";
        }
        
    }
       
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