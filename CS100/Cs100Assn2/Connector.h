#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "BaseCmd.h"

enum ConType {success, failure, next};

class Connector : public BaseCmd {
    private:
        BaseCmd* left;
        BaseCmd* right;
        ConType type;
    public:
        Connector() { };
        Connector(ConType t) : type(t) {};
        Connector(BaseCmd* l, BaseCmd* r, ConType t) : left(l), right(r), 
            type(t) { };
        void addLeft(BaseCmd* l) {
            left = l;
        };
        void addRight(BaseCmd* r) {
            right = r;
        };
        int execute() {
            int status = left->execute();
            if(status == 0 && type == success){
                status = right->execute();        
            }
            else if(status != 0 && type == failure){
                status = right->execute();
            }
            else if(type == next){
                status = right->execute();                
            }
            return status;
        };
        ~Connector() {
            delete left;
            delete right;
        };
};
#endif