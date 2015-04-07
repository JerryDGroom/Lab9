/*
*******************************************************************

Laboratory 9
Binary Search Tree Lab || Group Project                 BSTree.cpp

Jerry Groom & Dani Breon
4/12/2015

*******************************************************************
*/

#ifndef BSTREE_CPP
#define BSTREE_CPP

#include <new>
#include <iostream>
#include "BSTree.h"

using namespace std;

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>:: BSTreeNode :: BSTreeNode ( const DataType &nodeDataItem,
        BSTreeNode *leftPtr,
        BSTreeNode *rightPtr )

// Creates a binary search tree node containing data item elem, left
// child pointer leftPtr, and right child pointer rightPtr.

    : dataItem(nodeDataItem),
      left(leftPtr),
      right(rightPtr)

{}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>:: BSTree ()

// Creates an empty tree.

    : root(0)

{}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>:: BSTree ( const BSTree &source )

// Creates an empty tree.

    : root(0)

{
    copyTree(source);
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>& BSTree<DataType,KeyType>:: operator= ( const BSTree &sourceTree )

// Sets a tree to be equivalent to the tree "source".

{
    // Avoid accidentally trying to set object to itself.
    // Calling clear() on an object, then copying the deleted data doesn't work.
    // Although this may seems like overkill and an unlikely scenario, it can happen,
    if( this != &sourceTree )
    {
        clear();
        copyTree(sourceTree);
        return *this;
    }
    else
    {
        return *this;
    }
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: copyTree ( const BSTree<DataType,KeyType> &sourceTree )

// Sets a tree to be equivalent to the tree "source".

{
    copyTreeHelper( root, sourceTree.root );
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: copyTreeHelper ( BSTreeNode *&p, const BSTreeNode *sourcePtr )

// Recursive helper function that helps set a tree to be equivalent to another tree.

{
    if( p != 0 )
    {
        p = new BSTreeNode( sourcePtr->dataItem, 0, 0 );
        copyTreeHelper( p->left, sourcePtr->left );
        copyTreeHelper( p->right, sourcePtr->right );
    }
}

//--------------------------------------------------------------------
template < typename DataType, typename KeyType >
BSTree<DataType,KeyType>:: ~BSTree ()

// Frees the memory used by a tree.

{
    clear();
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: insert ( const DataType &newDataItem )

// Inserts newDataItem into a tree. If an data item with the same key
// as newDataItem already exists in the tree, then updates that
// data item's data with newDataItem's data.

{
    insertHelper(root, newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: insertHelper ( BSTreeNode *&p,
        const DataType &newDataItem   )

// Recursive helper function for insert. Inserts newDataItem in
// the subtree pointed to by p.

{
    if ( p == 0 ) // Insert
        p = new BSTreeNode(newDataItem,0,0);
    else if ( newDataItem.getKey() < p->dataItem.getKey() )
        insertHelper(p->left, newDataItem);                  // Search left
    else if ( newDataItem.getKey() > p->dataItem.getKey() )
        insertHelper(p->right, newDataItem);                 // Search right
    else
        p->dataItem = newDataItem;                           // Update
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>:: retrieve ( const KeyType& searchKey, DataType &searchDataItem ) const

// Searches a tree for the data item with key searchKey. If the data item
// is found, then copies the data item to searchDataItem and returns true.
// Otherwise, returns false with searchDataItem undefined.

{
    return retrieveHelper(root,searchKey,searchDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>:: retrieveHelper ( BSTreeNode *p,
        const KeyType& searchKey,
        DataType &searchDataItem     ) const

// Recursive helper function for retrieve. Searches the subtree
// pointed to by p.

{
    bool result;   // Result returned

    if ( p == 0 )
    {
        // Fell off the tree while searching. Item is not in tree.
        result = false;
    }
    else if ( searchKey < p->dataItem.getKey() )
    {
        // Key is smaller than currentNode node. Search to left.
        result = retrieveHelper(p->left,searchKey,searchDataItem);
    }
    else if ( searchKey > p->dataItem.getKey() )
    {
        // Key is larger than currentNode node. Search to right.
        result = retrieveHelper(p->right,searchKey,searchDataItem);
    }
    else
    {
        // Found the desired item
        searchDataItem = p->dataItem;
        result = true;
    }

    return result;
}

//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>:: remove ( const KeyType& deleteKey )

// Removes the data item with key deleteKey from a tree. If the
// data item is found, then deletes it from the tree and returns true.
// Otherwise, returns false.

{
    return removeHelper(root,deleteKey);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
bool BSTree<DataType,KeyType>:: removeHelper ( BSTreeNode *&p, const KeyType& deleteKey )

// Recursive helper function for remove.

{
    // YOUR CODE GOES HERE
BSTreeNode *deletePtr;  // Pointer node to delete

    int result; // this allows a bool and non-bool answer

    if ( p == NULL )
       result = false;
    else if ( deleteKey < p->dataItem.getKey() )    // search function to see if deleteKey is Less than current nodes data Item.
       result = removeHelper(p->left,deleteKey);    // if if it is, recursively send the left item child through the remove function.
    else if ( deleteKey > p->dataItem.getKey() )    // search function to see if deleteKey is Greater than current nodes data Item.
       result = removeHelper(p->right,deleteKey);   // if if it is, recursively send the right child item back through the remove function
    else
    {
       deletePtr = p;           // copy node to deletePtr
       if ( p->left == NULL )      // check if node has a left child
       {
           p = p->right;        // if it does, then node becomes the right child.
	   delete deletePtr;        // then its free to delete the current node.
       }
       else if ( p->right == NULL ) //check if node has a right child
       {
           p = p->left;          // if it does, then node becomes the left child
	   delete deletePtr;         // then its free to delete the current node.
       }
       else         // If none of these were true, go through the next set of steps
       {

	   BSTreeNode* tempHolder = p->left;   // Temporary holder for current nodes left value.
	   while( tempHolder->right ) {        // while node has a right child,
		tempHolder = tempHolder->right;    // copy to tempholders right child to tempholder.
	   }
	   p->dataItem = tempHolder->dataItem; // copy tempHolders data item to current nodes data item
	   removeHelper( p->left, tempHolder->dataItem.getKey()); // Recursive function, send back current nodes left, and tempHolders dataItem
                                                              // so it can run through the cod again, until it reaches base case.
       }
       result = true;       // result is set to true
    }

    return result; // this allows you to return a single response depending on which path the
                   // code ends at. It could be result = true, or result = false.
}


//--------------------------------------------------------------------

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: writeKeys () const

// Outputs the keys in a tree in ascending order.

{
    writeKeysHelper(root);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < typename DataType, typename KeyType >
void BSTree<DataType,KeyType>:: writeKeysHelper ( BSTreeNode *p ) const

// Recursive helper for writeKeys.
// Outputs the keys in the subtree pointed to by p.

{
    if ( p != 0 )
    {
       // YOUR CODE GOES HERE
        writeKeysHelper(p->left); //write keys to left
        cout << p->dataItem.getKey() << " ";
        writeKeysHelper(p->right);//write keys to right
    }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template < typename DataType, typename KeyType >
    void BSTree<DataType,KeyType>:: clear ()

// Removes all the nodes from a tree.

    {
        clearHelper(root);
        root = 0;
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template < typename DataType, typename KeyType >
    void BSTree<DataType,KeyType>:: clearHelper ( BSTreeNode *p )

// Recursive helper for clear. Clears the subtree pointed to by p.

    {
        if ( p != 0 )
        {
            // Use post-order traversal. Otherwise get into trouble by
            // referencing p->left and/or p->right after p had been deallocated.
            clearHelper(p->left);
            clearHelper(p->right);
            delete p;
        }
    }

//--------------------------------------------------------------------

    template < typename DataType, typename KeyType >
    bool BSTree<DataType,KeyType>:: isEmpty () const

// Returns true if a tree is empty. Otherwise returns false.

    {
        return root == 0;
    }

//--------------------------------------------------------------------

    template < typename DataType, typename KeyType >
    void BSTree<DataType,KeyType>:: showStructure () const

// Outputs the keys in a binary search tree. The tree is output
// rotated counterclockwise 90 degrees from its conventional
// orientation using a "reverse" inorder traversal. This operation is
// intended for testing and debugging purposes only.

    {
        if ( root == 0 )
            cout << "Empty tree" << endl;
        else
        {
            cout << endl;
            showHelper(root,1);
            cout << endl;
        }
    }

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    template < typename DataType, typename KeyType >
    void BSTree<DataType,KeyType>:: showHelper ( BSTreeNode *p,
            int level             ) const

// Recursive helper for showStructure.
// Outputs the subtree whose root node is pointed to by p.
// Parameter level is the level of this node within the tree.

    {
        int j;   // Loop counter

        if ( p != 0 )
        {
            showHelper(p->right,level+1);         // Output right subtree
            for ( j = 0 ; j < level ; j++ )    // Tab over to level
                cout << "\t";
            cout << " " << p->dataItem.getKey();   // Output key
            if ( ( p->left != 0 ) &&           // Output "connector"
                    ( p->right != 0 ) )
                cout << "<";
            else if ( p->right != 0 )
                cout << "/";
            else if ( p->left != 0 )
                cout << "\\";
            cout << endl;
            showHelper(p->left,level+1);          // Output left subtree
        }
    }

#endif
