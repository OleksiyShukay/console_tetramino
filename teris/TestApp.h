#pragma once
#include "BaseApp.h"
class TestApp : public BaseApp {//TestApp наследует BaseApp

typedef BaseApp Parent;//Parent псевдоним BaseApp

private:
  int mObj1XOld;
  int mObj1YOld;
  int mObj1X;
  int mObj1Y;

  int mObj2X;
  int mObj2Y;

  bool mDirection;

public:
  TestApp();
  virtual void KeyPressed(int btnCode);
  virtual void UpdateF(float deltaTime);
};