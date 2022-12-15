
struct users
{
    char *user;
    char *password;
    short is_admin;
    int size;
} *new_users;

struct config_model
{
    long long int commandChannelPort;
    long long int dataChannelPort;
    char **file;
} new_config_model;
