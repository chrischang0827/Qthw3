#ifndef QTHW3_H
#define QTHW3_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Qthw3;
}
QT_END_NAMESPACE

class Qthw3 : public QWidget
{
    Q_OBJECT

public:
    explicit Qthw3(QWidget *parent = nullptr);
    ~Qthw3() override;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Qthw3 *ui;
};
#endif // QTHW3_H
