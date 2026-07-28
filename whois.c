#include <stdbool.h>

typedef struct {
    const char *name;
    int         age;
    const char *title;
} person_t;

static const person_t me = {
    .name  = "Mustafa Yavuz Ak",
    .age   = 2147483647,
    .title = "Founder"
};
