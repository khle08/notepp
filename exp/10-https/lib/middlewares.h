
// ref: https://github.com/yhirose/cpp-httplib

#ifndef MIDDLEWARES_H
#define MIDDLEWARES_H

#include <httplib.h>


// Function to validate the authentication token
bool authenticate(const httplib::Request& req);

// Middleware function for authentication
void authentication_middleware(const httplib::Request& req,
                               httplib::Response& res,
                               std::function<void()> next);

#endif // MIDDLEWARES_H

