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
 * (c) 1999-2008 OpenMFG, LLC, d/b/a xTuple. All Rights Reserved. 
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
 * Copyright (c) 1999-2008 by OpenMFG, LLC, d/b/a xTuple
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

#include "updatePricesByPricingSchedule.h"

#include <QVariant>
#include <QMessageBox>
#include <QValidator>
#include "guiclient.h"

/*
 *  Constructs a updatePricesByPricingSchedule as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  true to construct a modal dialog.
 */
updatePricesByPricingSchedule::updatePricesByPricingSchedule(QWidget* parent, const char* name, bool modal, Qt::WFlags fl)
    : XDialog(parent, name, modal, fl)
{
  setupUi(this);


  // signals and slots connections
  connect(_close, SIGNAL(clicked()), this, SLOT(reject()));
  connect(_update, SIGNAL(clicked()), this, SLOT(sUpdate()));

  _ipshead->populate( "SELECT ipshead_id, (ipshead_name || '-' || ipshead_descrip) "
                      "FROM ipshead "
                      "ORDER BY ipshead_name;" );

  _updateBy->setValidator(new QDoubleValidator(-100, 9999, 2, _updateBy));
}

/*
 *  Destroys the object and frees any allocated resources
 */
updatePricesByPricingSchedule::~updatePricesByPricingSchedule()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void updatePricesByPricingSchedule::languageChange()
{
    retranslateUi(this);
}


void updatePricesByPricingSchedule::sUpdate()
{
  if (!_ipshead->isValid())
  {
    QMessageBox::critical( this, tr( "Select Pricing Schedule to Update"),
                           tr("You must select a Pricing Schedule to update.") );
    _ipshead->setFocus();
    return;
  }

  if (_updateBy->toDouble() == 0.0)
  {
    QMessageBox::critical( this, tr("Enter a Update Percentage"),
                           tr("You must indicate the percentage to update the selected Pricing Schedule.") );
    _updateBy->setFocus();
    return;
  }

  q.prepare( "SELECT updatePrice(ipsitem_id, :rate) "
             "FROM ipsitem "
             "WHERE (ipsitem_ipshead_id=:ipshead_id);" );
  q.bindValue(":rate", (1.0 + (_updateBy->toDouble() / 100.0)));
  q.bindValue(":ipshead_id", _ipshead->id());
  q.exec();

/*
  q.prepare( "UPDATE ipsprodcat"
             "   SET ipsprodcat_discntprcnt = ipsprodcat_discntprcnt - :rate"
             " WHERE (ipsprodcat_ipshead_id=:ipshead_id);");
  q.bindValue(":rate", (_updateBy->toDouble() / 100.0));
  q.bindValue(":ipshead_id", _ipshead->id());
  q.exec();
*/

  accept();
}

