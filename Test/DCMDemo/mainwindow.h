#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include "../config/include/dcmtk/config/osconfig.h"

//#include "dcmtk/oflog/tracelog.h"
#include "dcmtk\dcmdata\dctk.h"

//#include "G:\DCM\dcmtk-3.6.5\dcmdata\include\dcmtk\dcmdata\dctk.h"
//#include "G:\DCM\dcmtk-3.6.5\dcmdata\include\dcmtk\dcmdata\dcfilefo.h"
//#include "G:\DCM\dcmtk-3.6.5\ofstd\include\dcmtk\ofstd\ofstring.h"
//#include "G:\DCM\dcmtk-3.6.5\dcmdata\include\dcmtk\dcmdata\dcitem.h"

#include <iostream>
#include <string>
//#include <winnt.h>
//#include <stdint.h>
//#include <tchar.h>

//#include "xiofile.h"
//#include "ximage.h"



#include "LibCore.h"


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
