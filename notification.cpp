#include "notification.h"

// Notification class constructors
Notification::Notification() : pauseAll("") {}

Notification::Notification(std::string on) : pauseAll(on) {}

// likeNotification class constructors
likeNotification::likeNotification() : liken("") {}

likeNotification::likeNotification(std::string on) : liken(on) {}

// tagNotification class constructors
tagNotification::tagNotification() : tagn("") {}

tagNotification::tagNotification(std::string on) : tagn(on) {}


// commentNotification class constructors
commentNotification::commentNotification() : commentn("") {}

commentNotification::commentNotification(std::string on) : commentn(on) {}



// followNotification class constructors
followNotification::followNotification() : follown("") {}

followNotification::followNotification(std::string on) : follown(on) {}



// messagereqNotification class constructors
messagereqNotification::messagereqNotification() : messagen("") {}

messagereqNotification::messagereqNotification(std::string on) : messagen(on) {}

