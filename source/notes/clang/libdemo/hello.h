#ifndef __HELLO__
#define __HELLO__

/*
// First version would be
void hello_message(const char *name);

//Later:
*/

#ifdef __cplusplus
    extern "C" void hello_message(const char *name);
#else
    void hello_message(const char *name);
#endif


#endif
