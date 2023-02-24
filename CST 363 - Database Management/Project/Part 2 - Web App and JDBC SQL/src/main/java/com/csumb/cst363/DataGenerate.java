/*
 * DataGenerate: This program is intended to generate random data for the tables of 
 * doctor, patient, and prescription located in the pharmacy database. Specifically, this program 
 * fills the patient table with 1000 patients, the doctor table with 10 doctors, and the 
 * prescription table with 5000 prescriptions. This program also generates data for the 
 * ManagerReport class.
 * CST 363: Intro to Database Systems- Project 2
 * Jennah Yasin & Yukio Rivera
 */
package com.csumb.cst363;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;
import java.text.DecimalFormat;
import java.util.Random;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DataGenerate {
    public static void main(String[] args) {
        // List of random names/items for array to automatically generate
        String[] firstNames = {"Mark", "Ross", "Manny", "Josh", "Gilbert", "Michelle","Danita", "Gail", "Lawanda", "Quoc"};
        String[] lastNames = {"Vo", "Lopez", "Nguyen", "Patterson", "Noble", "Coltz", "Kar", "Filtz", "Shwartz", "Sauter"};
        String[] streets = {"Apple Dr", "17th Street", "Mona Blvrd", "Largo", "Watts", "Rosevelt Dr", "Brommer St", "Wala Street", "Decker Street", "Fredrick Road"};
        String[] cities = {"Santa Cruz", "Compton", "Lynwood", "Lakewood", "Santa Clara", "Padadena", "Scranton", "Brooklyn", "Foxhole", "New York"};
        String[] states = {"California", "Utah", "Florida", "New Jersey", "Texas"};
        String[] doctorFirstName = {"Weinstein", "Chagi", "Nair", "Bong", "Mitsunaga", "Chen", "Javier", "Yasmin",
        		"George", "Chris", "Louie", "David", "Eli", "Ernesto", "Laura", "Terri", "Ale", "Ahri", "Malz", "Patty"};
        String[] doctorLastName = {"Champlin", "Oswald", "Cardenas", "Lopez", "Chavez", "Johnson", "Gunter", "Huges", "Alfonzo", "Candice", 
        		"Guzman", "Aguilar", "Mazar", "Cassada", "Peterson", "Kelp", "Sato", "Tanaka", "Suzuki", "Wander"};
        String[] doctorSpecialty = {"Cardiologists", "Dermatologists", 
        		"Internal Medicine", "Family Physician", "Pediatricians", "Physiatrists"};	

    	String url = "jdbc:mysql://localhost:3306/pharmacy";
        String user = "root";
        String pw = "Sultana123!";
    	try (Connection con = DriverManager.getConnection(url, user, pw); ) {
    		con.setAutoCommit(false);
    		//Prepared statement to randomly generate a doctor's information by positions to add to the doctor table in SQL workbench
    		PreparedStatement ds = con.prepareStatement (
              		"insert into doctor(ssn, name, specialty, practice_since_year) values( ?, ?, ?, ?)");     
    		for(int i = 0; i < 10; i++) {
    			//randomly generates the doctor's ssn with given conditions: 9 digit number:
    			//first digit can't be a 0 or 9, middle numbers cannot be 00 (only 01-99),
    			//last four cannot be 0000 (only 0001-9999)  
    			Random doctorGen = new Random();           
              	ds.setString(1, "" + (doctorGen.nextInt(8) + 1) + 
                        (doctorGen.nextInt(89) + 11) + 
                        (doctorGen.nextInt(89) + 11) + 
                        (doctorGen.nextInt(8889) + 1111));
              	
              	//randomly generates the doctor's first + last name using array of strings
             	String doctorFullName = getRand(doctorFirstName) + " " + getRand(doctorLastName);
              	ds.setString(2, doctorFullName);
              	
              	//randomly generates the docotr's specialty using the array of strings created.
              	String specialty  = getRand(doctorSpecialty);
              	ds.setString(3, specialty);
              	
              	//randomly generates doctor's year since practice 
              	ds.setString(4, "" + (doctorGen.nextInt(122) + 1900));
                ds.executeUpdate();
            }
    		//Confirmation statement
    		System.out.println("Doctors have been generated.");
    		//Prepared statement to randomly generate a patient's information by positions to add to the patient table in SQL workbench
    		PreparedStatement ps = con.prepareStatement(
                    "insert into patient (name, birthdate, ssn, street, city, state, zipcode, primaryID) values(?, ?, ?, ?, ?, ?, ?, ?)");
    		
    		for (int i = 0; i < 1000; i++) {
    			//randomly generates patient's full name using array of strings of first names + last names
    			String fullName = getRand(firstNames) + " " + getRand(lastNames);
                ps.setString(1, fullName);
                
                //randomly generates patient's  birthdate by yyyy-mm-dd
                Random patientGen = new Random();
                String birthyear = "" + (patientGen.nextInt(51) + 1970);
                String birthmonths = "-" + (patientGen.nextInt(12) + 1) + "-" + (patientGen.nextInt(27) + 1);
                ps.setString(2, birthyear + birthmonths);
                
                //randomly generates patient's ssn following the requirements of:
                //9 total digits: first digit cannot be 0 or 9, middle two digits cannot be 00 (only 01-99),
                //last 4 digits cannot be 0000 (only 0001-9999)
                ps.setString(3, "" + (patientGen.nextInt(8) + 1) + 
                        (patientGen.nextInt(89) + 11) + 
                        (patientGen.nextInt(89) + 11) + 
                        (patientGen.nextInt(8889) + 1111));
                
                //randomly generates a patient's street address using array of strings of streets
                String wholeStreet = patientGen.nextInt(999) + " " + getRand(streets);
                ps.setString(4, wholeStreet);
                
                //randomly generates a patient's city address using array of strings of cities
                String wholeCity = getRand(cities);
                ps.setString(5, wholeCity);
                
                //randomly generates a patient's state address using array of strings of states
                String wholeState = getRand(states);
                ps.setString(6, wholeState);
                String zipcode = (""+patientGen.nextInt(88888) + 11111);
                ps.setString(7, zipcode);
                
                //seperates patients by birth year: anyone born after 2006 is assigned a pediatrician
                //otherwise, family physician/internal medicine 
                String str = "";
                if (Integer.parseInt(birthyear) > 2006) {
                	str = "SELECT id FROM doctor WHERE specialty = 'Pediatricians' ORDER BY RAND() LIMIT 1";
                } 
                else {
                    str = "SELECT id FROM doctor WHERE specialty = 'Family Physician' OR specialty = 'Internal Medicine' ORDER BY RAND() LIMIT 1";
                }
                
                //gets doctor's id to set primary physician for patient
                ResultSet grabbedRes = ps.executeQuery(str);
                String doctorID = "";
                while(grabbedRes.next()) {
                	doctorID = grabbedRes.getString("id");
                }
                ps.setString(8, doctorID);
                ps.executeUpdate();
            } 
    		//Confirmation statement
            System.out.println("Patients have been generated.");        
            
    		//Prepared statement to randomly generate drug information by positions to add to the drug table in SQL workbench
            PreparedStatement dns = con.prepareStatement (
            		"insert into prescription (drug_id, quantity, prescribed_date,"
            		+ "patientID, doctor_id, pharmacyID, date_filled, cost) values(?,?,?,?,?,?,?,?)");
            for (int i = 0; i < 5000; i++) {
            	Random drugGen = new Random();
            	//randomly generates a drug's rxnumber
            	int rxnum = drugGen.nextInt(99)+1;
            	dns.setInt(1, rxnum);
            	
            	//randomly generates a drugs prescription quantity
            	int quantity = drugGen.nextInt(30)+1;
            	dns.setInt(2,  quantity);
            	
            	//randomly generates the date medications were prescribed
            	String date = ("19" + (drugGen.nextInt(88) + 11)) + "-" + (drugGen.nextInt(11) + 1) + "-" + (drugGen.nextInt(27) + 1);
            	dns.setString(3, date);
            	
            	//selects a patient id to store drug prescriptions into
            	String pstr = "SELECT patientId FROM  patient ORDER BY RAND() LIMIT 1";
            	ResultSet grabbedRes = dns.executeQuery(pstr);
            	String patientId = "";
            	while(grabbedRes.next()) {
            		patientId = grabbedRes.getString("patientID");
                }
            	dns.setString(4, patientId);
            	
            	//selects a doctor that prescribes the medication to patient
            	String dstr = "SELECT id FROM doctor ORDER BY RAND() LIMIT 1";
            	ResultSet docRes = dns.executeQuery(dstr);
            	String doctorID = "";
            	while(docRes.next()) {
            		doctorID = docRes.getString("id");
            	}
            	dns.setString(5, doctorID);
            	
            	int pharmId = drugGen.nextInt(11);
            	if (pharmId == 0) {
            		dns.setNull(6, Types.NULL);
            		dns.setNull(7, Types.NULL);
            		dns.setNull(8, Types.NULL);
            	}
            	else {
            		dns.setInt(6, pharmId);
            		dns.setString(7, "" + (drugGen.nextInt(3) + 2010) + "-" + (drugGen.nextInt(12) + 1) + "-" + (drugGen.nextInt(27) + 1));
            		float price =  drugGen.nextFloat() + (drugGen.nextInt(100) + 1); 
            		DecimalFormat decimal = new DecimalFormat("###.00");
            		dns.setString(8,decimal.format(price));
            	}
            	dns.executeUpdate();
            }
            System.out.println("Prescriptions have been generated.");
            con.commit();
        } catch (SQLException e) {
        	System.out.println("Error" + e);
        }
    }

    /**
     * getRand: Given an array, generates a random index 
     * and returns the item inside back.
     * 
     * @param toGrab the given array
     * @return a random item
     */
    private static String getRand(String[] toGrab) {
    	Random randGen = new Random();
    	return toGrab[randGen.nextInt(toGrab.length)];
    }
}