-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema pharmainfo
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema pharmainfo
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `pharmainfo` DEFAULT CHARACTER SET utf8 ;
USE `pharmainfo` ;

-- -----------------------------------------------------
-- Table `pharmainfo`.`company`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`company` (
  `CompanyName` VARCHAR(70) NOT NULL,
  `PhoneNumber` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`CompanyName`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`pharmacy`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`pharmacy` (
  `PharmacyID` INT NOT NULL AUTO_INCREMENT,
  `Name` VARCHAR(70) NOT NULL,
  `Address` VARCHAR(255) NOT NULL,
  `PhoneNumber` VARCHAR(10) NOT NULL,
  PRIMARY KEY (`PharmacyID`))
ENGINE = InnoDB
AUTO_INCREMENT = 4
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`supervisor`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`supervisor` (
  `SSN` VARCHAR(9) NOT NULL,
  `FullName` VARCHAR(70) NOT NULL,
  PRIMARY KEY (`SSN`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`contract`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`contract` (
  `ContractID` INT NOT NULL AUTO_INCREMENT,
  `StartDate` DATE NOT NULL,
  `EndDate` DATE NOT NULL,
  `Text` VARCHAR(255) NOT NULL,
  `Price` DECIMAL(6,2) NOT NULL,
  `CompanyName` VARCHAR(70) NOT NULL,
  `PharmacyID` INT NOT NULL,
  `Supervisor_SSN` VARCHAR(9) NOT NULL,
  PRIMARY KEY (`ContractID`),
  INDEX `fk_Contract_Company1_idx` (`CompanyName` ASC) VISIBLE,
  INDEX `fk_Contract_Pharmacy1_idx` (`PharmacyID` ASC) VISIBLE,
  INDEX `fk_contract_Supervisor1_idx` (`Supervisor_SSN` ASC) VISIBLE,
  CONSTRAINT `fk_Contract_Company1`
    FOREIGN KEY (`CompanyName`)
    REFERENCES `pharmainfo`.`company` (`CompanyName`),
  CONSTRAINT `fk_Contract_Pharmacy1`
    FOREIGN KEY (`PharmacyID`)
    REFERENCES `pharmainfo`.`pharmacy` (`PharmacyID`),
  CONSTRAINT `fk_contract_Supervisor1`
    FOREIGN KEY (`Supervisor_SSN`)
    REFERENCES `pharmainfo`.`supervisor` (`SSN`))
ENGINE = InnoDB
AUTO_INCREMENT = 3
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`doctors`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`doctors` (
  `SSN` VARCHAR(9) NOT NULL,
  `FullName` VARCHAR(70) NOT NULL,
  `Specialty` VARCHAR(70) NOT NULL,
  `ExperienceInYears` INT NOT NULL,
  PRIMARY KEY (`SSN`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`medication`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`medication` (
  `TradeName` VARCHAR(70) NOT NULL,
  `GenericFormula` VARCHAR(70) NOT NULL,
  `CompanyName` VARCHAR(70) NOT NULL,
  PRIMARY KEY (`TradeName`),
  INDEX `fk_medication_Company1_idx` (`CompanyName` ASC) VISIBLE,
  CONSTRAINT `fk_medication_Company1`
    FOREIGN KEY (`CompanyName`)
    REFERENCES `pharmainfo`.`company` (`CompanyName`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`patient`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`patient` (
  `SSN` VARCHAR(9) NOT NULL,
  `FullName` VARCHAR(70) NOT NULL,
  `Age` INT NOT NULL,
  `Address` VARCHAR(255) NOT NULL,
  `PrimaryPhysicianSSN` VARCHAR(9) NOT NULL,
  PRIMARY KEY (`SSN`),
  INDEX `fk_patient_doctors1_idx` (`PrimaryPhysicianSSN` ASC) VISIBLE,
  CONSTRAINT `fk_patient_doctors1`
    FOREIGN KEY (`PrimaryPhysicianSSN`)
    REFERENCES `pharmainfo`.`doctors` (`SSN`))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8mb3;


-- -----------------------------------------------------
-- Table `pharmainfo`.`prescription`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `pharmainfo`.`prescription` (
  `RXNum` INT NOT NULL AUTO_INCREMENT,
  `Quantity` INT NOT NULL,
  `PrescribedDate` DATE NOT NULL,
  `FilledDate` DATE NULL DEFAULT NULL,
  `FilledPharmacyID` INT NULL,
  `medicationTradeName` VARCHAR(70) NOT NULL,
  `patient_SSN` VARCHAR(9) NOT NULL,
  `doctors_SSN` VARCHAR(9) NOT NULL,
  PRIMARY KEY (`RXNum`),
  INDEX `fk_prescription_medication1_idx` (`medicationTradeName` ASC) VISIBLE,
  INDEX `fk_prescription_patient1_idx` (`patient_SSN` ASC) VISIBLE,
  INDEX `fk_prescription_doctors1_idx` (`doctors_SSN` ASC) VISIBLE,
  INDEX `fk_prescription_pharmacy1_idx` (`FilledPharmacyID` ASC) VISIBLE,
  CONSTRAINT `fk_prescription_doctors1`
    FOREIGN KEY (`doctors_SSN`)
    REFERENCES `pharmainfo`.`doctors` (`SSN`),
  CONSTRAINT `fk_prescription_medication1`
    FOREIGN KEY (`medicationTradeName`)
    REFERENCES `pharmainfo`.`medication` (`TradeName`),
  CONSTRAINT `fk_prescription_patient1`
    FOREIGN KEY (`patient_SSN`)
    REFERENCES `pharmainfo`.`patient` (`SSN`),
  CONSTRAINT `fk_prescription_pharmacy1`
    FOREIGN KEY (`FilledPharmacyID`)
    REFERENCES `pharmainfo`.`pharmacy` (`PharmacyID`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
AUTO_INCREMENT = 2
DEFAULT CHARACTER SET = utf8mb3;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;



-- Display the pharmacy  names and pharmacyid that have the drug tradename  of ‘Tylenol’. 
-- SQL STATEMENT:
SELECT name, pharmacy.pharmacyid 
    FROM pharmacy
    INNER JOIN contract ON pharmacy.pharmacyid=contract.pharmacyid
    INNER JOIN company ON contract.companyname=company.companyname
    INNER JOIN medication ON company.companyname=medication.companyname
    WHERE tradename= 'Tylenol';
-- Display the patient name as PatientName, medication number, amount of meds, date, prescribing doctor as DoctorName, and pharmacy name as PharmacyName the meds need to be picked up at. 
-- SQL STATEMENT:
SELECT patient.fullname AS 'PatientName', prescription.RXnum, prescription.quantity, prescription.prescribeddate, doctors.fullname AS 'DoctorName', pharmacy.name AS 'PharmacyName'
    FROM patient JOIN prescription ON patient.ssn = prescription.patient_ssn
    JOIN doctors ON doctors.ssn = prescription.doctors_ssn
    JOIN medication ON prescription.medicationtradename = medication.tradename
    JOIN company ON medication.companyname = company.companyname
    JOIN contract ON company.companyname = contract.companyname
    JOIN pharmacy ON contract.pharmacyid = pharmacy.pharmacyid;

-- Using a sub-query, find the average age of the patients and display the maximumn of that average age and the medication being taken by them.
SELECT MAX(AverageAge), medicationTradeName
	FROM (SELECT AVG(Age) AS AverageAge, medicationtradename
	FROM patient p
	JOIN prescription pr ON pr.patient_SSN = p.ssn
	GROUP BY medicationTradeName) AS AvgAge
	GROUP BY medicationTradeName;

-- Display the names of all patients and doctors that have a ssn number that  ends with the number 9. Add the prefix Dr. before doctor names as FullName. USE UNION.
-- SQL STATEMENT: 
SELECT CONCAT('Dr. ', fullname) as ‘FullName’
	From doctors
	WHERE ssn LIKE  '%9'
	UNION
	SELECT fullname
	FROM patient
	WHERE ssn LIKE '%9';

-- Display the sum of the patients each doctor has as PatientCount. Order by the doctor’s name.
-- SQL STATEMENT:
SELECT doctors.fullname, COUNT(primaryphysicianSSN) as 'PatientCount'
	FROM patient  
	INNER JOIN doctors ON patient.primaryphysicianSSN=doctors.ssn
	GROUP BY doctors.fullname;