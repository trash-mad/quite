#ifndef NODESTRUCT_H
#define NODESTRUCT_H

#include <QtDebug>
#include <QObject>
#include <QLinkedList>

#include "src/ui/base/node.h"

#include <iostream>

using namespace Quite::Ui::Base;

namespace Quite {
namespace Objects {

/*****************************************************************************/

class NodeStruct {
  public:
    NodeStruct();
    NodeStruct* parent;
    Node* node;
    int childCount;
    bool newTree;
    int index;
    int type;
    int key;
  public:
    static bool equals(
        const NodeStruct* a,
        const NodeStruct* b,
        bool recursive = true
    );
    static void printInfo(const NodeStruct& that);
    static QString getInfo(const NodeStruct& that);
    friend inline bool operator==(const NodeStruct &a, const NodeStruct &b) {
        return NodeStruct::equals(std::addressof(a),std::addressof(b));
    }
    friend std::ostream& operator<<(std::ostream& os,const NodeStruct& a) {
        return os << NodeStruct::getInfo(a).toStdString();
    }
};



/*****************************************************************************/

} // namespace Objects
} // namespace Quite

#endif // NODESTRUCT_H
