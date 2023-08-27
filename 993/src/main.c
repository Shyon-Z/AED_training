#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

//////////////////////////////////////////////////////////////////////////////

int cousin_check(struct TreeNode* root, int x, int y) {
    if (root == NULL)
        return 0;
    
    int level = 0;
    struct TreeNode* parentX = NULL;
    struct TreeNode* parentY = NULL;
    
///////////////////////////////////////

    void Level_Parent(struct TreeNode* current, int val, struct TreeNode* parent, int currentLevel) {
        if (current == NULL)
            return;
        
        if (current->val == val) {
            level = currentLevel;
            if (parent != NULL) {
                if (parent->left != NULL && parent->left->val == val) {
                    parentX = parent;
                } else if (parent->right != NULL && parent->right->val == val) {
                    parentY = parent;
                }
            }
            return;
        }
        
        Level_Parent(current->left, val, current, currentLevel + 1);
        Level_Parent(current->right, val, current, currentLevel + 1);
    }
    
    Level_Parent(root, x, NULL, 0);
    Level_Parent(root, y, NULL, 0);

    
    return (level > 1 && level == level && parentX != parentY);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

int main() {

    struct TreeNode* root = malloc(sizeof(struct TreeNode));
    struct TreeNode* l1 = malloc(sizeof(struct TreeNode));
    struct TreeNode* l2 = malloc(sizeof(struct TreeNode));
    struct TreeNode* l3 = malloc(sizeof(struct TreeNode));
    struct TreeNode* r1 = malloc(sizeof(struct TreeNode));
    struct TreeNode* r2 = malloc(sizeof(struct TreeNode));
    struct TreeNode* r3 = malloc(sizeof(struct TreeNode));

    root->val = 1;
    l1->val = 2;
    l2->val = 5;
    l3->val = 4;
    r1->val = 3;
    r2->val = 6;
    r3->val = 7;

    root->left = l1;
    root->right = r1;
    l1->left = l2;
    l1->right = l3;
    r1->left = r2;
    r1->right = r3;

    int x = 5, y = 4;

///////////////////////////////////////

    if (cousin_check(root, x, y)) {
        printf("Nodes %d _ %d are cousins.\n", x, y);
    } else {
        printf("Nodes %d _ %d are not cousins.\n", x, y);
    }

    free(root);
    free(l1);
    free(l2);
    free(l3);
    free(r1);
    free(r2);
    free(r3);

    return 0;
}
