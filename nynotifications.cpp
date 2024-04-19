#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include "igpost.h"
#include "events.h"

/*
In this program we are taking an Instagram user as input and based on their notification settings, we are outputting various notifications they receive. These notifications
range from if their post has been liked, if they were tagged in a post, if someone commented on their post, if someone followed them, or if someone requested to message them.
Based on what settings the user has enabled, the corresponding notifications will be displayed. To not overwhelm the user with notifications, if there are more than 3 notifications
of the same type, then we will aggregate those notifications.
*/

// functions for extracting information for creating user
std::string extractuserId(std::string line)
{
    size_t userId_pos = line.find("id") + 6;
    size_t enduserId_pos = line.find("\"", userId_pos);
    std::string userId = line.substr(userId_pos, enduserId_pos - userId_pos);
    return userId;
}

std::string extractuserUsername(std::string line)
{
    size_t userUsername_pos = line.find("username") + 12;
    size_t enduserUsername_pos = line.find("\"", userUsername_pos);
    std::string userUsername = line.substr(userUsername_pos, enduserUsername_pos - userUsername_pos);
    return userUsername;
}

std::string extractuserUrl(std::string line)
{
    size_t userUrl_pos = line.find("url") + 7;
    size_t enduserUrl_pos = line.find("\"", userUrl_pos);
    std::string userUrl = line.substr(userUrl_pos, enduserUrl_pos - userUrl_pos);
    return userUrl;
}

std::string extractuserfullName(std::string line)
{
    size_t userfullName_pos = line.find("fullName") + 12;
    size_t enduserfullName_pos = line.find("\"", userfullName_pos);
    std::string userfullName = line.substr(userfullName_pos, enduserfullName_pos - userfullName_pos);
    return userfullName;
}

std::string extractuserBio(std::string line)
{
    size_t userBio_pos = line.find("biography") + 13;
    size_t enduserBio_pos = line.find("\"", userBio_pos);
    std::string userBio = line.substr(userBio_pos, enduserBio_pos - userBio_pos);
    return userBio;
}

// extracting notification information from the user input
Notification extractuserpauseAll(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t pauseAll_pos = userNotifications.find("pauseAll") + 12;
    size_t endpauseAll_pos = userNotifications.find("\"", pauseAll_pos);
    std::string pauseAll = userNotifications.substr(pauseAll_pos, endpauseAll_pos - pauseAll_pos);
    Notification pAll(pauseAll);
    return pAll;
}

likeNotification extractuserlikeNotif(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t likes_pos = userNotifications.find("likes") + 9;
    size_t endlikes_pos = userNotifications.find("\"", likes_pos);
    std::string likes = userNotifications.substr(likes_pos, endlikes_pos - likes_pos);
    likeNotification like(likes);
    return like;
}

tagNotification extractusertagNotif(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t tags_pos = userNotifications.find("tags") + 8;
    size_t endtags_pos = userNotifications.find("\"", tags_pos);
    std::string tags = userNotifications.substr(tags_pos, endtags_pos - tags_pos);
    tagNotification tag(tags);
    return tag;
}

commentNotification extractusercommentNotif(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t comments_pos = userNotifications.find("comments") + 12;
    size_t endcomments_pos = userNotifications.find("\"", comments_pos);
    std::string comments = userNotifications.substr(comments_pos, endcomments_pos - comments_pos);
    commentNotification comment(comments);
    return comment;
}

followNotification extractuserfollowNotif(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t newFollowers_pos = userNotifications.find("newFollowers") + 16;
    size_t endnewFollowers_pos = userNotifications.find("\"", newFollowers_pos);
    std::string newFollowers = userNotifications.substr(newFollowers_pos, endnewFollowers_pos - newFollowers_pos);
    followNotification follow(newFollowers);
    return follow;
}

messagereqNotification extractusermsgNotif(std::string line)
{
    size_t notifications_pos = line.find("notifications") + 19;
    size_t endnotifications_pos = line.find("}", notifications_pos);
    std::string userNotifications = line.substr(notifications_pos, endnotifications_pos - notifications_pos);

    size_t messageRequests_pos = userNotifications.find("messageRequests") + 19;
    size_t endmessageRequests_pos = userNotifications.find("\"", messageRequests_pos);
    std::string messageRequests = userNotifications.substr(messageRequests_pos, endmessageRequests_pos - messageRequests_pos);
    messagereqNotification messageR(messageRequests);
    return messageR;
}

