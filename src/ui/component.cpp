#include "component.h"

namespace Quite {
namespace Ui {

/*****************************************************************************/

Component::Component(ComponentNode* node, QQmlEngine* engine, Element* parent)
  : Element(
        QUrl(QStringLiteral("qrc:/qml/Component.qml")),
        node,
        engine,
        parent
    ) {
    qDebug() << "Component ctor";
    connect(
        node,
        SIGNAL(subtreeChanged(
            QVector<NodeStruct>,
            QVector<NodeStruct>,
            Node*
        )),
        this,
        SLOT(subtreeChangedHandler(
            QVector<NodeStruct>,
            QVector<NodeStruct>,
            Node*
        ))
    );
}

/*---------------------------------------------------------------------------*/

Component::~Component() {
    qDebug() << "Component dtor";
}

/*---------------------------------------------------------------------------*/

bool Component::checkTree(QVector<NodeStruct> &tree) {
    for (int i=1;i!=tree.length();i++) {
        if (tree[i]==tree[i-1]) {
            return false;
        } else {
            continue;
        }
    }
    return true;
}

/*---------------------------------------------------------------------------*/

bool Component::tryInsertAfterChild(
    std::vector<NodeStruct> &merged,
    NodeStruct child,
    int lastIndex
) {
    qDebug() << "Component tryInsertAfterChild";
    auto afterIndex = static_cast<unsigned long long>(lastIndex)-1;
    if (merged[afterIndex].parent==child.parent) {
        QMetaObject::invokeMethod(
            merged[afterIndex].parent->node,
            "insertAfterChild",
            Q_ARG(Node*, merged[afterIndex].node),
            Q_ARG(Node*, child.node)
        );
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------------*/

bool Component::tryAppendChild(
    std::vector<NodeStruct> &merged,
    NodeStruct child,
    int lastIndex
) {
    qDebug() << "Component tryAppendChild";
    for (int i=lastIndex;i>=0;i--) {
        auto index=static_cast<unsigned long long>(i);
        if (*child.parent==merged[index]) {
            QMetaObject::invokeMethod(
                merged[index].node,
                "appendChild",
                Q_ARG(Node*, child.node)
            );
            return true;
        } else {
            continue;
        }
    }
    return false;
}

/*---------------------------------------------------------------------------*/

void Component::subtreeChangedHandler(
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
        for (iter=changes.begin();iter!=changes.end();iter++) {
            dtl::edit_t type = iter->second.type;
            if (type==dtl::SES_ADD) {
                int index = static_cast<int>(iter->second.afterIdx)-1;
                if (tryInsertAfterChild(merged,iter->first,index)) {
                    continue;
                } else if (tryAppendChild(merged,iter->first,index)) {
                    continue;
                } else {
                    QMetaObject::invokeMethod(
                        this->getNode(),
                        "appendChild",
                        Q_ARG(Node*, iter->first.node)
                    );
                }
            } else if (type==dtl::SES_COMMON) {
                int afterIndex=static_cast<int>(iter->second.afterIdx)-1;
                int beforeIndex=static_cast<int>(iter->second.beforeIdx)-1;
                NodeStruct item = tree.at(beforeIndex);
                NodeStruct newItem = newTree.at(afterIndex);
                QMetaObject::invokeMethod(
                    item.node,
                    "mergeProps",
                    Qt::QueuedConnection,
                    Q_ARG(Node*,newItem.node)
                );
            } else if (type==dtl::SES_DELETE) {
                QMetaObject::invokeMethod(
                    iter->first.node,
                    "deleteLater",
                    Qt::QueuedConnection
                );
            } else {
                qCritical() << "Invalid change type";
            }
        }
        qDebug() << "Component diff render applied";
    } else {
        if (!diffImposible) {
            diffImposible=true;
            qInfo()
                << "Diff rendering is impossible."
                << "The sequence contains a list of items without a key prop"
                /*TODO: << "or root node changed"*/;
        }
        QMetaObject::invokeMethod(
            this->getChild().first(),
            "deleteLater",
            Qt::QueuedConnection
        );
        emit renderSubtree(newRoot);
    }
}

/*****************************************************************************/

} // namespace Ui
} // namespa Quite
