#ifndef FINDWAY_H
#define FINDWAY_H

#include <QWidget>
#include <QMessageBox>
#include <QSettings>
#include "customintvalidator.h"


QT_BEGIN_NAMESPACE
namespace Ui { class FindWay; }
QT_END_NAMESPACE

class FindWay : public QWidget
{
    Q_OBJECT

public:
    FindWay(QWidget *parent = nullptr);
    ~FindWay();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::FindWay *ui;
    CustomIntValidator* validLine;
    QMessageBox* errorMessage;
    QMessageBox* loadMessage;
    void saveSettings();
    void loadSettings();

private slots:
    void on_generationButton_clicked();

    void on_wEdit_textChanged(const QString &arg1);

    void on_hEdit_textChanged(const QString &arg1);

};
#endif // FINDWAY_H
