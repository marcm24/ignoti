#include "igpost.h"

// default constructor
IGPost::IGPost()
{
    postid = "";
    type = "";
    caption = "";
    hashtags = "";
    mentions = "";
    url = "";
    commentsCount = "";
    displayUrl = "";
    images = "";
    likesCount = "";
    timestamp = "";
    ownerUsername = "";
    ownerId = "";
    taggedUsers = std::vector<taggedUser>();
}

// constructor
IGPost::IGPost(std::string apostid, std::string atype, std::string acaption, std::string ahashtags, std::string amentions, std::string aurl, std::string acommentsCount, std::string adisplayUrl, std::string aimages, std::string alikescount, std::string atimestamp, std::string aownerUsername, std::string aownerId, std::vector<taggedUser> ataggedUsers)
{
    postid = apostid;
    type = atype;
    caption = acaption;
    hashtags = ahashtags;
    mentions = amentions;
    url = aurl;
    commentsCount = acommentsCount;
    displayUrl = adisplayUrl;
    images = aimages;
    likesCount = alikescount;
    timestamp = atimestamp;
    ownerUsername = aownerUsername;
    ownerId = aownerId;
    taggedUsers = ataggedUsers;
}

// get functions
std::string IGPost::getpostid() const {
    return postid;
}

std::string IGPost::gettype() const {
    return type;
}

std::string IGPost::getcaption() const {
    return caption;
}

std::string IGPost::gethashtags() const {
    return hashtags;
}

std::string IGPost::getmentions() const {
    return mentions;
}

std::string IGPost::geturl() const {
    return url;
}

std::string IGPost::getcommentsCount() const {
    return commentsCount;
}

std::string IGPost::getdisplayUrl() const {
    return displayUrl;
}

std::string IGPost::getimages() const {
    return images;
}

std::string IGPost::getlikescount() const {
    return likesCount;
}

std::string IGPost::gettimestamp() const {
    return timestamp;
}

std::string IGPost::getaownerUsername() const {
    return ownerUsername;
}

std::string IGPost::getownerId() const {
    return ownerId;
}

// equality operator to check if posts are equal by post id
bool IGPost::operator==(std::string other) const
{
    return postid == other;
}