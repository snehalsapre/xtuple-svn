
CREATE OR REPLACE FUNCTION formatBoolYN(BOOLEAN) RETURNS TEXT IMMUTABLE AS '
DECLARE pBool ALIAS FOR $1;
BEGIN
  IF (pBool) THEN
    RETURN ''Yes'';
  ELSE
    RETURN ''No'';
  END IF;
END;
' LANGUAGE 'plpgsql';

