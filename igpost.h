#include <iostream>
#include <vector>
#include "user.h"

#ifndef __IGPOST_H
#define __IGPOST_H

// IGPost class storing all the information for the posts. includes the user class as each post can contain taggedUsers

class IGPost
{
public:
    IGPost();
    IGPost(std::string apostid, std::string atype, std::string acaption, std::string ahashtags, std::string amentions, std::string aurl, std::string acommentsCount, std::string adisplayUrl, std::string aimages, std::string alikescount, std::string atimestamp, std::string aownerUsername, std::string aownerId, std::vector<taggedUser> ataggedUsers);

    std::string getpostid() const; 
    std::string gettype() const; 
    std::string getcaption() const; 
    std::string gethashtags() const; 
    std::string getmentions() const; 
    std::string geturl() const; 
    std::string getcommentsCount() const; 
    std::string getdisplayUrl() const; 
    std::string getimages() const; 
    std::string getlikescount() const; 
    std::string gettimestamp() const; 
    std::string getaownerUsername() const; 
    std::string getownerId() const; 
    std::vector<taggedUser> gettaggedUsers() const;

    bool operator==(std::string other) const;

    
private:
    
    std::string postid;
    std::string type;
    std::string caption;
    std::string hashtags;
    std::string mentions;
    std::string url;
    std::string commentsCount;
    std::string displayUrl;
    std::string images;
    std::string likesCount;
    std::string timestamp;
    std::string ownerUsername;
    std::string ownerId;
    std::vector<taggedUser> taggedUsers;

};

#endif