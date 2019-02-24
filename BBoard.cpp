#include "BBoard.h"

using namespace std;

//PRIVATE MEMBER FUNCTIONS

void BBoard::addUser (const string &name, const string &pass) {
    User temp (name, pass);
    userList.push_back(temp);
}

const User * BBoard::getUser (const string &name, const string &pw) const {
    for (unsigned i = 0; i < userList.size(); ++i) {
        if (userList.at(i).check(name, pw)) {
            return &userList.at(i);
        }
    }
    return NULL;
}

void BBoard::display() const {
    
    if (messageList.size() == 0) {
        cout << endl << "Nothing to Display." <<endl;
        return;
    }
    
    for (unsigned i = 0; i < messageList.size(); ++i) {
        if (!messageList.at(i)->isReply()) {
            cout << "---------------------------------------------------------" <<endl;
            messageList.at(i)->print(0);
        }
    }
    cout << "---------------------------------------------------------" <<endl;
}

void BBoard::addTopic() {
    string subject;
    string body;
    string tempbody;
    unsigned tempid;
    cout << "Please create a new Topic." <<endl;
    cout << "enter subject" <<endl;
    cin.ignore();
    getline(cin, subject);
    cout << "Enter Body: " <<endl;
    while (true) {
        getline(cin, tempbody);
        if (tempbody.empty()) {
            break;
        }
        
        tempbody.append("\n");
        body.append(tempbody);
        //body = body.substr(0, body.size() - 1);
        
        // if (tempbody == "") {
        //     break;
        // }
        // body.append("\n");
        // body.append(tempbody);
    }
    for (unsigned i = 0; i < messageList.size(); ++i) {
        ++tempid;
    }
    ++tempid;
    
    Topic *temptopic = new Topic (currentUser->getUsername(), subject, body, (tempid));
    //Reply temp (currentUser->getUsername(), resubject, body, tempid + 1);
    messageList.push_back(temptopic);
    //messageList[replytoid-1]->addChild(tempreply);
}

void BBoard::addReply() {
    unsigned replytoid = 0;
    string input;
    int check;
    string body;
    string tempbody;
    string resubject;
    unsigned tempid = 0;
    cout << "Enter Message ID (-1 for Menu): " <<endl;
    cin >> replytoid;
    while (replytoid > messageList.size() || replytoid <= 0) {
        cout << "Error, id is not valid, enter another id or a negative # to return to menu" <<endl;
        cin >> input;
        replytoid = atoi(input.c_str());
        check = atoi(input.c_str());
        if (check <= 0) {
            break;
        }
    }
    if (check <= 0) {
        return;
    }
    resubject = messageList[replytoid]->getSubject();
    cout << "Enter Body: " <<endl;
    cin.ignore();
    while (true) {
        getline(cin, tempbody);
        if (tempbody.empty()) {
            break;
        }
        tempbody.append("\n");
        body.append(tempbody);
        //body = body.substr(0, body.size() - 1);
        
        // if (tempbody == "") {
        //     break;
        // }
        // body.append("\n");
        // body.append(tempbody);
    }
    resubject = messageList.at(replytoid - 1)->getSubject();
    for (unsigned i = 0; i < messageList.size(); ++i) {
        ++tempid;
    }
    ++tempid;
    Reply *tempreply = new Reply (currentUser->getUsername(), resubject, body, (tempid));
    //Reply temp (currentUser->getUsername(), resubject, body, tempid + 1);
    messageList.push_back(tempreply);
    messageList[replytoid-1]->addChild(tempreply);
}


//PUBLIC MEMBER FUNCTIONS

BBoard::BBoard () {
    title = "default title";
    //userList;
    //messageList;
    //vector<Message *> messageList;
    currentUser = NULL;
}

BBoard::BBoard (const string &ttl) {
    title = ttl;
    //userList;
    //messageList;
    //vector<Message *> messageList;
    currentUser = NULL;
}

BBoard::~BBoard () {
    for (unsigned i = 0; i < messageList.size(); ++i) {
        delete messageList.at(i);
    }
}

bool BBoard::loadUsers(const string &userfile) {
    ifstream file;
    //file.open(userfile);
    file.open(userfile.c_str());
    
    if (!file.is_open()) {
        file.close();
        return false;
    }
    
    string tempname;
    string temppass;
    
    while (file >> tempname >> temppass) {
        addUser (tempname, temppass); 
    }
    // cout << "finished loading userfile!" <<endl;
    file.close();
    return true;
}

