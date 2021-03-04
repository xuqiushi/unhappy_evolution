#include <QStyleOption>
#include <QPainter>
#include <QProxyStyle>


class CustomDragInStyle : public QProxyStyle {
    Q_OBJECT
public:
//    CustomDragInStyle(){};
//    ~CustomDragInStyle() {};
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter,
                     const QWidget *widget) const override {
        if (element == QStyle::CE_ShapedFrame) {
            painter->drawRect(option->rect);
            painter->setBrush(QBrush(Qt::yellow));
            painter->fillRect(option->rect, painter->brush());
        } else {
            QProxyStyle::drawControl(element, option, painter, widget);
        }

    };
};