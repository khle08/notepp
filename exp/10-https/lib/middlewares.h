
// ref: https://github.com/yhirose/cpp-httplib

#ifndef MIDDLEWARES_H
#define MIDDLEWARES_H

#include <httplib.h>

using namespace httplib;


// Function to validate the authentication token
bool authenticate(const Request& req);

// Middleware function for authentication
void authentication_middleware(const Request& req, Response& res,
                               std::function<void()> next);

#endif // MIDDLEWARES_H

