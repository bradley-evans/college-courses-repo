#ifndef BASECMD_H
#define BASECMD_H
#include <iostream>
using namespace std;

class BaseCmd {
  public:
    BaseCmd() { };
    virtual int execute() = 0;
    virtual void addLeft(BaseCmd* l) = 0;
    virtual void addRight(BaseCmd* r) = 0;
    virtual ~BaseCmd() {};
};
#endif
