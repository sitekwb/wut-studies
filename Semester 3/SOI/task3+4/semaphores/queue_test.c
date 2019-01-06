//
// Created by Wojciech Sitek on 30/11/2018.
//
#include "sem.h"
int main() {
    char c;
    while (1) {
        printf("Add(a)/Pop(p)/Finish(0). Your decision: ");
        scanf("%2c", &c);
        if (c == 'a') {
            printf("Your char: ");
            scanf("%2c", &c);
            add_queue_char(&buffer, c);
        } else if (c == 'p') {
            if ((c = pick_queue_char(&buffer))) {
                printf("Your char is: %c\n", c);
            }
        } else break;
    }
    return 0;
}