// functions for extracting the post information to create instances of each post
std::string extractpostId(std::string line)
{
    size_t postId_pos = line.find("id") + 5;
    size_t endpostId_pos = line.find("\"", postId_pos);
    std::string postId = line.substr(postId_pos, endpostId_pos - postId_pos);
    return postId;
}

std::string extractpostType(std::string line)
{
    size_t postType_pos = line.find("type") + 7;
    size_t endpostType_pos = line.find("\"", postType_pos);
    std::string postType = line.substr(postType_pos, endpostType_pos - postType_pos);
    return postType;
}

std::string extractpostCaption(std::string line)
{
    size_t postCaption_pos = line.find("caption") + 10;
    size_t endpostCaption_pos = line.find("\"", postCaption_pos);
    std::string postCaption = line.substr(postCaption_pos, endpostCaption_pos - postCaption_pos);
    return postCaption;
}

std::string extractpostHashtags(std::string line)
{
    size_t hashtags_pos = line.find("hashtags") + 10;
    size_t starthashtag_pos = line.find("[", hashtags_pos) + 1;
    size_t endhashtags_pos = line.find("]", starthashtag_pos);

    std::string postHashtags = line.substr(starthashtag_pos, endhashtags_pos - starthashtag_pos);

    return postHashtags;
}

std::string extractpostMentions(std::string line)
{
    size_t mentions_pos = line.find("mentions") + 10;
    size_t startmentions_pos = line.find("[", mentions_pos) + 1;
    size_t endmentions_pos = line.find("]", startmentions_pos);

    std::string postMentions = line.substr(startmentions_pos, endmentions_pos - startmentions_pos);

    return postMentions;
}

std::string extractpostUrl(std::string line)
{
    size_t postUrl_pos = line.find("url") + 6;
    size_t endpostUrl_pos = line.find("\"", postUrl_pos);
    std::string postUrl = line.substr(postUrl_pos, endpostUrl_pos - postUrl_pos);
    return postUrl;
}

std::string extractpostcommentsCount(std::string line)
{
    size_t postcommentsCount_pos = line.find("commentsCount") + 15;
    size_t endpostcommentsCount_pos = line.find(",", postcommentsCount_pos);
    std::string postcommentCount = line.substr(postcommentsCount_pos, endpostcommentsCount_pos - postcommentsCount_pos);
    return postcommentCount;
}

std::string extractpostdisplayUrl(std::string line)
{
    size_t postdisplayUrl_pos = line.find("displayUrl") + 13;
    size_t endpostdisplayUrl_pos = line.find("\"", postdisplayUrl_pos);
    std::string postdisplayUrl = line.substr(postdisplayUrl_pos, endpostdisplayUrl_pos - postdisplayUrl_pos);
    return postdisplayUrl;
}

std::string extractpostImages(std::string line)
{
    size_t images_pos = line.find("images") + 8;
    size_t startimages_pos = line.find("[", images_pos) + 1;
    size_t endimages_pos = line.find("]", startimages_pos);

    std::string postImages = line.substr(startimages_pos, endimages_pos - startimages_pos);

    return postImages;
}

std::string extractpostlikesCount(std::string line)
{
    size_t postlikesCount_pos = line.find("likesCount") + 12;
    size_t endpostlikesCount_pos = line.find(",", postlikesCount_pos);
    std::string postlikesCount = line.substr(postlikesCount_pos, endpostlikesCount_pos - postlikesCount_pos);
    return postlikesCount;
}

std::string extractpostTimestamp(std::string line)
{
    size_t postTimestamp_pos = line.find("timestamp") + 12;
    size_t endpostTimestamp_pos = line.find("\"", postTimestamp_pos);
    std::string postTimestamp = line.substr(postTimestamp_pos, endpostTimestamp_pos - postTimestamp_pos);
    return postTimestamp;
}

std::string extractpostownerUsername(std::string line)
{
    size_t postownerUsername_pos = line.find("ownerUsername") + 16;
    size_t endpostownerUsername_pos = line.find("\"", postownerUsername_pos);
    std::string postownerUsername = line.substr(postownerUsername_pos, endpostownerUsername_pos - postownerUsername_pos);
    return postownerUsername;
}

