#include "componentnode.h"

namespace Quite {
namespace Ui {
namespace Base {

/*****************************************************************************/

ComponentNode::ComponentNode(
    QJSEngine* eval,
    QJSValue instance,
    QJSValue render
) : Node(
        QJSValue("Component"),
        instance.property("props"),
        ComponentNode::initialRender(eval, instance, render)
) {
    qDebug() << "ComponentNode ctor";
    instance.setProperty(
        "setState",
        eval->newQObject(this).property("setState")
    );
    this->instance=instance;
    this->render=render;

    this->getChild().first()->updateContext(instance);
}

/*---------------------------------------------------------------------------*/

ComponentNode::~ComponentNode() {
    qDebug() << "ComponentNode dtor";
}

/*---------------------------------------------------------------------------*/

void ComponentNode::incrementResolveCounter(QString from) {
    qDebug() << "ComponentNode incrementResolveCounter exec";
    while (!DiffCounter::instance()->tryIncrementCounter(from)) {
        QCoreApplication::processEvents();
        QThread::msleep(50);
    }
    qDebug() << "ComponentNode incrementResolveCounter resolve";
}

/*---------------------------------------------------------------------------*/

void ComponentNode::resolveChanges() {
    qDebug() << "ComponentNode resolveChanges exec";
    while (!DiffCounter::instance()->changesResolved()) {
        QCoreApplication::processEvents();
        QThread::msleep(50);
    }
    qDebug() << "ComponentNode resolveChanges resolve";
}

/*---------------------------------------------------------------------------*/

void ComponentNode::setState(QJSValue state) {
    instance.setProperty("state", state);
    QJSValue root = render.callWithInstance(
        instance, {
            instance.property("props"),
            instance.property("state")
        }
    );
    Node* node = nullptr;
    if (tryCastNode(root, node)) {
        resolveChanges();
        QVector<NodeStruct> newTree(countTotalChild(node)+1);
        {
            int initialIndex=0;
            ComponentNode::buildNodeTree(node, initialIndex, newTree, true);
        }
        QVector<NodeStruct> tree(countTotalChild(getChild().first())+1);
        {
            int initialIndex=0;
            ComponentNode::buildNodeTree(getChild().first(), initialIndex, tree);
        }
        node->updateContext(instance);
        subtreeChanged(newTree, tree, node);
    } else {
        qCritical() << "ComponentNode setState render is not Node*";
    }
}

/*---------------------------------------------------------------------------*/

void ComponentNode::updateContext(
    QJSValue context,
    bool recursive
) {
    Q_UNUSED(recursive);
    Node::updateContext(context, false);
    Node::updateChildContext(instance);
}

/*---------------------------------------------------------------------------*/

QVector<NodeStruct> ComponentNode::buildNodeTree(
    Node* root,
    int& itemIndex,
    QVector<NodeStruct>& result,
    bool newTree,
    NodeStruct* parent
) {
    result[itemIndex].type=root->getType();
    result[itemIndex].key=root->getKey();
    result[itemIndex].newTree=newTree;
    result[itemIndex].parent=parent;
    result[itemIndex].node=root;

    parent=std::addressof(result[itemIndex]);

    QLinkedList<Node*> child=root->getChild();
    QLinkedList<Node*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        itemIndex++;
        buildNodeTree(
            (*iter),
            itemIndex,
            result,
            newTree,
            parent
        );
    }
    return result;
}

/*---------------------------------------------------------------------------*/

QJSValue ComponentNode::initialRender(
    QJSEngine* eval,
    QJSValue instance,
    QJSValue render
) {
    qDebug() << "ComponentNode initialRender";
    Node* node = nullptr;
    QJSValue result;
    if (!render.isCallable()) {
        qCritical() << "ComponentNode initialRender render is not callable";
    } else {
        QJSValue root = render.callWithInstance(
            instance, {
                instance.property("props"),
                instance.property("state")
            }
        );
        if (root.isError()) {
            qCritical() << "ComponentNode initialRender" << root.toString();
        } else if (!tryCastNode(root, node)) {
            qCritical()
                << "initialRender renderSubtree"
                << "render result is not Node*";
        } else {
            result = eval->newArray(1);
            result.setProperty(0, eval->newQObject(node));
        }
    }
    return result;
}

/*---------------------------------------------------------------------------*/

int ComponentNode::countTotalChild(Node *root) {
    QLinkedList<Node*> child=root->getChild();
    QLinkedList<Node*>::iterator iter;
    int total=child.count();
    for (iter=child.begin();iter!=child.end();iter++) {
        total+=countTotalChild(*iter);
    }
    return total;
}

/*---------------------------------------------------------------------------*/

bool ComponentNode::checkTree(QVector<NodeStruct>& tree) {
    if (tree.length()<3) {
        return true;
    } else {
        for (int i=2;i!=tree.length();i++) {
            if (tree[i]==tree[i-1]&&tree[i]==tree[i-2]) {
                return false;
            } else {
                continue;
            }
        }
        return true;
    }
}

/*---------------------------------------------------------------------------*/

bool ComponentNode::tryInsertAfterChild(
    std::vector<NodeStruct> &merged,
    NodeStruct child,
    int lastIndex
) {
    qDebug() << "ComponentNode tryInsertAfterChild";
    auto afterIndex = static_cast<unsigned long long>(lastIndex)-1;
    if (merged[afterIndex].parent==child.parent) {
        incrementResolveCounter(QString("tryInsert %1").arg(
            QVariant(child.node->getEnumType()).toString()
        ));
        merged[afterIndex].parent->node->insertAfterChild(
            merged[afterIndex].node,
            child.node
        );
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------------*/

bool ComponentNode::tryAppendChild(
    std::vector<NodeStruct> &merged,
    NodeStruct child,
    int lastIndex
) {
    qDebug() << "ComponentNode tryAppendChild";
    for (int i=lastIndex;i>=0;i--) {
        auto index=static_cast<unsigned long long>(i);
        if (*child.parent==merged[index]) {
            incrementResolveCounter(QString("tryAppend %1").arg(
                QVariant(merged[index].node->getEnumType()).toString()
            ));
            merged[index].node->appendChild(
                child.node
            );
            return true;
        } else {
            continue;
        }
    }
    return false;
}

/*---------------------------------------------------------------------------*/

void ComponentNode::subtreeChanged(
    QVector<NodeStruct> newTree,
    QVector<NodeStruct> tree,
    Node *newRoot
) {
    qDebug() << "Component subtreeChangedHandler";
    qDebug() << "tree";
    for(int i=0;i!=tree.length();i++) {
        NodeStruct::printInfo(tree.at(i));
    }
    qDebug() << "newTree";
    for(int i=0;i!=newTree.length();i++) {
        NodeStruct::printInfo(newTree.at(i));
    }
    if (checkTree(tree)&&checkTree(newTree)) {
        std::vector<NodeStruct> treeStd=tree.toStdVector();
        std::vector<NodeStruct> newTreeStd=newTree.toStdVector();
        qDebug() << "shortestEditScript";
        dtl::Diff<NodeStruct, std::vector<NodeStruct>> d(
            treeStd,
            newTreeStd
        );
        std::ostringstream stream;
        d.onHuge();
        d.compose();
        d.printSES(stream);
        std::stringstream ss(stream.str().c_str());
        std::string buf;
        while (getline(ss,buf,'\n')) {
            qDebug() << QString::fromStdString(buf);
        }
        dtl::Ses<NodeStruct> ses = d.getSes();
        std::vector<std::pair<NodeStruct,dtl::elemInfo>> changes = ses.getSequence();
        auto merged = d.patch(treeStd);
        std::vector<std::pair<NodeStruct,dtl::elemInfo>>::iterator iter;
        NodeStruct* current=nullptr;
        for (iter=changes.begin();iter!=changes.end();iter++) {
            dtl::edit_t type = iter->second.type;
            if (type==dtl::SES_ADD) {
                int index = static_cast<int>(iter->second.afterIdx)-1;
                /*
                 * Skip node child if was appended/inserted
                 */
                if (current!=nullptr&&*iter->first.parent==*current) {
                    continue;
                } else {
                    current=nullptr;
                    if (tryInsertAfterChild(merged,iter->first,index)) {
                        current=std::addressof(iter->first);
                        continue;
                    } else if (tryAppendChild(merged,iter->first,index)) {
                        current=std::addressof(iter->first);
                        continue;
                    } else {
                        incrementResolveCounter(QString("Append %1").arg(
                            QVariant(iter->first.node->getEnumType()).toString()
                        ));
                        this->appendChild(iter->first.node);
                    }
                }
            } else if (type==dtl::SES_COMMON) {
                int afterIndex=static_cast<int>(iter->second.afterIdx)-1;
                int beforeIndex=static_cast<int>(iter->second.beforeIdx)-1;
                NodeStruct item = tree.at(beforeIndex);
                NodeStruct newItem = newTree.at(afterIndex);
                incrementResolveCounter(QString("MergeProps %1").arg(
                    QVariant(item.node->getEnumType()).toString()
                ));
                item.node->mergeProps(newItem.node);
            } else if (type==dtl::SES_DELETE) {
                incrementResolveCounter(QString("Delete %1").arg(
                    QVariant(iter->first.node->getEnumType()).toString()
                ));
                iter->first.node->deleteNodeDiff();
            } else {
                qCritical() << "Invalid change type";
            }
        }
        qDebug() << "Component diff render applied";
    } else {
        incrementResolveCounter("Subtree update delete");
        this->getChild().first()->deleteNodeDiff();
        incrementResolveCounter("Subtree update renderSubtree");
        appendChild(newRoot, true);
        emit renderSubtree(newRoot);
    }
}

/*****************************************************************************/

} // namespace Base
} // namespace Ui
} // namespace Quite
