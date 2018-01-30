#ifndef __SHAREDCONTEXT__
#define __SHAREDCONTEXT__

class SharedContext {
public:
  SharedContext();
  bool isParkingMode();
  bool isMovingMode();
  bool isOffMode();
  void setMode(int modality);

private:
  int  modality;
};

#endif

