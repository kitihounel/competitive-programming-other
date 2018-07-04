#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

struct node {
    node *children[26];
    bool  isEnd;
    int   count;

    node(): isEnd(false), count(0) {
        fill(children, children + 26, nullptr);
    }
    ~node() {
        for (const auto &n: this->children) {
            if (n != nullptr) delete n;
        }
    }
};

int visit(node *root)
{
    int ans = 0;

    if (root->isEnd) ans += root->count;
    for (auto &n: root->children) {
        if (n != nullptr) ans += visit(n);
    }

    return ans;
}

int insert(node *root, const char *s)
{
    int i;

    while (*s != 0) {
        i = *s - 'a';
        if (root->children[i] == nullptr) root->children[i] = new node();
        root->count += 1;
        root = root->children[i];
        ++s;
    }
    root->isEnd  = true;
    root->count += 1;

    return root->count - 1;
}

int main()
{
    int  n;
    char word[33];

    while (scanf("%d\n", &n) > 0) {
        node *root = new node();
        while (n > 0) {
            scanf("%s\n", word);
            printf("%d\n", insert(root, word));
            --n;
        }
        delete root;
    }

    return 0;
}
