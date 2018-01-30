#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

class SharedContext {
public:
  SharedContext();
  bool isInUse();
  void setUsing(bool inUse);    
  bool isSomeoneInside();
  void setSomeoneInside(bool inUse);    
  void trackNewWCUsage();
  int getWCUsageCount();
  bool isCleaning();
  void setCleaning(bool cleaning);
  void setAlarm(bool alarm);
  bool isAlarmOn();
  int getNUsers();
  void trackNewUser();

private:
  bool inUse;
  bool inside;
  int  wcUsageCount;
  bool cleaning;
  int  userCount;
  bool alarm;
};

#endif

