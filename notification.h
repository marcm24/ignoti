#include <iostream>

#ifndef __NOTIFICATION_H
#define __NOTIFICATION_H

/* 
notification class for storing if the notifications are enabled or not. contains base notification class to contain the pauseAll option, and other derived notification classes for each type.
contains virtual isEnabled function which is inherited among other derived classes. each derived notification class has a C1 IS A C2 relationship with the base notification 
class, as each derived notification type is a notification.
*/

class Notification {
    public:
        Notification();
        Notification(std::string pauseAll);

        virtual std::string isEnabled() const {
            return pauseAll;
        }
        
    protected:
        std::string pauseAll;

};

class likeNotification : public Notification { 
    public:
        likeNotification();
        likeNotification(std::string on);

        std::string isEnabled() const override {
            return liken;
        }
    private:
        std::string liken;
};

class tagNotification: public Notification {
    public:
        tagNotification();
        tagNotification(std::string on);
        
        std::string isEnabled() const override {
            return tagn;
        }
    private:
        std::string tagn;
};

class commentNotification: public Notification {
    public:
        commentNotification();
        commentNotification(std::string on);

        std::string isEnabled() const  override {
            return commentn;
        }
    private:
        std::string commentn;

};

class followNotification: public Notification {
    public:
        followNotification();
        followNotification(std::string on);

        std::string isEnabled() const override {
            return follown;
        }
    private:
        std::string follown;
};

class messagereqNotification: public Notification {
    public:
        messagereqNotification();
        messagereqNotification(std::string on);

        std::string isEnabled() const override {
            return messagen;
        }
    private:
        std::string messagen;
};

#endif