bool BBoard::loadMessages (const string &datafile) {
     
    ifstream file;
    stringstream file2;
    
    file.open(datafile.c_str());
    if (!file.is_open()) {
        file.close();
        return false;
    }
    
    string tempstr;
    string tempintstr;
    int tempint;
    
    unsigned j=0;
    bool endofchild = false;
    bool childidend = false;
    string childnum;
    unsigned nummsg = 0;
    unsigned msgcounter = 0;
    string msgtype;
    unsigned id=0;
    string subject;
    string author;
    vector<int> childid;
    string body;
    
    Message *temptopic = 0;
    Message *tempreply = 0;
    
    file >> nummsg;
        // cout<<endl;
        // cout<<"nummsg: "<<nummsg <<"|msgcounter: "<<msgcounter<<endl;
    getline(file, tempstr);
    while (!file.eof()) {
        // cout << "STARTING THE LOOP" <<endl;
    //childid.clear();
        body = "";
        
        // cout << "FIRST TEMPSTR: " <<tempstr <<endl;
        getline(file, msgtype);
            // cout<<"msgtype: "<<msgtype<<endl;
            
        file>>tempstr;
            // cout<<"|<:id:>|"<<tempstr<<endl;
        file>>id;
            // cout<<"id: "<<id<<endl;
            
        getline(file, tempstr);
        file>>tempstr;
            // cout<<"|<:subject:>|"<<tempstr<<endl;
        getline(file, subject);
        //file>>subject;
            // cout<<"subject: "<<subject<<endl;
            
        //getline(file, tempstr);
        file>>tempstr;
            // cout<<"|<:from:>|"<<tempstr<<endl;
        file>>author;
            // cout<<"author: "<<author<<endl;
            
        getline(file, tempstr);
        file>>tempstr; 
        
        if (tempstr == ":children:") {
                // cout<<"|<:children:>|"<<tempstr<<endl;
                
            getline(file, childnum);
            for ( unsigned i = 0; i < childnum.size(); ++i) {
                
                if (endofchild) {
                    // cout << "theres a endofchild here" <<endl;
                    break;
                }
                tempintstr = "";
                childidend = false;
                
                if (childnum.at(i) != ' '){
                    tempintstr = tempintstr + childnum.at(i);
                    j = i + 1;
                    
                    if (j < childnum.size()) {
                        
                        if (j == childnum.size()-1) {
                            // cout << "SPECIAL!!!" <<endl;
                            tempintstr = tempintstr + childnum.at(j);
                            endofchild = true;
                        }
                        
                        else if (childnum.at(j) != ' ') {
                            while (childnum.at(j) != ' ') {
                                tempintstr = tempintstr + childnum.at(j);
                                ++j;
                                if (j == childnum.size() - 1) {
                                    tempintstr = tempintstr + childnum.at(j);
                                    childidend = true;
                                }
                                if (childidend) {
                                    // cout << "theres a childidend here" <<endl;
                                    break;
                                }
                                if (childnum.at(j) == ' ') {
                                    break;
                                }
                            }
                        }
                    }
                    if (childnum.at(i-1) == ' ') {
                        // cout <<"string: "<< tempintstr<<endl;
                        // cout<< "atoi: " <<atoi(tempintstr.c_str()) <<endl;
                        childid.push_back(atoi(tempintstr.c_str()));
                    }
                }
            }
            //childid.push_back(-1);
            // cout << "Child IDs: ";
            // for (unsigned c = 0; c < childid.size(); ++c) {
            //     cout << childid.at(c) << " ";
            // }
            // cout <<endl;
            file >> tempstr;
        }
        if (tempstr == ":body:") {
                // cout<<"|<:body:>|"<<tempstr<<endl;
            getline(file,tempstr);
            body.append(tempstr);
            body.append("\n");
            while (tempstr != "<end>") {
                if (tempstr == "<end>") {
                    body.append("\n");
                    break;
                }
                getline(file,tempstr);
                body.append(tempstr);
                body.append("\n");
            }
            // cout << "body: " << body <<endl;
            childid.push_back(0);
        }
        //cout<<"I AM HERE"<<endl;
        if (msgtype == "<begin_topic>") {
            temptopic = new Topic (author, subject, body, id);
            // for (unsigned k = 0; k < childid.size()-1; ++k) {
            //     temptopic->addChild(messageList.at(childid.at(k)));
            // }
            // temptopic->addChild(messageList.at(childid));
            //Topic *point = &temptopic;
            messageList.push_back(temptopic);
            // cout<<"I AM HERE"<<endl;
        }
        // cout<<"I AM HERE2"<<endl;
        if (msgtype == "<begin_reply>") {
            tempreply = new Reply (author, subject, body, id);
            // for (unsigned k = 0; k < childid.size()-1; ++k) {
            //     tempreply->addChild(messageList.at(childid.at(k)));
            // }
            //tempreply->addChild(messageList.at(childid));
            messageList.push_back(tempreply);
        }
        //cout<<"nummsg: "<<nummsg <<"|msgcounter: "<<msgcounter<<endl;
        ++msgcounter;
        //cout<<"nummsg: "<<nummsg <<"|msgcounter: "<<msgcounter<<endl;
    }
    
    for(unsigned i = 0; i < childid.size(); i++) {
	    file2 << childid.at(i) << endl;
	}
    for(unsigned i = 0; i < nummsg; i++) {
        while(true) {
            file2 >> tempint;
            
            if(tempint == 0) {
                break;
            }
            // cout << "MSG #: " << i ;
            // cout << "ADDING CHILDS HERE: " <<tempint<<endl;
            messageList.at(i)->addChild(messageList.at(tempint - 1));
        }
    } 
    
    // cout << "finished loading msgfile!" <<endl;
    file.close();
    return true;
}

