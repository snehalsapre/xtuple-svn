/*
 * Common Public Attribution License Version 1.0. 
 * 
 * The contents of this file are subject to the Common Public Attribution 
 * License Version 1.0 (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License 
 * at http://www.xTuple.com/CPAL.  The License is based on the Mozilla 
 * Public License Version 1.1 but Sections 14 and 15 have been added to 
 * cover use of software over a computer network and provide for limited 
 * attribution for the Original Developer. In addition, Exhibit A has 
 * been modified to be consistent with Exhibit B.
 * 
 * Software distributed under the License is distributed on an "AS IS" 
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See 
 * the License for the specific language governing rights and limitations 
 * under the License. 
 * 
 * The Original Code is PostBooks Accounting, ERP, and CRM Suite. 
 * 
 * The Original Developer is not the Initial Developer and is __________. 
 * If left blank, the Original Developer is the Initial Developer. 
 * The Initial Developer of the Original Code is OpenMFG, LLC, 
 * d/b/a xTuple. All portions of the code written by xTuple are Copyright 
 * (c) 1999-2007 OpenMFG, LLC, d/b/a xTuple. All Rights Reserved. 
 * 
 * Contributor(s): ______________________.
 * 
 * Alternatively, the contents of this file may be used under the terms 
 * of the xTuple End-User License Agreeement (the xTuple License), in which 
 * case the provisions of the xTuple License are applicable instead of 
 * those above.  If you wish to allow use of your version of this file only 
 * under the terms of the xTuple License and not to allow others to use 
 * your version of this file under the CPAL, indicate your decision by 
 * deleting the provisions above and replace them with the notice and other 
 * provisions required by the xTuple License. If you do not delete the 
 * provisions above, a recipient may use your version of this file under 
 * either the CPAL or the xTuple License.
 * 
 * EXHIBIT B.  Attribution Information
 * 
 * Attribution Copyright Notice: 
 * Copyright (c) 1999-2007 by OpenMFG, LLC, d/b/a xTuple
 * 
 * Attribution Phrase: 
 * Powered by PostBooks, an open source solution from xTuple
 * 
 * Attribution URL: www.xtuple.org 
 * (to be included in the "Community" menu of the application if possible)
 * 
 * Graphic Image as provided in the Covered Code, if any. 
 * (online at www.xtuple.com/poweredby)
 * 
 * Display of Attribution Information is required in Larger Works which 
 * are defined in the CPAL as a work which combines Covered Code or 
 * portions thereof with code not governed by the terms of the CPAL.
 */

#include "resetQOHBalances.h"

#include <qvariant.h>
#include <qmessagebox.h>

/*
 *  Constructs a resetQOHBalances as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
resetQOHBalances::resetQOHBalances(QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
    : QDialog(parent, name, modal, fl)
{
    setupUi(this);


    // signals and slots connections
    connect(_reset, SIGNAL(clicked()), this, SLOT(sReset()));
    connect(_close, SIGNAL(clicked()), this, SLOT(reject()));
    init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
resetQOHBalances::~resetQOHBalances()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void resetQOHBalances::languageChange()
{
    retranslateUi(this);
}


void resetQOHBalances::init()
{
  _classCode->setType(ClassCode);
}

void resetQOHBalances::sReset()
{
  if (QMessageBox::information( this, tr("Reset Selected QOH Balances?"),
                                tr( "<p>You are about to issue Adjustment "
				    "Transactions for all Item Sites within "
				    "the selected Warehouse and Class Code(s) "
				    "that are not Lot/Serial or Location  "
				    "Controlled to adjust their QOH values to "
				    "0.<br>Are you sure that you want to do this?</p>" ),
                                tr("Yes"), tr("No"), "", 0, 1) != 0)
    return;

  QString sql( "SELECT resetQOHBalance(itemsite_id) AS result "
               "FROM itemsite, item "
               "WHERE ((itemsite_qtyonhand < 0)"
               " AND (itemsite_item_id=item_id)" );

  if (_warehouse->isSelected())
    sql += " AND (itemsite_warehous_id=:warehous_id)";

  if (_classCode->isSelected())
    sql += " AND (item_classcode_id=:classcode_id)";
  else if (_classCode->isPattern())
    sql += " AND (item_classcode_id IN (SELECT classcode_id FROM classcode WHERE (classcode_code ~ :classcode_pattern)))";

  sql += ");";

  q.prepare(sql);
  _warehouse->bindValue(q);
  _classCode->bindValue(q);
  q.exec();

  accept();
}
