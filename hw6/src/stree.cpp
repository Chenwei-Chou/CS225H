/**
 * @file stree.cpp
 * Definitions of the n-ary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "stree.h"
using namespace std;

NaryTree::NaryTree()
    : root(NULL)
{ /* nothing */
}

NaryTree::~NaryTree()
{
    clear(root);
}

void NaryTree::clear()
{
    clear(root);
    root = NULL;
}

/**
 * @return The root of the Nary tree.
 */

typename NaryTree::Node* NaryTree::getRoot() const
{
    return root;
}


/**
 * @return Prints a text representation of the edge connections of the NaryTree
 */

void NaryTree::print() 
{
    if (root == NULL){
        std::cout << "x" << std::endl;
    } else{ 
        std::cout << "o" << std::endl;
        std::vector<bool> dflag(this->height(),false);
        printHelper(root, 0, "", dflag);
        std::cout << std::endl;
    }

}

void NaryTree::printHelper(Node*& node, int depth, std::string partial, std::vector<bool> dflag) {
    
    std::map<std::string,Node*>::iterator it;
    std::vector<std::string> keyList;
    for (it = node->children.begin(); it != node->children.end(); it++){
        keyList.push_back(it->first);
    }

    std::sort(keyList.begin(),keyList.end()); 

    for(size_t i = 0; i < keyList.size(); ++i){
        std::string spacing = "";

        for(int j = 0; j < depth; ++j){
            if(dflag[j]){
                spacing+= "|    ";
            } else{
                spacing+= "     ";
            }
        }

        for(size_t q = 0; q < partial.size(); ++q){
            spacing += " ";
        }

        std::cout << spacing;

        std::cout << "+--" << keyList[i] << "--o" << std::endl;

        if (i < keyList.size() - 1){
            dflag[depth] = true;
        } else{
            dflag[depth] = false;
        }

        printHelper(node->children[keyList[i]], depth+1, partial+keyList[i],  dflag);

    }
}


void NaryTree::insert(const std::string& s, int i)
{
    insert(root, s, i);
}


void NaryTree::insert(Node*& node, const std::string & s, int i)
{
    // If we're at a NULL pointer, we make a new Node
    if (node == NULL) {
        node = new Node(s, i);
    } else {
        if(s.length() > 0 ){
            std::string f = s.substr(0,1);
            if(node->children.count(f) > 0){ //If this character is already an edge
                insert(node->children[f],s.substr(1), i); // move down the branch and try again (minus 1 char)
            }else{
                node->children[f] = new Node(s.substr(1), i); // If we haven't seen this edge, fill in the rest of the branch
            }
        } else{ // If end of the path, store our value
            node->index = i;
        }
    }
}


void NaryTree::clear(NaryTree::Node* subRoot)
{
    if (subRoot == NULL)
        return;

    std::map<std::string,Node*>::iterator it;
    for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
        clear(it->second);
    }
    
    delete subRoot;
}

/**
 * @return The height of the Nary tree. Recall that the height of a 
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
int NaryTree::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
int NaryTree::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    std::map<std::string,Node*>::const_iterator it;
    int max = -1;
    for (it = (subRoot->children).begin(); it != (subRoot->children).end(); it++){
        int temp = height(it->second);
        if (temp > max){
            max = temp;
        }
    }
    return 1 + max;
}

void NaryTree::inLexOrder(std::vector<std::string>& treeVector){
    inLexOrder(root, treeVector);
}

void NaryTree::inLexOrder(Node* subRoot, std::vector<std::string>& treeVector){
    if(subRoot == NULL){
        return;
    }

    std::map<std::string,Node*>::iterator it;
    for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
        treeVector.push_back(it->first);
        inLexOrder(it->second, treeVector);
    }

}

/*
 YOUR CODE BEGINS HERE.
*/


/**
 * Returns a NaryTree encoding the suffix-trie for a std::string T.
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An N-ary Tree storing a full n-dimensional suffix trie
 */
NaryTree build_strie(std::string T){
    NaryTree myTree;

    //YOUR CODE HERE
    const int t_size = T.size();
    for (int i = 0; i <= t_size; i ++ ) myTree.insert(T.substr(i) + "$", i);
    return myTree;
}

/**
 * Returns all the leaf pointers for the current subtree
 *
 * @param subRoot A Node* object pointing to the current subtree's root
 *
 * @return Pointers to all leaves in the subtree stored in leafList
 */
void NaryTree::getLeaves(Node* subRoot, std::vector<Node*>& leafList){
    // YOUR CODE HERE
    if (subRoot->isLeaf()) leafList.push_back(subRoot);
    else {
        for (auto s: subRoot->children)
            getLeaves(subRoot->children[s.first], leafList);
    }
}


/**
 * Returns all the exact matches for the input string s
 *
 * @param s A std::string storing the pattern of interest
 *
 * @return An std::vector<int> storing all matching indices (or -1)
 */
std::vector<int> NaryTree::patternMatch(const std::string & s){
    std::vector<int> outList;

    //YOUR CODE HERE
    patternMatch(s, root, outList);

    return outList;
}


/**
* Private helper function for the patternMatch function.
* @param s The pattern being matched
* @param subRoot The current node in the recursion
* @param outList stores the output index values
*/
void NaryTree::patternMatch(const std::string & s, Node* subRoot, std::vector<int>& outList){
    //YOUR CODE HERE
    vector<Node*> m_leaves;

    if (subRoot) {
        if (s.empty()) {
            getLeaves(subRoot, m_leaves);
            for (const auto i: m_leaves) outList.push_back(i->index);
        } else {
            map<string, Node*>::iterator it;
            for (it = subRoot->children.begin() ; it != subRoot->children.end() ; it ++ ) {
                string tmp = it->first;
                if (s[0] == tmp[0]) patternMatch(s.substr(1), it->second, outList);
            }
        }
    }
    if (outList.empty()) outList.push_back(-1);
}

/**
 * Converts a NaryTree encoding the suffix-trie to a NaryTree encoding a suffix-tree
 * The same tree object is used for both encodings
 */
void NaryTree::trie_to_tree(){
    trie_to_tree(root);
}

/**
 * Support function for suffix trie to suffix tree conversion
 *
 * @param subRoot A Node* object pointing to the current subtree's root
 *
 * @return A direct edit to the current tree replacing trie edges with tree edges
 */
void NaryTree::trie_to_tree(Node* subRoot){
    if (!subRoot->isLeaf()) {
        vector<string> m_delete;
        map<string, Node*>::iterator it = subRoot->children.begin();

        while (it != subRoot->children.end()) {
            Node* m_child = it->second;
            if (m_child->children.size() == 1) {
                map<string, Node*>::iterator iter = m_child->children.begin();
                subRoot->children.insert({it->first + iter->first, iter->second});
                m_delete.push_back(it->first);
            }
            it ++ ;
        }
        for (auto i: m_delete) subRoot->children.erase(i);
        for (auto i: subRoot->children) trie_to_tree(i.second);
    }
}

