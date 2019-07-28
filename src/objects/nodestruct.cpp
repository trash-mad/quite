#include "nodestruct.h"

namespace Quite {
namespace Objects {

/*****************************************************************************/

NodeStruct::NodeStruct() {
    parent = nullptr;
    node = nullptr;
    newTree = false;
    childCount = -1;
    index = -1;
    type = -1;
    key = -1;
}

/*---------------------------------------------------------------------------*/

void NodeStruct::printInfo(const NodeStruct& that) {
    qDebug() << getInfo(that);
}

/*---------------------------------------------------------------------------*/

QString NodeStruct::getInfo(const NodeStruct &that) {
    QStringList tmp;
    tmp << "NodeStruct"
    << "newTree:" << QVariant(that.newTree).toString()
    << "childCount" << QVariant(that.childCount).toString()
    << "type" << QVariant(that.type).toString()
    << "key" << QVariant(that.key).toString()
    << "index" << QVariant(that.index).toString();
    return tmp.join(' ');
}

/*---------------------------------------------------------------------------*/

bool NodeStruct::equals(
    const NodeStruct* a,
    const NodeStruct* b,
    bool recursive
) {
    if (a->key!=b->key) {
        return false;
    } else if (a->type!=b->type) {
        return false;
    } else if (recursive) {
        const NodeStruct* parent1 = a;
        const NodeStruct* parent2 = b;
        while(true) {
            parent1 = parent1->parent;
            parent2 = parent2->parent;
            if (parent1==nullptr&&parent2==nullptr) {
                return true;
            } else if (parent1==nullptr&&parent2!=nullptr) {
                return false;
            } else if (parent1!=nullptr&&parent2==nullptr) {
                return false;
            } else if (!equals(parent1, parent2, false)) {
                return false;
            } else {
                continue;
            }
        }
    } else {
        return true;
    }
}

/*****************************************************************************/

} // namespace Objects
} // namespace Quite
