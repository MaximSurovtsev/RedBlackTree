#include <iostream>
#include<string>
#include <stdexcept>
#include "Counter.hpp"
using namespace std;

enum Color{ RED, BLACK, BLACK_BLACK };



template<typename T>
class Tree
{
private:
	struct Node:public Counter
	{
		Node* left_;
		Node* right_;
		Node* parent_;
		Color color_;
		T key_;
		Node(T const & key) : key_{ key }, left_{ nullptr }, right_{ nullptr }, parent_{ nullptr }, color_{ RED } {}
		size_t count() { return Count(); }
	} *root_;

	void deleteNode_(Node* node)
	{
		if (node)
		{
			deleteNode_(node->left_);
			deleteNode_(node->right_);
			delete node;
		}
		if (root_->count() == 0)
			root_ = nullptr;
	}

	ostream& print_(ostream&stream)
	{
		print_(root_, stream, 0);
		return stream;
	}

	ostream& print_(Node* node, ostream&stream, size_t level)const
	{
		Node* cur = node;
		if (cur != nullptr)
		{
			string a;
			if (cur->color_ == RED)
				a = "r";
			else a = "b";
			print_(cur->right_, stream, level + 1);
			for (unsigned int i = 0; i < level; ++i)
				stream << '-';
			stream << cur->key_ << " (" << a << ")" << endl;
			print_(cur->left_, stream, level + 1);
		}
		return stream;
	}

	void insert_(Node* node, const T& key)
	{
		Node* parent = nullptr;
		Node* cur = node;
		while (cur)
		{
			parent = cur;
			if (key == cur->key_)
				return;
			if (key < cur->key_)
				cur = cur->left_;
			else //if (key > node->key_)
				cur = cur->right_;
		}
		cur = new Node(key);
		cur->parent_ = parent;
		if (cur->parent_ == nullptr)
		{
			root_ = cur;
			root_->color_ = BLACK;
		}
		else
		{
			if (key < parent->key_)
				parent->left_ = cur;
			else parent->right_ = cur;
			insertBalance_(cur);
		}
	}

	void insertBalance_(Node* cur)
	{
		while (cur != root_ && cur->parent_->color_ == RED && cur->color_ == RED)
		{
			Node* uncle = nullptr;
			if (cur->parent_->parent_->left_ == cur->parent_)
				uncle = cur->parent_->parent_->right_;
			else uncle = cur->parent_->parent_->left_;

			if (uncle == nullptr || uncle->color_ == BLACK)
			{
				if (cur->parent_->parent_->left_ == cur->parent_ && cur->parent_->left_ == cur)
				{
					cur->parent_->color_ = BLACK;
					cur->parent_->parent_->color_ = RED;
					rotateRight_(cur->parent_->parent_);
				}
				else if (cur->parent_->parent_->right_ == cur->parent_ && cur->parent_->right_ == cur)
				{
					cur->parent_->color_ = BLACK;
					cur->parent_->parent_->color_ = RED;
					rotateLeft_(cur->parent_->parent_);
				}
				else if (cur->parent_->parent_->left_ == cur->parent_ && cur->parent_->right_ == cur)
				{
					cur->color_ = BLACK;
					cur->parent_->parent_->color_ = RED;
					rotateLeft_(cur->parent_);
					rotateRight_(cur->parent_);
				}
				else if (cur->parent_->parent_->right_ == cur->parent_ && cur->parent_->left_ == cur)
				{
					cur->color_ = BLACK;
					cur->parent_->parent_->color_ = RED;
					rotateRight_(cur->parent_);
					rotateLeft_(cur->parent_);
				}
			}
			else if (uncle->color_ == RED)
			{
				changeColor_(cur);
				cur = cur->parent_->parent_;
				root_->color_ = BLACK;
			}
		}
	}

	void changeColor_(Node* node)
	{
		node->parent_->parent_->left_->color_ = node->parent_->parent_->right_->color_ = BLACK;
		node->parent_->parent_->color_ = RED;
	}

	void rotateRight_(Node* node)
	{
		Node* a = node->left_;
		node->left_ = a->right_;
		if (a->right_)
			a->right_->parent_ = node;
		a->parent_ = node->parent_;
		if (node->parent_ == nullptr)
			root_ = a;
		else if (node == node->parent_->right_)
			node->parent_->right_ = a;
		else node->parent_->left_ = a;
		a->right_ = node;
		node->parent_ = a;
	}

	void rotateLeft_(Node* node)
	{
		Node* a = node->right_;
		node->right_ = a->left_;
		if (a->left_)
			a->left_->parent_ = node;
		a->parent_ = node->parent_;
		if (node->parent_ == nullptr)
			root_ = a;
		else if (node == node->parent_->left_)
			node->parent_->left_ = a;
		else node->parent_->right_ = a;
		a->left_ = node;
		node->parent_ = a;
	}

	Node* sibling_(Node* node)
	{
		if (node && node->parent_)
		{
			if (node->parent_->left_ == node)
				return node->parent_->right_;
			else return node->parent_->left_;
		}
		return nullptr;
	}

