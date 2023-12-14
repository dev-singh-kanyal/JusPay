#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

struct Node
{
  string label;
  vector<Node *> children;
  Node *parent;
  int ancestorLocked, descendantLocked, userID;
  bool isLocked;

  Node(string name, Node *parentNode)
  {
    label = name;
    parent = parentNode;
    ancestorLocked = descendantLocked = userID = 0;
    isLocked = false;
  }

  void addChildren(vector<string> childLabels, Node *parentNode)
  {
    for (auto &childLabel : childLabels)
    {
      children.push_back(new Node(childLabel, parentNode));
    }
  }
};

// Print the Tree
// void printTree(Node *root)
// {
//     cout << "Parent: " << root->label << "\n";
//     cout << "Children: \n";
//     for (auto child : root->children)
//     {
//         cout << child->label << " ancestorLocked: " << child->ancestorLocked
//              << " descendantLocked: " << child->descendantLocked << " isLocked: "
//              << child->isLocked << " userID: " << child->userID << "\n";
//     }
//     cout << "\n";
//     for (auto child : root->children)
//     {
//         printTree(child);
//     }
// }

Node *buildTree(Node *root, int &numChildren, vector<string> &nodeLabels);

class LockingTree
{
private:
  Node *root;
  unordered_map<string, Node *> labelToNode;
  vector<string> outputLog;

public:
  LockingTree(Node *treeRoot) { root = treeRoot; }
  Node *getRoot() { return root; }

  void fillLabelToNode(Node *currentNode)
  {
    if (!currentNode)
      return;
    labelToNode[currentNode->label] = currentNode;
    for (auto child : currentNode->children)
      fillLabelToNode(child);
  }

  void updateDescendant(Node *currentNode, int value)
  {
    for (auto child : currentNode->children)
    {
      child->ancestorLocked += value;
      updateDescendant(child, value);
    }
  }

  bool checkDescendantsLocked(Node *currentNode, int &id,
                              vector<Node *> &lockedNodes)
  {
    if (currentNode->isLocked)
    {
      if (currentNode->userID != id)
        return false;
      lockedNodes.push_back(currentNode);
    }

    if (currentNode->descendantLocked == 0)
      return true;

    bool result = true;

    for (auto child : currentNode->children)
    {
      result &= checkDescendantsLocked(child, id, lockedNodes);
      if (!result)
        return false;
    }

    return result;
  }

  bool lockNode(string label, int id)
  {
    Node *targetNode = labelToNode[label];

    if (targetNode->isLocked)
      return false;

    if (targetNode->ancestorLocked != 0 || targetNode->descendantLocked != 0)
      return false;

    Node *currentNode = targetNode->parent;

    while (currentNode)
    {
      currentNode->descendantLocked++;
      currentNode = currentNode->parent;
    }

    updateDescendant(targetNode, 1);
    targetNode->isLocked = true;
    targetNode->userID = id;

    return true;
  }

  bool unlockNode(string label, int id)
  {
    Node *targetNode = labelToNode[label];

    if (!targetNode->isLocked)
      return false;

    if (targetNode->isLocked && targetNode->userID != id)
      return false;

    Node *currentNode = targetNode->parent;

    while (currentNode)
    {
      currentNode->descendantLocked--;
      currentNode = currentNode->parent;
    }

    updateDescendant(targetNode, -1);
    targetNode->isLocked = false;

    return true;
  }

  bool upgradeNode(string label, int id)
  {
    Node *targetNode = labelToNode[label];

    if (targetNode->isLocked)
      return false;

    if (targetNode->ancestorLocked != 0 || targetNode->descendantLocked == 0)
      return false;

    vector<Node *> lockedDescendants;

    if (checkDescendantsLocked(targetNode, id, lockedDescendants))
    {
      for (auto lockedDescendant : lockedDescendants)
      {
        unlockNode(lockedDescendant->label, id);
      }
    }
    else
      return false;

    lockNode(label, id);

    return true;
  }

  void processQueries(vector<pair<int, pair<string, int>>> queries)
  {
    for (auto query : queries)
    {
      int opcode = query.first;
      string nodeLabel = query.second.first;
      int userId = query.second.second;

      switch (opcode)
      {
      case 1:
        lockNode(nodeLabel, userId) ? outputLog.push_back("true")
                                    : outputLog.push_back("false");
        break;
      case 2:
        unlockNode(nodeLabel, userId) ? outputLog.push_back("true")
                                      : outputLog.push_back("false");
        break;
      case 3:
        upgradeNode(nodeLabel, userId) ? outputLog.push_back("true")
                                       : outputLog.push_back("false");
        break;
      }
    }
  }

  void printOutputLog()
  {
    for (const string &result : outputLog)
    {
      cout << result << "\n";
    }
  }
};

int main()
{
  int numNodes, numChildren, numQueries;
  cin >> numNodes >> numChildren >> numQueries;

  vector<string> nodeLabels(numNodes);

  for (int i = 0; i < numNodes; i++)
    cin >> nodeLabels[i];

  Node *rootNode = new Node(nodeLabels[0], nullptr);
  rootNode = buildTree(rootNode, numChildren, nodeLabels);

  LockingTree lockingTree(rootNode);
  lockingTree.fillLabelToNode(lockingTree.getRoot());

  vector<pair<int, pair<string, int>>> queries(numQueries);

  for (int i = 0; i < numQueries; i++)
  {
    cin >> queries[i].first >> queries[i].second.first >>
        queries[i].second.second;
  }

  lockingTree.processQueries(queries);
  lockingTree.printOutputLog();
  return 0;
}

// build the tree
Node *buildTree(Node *root, int &numChildren, vector<string> &nodeLabels)
{
  queue<Node *> q;
  q.push(root);

  int startIndex = 1;

  while (!q.empty())
  {
    Node *currentNode = q.front();
    q.pop();

    if (startIndex >= nodeLabels.size())
      continue;

    vector<string> tempChildrenLabels;

    for (int i = startIndex; i < startIndex + numChildren; i++)
      tempChildrenLabels.push_back(nodeLabels[i]);

    currentNode->addChildren(tempChildrenLabels, currentNode);
    startIndex += numChildren;

    for (auto child : currentNode->children)
      q.push(child);
  }

  return root;
}

// INPUT
// n = total number of nodes
// m = number of child per node
// q = number of queries
// next 'n' lines = node name in string
// next 'q' lines = queries with (opcode, string, uid)
// opcode => 1 = Lock, 2 = Unlock, 3 = Upgrade

// 7
// 2
// 5
// World
// Asia
// Africa
// China
// India
// SouthAfrica
// Egypt
// 1 China 9
// 1 India 9
// 3 Asia 9
// 2 India 9
// 2 Asia 9

// Output
// true
// true
// true
// false
// true
