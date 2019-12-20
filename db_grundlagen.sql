-- 1
-- A
SELECT name, addresse FROM passagier;
-- B
SELECT pinr, name, flug_h FROM PILOT WHERE quali="Captain";
-- C
SELECT DISTINCT start_in, ziel, dauer FROM FLUG;
-- D
SELECT start_in FROM FLUG WHERE ziel="London" OR ziel="Berlin";
-- E
SELECT name FROM PILOT WHERE NOT quali="Chiefpilot" AND flug_h > 1500;
-- F
SELECT fnr, ziel FROM FLUG WHERE ziel IN ("Berlin", "London", "Frankfurt", "Paris", "Koeln-Bonn");
-- G
SELECT * FROM PILOT WHERE quali IN ("Captain", "Chiefpilot") AND flug_h > 1500;

-- 2
--A
SELECT fznr, fztyp.typ, geschw FROM maschine, fztyp WHERE geschw > 870 AND maschine.typ=fztyp.typ;
-- B
SELECT DISTINCT preis FROM BUCHUNG, FLUG WHERE klasse=1 AND start_in="London" AND ziel="Boston" AND flug.fnr=buchung.fnr;
-- C
SELECT flug.fnr, start_in, ziel FROM FLUG, BUCHUNG, PASSAGIER WHERE name LIKE "% Ebert" AND flug.fnr=buchung.fnr AND buchung.panr=buchung.panr;
-- D
SELECT maschine.fznr, fztyp.typ, gewschw FROM FZTYP, BESTAND, MASCHINE WHERE gessell_bez="AIR BERLIN"
AND bestand.fznr=maschine.fznr AND fztyp.typ=maschine.typ;
-- E
SELECT DISTINCT name, fztyp.typ FROM FLUG, MASCHINE, FZTYP, PILOT WHERE geschw > 870 AND pilot.pinr=flug.pinnr AND maschine.fznr=flug.fznr AND maschine.typ=fztyp.typ;
-- F
SELECT passagier.name, fztyp.typ FROM PASSAGIER, BUCHUNG, MASCHINE, FLUG, PILOT WHERE passagiername="Swen Pfeifer" AND passagier.panr=buchung.panr AND flug.fnr=buchung.fnr AND maschine.fznr=flug.fznr AND pilot.pinr=flug.pinr;

-- 3
--A
SELECT fznr, typ, geschw FROM FZTYP NATURAL JOIN MASCHINE WHERE geschw > 870;
-- B
SELECT preis FROM BUCHUNG NATURAL JOIN FLUG WHERE klasse=1 AND ziel="Boston" AND start_in="London";
-- C
SELECT fnr, start_in, ziel FROM PASSAGIER NATURAL JOIN BUCHUNG NATURAL JOIN FLUG WHERE name="% Ebert";
-- D
SELECT fznr, typ, geschw FROM BESTAND NATURAL JOIN MASCHINE NATURAL JOIN FZTYP WHERE gesell_bez="AIR BERLIN";

-- 4 (19.12.)
-- A
SELECT COUNT(DISTINCT 'quali') AS anz FROM PILOT;
-- B
SELECT AVG('d_geschw') AS d_geschw FROM FZTYP, MASCHINE, BESTAND WHERE BESTAND.gesell_bez='LUFTHANSA' AND MASCHINE.fznr=BESTAND.fznr AND MASCHINE.typ=FZTYP.typ;
-- C
SELECT COUNT(DISTINCT 'panr') FROM BUCHUNG WHERE klasse=1;
-- D
SELECT COUNT(*) AS anz FROM PILOT, ANGESTELLT WHERE quali='Chiefpilot' AND gesell_bez='AIR FRANCE' AND ANGESTELLT.pinr=PILOT.pinr;
-- E