	void deleteBalance_(Node* node)
	{
		Node* cur = node;

		while (cur->color_ == BLACK_BLACK)
		{
			Node* brother = sibling_(cur);
			if ((brother->left_ && brother->left_->color_ == RED) || (brother->right_ && brother->right_->color_ == RED))
			{
				if (cur->parent_->left_ == cur)
				{
					if (!brother->right_ || brother->right_->color_ == BLACK)
					{
						brother->left_->color_ = BLACK;
						brother->color_ = RED;
						rotateRight_(brother);
					}
					else
					{
						brother->right_->color_ = BLACK;
						brother->color_ = cur->parent_->color_;
						cur->parent_->color_ = BLACK;
						cur->color_ = BLACK;
						rotateLeft_(cur->parent_);
					}
				}
				else
				{
					if (brother->right_ && brother->left_->color_ == BLACK)
					{
						brother->right_->color_ = BLACK;
						brother->color_ = RED;
						rotateLeft_(brother);
					}
					else
					{
						brother->left_->color_ = BLACK;
						brother->color_ = cur->parent_->color_;
						cur->parent_->color_ = BLACK;
						cur->color_ = BLACK;
						rotateRight_(cur->parent_);
					}
				}
			}
			else
			{
				if (cur->parent_->color_ == RED)
				{
					cur->parent_->color_ = BLACK;
					brother->color_ = RED;
					cur->color_ = BLACK;
				}
				else
				{
					if (brother->color_ == BLACK)
					{
						cur->parent_->color_ = BLACK_BLACK;
						brother->color_ = RED;
						cur->color_ = BLACK;
						cur = cur->parent_;
					}
					else if (brother->color_ == RED)
					{
						if (cur->parent_->left_ == cur)
						{
							brother->color_ = BLACK;
							cur->parent_->color_ = RED;
							rotateLeft_(cur->parent_);
						}
						else
						{
							brother->color_ = BLACK;
							cur->parent_->color_ = RED;
							rotateRight_(cur->parent_);
						}
					}
				}
			}
		}
	}
	
	void deleteElement_(Node* & node, const T& key)
	{
		if (node)
		{
			if (key < node->key_)
				deleteElement_(node->left_, key);
			else if (key > node->key_)
				deleteElement_(node->right_, key);
			else if (key == node->key_)
			{
				Node * parent = node->parent_;
				if (node == root_ && !node->left_ && !node->right_)
				{
					delete node;
					root_ = nullptr;
				}
				else if (node->left_ == nullptr && node->right_ == nullptr)
				{
					if (node->parent_->left_ == node)
					{
						delete node;
						parent->left_ = nullptr;
					}
					else //if (cur->parent_->right_ == cur)
					{
						delete node;
						parent->right_ = nullptr;
					}
				}
				else if (node->left_ != nullptr && node->right_ == nullptr)
				{
					Node * left = node->left_;
					if (node->color_ == RED)
					{
						if (parent->left_ == node)
						{
							delete node;
							parent->left_ = left;
						}
						else
						{
							delete node;
							parent->right_ = left;
						}
					}
					else
					{
						if (node->left_->color_ == RED)
						{
							if (parent->left_ == node)
							{
								delete node;
								parent->left_ = left;
								parent->left_->color_ = BLACK;
							}
							else
							{
								delete node;
								parent->right_ = left;
								parent->right_->color_ = BLACK;
							}
						}
						else
						{
							if (parent->left_ == node)
							{
								delete node;
								parent->left_ = left;
								parent->left_->color_ = BLACK_BLACK;
								deleteBalance_(parent->left_);
							}
							else
							{
								delete node;
								parent->right_ = left;
								parent->right_->color_ = BLACK_BLACK;
								deleteBalance_(parent->right_);
							}
						}
					}
					left->parent_ = parent;
				}
				else
				{
					Node* min = node->right_;
					while (min->left_)
						min = min->left_;
					T a = min->key_;
					deleteElement(min->key_);
					node->key_ = a;
				}
			}
		}
	}
public:
	Tree() : root_{ nullptr } {}
	~Tree() { deleteNode_(root_); }

	Node* search(const T& key)const
	{
		Node* cur = root_;
		while (cur != nullptr)
		{
			if (cur->key_ == key)
				break;
			else
			{
				if (key > cur->key_)
					cur = cur->right_;
				else cur = cur->left_;
			}
		}
		return cur;
	}

	Node* left(T key)
	{
		Node* node = search(key);
		return node->left_;
	}

	Node* right(T key)
	{
		Node* node = search(key);
		return node->right_;
	}

	Node* parent(T key)
	{
		Node* node = search(key);
		return node->parent_;
	}

	Color color(T key)
	{
		Node* node = search(key);
		return node->color_;
	}

	Node* root()
	{
		return root_;
	}

	size_t count()
	{
		return root_->count();
	}

	friend ostream& operator << (ostream&stream, Tree& tree)
	{
		return tree.print_(cout);
	}

	void insert(const T& key)
	{
		insert_(root_, key);
	}

	void deleteElement(const T& key)
	{
		deleteElement_(root_, key);
	}
};
