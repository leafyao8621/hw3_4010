#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "FutureEventList.h"

struct FutureEventList {
    Event* root;
    Event* last;
    int cnt;
};

void up(FutureEventList* f, Event* e) {
    if (get_parent(e) == NULL) {
        f->root = e;
    } else if (get_time_stamp(e) < get_time_stamp(get_parent(e))) {
        Event* epp = get_parent(get_parent(e));
        int is_left;
        if (epp != NULL) {
            is_left = get_parent(e) == get_left(get_parent(get_parent(e)));
        }
        if (e == get_left(get_parent(e))) {
            Event* epr = get_right(get_parent(e));
            Event* ep = get_parent(e);
            Event* er = get_right(e);
            Event* el = get_left(e);
            set_left(e, ep);
            set_right(e, epr);
            set_left(get_left(e), el);
            set_right(get_left(e), er);
            set_parent(get_left(e), e);
            set_parent(get_right(e), e);
            set_parent(get_left(get_left(e)), get_left(e));
            set_parent(get_right(get_left(e)), get_left(e));
        } else {
            Event* epl = get_left(get_parent(e));
            Event* ep = get_parent(e);
            Event* er = get_right(e);
            Event* el = get_left(e);
            set_right(e, ep);
            set_left(e, epl);
            set_left(get_right(e), el);
            set_right(get_right(e), er);
            set_parent(get_right(e), e);
            set_parent(get_left(e), e);
            set_parent(get_left(get_right(e)), get_right(e));
            set_parent(get_right(get_right(e)), get_right(e));
        }

        if (epp == NULL) {
            set_parent(e, NULL);
        } else {
            if (is_left) {
                set_left(epp, e);
            } else {
                set_right(epp, e);
            }
            set_parent(e, epp);
        }
        up(f, e);
    }
}

void down(Event* e) {
    if (get_left(e) == NULL) {
        return;
    }
    if (get_right(e) == NULL) {
        if (get_time_stamp(e) >= get_time_stamp(get_left(e))) {
            Event* ell = get_left(get_left(e));
            Event* elr = get_right(get_left(e));
            Event* ep = get_parent(e);
            int is_left = 2;
            if (ep != NULL) {
                is_left = e == get_left(ep);
            }
            set_parent(e, el);
            set_right(get_parent(e), NULL);
            set_left(get_parent(e), e);
            set_left(e, ell);
            set_right(e, elr);
            set_parent(get_left(e), e);
            set_parent(get_right(e), e);
            set_parent(get_parent(e), ep);
            if (is_left != 2) {
                if (is_left) {
                    set_left(get_parent(get_parent(e))) = get_parent(e);
                } else {
                    set_right(get_parent(get_parent(e))) = get_parent(e);
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
    int bits = log2(f->cnt);
    Event* temp = f->root;
    for (int i = bits - 1; i > -1; i--) {
        if ((f->cnt >> i) % 2 == 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    f->last = temp;
    return 0;
}

Event* find_par(FutureEventList* f) {
    if (f == NULL) {
        return NULL;
    }
    int bits = log2(f->cnt);
    Event* temp = f->root;
    for (int i = bits - 1; i > 0; i--) {
        if ((f->cnt >> i) % 2 == 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
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

int get_cnt(FutureEventList* f) {
    return f->cnt;
}
