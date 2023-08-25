#ifndef CALCCONTROLLER_H
#define CALCCONTROLLER_H

#include "../model/Model.h"

class CalcController {

public:

    CalcController(CalcModel *m):model(m) {};

    private:
        CalcModel *model;
};

#endif  // CALCCONTROLLER_H
