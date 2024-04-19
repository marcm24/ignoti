#include "user.h"

// default constructor
User::User()
{
    userId = "";
    username = "";
    url = "";
    fullName = "";
    bio = "";
    all = Notification();
    like = likeNotification();
    tag = tagNotification();
    com = commentNotification();
    follow = followNotification();
    msg = messagereqNotification();
}

// constructor
User::User(std::string auserId, std::string ausername, std::string aurl, std::string afullName, std::string abio, Notification aall, likeNotification alike, tagNotification atag, commentNotification acom, followNotification afollow, messagereqNotification amsg)
{
    userId = auserId;
    username = ausername;
    url = aurl;
    fullName = afullName;
    bio = abio;
    all = aall;
    like = alike;
    tag = atag;
    com = acom;
    follow = afollow;
    msg = amsg;
}

// taggedUser constructors
taggedUser::taggedUser() : User("", "", "", "", "", Notification(), likeNotification(), tagNotification(), commentNotification(), followNotification(), messagereqNotification()) {}
taggedUser::taggedUser(std::string auserId, std::string ausername) : User(auserId, ausername, "", "", "", Notification(), likeNotification(), tagNotification(), commentNotification(), followNotification(), messagereqNotification()) {}

// user get functions
std::string User::getuserId() const
{
    return userId;
}

std::string User::getuserUsername() const
{
    return username;
}

std::string User::getuserUrl() const
{
    return url;
}

std::string User::getuserfullName() const
{
    return fullName;
}

std::string User::getuserBio() const
{
    return bio;
}

std::string User::getuserpauseAll() const
{
    return all.isEnabled();
}

std::string User::getuserlikeNotif() const
{
    return like.isEnabled();
}

std::string User::getusertagNotif() const
{
    return tag.isEnabled();
}

std::string User::getusercommentNotif() const
{
    return com.isEnabled();
}

std::string User::getuserfollowNotif() const
{
    return follow.isEnabled();
}

std::string User::getusermessagereqNotif() const
{
    return msg.isEnabled();
}

// tagged user get functions
std::string taggedUser::gettaggedId() const
{
    return getuserId();
}

std::string taggedUser::gettaggedUsername() const
{
    return getuserUsername();
}

// overloaded equality operator to check if a user is the same by username
bool User::operator==(std::string otherusername) const
{
    return (username == otherusername);
}