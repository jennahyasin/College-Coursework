-- Before you begin create the database and tables with the script
--  assignment_3_schema.sql

-- 1  Find the model number and price of all products (of any type) made by 
--    manufacturer B?  The result should be in order by model number and 
--    then by  price (low to high)  
--     hint:  use a union over the pc, laptop and printer tables
SELECT pc.model, pc.price
FROM pc
INNER JOIN product p ON pc.model=p.model
WHERE maker='B'
UNION
SELECT l.model, l.price
FROM laptop l 
INNER JOIN product p ON l.model=p.model
WHERE maker='B'
UNION 
SELECT pr.model, pr.price
FROM printer pr
INNER JOIN product p ON pr.model=p.model
WHERE maker='B'
ORDER BY model, price;
-- 2  Find those manufacturers that sell laptops but not pc’s. 
--    Sort result by maker.
--    hint: use "not in" predicate and a subselect on the pc table.
SELECT distinct maker
FROM product p
INNER JOIN laptop l ON p.model=l.model
WHERE p.maker NOT IN (SELECT p2.maker FROM product p2
						INNER JOIN pc ON p2.model=pc.model)
ORDER BY maker;
-- 3  Find the hard-drive sizes that occur in two or more PC’s.   
--    Sort the list low to high. [hint: use group and having]
select pc.hd 
FROM pc
GROUP BY hd
HAVING COUNT(hd) >=2
ORDER BY hd ASC; 
-- 4  Find  PC models that have both the same speed and RAM.  The
--    output should have 2 columns,  "model1" and "model2".  A pair should be
--    listed only once:  e.g. if (f, g) is in the result then (g,f) should not
--    appear.   Sort the output by the first column.
SELECT pc.model as 'model1', pc2.model as 'model2' 
FROM pc 
INNER JOIN pc pc2 ON pc.ram=pc2.ram
	AND pc.speed=pc2.speed
WHERE pc.model>pc2.model
ORDER BY model1;
-- 5  Find the maker or makers of PC’s with at least three different speeds. 
--    If more than one, order by maker.
--    hint: use a having clause containing a count(distinct   ) function.
SELECT p.maker
FROM product p
INNER JOIN pc ON p.model=pc.model
GROUP BY maker
HAVING COUNT(DISTINCT(pc.speed)) >= 3
ORDER BY p.maker;
-- 6  Find those makers of at least two different computers (PC’s or 
--    laptops)  with speeds of at least 2.80.  Order the list by maker. 
--    hint:  use a subquery that does a UNION of the pc and laptop tables.
SELECT maker FROM 
        (SELECT p.maker, pc.model
                FROM pc 
                INNER JOIN product p ON p.model = pc.model
                WHERE pc.speed >= 2.80
                UNION
                SELECT p.maker, l.model
                FROM laptop l
                INNER JOIN product p ON p.model = l.model
                WHERE l.speed >= 2.80) AS allMakers
GROUP BY maker
HAVING COUNT(model) >= 2
ORDER BY maker;
-- 7  Find the maker(s) of the computer (PC or laptop) with the highest 
--    speed.  If there are multiple makers, list all of them and order by maker.
SELECT p.maker
FROM product p 
INNER JOIN pc ON p.model=pc.model
WHERE pc.speed=(SELECT MAX(speed) 
					FROM(SELECT speed FROM pc
                    UNION 
                    SELECT speed
                    FROM laptop) AS pcSpeed)
UNION 
SELECT p.maker
FROM product p
INNER JOIN laptop l ON p.model=l.model
WHERE l.speed=(SELECT MAX(speed) 
				FROM(SELECT speed FROM pc
                UNION
                SELECT speed
                FROM laptop) AS laptopSpeed)
ORDER BY maker; 