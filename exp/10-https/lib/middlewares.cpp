
#include "middlewares.h"

#define printMiddleware(x) std::cout << x << std::endl;


// Function to validate the authentication token
bool authenticate(const httplib::Request& req)
{
    // Extract token from headers (e.g., Authorization header)
    auto auth_header = req.get_header_value("Authorization");
    const std::string expected_token = "Bearer YOUR_SECRET_TOKEN";

    // Check if the token matches the expected one
    return auth_header == expected_token;
}


// Middleware function for authentication
void authentication_middleware(const httplib::Request& req,
                               httplib::Response& res,
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

