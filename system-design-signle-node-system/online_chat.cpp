/*
https://github.com/donnemartin/system-design-primer/blob/master/solutions/object_oriented_design/online_chat/online_chat.ipynb

Constraints and assumptions

Assume we'll focus on the following workflows:
Text conversations only
Users
Add a user
Remove a user
Update a user
Add to a user's friends list
Add friend request
Approve friend request
Reject friend request
Remove from a user's friends list
Create a group chat
Invite friends to a group chat
Post a message to a group chat
Private 1-1 chat
Invite a friend to a private chat
Post a meesage to a private chat
No need to worry about scaling initially
*/

#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <enum.h>

class User {
public:
    User(int user_id, const std::string& name, const std::string& pass_hash) 
        : user_id(user_id), name(name), pass_hash(pass_hash) {}

    int user_id;
    std::string name;
    std::string pass_hash;
    std::unordered_map<int, User*> friends_by_id;
    std::unordered_map<int, std::vector<PrivateChat*>> friend_ids_to_private_chats;
    std::unordered_map<int, GroupChat*> group_chats_by_id;
    std::unordered_map<int, AddRequest*> received_friend_requests_by_friend_id;
    std::unordered_map<int, AddRequest*> sent_friend_requests_by_friend_id;

    void message_user(int friend_id, const std::string& message) {
        // ...
    }

    void message_group(int group_id, const std::string& message) {
        // ...
    }

    void send_friend_request(int friend_id) {
        // ...
    }

    void receive_friend_request(int friend_id) {
        // ...
    }

    void approve_friend_request(int friend_id) {
        // ...
    }

    void reject_friend_request(int friend_id) {
        // ...
    }
};

class UserService {
public:
    UserService() {}

    void add_user(int user_id, const std::string& name, const std::string& pass_hash) {
        // ...
    }

    void remove_user(int user_id) {
        // ...
    }

    void add_friend_request(int from_user_id, int to_user_id) {
        // ...
    }

    void approve_friend_request(int from_user_id, int to_user_id) {
        // ...
    }

    void reject_friend_request(int from_user_id, int to_user_id) {
        // ...
    }

private:
    std::unordered_map<int, User*> users_by_id;
};

class Chat {
public:
    Chat(int chat_id) : chat_id(chat_id) {}

    int chat_id;
    std::vector<User*> users;
    std::vector<Message*> messages;
};

class PrivateChat : public Chat {
public:
    PrivateChat(User* first_user, User* second_user) : Chat(0) {
        users.push_back(first_user);
        users.push_back(second_user);
    }
};

class GroupChat : public Chat {
public:
    void add_user(User* user) {
        // ...
    }

    void remove_user(User* user) {
        // ...
    }
};

class Message {
public:
    Message(int message_id, const std::string& message, std::chrono::system_clock::time_point timestamp)
        : message_id(message_id), message(message), timestamp(timestamp) {}

    int message_id;
    std::string message;
    std::chrono::system_clock::time_point timestamp;
};

class AddRequest {
public:
    AddRequest(int from_user_id, int to_user_id, RequestStatus request_status, std::chrono::system_clock::time_point timestamp)
        : from_user_id(from_user_id), to_user_id(to_user_id), request_status(request_status), timestamp(timestamp) {}

    int from_user_id;
    int to_user_id;
    RequestStatus request_status;
    std::chrono::system_clock::time_point timestamp;
};

enum class RequestStatus {
    UNREAD,
    READ,
    ACCEPTED,
    REJECTED
};