bool BBoard::saveMessages(const string &datafile) {
    ofstream file;
    
    file.open(datafile.c_str());
    if (!file.is_open()) {
        file.close();
        return false;
    }
    
    file << messageList.size() <<endl;
    for (unsigned i = 0; i < messageList.size(); ++i) {
        file << messageList.at(i)->toFormattedString();
    }
    
    file.close();
    return true;
    
    
}

void BBoard::login( ) {
    
    string tempname;
    string temppass;
    // bool gotin = false;
    cout << "Welcome to " << title <<endl;
    while (tempname != "Q" || tempname != "q") {
        cout << "Enter your username ('Q' or 'q' to quit): ";
        cin >> tempname;
        if (tempname == "Q" || tempname == "q") {
            cout<<"Bye!"<<endl;
            return;
        }
        cout << "Enter your password: " <<endl;
        cin >> temppass;
        
        for (unsigned i = 0; i < userList.size(); ++i) {
            if (tempname == userList.at(i).getUsername() && temppass == userList.at(i).getpassword()) {
                currentUser = &userList.at(i);
                cout << "Welcome back " << userList.at(i).getUsername() << "!" <<endl<<endl;
                tempname = "Q";

            }
        }
        // if (gotin) {
            
        // }
        if (tempname == "Q" || tempname == "q") {
            
            break;
        }
            cout << "Invalid Username or Password!" <<endl<<endl;
        // }
    }
}

void BBoard::run( ) {
    
    if (currentUser == NULL) {
        exit(0);
    }
    
    string option;
    while (option != "Q" || option != "q") {
        cout << "Menu" <<endl;
        cout << "- Display Messages ('D' or 'd')" <<endl;
        cout << "- Add New Topic ('N' or 'n')" <<endl;
        cout << "- Add Reply to a Topic ('R' or 'r')" <<endl;
        cout << "- Quit ('Q' or 'q')" <<endl;
        cout << "Choose an action: " <<endl;
        cin >> option;
        
        if (option == "D" || option == "d") {
            display();
        }
        if (option == "N" || option == "n") {
            addTopic();
        }
        if (option == "R" || option == "r") {
            addReply();
        }
        if (option == "Q" || option == "q") {
            cout<<"Bye!"<<endl;
            return;
        }
    }
    
    
    
    // string option;
    // Message tempmsg;
    // string tempsubjct;
    // string tempbody;
    
    
    // if (currentUser.getUsername()=="n/a") {
    //     exit (0);
    // }
    
    // while (true) {
    //     cout<<"Menu"<<endl;
    //     cout<<"- Display Messages ('D' or 'd')"<<endl;
    //     cout<<"- Add New Message ('N' or 'n')"<<endl;
    //     cout<<"- Quit ('Q' or 'q')"<<endl;
    //     cout<<"Choose an action: "<<endl;
    //     //cin.ignore(1, '\n');
    //     cin>>option;
    //     if (option == "D" || option == "d") {
            
    //         if ( messageList.size() == 0){
    //             cout << "Nothing to Display." << endl<<endl;
    //         }
            
    //         else{
            
            
            
    //         for (unsigned i=0; i<messageList.size(); ++i) {
    //             cout<<"---------------------------------------------------------"<<endl;
    //             cout<<"Message #"<<i+1<<": ";
    //             messageList.at(i).display();
    //         }
    //         cout<<"---------------------------------------------------------"<<endl<<endl;
    //         }
    //     }
        
    //     else if (option == "N" || option == "n") {
    //         cout<<"Enter Subject: "<<endl;
    //         cin.ignore(1,'\n');
    //         getline(cin, tempsubjct);
            
           
    //         cout<<"Enter Body: "<<endl;
    //         getline(cin,tempbody);
    //         tempmsg.modifymsg(currentUser.getUsername(),tempsubjct,tempbody);
    //         messageList.push_back(tempmsg);
    //         cout<<"Message Recorded!"<<endl<<endl;
            
            
    //     }
        
    //     else if (option == "Q" || option == "q"){
    //         cout<<"Bye!"<<endl;
    //         exit(0);
    //         //break;
    //     }
        
        
    // }
}
//also need to fix message.print() to print childReplies recursively