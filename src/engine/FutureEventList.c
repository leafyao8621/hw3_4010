#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "FutureEventList.h"

char* d2b(int n) {
    int bits = log2(n);
    char* opt = malloc(bits + 1);
    for (int i = bits - 1; i > -1; i--) {
        opt[i] = n % 2 + '0';
        n /= 2;
    }
    opt[bits] = '\0';
    return opt;
}

void up(FutureEventList* f, Event* e) {
    if (e->parent == NULL) {
        f->root = e;
    } else if (e->time_stamp < e->parent->time_stamp) {
        Event* epp = e->parent->parent;
        int is_left;
        if (epp != NULL) {
            is_left = e->parent == e->parent->parent->left;
        }
        if (e == e->parent->left) {
            Event* epr = e->parent->right;
            Event* ep = e->parent;
            Event* er = e->right;
            Event* el = e->left;
            e->left = ep;
            e->right = epr;
            e->left->left = el;
            e->left->right = er;
            e->left->parent = e;

            if (e->right != NULL) {
                e->right->parent = e;
            }
            if (e->left->left != NULL) {
                e->left->left->parent = e->left;
            }
            if (e->left->right != NULL) {
                e->left->right->parent = e->left;
            }
        } else {
            Event* epl = e->parent->left;
            Event* ep = e->parent;
            Event* er = e->right;
            Event* el = e->left;
            e->right = ep;
            e->left = epl;
            e->right->left = el;
            e->right->right = er;
            e->right->parent = e;
            if (e->left != NULL) {
                e->left->parent = e;
            }
            if (e->right->left != NULL) {
                e->right->left->parent = e->right;
            }
            if (e->right->right != NULL) {
                e->right->right->parent = e->right;
            }
        }

        if (epp == NULL) {
            e->parent = NULL;
        } else {
            if (is_left) {
                epp->left = e;
            } else {
                epp->right = e;
            }
            e->parent = epp;
        }
        up(f, e);
    }
}

void down(Event* e) {
    if (e->left == NULL && e->right == NULL) {
        return;
    }
    if (e->left == NULL || e->right == NULL) {
        if (e->right == NULL) {
            if (e->time_stamp >= e->left->time_stamp) {
                Event* ep = e->left->parent->parent;
                Event* er = e->left->parent->right;
                e->parent = e;
                e->left = NULL;
                e->right = NULL;
            }
        } else {
            if (e->time_stamp >= e->right->time_stamp) {
                
            }
        }
    } else {
        if (e->time_stamp >= e->left->time_stamp ||
            e->time_stamp >= e->right->time_stamp) {
            if (e->left->left == NULL && e->left->right == NULL &&
                e->right->left == NULL && e->right->right == NULL) {
                if (e->left->time_stamp < e->right->time_stamp) {
                    

                }
            }
        }
    }

    down(e);
}

int set_last(FutureEventList* f) {
    if (f == NULL) {
        return 1;
    }
    char* seq = d2b(f->cnt);
    Event* temp = f->root;
    int i = 0;
    while (seq[i] != '\0') {
        if (seq[i] == '0') {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
        i++;
    }
    f->last = temp;
    free(seq);
    return 0;
}

Event* find_par(FutureEventList* f) {
    if (f == NULL) {
        return NULL;
    }
    char* seq = d2b(f->cnt);

    Event* temp = f->root;
    int i = 0;
    while (seq[i + 1] != '\0') {
        if (seq[i] == '0') {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
        i++;
    }
    free(seq);
    return temp;
}

FutureEventList* new_FutureEventList() {
    FutureEventList* opt = malloc(sizeof(FutureEventList));
    if (opt == NULL) {
        puts("Fatal error! Out of memory!");
        return NULL;
    }
    opt->root = NULL;
    opt->last = NULL;
    opt->cnt = 0;
    return opt;
}

int schedule(FutureEventList* f, Event* e) {
    if (f == NULL || e == NULL) {
        return 1;
    }
    if (f->cnt == 0) {
        f->root = e;
        f->last = e;
        f->cnt++;
    } else {
        f->cnt++;
        Event* par = find_par(f);
        e->parent = par;
        if (par->left == NULL) {
            par->left = e;
        } else {
            par->right = e;
        }
        up(f, e);
        set_last(f);
    }

    return 0;
}

int remove_event(FutureEventList* f) {
    if (f == NULL || f->root == NULL) {
        return 1;
    }
    if (f->cnt == 1) {
        free(f->root);
        f->root = NULL;
        f->last = NULL;
        f->cnt = 0;
        return 0;
    }
    Event* rl = f->root->left;
    Event* rr = f->root->right;
    free(f->root);
    f->root = f->last;
    if (f->last == f->last->parent->right) {
        f->last->parent->right = NULL;
    } else {
        f->last->parent->left = NULL;
    }
    f->root->left = rl;
    f->root->right = rr;

    down(f->root);
    f->cnt--;
    set_last(f);

    return 0;
}
