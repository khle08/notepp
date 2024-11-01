
// ref: https://github.com/yhirose/cpp-httplib

#include "middlewares.h"

#define printMiddleware(x) std::cout << x << std::endl;


// Function to validate the authentication token
bool authenticate(const Request& req)
{
    // Extract token from headers (e.g., Authorization header)
    auto auth_header = req.get_header_value("Authorization");
    const std::string expected_token = "Bearer YOUR_SECRET_TOKEN";

    // Check if the token matches the expected one
    return auth_header == expected_token;
}


// Middleware function for authentication
void authentication_middleware(const Request& req, Response& res,
                               std::function<void()> next)
{
    if (authenticate(req)) {
        // If authenticated, call the next handler
        next();
    } else {
        // If not authenticated, set 401 Unauthorized status
        res.status = 401;
        res.set_content("Unauthorized", "text/plain");
    }
}

