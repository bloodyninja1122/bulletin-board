/*You may not change the public interface or the encapsulated data in 
any way; you may modify or omit any of the suggested private "helper" 
functions, or add new ones.

Private Data Fields
title - string : title of the board; initialized via constructor


userList - vector<User> : list of members; initially empty, then 
populated via loadUsers()


currentUser (Major change from previous assignment!) - const User * : 
this is now a pointer to the user who is currently logged in; it is 
initialized by the constructors to 0 (nullptr), then set via login()
 	
 	REMEMBER to change all your currentUser.getUsername() to 
 	currentUser->getUsername()

messageList (Major change from previous assignment!) - 
 	vector<Message *> : list of message pointers, initially empty
Public Member Functions
This is the public interface of the class - the contract with the user.

BBoard( )
default constructor that creates a board with a default title, empty 
user & message lists, and a no current user (what should pointer be 
set to if there is nothing to point to?)

BBoard(const string &ttl) 
same as default c'tor, except that it sets the title of the board. 

~BBoard( )
destructor that deallocates all Messages pointed to by messageList  
(THINK CAREFULLY ABOUT THIS!!)

bool loadUsers(const string &userfile) 

This function gets a filename (userfile) of a file that stores the 
user info in the given format (See Input File Format Specs).

It opens and reads the file of all authorized users and passwords, 
constructs a User object from each name/password pair, and 
populates the userList vector.

If an error occurs when opening the file, it returns false. 
Returns true otherwise.

bool loadMessages(const string &datafile) New !!! 
This function gets a filename (datafile) of a file that stores 
the messages from previous sessions in the given format 
(See File Format Specs).

It opens and reads the file, creating Topic and Reply objects as 
appropriate, and fills the messageList vector (note: remember that 
messageList is a vector of Message pointers, not Messages).

If an error occurs when opening the file, it returns false. 
Returns true otherwise.

See below (Tips and Tricks) for tips.

bool saveMessages(const string &datafile) New !!! 
This is the final action of the bulletin board before closing:

It gets a filename (datafile) of a file that will store all of the 
the messages, and after opening the file writes the messages 
into it with the same format (See File Format Specs).

If an error occurs when opening the file, it returns false. 
Returns true otherwise.

(Note: Since you will be opening the file for writing 
- i.e. an ofstream - "file not found" is NOT an error; 
a new file will simply be created for you).

See below (Tips and Tricks) for tips.

void login( ) (Major changes from previous assignment!) 
asks for and validates current user/password

This function asks for a username and password, and checks the 
userList vector for a matching User.

If a match is found, it sets currentUser to the identified User 
from the list (remember, currentUser is now a pointer, 
not an actual object).

If not found, it will keep asking until a match is found or the 
user types: 'q' or 'Q' as the username (you may assume we do not 
have a member with name 'q' or 'Q')

When the user chooses to quit, say "Bye!" and just return from 
the login function - meaning that in main(), currentUser will 
be unchanged from its initial value, which should have been 
set to 0 or nullptr.

See the output specifications for details.

void run( ) (No direct change, but see the private display() and 
addReply() helper functions)  
This function includes the main loop of the BBoard.
If and only if there is a valid currentUser, enter the main loop, 
displaying the menu items:
Display Messages ('D' or 'd')
Add New Topic('N' or 'n')
Add Reply ('R' or 'r')
Quit ('Q' or 'q')

The user should select one of these menu items, which should then 
invoke the corresponding method of BBoard; with any other input, 
the user should be asked to try again.

'Q'/'q' should re-set currentUser to 0 (or nullptr) and then end 
the run function (return).

Note: if login() did not set a valid currentUser, this function 
must immediately return without showing the menu - i.e. there must be 
no way to get around logging in!

See suggested private functions for more details.
Suggested Private Member Functions
These are "helper functions": member functions that will never be 
needed by a user of the class - they are needed by the 
public interface functions. You are free to change/add/remove these 
functions as you wish:

void addUser(const string &name, const string &pass) 
This function may be called from the loadUsers function to 
add the users from file to userList. 

bool user_exists(const string& name, const string& pass) const 
(No longer needed) 

const User * getUser(const string &name, const string &pw) const 

This function includes the functionality of the old "user_exists" helper:

It traverses the userList, testing for the existence of a User 
with the given name and password; if this User is NOT found,
the function returns 0 (or nullptr); otherwise it returns 
a pointer to the identified User

(the statement return &userList.at(i) will work - make sure you 
understand why!!)

This function may be used by login() to set the currentUser 
(which is now, obviously, a pointer, not an object).

There must be no other way to set currentUser to anything 
other than 0 (or nullptr).

void display() const Major Change !!! 
This function will traverse the BBoard's message list, 
and invoke the print function on Topic objects ONLY.

It will then be the responsibility of the Topic object to 
invoke the print function recursively on its own replies.

The BBoard display function will ignore all Reply objects in its 
message list.

Question: how will BBoard know which Messages are Topics; and 
how will it know what argument to pass into the print function?

void add_message() (No longer needed)

void addTopic() New !!!
This function asks the user to create a new Topic 
(i.e. the first message of a new discussion "thread"). 
Every Topic includes a subject (single line), and a body that 
may consist of  multiple lines. e.g.,


Subject: "Thanks"
Body: "I would like to thank you for this awesome board.
      I'll visit here regularly."


The body ends when the user enters an empty line (i.e. a "double enter").  Each Topic also stores the username of currentUser; and a message id, which is 
(index of its Message* + 1)

For example, the first message on the board will be a Topic whose 
pointer will be stored at index 0 of the messageList vector, so its
message id will be (0 + 1) = 1

(there are better ways of establishing unique ids for 
a set of objects, but for now this will work fine)

Once the Topic has been constructed, a pointer to it is added to messageList.  
Hint: Do you need pointers to automatic or dynamic Topics?

void addReply() New !!!
This function asks the user to enter a reply to a given Message 
(which may be either a Topic or a Reply, so we can handle nested replies).

The addReply function first asks the user for the id of the Message to 
which they are replying; if the number provided is greater than 
the size of messageList it should output an error message and loop back, 
continuing to ask for a valid Message id number until the user enters 
either -1 (or any negative number, to return to the menu); or a valid id.

If the id is valid, then the function asks for the body of the 
new message, and constructs the Reply, pushing back a pointer 
to it on the messageList

The subject of the Reply is a copy of the parent Topic's subject with 
the "Re: " prefix.

e.g., suppose the subject of message #9 was "Thanks", and a user is 
replying to that message:

Enter Message ID: 9
Body: It was a pleasure implementing this.
      I hope everyone likes it.   



Note: As before, the body ends when the user enters an empty line.

The above dialog will generate a reply that has "Re: Thanks" as 
its subject and "It was a pleasure implementing this.\nI hope everyone 
likes it." as its body.

How will we know what Topic this is a reply to?

In addition to keeping a pointer to every Message 
(whether Topic or Reply) in BBoard's messageList vector, every Message 
(whether Topic or Reply) will also store a vector of pointers to all 
its own Replies.

So whenever we build a Reply, we must immediately store a pointer to it 
inside its parent Message. Therefore, you will:

create a dynamic Reply with the input data. The Reply's constructor 
should set the Reply's subject to "Re: " + its parent's subject.

call the addChild function on the parent message to push_back the 
Message* (to the new Reply) to the parent's childList vector;

Finally, push_back the same pointer to BBoard's messageList.

Note: When the user chooses to return to the menu, do not call run() 

again - just return from this addReply function.
*/