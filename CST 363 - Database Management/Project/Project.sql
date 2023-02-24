CREATE DATABASE  IF NOT EXISTS `pharmacy` /*!40100 DEFAULT CHARACTER SET utf8 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `pharmacy`;
-- MySQL dump 10.13  Distrib 8.0.27, for macos11 (x86_64)
--
-- Host: localhost    Database: pharmacy
-- ------------------------------------------------------
-- Server version	8.0.27

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `company`
--

DROP TABLE IF EXISTS `company`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `company` (
  `companyID` int NOT NULL AUTO_INCREMENT,
  `name` varchar(70) NOT NULL,
  `phone_number` varchar(10) NOT NULL,
  PRIMARY KEY (`companyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `company`
--

LOCK TABLES `company` WRITE;
/*!40000 ALTER TABLE `company` DISABLE KEYS */;
/*!40000 ALTER TABLE `company` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `contract`
--

DROP TABLE IF EXISTS `contract`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `contract` (
  `contractID` int NOT NULL AUTO_INCREMENT,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL,
  `text` varchar(255) NOT NULL,
  `price` decimal(7,2) NOT NULL,
  `supervisorID` int NOT NULL,
  `pharmacyID` int NOT NULL,
  `drug_id` int NOT NULL,
  PRIMARY KEY (`contractID`),
  KEY `fk_contract_supervisor1_idx` (`supervisorID`),
  KEY `fk_contract_pharmacy1_idx` (`pharmacyID`),
  KEY `fk_contract_drug1_idx` (`drug_id`),
  CONSTRAINT `fk_contract_drug1` FOREIGN KEY (`drug_id`) REFERENCES `drug` (`drug_id`),
  CONSTRAINT `fk_contract_pharmacy1` FOREIGN KEY (`pharmacyID`) REFERENCES `pharmacy` (`pharmacyID`),
  CONSTRAINT `fk_contract_supervisor1` FOREIGN KEY (`supervisorID`) REFERENCES `supervisor` (`supervisorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `contract`
--

LOCK TABLES `contract` WRITE;
/*!40000 ALTER TABLE `contract` DISABLE KEYS */;
/*!40000 ALTER TABLE `contract` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `doctor`
--

DROP TABLE IF EXISTS `doctor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `doctor` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ssn` varchar(9) NOT NULL,
  `name` varchar(70) NOT NULL,
  `specialty` varchar(70) NOT NULL,
  `practice_since_year` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `doctor`
--

LOCK TABLES `doctor` WRITE;
/*!40000 ALTER TABLE `doctor` DISABLE KEYS */;
/*!40000 ALTER TABLE `doctor` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `drug`
--

DROP TABLE IF EXISTS `drug`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `drug` (
  `drug_id` int NOT NULL AUTO_INCREMENT,
  `trade_name` varchar(45) DEFAULT NULL,
  `formula` varchar(45) DEFAULT NULL,
  `companyID` int DEFAULT NULL,
  PRIMARY KEY (`drug_id`),
  KEY `fk_drug_company1_idx` (`companyID`),
  CONSTRAINT `fk_drug_company1` FOREIGN KEY (`companyID`) REFERENCES `company` (`companyID`)
) ENGINE=InnoDB AUTO_INCREMENT=100 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `drug`
--

LOCK TABLES `drug` WRITE;
/*!40000 ALTER TABLE `drug` DISABLE KEYS */;
INSERT INTO `drug` VALUES (1,'Tylenol with Codeine','acetaminophen and codeine',NULL),(2,'Proair Proventil','albuterol aerosol',NULL),(3,'Accuneb','albuterol HFA',NULL),(4,'Fosamax','alendronate',NULL),(5,'Zyloprim','allopurinol',NULL),(6,'Xanax','alprazolam',NULL),(7,'Elavil','amitriptyline',NULL),(8,'Augmentin','amoxicillin and clavulanate K+',NULL),(9,'Amoxil','amoxicillin',NULL),(10,'Adderall XR','amphetamine and dextroamphetamine XR',NULL),(11,'Tenormin','atenolol',NULL),(12,'Lipitor','atorvastatin',NULL),(13,'Zithromax','azithromycin',NULL),(14,'Lotrel','benazepril and amlodipine',NULL),(15,'Soma','carisoprodol',NULL),(16,'Coreg','carvedilol',NULL),(17,'Omnicef','cefdinir',NULL),(18,'Celebrex','celecoxib',NULL),(19,'Keflex','cephalexin',NULL),(20,'Cipro','ciprofloxacin',NULL),(21,'Celexa','citalopram',NULL),(22,'Klonopin','clonazepam',NULL),(23,'Catapres','clonidine HCl',NULL),(24,'Plavix','clopidogrel',NULL),(25,'Premarin','conjugated estrogens',NULL),(26,'Flexeril','cyclobenzaprine',NULL),(27,'Valium','diazepam',NULL),(28,'Voltaren','diclofenac sodium',NULL),(29,'Yaz','drospirenone and ethinyl estradiol',NULL),(30,'Cymbalta','Duloxetine',NULL),(31,'Vibramycin','doxycycline hyclate',NULL),(32,'Vasotec','enalapril',NULL),(33,'Lexapro','escitalopram',NULL),(34,'Nexium','esomeprazole',NULL),(35,'Zetia','ezetimibe',NULL),(36,'Tricor','fenofibrate',NULL),(37,'Allegra','fexofenadine',NULL),(38,'Diflucan','fluconozole',NULL),(39,'Prozac','fluoxetine HCl',NULL),(40,'Advair','fluticasone and salmeterol inhaler',NULL),(41,'Flonase','fluticasone nasal spray',NULL),(42,'Folic Acid','folic acid',NULL),(43,'Lasix','furosemide',NULL),(44,'Neurontin','gabapentin',NULL),(45,'Amaryl','glimepiride',NULL),(46,'Diabeta','glyburide',NULL),(47,'Glucotrol','glipizide',NULL),(48,'Microzide','hydrochlorothiazide',NULL),(49,'Lortab','hydrocodone and acetaminophen',NULL),(50,'Motrin','ibuprophen',NULL),(51,'Lantus','insulin glargine',NULL),(52,'Imdur','isosorbide mononitrate',NULL),(53,'Prevacid','lansoprazole',NULL),(54,'Levaquin','levofloxacin',NULL),(55,'Levoxl','levothyroxine sodium',NULL),(56,'Zestoretic','lisinopril and hydrochlorothiazide',NULL),(57,'Prinivil','lisinopril',NULL),(58,'Ativan','lorazepam',NULL),(59,'Cozaar','losartan',NULL),(60,'Mevacor','lovastatin',NULL),(61,'Mobic','meloxicam',NULL),(62,'Glucophage','metformin HCl',NULL),(63,'Medrol','methylprednisone',NULL),(64,'Toprol','metoprolol succinate XL',NULL),(65,'Lopressor','metoprolol tartrate',NULL),(66,'Nasonex','mometasone',NULL),(67,'Singulair','montelukast',NULL),(68,'Naprosyn','naproxen',NULL),(69,'Prilosec','omeprazole',NULL),(70,'Percocet','oxycodone and acetaminophen',NULL),(71,'Protonix','pantoprazole',NULL),(72,'Paxil','paroxetine',NULL),(73,'Actos','pioglitazone',NULL),(74,'Klor-Con','potassium Chloride',NULL),(75,'Pravachol','pravastatin',NULL),(76,'Deltasone','prednisone',NULL),(77,'Lyrica','pregabalin',NULL),(78,'Phenergan','promethazine',NULL),(79,'Seroquel','quetiapine',NULL),(80,'Zantac','ranitidine',NULL),(81,'Crestor','rosuvastatin',NULL),(82,'Zoloft','sertraline HCl',NULL),(83,'Viagra','sildenafil HCl',NULL),(84,'Vytorin','simvastatin and ezetimibe',NULL),(85,'Zocor','simvastatin',NULL),(86,'Aldactone','spironolactone',NULL),(87,'Bactrim DS','sulfamethoxazole and trimethoprim DS',NULL),(88,'Flomax','tamsulosin',NULL),(89,'Restoril','temezepam',NULL),(90,'Topamax','topiramate',NULL),(91,'Ultram','tramadol',NULL),(92,'Aristocort','triamcinolone Ace topical',NULL),(93,'Desyrel','trazodone HCl',NULL),(94,'Dyazide','triamterene and hydrochlorothiazide',NULL),(95,'Valtrex','valaciclovir',NULL),(96,'Diovan','valsartan',NULL),(97,'Effexor XR','venlafaxine XR',NULL),(98,'Calan SR','verapamil SR',NULL),(99,'Ambien','zolpidem',NULL);
/*!40000 ALTER TABLE `drug` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `patient`
--

DROP TABLE IF EXISTS `patient`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `patient` (
  `patientID` int NOT NULL AUTO_INCREMENT,
  `name` varchar(70) NOT NULL,
  `birthdate` date NOT NULL,
  `ssn` varchar(9) NOT NULL,
  `street` varchar(70) NOT NULL,
  `city` varchar(70) NOT NULL,
  `state` varchar(45) NOT NULL,
  `zipcode` varchar(10) NOT NULL,
  `primaryID` int NOT NULL,
  PRIMARY KEY (`patientID`),
  KEY `fk_patient_doctor_idx` (`primaryID`),
  CONSTRAINT `fk_patient_doctor` FOREIGN KEY (`primaryID`) REFERENCES `doctor` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `patient`
--

LOCK TABLES `patient` WRITE;
/*!40000 ALTER TABLE `patient` DISABLE KEYS */;
/*!40000 ALTER TABLE `patient` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `pharmacy`
--

DROP TABLE IF EXISTS `pharmacy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `pharmacy` (
  `pharmacyID` int NOT NULL AUTO_INCREMENT,
  `name` varchar(70) NOT NULL,
  `address` varchar(70) NOT NULL,
  `phone_number` varchar(10) NOT NULL,
  PRIMARY KEY (`pharmacyID`)
) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pharmacy`
--

LOCK TABLES `pharmacy` WRITE;
/*!40000 ALTER TABLE `pharmacy` DISABLE KEYS */;
INSERT INTO `pharmacy` VALUES (1,'CVS on 41st','231 41st Ave','5551111111'),(2,'Downtown CVS','11 Downtown Street','5552222222'),(3,'Rite Aid on 41st','233 41st Ave','5553333333'),(4,'Downtown Rite Aid','13 Downtown Street','5554444444'),(5,'Walgreens on 41st','235 41st Ave','5555555555'),(6,'Downtown Walgreens','15 Downtown Street','5556666666'),(7,'Walmart Pharmacy','300 Walmart Ave','5557777777'),(8,'Costco Pharmacy','9 Downtown Street','5558888888'),(9,'Amazon Medicine','123 Online Ave','5559999999'),(10,'Safeway Pharmacy','12 Other Road','5550000000');
/*!40000 ALTER TABLE `pharmacy` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `prescription`
--

DROP TABLE IF EXISTS `prescription`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `prescription` (
  `rxid` int NOT NULL AUTO_INCREMENT,
  `drug_id` int NOT NULL,
  `quantity` int NOT NULL,
  `prescribed_date` date NOT NULL,
  `patientID` int NOT NULL,
  `doctor_id` int NOT NULL,
  `pharmacyID` int DEFAULT NULL,
  `date_filled` date DEFAULT NULL,
  `cost` decimal(7,2) DEFAULT NULL,
  PRIMARY KEY (`rxid`),
  KEY `fk_prescription_drug1_idx` (`drug_id`),
  KEY `fk_prescription_patient1_idx` (`patientID`),
  KEY `fk_prescription_doctor1_idx` (`doctor_id`),
  KEY `fk_prescription_pharmacy1_idx` (`pharmacyID`),
  CONSTRAINT `fk_prescription_doctor1` FOREIGN KEY (`doctor_id`) REFERENCES `doctor` (`id`),
  CONSTRAINT `fk_prescription_drug1` FOREIGN KEY (`drug_id`) REFERENCES `drug` (`drug_id`),
  CONSTRAINT `fk_prescription_patient1` FOREIGN KEY (`patientID`) REFERENCES `patient` (`patientID`),
  CONSTRAINT `fk_prescription_pharmacy1` FOREIGN KEY (`pharmacyID`) REFERENCES `pharmacy` (`pharmacyID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `prescription`
--

LOCK TABLES `prescription` WRITE;
/*!40000 ALTER TABLE `prescription` DISABLE KEYS */;
/*!40000 ALTER TABLE `prescription` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `supervisor`
--

DROP TABLE IF EXISTS `supervisor`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `supervisor` (
  `supervisorID` int NOT NULL AUTO_INCREMENT,
  `name` varchar(70) NOT NULL,
  `ssn` varchar(9) NOT NULL,
  PRIMARY KEY (`supervisorID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `supervisor`
--

LOCK TABLES `supervisor` WRITE;
/*!40000 ALTER TABLE `supervisor` DISABLE KEYS */;
/*!40000 ALTER TABLE `supervisor` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-02-08  3:00:42
