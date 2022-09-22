//
// Created by dando on 22/09/2022.
//

#ifndef DAVIDE_FLORE_66174_LETTERS_H
#define DAVIDE_FLORE_66174_LETTERS_H

#endif //DAVIDE_FLORE_66174_LETTERS_H



char A[5][10] = {
        "    x    \0",
        "   x x   \0",
        "  xxxxx  \0",
        " x     x \0",
        "xxx   xxx\0"
};

char B[5][10] = {
        "xxxxxxxx \0",
        "x       x\0",
        "xxxxxxxx \0",
        "x       x\0",
        "xxxxxxxx \0"
};

char C[5][10] = {
        " xxxxxxx \0",
        "x       x\0",
        "x        \0",
        "x       x\0",
        " xxxxxxx \0"
};

char D[5][10] = {
        "xxxxxxx  \0",
        "x      x \0",
        "x       x\0",
        "x      x \0",
        "xxxxxxx  \0"
};

char E[5][10] = {
        "xxxxxxxxx\0",
        "x        \0",
        "xxxxxxxxx\0",
        "x        \0",
        "xxxxxxxxx\0"
};

char F[5][10] = {
        "xxxxxxxxx\0",
        "x        \0",
        "xxxxxxxxx\0",
        "x        \0",
        "x        \0"
};

char G[5][10] = {
        " xxxxxxx \0",
        "x        \0",
        "x    xxxx\0",
        "x       x\0",
        " xxxxxxx \0"
};

char H[5][10] = {
        "x   x   x\0",
        "x   x   x\0",
        "xxxxxxxxx\0",
        "x       x\0",
        "x       x\0"
};

char I[5][10] = {
        "  xxxxx  \0",
        "    x    \0",
        "    x    \0",
        "    x    \0",
        "  xxxxx  \0"
};

char J[5][10] = {
        "  xxxxx  \0",
        "    x    \0",
        "    x    \0",
        "    x    \0",
        "  xx     \0"
};

char K[5][10] = {
        "x     xxx\0",
        "x  xxx   \0",
        "xxx      \0",
        "x  xxx   \0",
        "x     xxx\0"
};

char L[5][10] = {
        "x        \0",
        "x        \0",
        "x        \0",
        "x       x\0",
        "xxxxxxxxx\0"
};

char M[5][10] = {
        "x       x\0",
        "xx     xx\0",
        "x x   x x\0",
        "x  xxx  x\0",
        "x       x\0"
};

char N[5][10] = {
        "x       x\0",
        "x x     x\0",
        "x  xxx  x\0",
        "x     x x\0",
        "x       x\0"
};

char O[5][10] = {
        " xxxxxxx \0",
        "x       x\0",
        "x       x\0",
        "x       x\0",
        " xxxxxxx \0"
};

char P[5][10] = {
        "xxxxxxxx \0",
        "x       x\0",
        "xxxxxxxx \0",
        "x        \0",
        "x        \0"
};



char numbers[10][5][10] = {
        {
                "xxxxxxxxx\0",
                "x       x\0",
                "x       x\0",
                "x       x\0",
                "xxxxxxxxx\0"
        },
        {
                "    x    \0",
                "  xxx    \0",
                "    x    \0",
                "    x    \0",
                "   xxx   \0"
        },
        {
                "xxxxxxxxx\0",
                "        x\0",
                "xxxxxxxxx\0",
                "x        \0",
                "xxxxxxxxx\0"
        },
        {
                "xxxxxxxxx\0",
                "x        \0",
                "xxxxxxxxx\0",
                "x        \0",
                "xxxxxxxxx\0"
        },
        {
                "x        \0",
                "x   x    \0",
                "xxxxxxxx \0",
                "    x    \0",
                "    x    \0"
        },
        {
                "xxxxxxxxx\0",
                "x        \0",
                "xxxxxxxxx\0",
                "        x\0",
                "xxxxxxxxx\0"
        },
        {
                "xxxxxxxxx\0",
                "x        \0",
                "xxxxxxxxx\0",
                "x       x\0",
                "xxxxxxxxx\0"
        },
        {
                "xxxxxxxxx\0",
                "        x\0",
                "        x\0",
                "        x\0",
                "        x\0"
        },
        {
                "xxxxxxxxx\0",
                "x       x\0",
                "xxxxxxxxx\0",
                "x       x\0",
                "xxxxxxxxx\0"
        },
        {
                "xxxxxxxxx\0",
                "x       x\0",
                "xxxxxxxxx\0",
                "        x\0",
                "xxxxxxxxx\0"
        },
};


void print_num(const int *numero, int dim) {

    int i, j;

    for(i = 0; i < 5; i++) {
        for(j = 0; j < dim; j++) {
            printf("%s  %s                                      ", numbers[numero[j] / 10][i], numbers[numero[j] % 10][i]);
        }
        printf("\n");
    }
}

