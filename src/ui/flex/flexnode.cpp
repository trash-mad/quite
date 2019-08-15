#include "flexnode.h"

namespace Quite {
namespace Ui {
namespace Flex {

/*****************************************************************************/

FlexNode::FlexNode(QQuickItem* item, bool fill)
  : QObject (nullptr) {
    qDebug() << "FlexNode ctor";
    node = YGNodeNew();
    this->item=item;
    this->fill=fill;
    parseJustifyContent(item->property("justifyContent").toString());
    parseFlexDirection(item->property("flexDirection").toString());
    parseAlignContent(item->property("alignContent").toString());
    parseAlignItems(item->property("alignItems").toString());
    parseAlignSelf(item->property("alignSelf").toString());
    parseFlexWrap(item->property("flexWrap").toString());
    parseDisplay(item->property("display").toString());
    parseOtherProps();
}

/*---------------------------------------------------------------------------*/

FlexNode::~FlexNode() {
    qDebug() << "FlexNode dtor";
    YGNodeFree(node);
}

/*---------------------------------------------------------------------------*/

void FlexNode::printTree() {
    static int space=0;
    QStringList line;
    for (int i=space;i!=0;i--) {
        line.append(" ");
    }
    line.append(nodeInfo());
    qDebug() << line.join("");
    space+=2;
    QLinkedList<FlexNode*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        (*iter)->printTree();
    }
    space-=2;
}

/*---------------------------------------------------------------------------*/

QString FlexNode::nodeInfo() {
    return (QStringList()
        << "justifyContent: " << item->property("justifyContent").toString()
        << "flexDirection: " << item->property("flexDirection").toString()
        << "alignContent: " << item->property("alignContent").toString()
        << "alignItems: " << item->property("alignItems").toString()
        << "alignSelf: " << item->property("alignSelf").toString()
        << "flexWrap: " << item->property("flexWrap").toString()
        << "display: " << item->property("display").toString()
        << "minHeight: " << item->property("minHeight").toString()
        << "minWidth: " << item->property("minWidth").toString()
        << "maxHeight: " << item->property("maxHeight").toString()
        << "maxWidth: " << item->property("maxWidth").toString()
        << "height: " << item->property("height").toString()
        << "width: " << item->property("width").toString()
        << "flexGrow: " << item->property("flexGrow").toString()
        << "flexShrink: " << item->property("flexShrink").toString()
    ).join(" ");
}

/*---------------------------------------------------------------------------*/

void FlexNode::buildTree() {
    std::vector<YGNodeRef> tmp(static_cast<unsigned long>(childCount));
    QLinkedList<FlexNode*>::iterator iter;
    int index=0;
    for (iter=child.begin();iter!=child.end();iter++,index++) {
        FlexNode* item = *iter;
        tmp[static_cast<unsigned long>(index)]=item->getNode();
        item->buildTree();
    }
    YGNodeSetChildren(node,tmp);
}

/*---------------------------------------------------------------------------*/

void FlexNode::appendChild(FlexNode *child) {
    qDebug() << "FlexNode appendChild";
    childCount++;
    this->child.append(child);
    child->setParent(this);
}

/*---------------------------------------------------------------------------*/

YGNodeRef FlexNode::getNode() const {
    return node;
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseFlexDirection(QString direction) {
    if (direction=="row") {
        setFlexDirectionRow();
    } else if (direction=="column") {
        setFlexDirectionColumn();
    } else if (direction=="rowReverse") {
        setFlexDirectionRowReverse();
    } else if (direction=="columnReverse") {
        setFlexDirectionColumnReverse();
    } else {
        qCritical() << "setFlexDirection invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseJustifyContent(QString justify) {
    if (justify=="center") {
        setJustifyCenter();
    } else if (justify=="flexEnd") {
        setJustifyFlexEnd();
    } else if (justify=="flexStart") {
        setJustifyFlexStart();
    } else if (justify=="spaceAround") {
        setJustifySpaceAround();
    } else if (justify=="spaceEvenly") {
        setJustifySpaceEvenly();
    } else if (justify=="spaceBetween") {
        setJustifySpaceBetween();
    } else {
        qCritical() << "setJustifyContent invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseAlignContent(QString align) {
    if (align == "auto") {
        setAlignContentAuto();
    } else if (align == "flexStart") {
        setAlignContentFlexStart();
    } else if (align == "center") {
        setAlignContentCenter();
    } else if (align == "flexEnd") {
        setAlignContentFlexEnd();
    } else if (align == "stretch") {
        setAlignContentStretch();
    } else if (align == "baseline") {
        setAlignContentBaseline();
    } else if (align == "spaceBetween") {
        setAlignContentSpaceBetween();
    } else if (align == "spaceAround") {
        setAlignContentSpaceAround();
    } else {
        qCritical() << "setAlignContent invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseAlignItems(QString align) {
    if (align == "auto") {
        setAlignItemsAuto();
    } else if (align == "flexStart") {
        setAlignItemsFlexStart();
    } else if (align == "center") {
        setAlignItemsCenter();
    } else if (align == "flexEnd") {
        setAlignItemsFlexEnd();
    } else if (align == "stretch") {
        setAlignItemsStretch();
    } else if (align == "baseline") {
        setAlignItemsBaseline();
    } else if (align == "spaceBetween") {
        setAlignItemsSpaceBetween();
    } else if (align == "spaceAround") {
        setAlignItemsSpaceAround();
    } else {
        qCritical() << "setAlignItems invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseAlignSelf(QString align) {
    if (align == "auto") {
        setAlignSelfAuto();
    } else if (align == "flexStart") {
        setAlignSelfFlexStart();
    } else if (align == "center") {
        setAlignSelfCenter();
    } else if (align == "flexEnd") {
        setAlignSelfFlexEnd();
    } else if (align == "stretch") {
        setAlignSelfStretch();
    } else if (align == "baseline") {
        setAlignSelfBaseline();
    } else if (align == "spaceBetween") {
        setAlignSelfSpaceBetween();
    } else if (align == "spaceAround") {
        setAlignSelfSpaceAround();
    } else {
        qCritical() << "setAlignSelf invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseDisplay(QString display) {
    if (display=="flex") {
        setDisplayFlex();
    } else if (display=="none") {
        setDisplayNone();
    } else {
        qCritical() << "setDisplay invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseFlexWrap(QString wrap) {
    if (wrap=="wrap") {
        setWrap();
    } else if (wrap=="noWrap") {
        setNoWrap();
    } else if (wrap=="wrapReverser") {
        setWrapReverser();
    } else {
        qCritical() << "setFlexWrap invalid param";
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::parseOtherProps() {
    if (fill) {
        setHeightPercent(100);
        setWidthPercent(100);
    } else {
        setMinWidth(item->property("minWidth").toInt());
        //setMinWidthPercent(item->property("minWidthPercent").toInt());
        setMaxWidth(item->property("maxWidth").toInt());
        //setMaxWidthPercent(item->property("maxWidthPercent").toInt());
        setMinHeight(item->property("minHeight").toInt());
        //setMinHeightPercent(item->property("minHeightPercent").toInt());
        setMaxHeight(item->property("maxHeight").toInt());
        //setMaxHeightPercent(item->property("maxHeightPercent").toInt());
        setHeight(item->property("height").toInt());
        //setHeightPercent(item->property("heightPercent").toInt());
        setWidth(item->property("width").toInt());
        //setWidthPercent(item->property("widthPercent").toInt());
    }
    setFlexShrink(item->property("flexShrink").toInt());
    setFlexGrow(item->property("flexGrow").toInt());
    setMarginTop(item->property("marginTop").toInt());
    setMarginLeft(item->property("marginLeft").toInt());
    setMarginRight(item->property("marginRight").toInt());
    setMarginBottom(item->property("marginBottom").toInt());
    setPaddingTop(item->property("paddingTop").toInt());
    setPaddingLeft(item->property("paddingLeft").toInt());
    setPaddingRight(item->property("paddingRight").toInt());
    setPaddingBottom(item->property("paddingBottom").toInt());
}

/*---------------------------------------------------------------------------*/

void FlexNode::commitNewPos() {
    int top = getLayoutTop();
    int bottom = getLayoutBottom();
    int left = getLayoutLeft();
    int right = getLayoutRight();
    int height = getLayoutHeight();
    int width = getLayoutWidth();
    qDebug() << "FlexNode commitNewPos"
        << " top: " << top
        << " left: " << left
        << " right: " << right
        << " bottom: " << bottom
        << " height: " << height
        << " width: " << width;
    item->setY(top);
    item->setX(left);
    item->setHeight(height);
    item->setWidth(width);
}

/*---------------------------------------------------------------------------*/

void FlexNode::commitChildNewPos() {
    commitNewPos();
    QLinkedList<FlexNode*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        (*iter)->commitChildNewPos();
    }
}

/*****************************************************************************/

void FlexNode::setFlexGrow(int v) {
    YGNodeStyleSetFlexGrow(node, static_cast<float>(v));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getFlexGrow() {
    return static_cast<int>(YGNodeStyleGetFlexGrow(node));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getFlexShrink() {
    return static_cast<int>(YGNodeStyleGetFlexShrink(node));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexShrink(int v){
    YGNodeStyleSetFlexShrink(node, static_cast<float>(v));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getHeight() {
    return static_cast<int>(YGNodeStyleGetHeight(node).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setHeight(int height) {
    YGNodeStyleSetHeight(node, static_cast<float>(height));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setHeightPercent(int percent) {
    YGNodeStyleSetHeightPercent(node,static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxHeight(int points) {
    YGNodeStyleSetMaxHeight(node, static_cast<float>(points));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxHeightPercent(int percent) {
    YGNodeStyleSetMaxHeightPercent(node, static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMaxHeight() {
    return static_cast<int>(YGNodeStyleGetMaxHeight(node).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinHeight(int point) {
    YGNodeStyleSetMinHeight(node, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinHeightPercent(int percent) {
    YGNodeStyleSetMinHeightPercent(node, static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getWidth() {
    return static_cast<int>(YGNodeStyleGetWidth(node).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWidth(int width) {
    YGNodeStyleSetWidth(node, static_cast<float>(width));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWidthPercent(int percent) {
    YGNodeStyleSetWidthPercent(node,static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMaxWidth() {
    return static_cast<int>(YGNodeStyleGetMaxWidth(node).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMinWidth() {
    return static_cast<int>(YGNodeStyleGetMinWidth(node).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMinHeight() {
    return static_cast<int>(YGNodeStyleGetMinHeight(node).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxWidth(int points) {
    YGNodeStyleSetMaxWidth(node, static_cast<float>(points));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxWidthPercent(int percent) {
    YGNodeStyleSetMaxWidthPercent(node, static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinWidth(int point) {
    YGNodeStyleSetMinWidth(node, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinWidthPercent(int percent) {
    YGNodeStyleSetMinHeightPercent(node, static_cast<float>(percent));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setDisplayNone() {
    YGNodeStyleSetDisplay(node, YGDisplayNone);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setDisplayFlex() {
    YGNodeStyleSetDisplay(node, YGDisplayFlex);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexDirectionRow() {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRow);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexDirectionRowReverse() {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionRowReverse);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexDirectionColumn() {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumn);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexDirectionColumnReverse() {
    YGNodeStyleSetFlexDirection(node, YGFlexDirectionColumnReverse);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifyFlexStart() {
    YGNodeStyleSetJustifyContent(node, YGJustifyFlexStart);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifyCenter() {
    YGNodeStyleSetJustifyContent(node, YGJustifyCenter);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifyFlexEnd(){
    YGNodeStyleSetJustifyContent(node, YGJustifyFlexEnd);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifySpaceBetween() {
    YGNodeStyleSetJustifyContent(node, YGJustifySpaceBetween);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentAuto() {
    YGNodeStyleSetAlignContent(node, YGAlignAuto);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentCenter() {
    YGNodeStyleSetAlignContent(node, YGAlignCenter);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentFlexEnd() {
    YGNodeStyleSetAlignContent(node, YGAlignFlexEnd);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentStretch() {
    YGNodeStyleSetAlignContent(node, YGAlignStretch);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentBaseline() {
    YGNodeStyleSetAlignContent(node, YGAlignBaseline);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentFlexStart() {
    YGNodeStyleSetAlignContent(node, YGAlignFlexStart);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentSpaceAround() {
    YGNodeStyleSetAlignContent(node, YGAlignSpaceAround);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignContentSpaceBetween() {
    YGNodeStyleSetAlignContent(node, YGAlignSpaceBetween);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsAuto() {
    YGNodeStyleSetAlignItems(node, YGAlignAuto);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsCenter() {
    YGNodeStyleSetAlignItems(node, YGAlignCenter);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsFlexEnd() {
    YGNodeStyleSetAlignItems(node, YGAlignFlexEnd);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsStretch() {
    YGNodeStyleSetAlignItems(node, YGAlignStretch);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsBaseline() {
    YGNodeStyleSetAlignItems(node, YGAlignBaseline);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsFlexStart() {
    YGNodeStyleSetAlignItems(node, YGAlignFlexStart);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsSpaceAround() {
    YGNodeStyleSetAlignItems(node, YGAlignSpaceAround);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignItemsSpaceBetween() {
    YGNodeStyleSetAlignItems(node, YGAlignSpaceBetween);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfAuto() {
    YGNodeStyleSetAlignSelf(node, YGAlignAuto);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfCenter() {
    YGNodeStyleSetAlignSelf(node, YGAlignCenter);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfFlexEnd() {
    YGNodeStyleSetAlignSelf(node, YGAlignFlexEnd);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfStretch() {
    YGNodeStyleSetAlignSelf(node, YGAlignStretch);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfBaseline() {
    YGNodeStyleSetAlignSelf(node, YGAlignBaseline);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfFlexStart() {
    YGNodeStyleSetAlignSelf(node, YGAlignFlexStart);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfSpaceAround(){
    YGNodeStyleSetAlignSelf(node, YGAlignSpaceAround);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setAlignSelfSpaceBetween() {
    YGNodeStyleSetAlignSelf(node, YGAlignSpaceBetween);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWrap() {
    YGNodeStyleSetFlexWrap(node, YGWrapWrap);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setNoWrap() {
    YGNodeStyleSetFlexWrap(node, YGWrapNoWrap);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWrapReverser() {
    YGNodeStyleSetFlexWrap(node, YGWrapWrapReverse);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginTop(int point) {
    YGNodeStyleSetMargin(node, YGEdgeTop, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginTop() {
    return static_cast<int>(YGNodeStyleGetMargin(node, YGEdgeTop).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginLeft(int point) {
    YGNodeStyleSetMargin(node, YGEdgeLeft, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginLeft() {
    return static_cast<int>(YGNodeStyleGetMargin(node, YGEdgeLeft).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginRight(int point) {
    YGNodeStyleSetMargin(node, YGEdgeRight, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginRight() {
    return static_cast<int>(YGNodeStyleGetMargin(node, YGEdgeRight).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginBottom(int point) {
    YGNodeStyleSetMargin(node, YGEdgeBottom, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getPaddingTop() {
    return static_cast<int>(YGNodeStyleGetPadding(node, YGEdgeTop).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginBottom() {
    return static_cast<int>(YGNodeStyleGetMargin(node, YGEdgeBottom).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setPaddingTop(int point) {
    YGNodeStyleSetPadding(
        node,
        YGEdgeTop,
        static_cast<float>(point)
    );
}

/*---------------------------------------------------------------------------*/

int FlexNode::getPaddingLeft() {
    return static_cast<int>(YGNodeStyleGetPadding(node, YGEdgeLeft).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setPaddingLeft(int point) {
    YGNodeStyleSetPadding(
        node,
        YGEdgeLeft,
        static_cast<float>(point)
    );
}

/*---------------------------------------------------------------------------*/

int FlexNode::getPaddingRight() {
    return static_cast<int>(YGNodeStyleGetPadding(node, YGEdgeRight).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setPaddingRight(int point) {
    YGNodeStyleSetPadding(
        node,
        YGEdgeRight,
        static_cast<float>(point)
    );
}

/*---------------------------------------------------------------------------*/

int FlexNode::getPaddingBottom() {
    return static_cast<int>(YGNodeStyleGetPadding(node, YGEdgeBottom).value);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setPaddingBottom(int point) {
    YGNodeStyleSetPadding(
        node,
        YGEdgeBottom,
        static_cast<float>(point)
    );
}


/*---------------------------------------------------------------------------*/

void FlexNode::calculateLayoutLtr() {
    YGNodeCalculateLayout(
        node,
        static_cast<float>(getWidth()),
        static_cast<float>(getHeight()),
        YGDirectionLTR
    );
    commitNewPos();
    QLinkedList<FlexNode*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        (*iter)->commitChildNewPos();
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::calculateLayoutRtl() {
    YGNodeCalculateLayout(
        node,
        static_cast<float>(getWidth()),
        static_cast<float>(getHeight()),
        YGDirectionRTL
    );
    commitNewPos();
    QLinkedList<FlexNode*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        (*iter)->calculateLayoutRtl();
    }
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutHeight() {
    return static_cast<int>(YGNodeLayoutGetHeight(node));
}

/*---------------------------------------------------------------------------*/

void FlexNode::initDefaultProps(QObject *object) {
    qDebug() << "FlexNode initDefaultProps";
    object->setProperty("height", 0);
    object->setProperty("heightPercent", 0);
    object->setProperty("width", 0);
    object->setProperty("widthPercent", 0);
    object->setProperty("minHeight", 0);
    object->setProperty("minHeightPercent", 0);
    object->setProperty("minWidth", 0);
    object->setProperty("minWidthPercent", 0);
    object->setProperty("maxHeight",INT_MAX);
    object->setProperty("maxWidth", INT_MAX);
    object->setProperty("maxHeightPercent",100);
    object->setProperty("maxWidthPercent",100);
    object->setProperty("flexShrink", 0);
    object->setProperty("flexGrow", 0);
    object->setProperty("marginTop", 0);
    object->setProperty("marginLeft", 0);
    object->setProperty("marginRight", 0);
    object->setProperty("marginBottom", 0);
    object->setProperty("paddingTop", 0);
    object->setProperty("paddingLeft", 0);
    object->setProperty("paddingRight", 0);
    object->setProperty("paddingBottom", 0);
    object->setProperty("alignSelf", "auto");
    object->setProperty("alignItems", "auto");
    object->setProperty("alignContent", "auto");
    object->setProperty("display", "flex");
    object->setProperty("flexWrap", "noWrap");
    object->setProperty("flexDirection", "row");
    object->setProperty("justifyContent", "spaceBetween");
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutWidth() {
    return static_cast<int>(YGNodeLayoutGetWidth(node));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutTop() {
    return static_cast<int>(YGNodeLayoutGetTop(node));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutLeft() {
    return static_cast<int>(YGNodeLayoutGetLeft(node));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutRight() {
    return static_cast<int>(YGNodeLayoutGetRight(node));
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLayoutBottom() {
    return static_cast<int>(YGNodeLayoutGetBottom(node));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifySpaceAround() {
    YGNodeStyleSetJustifyContent(node, YGJustifySpaceAround);
}

/*---------------------------------------------------------------------------*/

void FlexNode::setJustifySpaceEvenly() {
    YGNodeStyleSetJustifyContent(node, YGJustifySpaceEvenly);
}


/*****************************************************************************/

} // namespace Quite
} // namespace Ui
} // namespace Flex
