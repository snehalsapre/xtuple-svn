/*
 * This file is part of the xTuple ERP: PostBooks Edition, a free and
 * open source Enterprise Resource Planning software suite,
 * Copyright (c) 1999-2009 by OpenMFG LLC, d/b/a xTuple.
 * It is licensed to you under the Common Public Attribution License
 * version 1.0, the full text of which (including xTuple-specific Exhibits)
 * is available at www.xtuple.com/CPAL.  By using this software, you agree
 * to be bound by its terms.
 */

#ifndef DSPBREEDERDISTRIBUTIONVARIANCEBYWAREHOUSE_H
#define DSPBREEDERDISTRIBUTIONVARIANCEBYWAREHOUSE_H

#include "guiclient.h"
#include "xwidget.h"
#include <parameter.h>

#include "ui_dspBreederDistributionVarianceByWarehouse.h"

class dspBreederDistributionVarianceByWarehouse : public XWidget, public Ui::dspBreederDistributionVarianceByWarehouse
{
    Q_OBJECT

public:
    dspBreederDistributionVarianceByWarehouse(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = Qt::Window);
    ~dspBreederDistributionVarianceByWarehouse();
    virtual bool setParams(ParameterList &);

public slots:
    virtual void sPrint();
    virtual void sPopulateMenu( QMenu * );
    virtual void sFillList();

protected slots:
    virtual void languageChange();

};

#endif // DSPBREEDERDISTRIBUTIONVARIANCEBYWAREHOUSE_H
