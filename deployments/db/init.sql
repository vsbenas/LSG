-- MariaDB dump 10.19  Distrib 10.11.16-MariaDB, for Linux (x86_64)
--
-- ------------------------------------------------------
/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Account`
--

DROP TABLE IF EXISTS `Account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Account` (
  `Name` char(25) NOT NULL,
  `Slaptazodis` CHAR(128) NOT NULL,
  `Money.Pocket` int(11) NOT NULL DEFAULT 0,
  `Money.Bank` int(11) NOT NULL DEFAULT 0,
  `Seklos` smallint(11) NOT NULL DEFAULT 0,
  `Zole` smallint(11) NOT NULL DEFAULT 0,
  `Biznis` tinyint(11) NOT NULL DEFAULT 0,
  `Wanted` tinyint(11) NOT NULL DEFAULT 0,
  `Gangas` tinyint(11) NOT NULL DEFAULT -1,
  `Kalejime` int(11) NOT NULL DEFAULT 0,
  `MLicense` tinyint(20) NOT NULL DEFAULT 0,
  `Mobsas` mediumint(11) NOT NULL DEFAULT 0,
  `Namu` tinyint(11) NOT NULL DEFAULT 0,
  `Ginklas0` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo0` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas1` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo1` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas2` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo2` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas3` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo3` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas4` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo4` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas5` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo5` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas6` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo6` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas7` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo7` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas8` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo8` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas9` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo9` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas10` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo10` mediumint(11) NOT NULL DEFAULT 0,
  `Ginklas11` tinyint(11) NOT NULL DEFAULT 0,
  `Ammo11` mediumint(11) NOT NULL DEFAULT 0,
  `Stilius` tinyint(11) NOT NULL DEFAULT 0,
  `pBoxiSkill` tinyint(11) NOT NULL DEFAULT 0,
  `pKneeSkill` tinyint(11) NOT NULL DEFAULT 0,
  `pKungSkill` tinyint(11) NOT NULL DEFAULT 0,
  `pGrabSkill` tinyint(11) NOT NULL DEFAULT 0,
  `pElbowSkill` tinyint(11) NOT NULL DEFAULT 0,
  `Job` tinyint(11) NOT NULL DEFAULT 0,
  `Drabuziai` smallint(11) NOT NULL DEFAULT 0,
  `Uniforma` smallint(11) NOT NULL DEFAULT 0,
  `Uniformd` tinyint(11) NOT NULL DEFAULT 0,
  `Adminas` tinyint(11) NOT NULL DEFAULT 0,
  `Xp` mediumint(11) NOT NULL DEFAULT 0,
  `Lytis` tinyint(11) NOT NULL DEFAULT 0,
  `pos_X` float DEFAULT NULL,
  `pos_Y` float DEFAULT NULL,
  `pos_Z` float DEFAULT NULL,
  `Interior` tinyint(11) NOT NULL DEFAULT 0,
  `Drugs` smallint(11) NOT NULL DEFAULT 0,
  `MotoLicense` tinyint(11) NOT NULL DEFAULT 0,
  `SLicense` tinyint(11) NOT NULL DEFAULT 0,
  `Laikrodis` tinyint(11) NOT NULL DEFAULT 0,
  `Draudimasg` tinyint(11) NOT NULL DEFAULT 0,
  `World` int(11) NOT NULL DEFAULT 0,
  `Insurance` smallint(11) NOT NULL DEFAULT 0,
  `Teises` tinyint(11) NOT NULL DEFAULT 0,
  `Teorinis` tinyint(11) NOT NULL DEFAULT 0,
  `Kortele` tinyint(11) NOT NULL DEFAULT 0,
  `Imtuvas` tinyint(11) NOT NULL DEFAULT 0,
  `IP` text DEFAULT NULL,
  `Lead` tinyint(11) NOT NULL DEFAULT 0,
  `Kreditai` smallint(11) NOT NULL DEFAULT 0,
  `Vip` smallint(11) NOT NULL DEFAULT 0,
  `Raktas` tinyint(11) NOT NULL DEFAULT 0,
  `Pradirbo` smallint(11) NOT NULL DEFAULT 0,
  `F0` tinyint(11) NOT NULL DEFAULT 0,
  `F1` tinyint(11) DEFAULT 0,
  `F2` tinyint(11) DEFAULT 0,
  `F3` tinyint(11) DEFAULT 0,
  `F4` tinyint(11) DEFAULT 0,
  `F5` tinyint(11) DEFAULT 0,
  `F6` tinyint(11) DEFAULT 0,
  `F7` tinyint(11) DEFAULT 0,
  `Akiniai` tinyint(11) DEFAULT 0,
  `Zuvis` smallint(11) DEFAULT 0,
  `Masalas` smallint(11) DEFAULT 0,
  `Sotumas` smallint(11) DEFAULT 80,
  `LSD` smallint(11) DEFAULT 0,
  `Ratai` smallint(11) DEFAULT 0,
  `Kepure` tinyint(11) DEFAULT 0,
  `Salmas` tinyint(11) DEFAULT 0,
  `Cig` smallint(11) DEFAULT 0,
  `HP` int(11) DEFAULT 50,
  `Armour` int(11) DEFAULT 0,
  `CFG` int(11) DEFAULT 2147483647,
  `Naud` int(11) DEFAULT 0,
  `Bakelis` int(11) DEFAULT 0,
  `PLigonine` int(11) DEFAULT 0,
  `Loterijos` int(11) DEFAULT 0,
  `Adrenalinas` int(11) DEFAULT 0,
  PRIMARY KEY (`Name`(24))
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Account`
--

LOCK TABLES `Account` WRITE;
/*!40000 ALTER TABLE `Account` DISABLE KEYS */;
/*!40000 ALTER TABLE `Account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `AchInfo`
--

