CREATE OR REPLACE FUNCTION qtyOrdered(INTEGER, INTEGER) RETURNS NUMERIC AS '
DECLARE
  pItemsiteid ALIAS FOR $1;
  pLookahead ALIAS FOR $2;
  _itemType TEXT;
  _result NUMERIC;

BEGIN

  RETURN qtyOrdered(pItemsiteid, startOfTime(), (CURRENT_DATE + pLookahead));

END;
' LANGUAGE 'plpgsql';


CREATE OR REPLACE FUNCTION qtyOrdered(INTEGER, DATE) RETURNS NUMERIC AS '
DECLARE
  pItemsiteid ALIAS FOR $1;
  pDate ALIAS FOR $2;

BEGIN

  RETURN qtyOrdered(pItemsiteid, startOfTime(), pDate);

END;
' LANGUAGE 'plpgsql';


CREATE OR REPLACE FUNCTION qtyOrdered(INTEGER, DATE, DATE) RETURNS NUMERIC AS '
DECLARE
  pItemsiteid ALIAS FOR $1;
  pStartDate ALIAS FOR $2;
  pEndDate ALIAS FOR $3;
  _itemType TEXT;

BEGIN

  SELECT item_type INTO _itemType
  FROM item, itemsite
  WHERE ( (itemsite_item_id=item_id)
   AND (itemsite_id=pItemsiteid) );

  IF ( SELECT metric_value
	FROM metric
	WHERE ((metric_name = ''MultiWhs'')
	AND (metric_value = ''t''))) THEN
    IF (_itemType IN (''P'', ''O'')) THEN
      RETURN orderedByPo(pItemsiteid, pStartDate, pEndDate) +
	     orderedByTo(pItemsiteid, pStartDate, pEndDate);

    ELSIF (_itemType IN (''M'', ''C'', ''B'')) THEN
      RETURN orderedByWo(pItemsiteid, pStartDate, pEndDate) +
	     orderedByTo(pItemsiteid, pStartDate, pEndDate);

    ELSE
      RETURN 0 +
	     orderedByTo(pItemsiteid, pStartDate, pEndDate);
    END IF;
  ELSE
    IF (_itemType IN (''P'', ''O'')) THEN
      RETURN orderedByPo(pItemsiteid, pStartDate, pEndDate);

    ELSIF (_itemType IN (''M'', ''C'', ''B'')) THEN
      RETURN orderedByWo(pItemsiteid, pStartDate, pEndDate);

    ELSE
      RETURN 0;
    END IF;
  END IF;

END;
' LANGUAGE 'plpgsql';
