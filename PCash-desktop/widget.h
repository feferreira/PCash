#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class PgConnection;
class Operacao;

class Widget : public QWidget
{
    Q_OBJECT
    Operacao *op{nullptr};
public:
    Widget(QWidget *parent = nullptr);
    void setConnection(PgConnection *conn);
    ~Widget();

private slots:
    void on_InsereOrdem_clicked();

    void on_insereProvento_clicked();

private:
    PgConnection *conn{nullptr};
    Ui::Widget *ui;
    bool getValoresDefault();
};
#endif // WIDGET_H