std::string extractpostownerId(std::string line)
{
    size_t postownerId_pos = line.find("ownerId") + 10;
    size_t endpostownerId_pos = line.find("\"", postownerId_pos);
    std::string postownerId = line.substr(postownerId_pos, endpostownerId_pos - postownerId_pos);
    return postownerId;
}

// extracting tagged user information from the post information
std::string extracttaggedId(std::string line)
{
    size_t id_pos = line.find("id\":") + 5;
    size_t endid_pos = line.find("\"", id_pos);
    std::string taggedId = line.substr(id_pos, endid_pos - id_pos);
    return taggedId;
}

std::string extracttaggedUsername(std::string line)
{
    size_t username_pos = line.find("username") + 11;
    size_t endusername_pos = line.find("\"", username_pos);
    std::string taggedUsername = line.substr(username_pos, endusername_pos - username_pos);
    return taggedUsername;
}

// extracting all the tagged users from a post
std::vector<taggedUser> extractposttaggedUsers(std::string line)
{
    std::vector<taggedUser> taggedUsers;
    if (line.find("taggedUsers") != std::string::npos)
    {
        size_t tagged_pos = line.find("taggedUsers") + 14; // starts at {
        size_t endtagged_pos = line.find("]", tagged_pos);
        std::string taggedLine = line.substr(tagged_pos, endtagged_pos - tagged_pos);
        int count = std::count(taggedLine.begin(), taggedLine.end(), '{');

        if (count > 1)
        {
            for (int i = 0; i < count; i++)
            {
                size_t start = taggedLine.find("{");
                size_t end = taggedLine.find("}", start);
                std::string taguser = taggedLine.substr(start, end - start);
                taggedUsers.push_back(taggedUser(extracttaggedId(taguser), extracttaggedUsername(taguser)));
                taggedLine.erase(start, (end - start) + 1);
            }
        }
    }
    else
    {
        taggedUsers.push_back(taggedUser());
    }
    return taggedUsers;
}

