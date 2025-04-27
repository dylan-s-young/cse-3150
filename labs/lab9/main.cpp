#include "Node.h"
#include <vector>

void demonstrateSharedPtrCycle() {
    cout << "\n=== DEMONSTRATING SHARED_PTR CYCLE ===" << endl;
    
    string names[] = {"one", "two", "three", "four", "five"};
    int numberOfNodes = sizeof(names)/sizeof(names[0]);
    
    {
        // Create scope to test destruction
        cout << "Creating circular linked list with shared_ptr..." << endl;
        
        shared_ptr<Node> root = make_shared<Node>(names[0]);
        shared_ptr<Node> node = root;
        
        for (int i=1; i < numberOfNodes; i++) {
            node->next_shared = make_shared<Node>(names[i]);
            node = node->next_shared;
        }
        
        // Create the cycle!
        node->next_shared = root;
        
        // Demonstrate the cycle by traversing the list
        cout << "Traversing the circular list with shared_ptr:" << endl;
        node = root;
        for (int i = 0; i < numberOfNodes * 2; i++) {
            cout << "Node: " << node->name << endl;
            node = node->next_shared;
        }
        
        cout << "End of shared_ptr scope - no destructors will be called due to cycle" << endl;
    }  // End of scope - should trigger destruction, but won't due to cycle
    
    cout << "After shared_ptr scope - notice no destructors were called!" << endl;
}

void demonstrateWeakPtrCycle() {
    cout << "\n=== DEMONSTRATING WEAK_PTR CYCLE ===" << endl;
    
    string names[] = {"one", "two", "three", "four", "five"};
    int numberOfNodes = sizeof(names)/sizeof(names[0]);
    
    {
        // Create scope to test destruction
        cout << "Creating circular linked list with weak_ptr..." << endl;
        
        // We need to keep all shared_ptr references in a container
        vector<shared_ptr<Node>> nodes;
        
        shared_ptr<Node> root = make_shared<Node>(names[0]);
        nodes.push_back(root);
        shared_ptr<Node> node = root;
        
        for (int i=1; i < numberOfNodes; i++) {
            shared_ptr<Node> newNode = make_shared<Node>(names[i]);
            nodes.push_back(newNode);
            node->next_weak = newNode;  // Store weak reference
            node = newNode;
        }
        
        // Create the cycle with weak_ptr!
        node->next_weak = root;
        
        // Demonstrate the cycle by traversing the list
        cout << "Traversing the circular list with weak_ptr:" << endl;
        node = root;
        for (int i = 0; i < numberOfNodes * 2; i++) {
            cout << "Node: " << node->name << endl;
            // We need to lock the weak_ptr to get a valid shared_ptr
            shared_ptr<Node> nextNode = node->next_weak.lock();
            if (nextNode) {
                node = nextNode;
            } else {
                cout << "Next node has been destroyed!" << endl;
                break;
            }
        }
        
        cout << "End of weak_ptr scope - destructors will be called when vector is destroyed" << endl;
    }  // End of scope - should trigger destruction
    
    cout << "After weak_ptr scope - all nodes were properly destroyed!" << endl;
}

int main() {
    demonstrateSharedPtrCycle();
    demonstrateWeakPtrCycle();
    
    return 0;
}
