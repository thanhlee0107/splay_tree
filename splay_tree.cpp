#include<iostream>
#include<string>
#include<queue>
using namespace std;
class SplayTree {
    struct Node {
        int val;
        Node* pLeft;
        Node* pRight;
        Node* pParent;
        Node(int val = 0, Node* l = nullptr, Node* r = nullptr, Node* par = nullptr) : val(val), pLeft(l), pRight(r), pParent(par) { }
    };
    Node* root;

    // print the tree structure for local testing
    void printBinaryTree(string prefix, const Node* root, bool isLeft, bool hasRightSibling) {
        if (!root && isLeft && hasRightSibling) {
            cout << prefix << "├──\n";
        }
        if (!root) return;
        cout << prefix;
        if (isLeft && hasRightSibling) 
            cout << "├──";
        else 
            cout << "└──";
        cout << root->val << '\n';
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pLeft, true, root->pRight);
        printBinaryTree(prefix + (isLeft && hasRightSibling ? "|  " : "   "), root->pRight, false, root->pRight);
    }

    void printPreorder(Node* p) {
        if (!p) {
            return;
        }
        cout << p->val << ' ';
        printPreorder(p->pLeft);
        printPreorder(p->pRight);
    }
public:
    SplayTree() {
        root = nullptr;
    }
    ~SplayTree() {
        // Ignore deleting all nodes in the tree
    }

    void printBinaryTree() {
        printBinaryTree("", root, false, false);
    }

    void printPreorder() {
        printPreorder(root);
        cout << "\n";
    }
        Node*rotateRight(Node*x){
        Node *y = x->pLeft; 
        x->pLeft = y->pRight; 
        y->pRight = x; 
        return y; 
        
    }
void rightRotate(Node *P)
{
	Node *T=P->pLeft;// T is subleft of root  B is subright of T,
	Node *B=T->pRight;
	Node *D=P->pParent;//D is Node parent of P(root)
	if(D)//co Node cha-me
	{
		if(D->pRight==P) D->pRight=T;
		else D->pLeft=T;
	}
	if(B)
		B->pParent=P;
	T->pParent=D;
	T->pRight=P;
	
	P->pParent=T;
	P->pLeft=B;
}
void leftRotate(Node *P)
{
	Node *T=P->pRight;
	Node *B=T->pLeft;
	Node *D=P->pParent;
	if(D)
	{
		if(D->pRight==P) D->pRight=T;
		else D->pLeft=T;
	}
	if(B)
		B->pParent=P;
	T->pParent=D;
	T->pLeft=P;
	
	P->pParent=T;
	P->pRight=B;
}

void splay(Node *&T)
{
	while(true)
	{
		Node *p=T->pParent;
		if(!p) break;
		Node *pp=p->pParent;
		if(!pp)//Zig
		{
			if(p->pLeft==T)
				rightRotate(p);
			else
				leftRotate(p);
			break;
		}
		if(pp->pLeft==p)
		{
			if(p->pLeft==T)
			{//ZigZig
				rightRotate(pp);
				rightRotate(p);
			}
			else
			{//ZigZag
				leftRotate(p);
				rightRotate(pp);
			}
		}
		else
		{
			if(p->pLeft==T)
			{//ZigZag
				rightRotate(p);
				leftRotate(pp);
			}
			else
			{//ZigZig
				leftRotate(pp);
				leftRotate(p);
			}
		}
	}
	root=T;
}
    
    Node*add(Node*&sub,Node*&p){
        if(!sub){
            sub=p;
            //cout<<p->val<<endl;
            return sub;
        }
        p->pParent=sub;
        if(sub->val<=p->val){
            return add(sub->pRight,p);
        }
        return add(sub->pLeft,p);
    }
    void insert(int val) {
        // To Do
        Node*p=new Node(val);
        add(root,p);
        splay(p);
    }

bool find(int val,Node*root){
    if(!root){ 
        return false;}
        while(true){
            if(val>root->val){
                if(root->pRight)
                    root=root->pRight;
                else break;
            }
            
            else if(val<root->val){
                if(root->pLeft)
                    root=root->pLeft;
                else break;
            }
            else{
                break;
            }
        }
    splay(root);
    if(root->val==val) return true;
    return false;
}
bool search(int val){
    //TODO
    return find(val,this->root);
}
Node*findMax(Node*subroot){
    if(!subroot) return nullptr;
    if(!subroot->pRight) return subroot;
    return findMax(subroot->pRight);
}
Node* remove(int val){
    //TODO
    if(!root) return nullptr;
    if(search(val)){
        Node*tree1=root->pLeft;
        Node*tree2=root->pRight;
        delete root;
        if(!tree1){
            if(tree2){
            root=tree2;
            root->pParent=nullptr;
            return root;
            }
            return nullptr;
        }
        root=tree1;
        root->pParent=nullptr;
        root=findMax(root);
        splay(root);
        if(tree2){
            tree2->pParent=root;
            root->pRight=tree2;
        }
        return root;
    }
    return nullptr;
}
};
int main(){
SplayTree tree;
int query;
cin >> query;
for(int i = 0; i < query; i++) {
    string op;
    int val;
    cin >> op >> val;
    if (op == "insert")
        tree.insert(val);
    else if (op == "remove")
        cout << (tree.remove(val) != nullptr ? "removed" : "not found") << '\n';
    else if (op == "search")
        cout << (tree.search(val) ? "found" : "not found") << '\n';
    else if (op == "print")
        tree.printPreorder();
}
}