#include "majorwindow.h"

#include <iostream>
Stage MajorWindow::buttonClicked(Action actNum)
{
    Stage rc = Stage::AccordingToPlan;

    procOutput out;
    action act;
    act.type = actNum;

    rc = loadInput(act);

    rc = proc_action(out, act);

    canv->setProj(out);
    canv->update();

    return rc;
}


MajorWindow::MajorWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MajorWindow)
{
    ui->setupUi(this);
    setButtonActions();
    connectButtons();
    connectColorLeds();
    this->canv = ui->widget;
}


MajorWindow::~MajorWindow()
{
    delete ui;
    delete canv;
}

Stage MajorWindow::loadInput(action &act)
{
    Stage rc = Stage::AccordingToPlan;

    switch (act.type)
    {
    case Action::Move:
        rc = load3doubles(act.args.dArgs, *(ui->led_dx), *(ui->led_dy), *(ui->led_dz));
        break;
    case Action::Rotate:
        rc = load3doubles(act.args.dArgs, *(ui->led_ox), *(ui->led_oy), *(ui->led_oz));
        break;
    case Action::Scale:
        rc = load1double(act.args.dArgs, *(ui->led_scl));
        break;
    case Action::Load:
        rc = askDir(act.args.strArgs);
        break;
    case Action::Save:
        rc = askDir(act.args.strArgs);
        break;
    default:
        break;
    }

    return rc;
}

bool MajorWindow::is_double(QString &str)
{
    bool result;
    str.toDouble(&result);
    return result;
}


Stage MajorWindow::load3doubles(double *args, ColoredLed &led1,
                               ColoredLed &led2, ColoredLed &led3)
{
    Stage rc = Stage::AccordingToPlan;

    rc = load1double(args, led1);
    if (rc == Stage::AccordingToPlan)
    {
        rc = load1double(args + 1, led2);
    }

    if (rc == Stage::AccordingToPlan)
    {
        rc = load1double(args + 2, led3);
    }

    return rc;
}

Stage MajorWindow::load1double(double *args, ColoredLed &led)
{

    Stage rc = Stage::AccordingToPlan;

    QString str = led.text();
    bool is_empty = str.isEmpty();

    if (is_empty == true)
    {
        led.setErrorPalette();
        rc = Stage::EmptyInput;
    }

    if (rc == Stage::AccordingToPlan && is_double(str) == false)
    {
        led.setErrorPalette();
        rc = Stage::InputError;
    }

    if (rc == Stage::AccordingToPlan)
    {
        *args = str.toDouble();
    }

    return rc;
}

Stage MajorWindow::askDir(char *&str)
{
    str = new char [BUFSIZ];
    char *tmpStr = QFileDialog::getOpenFileName(this, "select the carcas file",
               "/home/ApTyp/Frames", "*.fr").toUtf8().data();
    if (strlen(tmpStr) > BUFSIZ)
    {
        return Stage::TooLongFnam;
    }
    strncpy(str, tmpStr, BUFSIZ);

    return Stage::AccordingToPlan;

}


void MajorWindow::setButtonActions()
{

    ui->but_mov->setAction(Action::Move);
    ui->but_scl->setAction(Action::Scale);
    ui->but_rot->setAction(Action::Rotate);
    ui->but_load->setAction(Action::Load);
    ui->but_save->setAction(Action::Save);
}

void MajorWindow::connectButtons()
{
    connect(ui->but_mov, &ActionButton::act_clicked, this, &MajorWindow::buttonClicked);
    connect(ui->but_rot, &ActionButton::act_clicked, this, &MajorWindow::buttonClicked);
    connect(ui->but_scl, &ActionButton::act_clicked, this, &MajorWindow::buttonClicked);
    connect(ui->but_load, &ActionButton::act_clicked, this, &MajorWindow::buttonClicked);
    connect(ui->but_save, &ActionButton::act_clicked, this, &MajorWindow::buttonClicked);
}


void MajorWindow::connectColorLeds()
{
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dx, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dy, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dz, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_ox, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_oy, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_oz, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dx_cam, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dy_cam, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_dz_cam, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_ox_cam, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_oy_cam, &ColoredLed::setNormalPalette);
    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_oz_cam, &ColoredLed::setNormalPalette);

    connect(this, &MajorWindow::led_setNormalPalette,
            ui->led_scl, &ColoredLed::setNormalPalette);
}
