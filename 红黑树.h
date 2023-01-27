#ifndef RBT
#define RBT
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;

enum RBTreeColor
{
	RED,
	BLACK
};

template<typename T>
struct TreeNode
{
	T key;
	RBTreeColor color;
	TreeNode<T>* left;
	TreeNode<T>* right;
	TreeNode<T>* parent;

	TreeNode(T x, RBTreeColor _color)
	{
		key = x;
		color = _color;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
};

template<typename T>
class RedBlackTree
{
private:
	TreeNode<T>* root;
public:
	RedBlackTree();
	RedBlackTree(T x);
	RedBlackTree(TreeNode<T>* root);
	RedBlackTree(RedBlackTree& _root);
	RedBlackTree(vector<T> v);
	~RedBlackTree();
	vector<T> PerOrderTraverse();
	vector<T> InOrderTraverse();
	vector<T> PostOrderTraverse();
	vector<T> LevelOrderTraverse();
	void clear();
	bool isEmpty();
	bool isBalanced();
	int Height();
	int Size();
	T Maximum();
	T Minimum();
	TreeNode<T>* search(T e);
	bool insert(T e);
	bool remove(T e);
	T operator[](int r);
	RBTreeColor getColor(T e);
};

template<typename T>
RedBlackTree<T>::RedBlackTree()
{
	root = nullptr;
}
template<typename T>
RedBlackTree<T>::RedBlackTree(T x)
{
	root = new TreeNode<T>(x, BLACK);
}
template<typename T>
TreeNode<T>* copyBiTree(TreeNode<T>*& root)
{
	if (root)
	{
		TreeNode<T>* another;
		another = new TreeNode<T>(root->key, root->color);
		if (root->left)
		{
			another->left = copyBiTree(root->left);
		}
		if (root->right)
		{
			another->right = copyBiTree(root->right);
		}
		return another;
	}
	else
	{
		return nullptr;
	}
}
template<typename T>
RedBlackTree<T>::RedBlackTree(TreeNode<T>* _root)
{
	root = nullptr;
	TreeNode<T>* copy = nullptr;
	vector<T> v;
	In(_root, v);
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		copy = new TreeNode<T>(v[i], BLACK);
		insertIn(root, copy);
	}
}
template<typename T>
RedBlackTree<T>::RedBlackTree(RedBlackTree<T>& _root)
{
	root = copyBiTree(_root.root);
}
template<typename T>
RedBlackTree<T>::RedBlackTree(vector<T> v)
{
	root = nullptr;
	TreeNode<T>* node = nullptr;
	for (unsigned int i = 0; i < v.size(); ++i)
	{
		node = new TreeNode<T> (v[i], BLACK);
		insertIn(root, node);
	}
}
template<typename T>
void destroyBiTree(TreeNode<T>*& root)
{
	if (root)
	{
		TreeNode<T>* left;
		TreeNode<T>* right;
		left = root->left;
		right = root->right;
		delete root;
		root = nullptr;
		if (left)
			destroyBiTree(left);
		else
			destroyBiTree(right);
	}
}
template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	destroyBiTree(root);
}
template<typename T>
void Per(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		v.push_back(root->key);
		Per(root->left, v);
		Per(root->right, v);
	}
}
template<typename T>
vector<T> RedBlackTree<T>::PerOrderTraverse()
{
	vector<T>v;
	Per(root, v);
	return v;
}
template<typename T>
void In(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		In(root->left, v);
		v.push_back(root->key);
		In(root->right, v);
	}
}
template<typename T>
vector<T> RedBlackTree<T>::InOrderTraverse()
{
	vector<T> v;
	In(root, v);
	return v;
}
template<typename T>
void Post(TreeNode<T>*& root, vector<T>& v)
{
	if (root)
	{
		Post(root->left, v);
		Post(root->right, v);
		v.push_back(root->key);
	}
}
template<typename T>
vector<T> RedBlackTree<T>::PostOrderTraverse()
{
	vector<T> v;
	Post(root, v);
	return v;
}
template<typename T>
vector<T> RedBlackTree<T>::LevelOrderTraverse()
{
	vector<T> v;
	if (!root)
		return v;
	queue<TreeNode<T>*>q;
	q.push(root);
	while (!q.empty())
	{
		TreeNode<T>* Node;
		Node = q.front();
		v.push_back(Node->key);
		q.pop();
		if (Node->left)
		{
			q.push(Node->left);
		}
		if (Node->right)
		{
			q.push(Node->right);
		}
	}
	return v;
}
template<typename T>
void RedBlackTree<T>::clear()
{
	destroyBiTree(root);
}
template<typename T>
bool RedBlackTree<T>::isEmpty()
{
	return !root;
}
template<typename T>
bool isBalancedBiTree(TreeNode<T>*& root)
{
	if (!root)
		return true;
	if (!root->left && !root->right)
		return true;
	else if (abs(getHeight(root->left) - getHeight(root->right)) > 1)
		return false;
	else
		return isBalancedBiTree(root->left) && isBalancedBiTree(root->right);
}
template<typename T>
bool RedBlackTree<T>::isBalanced()
{
	return isBalancedBiTree(root);
}
template<typename T>
int getHeight(TreeNode<T>*& root)
{
	if (root)
		return 1 + max(getHeight(root->left), getHeight(root->right));
	else
		return 0;

}
template<typename T>
int RedBlackTree<T>::Height()
{
	return getHeight(root);
}
template<typename T>
int getSize(TreeNode<T>*& root)
{
	if (root)
		return 1 + getSize(root->left) + getSize(root->right);
	else
		return 0;
}
template<typename T>
int RedBlackTree<T>::Size()
{
	return getSize(root);
}
template<typename T>
TreeNode<T>* getMax(TreeNode<T>*& root)
{
	if (!root)
		return nullptr;
	TreeNode<T>* temp;
	temp = root;
	while (temp->right)
		temp = temp->right;
	return right;
}
template<typename T>
T RedBlackTree<T>::Maximum()
{
	if (!root)
	{
		return 0;
	}
	TreeNode<T>* Max;
	Max = getMax(root);
	return Max->key;
}
template<typename T>
TreeNode<T>* getMin(TreeNode<T>*& root)
{
	if (!root)
		return nullptr;
	TreeNode<T>* temp;
	temp = root;
	while (temp->left)
		temp = temp->left;
	return temp;
}
template<typename T>
T RedBlackTree<T>::Minimum()
{
	if (!root)
		return 0;
	TreeNode<T>* Min;
	Min = getMin(root);
	return Min->key;
}
template<typename T>
TreeNode<T>* searchIn(TreeNode<T>*& root, T val)
{
	if (root == nullptr)
		return nullptr;
	if (root->key == val)
		return root;
	else
		if (root->key > val)
			return searchIn(root->left, val);
		else
			return searchIn(root->right, val);
}
template<typename T>
TreeNode<T>* RedBlackTree<T>::search(T e)
{
	return searchIn(root, e);
}
template<typename T>
void leftRotate(TreeNode<T>*& root, TreeNode<T>*& x)//x是要旋转的节点
{
	TreeNode<T>* y = x->right;
	x->right = y->left;
	if (y->left)
		y->left->parent = x;
	y->parent = x->parent;
	if (!x->parent)
		root = y;
	else
	{
		if (x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	y->left = x;
	x->parent = y;
}
template<typename T>
void rightRotate(TreeNode<T>*& root, TreeNode<T>*& y)
{
	TreeNode<T>* x = y->left;
	y->left = x->right;
	if (x->right)
		x->right->parent = y;
	x->parent = y->parent;
	if (!y->parent)
		root = x;
	else
	{
		if (y->parent->left == y)
		{
			y->parent->left = x;
		}
		else
		{
			y->parent->right = x;
		}
	}
	x->right = y;
	y->parent = x;
}
template<typename T>
void insertFixup(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* _parent = node->parent;
	TreeNode<T>* _gparent;
	while (_parent && _parent->color == RED)
	{
		_gparent = _parent->parent;
		if (_parent == _gparent->left)
		{
			TreeNode<T>* uncle = _gparent->right;
			if (uncle && uncle->color == RED)
			{
				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				continue;
			}
			if (node == uncle)
			{
				leftRotate(root, _parent);
				TreeNode<T>* tmp =_parent;
				_parent = node;
				node = tmp;
			}
			_parent->color = BLACK;
			_gparent->color = RED;
			rightRotate(root, _gparent);
		}
		else
		{
			TreeNode<T>* uncle = _gparent->left;
			if (uncle && uncle->color == RED)
			{
				_gparent->color = RED;
				uncle->color = BLACK;
				_parent->color = BLACK;
				node = _gparent;
				continue;
			}
			if (node==uncle)
			{
				rightRotate(root, _parent);
				TreeNode<T>* tmp = _parent;
				_parent = node;
				node = tmp;
			}
			_parent->color = BLACK;
			_gparent->color = RED;
			leftRotate(root, _gparent);
		}
	}
	root->color = BLACK;
}
template <typename T>
void insertFixUp(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* _parent = node->parent;
	TreeNode<T>* _gparent;

	// 若父节点存在,并且父节点的颜色是红色
	while (_parent && _parent->color == RED)
	{
		_gparent = _parent->parent;

		if (_parent == _gparent->left)
		{
			TreeNode<T>* uncle = _gparent->right;
			if (uncle && uncle->color == RED)
			{

				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				continue;
			}
			if (node == node->parent->right)
			{
	
				leftRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			_parent->color = BLACK;
			_gparent->color = RED;
			rightRotate(root, _gparent);
		}

		else
		{
			TreeNode<T>* uncle = _gparent->left;
			if (uncle && uncle->color == RED)
			{

				uncle->color = BLACK;
				_parent->color = BLACK;
				_gparent->color = RED;
				node = _gparent;
				continue;
			}
			if (uncle == node)
			{

				rightRotate(root, _parent);
				TreeNode<T>* tmp;
				tmp = _parent;
				_parent = node;
				node = tmp;
			}
			//叔叔是黑色,且当前节点是右孩子的情况
			_parent->color = BLACK;
			_gparent->color = RED;
			leftRotate(root, _gparent);
		}
	}
	//将根节点设为黑色
	root->color = BLACK;
}
template<typename T>
void insertIn(TreeNode<T>*& root, TreeNode<T>*& node)
{
	TreeNode<T>* y = nullptr;
	TreeNode<T>* x = root;
	while (x)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	node->parent = y;
	if (y)
	{
		if (node->key < y->key)
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}
	}
	else
	{
		root = node;
	}
	node->color = RED;
	insertFixup(root, node);
}
template<typename T>
bool RedBlackTree<T>::insert(T e)
{
	if (search(e))
		return false;
	TreeNode<T>* node;
	node = new TreeNode<T>(e, BLACK);

	insertIn(root, node);
	return true;
}
template <typename T>
void removeFixUp(TreeNode<T>*& root, TreeNode<T>*& node, TreeNode<T>*& parent)
{
	while ((!node || node->color == BLACK) && node != root)
	{
		if (parent->left == node)
		{
			TreeNode<T>* other = parent->right;
			if (other->color == RED)
			{
	
				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->right || other->right->color == BLACK)
				{
					other->left->color = BLACK;
					other->color = RED;
					rightRotate(root, other);
					other = parent->right;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			TreeNode<T>* other = parent->left;
			if (other->color == RED)
			{

				other->color = BLACK;
				parent->color = RED;
				leftRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK) && (!other->right || other->right->color == BLACK))
			{
	
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					other->right->color = BLACK;
					other->color = RED;
					leftRotate(root, other);
					other = parent->left;
				}
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}

	if (node)
		node->color = BLACK;
}

template<typename T>
void removeAt(TreeNode<T>*& root, TreeNode<T>*&  node)
{
	TreeNode<T>* child;
	TreeNode<T>* parent;
	RBTreeColor color;

	if (node->left && node->right)
	{
		TreeNode<T>* replace = node;
		replace = replace->right;
		while (replace->left)
			replace = replace->left;
		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		else
		{
			root = replace;
		}
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent == replace;
		else
		{
			if (child)
			{
				child->parent = parent;
			}
			parent->left = child;
			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == BLACK)
			removeFixUp(root, child, parent);
		delete node;
		node = nullptr;
		return;
	}
	if (node->left)
		child = node->left;
	else
		child = node->right;
	parent = node->parent;
	color = node->color;

	if (child)
		child->parent = parent;
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;
	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
	node = nullptr;
}
template <typename T>
bool RedBlackTree<T>::remove(T e)
{
	TreeNode<T>* node = searchIn(root, e);
	if (node)
	{
		removeAt(root, node);
		return true;
	}
	return false;
}
template<typename T>
T RedBlackTree<T>::operator[](int r)
{
	if (r < 0 || r >= Size)
		return NULL;
	vector<T> v = InOrderTraverse();
	return v[r];
}
template <typename T>
RBTreeColor RedBlackTree<T>::getColor(T e)
{
	TreeNode<T>* node = searchIn(root, e);
	if (node)
		return node->color;
	else
		return BLACK;
}
template <typename T>
ostream& operator<<(ostream& os, RedBlackTree<T>& m)
{
	vector<T> v = m.InOrderTraverse();
	if (v.size() == 0)
		return os;

	if (v.size() == 1)
	{
		os << "(" << v.front();
		if (m.getColor(v.front()) == RED)
			os << ",红)";
		else
			os << ",黑)";
		return os;
	}
	else
	{
		for (unsigned int i = 0; i < v.size() - 1; i++)
		{
			os << "(" << v[i];
			if (m.getColor(v[i]) == RED)
				os << ",红) ";
			else
				os << ",黑) ";
		}
		os << "(" << v.back();
		if (m.getColor(v.back()) == RED)
			os << ",红)";
		else
			os << ",黑)";
		return os;
	}
}
#endif
