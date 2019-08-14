#ifndef FLEXNODE_H
#define FLEXNODE_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QLinkedList>

#include <limits>
#include <vector>

#include "3rdparty/yoga/Yoga.h"

namespace Quite {
namespace Ui {
namespace Flex {

/*****************************************************************************/

class FlexNode : public QObject {
  Q_OBJECT
  private:
    YGNodeRef node;
  private:
    QQuickItem* item;
    QLinkedList<FlexNode*> child;
    int childCount=0;
  public:
    FlexNode(QQuickItem* item);
    virtual ~FlexNode();
  public:
    void printTree();
    QString nodeInfo();
    void buildTree();
    void calculateLayoutLtr();
    void calculateLayoutRtl();
    void appendChild(FlexNode* child);
  public:
    YGNodeRef getNode() const;
  private:
    void parseFlexDirection(QString direction);
    void parseJustifyContent(QString justify);
    void parseAlignContent(QString align);
    void parseAlignItems(QString align);
    void parseAlignSelf(QString align);
    void parseDisplay(QString display);
    void parseFlexWrap(QString wrap);
    void parseOtherProps();
  private:
    void commitNewPos();
    void commitChildNewPos();
  public:
    /* flex */
    int getFlexGrow();
    int getFlexShrink();
    void setFlexGrow(int v);
    void setFlexShrink(int v);
    /* height */
    int getHeight();
    void setHeight(int height);
    int getMaxHeight();
    int getMinHeight();
    void setMaxHeight(int point);
    void setMinHeight(int point);
    /* width */
    int getWidth();
    void setWidth(int width);
    int getMaxWidth();
    int getMinWidth();
    void setMaxWidth(int point);
    void setMinWidth(int point);
    /* display */
    void setDisplayNone();
    void setDisplayFlex();
    /* flex-direction */
    void setFlexDirectionRow();
    void setFlexDirectionColumn();
    void setFlexDirectionRowReverse();
    void setFlexDirectionColumnReverse();
    /* justify-content */
    void setJustifyCenter();
    void setJustifyFlexEnd();
    void setJustifyFlexStart();
    void setJustifySpaceAround();
    void setJustifySpaceEvenly();
    void setJustifySpaceBetween();
    /* align-content */
    void setAlignContentAuto();
    void setAlignContentCenter();
    void setAlignContentFlexEnd();
    void setAlignContentStretch();
    void setAlignContentBaseline();
    void setAlignContentFlexStart();
    void setAlignContentSpaceAround();
    void setAlignContentSpaceBetween();
    /* align-items */
    void setAlignItemsAuto();
    void setAlignItemsCenter();
    void setAlignItemsFlexEnd();
    void setAlignItemsStretch();
    void setAlignItemsBaseline();
    void setAlignItemsFlexStart();
    void setAlignItemsSpaceAround();
    void setAlignItemsSpaceBetween();
    /* align-self */
    void setAlignSelfAuto();
    void setAlignSelfCenter();
    void setAlignSelfFlexEnd();
    void setAlignSelfStretch();
    void setAlignSelfBaseline();
    void setAlignSelfFlexStart();
    void setAlignSelfSpaceAround();
    void setAlignSelfSpaceBetween();
    /* flex-wrap */
    void setWrap();
    void setNoWrap();
    void setWrapReverser();
    /* margin */
    int getMarginTop();
    int getMarginLeft();
    int getMarginRight();
    int getMarginBottom();
    void setMarginTop(int point);
    void setMarginLeft(int point);
    void setMarginRight(int point);
    void setMarginBottom(int point);
    /* padding */
    int getPaddingTop();
    int getPaddingLeft();
    int getPaddingRight();
    int getPaddingBottom();
    void setPaddingTop(int point);
    void setPaddingLeft(int point);
    void setPaddingRight(int point);
    void setPaddingBottom(int point);
    /* calculate */
    int getLayoutTop();
    int getLayoutLeft();
    int getLayoutRight();
    int getLayoutWidth();
    int getLayoutBottom();
    int getLayoutHeight();

  public:
    static void initDefaultProps(QObject* object);
};

/*****************************************************************************/

} // namespace Flex
} // namespace Ui
} // namespace Quite

#endif // FLEXNODE_H
