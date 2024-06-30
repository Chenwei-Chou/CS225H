/**
 * @file narytree.cpp
 * Definitions of the n-ary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "narytree.h"

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
 * Prints a text representation of the edge connections of the NaryTree
 */

void NaryTree::print() 
{
    if (root == NULL){
        std::cout << "x" << std::endl;
    } else{ 
        std::cout << "o" << std::endl;
        std::vector<bool> dflag(this->height(),false);
        printHelper(root, 0, dflag);
        std::cout << std::endl;
    }

}

/**
 *  Helper function for printing a tree while preserving formatting
 */

void NaryTree::printHelper(Node*& node, int depth, std::vector<bool> dflag) {
    
    std::map<char,Node*>::iterator it;
    std::vector<char> keyList;
    for (it = node->children.begin(); it != node->children.end(); it++){
        keyList.push_back(it->first);
    }

    std::sort(keyList.begin(),keyList.end()); 

    for(size_t i = 0; i < keyList.size(); ++i){
        std::string spacing = "";

        for(int j = 0; j < depth; ++j){
            if(dflag[j]){
                spacing+= "|     ";
            } else{
                spacing+= "      ";
            }
        }

        std::cout << spacing;


        std::cout << "+--" << keyList[i] << "--o" << std::endl;

        if (i < keyList.size() - 1){
            dflag[depth] = true;
        } else{
            dflag[depth] = false;
        }

        printHelper(node->children[keyList[i]], depth+1, dflag);

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
            if(node->children.count(s[0]) > 0){ //If this character is already an edge
                insert(node->children[s[0]],s.substr(1), i); // move down the branch and try again (minus 1 char)
            }else{
                node->children[s[0]] = new Node(s.substr(1), i); // If we haven't seen this edge, fill in the rest of the branch
            }
        } else{ // If end of the path, store our value at this node
            node->index.push_back(i);
        }
    }
}


void NaryTree::clear(NaryTree::Node* subRoot)
{
    if (subRoot == NULL)
        return;

    std::map<char,Node*>::iterator it;
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
    std::map<char,Node*>::const_iterator it;
    int max = -1;
    for (it = (subRoot->children).begin(); it != (subRoot->children).end(); it++){
        int temp = height(it->second);
        if (temp > max){
            max = temp;
        }
    }
    return 1 + max;
}

void NaryTree::inLexOrder(std::vector<char>& treeVector){
    inLexOrder(root, treeVector);
}

void NaryTree::inLexOrder(Node* subRoot, std::vector<char>& treeVector){
    if(subRoot == NULL){
        return;
    }

    std::map<char,Node*>::iterator it;
    for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
        treeVector.push_back(it->first);
        inLexOrder(it->second, treeVector);
    }

}

/*
 YOUR CODE BEGINS HERE.
*/


/**
 * NaryTree Pattern Matching function
 * Given input pattern, search the already stored text (the tree)
 * @param s, the input string being searched
 * @return an std::vector<int> containing all matches (or -1 if no match)
 */
std::vector<int> NaryTree::patternMatch(const std::string & s){
    std::vector<int> outList;

    //YOUR CODE HERE
    patternMatch(s, root, outList);

    return outList;
}


/**
 * NaryTree Pattern Matching helper function
 * Given input pattern, search the already stored text (the tree)
 * @param s, the input string being searched
 * @param subRoot, a Node* pointing to the current node
 * @param outList, an std::vector<int> containing all matches found so far
 */
void NaryTree::patternMatch(const std::string & s, Node* subRoot, std::vector<int>& outList){
    //YOUR CODE HERE
    if (subRoot) {
        if (s.empty()) {
            vector<int> tmp = subRoot->index;
            const int t_size = tmp.size();
            for (int i = 0; i < t_size; i ++ ) outList.push_back(tmp[i]);
        } else {
            if (subRoot->children.find(s[0]) != subRoot->children.end()) {
                subRoot = subRoot->children[s[0]];
                patternMatch(s.substr(1), subRoot, outList);
            }
        }
    }
    if (outList.empty()) outList.push_back(-1);
}

/**
 * Returns a NaryTree encoding the string std::string T as key-value pairs.
 * There is a key for each substring in T
 * The correspond value is the starting index position for the key in T
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An N-ary Tree storing a full n-dimensional trie
 */
NaryTree build_trie(std::string T){
  NaryTree myTree;

  //Your code here
  myTree.insert(T, 0);
  const int t_size = T.size();

  for (int i = 1; i <= t_size ; i ++)
    for (int j = 0; j <= t_size - i ; j ++ )
        myTree.insert(T.substr(j, i), j);
  return myTree;
}