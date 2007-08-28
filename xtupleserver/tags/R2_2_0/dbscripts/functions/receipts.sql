CREATE OR REPLACE FUNCTION receipts(TEXT) RETURNS BOOLEAN AS '
DECLARE
  pTransType ALIAS FOR $1;

BEGIN
  IF (pTransType IN (''RM'', ''RB'', ''RT'', ''RP'', ''RX'', ''TR'')) THEN
    RETURN TRUE;
  ELSE
    RETURN FALSE;
  END IF;

END;
' LANGUAGE 'plpgsql';
