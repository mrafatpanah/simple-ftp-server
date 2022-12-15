
#include <string.h>


char *read_file(const char *path) {

    FILE *input = fopen(path, "r");

    char *line = NULL;
    size_t line_capacity = 0;
    char *buf;
    buf = malloc(sizeof(char) * 8096);

    while(getline(&line, &line_capacity, input) > 0 ) {
        size_t last_idx = strlen(line) - 1;
        if(line[last_idx] == '\n')
            line[last_idx] = '\0';
        strcat(buf, line);
    }
    return buf;
}

void parse_config() {

    json_t *root = load_json(read_file("./src/config.json"));
    
    json_t *commandChannelPort = json_object_get(root, "commandChannelPort");
    new_config_model.commandChannelPort = json_integer_value(commandChannelPort);

    json_t *dataChannelPort = json_object_get(root, "dataChannelPort");
    new_config_model.dataChannelPort = json_integer_value(dataChannelPort);

    json_t *array_object = json_object_get(root, "users");
    int array_num = json_array_size(array_object);
    new_users = malloc(sizeof(struct users) * array_num);

    for(int i = 0; i < array_num; i++) {
        json_t *arr1 = json_array_get(array_object, i);
        
        json_t *user = json_object_get(arr1, "user");
        new_users[i].user = malloc(sizeof(char) * 100);
        new_users[i].user = json_string_value(user);
        
        json_t *password = json_object_get(arr1, "password");
        new_users[i].password = malloc(sizeof(char) * 100);
        new_users[i].password = json_string_value(password);

        json_t *admin = json_object_get(arr1, "admin");
        if (!strcmp(json_string_value(admin), "true"))
            new_users[i].is_admin = 1;
        else 
            new_users[i].is_admin = 0;
        json_t *size = json_object_get(arr1, "size");
        new_users[i].size = atoi(json_string_value(size));

        printf("user: %s\npass: %s\nadmin: %d\nsize: %d\n", 
                        new_users[i].user, new_users[i].password, 
                        new_users[i].is_admin, new_users[i].size);
    }

    json_t *files = json_object_get(root, "files");
    array_num = json_array_size(files);
    new_config_model.file = malloc(sizeof(char*) * array_num);
    for(int i = 0; i < array_num; i++) {
        new_config_model.file[i] = malloc(100);
        json_t *arr1 = json_array_get(files, i);
        new_config_model.file[i] = json_string_value(arr1);
        printf("files[%d]: %s\n", i, new_config_model.file[i]);
    }
}
