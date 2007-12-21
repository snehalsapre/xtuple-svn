
CREATE OR REPLACE FUNCTION selectDiscountItemsForPayment(INTEGER, INTEGER) RETURNS INTEGER AS '
DECLARE
  pVendid ALIAS FOR $1;
  pBankaccntid ALIAS FOR $2;
  _r RECORD;

BEGIN

  FOR _r IN SELECT apopen_id
              FROM apopen, terms
             WHERE((CURRENT_DATE <= (apopen_docdate + terms_discdays))
               AND (terms_discprcnt > 0.0)
               AND (apopen_terms_id=terms_id)
               AND (apopen_open)
               AND (apopen_doctype IN (''V'', ''D''))
               AND (apopen_vend_id=pVendid) ) LOOP
    PERFORM selectPayment(_r.apopen_id, pBankaccntid);
  END LOOP;

  RETURN 1;

END;
' LANGUAGE 'plpgsql';

