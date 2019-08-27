#ifndef FLEXNODE_H
#define FLEXNODE_H

#include <QtDebug>
#include <QObject>
#include <QQuickItem>
#include <QLinkedList>

#include <limits>
#include <vector>

#include "3rdparty/yoga/Yoga.h"

#include "src/ui/components/windowcomponent.h"

using namespace Quite::Ui::Components;

namespace Quite {
namespace Objects {

/*****************************************************************************/

class FlexNode : public QObject {
  Q_OBJECT
  private:
    YGNodeRef node;
    bool fill=false;
    int lastTop=-1;
    int lastLeft=-1;
  private:
    QQuickItem* item;
    QLinkedList<FlexNode*> child;
    int childCount=0;
  public:
    FlexNode(QQuickItem* item, bool fill=false);
    FlexNode(QQuickItem* item, int height, int width);
    virtual ~FlexNode();
  public:
    void printTree();
    QString nodeInfo();
    void buildTree();
    void calculateLayoutLtr(int T,int L, int H,int W);
    void calculateLayoutLtr(int H,int W);
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
    /* diff update getters */
    void setLastTop(int top);
    void setLastLeft(int left);
    int getHeight() const;
    int getWidth() const;
    int getMarginLeft() const;
    int getMarginTop() const;
    int getLastLeft() const;
    int getLastTop() const;
    /* flex */
    void setFlexGrow(int v);
    void setFlexShrink(int v);
    /* height */
    void setHeight(int height);
    void setHeightPercent(int percent);
    void setMaxHeight(int point);
    void setMaxHeightPercent(int percent);
    void setMinHeight(int point);
    void setMinHeightPercent(int percent);
    /* width */
    void setWidth(int width);
    void setWidthPercent(int percent);
    void setMaxWidth(int point);
    void setMaxWidthPercent(int percent);
    void setMinWidth(int point);
    void setMinWidthPercent(int percent);
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
    bool setMarginTotal(int point);
    bool setMarginTotalPercent(int percent);
    void setMarginTop(int point);
    void setMarginTopPercent(int percent);
    void setMarginLeft(int point);
    void setMarginLeftPercent(int percent);
    void setMarginRight(int point);
    void setMarginRightPercent(int percent);
    void setMarginBottom(int point);
    void setMarginBottomPercent(int percent);
    /* padding */
    bool setPaddingTotal(int point);
    bool setPaddingTotalPercent(int percent);
    void setPaddingTop(int point);
    void setPaddingTopPercent(int percent);
    void setPaddingLeft(int point);
    void setPaddingLeftPercent(int percent);
    void setPaddingRight(int point);
    void setPaddingRightPercent(int percent);
    void setPaddingBottom(int point);
    void setPaddingBottomPercent(int percent);
    /* calculate */
    int getHeight();
    int getWidth();
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

} // namespace Objects
} // namespace Quite

#endif // FLEXNODE_H
