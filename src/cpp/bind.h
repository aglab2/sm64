#define BINDED_FN(module, cl, fn) module##_##cl##_##fn
#define BIND_PROXY(module, cl, fn) extern void BINDED_FN(module, cl, fn) ();