DROP TABLE IF EXISTS `AchInfo`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `AchInfo` (
  `id` int(11) NOT NULL,
  `Name` varchar(255) DEFAULT NULL,
  `Description` varchar(255) DEFAULT NULL,
  `amount` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `AchInfo`
--

LOCK TABLES `AchInfo` WRITE;
/*!40000 ALTER TABLE `AchInfo` DISABLE KEYS */;
INSERT INTO `AchInfo` VALUES
(0,'Newbie','Pirma karta issaugok zaidima.',1),
(1,'First job','Mano pirmasis darbas BMXeris!',1),
(2,'Car rent','Issinuomok masina.',1),
(3,'First vehicle','Daugiau jokio viesojo transporto!',1),
(4,'Public transport','20 kartu pasinaudok autobusu ar mikro autobusu paslaugomis.',20),
(5,'Driver','Masina nuvaziuok 50.000KM.',50000),
(6,'Healthy life','Dviraciu nuvaziuok daugiau nei 1.000KM.',1000),
(7,'Racer','Laimek 10 RACE event\'u.',10),
(8,'Advanced racer','Laimek 100 RACE event\'u.',100),
(9,'Come here piggy','Nuzudyk 200 policijos pareigunu.',200),
(10,'First blood','O ne, as nuzudziau zmogu!',1),
(11,'First of many','Tai stai kaip atrodo Los Santos ligonine.',1),
(12,'Starving','As toks alkanas!',1),
(13,'Stunter','Uzsok i 1.000 BMX darbo vietu.',1000),
(14,'Wanted','10-tas ieskomumo lygis.',1),
(15,'Manhunt','Sumedziok labiausiai ieskoma zmogu mieste.',1),
(16,'Fast food','20 kartu pavalgyk greito maisto restorane.',20),
(17,'Paintballer','Paintball zaidime nusauk 1.200 zmoniu.',1200),
(18,'Home sweet home','Issaugok zaidima name.',1),
(19,'First home','Nusipirk buta arba nama.',1),
(20,'For rent','Isnuomok savo nama ar buta.',1),
(21,'Against athorities','Nuzudyk 20 Admin\'u.',20),
(22,'Workaholic','Pradirbk daugiau nei 800min per \"LSG savaite\".',1),
(23,'Prisoner','Gauk daugiau nei 2h bausmes kalejime ir isbuk visa tau skirta laika.',1),
(24,'Prison break','Pabek i kalejimo.',1),
(25,'Michael Scofield','Jis ir vel laisveje? Pabek is kalejimo uz kreditus.',1),
(26,'Recovery','1.000 kartu ligonineje palauk kol tau atsistatys pilnas gyvybiu stulpelis.',1000),
(27,'Medic','Suteik 2000 sveikatos pazymejimu.',2000),
(28,'Scout','Visada pasiruoses! Turek visas teises bei sveikatos pazymejima.',1),
(29,'Designer','Namo ar buto interjere pastatyk daugiau nei 10 baldu.',10),
(30,'Mailman','Pristatyk 3.000 laisku.',3000),
(31,'Fisherman','Sugauk 2.000 zuvu.',2000),
(32,'Email','Tai mano pirmoji parasyta Email zinute.',1),
(33,'Out of fuel','O ne! Pasibaige degalai...',1),
(34,'Mechanic','Pataisyk ar patobulink 5.000 masinu.',5000),
(35,'Drug dealer','Parduok daugiau nei 1.000 amfetamino paketu.',1000),
(36,'Gun dealer','Parduok daugiau nei 50.000 kulku.',50000),
(37,'Freshman','Surink 500XP.',1),
(38,'Traitor','Ilgiau ar trumpiau pabuvok visose gaujose per viena savaite.',1),
(39,'Scrap-iron','Nutempk 1.000 darbiniu masinu i savartyna.',1000),
(40,'Broke','Jusu saskaitoje nepakanka pinigu apmoketi siai operacijai. Prasome pasipildyti saskaita.',1),
(41,'Invitation','Mano pirmasis darbas su pakvietimu.',1),
(42,'Drug king','Su gauja iskovok visus tris narkotiku sandelius vienu metu.',1),
(43,'Under the mattress','Namuose pasidek daugiau nei 10.000LT',1),
(44,'Millionaire','Na stai ir milijonas!',1),
(45,'Businessman','Nusipirk versla.',1),
(46,'Smuggler','Pristatyk 500 amfetamino paketu.',500),
(47,'Thief','Pavok daugiau nei 2.000 automobiliu.',2000),
(48,'Wardrobe','Nusipirk daugiau nei 15 skin\'u.',15),
(49,'Pothead','20 kartu parukyk zoles.',20),
(50,'Drug addict','Suvartok daugiau nei 400 narkotiku paketu.',400),
(51,'Fine','Gauk 10.000LT vertes bauda.',1),
(52,'Released on bail','Sumokek advokatui, kad tave isteisintu.',1),
(53,'Can\'t find my place','Isbandyk visus darbus be pakvietimo per savaite.',1),
(54,'Speed camera','Buk uzfiksuotas greicio matuoklio 100 kartu.',100),
(55,'Homeless man','200 kartu pavalgyk is siuksliu konteinerio.',200),
(56,'Life Sentence','Kaleime praleisk ilgiau nei 24 valandas.',1440),
(57,'First flight','Nuskrisk i kita miesta.',1),
(58,'Suicide','50 kartu nusizudyk niekieno nepadedamas.',50),
(59,'Parachute','Issok su parasiutu is lektuvo ar nuo pastato.',1),
(60,'Poker addict','Suzaisk 5.000 kortu dalinimus.',5000),
(61,'High bidder','Pokeryje padaryk bent 100.000LT statyma.',1),
(62,'Taxi driver','Taksometras rodo 25.000KM.',25000),
(63,'Orator','Parasyk daugiau nei 1.000 skelbimu.',1000),
(64,'For my hood','Nuzudyk 500 kitu gauju nariu.',500),
(65,'The Don','Perimk 20 sandeliu.',20),
(66,'Officer','Policijos pareigose isdirbk 4 algas(turi buti prisijunges per algas).',4),
(67,'Clean up','Su kolegomis isvalyk gaudomuju sarasa(prisijungus gaudomuju turi buti daugiau nei 10).',1),
(68,'Radio man','Praklausyk radijos daugiau nei 10 valandu.',600),
(69,'Saving lifes','Pagydyk 3.000 zmoniu.',3000),
(70,'The trade','Pasinaudok mainu sistema(per abi puses turi ieiti namas arba masina bei pinigai).',1),
(71,'For sale','Parduok savo nama ar buta kitam zmogui.',1),
(72,'Active gang member','Purskiamais dazais uzpaisyk 100 gauju tag\'u.',100),
(73,'Stay clean','Neturek narkotiku, kai tave aptikrina pareigunas.',1),
(74,'Competitor','Sudalyvauk 5 eventuose is eiles.',1),
(75,'Full tank','30 kartu pripildyk automobilio ar kitos transporto priemones baka.',30),
(76,'Routine','500 kartu pravaziuok ivairiu darbu marsrutus.',500),
(77,'Travaler','Sudalyvauk 300-uose autoklubo kelioniu.',300),
(78,'Self defence','Nusipirk ginkla ir sarvus.',1),
(79,'LSG Mania','Serveryje be atsijungimo isbuk 8 valandas.',1),
(80,'Changing sides','Palik gauja del policijos ar atvirksciai(neatsijungus).',1),
(81,'Lawyer','Isteisink 1000 nusikalteliu.',1000),
(82,'Communicate','Parasyk daugiau nei 20.000 SMS zinuciu.',20000),
(83,'Boat','Hmm, kur deti pinigus? Kodel gi nenusipirkus jachtos?',1),
(84,'Creeper','10 kartu nusipirk dildo.',10),
(85,'Assasin','Su peiliu nuzudyk 100 zmoniu.',100),
(86,'Safety first','Nusipirk salma.',1),
(87,'Fight club','Ismok visus musimosi stilius.',1),
(88,'Rainbow man','Turek 7 nick\'o spalvas.',1),
(89,'Sharpshooter','100 kartu sudalyvauk saudyklos rungtyje.',100),
(90,'Incorrectly accused','Patvirtinta BAN apeliacija.',1),
(91,'Partnership','Paspausk ranka administratoriui.',1),
(92,'Speed limit','Pasiek maksimalu imanima greiti.',1),
(93,'Open doors','Surink 100000XP, kad galetum patekti i visus darbus.',1),
(94,'Promoted','Gauk direktoriaus ar administratoriaus posta.',1),
(95,'I won!','Laimek 1 milijona euru pokeryje.',1000000),
(96,'Taxes','20 kartu sumokek mokescius.',20),
(97,'Fireman','Uzgesink 500 gaisru.',500),
(98,'Trunk','Bagazineje pasidek bent 10.000LT.',1),
(99,'Generous','Padovanok bent 3.000LT naujokui.',3000),
(100,'No luck','150 nesekmingu loterijos bilietu...',150),
(101,'New Year','Issauk 200 fejerverku.',200),
(102,'Drift King','Pradriftink 100.000.000 tasku!',100000000),
(103,'Pirate','40 kartu rask lobi.',40),
(104,'Butcher','Surink 3.000 mesu.',3000),
(205,'Garbage man','Istustink ir i savartyna nuvezk 400 konteineriu.',400),
(206,'Spammer','Gauk kick\'a nuo \"anti-cheat\" uz spaminima.',1),
(207,'a','a',15),
(208,'Artillery','Vienu metu turek visu rusiu ginklus.',1),
(209,'Call me maybe','Sulauk 1.000 skambuciu is zaideju.',1000),
(210,'The Leader','50 ar daugiau kartu perimk sandeli.',50),
(211,'It\'s my block','Uzpaisyk visus savo gaujos tagus po uzgrobimo.',1),
(212,'Food poisoning','100 kartu apsinuodyk maistu.',100),
(213,'Stalker','Parasyk /admin, kai jie visi prisijunge vienu metu.',1),
(214,'Under the limit','20 valandu pravazinek su ijungtu /autop.',1200),
(215,'Its me!','Uzsidek vardinius numerius.',1),
(216,'Kidnap','Surisk ir is miesto isvezk 500 zmoniu.',500),
(217,'Truck driver','Nuvezk 2.000 kroviniu.',2000),
(218,'Delivery boy','Pristatyk 3.000 prekiu.',3000),
(219,'Fully settled','Na va, stai ir antras namas.',1),
(220,'Pizza boy','Parduok 500 picu.',500),
(221,'Peon','4 \"LSG savaites\" pradirbk darbuose kurie nereikalauja daugiau kaip 1.000XP.',4),
(222,'Farmer','1.500 checkpoint\'u tikram fermeriui - ne beda.',1500),
(223,'I love my cars','Nusipirk visas 3 masinas, kuriu kiekvienos verte nemazesne nei 125.000LT',3),
(224,'Middle class','Nusipirkes masina uz nemaziau kaip 15.000LT, bet nedaugiau kaip uz 65.000LT su ja nuvaziuok 10.000KM.',10000),
(225,'Warder','Dalyvauk 100-te kaliniu pabegimu numalsinimu ir sustabdymu.',100),
(226,'Deposit','Pasidek daugiau nei 200.000LT i banka.',1),
(227,'Emergency','Vienu paemimu pasiimk 100.000LT is banko saskaitos.',1),
(228,'First pay slip','Pirmoji alga darbe su pakvietimu.',1),
(229,'Get paid','Gauk 7 algas is eiles.',7),
(230,'Builder','Sutvarkyk 500 remontuojamu vietu.',500),
(231,'Celebrity','Limuzino galineje sedyneje nuvaziuok daugiau nei 1.000KM.',1000),
(232,'Banker','Pripildyk 700 bankomatu.',700),
(233,'Show off','Patiuninguok masina uz nemaziau nei 10.000LT.',1),
(234,'Changing looks','Nusipirk bent 4 dalykus aksesuaru parduotuveje.',4),
(235,'a','a',200),
(236,'Buster','Sugauk 200 masinu vagiu ar kontrabandininku.',200),
(237,'Land, water, air','Nusipirk masina arba motocikla, valti ir sraigtasparni.s',1),
(238,'Stay safe','Bent karta, per \"LSG savaite\" pasikeisk slaptazodi ir taip daryk 3 tokias savaites.',3),
(239,'Valentine','Pasibuciuok daugiau nei 100-ta kartu.',100),
(240,'Drunk like always','Pasiek paskutini girtumo lygi 50 kartu.',50),
(241,'Loyal to the gang','Isbuk vienoje gaujoje daugiau nei 2 menesius.',60),
(242,'Veteran','50.000XP? Juokai.',1),
(105,'Goldfish','Pagauk auksine zuvele.',1),
(106,'Psycho Killer','Padaryk masyvu zudyma 13 kartu.',13),
(107,'Completionist','Isidarbink inkasatoriumi.',1),
(108,'Homeowner','Nusipirk nama arba buta is serverio.',1),
(109,'Online banking','Pervesk kitam zaidejui pinigu arba kreditu.',1),
(110,'Double the money','Isbuk prisijunges visa happy hour be AFK.',1),
(111,'No space','Nusipirk papildoma vieta automobiliu saugykloje.',1),
(112,'Phone addict','Pasipildyk saskaita iki 10.000 EUR.',1),
(113,'Rider','Pasiek maksimalia masinos rida.',1),
(114,'Leader','Tapk gaujos vadu arba pavaduotoju.',1),
(115,'The Starter','Pradek skaiciavima.',1),
(116,'Resourceful','Pavaisink 100 cigareciu kitiems zaidejams.',100),
(117,'Greetings','Pasisveikink su 3 zaidejais.',3),
(118,'Upper class','Turek du namus vienu metu.',1),
(119,'Designer','Pasikelk namo lygi.',1),
(120,'Break in','Isilauzk i 5 namus.',5),
(121,'The VIP Experience','Nusipirk VIP ginklus 100 kartu.',100),
(122,'Moving day','Nusipirk 200 baldu is baldu, elektronikos ar interjero parduotuviu.',200),
(123,'A new man','Atsiblokuok zaidime.',1),
(124,'Car Insurance','Apdrausk savo automobili masinu draudime.',1),
(125,'Participant','Sudalyvauk 1000 eventu.',1000),
(126,'Drug abuse','Suvartok 600 narkotiku.',600),
(127,'Pusher','Is sandelio nusipirk 100 narkotiku.',100),
(128,'Harvest','10 kartu nuimk derliu savo namuose.',10),
(129,'Tourist','Viesbutyje issisaugok zaidima 300 kartu.',300),
(130,'Farmer','Apvaziuok ukininku marsruta 50 kartu.',50),
(131,'Healed','Pasigydyk pas medika 100 kartu.',100),
(132,'Coinflip','Monetoje laimek bent 1.000.000 EUR.',1),
(133,'Fill up','Degalineje uzsipilk 10.000 litru degalu.',10000),
(134,'Promoted','Gauk paaukstinima darbo pareigose.',1);
/*!40000 ALTER TABLE `AchInfo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Achievements`
--

DROP TABLE IF EXISTS `Achievements`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Achievements` (
  `Name` varchar(255) NOT NULL DEFAULT '',
  `id` int(11) NOT NULL DEFAULT 0,
  `progress` float(11,0) DEFAULT NULL,
  `status` int(11) DEFAULT 0,
  PRIMARY KEY (`Name`,`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Achievements`
--

LOCK TABLES `Achievements` WRITE;
/*!40000 ALTER TABLE `Achievements` DISABLE KEYS */;
/*!40000 ALTER TABLE `Achievements` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `BANS`
--

DROP TABLE IF EXISTS `BANS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `BANS` (
  `Vardas` varchar(24) NOT NULL,
  `IP` varchar(255) NOT NULL DEFAULT '',
  `Priezastis` varchar(255) DEFAULT NULL,
  `Adminas` varchar(255) DEFAULT NULL,
  `Date` datetime DEFAULT NULL,
  `Gauja` int(11) DEFAULT NULL,
  `Hidden` int(11) DEFAULT NULL,
  PRIMARY KEY (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `BANS`
--

LOCK TABLES `BANS` WRITE;
/*!40000 ALTER TABLE `BANS` DISABLE KEYS */;
/*!40000 ALTER TABLE `BANS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Bagazine`
--

DROP TABLE IF EXISTS `Bagazine`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Bagazine` (
  `Vardas` varchar(30) DEFAULT NULL,
  `Masina` smallint(6) DEFAULT NULL,
  `Item` int(11) DEFAULT NULL,
  `Count` int(11) DEFAULT NULL,
  KEY `pagr` (`Vardas`,`Masina`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Bagazine`
--

LOCK TABLES `Bagazine` WRITE;
/*!40000 ALTER TABLE `Bagazine` DISABLE KEYS */;
/*!40000 ALTER TABLE `Bagazine` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Bizniai`
--

DROP TABLE IF EXISTS `Bizniai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Bizniai` (
  `Name` text CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `Owner` text DEFAULT NULL,
  `EnterX` text DEFAULT NULL,
  `EnterY` text DEFAULT NULL,
  `EnterZ` text DEFAULT NULL,
  `ExitX` text DEFAULT NULL,
  `ExitY` text DEFAULT NULL,
  `ExitZ` text DEFAULT NULL,
  `EnterInt` int(11) DEFAULT NULL,
  `EnterWorld` int(11) NOT NULL DEFAULT 0,
  `Price` int(11) DEFAULT 0,
  `Number` int(11) DEFAULT 0,
  `Earning` int(11) DEFAULT 0,
  `Type` int(11) DEFAULT 0,
  `Owned` int(11) DEFAULT 0,
  `Radio` int(11) DEFAULT 0,
  `Mokesciai` int(11) DEFAULT 14,
  `Paeme` int(11) DEFAULT 0,
  PRIMARY KEY (`EnterWorld`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Bizniai`
--

LOCK TABLES `Bizniai` WRITE;
/*!40000 ALTER TABLE `Bizniai` DISABLE KEYS */;
INSERT INTO `Bizniai` VALUES
('-','Nera','655.338134','-502.884033','16.335937','296.919982','-108.071998','1001.515625',6,2000,200000,1,0,6,0,0,0,0),
('-','Nera','1309.888061','-1367.342529','13.529211','1131.729370','-348.983489','1055.947143',1,2001,220000,1,0,17,0,0,0,0),
('-','Nera','1654.389282','-1655.827758','22.515625','2193.240478','-1139.244628','1029.796875',15,2002,600000,1,0,16,0,0,0,0),
('-','Nera','811.210693','-1616.062988','13.546875','362.816802','-74.889198','1001.507812',10,2003,45000,1,0,10,0,0,0,0),
('-','Nera','1481.110107','-1771.480468','18.795755','1131.729370','-348.983489','1055.947143',1,2004,590000,1,0,17,0,0,0,0),
('-','Nera','1169.940795','-1489.540283','22.755851','372.382904','-133.524307','1001.492187',5,2005,23000,1,0,11,0,0,0,0),
('-','Nera','1368.601562','-1279.839477','13.546875','314.820983','-141.431991','999.601562',7,2006,550000,1,0,6,0,0,0,0),
('-','Nera','1154.036865','-1440.184570','15.796875','-204.439987','-43.652496','1002.273437',3,2007,49000,1,0,13,0,0,0,0),
('-','Nera','2105.048095','-1806.391113','13.554677','372.382904','-133.524307','1001.492187',5,2008,140000,1,0,11,0,0,0,0),
('-','Nera','1143.654785','-1520.698486','15.796875','-2240.468505','137.060440','1035.414062',6,2009,2500000,1,0,8,0,0,0,0),
('-','Nera','1631.612670','-1172.299682','24.084280','833.237304','7.059800','1004.179687',3,2010,95000,1,0,15,0,0,0,0),
('-','Nera','1247.930908','-1560.578491','13.555603','-2158.918945','642.681274','1052.375000',1,2011,80000,1,0,14,0,0,0,0),
('-','Nera','2423.896240','-1742.749633','13.541769','-25.132598','-139.066986','1003.546875',16,2012,45000,1,0,2,0,0,0,0),
('-','Nera','1940.147094','-2116.011718','13.695302','-100.236297','-25.038099','1000.718811',3,2013,8000,1,0,9,0,0,0,0),
('-','Nera','2177.652832','-1770.602294','13.543416','2193.240478','-1139.244628','1029.796875',15,2014,50000,1,0,16,0,0,0,0),
('-','Nera','2244.821533','-1664.903686','15.476552','207.737991','-109.019996','1005.132812',15,2015,45000,1,0,3,0,0,0,0),
('-','Nera','2397.899414','-1898.294311','13.546875','365.050109','-11.548295','1001.851623',9,2016,23000,1,0,5,0,0,0,0),
('-','Nera','1112.623291','-1520.491821','15.796875','207.054992','-138.804992','1003.507812',3,2017,55000,1,0,3,0,0,0,0),
('-','Nera','2400.486816','-1981.470214','13.546875','316.524993','-167.706985','999.593750',6,2018,95000,1,0,6,0,0,0,0),
('-','Nera','333.824279','-1337.015136','14.507802','-204.439987','-43.652496','1002.273437',3,2019,25000,1,0,13,0,0,0,0),
('-','Nera','1463.677490','-1011.862121','26.843750','1131.729370','-348.983489','1055.947143',1,2020,50000,1,0,17,0,0,0,0),
('-','Nera','2229.655517','-1721.711425','13.565686','772.111999','-3.898648','1000.728820',5,2021,175000,1,0,1,0,0,0,0),
('-','Nera','1676.246337','-1636.566162','14.226552','207.737991','-109.019996','1005.132812',15,2022,80000,1,0,3,0,0,0,0),
('-','Nera','1099.619140','-1473.646484','15.796875','-26.691598','-55.714897','1003.546875',6,2023,70000,1,0,2,0,0,0,0),
('-','Nera','2232.429443','-1159.712402','25.890625','2193.240478','-1139.244628','1029.796875',15,2024,95000,1,0,16,0,0,0,0),
('-','Nera','1411.753662','-1700.049804','13.539484','2193.240478','-1139.244628','1029.796875',15,2025,85000,1,0,16,0,0,0,0),
('-','Nera','2313.027587','-1347.624389','24.022655','-2240.468505','137.060440','1035.414062',6,2026,35000,1,0,8,0,0,0,0),
('-','Nera','2420.468750','-1508.902343','24.000000','365.050109','-11.548295','1001.851623',9,2027,36000,1,0,5,0,0,0,0),
('-','Nera','499.904724','-1360.223266','16.327777','207.054992','-138.804992','1003.507812',3,2028,45000,1,0,3,0,0,0,0),
('-','Nera','2751.854492','-1438.201293','30.453125','-25.132598','-139.066986','1003.546875',16,2029,16000,1,0,2,0,0,0,0),
('-','Nera','1836.127685','-1682.081054','13.360918','493.390991','-22.722799','1000.679687',17,2030,33000,1,0,4,0,0,0,0),
('-','Nera','2152.067871','-1014.276672','62.796344','-26.691598','-55.714897','1003.546875',6,2031,39000,1,0,2,0,0,0,0),
('-','Nera','2112.816894','-1211.705566','23.963230','203.777999','-48.492397','1001.804687',1,2032,43000,1,0,3,0,0,0,0),
('-','Nera','1071.418212','-1221.133300','16.890625','207.054992','-138.804992','1003.507812',3,2033,64000,1,0,3,0,0,0,0),
('-','Nera','2353.082275','-1463.486083','24.000000','-100.236297','-25.038099','1000.718811',3,2034,6000,1,0,9,0,0,0,0),
('-','Nera','1457.364135','-1137.508911','23.969947','161.391006','-93.159156','1001.804687',18,2035,300000,1,0,3,0,0,0,0),
('-','Nera','2389.956298','-1548.559936','24.164062','-27.312299','-29.277599','1003.557250',4,2036,23000,1,0,2,0,0,0,0),
('-','Nera','1087.596191','-922.523315','43.390625','-100.236297','-25.038099','1000.718811',3,2037,11000,1,0,9,0,0,0,0),
('-','Nera','1144.960083','-1131.451538','23.828125','-100.236297','-25.038099','1000.718811',3,2038,14000,1,0,9,0,0,0,0),
('-','Nera','954.060546','-1336.583251','13.538757','-100.236297','-25.038099','1000.718811',3,2039,19000,1,0,9,0,0,0,0),
('-','Nera','2139.923828','-1176.901245','23.992187','-25.884498','-185.868988','1003.546875',17,2040,29000,1,0,2,0,0,0,0),
('-','Nera','928.329895','-1352.964843','13.343750','365.050109','-11.548295','1001.851623',9,2041,70000,1,0,5,0,0,0,0),
('-','Nera','1094.790527','-1272.055664','13.546875','-204.439987','-43.652496','1002.273437',3,2042,60000,1,0,13,0,0,0,0),
('-','Nera','278.752227','-1434.544555','13.944662','377.086608','-177.602096','1000.632812',17,2043,16000,1,0,12,0,0,0,0),
('-','Nera','1199.316040','-918.432495','43.120628','362.816802','-74.889198','1001.507812',10,2044,65000,1,0,10,0,0,0,0),
('-','Nera','511.805206','-1510.947631','14.566882','1131.729370','-348.983489','1055.947143',1,2045,36000,1,0,17,0,0,0,0),
('-','Nera','1024.276733','-983.715209','42.661308','2193.240478','-1139.244628','1029.796875',15,2046,21000,1,0,16,0,0,0,0),
('-','Nera','1133.431396','-1370.642211','13.984375','-30.946699','-89.609596','1003.546875',18,2047,67000,1,0,2,0,0,0,0),
('-','Nera','1234.838134','-1158.346923','23.540889','833.237304','7.059800','1004.179687',3,2048,93000,1,0,15,0,0,0,0),
('-','Nera','1104.886718','-1370.762573','13.984375','-25.132598','-139.066986','1003.546875',16,2049,65000,1,0,2,0,0,0,0),
('-','Nera','595.560424','-1250.529907','18.289648','1131.729370','-348.983489','1055.947143',1,2050,55000,1,0,17,0,0,0,0),
('-','Nera','816.231750','-1386.916381','13.608567','1204.809936','-11.586791','1000.921875',2,2051,12000,1,0,4,0,0,0,0),
('-','Nera','461.086914','-1500.813720','31.059431','226.293991','-7.431529','1002.210937',5,2052,40000,1,0,3,0,0,0,0),
('-','Nera','1081.364746','-1697.493164','13.546875','-2158.918945','642.681274','1052.375000',1,2053,27000,1,0,14,0,0,0,0),
('-','Nera','376.388336','-2054.375244','8.015625','372.382904','-133.524307','1001.492187',5,2054,6500,1,0,11,0,0,0,0),
('-','Nera','1111.929931','-1370.076538','13.984375','-100.236297','-25.038099','1000.718811',3,2055,16000,1,0,9,0,0,0,0),
('-','Nera','1119.288696','-1370.796875','13.984375','-2158.918945','642.681274','1052.375000',1,2056,54000,1,0,14,0,0,0,0),
('-','Nera','1667.318481','-1498.112182','13.546875','-2158.918945','642.681274','1052.375000',1,2057,48000,1,0,14,0,0,0,0),
('-','Nera','822.158752','-1757.599487','13.648427','773.579956','-77.096694','1000.655029',7,2058,56000,1,0,1,0,0,0,0),
('-','Nera','1352.678466','-1757.707153','13.507802','-27.312299','-29.277599','1003.557250',4,2059,39000,1,0,2,0,0,0,0),
('-','Nera','1111.478637','-1795.516601','16.593750','2193.240478','-1139.244628','1029.796875',15,2060,17000,1,0,16,0,0,0,0),
('-','Nera','2861.455322','-1405.809570','11.738203','-2158.918945','642.681274','1052.375000',1,2061,12000,1,0,14,0,0,0,0),
('-','Nera','1274.942871','-1662.706298','19.734375','1204.809936','-11.586791','1000.921875',2,2062,4500,1,0,4,0,0,0,0),
('-','Nera','1186.329101','-1361.100341','13.565052','-1543.403442','-446.275909','6.099997',0,2063,115000,1,0,7,0,0,0,0),
('-','Nera','1546.298095','-1269.064331','17.406250','2193.240478','-1139.244628','1029.796875',15,2064,18000,1,0,16,0,0,0,0),
('-','Nera','1631.955200','-1664.460327','13.425886','-1543.403442','-446.275909','6.099997',0,2065,100000,1,0,7,0,0,0,0),
('-','Nera','453.710266','-1478.189208','30.815128','204.332992','-166.694992','1000.523437',14,2066,25000,1,0,3,0,0,0,0),
('-','Nera','357.454833','-1765.506591','5.412032','-1543.403442','-446.275909','6.099997',0,2067,32000,1,0,7,0,0,0,0),
('-','Nera','418.743316','-1429.551879','32.462844','372.382904','-133.524307','1001.492187',5,2068,18000,1,0,11,0,0,0,0),
('-','Nera','2399.553222','-1390.508056','24.000000','-1543.403442','-446.275909','6.099997',0,2069,15000,1,0,7,0,0,0,0),
('-','Nera','2353.955566','-1512.077270','24.000000','774.213989','-48.924297','1000.585937',6,2070,34000,1,0,1,0,0,0,0),
('-','Nera','1593.091186','-2243.257080','13.550263','-1543.403442','-446.275909','6.099997',0,2071,8000,1,0,7,0,0,0,0),
('-','Nera','1455.015014','-1744.556274','13.546875','-1543.403442','-446.275909','6.099997',0,2072,70000,1,0,7,0,0,0,0),
('-','Nera','648.711364','-519.613647','16.553686','1131.729370','-348.983489','1055.947143',1,2073,175000,1,0,17,0,0,0,0),
('-','Nera','1078.009277','-1807.871215','13.635025','-1543.403442','-446.275909','6.099997',0,2074,40000,1,0,7,0,0,0,0),
('-','Nera','854.527832','-605.054321','18.421875','2193.240478','-1139.244628','1029.796875',15,2075,99000,1,0,16,0,0,0,0),
('-','Nera','1713.089355','-1151.651245','23.828125','-1543.403442','-446.275909','6.099997',0,2076,26000,1,0,7,0,0,0,0),
('-','Nera','681.640563','-473.907348','16.536296','365.050109','-11.548295','1001.851623',9,2077,4500000,1,0,5,0,0,0,0),
('-','Nera','1721.791259','-1942.026733','13.580360','-1543.403442','-446.275909','6.099997',0,2078,60000,1,0,7,0,0,0,0),
('-','Nera','672.626586','-627.890686','16.335937','-2158.918945','642.681274','1052.375000',1,2079,50000,1,0,14,0,0,0,0),
('-','Nera','660.707153','-1208.648803','18.406250','-1543.403442','-446.275909','6.099997',0,2080,24000,1,0,7,0,0,0,0),
('-','Nera','2380.357910','-1213.403076','27.422292','1985.357299','696.030822','2819.595947',3,2081,500000,1,0,18,0,0,0,0),
('-','Nera','1275.287963','-1029.714355','32.216026','-897.228271','-2586.273193','2146.554931',1,2082,300000,1,0,20,0,0,0,0),
('-','Nera','661.362915','-573.629089','16.335937','1010.205627','-934.538879','23.693300',3,2083,3000000,1,0,21,0,0,0,0),
('-','Nera','370.982543','-1637.825195','32.890625','-870.240295','-1214.998535','3248.995849',2,2084,500000,1,0,19,0,0,0,0),
('-','Nera','820.696289','-576.050354','16.536296','372.382904','-133.524307','1001.492187',5,2085,60000,1,0,11,0,0,0,0),
('-','Nera','1498.409301','-1582.734741','13.546875','-897.228271','-2586.273193','2146.554931',1,2086,400000,1,0,20,0,0,0,0),
('-','Nera','690.580810','-546.866638','16.335937','-27.312299','-29.277599','1003.557250',4,2087,45000,1,0,2,0,0,0,0),
('-','Nera','671.795166','-520.065979','16.335937','-897.228271','-2586.273193','2146.554931',1,2088,364000,1,0,20,0,0,0,0),
('-','Nera','701.599182','-519.430053','16.331737','207.054992','-138.804992','1003.507812',3,2089,48700,1,0,3,0,0,0,0),
('-','Nera','1928.659667','-1775.043579','13.546875','1957.223144','-1742.262207','-5.170495',3,2090,8000000,1,0,21,0,0,0,0),
('-','Nera','1852.968261','-1145.468017','23.839866','1985.357299','696.030822','2819.595947',3,2091,500000,1,0,18,0,0,0,0),
('-','Nera','2060.985595','-2541.581542','13.546875','1010.205627','-934.538879','23.693300',3,2092,1000000,1,0,21,0,0,0,0),
('-','Nera','1271.277099','-944.690979','42.415019','1985.357299','696.030822','2819.595947',3,2093,530000,1,0,18,0,0,0,0),
('-','Nera','-1676.215209','432.152526','7.179687','1957.223144','-1742.262207','-5.170495',3,2094,600000,1,0,21,0,0,0,0),
('-','Nera','1419.707031','-1623.944580','13.546875','-870.240295','-1214.998535','3248.995849',2,2095,600000,1,0,19,0,0,0,0),
('-','Nera','638.974792','1683.279663','7.187500','1010.205627','-934.538879','23.693300',3,2096,200000,1,0,21,0,0,0,0),
('-','Nera','801.013610','-573.937438','16.335937','1985.357299','696.030822','2819.595947',3,2097,554000,1,0,18,0,0,0,0),
('-','Nera','-2032.818847','161.450790','29.046106','1010.205627','-934.538879','23.693300',3,2098,300000,1,0,21,0,0,0,0),
('-','Nera','800.902832','-545.709777','16.335937','-870.240295','-1214.998535','3248.995849',2,2099,422000,1,0,19,0,0,0,0),
('-','Nera','1000.085815','-920.085205','42.328125','1957.223144','-1742.262207','-5.170495',3,2100,7000000,1,0,21,0,0,0,0),
('-','Nera','2512.019042','-1477.318847','24.159000','1010.205627','-934.538879','23.693300',3,2101,2500000,1,0,21,0,0,0,0),
('-','Nera','1383.254150','465.554870','20.191904','1010.205627','-934.538879','23.693300',3,2102,650000,1,0,21,0,0,0,0),
('-','Nera','-1623.556640','-2693.195556','48.742660','1010.205627','-934.538879','23.693300',3,2103,400000,1,0,21,0,0,0,0),
('-','Nera','-78.457878','-1169.878540','2.137552','1010.205627','-934.538879','23.693300',3,2104,600000,1,0,21,0,0,0,0),
('-','Nera','1038.166870','-1340.029174','13.736515','377.086608','-177.602096','1000.632812',17,2105,300000,1,0,12,0,0,0,0),
('-','Nera','842.595458','-2067.028564','3.756999','1010.205627','-934.538879','23.693300',3,2106,20000,1,0,21,0,0,0,0);
/*!40000 ALTER TABLE `Bizniai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `CarSaugykla`
--

DROP TABLE IF EXISTS `CarSaugykla`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `CarSaugykla` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Vardas` varbinary(50) NOT NULL,
  `Typ` int(11) NOT NULL DEFAULT -1,
  `X` float DEFAULT NULL,
  `Y` float DEFAULT NULL,
  `Z` float DEFAULT NULL,
  `Rot` float DEFAULT NULL,
  `Status` int(11) DEFAULT NULL,
  `Lock` int(11) DEFAULT NULL,
  `Paintjob` int(11) DEFAULT NULL,
  `Color1` int(11) DEFAULT NULL,
  `Color2` int(11) DEFAULT NULL,
  `mod1` int(11) DEFAULT NULL,
  `mod2` int(11) DEFAULT NULL,
  `mod3` int(11) DEFAULT NULL,
  `mod4` int(11) DEFAULT NULL,
  `mod5` int(11) DEFAULT NULL,
  `mod6` int(11) DEFAULT NULL,
  `mod7` int(11) DEFAULT NULL,
  `mod8` int(11) DEFAULT NULL,
  `mod9` int(11) DEFAULT NULL,
  `mod10` int(11) DEFAULT NULL,
  `mod11` int(11) DEFAULT NULL,
  `mod12` int(11) DEFAULT NULL,
  `mod13` int(11) DEFAULT NULL,
  `mod14` int(11) DEFAULT NULL,
  `mod15` int(11) DEFAULT NULL,
  `mod16` int(11) DEFAULT NULL,
  `mod17` int(11) DEFAULT NULL,
  `Gas` int(11) DEFAULT NULL,
  `Sirena` int(11) DEFAULT NULL,
  `Nr` varchar(50) DEFAULT NULL,
  `Energy` int(11) DEFAULT NULL,
  `vw` int(11) DEFAULT NULL,
  `Draud` int(11) DEFAULT NULL,
  `Rankinis` int(11) DEFAULT NULL,
  `VeHP` int(11) DEFAULT NULL,
  `Rida` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`),
  KEY `Vardas` (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `CarSaugykla`
--

LOCK TABLES `CarSaugykla` WRITE;
/*!40000 ALTER TABLE `CarSaugykla` DISABLE KEYS */;
/*!40000 ALTER TABLE `CarSaugykla` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Cars`
--

DROP TABLE IF EXISTS `Cars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Cars` (
  `Owner` text NOT NULL,
  `AH_Typ` int(11) DEFAULT -1,
  `AH_X` float DEFAULT NULL,
  `AH_Y` float DEFAULT NULL,
  `AH_Z` float NOT NULL,
  `AH_Rot` float NOT NULL,
  `AH_Status` int(11) DEFAULT 0,
  `AH_Lock` int(11) DEFAULT 0,
  `AH_Paintjob` int(11) DEFAULT NULL,
  `AH_Color1` int(11) DEFAULT NULL,
  `AH_Color2` int(11) DEFAULT NULL,
  `AH_mod1` int(11) DEFAULT NULL,
  `AH_mod2` int(11) DEFAULT NULL,
  `AH_mod3` int(11) DEFAULT NULL,
  `AH_mod4` int(11) DEFAULT NULL,
  `AH_mod5` int(11) DEFAULT NULL,
  `AH_mod6` int(11) DEFAULT NULL,
  `AH_mod7` int(11) DEFAULT NULL,
  `AH_mod8` int(11) DEFAULT NULL,
  `AH_mod9` int(11) DEFAULT NULL,
  `AH_mod10` int(11) DEFAULT NULL,
  `AH_mod11` int(11) DEFAULT NULL,
  `AH_mod12` int(11) DEFAULT NULL,
  `AH_mod13` int(11) DEFAULT NULL,
  `AH_mod14` int(11) DEFAULT NULL,
  `AH_mod15` int(11) DEFAULT NULL,
  `AH_mod16` int(11) DEFAULT NULL,
  `AH_mod17` int(11) DEFAULT NULL,
  `AH2_Typ` int(11) DEFAULT NULL,
  `AH2_X` float DEFAULT NULL,
  `AH2_Y` float NOT NULL,
  `AH2_Z` float NOT NULL,
  `AH2_Rot` float DEFAULT NULL,
  `AH2_Status` int(11) DEFAULT NULL,
  `AH2_Lock` int(11) DEFAULT NULL,
  `AH2_Paintjob` int(11) DEFAULT NULL,
  `AH2_Color1` int(11) DEFAULT NULL,
  `AH2_Color2` int(11) DEFAULT NULL,
  `AH2_mod1` int(11) DEFAULT NULL,
  `AH2_mod2` int(11) DEFAULT NULL,
  `AH2_mod3` int(11) DEFAULT NULL,
  `AH2_mod4` int(11) DEFAULT NULL,
  `AH2_mod5` int(11) DEFAULT NULL,
  `AH2_mod6` int(11) DEFAULT NULL,
  `AH2_mod7` int(11) DEFAULT NULL,
  `AH2_mod8` int(11) DEFAULT NULL,
  `AH2_mod9` int(11) DEFAULT NULL,
  `AH2_mod10` int(11) DEFAULT NULL,
  `AH2_mod11` int(11) DEFAULT NULL,
  `AH2_mod12` int(11) DEFAULT NULL,
  `AH2_mod13` int(11) DEFAULT NULL,
  `AH2_mod14` int(11) DEFAULT NULL,
  `AH2_mod15` int(11) DEFAULT NULL,
  `AH2_mod16` int(11) DEFAULT NULL,
  `AH2_mod17` int(11) DEFAULT NULL,
  `AH3_Typ` int(11) DEFAULT NULL,
  `AH3_X` float DEFAULT NULL,
  `AH3_Y` float NOT NULL,
  `AH3_Z` float DEFAULT NULL,
  `AH3_Rot` float DEFAULT NULL,
  `AH3_Status` int(11) DEFAULT NULL,
  `AH3_Lock` int(11) DEFAULT NULL,
  `AH3_Paintjob` int(11) DEFAULT NULL,
  `AH3_Color1` int(11) DEFAULT NULL,
  `AH3_Color2` int(11) DEFAULT NULL,
  `AH3_mod1` int(11) DEFAULT NULL,
  `AH3_mod2` int(11) DEFAULT NULL,
  `AH3_mod3` int(11) DEFAULT NULL,
  `AH3_mod4` int(11) DEFAULT NULL,
  `AH3_mod5` int(11) DEFAULT NULL,
  `AH3_mod6` int(11) DEFAULT NULL,
  `AH3_mod7` int(11) DEFAULT NULL,
  `AH3_mod8` int(11) DEFAULT NULL,
  `AH3_mod9` int(11) DEFAULT NULL,
  `AH3_mod10` int(11) DEFAULT NULL,
  `AH3_mod11` int(11) DEFAULT NULL,
  `AH3_mod12` int(11) DEFAULT NULL,
  `AH3_mod13` int(11) DEFAULT NULL,
  `AH3_mod14` int(11) DEFAULT NULL,
  `AH3_mod15` int(11) DEFAULT NULL,
  `AH3_mod16` int(11) DEFAULT NULL,
  `AH3_mod17` int(11) DEFAULT NULL,
  `Gas` int(11) DEFAULT 0,
  `Gas2` int(11) DEFAULT 0,
  `Gas3` int(11) DEFAULT 0,
  `Sirena` int(11) DEFAULT 0,
  `Sirena2` int(11) DEFAULT 0,
  `Sirena3` int(11) DEFAULT 0,
  `AH_Nr` varchar(100) DEFAULT '{FF0000}NERA',
  `AH2_Nr` varchar(100) DEFAULT '{FF0000}NERA',
  `AH3_Nr` varchar(100) DEFAULT '{FF0000}NERA',
  `Energy` int(11) DEFAULT 50,
  `Energy2` int(11) DEFAULT 50,
  `Energy3` int(11) DEFAULT 50,
  `vw1` int(11) DEFAULT 0,
  `vw2` int(11) DEFAULT 0,
  `vw3` int(11) DEFAULT 0,
  `AH_Draud` int(11) DEFAULT 0,
  `AH2_Draud` int(11) DEFAULT 0,
  `AH3_Draud` int(11) DEFAULT 0,
  `Rankinis1` int(11) DEFAULT 0,
  `Rankinis2` int(11) DEFAULT 0,
  `Rankinis3` int(11) DEFAULT 0,
  `VeHP` int(11) DEFAULT 1000,
  `VeHP2` int(11) DEFAULT 1000,
  `VeHP3` int(11) DEFAULT 1000,
  `Rida` int(11) DEFAULT 0,
  `Rida2` int(11) DEFAULT 0,
  `Rida3` int(11) DEFAULT 0,
  PRIMARY KEY (`Owner`(50))
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Cars`
--

LOCK TABLES `Cars` WRITE;
/*!40000 ALTER TABLE `Cars` DISABLE KEYS */;
/*!40000 ALTER TABLE `Cars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Checkpoints`
--

DROP TABLE IF EXISTS `Checkpoints`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Checkpoints` (
  `type` varchar(50) NOT NULL DEFAULT '',
  `id` varchar(50) NOT NULL DEFAULT '',
  `cpid` int(11) NOT NULL,
  `x` double DEFAULT NULL,
  `y` double DEFAULT NULL,
  `z` double DEFAULT NULL,
  PRIMARY KEY (`type`,`id`,`cpid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Checkpoints`
--

LOCK TABLES `Checkpoints` WRITE;
/*!40000 ALTER TABLE `Checkpoints` DISABLE KEYS */;
/*!40000 ALTER TABLE `Checkpoints` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Config`
--

DROP TABLE IF EXISTS `Config`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Config` (
  `variable` varchar(255) NOT NULL DEFAULT '',
  `value` varchar(255) DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Config`
--

LOCK TABLES `Config` WRITE;
/*!40000 ALTER TABLE `Config` DISABLE KEYS */;
INSERT INTO `Config` VALUES
('aak','0'),
('aawp','0'),
('adgl','0'),
('Admin','-'),
('afondas','0'),
('amp','0'),
('atveztan','0'),
('Admin','-'),
('Gaujos','-'),
('DJ','-'),
('Discord','-'),
('FURU_0','0'),
('FURU_1','0'),
('FURU_2','0'),
('FURU_3','0'),
('FURU_4','0'),
('FURU_5','0'),
('FURU_6','0'),
('FURU_7','0'),
('Restart','0'),
('Kreditai','-'),
('MAP darbai',''),
('Namai','-'),
('OrderID','0'),
('Permaban','-'),
('RadioUrl','-'),
('Atnaujinimai','-'),
('Session','0'),
('Skundai','-'),
('Konkursai','-'),
('kysiai','0'),
('Dyrikai','-'),
('Serveris','-'),
('Pasiulymai','-'),
('Klaidos/Bugai','-'),
('Banai','-'),
('Radija','-'),
('Aukcionai','-');
/*!40000 ALTER TABLE `Config` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Darbines`
--

DROP TABLE IF EXISTS `Darbines`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Darbines` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Vardas` varchar(255) DEFAULT NULL,
  `Job` int(11) DEFAULT NULL,
  `Cartype` int(11) DEFAULT NULL,
  `Status` int(11) DEFAULT NULL,
  `Health` float DEFAULT NULL,
  `Degalai` float DEFAULT NULL,
  `mod1` int(11) DEFAULT 0,
  `mod2` int(11) DEFAULT 0,
  `mod3` int(11) DEFAULT 0,
  `mod4` int(11) DEFAULT 0,
  `mod5` int(11) DEFAULT 0,
  `mod6` int(11) DEFAULT 0,
  `mod7` int(11) DEFAULT 0,
  `mod8` int(11) DEFAULT 0,
  `mod9` int(11) DEFAULT 0,
  `mod10` int(11) DEFAULT 0,
  `mod11` int(11) DEFAULT 0,
  `mod12` int(11) DEFAULT 0,
  `mod13` int(11) DEFAULT 0,
  `mod14` int(11) DEFAULT 0,
  `mod15` int(11) DEFAULT 0,
  `mod16` int(11) DEFAULT 0,
  `mod17` int(11) DEFAULT 0,
  `rida` float DEFAULT 0,
  `color1` int(11) DEFAULT -1,
  `color2` int(11) DEFAULT -1,
  `paintjob` int(11) DEFAULT -1,
  PRIMARY KEY (`id`),
  KEY `first` (`Vardas`,`Job`,`Cartype`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Darbines`
--

LOCK TABLES `Darbines` WRITE;
/*!40000 ALTER TABLE `Darbines` DISABLE KEYS */;
/*!40000 ALTER TABLE `Darbines` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Daugiabuciai`
--

DROP TABLE IF EXISTS `Daugiabuciai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Daugiabuciai` (
  `id` mediumint(9) NOT NULL DEFAULT 0,
  `dX` float NOT NULL,
  `dY` float NOT NULL,
  `dZ` float NOT NULL,
  `dLift` smallint(6) NOT NULL DEFAULT 1,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Daugiabuciai`
--

LOCK TABLES `Daugiabuciai` WRITE;
/*!40000 ALTER TABLE `Daugiabuciai` DISABLE KEYS */;
INSERT INTO `Daugiabuciai` VALUES
(0,1863.81,-1598.51,14.3062,0),
(1,952.546,-910.279,45.7656,0),
(2,327.307,-1514.52,36.0325,0);
/*!40000 ALTER TABLE `Daugiabuciai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Discord`
--

DROP TABLE IF EXISTS `Discord`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Discord` (
  `Vardas` varchar(50) NOT NULL DEFAULT '',
  `Discord` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Discord`
--

LOCK TABLES `Discord` WRITE;
/*!40000 ALTER TABLE `Discord` DISABLE KEYS */;
/*!40000 ALTER TABLE `Discord` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Dovanos`
--

DROP TABLE IF EXISTS `Dovanos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Dovanos` (
  `Vardas` varchar(255) DEFAULT NULL,
  `IP` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Dovanos`
--

LOCK TABLES `Dovanos` WRITE;
/*!40000 ALTER TABLE `Dovanos` DISABLE KEYS */;
/*!40000 ALTER TABLE `Dovanos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Easter17`
--

DROP TABLE IF EXISTS `Easter17`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Easter17` (
  `Name` varchar(255) DEFAULT NULL,
  `Ip` varchar(255) DEFAULT NULL,
  `Egg` int(11) DEFAULT NULL,
  `Hashas` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Easter17`
--

LOCK TABLES `Easter17` WRITE;
/*!40000 ALTER TABLE `Easter17` DISABLE KEYS */;
/*!40000 ALTER TABLE `Easter17` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Easter18`
--

DROP TABLE IF EXISTS `Easter18`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Easter18` (
  `Vardas` varchar(25) NOT NULL,
  `IP` varchar(255) DEFAULT NULL,
  `k1` int(11) DEFAULT 0,
  `k2` int(11) DEFAULT 0,
  `k3` int(11) DEFAULT 0,
  `k4` int(11) DEFAULT 0,
  `k5` int(11) DEFAULT 0,
  `prizas` int(11) DEFAULT 0,
  PRIMARY KEY (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Easter18`
--

LOCK TABLES `Easter18` WRITE;
/*!40000 ALTER TABLE `Easter18` DISABLE KEYS */;
/*!40000 ALTER TABLE `Easter18` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Easter19`
--

DROP TABLE IF EXISTS `Easter19`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Easter19` (
  `Vardas` varchar(50) NOT NULL,
  `IP` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Easter19`
--

LOCK TABLES `Easter19` WRITE;
/*!40000 ALTER TABLE `Easter19` DISABLE KEYS */;
/*!40000 ALTER TABLE `Easter19` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Emails`
--

DROP TABLE IF EXISTS `Emails`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Emails` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Sender` varchar(100) NOT NULL,
  `Reciever` varchar(100) NOT NULL,
  `Date` varchar(24) NOT NULL,
  `Time` varchar(24) NOT NULL,
  `MK` int(11) NOT NULL,
  `New` smallint(6) NOT NULL,
  `Subject` varchar(100) NOT NULL,
  `Text` longtext NOT NULL,
  `DateTime` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Emails`
--

LOCK TABLES `Emails` WRITE;
/*!40000 ALTER TABLE `Emails` DISABLE KEYS */;
/*!40000 ALTER TABLE `Emails` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Gangs`
--

DROP TABLE IF EXISTS `Gangs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Gangs` (
  `ID` int(11) NOT NULL,
  `Leader` varchar(50) NOT NULL DEFAULT 'Nera',
  `Substitute` varchar(50) DEFAULT 'Nera',
  `Funds` int(11) DEFAULT 0,
  `Limit` int(11) NOT NULL DEFAULT 1000,
  `SandelioLimitai` varchar(100) NOT NULL DEFAULT '100|100|100',
  `SaugyklosLimitai` varchar(200) NOT NULL DEFAULT '100|100|100|100|100|100|100|100|100|100',
  `Saugykla` varchar(200) NOT NULL DEFAULT '0|0|0|0|0|0|0|0|0|0',
  `Delay` int(11) NOT NULL DEFAULT 0,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Gangs`
--

LOCK TABLES `Gangs` WRITE;
/*!40000 ALTER TABLE `Gangs` DISABLE KEYS */;
INSERT INTO `Gangs` VALUES
(0,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4),
(1,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4),
(2,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4),
(3,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4),
(4,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4),
(5,'Nera','Nera',0,0,'10|10|10','1|1|1|1|1|1|1|1|1|1','0|0|0|0|0|0|0|0|0|0',4);
/*!40000 ALTER TABLE `Gangs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `HBans`
--

DROP TABLE IF EXISTS `HBans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `HBans` (
  `Vardas` varchar(255) DEFAULT NULL,
  `Hash` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `HBans`
--

LOCK TABLES `HBans` WRITE;
/*!40000 ALTER TABLE `HBans` DISABLE KEYS */;
/*!40000 ALTER TABLE `HBans` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `HouseSale`
--

DROP TABLE IF EXISTS `HouseSale`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `HouseSale` (
  `houseid` int(11) NOT NULL DEFAULT 0,
  `posx` float DEFAULT NULL,
  `posy` float DEFAULT NULL,
  `posz` float DEFAULT NULL,
  `rotz` float DEFAULT NULL,
  `price` int(11) DEFAULT NULL,
  PRIMARY KEY (`houseid`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `HouseSale`
--

LOCK TABLES `HouseSale` WRITE;
/*!40000 ALTER TABLE `HouseSale` DISABLE KEYS */;
/*!40000 ALTER TABLE `HouseSale` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Irengimas`
--

DROP TABLE IF EXISTS `Irengimas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Irengimas` (
  `houseid` int(11) NOT NULL,
  `nta` varchar(255) DEFAULT NULL,
  `data` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Irengimas`
--

LOCK TABLES `Irengimas` WRITE;
/*!40000 ALTER TABLE `Irengimas` DISABLE KEYS */;
/*!40000 ALTER TABLE `Irengimas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Ispejimai`
--

DROP TABLE IF EXISTS `Ispejimai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Ispejimai` (
  `entity` varchar(50) NOT NULL,
  `id` varchar(50) NOT NULL,
  `time` datetime NOT NULL,
  `count` tinyint(4) NOT NULL,
  `by` varchar(50) DEFAULT NULL,
  `reason` varchar(256) DEFAULT NULL,
  PRIMARY KEY (`entity`,`id`,`time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ispejimai`
--

LOCK TABLES `Ispejimai` WRITE;
/*!40000 ALTER TABLE `Ispejimai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Ispejimai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Kaledos`
--

DROP TABLE IF EXISTS `Kaledos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Kaledos` (
  `Vardas` varchar(50) NOT NULL,
  `Ip` varchar(50) DEFAULT NULL,
  `gift0` smallint(6) NOT NULL DEFAULT 0,
  `gift1` smallint(6) NOT NULL DEFAULT 0,
  `gift2` smallint(6) NOT NULL DEFAULT 0,
  `gift3` smallint(6) NOT NULL DEFAULT 0,
  `gift4` smallint(6) NOT NULL DEFAULT 0,
  `gift5` smallint(6) NOT NULL DEFAULT 0,
  `gift6` smallint(6) NOT NULL DEFAULT 0,
  `Registered` datetime NOT NULL,
  `Hashas` varchar(128) NOT NULL DEFAULT '',
  PRIMARY KEY (`Vardas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Kaledos`
--

LOCK TABLES `Kaledos` WRITE;
/*!40000 ALTER TABLE `Kaledos` DISABLE KEYS */;
/*!40000 ALTER TABLE `Kaledos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Kaledos11`
--

DROP TABLE IF EXISTS `Kaledos11`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Kaledos11` (
  `Vardas` varchar(30) NOT NULL DEFAULT '',
  `Cps` int(11) DEFAULT 0,
  `Ip` varchar(255) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Kaledos11`
--

LOCK TABLES `Kaledos11` WRITE;
/*!40000 ALTER TABLE `Kaledos11` DISABLE KEYS */;
/*!40000 ALTER TABLE `Kaledos11` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Keliones`
--

DROP TABLE IF EXISTS `Keliones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Keliones` (
  `id` varchar(50) NOT NULL DEFAULT '',
  `name` varchar(50) DEFAULT NULL,
  `kurejas` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Keliones`
--

LOCK TABLES `Keliones` WRITE;
/*!40000 ALTER TABLE `Keliones` DISABLE KEYS */;
/*!40000 ALTER TABLE `Keliones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Keybinds`
--

DROP TABLE IF EXISTS `Keybinds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Keybinds` (
  `Name` varchar(50) NOT NULL DEFAULT '',
  `ID` int(11) NOT NULL DEFAULT 0,
  `Value` varchar(500) DEFAULT NULL,
  PRIMARY KEY (`Name`,`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Keybinds`
--

LOCK TABLES `Keybinds` WRITE;
/*!40000 ALTER TABLE `Keybinds` DISABLE KEYS */;
/*!40000 ALTER TABLE `Keybinds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Kiemas`
--

DROP TABLE IF EXISTS `Kiemas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Kiemas` (
  `houseid` int(11) NOT NULL,
  `kiemox` float DEFAULT NULL,
  `kiemoy` float DEFAULT NULL,
  `kiemoz` float DEFAULT NULL,
  PRIMARY KEY (`houseid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Kiemas`
--

LOCK TABLES `Kiemas` WRITE;
/*!40000 ALTER TABLE `Kiemas` DISABLE KEYS */;
INSERT INTO `Kiemas` VALUES
(1,2247.61,-1627.71,15.7503),
(2,2258.31,-1633.63,15.6216),
(3,2284.32,-1626.45,15.8898),
(4,2307.7,-1689.57,13.5685),
(5,2368.45,-1637.48,13.495),
(6,2366.27,-1690.13,14.1682),
(7,2390.99,-1633.66,13.9051),
(8,2384.96,-1686.28,14.6958),
(9,2415.94,-1632,14.0119),
(10,2403.24,-1680.68,13.6149),
(11,2451.01,-1630.71,13.3956),
(12,2469.98,-1698.58,13.5161),
(13,2467.31,-1633.97,13.7801),
(14,2491.8,-1638.03,13.7324),
(15,2524.39,-1702.58,14.046),
(16,2497.89,-1631.62,13.4086),
(18,2525.61,-1641.12,14.3557),
(19,2535.24,-1658.16,15.2699),
(20,2317.59,-1686.29,14.3756),
(21,2381.22,-1702.06,13.6504),
(22,2404.51,-1700.23,14.1351),
(23,2326.47,-1706.12,13.5469),
(24,2308.11,-1703.69,14.3281),
(25,2151.55,-1717.98,15.0859),
(26,2144.77,-1688.64,15.0859),
(27,2163.66,-1660.85,15.0859),
(28,2141.48,-1652.87,15.0859),
(29,2056.39,-1732.19,13.5469),
(30,2058.06,-1697.94,13.8389),
(31,2055.39,-1717.33,13.5547),
(32,2060.96,-1650.83,13.5469),
(33,2057.04,-1643.85,13.5469),
(34,2056.88,-1629.62,13.5469),
(35,2028.43,-1629.65,13.5469),
(36,2024.09,-1656.14,13.5547),
(37,2027.13,-1640.93,13.5547),
(38,2027.51,-1699.11,13.5469),
(39,2021.96,-1722.6,13.5547),
(40,2024.92,-1728.46,13.5469),
(41,1969.31,-1714.71,17.0603),
(43,1969.92,-1678.5,17.0868),
(52,1857.02,-1904.92,15.033),
(53,1875.5,-1902.68,15.0314),
(54,1895.32,-1905.06,15.0309),
(55,1916.47,-1902.47,15.0281),
(56,1947.73,-1914.32,15.0312),
(57,1931.62,-1906.48,15.03),
(58,1906,-2034.67,13.5469),
(61,1901.33,-2019.78,13.5469),
(63,1898.5,-1997.72,13.5469),
(64,1866.37,-1997.92,13.5469),
(65,1864.98,-2021.47,13.5469),
(66,1846.42,-2021.1,13.5469),
(67,1846.24,-1992.04,13.5469),
(68,1867.61,-1979.4,13.5469),
(69,1814.2,-1994.47,13.5544),
(72,1857,-2034.94,13.5469),
(74,1919.76,-2021.59,13.5469),
(75,1804.46,-2136.4,13.5469),
(77,1781.24,-2089.65,13.63),
(78,1761.56,-2136.93,13.63),
(83,1715.26,-2137.24,13.63),
(87,1667.19,-2095.11,13.6456),
(88,1684.38,-2086.59,13.5469),
(89,2159.88,-1488.98,26.6524),
(90,2155.65,-1439.33,25.5391),
(91,2162.59,-1445.5,25.5391),
(92,2161.64,-1418.21,25.5391),
(93,2161.94,-1400.06,25.5467),
(94,2185.39,-1404.72,25.5391),
(95,2178.88,-1423.39,25.5391),
(96,2183.13,-1443.33,25.5391),
(97,2185.15,-1450.28,25.5391),
(98,2179.7,-1471.17,25.5391),
(99,2179.94,-1488.49,25.5391),
(100,2232.16,-1458.88,24.0203),
(101,2247.35,-1458.83,24.0248),
(102,2263.64,-1458.7,24.0083),
(103,2230.72,-1407.62,24),
(104,2243.83,-1407.82,24),
(105,2256.88,-1407.82,24),
(106,2202.36,-1353.3,25.6383),
(107,2184.43,-1353.12,25.5983),
(108,2149.32,-1330.46,25.5456),
(109,2146.79,-1355.75,25.5391),
(110,2122.63,-1331.88,26.6504),
(111,2129.34,-1351.25,25.5391),
(112,2101.76,-1332.26,25.5391),
(113,2086.88,-1268.69,25.4986),
(114,2149.54,-1274.67,23.9907),
(115,2110.66,-1268.15,25.4902),
(116,2131.36,-1269.44,25.4954),
(117,2131.32,-1247.7,24.4219),
(118,2154.69,-1254.19,24.9929),
(119,2112.11,-1254.78,25.4881),
(120,2090.94,-1245.57,25.488),
(121,2102.68,-1188.45,26.7144),
(122,2101.9,-1168.97,25.5938),
(123,2192.25,-1249.61,23.9419),
(124,2210.41,-1250.62,23.8715),
(125,2234,-1250.76,25.4066),
(126,2105.02,-1142.78,25.586),
(127,2104.93,-1126.69,27.4228),
(128,2034.34,-1112.44,25.9608),
(129,2020.36,-1110.6,26.2031),
(130,1997.56,-1104.73,26.7812),
(131,2250.98,-1249.31,25.4449),
(132,2249.12,-1269.66,25.3594),
(133,2229.42,-1269.69,25.3672),
(134,2207.46,-1270.42,24.5607),
(135,2187.46,-1266.21,24.6256),
(136,1959.03,-1104.43,27.564),
(137,1936.97,-1104.82,26.4531),
(138,1925.46,-1104.18,26.8005),
(139,1908.31,-1103.14,25.6719),
(140,1889.8,-1102.72,26.0089),
(141,2031.26,-1044.65,25.2864),
(142,2044.27,-1051.12,25.5814),
(143,2059.08,-1057.53,26.5094),
(145,2091.7,-1068.29,28.0833),
(164,2390.7,-1123.8,31.0659),
(169,2591.46,-1072.81,69.8322),
(170,2581.42,-1103.61,67.2257),
(171,2424.65,-1126.67,34.424),
(172,2506.7,-1115.31,56.5926),
(173,2471.14,-1115.69,43.914),
(174,2457.83,-1112.88,43.593),
(175,2439.49,-1116.17,42.556),
(176,2409.94,-1119.64,40.6517),
(177,2375.76,-1124.09,29.0588),
(179,2493.65,-1129.45,39.2296),
(180,2521.11,-1132.43,41.1728),
(181,2613.4,-1065.8,69.9656),
(182,2612.85,-1083.07,69.9656),
(183,2403.29,-1281.87,25.1291),
(184,2611.11,-1097.39,69.6047),
(185,2610.84,-1111.05,67.6763),
(186,2402.68,-1330.35,25.3923),
(187,2402.11,-1343.98,25.3549),
(188,2398.3,-1368.53,24.4914),
(189,2421.22,-1276.99,24.7567),
(190,2420.02,-1287.26,25.3479),
(191,2418.98,-1302.02,25.4069),
(192,2483.95,-1280.34,30.4714),
(193,2482.75,-1293.21,30.2332),
(194,2419.23,-1319.19,25.5734),
(195,2424.79,-1336.88,24.325),
(196,2474.7,-1223,32.3349),
(197,2424.84,-1355.35,24.325),
(198,2493.96,-1224.25,37.9054),
(199,2530.98,-1228.61,43.7219),
(200,2549.95,-1223.2,49.7631),
(201,2549.98,-1209.29,54.5424),
(202,2520.71,-1209.66,50.2936),
(203,2465.66,-1215.18,36.8117),
(213,2108.91,-1018.62,62.5391),
(222,2013.8,-966.919,42.4609),
(231,1419.36,-916.087,36.0469),
(232,1449.02,-922.02,37.5064),
(234,1481.76,-908.936,55.5944),
(236,1562.09,-856.789,61.3654),
(237,1547.7,-803.174,72.2175),
(238,1534.69,-761.618,79.9453),
(239,1496.94,-666.739,95.6013),
(240,1454.45,-609.362,95.7188),
(241,1258.98,-785.528,92.0302),
(242,1345.84,-653.447,109.135),
(243,1134.48,-747.574,97.1622),
(245,1048.29,-811.157,102.583),
(247,1006.36,-841.026,95.4973),
(249,919.774,-863.059,93.4565),
(252,824.142,-849.357,69.9216),
(253,829.934,-903.179,68.7734),
(255,785.96,-760.014,73.5607),
(257,895.333,-792.398,101.422),
(258,878.215,-725.725,106.391),
(259,888.265,-656.45,116.891),
(260,951.321,-718.697,122.211),
(261,991.717,-695.346,121.938),
(262,1047,-653.03,120.111),
(263,1094.86,-661.439,113.648),
(266,681.576,-1022.06,55.7596),
(267,711.426,-1080.09,49.4219),
(268,656.366,-1061.7,52.5799),
(270,666.075,-1124.04,44.2358),
(272,567.612,-1214.97,44.8603),
(273,569.006,-1164.24,54.4297),
(275,432.674,-1138.28,73.7169),
(276,485.09,-1114.55,82.3594),
(277,565.16,-1097.9,69.9513),
(279,398.131,-1291.97,50.0485),
(282,304.981,-1347.41,53.4438),
(283,239.017,-1378.77,53.3259),
(284,167.896,-1308.33,70.3513),
(285,211.775,-1238.96,78.3487),
(286,265.62,-1287.85,74.6325),
(287,239.439,-1202.78,76.1403),
(288,315.591,-1139.05,81.5934),
(289,364.445,-1191.41,77.222),
(290,223.876,-1413.97,51.8386),
(292,143.007,-1480.79,25.2109),
(295,206.235,-1767.85,9.50781),
(300,920.686,-1817.41,13.3067),
(301,750.105,-1567.02,13.5469),
(302,761.169,-1508.13,13.9219),
(304,739.035,-1428.99,13.7178),
(307,852.348,-1436.25,15.0437),
(314,777.054,-1603.51,13.4311),
(315,777.739,-1657.85,4.73438),
(316,779.307,-1694.52,4.71209),
(317,779.315,-1744.04,12.5),
(318,683.879,-1708.07,3.12347),
(319,663.257,-1711.89,13.8744),
(320,683.853,-1686.51,4.0436),
(321,684.098,-1643.33,3.33362),
(322,666.887,-1654.94,14.143),
(323,666.964,-1639.94,15.5943),
(324,687.621,-1629.56,3.37856),
(325,690.295,-1612.46,14.107),
(328,2697.48,-2033.23,13.4242),
(329,2671.26,-2035.08,14.1682),
(330,2698.16,-1975.58,14.2229),
(331,2662.21,-2021.74,13.75),
(332,2671.97,-1979.04,13.5469),
(333,2626.72,-2018.32,13.5469),
(334,2629.07,-1985.04,13.5469),
(335,2650.81,-1977.04,13.9988),
(427,759.3,-591.862,18.0133),
(428,742.612,-495.802,18.0129),
(429,745.851,-570.459,18.0133),
(431,767.317,-489.962,18.0133),
(433,767.562,-570.505,18.0133),
(434,796.096,-492.55,18.0133),
(435,817.312,-495.583,18.0129),
(436,1018.27,-1939.21,12.5834),
(437,1015.39,-1952.89,12.6186),
(438,1015.26,-1968.21,12.7786),
(439,1012.48,-1982.12,12.071),
(440,1010.32,-1995.75,11.1564),
(441,1009.95,-2011.33,11.8065),
(442,1007.28,-2025.06,11.5894),
(443,2435.85,-2035.63,13.9025),
(444,2465.77,-1985.16,13.5469),
(445,2463.45,-2035.55,14.1242),
(446,2483.02,-1983.84,13.5469),
(447,2488.69,-2033.93,13.9988),
(448,2510.21,-1983.58,13.9025),
(449,2505.81,-2035.82,14.2101),
(450,2531.98,-1991.27,13.554),
(451,2531.85,-2030.81,14.0744),
(464,1977.78,-1325.06,24),
(465,1995.2,-1277.23,23.989),
(466,2002.78,-1324.99,23.989),
(467,2027.87,-1324.72,23.989),
(468,2020.39,-1277.23,23.989),
(469,2045.14,-1277.23,23.989),
(470,2052.71,-1324.74,23.989),
(471,1970.17,-1277.22,24),
(472,-679.54,934.47,16.7917),
(473,-696.91,934.82,16.8293);
/*!40000 ALTER TABLE `Kiemas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Kreditai`
--

DROP TABLE IF EXISTS `Kreditai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Kreditai` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL,
  `Action` varchar(50) NOT NULL COMMENT 'buy,spend,sell',
  `Amount` int(11) NOT NULL DEFAULT 0,
  `Price` int(11) DEFAULT NULL,
  `Time` datetime NOT NULL DEFAULT current_timestamp(),
  `Source` varchar(50) DEFAULT NULL COMMENT 'sms,bank,paypal,etc',
  `Service` varchar(50) DEFAULT NULL COMMENT 'unban,vip,etc',
  `Buyer` varchar(50) DEFAULT NULL,
  `Details` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `Action` (`Action`),
  KEY `Time` (`Time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Kreditai`
--

LOCK TABLES `Kreditai` WRITE;
/*!40000 ALTER TABLE `Kreditai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Kreditai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Login`
--

DROP TABLE IF EXISTS `Login`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Login` (
  `Id` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL,
  `Ip` varchar(50) NOT NULL,
  `Login` datetime NOT NULL,
  `Logout` datetime DEFAULT NULL,
  `Time` int(11) DEFAULT NULL,
  `Hash` varchar(50) DEFAULT NULL,
  `Authkey` varchar(50) DEFAULT NULL,
  `Uniqueid` int(11) DEFAULT NULL,
  `Registered` int(11) DEFAULT NULL,
  PRIMARY KEY (`Id`),
  KEY `Name` (`Name`),
  KEY `Ip` (`Ip`),
  KEY `Login` (`Login`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Login`
--

LOCK TABLES `Login` WRITE;
/*!40000 ALTER TABLE `Login` DISABLE KEYS */;
/*!40000 ALTER TABLE `Login` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Logs`
--

DROP TABLE IF EXISTS `Logs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Logs` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Zaidejas` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `Veiksmas` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `Variable` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `Data` datetime DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Logs`
--

LOCK TABLES `Logs` WRITE;
/*!40000 ALTER TABLE `Logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `Logs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Mainai`
--

DROP TABLE IF EXISTS `Mainai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Mainai` (
  `Vardas1` varchar(30) DEFAULT NULL,
  `Vardas2` varchar(30) DEFAULT NULL,
  `Siulymas1` varchar(500) DEFAULT NULL,
  `Siulymas2` varchar(500) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Mainai`
--

LOCK TABLES `Mainai` WRITE;
/*!40000 ALTER TABLE `Mainai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Mainai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Metrics`
--

DROP TABLE IF EXISTS `Metrics`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Metrics` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `metric` varchar(50) NOT NULL DEFAULT 'None',
  `value` float NOT NULL DEFAULT 0,
  `time` datetime DEFAULT NULL,
  PRIMARY KEY (`id`) USING HASH,
  KEY `metric` (`metric`,`time`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Metrics`
--

LOCK TABLES `Metrics` WRITE;
/*!40000 ALTER TABLE `Metrics` DISABLE KEYS */;
/*!40000 ALTER TABLE `Metrics` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Namai`
--

DROP TABLE IF EXISTS `Namai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Namai` (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Name` varchar(30) DEFAULT '121',
  `Renter` varchar(30) DEFAULT 'ForRent',
  `Rentable` int(11) DEFAULT 0,
  `Rentcost` int(11) DEFAULT 0,
  `Cost` int(11) DEFAULT 0,
  `Locked` int(11) DEFAULT 0,
  `RentPay` int(11) DEFAULT 0,
  `RentGet` int(11) DEFAULT 0,
  `Vidus` int(11) DEFAULT 0,
  `X` varchar(30) DEFAULT '0',
  `Y` varchar(30) DEFAULT '0',
  `Z` varchar(30) DEFAULT '0',
  `Zole` int(11) DEFAULT 0,
  `Pinigai` int(11) DEFAULT 0,
  `Kulkos0` int(11) DEFAULT 0,
  `Ginklas0` int(11) DEFAULT 0,
  `Kulkos1` int(11) DEFAULT 0,
  `Ginklas1` int(11) DEFAULT 0,
  `Kulkos2` int(11) DEFAULT 0,
  `Ginklas2` int(11) DEFAULT 0,
  `Kulkos3` int(11) DEFAULT 0,
  `Ginklas3` int(11) DEFAULT 0,
  `Kulkos4` int(11) DEFAULT 0,
  `Ginklas4` int(11) DEFAULT 0,
  `Kulkos5` int(11) DEFAULT 0,
  `Ginklas5` int(11) DEFAULT 0,
  `Kulkos6` int(11) DEFAULT 0,
  `Ginklas6` int(11) DEFAULT 0,
  `Kulkos7` int(11) DEFAULT 0,
  `Ginklas7` int(11) DEFAULT 0,
  `Kulkos8` int(11) DEFAULT 0,
  `Ginklas8` int(11) DEFAULT 0,
  `Kulkos9` int(11) DEFAULT 0,
  `Ginklas9` int(11) DEFAULT 0,
  `Kulkos10` int(11) DEFAULT 0,
  `Ginklas10` int(11) DEFAULT 0,
  `Kulkos11` int(11) DEFAULT 0,
  `Ginklas11` int(11) DEFAULT 0,
  `Krumeliai` int(11) DEFAULT 0,
  `Dregme` int(11) DEFAULT 0,
  `Bukle` int(11) DEFAULT 0,
  `Amzius` int(11) DEFAULT 0,
  `Nark` int(11) DEFAULT 0,
  `Maistas` int(11) DEFAULT 0,
  `LSD` int(11) DEFAULT 0,
  `Ratai` int(11) DEFAULT 0,
  `Seklos` int(11) DEFAULT 0,
  `Radio` int(11) DEFAULT 0,
  `Garazas` int(11) DEFAULT 0,
  `GarazoX` varchar(30) DEFAULT '0',
  `GarazoY` varchar(30) DEFAULT '0',
  `GarazoZ` varchar(30) DEFAULT '0',
  `GarazoA` varchar(30) DEFAULT '0',
  `Tobulina` int(11) DEFAULT 0,
  `Daugiabutis` int(11) DEFAULT 0,
  `bMokesciai` int(11) DEFAULT 14,
  `polyId` int(11) DEFAULT -1,
  PRIMARY KEY (`ID`),
  KEY `Name` (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Namai`
--

LOCK TABLES `Namai` WRITE;
/*!40000 ALTER TABLE `Namai` DISABLE KEYS */;
INSERT INTO `Namai` VALUES
(1,'Nera','ForRent',0,0,148672,0,0,0,1,'2244.374511','-1638.043579','15.907407',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(2,'Nera','ForRent',0,0,108564,1,0,0,1,'2257.134765','-1645.252319','15.512241',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(3,'Nera','ForRent',0,0,115829,1,0,0,1,'2282.424804','-1641.989013','15.627917',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(4,'Nera','ForRent',0,0,112892,0,0,0,1,'2306.807861','-1678.813842','14.001157',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(5,'Nera','ForRent',0,0,121549,1,0,0,1,'2362.834472','-1644.187011','13.533133',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(6,'Nera','ForRent',0,0,103456,0,0,0,1,'2368.330810','-1674.977905','14.168166',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(7,'Nera','ForRent',0,0,104947,0,0,0,1,'2393.146484','-1646.608520','13.643225',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(8,'Nera','ForRent',0,0,123578,1,0,0,1,'2384.698242','-1674.902709','14.721035',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(9,'Nera','ForRent',0,0,108526,0,0,0,1,'2413.789062','-1647.167480','14.011916',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(10,'Nera','ForRent',0,0,105879,0,0,0,1,'2408.943359','-1674.158935','13.605044',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(11,'Nera','ForRent',0,0,115478,0,0,0,1,'2452.020019','-1641.858276','13.735734',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(12,'Nera','ForRent',0,0,279621,0,0,0,1,'2459.474365','-1690.209472','13.544446',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(13,'Nera','ForRent',0,0,99589,1,0,0,1,'2469.307373','-1646.771362','13.780097',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(14,'Nera','ForRent',0,0,267300,0,0,0,1,'2486.485351','-1645.234008','14.077178',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(15,'Nera','ForRent',0,0,71000,0,0,0,1,'2514.099365','-1691.397705','14.046038',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(16,'Nera','ForRent',0,0,74343,1,0,0,1,'2498.475341','-1642.375854','14.113082',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(17,'Nera','ForRent',0,0,264843,1,0,0,1,'2522.928222','-1679.223510','15.496999',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2516.464843','-1672.928710','13.722790','81.817108',0,0,14,-1),
(18,'Nera','ForRent',0,0,108600,1,0,0,1,'2513.287841','-1650.621948','14.355666',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(19,'Nera','ForRent',0,0,116826,0,0,0,1,'2524.428222','-1658.454345','15.493547',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(20,'Nera','ForRent',0,0,203456,1,0,0,1,'2328.186523','-1682.025146','14.871517',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2328.010742','-1677.470825','14.206235','270.285400',0,0,14,-1),
(21,'Nera','ForRent',0,0,223698,1,0,0,1,'2385.462890','-1712.277587','14.242187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2390.085449','-1713.549194','13.397480','180.725189',0,0,14,-1),
(22,'Nera','ForRent',0,0,108462,0,0,0,1,'2402.591308','-1715.837768','14.042688',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(23,'Nera','ForRent',0,0,129853,1,0,0,1,'2326.790527','-1717.119873','13.907408',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(24,'Nera','ForRent',0,0,141596,1,0,0,1,'2308.894775','-1715.378662','14.649595',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(25,'Nera','ForRent',0,0,114785,0,0,0,1,'2157.068847','-1709.206542','15.085937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(26,'Nera','ForRent',0,0,117482,0,0,0,1,'2155.367431','-1699.359497','15.085937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(27,'Nera','ForRent',0,0,125482,1,0,0,1,'2165.906494','-1671.284301','15.073219',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(28,'Nera','ForRent',0,0,111345,0,0,0,1,'2143.915283','-1663.309814','15.085937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(29,'Nera','ForRent',0,0,156489,1,0,0,1,'2067.226806','-1731.830688','13.876157',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(30,'Nera','ForRent',0,0,172594,1,0,0,1,'2065.100097','-1703.448242','14.148437',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(31,'Nera','ForRent',0,0,121200,0,0,0,1,'2066.421386','-1716.848632','13.805846',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(32,'Nera','ForRent',0,0,114743,1,0,0,1,'2066.760986','-1656.570068','14.132812',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(33,'Nera','ForRent',0,0,133843,0,0,0,1,'2067.803222','-1643.690917','13.805846',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(34,'Nera','ForRent',0,0,206851,1,0,0,1,'2068.331787','-1629.279785','13.876157',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2057.731445','-1636.552734','13.328703','268.970062',0,0,14,-1),
(35,'Nera','ForRent',0,0,131100,0,0,0,1,'2017.739746','-1630.056274','13.712096',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(36,'Nera','ForRent',0,0,73000,0,0,0,1,'2013.198730','-1656.343139','13.805846',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(37,'Nera','ForRent',0,0,209875,1,0,0,1,'2016.508422','-1641.613647','14.112878',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2026.108154','-1648.632202','13.336423','91.831993',0,0,14,-1),
(38,'Nera','ForRent',0,0,221854,0,0,0,1,'2018.088500','-1703.371948','14.234375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2014.084228','-1707.219848','13.334737','91.835502',0,0,14,-1),
(39,'Nera','ForRent',0,0,75132,1,0,0,1,'2015.876464','-1717.075927','14.013248',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(40,'Nera','ForRent',0,0,205874,0,0,0,1,'2015.350097','-1732.524780','14.234375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2014.789428','-1737.395263','13.122910','93.381378',0,0,14,-1),
(41,'Nera','ForRent',0,0,254892,0,0,0,1,'1980.596435','-1718.953613','17.030340',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(42,'Nera','ForRent',0,0,122486,0,0,0,1,'1973.208251','-1705.786743','15.968750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(43,'Nera','ForRent',0,0,254895,0,0,0,1,'1981.749023','-1683.010742','17.053943',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(44,'Nera','ForRent',0,0,124569,0,0,0,1,'1974.948364','-1671.361083','15.968750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(45,'Nera','ForRent',0,0,118234,0,0,0,1,'1973.466918','-1655.363525','15.968750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(46,'Nera','ForRent',0,0,138461,0,0,0,1,'1972.301513','-1633.710815','15.968750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(47,'Nera','ForRent',0,0,180544,1,0,0,1,'2011.482421','-1594.260986','13.583712',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2014.059570','-1596.779663','13.354621','132.372833',0,0,14,-1),
(48,'Nera','ForRent',0,0,173246,1,0,0,1,'2002.415161','-1594.006835','13.577538',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2003.964721','-1597.420776','13.349663','132.374588',0,0,14,-1),
(49,'Nera','ForRent',0,0,119852,0,0,0,1,'1986.572753','-1605.067626','13.532093',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(50,'Nera','ForRent',0,0,124589,0,0,0,1,'1973.325683','-1560.262329','13.639022',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','-0','0','0',0,0,14,-1),
(51,'Nera','ForRent',0,0,169842,0,0,0,1,'1958.692138','-1560.581176','13.594673',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1950.775634','-1564.293212','13.395774','132.354263',0,0,14,-1),
(52,'Nera','ForRent',0,0,185267,0,0,0,1,'1854.054687','-1914.283081','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1845.703247','-1885.220581','13.212705','90.074935',0,0,14,-1),
(53,'Nera','ForRent',0,0,188479,0,0,0,1,'1872.234130','-1911.788330','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1867.620849','-1885.694091','13.237982','90.077476',0,0,14,-1),
(54,'Nera','ForRent',0,0,179542,1,0,0,1,'1891.907836','-1914.394653','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1897.032836','-1884.343139','13.270669','90.060539',0,0,14,-1),
(55,'Nera','ForRent',0,0,182459,1,0,0,1,'1913.371215','-1911.908569','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1909.917968','-1884.417236','13.291051','90.062820',0,0,14,-1),
(56,'Nera','ForRent',0,0,178942,0,0,0,1,'1938.447875','-1911.223754','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1934.431396','-1884.141357','13.315013','90.063453',0,0,14,-1),
(57,'Nera','ForRent',0,0,125879,1,0,0,1,'1928.653320','-1915.905151','15.256797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(58,'Nera','ForRent',0,0,108543,0,0,0,1,'1905.983398','-2041.416015','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(59,'Nera','ForRent',0,0,192578,1,0,0,1,'1895.482177','-2068.542968','15.668893',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1898.127075','-2098.944091','13.288770','94.597381',0,0,14,-1),
(60,'Nera','ForRent',0,0,198752,0,0,0,1,'1873.515258','-2070.202392','15.497086',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1876.404541','-2098.828125','13.316974','93.373939',0,0,14,-1),
(61,'Nera','ForRent',0,0,75044,1,0,0,1,'1895.151000','-2021.485351','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(62,'Nera','ForRent',0,0,194582,0,0,0,1,'1851.963378','-2069.476806','15.481237',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1847.766723','-2098.977783','13.328635','93.126693',0,0,14,-1),
(63,'Nera','ForRent',0,0,80033,0,0,0,1,'1898.417114','-2004.323608','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(64,'Nera','ForRent',0,0,74030,0,0,0,1,'1867.836547','-2004.330322','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(65,'Nera','ForRent',0,0,114285,0,0,0,1,'1871.072143','-2019.655029','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(66,'Nera','ForRent',0,0,101456,0,0,0,1,'1852.567138','-2019.618408','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(67,'Nera','ForRent',0,0,81000,0,0,0,1,'1852.453125','-1990.141845','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(68,'Nera','ForRent',0,0,83454,0,0,0,1,'1867.704101','-1985.395874','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(69,'Nera','ForRent',0,0,108954,1,0,0,1,'1820.276245','-1994.333251','13.554395',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(70,'Nera','ForRent',0,0,184693,1,0,0,1,'1894.168212','-2133.939941','15.466326',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1899.324951','-2104.843750','13.361536','266.584228',0,0,14,-1),
(71,'Nera','ForRent',0,0,187892,1,0,0,1,'1872.430786','-2133.928710','15.481951',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1869.789306','-2104.889648','13.338756','268.061004',0,0,14,-1),
(72,'Nera','ForRent',0,0,79999,0,0,0,1,'1858.740600','-2040.889404','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(73,'Nera','ForRent',0,0,181594,0,0,0,1,'1851.869750','-2135.578125','15.388201',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1847.694335','-2104.744384','13.325108','268.671661',0,0,14,-1),
(74,'Nera','ForRent',0,0,71234,0,0,0,1,'1913.954589','-2021.287231','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(75,'Nera','ForRent',0,0,170000,1,0,0,1,'1804.299560','-2124.647705','13.942373',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1795.368652','-2148.855224','13.355680','13.935524',0,0,14,-1),
(76,'Nera','ForRent',0,0,116439,0,0,0,1,'1801.878906','-2098.948730','14.021014',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(77,'Nera','ForRent',0,0,118952,0,0,0,1,'1781.539184','-2101.275634','14.056648',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1788.959838','-2083.116455','13.411230','235.811035',0,0,14,-1),
(78,'Nera','ForRent',0,0,169852,1,0,0,1,'1761.014770','-2125.262207','14.056648',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1753.776611','-2144.981689','13.327650','85.395881',0,0,14,-1),
(79,'Nera','ForRent',0,0,134000,0,0,0,1,'1782.258544','-2126.508056','14.067889',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(80,'Nera','ForRent',0,0,136520,0,0,0,1,'1762.604248','-2102.243896','13.856951',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(81,'Nera','ForRent',0,0,118682,1,0,0,1,'1734.142578','-2099.024169','14.036639',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(82,'Nera','ForRent',0,0,135892,1,0,0,1,'1734.756713','-2130.345214','14.021014',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(83,'Nera','ForRent',0,0,175236,1,0,0,1,'1715.144409','-2125.244873','14.056648',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1707.890625','-2145.218261','13.302906','92.054069',0,0,14,-1),
(84,'Nera','ForRent',0,0,123456,0,0,0,1,'1711.370483','-2101.384765','14.021014',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(85,'Nera','ForRent',0,0,119698,1,0,0,1,'1695.535766','-2125.836914','13.810076',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(86,'Nera','ForRent',0,0,126700,1,0,0,1,'1673.635498','-2122.400390','14.146014',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(87,'Nera','ForRent',0,0,100000,0,0,0,1,'1667.422729','-2106.957031','14.072273',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1674.690673','-2089.034912','13.334329','252.933959',0,0,14,-1),
(88,'Nera','ForRent',0,0,215896,1,0,0,1,'1684.783325','-2098.168701','13.834323',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(89,'Nera','ForRent',0,0,305042,1,0,0,1,'2148.798339','-1484.907348','26.624031',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2176.032714','-1499.347167','23.753814','39.107910',0,0,14,-1),
(90,'Nera','ForRent',0,0,121589,0,0,0,1,'2149.378662','-1433.776489','25.860511',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(91,'Nera','ForRent',0,0,129872,0,0,0,1,'2152.214599','-1446.265136','26.105066',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(92,'Nera','ForRent',0,0,139854,0,0,0,1,'2150.108642','-1419.092041','25.921875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(93,'Nera','ForRent',0,0,135864,0,0,0,1,'2151.180664','-1400.600952','26.128503',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(94,'Nera','ForRent',0,0,90000,1,0,0,1,'2196.285156','-1404.245117','25.948816',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(95,'Nera','ForRent',0,0,211546,1,0,0,1,'2188.553955','-1419.235229','26.156250',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2189.510986','-1414.418579','25.320596','268.241912',0,0,14,-1),
(96,'Nera','ForRent',0,0,125795,1,0,0,1,'2194.367431','-1443.000244','26.073816',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(97,'Nera','ForRent',0,0,123500,0,0,0,1,'2191.116699','-1455.809204','26.000000',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(98,'Nera','ForRent',0,0,146528,0,0,0,1,'2191.183349','-1470.351806','25.914062',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(99,'Nera','ForRent',0,0,203456,1,0,0,1,'2190.315185','-1487.588989','26.105066',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2198.437988','-1503.852294','23.743104','335.351348',0,0,14,-1),
(100,'Nera','ForRent',0,0,112578,0,0,0,1,'2232.585937','-1469.339355','24.581628',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(101,'Nera','ForRent',0,0,108900,1,0,0,1,'2247.784423','-1469.359008','24.480066',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(102,'Nera','ForRent',0,0,105920,0,0,0,1,'2263.800781','-1469.334960','24.370691',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(103,'Nera','ForRent',0,0,104582,0,0,0,1,'2230.228027','-1396.874633','24.243347',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(104,'Nera','ForRent',0,0,101894,0,0,0,1,'2243.523925','-1396.862182','24.243347',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(105,'Nera','ForRent',0,0,108527,0,0,0,1,'2256.093505','-1396.854858','24.243347',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(106,'Nera','ForRent',0,0,130400,0,0,0,1,'2202.557373','-1364.057006','25.860534',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(107,'Nera','ForRent',0,0,125698,0,0,0,1,'2185.245605','-1363.923950','25.829282',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(108,'Nera','ForRent',0,0,128200,0,0,0,1,'2148.439941','-1319.571411','25.743345',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(109,'Nera','ForRent',0,0,116854,1,0,0,1,'2147.768798','-1366.132812','25.972253',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(110,'Nera','ForRent',0,0,254817,1,0,0,1,'2126.829345','-1320.399780','26.624254',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(111,'Nera','ForRent',0,0,133456,0,0,0,1,'2129.609619','-1361.689086','26.136316',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(112,'Nera','ForRent',0,0,114856,1,0,0,1,'2100.685058','-1321.326293','25.953125',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(113,'Nera','ForRent',0,0,242897,1,0,0,1,'2091.238037','-1278.095947','26.179687',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2095.869140','-1278.731201','25.275163','179.674728',0,0,14,-1),
(114,'Nera','ForRent',0,0,122322,1,0,0,1,'2150.230468','-1285.066406','24.526941',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2161.270507','-1267.477050','23.752128','265.350769',0,0,14,-1),
(115,'Nera','ForRent',0,0,129845,1,0,0,1,'2111.471435','-1279.787841','25.687500',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(116,'Nera','ForRent',0,0,129800,1,0,0,1,'2132.260253','-1280.046630','25.890625',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(117,'Nera','ForRent',0,0,75000,1,0,0,1,'2133.360595','-1232.654052','24.421875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2121.892578','-1260.760742','23.772939','271.882568',0,0,14,-1),
(118,'Nera','ForRent',0,0,124582,0,0,0,1,'2153.907714','-1243.082275','25.367187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(119,'Nera','ForRent',0,0,123700,0,0,0,1,'2110.979003','-1243.687133','25.851562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(120,'Nera','ForRent',0,0,204521,1,0,0,1,'2090.723144','-1235.180419','26.019128',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2096.603271','-1260.728149','23.769350','272.319854',0,0,14,-1),
(121,'Nera','ForRent',0,0,111254,1,0,0,1,'2091.546875','-1185.028686','27.057060',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(122,'Nera','ForRent',0,0,235864,0,0,0,1,'2092.114990','-1166.439086','26.585937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2089.091064','-1170.689575','25.236768','88.658523',0,0,14,-1),
(123,'Nera','ForRent',0,0,114596,0,0,0,1,'2191.748535','-1239.226440','24.487878',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(124,'Nera','ForRent',0,0,105000,0,0,0,1,'2209.796386','-1240.240844','24.480066',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(125,'Nera','ForRent',0,0,218600,1,0,0,1,'2229.569335','-1241.608154','25.656250',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2224.666748','-1240.392333','24.937273','359.542846',0,0,14,-1),
(126,'Nera','ForRent',0,0,126548,0,0,0,1,'2095.361328','-1145.030151','26.592920',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(127,'Nera','ForRent',0,0,105500,1,0,0,1,'2093.870361','-1123.181518','27.689872',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(128,'Nera','ForRent',0,0,116894,1,0,0,1,'2045.676391','-1116.585937','26.361747',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(129,'Nera','ForRent',0,0,119854,1,0,0,1,'2023.078613','-1120.624877','26.421045',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(130,'Nera','ForRent',0,0,275842,1,0,0,1,'2000.038696','-1114.552612','27.125000',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1991.174072','-1119.394897','26.551815','269.590820',0,0,14,-1),
(131,'Nera','ForRent',0,0,134300,0,0,0,1,'2249.817871','-1238.907226','25.898437',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(132,'Nera','ForRent',0,0,115800,1,0,0,1,'2250.293701','-1280.045776','25.476562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(133,'Nera','ForRent',0,0,112450,0,0,0,1,'2230.072753','-1280.066162','25.628503',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(134,'Nera','ForRent',0,0,113289,0,0,0,1,'2207.885498','-1280.825073','25.120691',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(135,'Nera','ForRent',0,0,216800,1,0,0,1,'2191.542236','-1275.607299','25.156250',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2196.427246','-1276.296875','24.317087','179.694641',0,0,14,-1),
(136,'Nera','ForRent',0,0,109824,0,0,0,1,'1955.438842','-1115.295166','27.830497',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(137,'Nera','ForRent',0,0,132300,1,0,0,1,'1939.052368','-1114.655395','27.452295',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(138,'Nera','ForRent',0,0,103420,1,0,0,1,'1921.848022','-1115.198364','27.088310',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(139,'Nera','ForRent',0,0,220400,1,0,0,1,'1906.012451','-1113.107177','26.664062',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1910.754516','-1117.131835','25.467555','180.457382',0,0,14,-1),
(140,'Nera','ForRent',0,0,116900,1,0,0,1,'1886.282348','-1113.940185','26.275810',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(141,'Nera','ForRent',0,0,81453,1,0,0,1,'2023.007934','-1052.965942','25.596122',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(142,'Nera','ForRent',0,0,76851,1,0,0,1,'2036.709350','-1059.750000','25.650810',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(143,'Nera','ForRent',0,0,78950,0,0,0,1,'2050.754638','-1065.713378','25.783622',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(144,'Nera','ForRent',0,0,105840,0,0,0,1,'2061.038085','-1075.548706','25.500129',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(145,'Nera','ForRent',0,0,98540,1,0,0,1,'2075.234375','-1081.875122','25.680694',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(146,'Nera','ForRent',0,0,164892,0,0,0,1,'2108.755615','-1082.189086','25.407815',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2094.071044','-1094.435913','24.820062','157.464996',0,0,14,-1),
(147,'Nera','ForRent',0,0,40000,0,0,0,1,'2207.798339','-1100.952026','31.554687',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2197.461425','-1107.845336','24.902465','157.500625',0,0,14,-1),
(148,'Nera','ForRent',0,0,103900,0,0,0,1,'2145.328369','-1084.705078','25.035003',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(149,'Nera','ForRent',0,0,93800,0,0,0,1,'2188.884521','-1081.625976','43.833290',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(150,'Nera','ForRent',0,0,53433,0,0,0,1,'2221.089843','-1082.969116','41.779808',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(151,'Nera','ForRent',0,0,96500,0,0,0,1,'2249.324462','-1060.165893','55.968750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(152,'Nera','ForRent',0,0,113540,1,0,0,1,'2218.855468','-1031.771728','60.266338',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(153,'Nera','ForRent',0,0,110000,0,0,0,1,'2287.525878','-1080.941772','48.142734',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2274.425781','-1107.834472','37.841888','157.593399',0,0,14,-1),
(154,'Nera','ForRent',0,0,86540,1,0,0,1,'2208.101074','-1026.599853','61.350379',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(155,'Nera','ForRent',0,0,139540,0,0,0,1,'2259.367919','-1019.190124','59.296722',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(156,'Nera','ForRent',0,0,45850,0,0,0,1,'2283.834472','-1045.976318','49.887119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(157,'Nera','ForRent',0,0,41520,0,0,0,1,'2297.594970','-1053.299072','49.933994',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(158,'Nera','ForRent',0,0,44200,0,0,0,1,'2335.325683','-1045.181152','52.358196',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(159,'Nera','ForRent',0,0,41500,0,0,0,1,'2370.023681','-1035.168823','54.410556',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(160,'Nera','ForRent',0,0,53200,0,0,0,1,'2440.358398','-1056.579345','54.738681',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(161,'Nera','ForRent',0,0,62500,1,0,0,1,'2461.934082','-1011.908203','60.113681',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(162,'Nera','ForRent',0,0,54500,1,0,0,1,'2457.620361','-1054.734741','59.959186',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(163,'Nera','ForRent',0,0,57900,0,0,0,1,'2479.415527','-1063.782104','66.835937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(164,'Nera','ForRent',0,0,222100,0,0,0,1,'2394.879150','-1133.539062','30.718750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2399.839111','-1134.767456','29.983989','182.006164',0,0,14,-1),
(165,'Nera','ForRent',0,0,53400,1,0,0,1,'2512.673095','-1027.301879','70.085937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(166,'Nera','ForRent',0,0,51600,1,0,0,1,'2527.003173','-1060.290283','69.568328',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(167,'Nera','ForRent',0,0,57000,1,0,0,1,'2579.422119','-1033.299072','69.579879',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(168,'Nera','ForRent',0,0,44000,0,0,0,1,'2561.784667','-1034.956909','69.869216',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(169,'Nera','ForRent',0,0,87600,0,0,0,1,'2576.377441','-1070.492675','69.832229',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(170,'Nera','ForRent',0,0,92500,1,0,0,1,'2572.263916','-1090.944824','67.225723',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(171,'Nera','ForRent',0,0,83400,1,0,0,1,'2427.441650','-1135.772583','34.710937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(172,'Nera','ForRent',0,0,90000,0,0,0,1,'2519.541259','-1113.151000','56.592597',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(173,'Nera','ForRent',0,0,69000,0,0,0,1,'2470.595947','-1105.207763','44.487880',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(174,'Nera','ForRent',0,0,126100,1,0,0,1,'2456.708984','-1101.929321','43.867187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(175,'Nera','ForRent',0,0,103800,0,0,0,1,'2438.566650','-1105.410156','42.751155',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(176,'Nera','ForRent',0,0,66500,1,0,0,1,'2408.136230','-1106.561767','40.295722',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(177,'Nera','ForRent',0,0,100200,0,0,0,1,'2374.134521','-1139.172729','29.058792',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(178,'Nera','ForRent',0,0,115500,0,0,0,1,'2351.978271','-1170.479736','28.065654',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(179,'Nera','ForRent',0,0,116950,0,0,0,1,'2488.038085','-1136.364746','39.154315',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(180,'Nera','ForRent',0,0,113450,0,0,0,1,'2510.416992','-1132.523803','41.620693',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(181,'Nera','ForRent',0,0,93400,1,0,0,1,'2628.659912','-1068.081298','69.613059',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(182,'Nera','ForRent',0,0,90350,0,0,0,1,'2627.801513','-1084.869750','69.616462',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(183,'Nera','ForRent',0,0,101540,1,0,0,1,'2388.365234','-1279.636718','25.129104',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(184,'Nera','ForRent',0,0,103500,0,0,0,1,'2625.936279','-1098.823242','69.354682',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(185,'Nera','ForRent',0,0,99900,1,0,0,1,'2626.729248','-1112.664550','67.865280',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(186,'Nera','ForRent',0,0,112200,1,0,0,1,'2387.668212','-1328.390869','25.124164',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(187,'Nera','ForRent',0,0,97860,0,0,0,1,'2389.529296','-1346.001464','25.076972',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(188,'Nera','ForRent',0,0,89950,0,0,0,1,'2383.506103','-1366.285644','24.491352',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(189,'Nera','ForRent',0,0,101500,0,0,0,1,'2433.604736','-1274.952392','24.756660',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(190,'Nera','ForRent',0,0,104200,1,0,0,1,'2434.811767','-1289.403198','25.347854',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(191,'Nera','ForRent',0,0,109580,0,0,0,1,'2434.190673','-1303.423217','24.986663',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(192,'Nera','ForRent',0,0,79500,0,0,0,1,'2468.547851','-1278.291992','30.366352',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(193,'Nera','ForRent',0,0,80000,1,0,0,1,'2469.890136','-1295.584472','30.233222',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(194,'Nera','ForRent',0,0,107580,0,0,0,1,'2433.949462','-1320.652465','25.323432',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(195,'Nera','ForRent',0,0,92400,0,0,0,1,'2439.834472','-1338.839355','24.101562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(196,'Nera','ForRent',0,0,185850,1,0,0,1,'2472.721435','-1238.531982','32.569477',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2466.330322','-1248.484008','25.238010','177.732101',0,0,14,-1),
(197,'Nera','ForRent',0,0,94400,0,0,0,1,'2439.591308','-1357.192382','24.100704',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(198,'Nera','ForRent',0,0,182850,0,0,0,1,'2492.133789','-1239.495117','37.905414',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2486.135009','-1248.458496','30.580526','177.702194',0,0,14,-1),
(199,'Nera','ForRent',0,0,123233,0,0,0,1,'2529.790771','-1243.378051','43.971870',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2530.870849','-1248.400024','37.300788','177.709136',0,0,14,-1),
(200,'Nera','ForRent',0,0,193540,1,0,0,1,'2550.942871','-1234.588989','49.001361',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2547.239257','-1248.340942','41.876163','177.763168',0,0,14,-1),
(201,'Nera','ForRent',0,0,324582,1,0,0,1,'2550.202392','-1197.475585','60.839477',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2558.977050','-1194.579956','61.098155','346.703002',0,0,14,-1),
(202,'Nera','ForRent',0,0,165656,0,0,0,1,'2520.743164','-1197.491333','56.564640',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2529.007080','-1194.618896','56.603485','0.395681',0,0,14,-1),
(203,'Nera','ForRent',0,0,105400,0,0,0,1,'2467.757324','-1199.943847','36.811664',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(204,'Nera','ForRent',0,0,308900,1,0,0,1,'2808.116699','-1176.470458','25.376346',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'2827.177001','-1169.995117','24.814540','270.394836',0,0,14,-1),
(205,'Nera','ForRent',0,0,305400,1,0,0,1,'2808.115722','-1190.187377','25.341939',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'2826.561279','-1194.525390','24.769218','314.254394',0,0,14,-1),
(206,'Nera','ForRent',0,0,224800,1,0,0,1,'2842.374511','-1335.399169','14.742118',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2853.311523','-1330.238159','10.785810','278.398101',0,0,14,-1),
(207,'Nera','ForRent',0,0,217800,1,0,0,1,'2853.057128','-1366.126708','14.164062',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'2854.603027','-1355.687011','10.789004','271.733795',0,0,14,-1),
(208,'Nera','ForRent',0,0,49200,0,0,0,1,'2582.784667','-952.959533','81.387695',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(209,'Nera','ForRent',0,0,41640,0,0,0,1,'2552.047363','-958.384216','82.615173',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(210,'Nera','ForRent',0,0,47900,0,0,0,1,'2531.139160','-963.461547','82.368598',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(211,'Nera','ForRent',0,0,54530,1,0,0,1,'2139.910888','-1008.217895','61.744888',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(212,'Nera','ForRent',0,0,40400,0,0,0,1,'2492.097900','-965.833374','82.548904',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(213,'Nera','ForRent',0,0,112500,0,0,0,1,'2109.260986','-1000.724609','60.507812',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(214,'Nera','ForRent',0,0,43600,0,0,0,1,'2517.861083','-965.424621','82.328361',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(215,'Nera','ForRent',0,0,182450,1,0,0,1,'2090.916503','-972.347961','51.906215',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2076.205810','-974.115722','49.310844','165.245193',0,0,14,-1),
(216,'Nera','ForRent',0,0,48100,1,0,0,1,'2472.552734','-962.567138','80.325462',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(217,'Nera','ForRent',0,0,103470,0,0,0,1,'2066.681640','-993.272216','48.800392',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(218,'Nera','ForRent',0,0,45000,0,0,0,1,'2459.551513','-947.705749','80.083290',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(219,'Nera','ForRent',0,0,194800,1,0,0,1,'2049.307373','-986.866821','44.574398',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2058.766357','-986.551513','46.439392','352.860168',0,0,14,-1),
(220,'Nera','ForRent',0,0,188400,0,0,0,1,'2044.596801','-991.075195','43.212570',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2036.206542','-989.732543','40.506721','12.725608',0,0,14,-1),
(221,'Nera','ForRent',0,0,49500,1,0,0,1,'2454.208496','-965.039245','80.073226',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(222,'Nera','ForRent',0,0,62000,1,0,0,1,'2015.818725','-977.860229','36.647483',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(223,'Nera','ForRent',0,0,102590,1,0,0,1,'2007.784790','-984.558410','34.317432',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(224,'Nera','ForRent',0,0,56900,1,0,0,1,'2439.912109','-1010.827453','54.343750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(225,'Nera','ForRent',0,0,205500,1,0,0,1,'2044.761108','-966.522888','44.110225',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2032.025878','-965.293762','40.966457','136.644195',0,0,14,-1),
(226,'Nera','ForRent',0,0,181460,0,0,0,1,'2051.031005','-954.576904','48.034931',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'2054.400878','-970.629455','45.543739','178.217346',0,0,14,-1),
(227,'Nera','ForRent',0,0,59640,0,0,0,1,'2491.393066','-1012.218139','65.398437',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(228,'Nera','ForRent',0,0,49850,0,0,0,1,'2499.739501','-1065.558349','70.235939',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(229,'Nera','ForRent',0,0,54600,1,0,0,1,'2534.468017','-1063.263549','69.565605',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(230,'Nera','ForRent',0,0,48920,0,0,0,1,'2549.204345','-1032.262084','69.578872',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(231,'Nera','ForRent',0,0,256890,1,0,0,1,'1410.805908','-920.819091','38.421875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1402.299072','-922.652526','35.822738','170.304931',0,0,14,-1),
(232,'Nera','ForRent',0,0,259890,0,0,0,1,'1440.425903','-926.253601','39.647666',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1431.858764','-927.861083','36.958850','170.231338',0,0,14,-1),
(233,'Nera','ForRent',0,0,275840,1,0,0,1,'1421.893798','-885.970703','50.676860',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1430.257934','-882.563537','50.571334','17.077337',0,0,14,-1),
(234,'Nera','ForRent',0,0,284840,1,0,0,1,'1468.795776','-906.164672','54.835937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1464.196655','-901.894104','54.613571','359.612487',0,0,14,-1),
(235,'Nera','ForRent',0,0,124890,1,0,0,1,'1535.838867','-885.335327','57.657482',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(236,'Nera','ForRent',0,0,320000,0,0,0,1,'1540.469970','-851.291870','64.336059',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1538.019165','-841.803527','64.318046','91.700340',0,0,14,-1),
(237,'Nera','ForRent',0,0,267480,0,0,0,1,'1535.033325','-800.278747','72.849456',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1530.840454','-813.184875','71.773582','88.255226',0,0,14,-1),
(238,'Nera','ForRent',0,0,276500,0,0,0,1,'1527.792724','-772.557495','80.578125',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1515.754272','-765.791748','79.885589','138.145202',0,0,14,-1),
(239,'Nera','ForRent',0,0,650000,1,0,0,1,'1496.978271','-687.954101','95.563308',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1516.859497','-694.316406','94.528450','89.621337',0,0,14,-1),
(240,'Nera','ForRent',0,0,460500,1,0,0,1,'1442.621582','-628.867126','95.718566',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1460.516357','-632.066833','95.539138','178.979492',0,0,14,-1),
(241,'Nera','ForRent',0,0,1000000,1,0,0,1,'1298.735351','-798.725341','84.140625',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1248.833007','-804.183227','83.918762','178.980331',0,0,14,-1),
(242,'Nera','ForRent',0,0,545200,1,0,0,1,'1331.412353','-632.513610','109.134902',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(243,'Nera','ForRent',0,0,432500,1,0,0,1,'1112.639770','-742.052246','100.132926',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1109.739135','-732.429748','100.145416','89.887535',0,0,14,-1),
(244,'Nera','ForRent',0,0,365000,0,0,0,1,'1094.311401','-806.849914','107.416732',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(245,'Nera','ForRent',0,0,323900,0,0,0,1,'1034.636596','-813.097656','101.851562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1029.369018','-811.783935','101.629104','23.505352',0,0,14,-1),
(246,'Nera','ForRent',0,0,210231,1,0,0,1,'1016.870910','-763.356262','112.563018',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1024.971069','-777.300781','102.878555','182.255310',0,0,14,-1),
(247,'Nera','ForRent',0,0,390500,0,0,0,1,'989.811279','-828.649963','95.468574',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'979.341735','-830.469848','95.468322','26.014112',0,0,14,-1),
(248,'Nera','ForRent',0,0,245300,0,0,0,1,'937.861999','-848.646545','93.586387',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'944.464111','-841.819274','93.862792','26.015199',0,0,14,-1),
(249,'Nera','ForRent',0,0,261450,0,0,0,1,'923.902587','-853.404479','93.456520',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'929.496093','-856.776489','93.251319','344.568664',0,0,14,-1),
(250,'Nera','ForRent',0,0,240533,1,0,0,1,'910.391174','-817.543029','103.126029',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'912.306335','-832.457763','92.181404','207.858612',0,0,14,-1),
(251,'Nera','ForRent',0,0,369450,1,0,0,1,'858.349792','-828.791442','89.501670',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'859.686645','-847.813659','77.078010','206.303375',0,0,14,-1),
(252,'Nera','ForRent',0,0,335500,1,0,0,1,'828.069335','-858.777893','70.330810',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(253,'Nera','ForRent',0,0,537700,1,0,0,1,'835.950012','-894.827514','68.768898',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'832.307434','-888.105651','68.554969','323.642303',0,0,14,-1),
(254,'Nera','ForRent',0,0,321450,1,0,0,1,'785.891906','-828.555603','70.289581',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'796.400451','-840.828430','60.421649','188.333633',0,0,14,-1),
(255,'Nera','ForRent',0,0,354800,1,0,0,1,'808.269775','-759.403747','76.531364',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'814.333068','-767.991638','76.622329','283.322143',0,0,14,-1),
(256,'Nera','ForRent',0,0,315650,1,0,0,1,'848.028747','-745.551940','94.969268',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'843.674255','-762.021484','84.712394','180.807006',0,0,14,-1),
(257,'Nera','ForRent',0,0,449500,1,0,0,1,'891.582031','-782.987731','101.314811',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'896.335693','-778.243591','101.101356','16.381961',0,0,14,-1),
(258,'Nera','ForRent',0,0,369000,1,0,0,1,'867.574157','-717.616333','105.679687',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'865.257568','-712.087463','105.462127','334.761932',0,0,14,-1),
(259,'Nera','ForRent',0,0,465200,1,0,0,1,'898.075317','-677.267395','116.890441',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'910.378234','-664.174865','116.712059','235.322875',0,0,14,-1),
(260,'Nera','ForRent',0,0,333500,0,0,0,1,'945.825927','-710.052612','122.619873',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(261,'Nera','ForRent',0,0,720000,0,0,0,1,'980.391418','-677.305175','121.976257',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1007.026794','-663.711486','120.924072','33.532417',0,0,14,-1),
(262,'Nera','ForRent',0,0,535600,0,0,0,1,'1045.186523','-642.914428','120.117187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1039.389648','-641.072814','119.895111','5.241348',0,0,14,-1),
(263,'Nera','ForRent',0,0,623000,0,0,0,1,'1094.878662','-647.911376','113.648437',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1088.319702','-641.134277','112.958946','272.165100',0,0,14,-1),
(264,'Nera','ForRent',0,0,261400,1,0,0,1,'977.454895','-771.683898','112.202629',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(265,'Nera','ForRent',0,0,480000,1,0,0,1,'731.209411','-1012.805541','52.737854',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'726.094543','-994.790649','52.429859','58.886409',0,0,14,-1),
(266,'Nera','ForRent',0,0,242500,0,0,0,1,'673.246520','-1019.899108','55.759605',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(267,'Nera','ForRent',0,0,415350,1,0,0,1,'700.228271','-1060.046875','49.421691',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'688.389282','-1074.192382','49.253158','58.899448',0,0,14,-1),
(268,'Nera','ForRent',0,0,216900,0,0,0,1,'648.384216','-1058.624389','52.579917',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(269,'Nera','ForRent',0,0,303460,0,0,0,1,'612.165893','-1085.924316','58.826656',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'619.855651','-1102.939331','46.484848','210.263275',0,0,14,-1),
(270,'Nera','ForRent',0,0,350600,0,0,0,1,'645.952453','-1117.460327','44.207038',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'636.480651','-1123.233764','44.376194','47.109180',0,0,14,-1),
(271,'Nera','ForRent',0,0,362450,0,0,0,1,'566.194396','-1113.064453','62.806358',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'568.691101','-1132.212158','50.383693','210.669876',0,0,14,-1),
(272,'Nera','ForRent',0,0,323500,0,0,0,1,'552.850830','-1200.317138','44.831535',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'542.307556','-1201.399047','44.291679','18.528697',0,0,14,-1),
(273,'Nera','ForRent',0,0,167099,0,0,0,1,'558.704223','-1161.091186','54.429687',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(274,'Nera','ForRent',0,0,187000,0,0,0,1,'470.368255','-1163.868164','67.215682',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(275,'Nera','ForRent',0,0,389859,0,0,0,1,'416.629608','-1154.225708','76.687614',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'407.052154','-1151.052612','76.658012','149.413543',0,0,14,-1),
(276,'Nera','ForRent',0,0,415486,1,0,0,1,'497.718505','-1094.891845','82.359191',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'479.875701','-1091.445556','82.183792','357.511505',0,0,14,-1),
(277,'Nera','ForRent',0,0,357200,1,0,0,1,'559.050781','-1076.441284','72.921989',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'565.877502','-1069.771850','72.882888','25.684177',0,0,14,-1),
(278,'Nera','ForRent',0,0,224560,0,0,0,1,'432.084472','-1253.944335','51.580940',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(279,'Nera','ForRent',0,0,361800,1,0,0,1,'398.380950','-1271.275024','50.019790',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'405.943878','-1264.540405','50.195095','25.786363',0,0,14,-1),
(280,'Nera','ForRent',0,0,160000,0,0,0,1,'355.265747','-1281.066650','53.703639',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(281,'Nera','ForRent',0,0,169000,0,0,0,1,'345.112548','-1298.133056','50.759044',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(282,'Nera','ForRent',0,0,660000,0,0,0,1,'298.695312','-1338.315917','53.441520',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(283,'Nera','ForRent',0,0,695000,1,0,0,1,'256.784332','-1366.215698','53.528709',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'268.921539','-1366.563110','52.953250','35.197307',0,0,14,-1),
(284,'Nera','ForRent',0,0,725400,0,0,0,1,'189.638534','-1308.244018','70.249313',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'166.381225','-1340.652099','69.503059','176.939392',0,0,14,-1),
(285,'Nera','ForRent',0,0,500500,1,0,0,1,'219.343383','-1249.962524','78.335556',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'227.904968','-1245.189208','78.069053','167.223190',0,0,14,-1),
(286,'Nera','ForRent',0,0,640000,0,0,0,1,'253.483856','-1269.794433','74.425575',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'276.730560','-1252.072998','73.698661','310.575500',0,0,14,-1),
(287,'Nera','ForRent',0,0,1300000,1,0,0,1,'251.533615','-1220.140258','76.102371',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'247.087371','-1236.297973','76.139801','305.393646',0,0,14,-1),
(288,'Nera','ForRent',0,0,750000,1,0,0,1,'300.221954','-1154.432861','81.389831',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'283.250579','-1160.272705','80.691452','227.015380',0,0,14,-1),
(289,'Nera','ForRent',0,0,316500,1,0,0,1,'352.238616','-1197.819213','76.515625',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'346.779235','-1198.285644','76.298614','40.654880',0,0,14,-1),
(290,'Nera','ForRent',0,0,390000,0,0,0,1,'228.169143','-1405.439086','51.609375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(291,'Nera','ForRent',0,0,252420,0,0,0,1,'161.595489','-1455.761230','32.844982',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(292,'Nera','ForRent',0,0,313500,1,0,0,1,'142.587829','-1470.330932','25.210937',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(293,'Nera','ForRent',0,0,269000,0,0,0,1,'167.758026','-1759.020874','6.796875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'167.419158','-1770.561523','4.201380','87.361885',0,0,14,-1),
(294,'Nera','ForRent',0,0,95400,0,0,0,1,'192.722640','-1769.679443','4.313369',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(295,'Nera','ForRent',0,0,110800,0,0,0,1,'206.838226','-1768.940429','4.368735',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(296,'Nera','ForRent',0,0,178450,0,0,0,1,'280.694000','-1767.913330','4.536153',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(297,'Nera','ForRent',0,0,105460,0,0,0,1,'295.336425','-1764.510864','4.547885',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(298,'Nera','ForRent',0,0,78600,0,0,0,1,'305.570251','-1770.361450','4.538797',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(299,'Nera','ForRent',0,0,315000,1,0,0,1,'315.951110','-1769.467285','4.624524',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(300,'Nera','ForRent',0,0,235000,1,0,0,1,'922.176818','-1803.902832','13.836963',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(301,'Nera','ForRent',0,0,277300,0,0,0,1,'761.248107','-1564.412597','13.911296',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(302,'Nera','ForRent',0,0,274500,0,0,0,1,'771.061767','-1510.947875','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(303,'Nera','ForRent',0,0,285400,0,0,0,1,'782.924377','-1464.568725','13.546875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(304,'Nera','ForRent',0,0,315450,1,0,0,1,'738.773071','-1418.513305','13.523437',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(305,'Nera','ForRent',0,0,242500,1,0,0,1,'675.145507','-1430.451049','14.851562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'666.523376','-1421.915527','14.453478','2.154325',0,0,14,-1),
(306,'Nera','ForRent',0,0,265000,0,0,0,1,'824.876098','-1424.027343','14.497745',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'844.274536','-1420.360107','12.503164','2.203414',0,0,14,-1),
(307,'Nera','ForRent',0,0,273600,0,0,0,1,'851.982421','-1423.118530','14.143129',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'860.011901','-1420.542846','12.456041','2.206526',0,0,14,-1),
(308,'Nera','ForRent',0,0,191400,0,0,0,1,'880.092590','-1424.661865','14.484375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(309,'Nera','ForRent',0,0,355000,0,0,0,1,'900.223510','-1447.190063','14.369938',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'903.722595','-1455.083740','12.809603','270.696716',0,0,14,-1),
(310,'Nera','ForRent',0,0,339300,0,0,0,1,'813.528259','-1456.619140','14.147764',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'811.265625','-1448.875244','12.737108','85.824340',0,0,14,-1),
(311,'Nera','ForRent',0,0,346700,1,0,0,1,'822.352294','-1505.338012','14.395904',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'815.071777','-1502.295043','12.689199','358.769561',0,0,14,-1),
(312,'Nera','ForRent',0,0,337850,0,0,0,1,'876.148864','-1513.293823','14.347785',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'872.192565','-1504.829833','12.853862','92.658180',0,0,14,-1),
(313,'Nera','ForRent',0,0,339480,1,0,0,1,'849.828979','-1520.201293','14.353009',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'853.136596','-1527.899291','12.859915','267.010894',0,0,14,-1),
(314,'Nera','ForRent',0,0,205800,0,0,0,1,'766.915344','-1605.881835','13.803857',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(315,'Nera','ForRent',0,0,254600,0,0,0,1,'768.072326','-1655.763549','5.609375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'764.142517','-1660.343750','4.209957','91.004661',0,0,14,-1),
(316,'Nera','ForRent',0,0,239550,0,0,0,1,'769.221496','-1696.546752','5.155420',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(317,'Nera','ForRent',0,0,231500,1,0,0,1,'769.221740','-1745.938842','13.077295',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(318,'Nera','ForRent',0,0,201200,0,0,0,1,'693.554504','-1705.854003','3.819482',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(319,'Nera','ForRent',0,0,205460,0,0,0,1,'653.438720','-1714.115600','14.764795',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(320,'Nera','ForRent',0,0,156800,0,0,0,1,'694.969299','-1690.571533','4.346122',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(321,'Nera','ForRent',0,0,237970,0,0,0,1,'693.757324','-1645.820068','4.093750',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'697.483459','-1641.294921','3.199782','268.352172',0,0,14,-1),
(322,'Nera','ForRent',0,0,269450,0,0,0,1,'657.220642','-1652.640014','15.406250',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'652.828552','-1657.444335','14.442006','90.649620',0,0,14,-1),
(323,'Nera','ForRent',0,0,112450,0,0,0,1,'656.406005','-1636.347290','15.861747',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(324,'Nera','ForRent',0,0,206600,1,0,0,1,'697.283142','-1627.215820','3.749170',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(325,'Nera','ForRent',0,0,249900,1,0,0,1,'692.936035','-1602.753295','15.046875',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'688.235717','-1599.844360','13.880574','359.534240',0,0,14,-1),
(326,'Nera','ForRent',0,0,214000,1,0,0,1,'653.228698','-1619.775878','15.000000',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(327,'Nera','ForRent',0,0,178930,1,0,0,1,'652.664733','-1694.018676','14.550196',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(328,'Nera','ForRent',0,0,60000,1,0,0,1,'2695.277587','-2020.042114','14.022284',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(329,'Nera','ForRent',0,0,101100,1,0,0,1,'2673.436279','-2019.771850','14.168166',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(330,'Nera','ForRent',0,0,115200,1,0,0,1,'2696.435791','-1990.359863','14.222853',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(331,'Nera','ForRent',0,0,186700,0,0,0,1,'2650.691406','-2021.726806','14.176628',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(332,'Nera','ForRent',0,0,114900,1,0,0,1,'2672.588623','-1989.472656','14.324020',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(333,'Nera','ForRent',0,0,82500,0,0,0,1,'2636.043945','-2012.586914','13.813860',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(334,'Nera','ForRent',0,0,95600,0,0,0,1,'2636.981201','-1991.809204','14.324020',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(335,'Nera','ForRent',0,0,115900,0,0,0,1,'2652.561035','-1989.458618','13.998847',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(336,'Nera','ForRent',0,0,80000,1,0,0,1,'1903.108642','-1404.806518','3173.523193',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(337,'Nera','ForRent',0,0,25000,0,0,0,1,'1896.506225','-1404.818481','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(338,'Nera','ForRent',0,0,80000,0,0,0,1,'1894.360229','-1406.500488','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(339,'Nera','ForRent',0,0,26000,0,0,0,1,'1894.578735','-1412.823730','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(340,'Nera','ForRent',0,0,80000,1,0,0,1,'1896.782104','-1417.007446','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(341,'Nera','ForRent',0,0,80000,1,0,0,1,'1898.619018','-1413.890136','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(342,'Nera','ForRent',0,0,30000,1,0,0,1,'1914.587524','-1395.788940','3196.297119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(343,'Nera','ForRent',0,0,27777,0,0,0,1,'1903.011596','-1404.813598','3179.198486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(344,'Nera','ForRent',0,0,75000,1,0,0,1,'1896.442871','-1404.838256','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(345,'Nera','ForRent',0,0,30000,1,0,0,1,'1894.470458','-1406.663574','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(346,'Nera','ForRent',0,0,30000,0,0,0,1,'1894.560546','-1412.619873','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(347,'Nera','ForRent',0,0,30000,1,0,0,1,'1896.359130','-1417.108642','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(348,'Nera','ForRent',0,0,31000,1,0,0,1,'1898.549316','-1413.882812','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(349,'Nera','ForRent',0,0,28000,0,0,0,1,'1911.711914','-1423.182739','3184.448486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(350,'Nera','ForRent',0,0,27000,0,0,0,1,'1911.837524','-1429.772705','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(351,'Nera','ForRent',0,0,32000,0,0,0,1,'1913.674316','-1431.677612','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(352,'Nera','ForRent',0,0,30000,0,0,0,1,'1919.774047','-1431.692382','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(353,'Nera','ForRent',0,0,33000,0,0,0,1,'1924.191772','-1429.868164','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(354,'Nera','ForRent',0,0,28000,0,0,0,1,'1920.925170','-1427.563964','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(355,'Nera','ForRent',0,0,30000,1,0,0,1,'1914.671264','-1395.945556','3190.547119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(356,'Nera','ForRent',0,0,30000,1,0,0,1,'1914.563598','-1389.412475','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(357,'Nera','ForRent',0,0,30000,0,0,0,1,'1912.831909','-1387.282226','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(358,'Nera','ForRent',0,0,30000,1,0,0,1,'1906.520874','-1387.489135','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(359,'Nera','ForRent',0,0,30000,1,0,0,1,'1902.295898','-1389.501831','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(360,'Nera','ForRent',0,0,25000,1,0,0,1,'1905.471679','-1391.569580','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(361,'Nera','ForRent',0,0,23000,1,0,0,1,'1914.681152','-1389.229980','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(362,'Nera','ForRent',0,0,30000,1,0,0,1,'1912.812377','-1387.459228','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(363,'Nera','ForRent',0,0,32000,0,0,0,1,'1906.557861','-1387.564453','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(364,'Nera','ForRent',0,0,30000,1,0,0,1,'1902.284790','-1389.535522','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(365,'Nera','ForRent',0,0,70000,1,0,0,1,'1905.145507','-1391.548217','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(366,'Nera','ForRent',0,0,64200,0,0,0,1,'1913.214721','-1403.987182','3202.569335',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(367,'Nera','ForRent',0,0,32000,1,0,0,1,'1902.997802','-1404.806396','3173.523193',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(368,'Nera','ForRent',0,0,32000,0,0,0,1,'1896.580200','-1404.981689','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(369,'Nera','ForRent',0,0,32000,0,0,0,1,'1894.357910','-1406.593505','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(370,'Nera','ForRent',0,0,32000,1,0,0,1,'1894.579589','-1412.835571','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(371,'Nera','ForRent',0,0,80000,1,0,0,1,'1896.542114','-1417.008789','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(372,'Nera','ForRent',0,0,80000,1,0,0,1,'1898.618408','-1413.835693','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(373,'Nera','ForRent',0,0,30000,0,0,0,1,'1902.948120','-1404.816894','3179.198486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(374,'Nera','ForRent',0,0,30000,0,0,0,1,'1896.361572','-1404.837646','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(375,'Nera','ForRent',0,0,30000,1,0,0,1,'1894.465087','-1406.655273','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(376,'Nera','ForRent',0,0,30000,0,0,0,1,'1896.445068','-1417.106079','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(377,'Nera','ForRent',0,0,75000,0,0,0,1,'1898.550048','-1414.008422','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(378,'Nera','ForRent',0,0,28000,0,0,0,1,'1911.828857','-1429.785888','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(379,'Nera','ForRent',0,0,28000,1,0,0,1,'1913.631469','-1431.691894','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(380,'Nera','ForRent',0,0,28000,1,0,0,1,'1919.878051','-1431.689086','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(381,'Nera','ForRent',0,0,28000,1,0,0,1,'1924.193603','-1429.784301','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(382,'Nera','ForRent',0,0,25000,0,0,0,1,'1914.671020','-1395.873168','3190.547119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(383,'Nera','ForRent',0,0,25000,1,0,0,1,'1914.567016','-1389.400512','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(384,'Nera','ForRent',0,0,25000,0,0,0,1,'1912.721069','-1387.286865','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(385,'Nera','ForRent',0,0,70000,0,0,0,1,'1906.440795','-1387.484008','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(386,'Nera','ForRent',0,0,25000,1,0,0,1,'1902.300048','-1389.503295','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(387,'Nera','ForRent',0,0,70000,0,0,0,1,'1914.590820','-1395.945678','3196.297119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(388,'Nera','ForRent',0,0,70000,1,0,0,1,'1912.658447','-1387.455322','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(389,'Nera','ForRent',0,0,23000,1,0,0,1,'1906.681518','-1387.563720','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(390,'Nera','ForRent',0,0,23000,1,0,0,1,'1902.283691','-1389.397338','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(391,'Nera','ForRent',0,0,70000,0,0,0,1,'1905.455322','-1391.549926','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,2,14,-1),
(392,'Nera','ForRent',0,0,30000,0,0,0,1,'1914.673095','-1389.292236','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(393,'Nera','ForRent',0,0,32000,0,0,0,1,'1920.859863','-1427.564208','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(394,'Nera','ForRent',0,0,30000,0,0,0,1,'1894.563110','-1412.738037','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(395,'Nera','ForRent',0,0,30000,1,0,0,1,'1905.496337','-1391.578247','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(396,'Nera','ForRent',0,0,80000,0,0,0,1,'1903.021118','-1404.806030','3173.523193',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(397,'Nera','ForRent',0,0,30000,1,0,0,1,'1896.343627','-1404.818969','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(398,'Nera','ForRent',0,0,31000,1,0,0,1,'1894.354003','-1406.609863','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(399,'Nera','ForRent',0,0,31000,1,0,0,1,'1894.579101','-1412.809570','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(400,'Nera','ForRent',0,0,80000,1,0,0,1,'1896.559692','-1417.001220','3173.520019',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(401,'Nera','ForRent',0,0,30000,1,0,0,1,'1898.619506','-1413.982788','3173.527343',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(402,'Nera','ForRent',0,0,75000,0,0,0,1,'1902.955444','-1404.813598','3179.198486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(403,'Nera','ForRent',0,0,29000,1,0,0,1,'1896.351318','-1404.838989','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(404,'Nera','ForRent',0,0,29000,1,0,0,1,'1894.461669','-1406.570312','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(405,'Nera','ForRent',0,0,29000,1,0,0,1,'1894.569335','-1412.830688','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(406,'Nera','ForRent',0,0,29000,1,0,0,1,'1896.598510','-1417.104003','3179.195312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(407,'Nera','ForRent',0,0,29000,0,0,0,1,'1898.534667','-1413.840087','3179.202636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(408,'Nera','ForRent',0,0,27000,1,0,0,1,'1911.714477','-1423.188964','3184.448486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(409,'Nera','ForRent',0,0,27000,1,0,0,1,'1911.835327','-1429.759521','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(410,'Nera','ForRent',0,0,27000,1,0,0,1,'1913.663452','-1431.689086','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(411,'Nera','ForRent',0,0,27000,1,0,0,1,'1919.845458','-1431.692504','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(412,'Nera','ForRent',0,0,27000,1,0,0,1,'1924.192626','-1429.848999','3184.445312',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(413,'Nera','ForRent',0,0,27000,1,0,0,1,'1921.024780','-1427.561157','3184.452636',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(414,'Nera','ForRent',0,0,26000,1,0,0,1,'1914.670898','-1395.953491','3190.547119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(415,'Nera','ForRent',0,0,26000,0,0,0,1,'1914.563964','-1389.458251','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(416,'Nera','ForRent',0,0,26000,1,0,0,1,'1912.743530','-1387.286987','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(417,'Nera','ForRent',0,0,26000,0,0,0,1,'1906.541503','-1387.485351','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(418,'Nera','ForRent',0,0,26000,1,0,0,1,'1902.302368','-1389.492797','3190.543945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(419,'Nera','ForRent',0,0,26000,1,0,0,1,'1905.544433','-1391.579711','3190.551269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(420,'Nera','ForRent',0,0,70000,0,0,0,1,'1914.589477','-1395.906127','3196.297119',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(421,'Nera','ForRent',0,0,24000,0,0,0,1,'1914.678955','-1389.265991','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(422,'Nera','ForRent',0,0,70000,1,0,0,1,'1912.743164','-1387.458007','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(423,'Nera','ForRent',0,0,70000,0,0,0,1,'1906.565795','-1387.566162','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(424,'Nera','ForRent',0,0,70000,1,0,0,1,'1902.286132','-1389.505981','3196.293945',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(425,'Nera','ForRent',0,0,70000,1,0,0,1,'1905.322265','-1391.549926','3196.301269',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,3,14,-1),
(426,'Nera','ForRent',0,0,30000,0,0,0,1,'1911.790161','-1423.221801','3184.448486',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,1,14,-1),
(427,'Nera','ForRent',0,0,530000,1,0,0,1,'745.526367','-591.154296','18.012922',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'754.360412','-581.661560','17.521114','89.925720',0,0,14,-1),
(428,'Nera','ForRent',0,0,450000,1,0,0,1,'743.232177','-509.360626','18.012922',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'752.138488','-495.406127','17.521451','178.622665',0,0,14,-1),
(429,'Nera','ForRent',0,0,345000,0,0,0,1,'745.147705','-556.553039','18.012926',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'750.512878','-551.317504','17.407062','2.128055',0,0,14,-1),
(430,'Nera','ForRent',0,0,278000,1,0,0,1,'736.661010','-556.694519','18.012926',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(431,'Nera','ForRent',0,0,383400,1,0,0,1,'768.255615','-503.741088','18.012926',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'762.812255','-508.291839','17.425622','182.133804',0,0,14,-1),
(432,'Nera','ForRent',0,0,280000,1,0,0,1,'776.787841','-503.481079','18.012926',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(433,'Nera','ForRent',0,0,469300,1,0,0,1,'766.581420','-556.782592','18.012924',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'772.022705','-552.932434','17.457960','358.185424',0,0,14,-1),
(434,'Nera','ForRent',0,0,423430,0,0,0,1,'795.025390','-506.368255','18.012922',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(435,'Nera','ForRent',0,0,552400,1,0,0,1,'818.369934','-509.567474','18.012922',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'827.670654','-496.275451','17.516853','182.026733',0,0,14,-1),
(436,'Nera','ForRent',0,0,486900,1,0,0,1,'1029.340454','-1940.438232','13.759815',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1033.445068','-1946.174560','12.811528','262.412689',0,0,14,-1),
(437,'Nera','ForRent',0,0,260000,0,0,0,1,'1028.150268','-1954.326660','13.331192',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1031.355346','-1961.058837','12.814179','263.573394',0,0,14,-1),
(438,'Nera','ForRent',0,0,408700,1,0,0,1,'1024.683227','-1969.451171','13.759662',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1029.083984','-1974.837036','12.812786','262.717407',0,0,14,-1),
(439,'Nera','ForRent',0,0,270000,0,0,0,1,'1023.471374','-1983.160156','13.760034',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1027.710937','-1989.055541','12.812904','263.134704',0,0,14,-1),
(440,'Nera','ForRent',0,0,250000,1,0,0,1,'1022.880249','-1997.700439','13.247702',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1025.714355','-2004.059326','12.813369','264.919708',0,0,14,-1),
(441,'Nera','ForRent',0,0,270000,1,0,0,1,'1019.613830','-2012.552001','13.760076',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1024.092895','-2018.043212','12.813090','265.183532',0,0,14,-1),
(442,'Nera','ForRent',0,0,420100,1,0,0,1,'1018.004882','-2026.294067','13.760211',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,'1022.338012','-2032.207031','12.812969','264.554077',0,0,14,-1),
(443,'Nera','ForRent',0,0,46900,1,0,0,1,'2437.856689','-2020.473876','13.902541',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(444,'Nera','ForRent',0,0,57900,1,0,0,1,'2464.815917','-1995.944702','13.688860',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(445,'Nera','ForRent',0,0,42800,0,0,0,1,'2465.347656','-2020.793457','14.124163',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(446,'Nera','ForRent',0,0,53200,0,0,0,1,'2483.520019','-1995.369018','13.834323',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(447,'Nera','ForRent',0,0,21900,1,0,0,1,'2486.442138','-2021.319091','13.998847',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(448,'Nera','ForRent',0,0,39900,1,0,0,1,'2508.291015','-1998.364746','13.902541',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(449,'Nera','ForRent',0,0,40600,1,0,0,1,'2507.828369','-2020.546997','14.210101',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(450,'Nera','ForRent',0,0,47300,0,0,0,1,'2524.093017','-1998.588500','13.782610',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(451,'Nera','ForRent',0,0,42500,1,0,0,1,'2522.462890','-2019.075561','14.074416',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(452,'Nera','ForRent',0,0,27200,1,0,0,1,'704.156494','-680.736572','16.201381',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(453,'Nera','ForRent',0,0,54600,0,0,0,1,'718.906188','-684.283569','17.120265',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(454,'Nera','ForRent',0,0,27300,0,0,0,1,'726.984619','-671.997375','16.351116',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(455,'Nera','ForRent',0,0,44800,0,0,0,1,'712.060302','-649.934326','15.974402',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(456,'Nera','ForRent',0,0,32400,1,0,0,1,'721.126281','-637.907104','15.561620',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(457,'Nera','ForRent',0,0,53800,0,0,0,1,'730.729675','-642.978088','15.508620',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(458,'Nera','ForRent',0,0,31300,1,0,0,1,'737.089172','-654.673522','15.796620',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(459,'Nera','ForRent',0,0,587500,0,0,0,1,'1051.008056','-1058.764404','34.796646',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1040.604492','-1053.911621','31.359464','358.929168',0,0,14,-1),
(460,'Nera','ForRent',0,0,487900,1,0,0,1,'993.905090','-1058.097045','33.703125',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1004.410034','-1053.719116','30.670736','0.111166',0,0,14,-1),
(461,'Nera','ForRent',0,0,509000,0,0,0,1,'1118.063232','-1022.313476','34.992187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1108.103027','-1026.346069','31.599229','180.641571',0,0,14,-1),
(462,'Nera','ForRent',0,0,556800,0,0,0,1,'1127.976928','-1022.966552','34.992187',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,'1137.976928','-1025.461425','31.559020','179.161758',0,0,14,-1),
(463,'Nera','ForRent',0,0,9999999,0,0,0,1,'-1427.031738','2171.166503','50.625000',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(464,'Nera','ForRent',0,0,420000,1,0,0,1,'1973.679931','-1314.711547','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1968.868774','-1314.713256','23.733079','359.403900',0,0,14,-1),
(465,'Nera','ForRent',0,0,333311,1,0,0,1,'1999.544189','-1287.192260','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2004.325805','-1287.132812','23.747072','181.347122',0,0,14,-1),
(466,'Nera','ForRent',0,0,700000,1,0,0,1,'1998.728271','-1314.958251','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1994.009643','-1315.466918','23.747083','1.028885',0,0,14,-1),
(467,'Nera','ForRent',0,0,340000,1,0,0,1,'2023.716064','-1314.897949','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2018.954589','-1314.568481','23.746969','359.955780',0,0,14,-1),
(468,'Nera','ForRent',0,0,300000,0,0,0,1,'2024.584716','-1286.851562','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2029.060058','-1287.221191','23.746850','178.867370',0,0,14,-1),
(469,'Nera','ForRent',0,0,310000,0,0,0,1,'2049.564453','-1286.991699','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2054.395019','-1287.005615','23.747077','181.061096',0,0,14,-1),
(470,'Nera','ForRent',0,0,750000,1,0,0,1,'2048.782470','-1315.181884','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'2043.853515','-1315.480712','23.746099','359.402404',0,0,14,-1),
(471,'Nera','ForRent',0,0,350000,1,0,0,1,'1974.628051','-1286.832397','24.664375',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,'1979.302490','-1287.173828','23.759189','180.000000',0,0,14,-1),
(472,'Nera','ForRent',0,0,0,1,0,0,1,'-683.993835','939.585876','13.632812',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(473,'Nera','ForRent',0,0,574500,0,0,0,1,'-691.728210','939.535705','13.632812',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,-1),
(475,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.936279','-1183.083129','49.323734',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,2),
(476,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.937988','-1183.062255','54.515663',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,3),
(477,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.937988','-1183.054565','59.724231',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,4),
(478,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.937744','-1183.056152','38.914100',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,0),
(479,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.871704','-1183.053710','44.120239',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,1),
(480,'Nera','ForRent',0,0,1000000,1,0,0,1,'1178.937988','-1183.075683','64.914100',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,5),
(481,'Nera','ForRent',0,0,1000000,0,0,0,1,'1178.937988','-1183.084228','70.117225',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,6),
(482,'Nera','ForRent',0,0,2000000,1,0,0,1,'1178.937988','-1183.064331','75.312538',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,7),
(483,'Nera','ForRent',0,0,5000000,0,0,0,1,'1178.937866','-1183.085205','80.510589',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,8),
(484,'Nera','ForRent',0,0,1000000,0,0,0,1,'289.944000','-1612.403564','47.001365',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,9),
(485,'Nera','ForRent',0,0,1000000,1,0,0,1,'289.948669','-1612.403686','51.502464',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,10),
(486,'Nera','ForRent',0,0,1000000,1,0,0,1,'289.959869','-1612.406005','56.003562',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,11),
(487,'Nera','ForRent',0,0,1000000,0,0,0,1,'289.968841','-1612.407958','60.504665',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,12),
(488,'Nera','ForRent',0,0,1000000,1,0,0,1,'289.955535','-1612.405151','65.005767',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,13),
(489,'Nera','ForRent',0,0,1000000,1,0,0,1,'289.960052','-1612.405517','69.506858',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,14),
(490,'Nera','ForRent',0,0,1000000,1,0,0,1,'289.945404','-1612.403442','73.992332',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,15),
(491,'Nera','ForRent',0,0,2000000,1,0,0,1,'289.959472','-1612.407104','78.493431',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,16),
(492,'Nera','ForRent',0,0,2000000,1,0,0,1,'289.944396','-1612.405639','82.994529',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,17),
(493,'Nera','ForRent',0,0,2000000,1,0,0,1,'289.963745','-1612.406250','87.495628',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,18),
(494,'Nera','ForRent',0,0,2000000,1,0,0,1,'289.955657','-1612.405029','91.996726',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,19),
(495,'Nera','ForRent',0,0,5000000,1,0,0,1,'289.948974','-1612.403442','96.497825',0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,'0','0','0','0',0,0,14,20);
/*!40000 ALTER TABLE `Namai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `NarkTrade`
--

DROP TABLE IF EXISTS `NarkTrade`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `NarkTrade` (
  `busid` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `price` int(11) DEFAULT NULL,
  `amount` int(11) DEFAULT NULL,
  PRIMARY KEY (`busid`,`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `NarkTrade`
--

LOCK TABLES `NarkTrade` WRITE;
/*!40000 ALTER TABLE `NarkTrade` DISABLE KEYS */;
/*!40000 ALTER TABLE `NarkTrade` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Orders`
--

DROP TABLE IF EXISTS `Orders`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Orders` (
  `orderid` int(25) NOT NULL AUTO_INCREMENT,
  `from` varchar(25) DEFAULT NULL,
  `type` tinyint(11) DEFAULT NULL,
  `forid` int(11) DEFAULT NULL,
  `amount` int(11) DEFAULT NULL,
  `status` tinyint(4) DEFAULT 0,
  `takenby` varchar(25) DEFAULT NULL,
  `date` datetime DEFAULT NULL,
  PRIMARY KEY (`orderid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Orders`
--

LOCK TABLES `Orders` WRITE;
/*!40000 ALTER TABLE `Orders` DISABLE KEYS */;
/*!40000 ALTER TABLE `Orders` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pastas`
--

DROP TABLE IF EXISTS `Pastas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Pastas` (
  `Vardas` varchar(255) NOT NULL DEFAULT '',
  `Email` varchar(255) DEFAULT NULL,
  `Confirmation` varchar(255) DEFAULT NULL,
  `Confirmed` int(2) DEFAULT 0,
  `NewEmail` varchar(50) DEFAULT NULL,
  `ChangeDate` datetime DEFAULT NULL,
  PRIMARY KEY (`Vardas`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pastas`
--

LOCK TABLES `Pastas` WRITE;
/*!40000 ALTER TABLE `Pastas` DISABLE KEYS */;
/*!40000 ALTER TABLE `Pastas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Patruliai`
--

DROP TABLE IF EXISTS `Patruliai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Patruliai` (
  `Name` varchar(255) DEFAULT '30',
  `X` float DEFAULT NULL,
  `Y` float DEFAULT NULL,
  `Range` float DEFAULT NULL,
  `Max` int(11) DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Patruliai`
--

LOCK TABLES `Patruliai` WRITE;
/*!40000 ALTER TABLE `Patruliai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Patruliai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pelnai`
--

DROP TABLE IF EXISTS `Pelnai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Pelnai` (
  `ID` smallint(6) NOT NULL DEFAULT 0,
  `Suma` int(11) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pelnai`
--

LOCK TABLES `Pelnai` WRITE;
/*!40000 ALTER TABLE `Pelnai` DISABLE KEYS */;
INSERT INTO `Pelnai` VALUES
(0,0),
(1,0),
(2,0),
(3,0),
(4,0),
(5,0),
(6,0),
(7,0),
(8,0),
(9,0),
(10,0),
(11,0),
(12,0),
(13,0),
(14,0),
(15,0),
(16,0),
(17,0),
(18,0),
(19,0),
(20,0),
(21,0),
(22,0),
(23,0),
(24,0),
(25,0),
(26,0),
(27,0),
(28,0),
(29,0),
(30,0),
(31,0),
(32,0),
(33,0),
(34,0),
(35,0),
(36,0),
(37,0),
(38,0),
(39,0),
(40,0),
(41,0),
(42,0),
(43,0),
(44,0),
(45,0),
(46,0),
(47,0),
(48,0),
(49,0),
(50,0),
(51,0),
(52,0),
(53,0),
(54,0),
(55,0),
(56,0),
(57,0),
(58,0),
(59,0),
(60,0),
(61,0),
(62,0),
(63,0),
(64,0),
(65,0),
(66,0),
(67,0),
(68,0),
(69,0),
(70,0),
(71,0),
(72,0),
(73,0),
(74,0),
(75,0),
(76,0),
(77,0),
(78,0),
(79,0),
(80,0),
(81,0),
(82,0),
(83,0),
(84,0),
(85,0),
(86,0),
(87,0),
(88,0),
(89,0),
(90,0),
(91,0),
(92,0),
(93,0),
(94,0),
(95,0),
(96,0),
(97,0),
(98,0),
(99,0);
/*!40000 ALTER TABLE `Pelnai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pending`
--

DROP TABLE IF EXISTS `Pending`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Pending` (
  `Name` varchar(24) NOT NULL DEFAULT '',
  `Admin` varchar(24) DEFAULT NULL,
  `Reason` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pending`
--

LOCK TABLES `Pending` WRITE;
/*!40000 ALTER TABLE `Pending` DISABLE KEYS */;
/*!40000 ALTER TABLE `Pending` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Permabans`
--

DROP TABLE IF EXISTS `Permabans`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Permabans` (
  `address` varchar(50) NOT NULL,
  `player` varchar(50) DEFAULT NULL,
  `reason` varchar(255) DEFAULT NULL,
  `time` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`address`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Permabans`
--

LOCK TABLES `Permabans` WRITE;
/*!40000 ALTER TABLE `Permabans` DISABLE KEYS */;
/*!40000 ALTER TABLE `Permabans` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Phones`
--

DROP TABLE IF EXISTS `Phones`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Phones` (
  `Vardas` char(25) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT '',
  `Numeris` varchar(50) NOT NULL,
  `IP` varchar(50) NOT NULL DEFAULT '',
  `Patvirtinta` int(11) NOT NULL DEFAULT 0,
  `Kodas` int(11) NOT NULL DEFAULT 0,
  `Data` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`Vardas`),
  KEY `Numeris` (`Numeris`),
  KEY `IP` (`IP`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Phones`
--

LOCK TABLES `Phones` WRITE;
/*!40000 ALTER TABLE `Phones` DISABLE KEYS */;
/*!40000 ALTER TABLE `Phones` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `PlayerKVS`
--

DROP TABLE IF EXISTS `PlayerKVS`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `PlayerKVS` (
  `Vardas` varchar(25) NOT NULL,
  `Key` varchar(100) NOT NULL,
  `Value` varchar(512) DEFAULT NULL,
  PRIMARY KEY (`Vardas`,`Key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `PlayerKVS`
--

LOCK TABLES `PlayerKVS` WRITE;
/*!40000 ALTER TABLE `PlayerKVS` DISABLE KEYS */;
/*!40000 ALTER TABLE `PlayerKVS` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Registrations`
--

DROP TABLE IF EXISTS `Registrations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Registrations` (
  `Name` varchar(50) NOT NULL DEFAULT '',
  `Ip` varchar(50) NOT NULL DEFAULT '',
  `Diskid` varchar(50) NOT NULL,
  `Time` datetime NOT NULL,
  `Unique` int(11) NOT NULL,
  PRIMARY KEY (`Name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Registrations`
--

LOCK TABLES `Registrations` WRITE;
/*!40000 ALTER TABLE `Registrations` DISABLE KEYS */;
/*!40000 ALTER TABLE `Registrations` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Rekordas`
--

DROP TABLE IF EXISTS `Rekordas`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Rekordas` (
  `Rekordas` int(11) NOT NULL DEFAULT 0,
  `Data` datetime DEFAULT NULL,
  `Pagerino` varchar(26) DEFAULT NULL,
  PRIMARY KEY (`Rekordas`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Rekordas`
--

LOCK TABLES `Rekordas` WRITE;
/*!40000 ALTER TABLE `Rekordas` DISABLE KEYS */;
/*!40000 ALTER TABLE `Rekordas` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `RemindPassword`
--

DROP TABLE IF EXISTS `RemindPassword`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `RemindPassword` (
  `Vardas` varchar(255) DEFAULT NULL,
  `Kodas` varchar(255) DEFAULT NULL,
  `Data` datetime DEFAULT NULL,
  `Ip` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `RemindPassword`
--

LOCK TABLES `RemindPassword` WRITE;
/*!40000 ALTER TABLE `RemindPassword` DISABLE KEYS */;
/*!40000 ALTER TABLE `RemindPassword` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Sandeliai`
--

DROP TABLE IF EXISTS `Sandeliai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Sandeliai` (
  `Numeris` int(11) NOT NULL DEFAULT 0,
  `Priklauso` int(11) DEFAULT NULL,
  `Atvezta` int(11) DEFAULT NULL,
  `Bomba` int(11) DEFAULT 0,
  PRIMARY KEY (`Numeris`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Sandeliai`
--

LOCK TABLES `Sandeliai` WRITE;
/*!40000 ALTER TABLE `Sandeliai` DISABLE KEYS */;
INSERT INTO `Sandeliai` VALUES
(0,-1,0,0),
(1,-1,0,0),
(2,-1,0,0),
(3,-1,0,0),
(4,-1,0,0),
(5,-1,0,0);
/*!40000 ALTER TABLE `Sandeliai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Saudykla`
--

DROP TABLE IF EXISTS `Saudykla`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Saudykla` (
  `Vardas` varchar(25) NOT NULL,
  `Saudykla` int(11) NOT NULL,
  `Laikas` int(11) DEFAULT NULL,
  `Ginklas` int(11) NOT NULL,
  `Data` datetime DEFAULT NULL,
  `Pataikymas` float DEFAULT NULL,
  PRIMARY KEY (`Vardas`,`Saudykla`,`Ginklas`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Saudykla`
--

LOCK TABLES `Saudykla` WRITE;
/*!40000 ALTER TABLE `Saudykla` DISABLE KEYS */;
/*!40000 ALTER TABLE `Saudykla` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `SaveVehicles`
--

DROP TABLE IF EXISTS `SaveVehicles`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `SaveVehicles` (
  `vehicleid` int(11) NOT NULL DEFAULT 0,
  `X` varchar(255) DEFAULT NULL,
  `Y` varchar(255) DEFAULT NULL,
  `Z` varchar(255) DEFAULT NULL,
  `A` varchar(255) DEFAULT NULL,
  `pakrauta` int(11) DEFAULT NULL,
  `krovinys` int(11) DEFAULT NULL,
  `vmp` int(11) DEFAULT NULL,
  `vak` int(11) DEFAULT NULL,
  `vdgl` int(11) DEFAULT NULL,
  `vawp` int(11) DEFAULT NULL,
  `vkurjeriams` int(11) DEFAULT NULL,
  PRIMARY KEY (`vehicleid`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `SaveVehicles`
--

LOCK TABLES `SaveVehicles` WRITE;
/*!40000 ALTER TABLE `SaveVehicles` DISABLE KEYS */;
/*!40000 ALTER TABLE `SaveVehicles` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Siena`
--

DROP TABLE IF EXISTS `Siena`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Siena` (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(50) NOT NULL DEFAULT '0',
  `Color` varchar(50) NOT NULL DEFAULT '0',
  `Date` datetime NOT NULL DEFAULT '0000-00-00 00:00:00',
  PRIMARY KEY (`sid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Siena`
--

LOCK TABLES `Siena` WRITE;
/*!40000 ALTER TABLE `Siena` DISABLE KEYS */;
/*!40000 ALTER TABLE `Siena` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Spalvos`
--

DROP TABLE IF EXISTS `Spalvos`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Spalvos` (
  `Vardas` varchar(255) NOT NULL DEFAULT '',
  `Color` varchar(255) DEFAULT NULL,
  `Set` int(11) DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Spalvos`
--

LOCK TABLES `Spalvos` WRITE;
/*!40000 ALTER TABLE `Spalvos` DISABLE KEYS */;
/*!40000 ALTER TABLE `Spalvos` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Spinta`
--

DROP TABLE IF EXISTS `Spinta`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Spinta` (
  `Vardas` varchar(255) NOT NULL DEFAULT '',
  `Skin` smallint(6) NOT NULL DEFAULT 0,
  `LastUsed` datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Spinta`
--

LOCK TABLES `Spinta` WRITE;
/*!40000 ALTER TABLE `Spinta` DISABLE KEYS */;
/*!40000 ALTER TABLE `Spinta` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Stiliai`
--

DROP TABLE IF EXISTS `Stiliai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Stiliai` (
  `Vardas` varchar(30) DEFAULT NULL,
  `Stilius` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Stiliai`
--

LOCK TABLES `Stiliai` WRITE;
/*!40000 ALTER TABLE `Stiliai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Stiliai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tags`
--

DROP TABLE IF EXISTS `Tags`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tags` (
  `ID` int(11) NOT NULL DEFAULT 0,
  `Gang` int(11) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tags`
--

LOCK TABLES `Tags` WRITE;
/*!40000 ALTER TABLE `Tags` DISABLE KEYS */;
INSERT INTO `Tags` VALUES
(0,-1),
(1,-1),
(2,-1),
(3,-1),
(4,-1),
(5,-1),
(6,-1),
(7,-1),
(8,-1),
(9,-1),
(10,-1),
(11,-1),
(12,-1),
(13,-1),
(14,-1),
(15,-1),
(16,-1),
(17,-1),
(18,-1),
(19,-1),
(20,-1),
(21,-1),
(22,-1),
(23,-1),
(24,-1),
(25,-1),
(26,-1),
(27,-1),
(28,-1),
(29,-1);
/*!40000 ALTER TABLE `Tags` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `TaskQueue`
--

DROP TABLE IF EXISTS `TaskQueue`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `TaskQueue` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `task` varchar(50) DEFAULT NULL,
  `name` varchar(50) DEFAULT NULL,
  `message` text CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `status` tinyint(4) DEFAULT 0,
  `created` timestamp NULL DEFAULT NULL,
  `last_updated` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `status` (`status`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `TaskQueue`
--

LOCK TABLES `TaskQueue` WRITE;
/*!40000 ALTER TABLE `TaskQueue` DISABLE KEYS */;
/*!40000 ALTER TABLE `TaskQueue` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Textures`
--

DROP TABLE IF EXISTS `Textures`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Textures` (
  `houseid` int(11) NOT NULL,
  `isdoor` int(11) NOT NULL,
  `matid` int(11) NOT NULL,
  `tid` int(11) DEFAULT NULL,
  PRIMARY KEY (`houseid`,`isdoor`,`matid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Textures`
--

LOCK TABLES `Textures` WRITE;
/*!40000 ALTER TABLE `Textures` DISABLE KEYS */;
/*!40000 ALTER TABLE `Textures` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Traffic`
--

DROP TABLE IF EXISTS `Traffic`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Traffic` (
  `x` varchar(255) DEFAULT NULL,
  `y` varchar(255) DEFAULT NULL,
  `z` varchar(255) DEFAULT NULL,
  `rz` varchar(255) DEFAULT NULL,
  `text` varchar(255) DEFAULT NULL,
  `type` int(11) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Traffic`
--

LOCK TABLES `Traffic` WRITE;
/*!40000 ALTER TABLE `Traffic` DISABLE KEYS */;
/*!40000 ALTER TABLE `Traffic` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Tyrimai`
--

DROP TABLE IF EXISTS `Tyrimai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Tyrimai` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` int(11) NOT NULL DEFAULT 0,
  `status` int(11) NOT NULL DEFAULT 0,
  `ticks_done` int(11) NOT NULL DEFAULT 0,
  `ticks_total` int(11) NOT NULL DEFAULT 0,
  `started_by` varchar(50) NOT NULL,
  `start_time` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Tyrimai`
--

LOCK TABLES `Tyrimai` WRITE;
/*!40000 ALTER TABLE `Tyrimai` DISABLE KEYS */;
/*!40000 ALTER TABLE `Tyrimai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Updates`
--

DROP TABLE IF EXISTS `Updates`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Updates` (
  `Versija` varchar(30) NOT NULL DEFAULT 'LSG',
  `Data` varchar(30) NOT NULL DEFAULT '',
  `Atnaujinimas` varchar(3000) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`Versija`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Updates`
--

LOCK TABLES `Updates` WRITE;
/*!40000 ALTER TABLE `Updates` DISABLE KEYS */;
/*!40000 ALTER TABLE `Updates` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Whitelist`
--

DROP TABLE IF EXISTS `Whitelist`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Whitelist` (
  `Name` varchar(255) DEFAULT NULL,
  `Ip` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Whitelist`
--

LOCK TABLES `Whitelist` WRITE;
/*!40000 ALTER TABLE `Whitelist` DISABLE KEYS */;
/*!40000 ALTER TABLE `Whitelist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `WorldObjects`
--

DROP TABLE IF EXISTS `WorldObjects`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `WorldObjects` (
  `worldid` int(11) NOT NULL,
  `slotid` int(11) NOT NULL,
  `data` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin NOT NULL,
  PRIMARY KEY (`worldid`,`slotid`) USING BTREE,
  CONSTRAINT `FK__Worlds` FOREIGN KEY (`worldid`) REFERENCES `Worlds` (`id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `WorldObjects`
--

LOCK TABLES `WorldObjects` WRITE;
/*!40000 ALTER TABLE `WorldObjects` DISABLE KEYS */;
/*!40000 ALTER TABLE `WorldObjects` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Worlds`
--

DROP TABLE IF EXISTS `Worlds`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `Worlds` (
  `id` int(11) NOT NULL,
  `houseid` int(11) DEFAULT NULL,
  `worldid` int(11) DEFAULT NULL,
  `data` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_bin DEFAULT NULL,
  `objects` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Worlds`
--

LOCK TABLES `Worlds` WRITE;
/*!40000 ALTER TABLE `Worlds` DISABLE KEYS */;
/*!40000 ALTER TABLE `Worlds` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `baldai`
--

DROP TABLE IF EXISTS `baldai`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `baldai` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `houseid` int(11) DEFAULT NULL,
  `obj` int(11) DEFAULT NULL,
  `x` float DEFAULT NULL,
  `y` float DEFAULT NULL,
  `z` float DEFAULT NULL,
  `rotx` float DEFAULT NULL,
  `roty` float DEFAULT NULL,
  `rotz` float DEFAULT NULL,
  `cat` int(11) DEFAULT 0,
  PRIMARY KEY (`id`),
  KEY `house` (`houseid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `baldai`
--

LOCK TABLES `baldai` WRITE;
/*!40000 ALTER TABLE `baldai` DISABLE KEYS */;
/*!40000 ALTER TABLE `baldai` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `baldai_cat`
--

DROP TABLE IF EXISTS `baldai_cat`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `baldai_cat` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pav` varchar(255) DEFAULT NULL,
  `rusis` int(11) DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=149 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `baldai_cat`
--

LOCK TABLES `baldai_cat` WRITE;
/*!40000 ALTER TABLE `baldai_cat` DISABLE KEYS */;
INSERT INTO `baldai_cat` VALUES
(0,'Lovos',0),
(1,'Sofos',0),
(2,'Foteliai',0),
(3,'Kedes',0),
(4,'Stalai',0),
(5,'Spintos',0),
(14,'Kilimai',2),
(7,'Uzuolaidos',2),
(8,'Paveikslai',2),
(9,'Televizoriai',1),
(10,'Kompiuteriai',1),
(11,'Audio sistemos',1),
(12,'Skalbimo masinos',1),
(13,'Dovanos',3),
(6,'Virtuves spinteles',0),
(15,'Saldytuvai',1),
(16,'Virykles',1),
(17,'Mikrobangu krosneles',1),
(18,'Kavos stalai',0),
(19,'Knygos ir zurnalai',2),
(20,'Zaidimai',2),
(21,'Augalai',2),
(24,'Rasomieji stalai',0),
(25,'Tualetai',0),
(26,'Vonios',0),
(27,'Dusai',0),
(28,'Kriaukles',0),
(22,'Sviestuvai',1),
(31,'Indai',2),
(29,'Vaizdo grotuvai',1),
(30,'Zaidimu konsoles',1),
(23,'Zvakes',2),
(32,'Sporto prekes',2),
(34,'Telefonai',1),
(35,'Siuksliadezes',0),
(36,'Zidiniai',2),
(37,'Durys',0);
/*!40000 ALTER TABLE `baldai_cat` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `baldai_id`
--

DROP TABLE IF EXISTS `baldai_id`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `baldai_id` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `cat` int(11) DEFAULT NULL,
  `obj` int(11) DEFAULT NULL,
  `kaina` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=532 DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci ROW_FORMAT=DYNAMIC;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `baldai_id`
--

LOCK TABLES `baldai_id` WRITE;
/*!40000 ALTER TABLE `baldai_id` DISABLE KEYS */;
INSERT INTO `baldai_id` VALUES
(1,0,1793,1000),
(2,0,14446,3000),
(3,0,2575,3000),
(4,0,2566,3000),
(5,0,2563,3000),
(6,0,2302,1500),
(7,0,2301,1700),
(8,0,2300,1700),
(9,0,2299,2300),
(10,0,2298,2300),
(11,0,2090,1900),
(12,0,1812,600),
(13,0,1803,2300),
(14,0,1802,2000),
(15,0,1801,1500),
(16,0,1799,1900),
(17,0,1797,1500),
(18,0,1745,1400),
(19,0,1725,1200),
(20,0,1700,1200),
(21,1,1712,500),
(22,1,2290,1400),
(23,1,1768,1000),
(24,1,1766,600),
(25,1,1764,700),
(26,1,1763,600),
(27,1,1761,800),
(28,1,1760,900),
(29,1,1757,800),
(30,1,1713,1000),
(31,1,1710,2000),
(32,1,1709,2300),
(33,1,1706,1100),
(34,1,1703,1400),
(35,1,1702,1400),
(36,2,1671,500),
(37,2,1704,900),
(38,2,1705,900),
(39,2,1708,900),
(40,2,1711,800),
(41,2,1714,500),
(42,2,1735,1000),
(43,2,2096,800),
(44,2,2356,400),
(142,3,2121,150),
(143,3,2788,200),
(144,3,2636,200),
(145,3,1720,250),
(146,3,1811,300),
(147,3,1739,500),
(80,4,1770,700),
(81,4,2118,1000),
(82,4,2117,900),
(83,4,2115,800),
(84,4,2112,800),
(85,4,2111,1000),
(140,3,2125,100),
(141,3,2350,100),
(86,4,2110,800),
(87,4,2109,700),
(88,4,2032,800),
(89,4,2031,800),
(90,4,2030,1000),
(91,4,2119,900),
(92,5,2140,800),
(93,5,1743,800),
(94,5,1742,700),
(95,5,2708,1000),
(96,5,2576,1000),
(97,5,2329,900),
(98,5,2328,300),
(99,5,2323,700),
(100,5,2167,500),
(101,5,2145,1000),
(102,5,2089,800),
(103,5,2025,1300),
(104,6,2151,1000),
(105,6,2152,800),
(106,6,2128,800),
(107,6,2129,800),
(108,6,2140,1000),
(109,6,2139,800),
(110,6,2137,900),
(111,6,15036,6000),
(112,6,2158,1000),
(113,6,2160,800),
(114,6,2157,500),
(115,18,1823,300),
(116,18,1821,200),
(117,18,1820,200),
(118,18,1819,400),
(119,18,1818,500),
(120,18,1814,500),
(121,18,1816,300),
(122,18,1815,500),
(123,24,2169,700),
(124,24,2205,1000),
(125,24,2180,200),
(126,24,2173,500),
(127,24,2171,500),
(128,24,2175,500),
(129,25,2521,100),
(130,25,2525,300),
(131,25,2514,300),
(132,25,2528,500),
(133,26,2526,1000),
(134,27,2527,500),
(135,27,2520,700),
(136,27,2517,1000),
(137,28,2523,300),
(138,28,2518,300),
(139,28,2524,500),
(148,3,2124,500),
(149,3,2079,400),
(150,22,2726,100),
(151,22,2238,100),
(152,22,2105,100),
(153,22,2106,100),
(154,22,2239,300),
(155,22,2108,300),
(156,22,2069,300),
(157,9,2224,200),
(158,9,1747,250),
(159,9,1748,300),
(160,9,1749,350),
(161,9,1750,400),
(162,9,1751,450),
(163,9,1429,500),
(164,9,2312,550),
(165,9,2316,600),
(166,9,1786,650),
(167,9,1518,700),
(168,10,2190,500),
(169,11,2232,700),
(170,11,2231,200),
(171,11,2230,250),
(172,11,2229,500),
(173,11,2099,700),
(174,11,2100,700),
(175,11,2226,100),
(176,11,2103,200),
(177,11,1809,300),
(178,11,2102,100),
(179,12,1208,200),
(180,15,2147,200),
(181,15,2131,600),
(182,15,2127,600),
(183,16,2135,700),
(184,16,2144,200),
(185,16,2294,700),
(186,16,2417,500),
(187,16,2339,400),
(188,17,2149,300),
(189,17,2421,500),
(190,29,1782,400),
(191,29,1783,400),
(192,29,1787,400),
(193,29,1788,500),
(194,29,1785,700),
(195,30,2028,500),
(196,30,1719,200),
(197,30,1718,100),
(199,7,2558,200),
(200,7,2559,200),
(201,7,2560,400),
(202,7,2561,400),
(203,14,1828,1500),
(204,14,2815,200),
(205,14,2817,150),
(206,14,2818,150),
(207,14,2833,500),
(208,14,2834,400),
(209,14,2835,300),
(210,14,2836,200),
(211,14,2841,300),
(212,14,2842,300),
(213,14,2847,200),
(214,19,2853,100),
(215,19,2855,70),
(216,19,2827,50),
(217,19,2854,70),
(218,19,2852,50),
(219,19,2813,200),
(220,19,2816,50),
(221,20,2484,500),
(222,21,2245,100),
(223,21,2244,100),
(224,21,2241,150),
(225,21,2240,150),
(226,21,2195,200),
(227,21,948,100),
(228,21,949,200),
(229,21,2251,50),
(230,21,2252,50),
(231,21,2253,100),
(232,21,2811,250),
(233,21,2011,300),
(235,21,2001,300),
(236,31,2865,300),
(237,31,2864,300),
(238,31,2863,300),
(239,31,2862,300),
(240,31,2848,100),
(241,31,2849,100),
(242,31,2850,100),
(243,31,2851,100),
(244,23,2868,100),
(245,23,2869,100),
(246,8,2255,200),
(247,8,2256,200),
(248,8,2257,200),
(249,8,2258,200),
(250,8,2259,200),
(251,8,2260,200),
(252,8,2261,200),
(253,8,2262,200),
(254,8,2263,200),
(255,8,2264,200),
(256,8,2265,2000),
(257,8,2266,200),
(258,8,2267,200),
(259,8,2268,200),
(260,8,2269,200),
(261,8,2270,200),
(262,8,2271,200),
(263,8,2272,200),
(264,8,2273,200),
(265,8,2274,200),
(266,8,2275,200),
(267,8,2276,200),
(268,8,2277,200),
(269,8,2278,200),
(270,8,2279,200),
(271,8,2280,200),
(272,8,2281,200),
(273,8,2282,200),
(274,8,2283,200),
(275,8,2284,200),
(276,8,2285,200),
(277,8,2286,200),
(278,8,2287,200),
(279,8,2288,200),
(280,8,2289,200),
(281,31,1520,200),
(282,31,1455,200),
(283,31,1484,200),
(284,31,1486,200),
(285,31,1510,200),
(286,31,1512,200),
(287,31,1543,200),
(288,31,1544,400),
(289,31,1546,200),
(290,31,1664,900),
(291,31,1665,900),
(292,22,2026,500),
(293,22,1734,800),
(294,22,2073,800),
(295,32,2916,400),
(296,32,2915,600),
(297,32,2913,800),
(298,32,2627,2000),
(299,32,2628,2000),
(300,32,2629,1000),
(301,32,2630,2000),
(302,32,2631,600),
(303,32,2632,600),
(304,11,1954,8000),
(305,11,1961,200),
(306,11,1960,200),
(307,11,1962,200),
(308,11,1958,1200),
(309,13,19474,100),
(310,13,1925,100),
(311,13,1926,100),
(312,13,1924,100),
(313,13,1923,100),
(314,13,1667,100),
(315,13,2964,100),
(316,13,3004,100),
(317,13,3003,100),
(318,13,3002,100),
(319,13,3101,100),
(320,13,2995,100),
(321,13,2996,100),
(322,13,3106,100),
(323,13,3105,100),
(324,13,3103,100),
(325,13,3001,100),
(326,13,3100,100),
(327,13,2997,100),
(328,13,3000,100),
(329,13,3102,100),
(330,13,2999,100),
(331,13,2998,100),
(332,13,3104,100),
(333,13,3027,100),
(334,13,3044,100),
(335,13,1485,100),
(336,13,19473,100),
(337,13,19468,100),
(338,13,1225,100),
(339,13,346,1),
(340,13,348,1),
(341,13,350,1),
(342,13,355,1),
(343,13,356,1),
(344,13,362,1),
(345,13,370,1),
(346,13,371,1),
(347,13,373,1),
(348,21,19076,1000),
(349,13,19341,1),
(350,13,19342,1),
(351,13,19343,1),
(352,13,19344,1),
(353,13,19345,1),
(354,13,19833,1),
(355,13,19473,1),
(356,13,2690,1),
(357,13,2985,1),
(358,13,1654,1),
(359,13,2036,1),
(360,13,1506,1),
(361,13,19320,1),
(362,1,11682,1000),
(363,1,11683,1000),
(364,1,11684,1000),
(365,1,11685,1000),
(366,4,11686,5000),
(367,3,11687,500),
(368,4,11690,2000),
(369,4,11691,5000),
(370,34,11705,300),
(371,35,11706,100),
(372,28,11707,300),
(373,31,11715,100),
(374,31,11716,100),
(375,1,11717,3000),
(376,31,11718,200),
(377,31,11719,200),
(378,0,11720,3000),
(379,31,11722,800),
(380,31,11723,800),
(381,36,11724,5000),
(382,36,11725,5000),
(383,22,11726,3000),
(384,22,11726,800),
(385,34,11728,1000),
(386,5,11729,700),
(387,5,11730,700),
(388,0,11731,10000),
(389,26,11732,10000),
(390,20,11733,3000),
(391,3,11734,3000),
(392,14,11737,2000),
(393,31,11739,500),
(394,31,11740,500),
(395,31,11740,500),
(396,31,11743,1500),
(397,31,11744,500),
(398,34,18865,500),
(399,34,18866,500),
(400,34,18867,500),
(401,34,18868,500),
(402,34,18869,500),
(403,34,18870,500),
(404,34,18871,500),
(405,34,18872,500),
(406,34,18873,500),
(407,34,18874,500),
(408,32,19555,300),
(409,32,19556,300),
(410,31,19561,200),
(411,31,19562,200),
(412,31,19563,200),
(413,31,19564,200),
(414,31,19565,200),
(415,31,19566,200),
(416,31,19567,200),
(417,31,19568,200),
(418,31,19569,200),
(419,31,19571,200),
(420,31,19570,200),
(421,31,19572,200),
(422,31,19573,200),
(423,31,19574,200),
(424,31,19575,200),
(425,31,19576,200),
(426,31,19577,200),
(427,31,19578,200),
(428,31,19579,200),
(429,31,19580,200),
(430,31,19581,500),
(431,31,19582,200),
(432,31,19583,200),
(433,31,19584,500),
(434,31,19585,200),
(435,31,19586,200),
(436,36,19632,1000),
(437,31,19811,200),
(438,22,19806,2000),
(439,20,19805,1000),
(440,34,19807,500),
(441,10,19808,800),
(442,31,19818,500),
(443,31,19819,500),
(444,31,19820,500),
(445,31,19821,500),
(446,31,19822,500),
(447,31,19823,500),
(448,31,19824,500),
(449,31,19830,1500),
(450,16,19831,3000),
(451,31,19835,200),
(452,31,19847,500),
(453,25,19873,200),
(454,28,19874,100),
(455,10,19893,3000),
(456,10,19894,3000),
(457,15,19916,2000),
(458,4,19922,1000),
(459,16,19923,2000),
(460,16,19924,1000),
(461,6,19925,500),
(462,6,19926,1000),
(463,6,19927,1000),
(464,6,19928,500),
(465,6,19929,1000),
(466,6,19930,500),
(467,6,19931,500),
(468,6,19932,500),
(469,6,19933,500),
(470,6,19934,500),
(471,6,19935,500),
(472,6,19936,500),
(473,6,19937,500),
(474,6,19938,300),
(475,6,19939,300),
(476,6,19940,500),
(477,31,19993,300),
(478,3,19994,300),
(479,3,19996,300),
(480,18,19997,500),
(481,3,19999,1500),
(482,9,19787,1500),
(483,9,19786,3000),
(484,37,1502,1000),
(485,13,19054,100),
(486,13,19055,100),
(487,13,19056,100),
(488,13,19057,100),
(489,13,19058,100),
(490,13,19059,100),
(491,13,19060,100),
(492,13,19061,100),
(493,13,19062,100),
(494,13,19063,100),
(495,13,19064,100),
(496,13,19065,100),
(497,13,19066,100),
(498,13,2905,10000),
(499,13,2906,10000),
(500,13,2907,10000),
(501,13,2908,10000),
(502,13,2470,100000),
(503,13,2472,50000),
(504,13,2492,100000),
(505,13,2464,100000),
(506,13,2485,10000),
(507,13,2493,100000),
(508,13,2465,100000),
(509,13,2481,100000),
(510,13,2489,100000),
(511,13,2503,100000),
(512,13,2480,100000),
(513,13,2501,100000),
(514,13,2487,100000),
(515,13,11704,1000000),
(516,13,954,10000000),
(517,13,1276,1000000),
(518,13,1008,1000),
(519,13,1009,1000),
(520,13,1010,1000),
(521,13,1609,100000),
(522,13,1600,1000000),
(523,13,1946,100000),
(524,13,1895,250000),
(525,13,1736,25000),
(526,13,1985,250000),
(527,13,19128,50000),
(528,13,918,50000),
(529,13,19917,10000),
(530,13,19609,20000),
(531,13,19088,1000000);
/*!40000 ALTER TABLE `baldai_id` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `changedpass`
--

DROP TABLE IF EXISTS `changedpass`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `changedpass` (
  `Vardas` varchar(255) DEFAULT NULL,
  `Newpass` varchar(255) DEFAULT NULL,
  `Newhash` int(11) DEFAULT NULL,
  `Data` datetime DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `changedpass`
--

LOCK TABLES `changedpass` WRITE;
/*!40000 ALTER TABLE `changedpass` DISABLE KEYS */;
/*!40000 ALTER TABLE `changedpass` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `gangcars`
--

DROP TABLE IF EXISTS `gangcars`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `gangcars` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `gang` int(11) DEFAULT NULL,
  `lastuser` varchar(255) DEFAULT NULL,
  `status` int(11) DEFAULT NULL,
  `health` float DEFAULT NULL,
  `gas` float DEFAULT NULL,
  `mod1` int(11) DEFAULT NULL,
  `mod2` int(11) DEFAULT NULL,
  `mod3` int(11) DEFAULT NULL,
  `mod4` int(11) DEFAULT NULL,
  `mod5` int(11) DEFAULT NULL,
  `mod6` int(11) DEFAULT NULL,
  `mod7` int(11) DEFAULT NULL,
  `mod8` int(11) DEFAULT NULL,
  `mod9` int(11) DEFAULT NULL,
  `mod10` int(11) DEFAULT NULL,
  `mod11` int(11) DEFAULT NULL,
  `mod12` int(11) DEFAULT NULL,
  `mod13` int(11) DEFAULT NULL,
  `mod14` int(11) DEFAULT NULL,
  `mod15` int(11) DEFAULT NULL,
  `mod16` int(11) DEFAULT NULL,
  `mod17` int(11) DEFAULT NULL,
  `rida` float DEFAULT 0,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gangcars`
--

LOCK TABLES `gangcars` WRITE;
/*!40000 ALTER TABLE `gangcars` DISABLE KEYS */;
/*!40000 ALTER TABLE `gangcars` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `yrace`
--

DROP TABLE IF EXISTS `yrace`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8mb4 */;
CREATE TABLE `yrace` (
  `raceid` varchar(50) NOT NULL,
  `creator` varchar(50) DEFAULT NULL,
  `config` text DEFAULT NULL,
  `best_race` text DEFAULT NULL,
  `best_lap` text DEFAULT NULL,
  PRIMARY KEY (`raceid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `yrace`
--

LOCK TABLES `yrace` WRITE;
/*!40000 ALTER TABLE `yrace` DISABLE KEYS */;
/*!40000 ALTER TABLE `yrace` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'samp'
--
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'IGNORE_SPACE,STRICT_TRANS_TABLES,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
/*!50003 DROP PROCEDURE IF EXISTS `NightlyProcedure` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_general_ci */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`%` PROCEDURE `NightlyProcedure`()
BEGIN
		UPDATE `Account` SET `Vip`=`Vip`-1 WHERE `VIP` > 0;
		UPDATE `Account` SET `Mlicense`=`Mlicense`-1 WHERE `Mlicense` > 0;
		UPDATE `Account` SET `Draudimasg`=`Draudimasg`-1 WHERE `Draudimasg` > 0;
		UPDATE `Account` SET `PLigonine`=`PLigonine`-1 WHERE `PLigonine` > 0;
		UPDATE `Cars` SET `AH_Draud`=`AH_Draud`-1 WHERE `AH_Draud` > 0;
		UPDATE `Cars` SET `AH2_Draud`=`AH2_Draud`-1 WHERE `AH2_Draud` > 0;
		UPDATE `Cars` SET `AH3_Draud`=`AH3_Draud`-1 WHERE `AH3_Draud` > 0;
		DELETE FROM Logs WHERE Data < SUBDATE(NOW(), 7 ) AND Veiksmas <> "Vardo keitimas is"; 
		DELETE FROM Emails WHERE DateTime < SUBDATE(NOW(), 14 );
		DELETE FROM `BANS` WHERE `Date` < SUBDATE(NOW(), 365);
		DELETE From RemindPassword;
		UPDATE Pastas SET Email=NewEmail, NewEmail=NULL, ChangeDate=NULL WHERE NewEmail IS NOT NULL AND ChangeDate < SUBDATE(NOW(), 1);
		DELETE FROM Ispejimai WHERE time < SUBDATE(NOW(), 30 );
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
