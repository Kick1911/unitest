void suite_setup(void** args){
    char* ptr;
    args[0] = "This is a test";
    args[1] = malloc(sizeof(char));
    ptr = args[1];
    *ptr = 'T';
}

void suite_teardown(void** args){
    free(args[1]);
}
