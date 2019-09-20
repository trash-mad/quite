#include "flexnode.h"

namespace Quite {
namespace Objects {

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

FlexNode::FlexNode(QQuickItem *item, int height, int width)
  : FlexNode(item) {
    qDebug() << "FlexNode root ctor";
    setHeight(height);
    setWidth(width);
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
    if (childCount>0) {
        std::vector<YGNodeRef> tmp(static_cast<unsigned long>(childCount));
        QLinkedList<FlexNode*>::iterator iter;
        int index=0;
        for (iter=child.begin();iter!=child.end();iter++,index++) {
            FlexNode* item = *iter;
            tmp[static_cast<unsigned long>(index)]=item->getNode();
            item->buildTree();
        }
        YGNodeSetChildren(node,tmp);
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::calculateLayoutLtr(int T, int L, int H, int W) {
    YGNodeStyleSetPosition(node,YGEdgeTop,static_cast<int>(T));
    YGNodeStyleSetPosition(node,YGEdgeLeft,static_cast<int>(L));
    calculateLayoutLtr(H,W);
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

    int height=item->property("preferredHeight").toInt();
    int width=item->property("preferredWidth").toInt();

    int minWidth=item->property("minWidth").toInt();
    int minWidthPercent=item->property("minWidthPercent").toInt();
    int maxWidth=item->property("maxWidth").toInt();
    int maxWidthPercent=item->property("maxWidthPercent").toInt();
    int minHeight=item->property("minHeight").toInt();
    int minHeightPercent=item->property("minHeightPercent").toInt();
    int maxHeight=item->property("maxHeight").toInt();
    int maxHeightPercent=item->property("maxHeightPercent").toInt();
    int heightPercent=item->property("heightPercent").toInt();
    int widthPercent=item->property("widthPercent").toInt();

    int margin=item->property("margin").toInt();
    int marginPercent=item->property("marginPercent").toInt();
    int padding=item->property("padding").toInt();
    int paddingPercent=item->property("paddingPercent").toInt();

    int marginTop=item->property("marginTop").toInt();
    int marginTopPercent=item->property("marginTopPercent").toInt();
    int marginLeft=item->property("marginLeft").toInt();
    int marginLeftPercent=item->property("marginLeftPercent").toInt();
    int marginRight=item->property("marginRight").toInt();
    int marginRightPercent=item->property("marginRightPercent").toInt();
    int marginBottom=item->property("marginBottom").toInt();
    int marginBottomPercent=item->property("marginBottomPercent").toInt();

    int paddingTop=item->property("paddingTop").toInt();
    int paddingTopPercent=item->property("paddingTopPercent").toInt();
    int paddingLeft=item->property("paddingLeft").toInt();
    int paddingLeftPercent=item->property("paddingLeftPercent").toInt();
    int paddingRight=item->property("paddingRight").toInt();
    int paddingRightPercent=item->property("paddingRightPercent").toInt();
    int paddingBottom=item->property("paddingBottom").toInt();
    int paddingBottomPercent=item->property("paddingBottomPercent").toInt();

    if (fill) {
        setHeightPercent(100);
        setWidthPercent(100);
    } else {
        setMinWidth(minWidth);
        setMinWidthPercent(minWidthPercent);
        setMaxWidth(maxWidth);
        setMaxWidthPercent(maxWidthPercent);
        setMinHeight(minHeight);
        setMinHeightPercent(minHeightPercent);
        setMaxHeight(maxHeight);
        setMaxHeightPercent(maxHeightPercent);
        setHeight(height);
        setHeightPercent(heightPercent);
        setWidth(width);
        setWidthPercent(widthPercent);
    }

    setFlexShrink(item->property("flexShrink").toInt());
    setFlexGrow(item->property("flexGrow").toInt());

    if (!(setPaddingTotal(padding)||setPaddingTotalPercent(paddingPercent))) {
        setPaddingTop(paddingTop);
        setPaddingTopPercent(paddingTopPercent);
        setPaddingLeft(paddingLeft);
        setPaddingLeftPercent(paddingLeftPercent);
        setPaddingRight(paddingRight);
        setPaddingRightPercent(paddingRightPercent);
        setPaddingBottom(paddingBottom);
        setPaddingBottomPercent(paddingBottomPercent);
    }

    if (!(setMarginTotal(margin)||setMarginTotalPercent(marginPercent))) {
        setMarginTop(marginTop);
        setMarginTopPercent(marginTopPercent);
        setMarginLeft(marginLeft);
        setMarginLeftPercent(marginLeftPercent);
        setMarginRight(marginRight);
        setMarginRightPercent(marginRightPercent);
        setMarginBottom(marginBottom);
        setMarginBottomPercent(marginBottomPercent);
    }

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

/*---------------------------------------------------------------------------*/

void FlexNode::setLastLeft(int left) {
    lastLeft=left;
}

/*---------------------------------------------------------------------------*/

void FlexNode::setLastTop(int top) {
    lastTop=top;
}

/*---------------------------------------------------------------------------*/

int FlexNode::getHeight() const{
    return static_cast<int>(YGNodeStyleGetHeight(node).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getWidth() const {
    return static_cast<int>(YGNodeStyleGetWidth(node).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginLeft() const {
    return static_cast<int>(YGNodeStyleGetMargin(node,YGEdgeLeft).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getMarginTop() const {
    return static_cast<int>(YGNodeStyleGetMargin(node,YGEdgeTop).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLastTop() const {
    return lastTop;
}

/*---------------------------------------------------------------------------*/

int FlexNode::getLastLeft() const {
    return lastLeft;
}

/*****************************************************************************/

void FlexNode::setFlexGrow(int v) {
    YGNodeStyleSetFlexGrow(node, static_cast<float>(v));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setFlexShrink(int v){
    YGNodeStyleSetFlexShrink(node, static_cast<float>(v));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setHeight(int height) {
    YGNodeStyleSetHeight(node, static_cast<float>(height));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setHeightPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetHeightPercent(node,static_cast<float>(percent));
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxHeight(int points) {
    YGNodeStyleSetMaxHeight(node, static_cast<float>(points));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxHeightPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMaxHeightPercent(node, static_cast<float>(percent));
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinHeight(int point) {
    YGNodeStyleSetMinHeight(node, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinHeightPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMinHeightPercent(node, static_cast<float>(percent));
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWidth(int width) {
    YGNodeStyleSetWidth(node, static_cast<float>(width));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setWidthPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetWidthPercent(node,static_cast<float>(percent));
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxWidth(int points) {
    YGNodeStyleSetMaxWidth(node, static_cast<float>(points));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMaxWidthPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMaxWidthPercent(node, static_cast<float>(percent));
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinWidth(int point) {
    YGNodeStyleSetMinWidth(node, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMinWidthPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMinHeightPercent(node, static_cast<float>(percent));
    } else {
        return;
    }
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

bool FlexNode::setMarginTotal(int point) {
    if (point!=-1) {
        YGNodeStyleSetMargin(
            node,
            YGEdgeAll,
            static_cast<float>(point)
        );
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------------*/

bool FlexNode::setMarginTotalPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMarginPercent(
            node,
            YGEdgeAll,
            static_cast<float>(percent)
        );
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginTop(int point) {
    YGNodeStyleSetMargin(node, YGEdgeTop, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginTopPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMarginPercent(
            node,
            YGEdgeTop,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginLeft(int point) {
    YGNodeStyleSetMargin(node, YGEdgeLeft, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginLeftPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMarginPercent(
            node,
            YGEdgeLeft,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginRight(int point) {
    YGNodeStyleSetMargin(node, YGEdgeRight, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginRightPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMarginPercent(
            node,
            YGEdgeRight,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginBottom(int point) {
    YGNodeStyleSetMargin(node, YGEdgeBottom, static_cast<float>(point));
}

/*---------------------------------------------------------------------------*/

void FlexNode::setMarginBottomPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetMarginPercent(
            node,
            YGEdgeBottom,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

bool FlexNode::setPaddingTotal(int point) {
    if (point!=-1) {
        YGNodeStyleSetPadding(
            node,
            YGEdgeAll,
            static_cast<float>(point)
        );
        return true;
    } else {
        return false;
    }
}

/*---------------------------------------------------------------------------*/

bool FlexNode::setPaddingTotalPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetPaddingPercent(
            node,
            YGEdgeAll,
            static_cast<float>(percent)
        );
        return true;
    } else {
        return false;
    }
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

void FlexNode::setPaddingTopPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetPaddingPercent(
            node,
            YGEdgeTop,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
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

void FlexNode::setPaddingLeftPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetPaddingPercent(
            node,
            YGEdgeLeft,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
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

void FlexNode::setPaddingRightPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetPaddingPercent(
            node,
            YGEdgeRight,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
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

void FlexNode::setPaddingBottomPercent(int percent) {
    if (percent!=-1) {
        YGNodeStyleSetPaddingPercent(
            node,
            YGEdgeBottom,
            static_cast<float>(percent)
        );
    } else {
        return;
    }
}

/*---------------------------------------------------------------------------*/

int FlexNode::getHeight() {
    return static_cast<int>(YGNodeStyleGetHeight(node).value);
}

/*---------------------------------------------------------------------------*/

int FlexNode::getWidth() {
    return static_cast<int>(YGNodeStyleGetWidth(node).value);
}

/*---------------------------------------------------------------------------*/

/*
 * Параметры T, L, H, W обозначают базис компонента, от которого производится
 * рассчет (отступ сверху, слева, ширина, высота). Используется для запоминания
 * при инкрементальном пересчете поддрева, когда мы считаем компоновку только
 * изменившегося компонента.
 */
void FlexNode::calculateLayoutLtr(int H,int W) {
    YGNodeCalculateLayout(
        node,
        static_cast<float>(W),
        static_cast<float>(H),
        YGDirectionLTR
    );
    /*
     * Родительский элемент не сдвигается по базису
     */
    commitNewPos();
    QLinkedList<FlexNode*>::iterator iter;
    for (iter=child.begin();iter!=child.end();iter++) {
        (*iter)->commitChildNewPos();
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
    object->setProperty("heightPercent", -1);
    object->setProperty("width", 0);
    object->setProperty("widthPercent", -1);
    object->setProperty("minHeight", 0);
    object->setProperty("minHeightPercent", -1);
    object->setProperty("minWidth", 0);
    object->setProperty("minWidthPercent", -1);
    object->setProperty("maxHeight",INT_MAX);
    object->setProperty("maxHeightPercent",-1);
    object->setProperty("maxWidth", INT_MAX);
    object->setProperty("maxWidthPercent",-1);
    object->setProperty("flexShrink", 0);
    object->setProperty("flexGrow", 0);
    object->setProperty("margin", -1);
    object->setProperty("marginPercent", -1);
    object->setProperty("marginTop", 0);
    object->setProperty("marginTopPercent", -1);
    object->setProperty("marginLeft", 0);
    object->setProperty("marginLeftPercent", -1);
    object->setProperty("marginRight", 0);
    object->setProperty("marginRightPercent", -1);
    object->setProperty("marginBottom", 0);
    object->setProperty("marginBottomPercent", -1);
    object->setProperty("padding", -1);
    object->setProperty("paddingPercent", -1);
    object->setProperty("paddingTop", 0);
    object->setProperty("paddingTopPercent", -1);
    object->setProperty("paddingLeft", 0);
    object->setProperty("paddingLeftPercent", -1);
    object->setProperty("paddingRight", 0);
    object->setProperty("paddingRightPercent", -1);
    object->setProperty("paddingBottom", 0);
    object->setProperty("paddingBottomPercent", -1);
    object->setProperty("alignSelf", "auto");
    object->setProperty("alignItems", "stretch");
    object->setProperty("alignContent", "stretch");
    object->setProperty("display", "flex");
    object->setProperty("flexWrap", "noWrap");
    object->setProperty("flexDirection", "row");
    object->setProperty("justifyContent", "flexStart");
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

} // namespace Objects
} // namespace Quite
