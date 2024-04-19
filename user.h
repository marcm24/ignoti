#include <iostream>
#include <vector>
#include "notification.h"

#ifndef __USER_H
#define __USER_H

// user class for storing all user information. includes notification class as we store the users settings if they have certain notifications enabled

class User
{
public:
    User();
    User(std::string auserId, std::string ausername, std::string aurl, std::string afullName, std::string abio, Notification aall, likeNotification alike, tagNotification atag, commentNotification acom, followNotification afollow, messagereqNotification amsg);

    std::string getuserId() const;
    std::string getuserUsername() const;
    std::string getuserUrl() const;
    std::string getuserfullName() const;
    std::string getuserBio() const;
    std::string getuserpauseAll() const;
    std::string getuserlikeNotif() const;
    std::string getusertagNotif() const;
    std::string getusercommentNotif() const;
    std::string getuserfollowNotif() const;
    std::string getusermessagereqNotif() const;

    bool operator==(std::string otherusername) const;

protected:
    std::string userId;
    std::string username;
    std::string url;
    std::string fullName;
    std::string bio;
    Notification all;
    likeNotification like;
    tagNotification tag;
    commentNotification com;
    followNotification follow;
    messagereqNotification msg;
};

// derived taggedUser class as they are still a user, but we are only working with their username and ID. the fields for a tagged user differ slightly than from the user input

class taggedUser : public User
{
public:
    taggedUser();
    taggedUser(std::string userId, std::string username);

    std::string gettaggedId() const;
    std::string gettaggedUsername() const;
};
#endif