int main(int argc, char *argv[])
{
    // exception for if there are not enough command line arguments provided
    try
    {
        if (argc < 5)
        {
            throw std::runtime_error("expected 5 command line arguments");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // command line inputs
    std::string posts_in = argv[1];
    std::string users_in = argv[2];
    std::string events_in = argv[3];
    std::string output = argv[4];
    std::string username_in = argv[5];

    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream postJSON(posts_in);
    if (!postJSON.is_open())
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }

    // taking in the post file lines and creating a post object for each line
    std::vector<IGPost> igposts;
    std::string line;
    while (std::getline(postJSON, line))
    {
        igposts.push_back(IGPost(extractpostId(line), extractpostType(line), extractpostCaption(line), extractpostHashtags(line), extractpostMentions(line), extractpostUrl(line), extractpostcommentsCount(line), extractpostdisplayUrl(line), extractpostImages(line), extractpostlikesCount(line), extractpostTimestamp(line), extractpostownerUsername(line), extractpostownerId(line), extractposttaggedUsers(line)));
    }
    // don't need this json file anymore, as the content is read into json_content.
    postJSON.close();

    // assume inputFile is a std::string, containing the file name of the input file.
    std::ifstream userJSON(users_in);
    if (!userJSON.is_open())
    {
        std::cerr << "Failed to open the JSON file." << std::endl;
        exit(1);
    }

    // taking in the user file lines and creating a user object for each line
    std::vector<User> igusers;
    std::string line2;
    while (std::getline(userJSON, line2))
    {
        igusers.push_back(User(extractuserId(line2), extractuserUsername(line2), extractuserUrl(line2), extractuserfullName(line2), extractuserBio(line2), extractuserpauseAll(line2), extractuserlikeNotif(line2), extractusertagNotif(line2), extractusercommentNotif(line2), extractuserfollowNotif(line2), extractusermsgNotif(line2)));
    }
    // don't need this json file anymore, as the content is read into json_content.
    userJSON.close();

    std::ifstream eventsfile(events_in);
    if (!eventsfile.is_open())
    {
        std::cerr << "Failed to open the txt file." << std::endl;
        exit(1);
    }

    // taking in event file lines and creating event objects for each line, and adding to stack to maintain order
    std::stack<Event> events;
    std::string line3;
    while (std::getline(eventsfile, line3))
    {
        if (line3.find("likes") != std::string::npos)
        {

            size_t type_pos = line3.find("likes");
            std::string type = line3.substr(type_pos, 5);

            size_t liker_pos = 0;
            size_t endliker_pos = line3.find(" ", liker_pos);
            std::string liker = line3.substr(liker_pos, endliker_pos - liker_pos);

            size_t liked_pos = line3.find("likes") + 6;
            size_t endliked_pos = line3.size();
            std::string liked = line3.substr(liked_pos, endliked_pos - liked_pos);

            Event l_event(type, liker, liked, 0);
            events.push(l_event);
        }
        else if (line3.find("tags") != std::string::npos)
        {

            size_t type_pos = line3.find("tags");
            std::string type = line3.substr(type_pos, 4);

            size_t tagger_pos = 0;
            size_t endtagger_pos = line3.find(" ", tagger_pos);
            std::string tagger = line3.substr(tagger_pos, endtagger_pos - tagger_pos);

            size_t tagged_pos = line3.find("tags") + 5;
            size_t endtagged_pos = line3.size();
            std::string tagged = line3.substr(tagged_pos, endtagged_pos - tagged_pos);

            Event t_event(type, tagger, tagged, 0);
            events.push(t_event);
        }
        else if (line3.find("comments_on") != std::string::npos)
        {
            size_t type_pos = line3.find("comments_on");
            std::string type = line3.substr(type_pos, 11);

            size_t commenter_pos = 0;
            size_t endcommenter_pos = line3.find(" ", commenter_pos);
            std::string commenter = line3.substr(commenter_pos, endcommenter_pos - commenter_pos);

            size_t commented_pos = line3.find("comments_on") + 12;
            size_t endcommented_pos = line3.size();
            std::string commented = line3.substr(commented_pos, endcommented_pos - commented_pos);

            Event cEvent(type, commenter, commented, 0);
            events.push(cEvent);
        }
        else if (line3.find("follows") != std::string::npos)
        {
            size_t type_pos = line3.find("follows");
            std::string type = line3.substr(type_pos, 7);

            size_t follower_pos = 0;
            size_t endfollower_pos = line3.find(" ", follower_pos);
            std::string follower = line3.substr(follower_pos, endfollower_pos - follower_pos);

            size_t followed_pos = line3.find("follows") + 8;
            size_t endfollowed_pos = line3.size();
            std::string followed = line3.substr(followed_pos, endfollowed_pos - followed_pos);

            Event fEvent(type, follower, followed, 0);
            events.push(fEvent);
        }
        else if (line3.find("messageRequests") != std::string::npos)
        {
            size_t type_pos = line3.find("messageRequests");
            std::string type = line3.substr(type_pos, 15);

            size_t messenger_pos = 0;
            size_t endmessenger_pos = line3.find(" ", messenger_pos);
            std::string messenger = line3.substr(messenger_pos, endmessenger_pos - messenger_pos);

            size_t messaged_pos = line3.find("messageRequests") + 16;
            size_t endmessaged_pos = line3.size();
            std::string messaged = line3.substr(messaged_pos, endmessaged_pos - messaged_pos);

            Event mEvent(type, messenger, messaged, 0);
            events.push(mEvent);
        }
    }

    eventsfile.close();

    // initialize file for output
    std::ofstream ignotifications(output);

    // obtaining the input users information
    std::vector<User>::iterator it = std::find(igusers.begin(), igusers.end(), username_in);
    if (it != igusers.end())
    {
        // output nothing if all notifications are toggled off
        if (it->getuserpauseAll() == "true")
        {
            ignotifications << "";
        }
        else
        {
            std::string user_id = it->getuserId();
            std::vector<IGPost> searched_posts;
            for (long unsigned int i = 0; i < igposts.size(); i++)
            { // searching for all their posts
                if (igposts[i].getaownerUsername() == username_in)
                {
                    searched_posts.push_back(igposts[i]);
                }
            }

            // if the user has pauseAll disabled, but each notification off individually, handle this case
            if (it->getuserlikeNotif() == "false" && it->getusertagNotif() == "false" && it->getusercommentNotif() == "false" && it->getuserfollowNotif() == "false" && it->getusermessagereqNotif() == "false")
            {
                ignotifications << "";
            }
            else
            {
                // ordering the events with an integer representing the order they appear
                int oCount = 1;
                std::stack<Event> EventsOrdered;
                while (!events.empty())
                {
                    Event top = events.top();
                    top.setOrder(oCount);
                    EventsOrdered.push(top);
                    events.pop();
                    oCount++;
                }

                // storing each of the respective events
                std::vector<Event> likeEvents;
                std::vector<Event> tagEvents;
                std::vector<Event> commentEvents;
                std::vector<Event> followEvents;
                std::vector<Event> msgEvents;

                if (it->getuserlikeNotif() == "true")
                {
                    std::stack<Event> EventsOrderedl = EventsOrdered;
                    while (!EventsOrderedl.empty())
                    {
                        Event top = EventsOrderedl.top();
                        bool match = false;
                        for (long unsigned int x = 0; x < igposts.size(); x++)
                        {
                            if (igposts[x] == top.getSecond() && igposts[x].getaownerUsername() == username_in)
                            {
                                match = true;
                            }
                        }
                        if (top.getType() == "likes" && match)
                        {
                            likeEvents.push_back(top);
                        }
                        EventsOrderedl.pop();
                    }
                }

                if (it->getusertagNotif() == "true")
                {
                    std::stack<Event> EventsOrderedt = EventsOrdered;
                    while (!EventsOrderedt.empty())
                    {
                        Event top = EventsOrderedt.top();
                        if (top.getType() == "tags" && top.getSecond() == username_in)
                        {
                            tagEvents.push_back(top);
                        }
                        EventsOrderedt.pop();
                    }
                }

                if (it->getusercommentNotif() == "true")
                {
                    std::stack<Event> EventsOrderedc = EventsOrdered;
                    while (!EventsOrderedc.empty())
                    {
                        Event top = EventsOrderedc.top();
                        bool match = false;
                        for (long unsigned int x = 0; x < igposts.size(); x++)
                        {
                            if (igposts[x] == top.getSecond() && igposts[x].getaownerUsername() == username_in)
                            {
                                match = true;
                            }
                        }
                        if (top.getType() == "comments_on" && match)
                        {
                            commentEvents.push_back(top);
                        }
                        EventsOrderedc.pop();
                    }
                }

                if (it->getuserfollowNotif() == "true")
                {
                    std::stack<Event> EventsOrderedf = EventsOrdered;
                    while (!EventsOrderedf.empty())
                    {
                        Event top = EventsOrderedf.top();
                        if (top.getType() == "follows" && top.getSecond() == username_in)
                        {
                            followEvents.push_back(top);
                        }
                        EventsOrderedf.pop();
                    }
                }

                if (it->getusermessagereqNotif() == "true")
                {
                    std::stack<Event> EventsOrderedm = EventsOrdered;
                    while (!EventsOrderedm.empty())
                    {
                        Event top = EventsOrderedm.top();
                        if (top.getType() == "messageRequests" && top.getSecond() == username_in)
                        {
                            msgEvents.push_back(top);
                        }
                        EventsOrderedm.pop();
                    }
                }

                // vector of all the events which we need to output, which adds all the individual notification events
                std::vector<Event> allEvents;
                allEvents.insert(allEvents.end(), likeEvents.begin(), likeEvents.end());
                allEvents.insert(allEvents.end(), tagEvents.begin(), tagEvents.end());
                allEvents.insert(allEvents.end(), commentEvents.begin(), commentEvents.end());
                allEvents.insert(allEvents.end(), followEvents.begin(), followEvents.end());
                allEvents.insert(allEvents.end(), msgEvents.begin(), msgEvents.end());

                // event is sorted based on its order integer, implemented in events class
                std::sort(allEvents.begin(), allEvents.end());
                // creating consecuitive integer to track if there are consecutive notifications of the same type, for aggregation
                int consecutive = 1;

                // handling case if there is only 1 notification to output
                if (allEvents.size() == 1)
                {
                    for (unsigned long int l = 0; l < allEvents.size(); l++)
                    {
                        if (allEvents[l].getType() == "likes")
                        {
                            ignotifications << allEvents[l].getFirst() << " liked your post." << std::endl;
                        }
                        else if (allEvents[l].getType() == "tags")
                        {
                            ignotifications << allEvents[l].getFirst() << " tagged you in a post." << std::endl;
                        }
                        else if (allEvents[l].getType() == "comments_on")
                        {
                            ignotifications << allEvents[l].getFirst() << " commented on your post." << std::endl;
                        }
                        else if (allEvents[l].getType() == "follows")
                        {
                            ignotifications << allEvents[l].getFirst() << " started following you." << std::endl;
                        }
                        else if (allEvents[l].getType() == "messageRequests")
                        {
                            ignotifications << allEvents[l].getFirst() << " wants to send you a message." << std::endl;
                        }
                    }
                }
                // if there are more than 100 notifications to output, limit the amount of lines to output to 100 with lines variable
                else if (allEvents.size() > 100)
                {
                    int lines = 0;
                    for (long unsigned int z = 1; z < allEvents.size() && lines < 100; z++)
                    {
                        // keeping track of consecutive notification types, handling accordingly if there are more than 3
                        if (allEvents[z].getType() == allEvents[z - 1].getType())
                        {
                            consecutive++;
                        }
                        else
                        {
                            if (consecutive > 3 && lines < 100)
                            {
                                if (allEvents[z - 1].getType() == "messageRequests")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others wants to send you a message." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "likes")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others liked your post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "tags")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others tagged you in a post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "comments_on")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others commented on your post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "follows")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others started following you." << std::endl;
                                }
                                lines += 1;
                            }
                            else
                            {
                                // if not consecutive, just output regularly
                                for (unsigned long int l = z - consecutive; l < z && lines < 100; l++)
                                {
                                    if (allEvents[l].getType() == "likes")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " liked your post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "tags")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " tagged you in a post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "comments_on")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " commented on your post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "follows")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " started following you." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "messageRequests")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " wants to send you a message." << std::endl;
                                    }

                                    lines++;
                                }
                            }
                            consecutive = 1;
                        }
                    }
                }
                else
                {
                    // if there are less than 100 notifications to output, but more than 1, just iterate through all of them
                    for (long unsigned int z = 1; z < allEvents.size(); z++)
                    {
                        // keeping track of consecutive notification types, handling accordingly if there are more than 3
                        if (allEvents[z].getType() == allEvents[z - 1].getType())
                        {
                            consecutive++;
                        }
                        else
                        {
                            if (consecutive > 3)
                            {
                                if (allEvents[z - 1].getType() == "messageRequests")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others wants to send you a message." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "likes")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others liked your post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "tags")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others tagged you in a post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "comments_on")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " commented on your post." << std::endl;
                                }
                                else if (allEvents[z - 1].getType() == "follows")
                                {
                                    ignotifications << allEvents[z - consecutive].getFirst() << ", "
                                                    << allEvents[z - consecutive + 1].getFirst()
                                                    << " and " << (consecutive - 2) << " others started following you." << std::endl;
                                }
                            }
                            else
                            {
                                // if not consecutive, just output regularly
                                for (unsigned long int l = z - consecutive; l < z; l++)
                                {

                                    if (allEvents[l].getType() == "likes")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " liked your post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "tags")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " tagged you in a post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "comments_on")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " commented on your post." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "follows")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " started following you." << std::endl;
                                    }
                                    else if (allEvents[l].getType() == "messageRequests")
                                    {
                                        ignotifications << allEvents[l].getFirst() << " wants to send you a message." << std::endl;
                                    }
                                    // handling case where output stops prematurely, and gives out last notification
                                    if (allEvents.size() - l == 2)
                                    {
                                        if (allEvents[l + 1].getType() == "likes")
                                        {
                                            ignotifications << allEvents[l + 1].getFirst() << " liked your post." << std::endl;
                                        }
                                        else if (allEvents[l + 1].getType() == "tags")
                                        {
                                            ignotifications << allEvents[l + 1].getFirst() << " tagged you in a post." << std::endl;
                                        }
                                        else if (allEvents[l + 1].getType() == "comments_on")
                                        {
                                            ignotifications << allEvents[l + 1].getFirst() << " commented on your post." << std::endl;
                                        }
                                        else if (allEvents[l + 1].getType() == "follows")
                                        {
                                            ignotifications << allEvents[l + 1].getFirst() << " started following you." << std::endl;
                                        }
                                        else if (allEvents[l + 1].getType() == "messageRequests")
                                        {
                                            ignotifications << allEvents[l + 1].getFirst() << " wants to send you a message." << std::endl;
                                        }
                                    }
                                }
                            }
                            consecutive = 1;
                        }
                    }
                }
            }
        }
    }
}