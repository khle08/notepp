
#include "param.h"


int main()
{
    Param* p = new Param("/Users/kcl/Documents/Cpp_Projects/cpp_notes/cpp/param/test.yaml", false);

    print(p->getValue("MODEL_NAME"));

    int res = p->updateValue("MODEL_NAME", "abc");
    if (res < 0) {
        print("failed to update value");
    }

    print(p->getValue("MODEL_NAMEs"));

    print("totalParam: " << p->totalParam);

    delete p;
    return 0;
}



