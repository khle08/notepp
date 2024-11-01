
// ref: https://github.com/yhirose/cpp-httplib

#ifndef ROUTES_H
#define ROUTES_H

#include <httplib.h>
#include "middlewares.h"


// Function to set up router
void router(httplib::Server& server);


#endif // ROUTES_H
