#include "findway.h"
#include "ui_findway.h"

FindWay::FindWay(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FindWay)
{
    ui->setupUi(this);
    loadSettings();
    validLine = new CustomIntValidator(1, 999, this);
    ui->wEdit->setValidator(validLine);
    ui->hEdit->setValidator(validLine);
    errorMessage = new QMessageBox(this);
    errorMessage->setWindowTitle("Ошибка");
    errorMessage->setStandardButtons(QMessageBox::Ok);
    ui->fieldView->setRenderHint(QPainter::Antialiasing);

    connect(ui->fieldView, &CustomGraphicsView::signalGrayColor,this, [this](){
        errorMessage->setText("Путь нельзя начать/закончить на участке с препятствием");
        errorMessage->show();
    });

    connect(ui->fieldView, &CustomGraphicsView::signalLetter,this, [this](){
        errorMessage->setText("Вы не можете закончить путь в точке начала");
        errorMessage->show();
    });

    connect(ui->fieldView, &CustomGraphicsView::signalBorder, this, [this](){
        errorMessage->setText("Вы попали на границу нескольких ячеек. Попробуйте снова.");
        errorMessage->show();
    });

    connect(ui->fieldView, &CustomGraphicsView::signalNoWay, this, [this](){
        errorMessage->setText("Путь между A и B отсутствует");
        errorMessage->show();
    });
}

FindWay::~FindWay()
{
    saveSettings();
    delete validLine;
    delete errorMessage;
    delete ui;
}

void FindWay::closeEvent(QCloseEvent *event){
    saveSettings();
    QWidget::closeEvent(event);
}

void FindWay::saveSettings(){
    QSettings settings("Testovoe", "App");
    settings.setValue("geometry", saveGeometry());
}

void FindWay::loadSettings(){
    QSettings settings("Testovoe", "App");
    restoreGeometry(settings.value("geometry").toByteArray());
}


void FindWay::on_generationButton_clicked()
{
    if (ui->wEdit->text() == "" || ui->hEdit->text() == ""){
        errorMessage->setText("Оба поля Widht и Height должны быть заполнены");
        errorMessage->show();
        return;
    }

    if (ui->wEdit->text() == "0" || ui->hEdit->text() == "0"){
        errorMessage->setText("Widht и Height не могут быть равными 0");
        errorMessage->show();
        return;
    }

    ui->fieldView->clearFocus();
    ui->fieldView->clearMask();
    int h = ui->hEdit->text().toInt();
    int w = ui->wEdit->text().toInt();
    ui->fieldView->createScene(h, w);
}




void FindWay::on_wEdit_textChanged(const QString &arg1)
{
    QString str = arg1;
    validLine->fixup(str);
    ui->wEdit->setText(str.simplified().remove(' '));
}


void FindWay::on_hEdit_textChanged(const QString &arg1)
{
    QString str = arg1;
    validLine->fixup(str);
    ui->hEdit->setText(str.simplified().remove(' '));
}



