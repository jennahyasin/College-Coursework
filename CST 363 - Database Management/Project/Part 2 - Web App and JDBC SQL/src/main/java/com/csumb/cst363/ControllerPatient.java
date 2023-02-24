/*
 * Controller Patient: This program works as a controller class that handles registering new patients,
 * viewing existing patient information, and being able to edit and update portions of patient's information 
 * through the pharmacy database.
 * CST 363: Intro to Database Systems- Project 2
 * Jennah Yasin & Yukio Rivera
 */
package com.csumb.cst363;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

/*
 * Controller class for patient interactions.
 *   register as a new patient.
 *   update patient profile.
 */
@Controller
public class ControllerPatient {
	
	@Autowired
	private JdbcTemplate jdbcTemplate;
	
	/*
	 * Request patient_register form.
	 */
	@GetMapping("/patient/new")
	public String newPatient(Model model) {
		// return blank form for new patient registration
		model.addAttribute("patient", new Patient());
		return "patient_register";
	}
	
	/*
	 * Request form to search for patient.
	 */
	@GetMapping("/patient/edit")
	public String getPatientForm(Model model) {
		// prompt for patient id and name
		return "patient_get";
	}
	
	/*
	 * Process a form to create new patient.
	 */
	@PostMapping("/patient/new")
	public String newPatient(Patient patient, Model model) {
		//Several if-statements that checks the validity of the user input on the web application.
		
		//Makes sure street information is not a null value or empty.
		if(patient.getStreet() == null || patient.getStreet().isEmpty())
		{
			model.addAttribute("message", "Invalid street info");
			return "patient_register";
		}
		
		//Makes sure city information is not a null value, empty, or non-alphabetical.
		else if(patient.getCity() == null || patient.getCity().isEmpty() || !patient.getCity().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid city info");
			return "patient_register";
		}
		//Makes sure state information is not a null value, empty, or non-alphabetical
		else if(patient.getState() == null || patient.getState().isEmpty() || !patient.getState().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid state info");
			return "patient_register";
		}
		//Makes sure patient's name information is not a null value, empty, or non-alphabetical
		else if(patient.getName() == null || patient.getName().isEmpty() || !patient.getName().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid name info");
			return "patient_register";
		}
		//Makes sure zipcode information is not null, empty, or longer than 5 digits.
		else if(patient.getZipcode() == null || patient.getZipcode().isEmpty() || patient.getZipcode().length()!=5)
		{
			model.addAttribute("message", "Invalid zipcode info");
			return "patient_register";
		}
		//Makes sure patient's birth year is not earlier than 1900 or later than 2022
		else if(Integer.valueOf(patient.getBirthdate().substring(0,4)) <= 1900|| (Integer.valueOf(patient.getBirthdate().substring(0,4)) >= 2022))
		{
			model.addAttribute("message", "Invalid year info");
			return "patient_register"; 
		}
		//Makes sure patient's ssn is 9 digits: first digit cannot be 0 or 9, two middle digits cannot be 00 (only 01-99)
		//last four numbers cannot be 0000 (only 0001-9999)
		else if(patient.getSsn().length() != 9 || patient.getSsn().isEmpty()
			   ||Integer.valueOf(patient.getSsn().substring(0,1)) == 0 || Integer.valueOf(patient.getSsn().substring(0,1)) == 9
			   || Integer.valueOf(patient.getSsn().substring(4,5)) == 00
			   || Integer.valueOf(patient.getSsn().substring(6,9)) == 0000) {
			model.addAttribute("message", "Invalid ssn info");
			return "patient_register";
		} 
	   //otherwise, display the patient's inserted information
	   else {
		   try (Connection con = getConnection(); ) {
			   String Query = "insert into patient (name, birthdate, ssn, street, city, state, zipcode, primaryID) values (?,?,?,?,?,?,?,?)";
			   String doc = "select id from doctor WHERE name = ?";
			   //prepared statement that finds primary doctor through doctor's id
			   PreparedStatement docFind = con.prepareStatement(doc);
			   
			   //prepared statement that inserts patient's information from web app into the SQL workbench patient table.
	           PreparedStatement prepStatement = con.prepareStatement(Query, Statement.RETURN_GENERATED_KEYS);
	           prepStatement.setString(1, patient.getName());
	           prepStatement.setString(2, patient.getBirthdate());
	           prepStatement.setString(3, patient.getSsn());
	           prepStatement.setString(4, patient.getStreet());
	           prepStatement.setString(5, patient.getCity());
	           prepStatement.setString(6, patient.getState());
	           prepStatement.setString(7, patient.getZipcode());
	           
	           //finds the primary doctor's id and adds it into the patient table for primary doctor's name
	           docFind.setString(1,  patient.getPrimaryName());
	           ResultSet res = docFind.executeQuery();
		       while(res.next()) {
		    	   prepStatement.setString(8, res.getString("id"));
		       }
	           prepStatement.executeUpdate();
	           
	           //inserts new patient's info to the patient table 
	           ResultSet pf = prepStatement.getGeneratedKeys();
	           if (pf.next())
	           {
	        	   patient.setPatientId(pf.getString(1));
	           }
	           //shows patient info to user
	           model.addAttribute("patient", patient);
	           return "patient_show";
	       } catch (SQLException ex) {
	    	   //if anything fails, error message displayed 
	    	   model.addAttribute("message", "SQL Error."+ex.getMessage());
	    	   model.addAttribute("patient", patient);
	    	   //resets the new patient fill form
	    	   return "patient_register";       
	       }
	   }
	}
	
	/*
	 * Search for patient by patient id and name.
	 */
	@PostMapping("/patient/show")
	public String getPatientForm(@RequestParam("patientId") String patientId, @RequestParam("name") String name,
			Model model) {
		Patient patient = new Patient();
		try (Connection con = getConnection();) {
			//prepared statement for viewing patient's information
			PreparedStatement ps = con
                    .prepareStatement("SELECT p.birthdate, p.ssn, p.street, p.city, p.state, p.zipcode, p.primaryID, d.name FROM patient p INNER JOIN doctor d ON p.primaryID=d.id where p.patientID=? AND p.name=?");
            // sets values for prepared statement to user's input on the form to search the databse
            ps.setString(1, patientId); 
            ps.setString(2, name);
            
            //sets all the patient's information from patient table and displays it to the user
            ResultSet rs = ps.executeQuery();
            
            if (rs.next()) { //If a patient is found: 
            	//set all patient's info:
                patient.setPatientId(patientId);
                patient.setName(name);
                patient.setBirthdate(rs.getString(1));
                patient.setSsn(rs.getString(2));
                patient.setStreet(rs.getString(3));
                patient.setCity(rs.getString(4));
                patient.setState(rs.getString(5));
                patient.setZipcode(rs.getString(6));
                patient.setPrimaryID(rs.getInt(7));
                patient.setPrimaryName(rs.getString(8));
                
                //displays the patients information on web application
                model.addAttribute("patient", patient);
                return "patient_show";
            } else { //if patient is not found in the table/database:
            	//Display error message and reset the returns back to get patient info form
                model.addAttribute("message", "Patient not found.");
                return "patient_get";
            }
        } catch (SQLException e) {
        	//if setting values fails, error is displayed and get patient info form is reset
            model.addAttribute("message", "SQL Error." + e.getMessage());
            model.addAttribute("patient", patient);
            return "patient_get";
        }
	}

	/*
	 * Search for patient by patient id.
	 */
	@GetMapping("/patient/edit/{patientId}")
	public String updatePatient(@PathVariable String patientId, Model model) {
		Patient patient = new Patient();
		try (Connection con = getConnection();) {
			//prepared statement that displays a patients info from patient table in database
			PreparedStatement ps = con
                    .prepareStatement("SELECT p.birthdate, p.ssn, p.street, p.city, p.state, p.zipcode, p.primaryID, d.name, p.name, d.specialty, d.practice_since_year FROM patient p INNER JOIN doctor d ON p.primaryID=d.id where p.patientID=?");
            //searches for patient from patientID 
            ps.setString(1, patientId); 
            
            //Executes the query and sets all columns to inserted information
            ResultSet rs = ps.executeQuery();
            if (rs.next()) { //If the patient is found: 
                patient.setPatientId(patientId);
                patient.setBirthdate(rs.getString(1));
                patient.setSsn(rs.getString(2));
                patient.setStreet(rs.getString(3));
                patient.setCity(rs.getString(4));
                patient.setState(rs.getString(5));
                patient.setZipcode(rs.getString(6));
                patient.setPrimaryID(rs.getInt(7));
                patient.setPrimaryName(rs.getString(8));
                patient.setName(rs.getString(9));
                patient.setSpecialty(rs.getString(10));
                patient.setYears(rs.getString(11));

                // displays the patient's information and shows the patient edit form
                model.addAttribute("patient", patient);
                return "patient_edit";
            } else { //If patient doesn't exist in database: 
            	//display error message and refresh the get user info form
                model.addAttribute("message", "Patient not found. ");
                return "patient_get";
            }
        } catch (SQLException e) {
        	System.out.println("SQL error in getPatient " + e.getMessage());
            model.addAttribute("message", "SQL Error." + e.getMessage());
            model.addAttribute("patient", patient);
            return "patient_get";
        }
	}
	
	
	/*
	 * Process changes to patient address and primary doctor
	 */
	@PostMapping("/patient/edit")
	public String updatePatient(Patient p, Model model) {
		//makes sure street information is not a null value or empty string.
		if(p.getStreet() == null || p.getStreet().isEmpty())
		{
			model.addAttribute("message", "Invalid street info");
			return "patient_register";
		}
		//makes sure state information is not a null value, empty, or non-alphabetic value
		else if(p.getState() == null || p.getState().isEmpty() || !p.getState().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid state info");
			return "patient_register";
		}
		//makes sure city information is not a null value, empty, or non-alphabetic value
		else if(p.getCity() == null || p.getCity().isEmpty() || !p.getCity().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid city info");
			return "patient_register";
		}
		//makes sure patient's name is not a null value, empty, or non-alphabetic value
		else if(p.getName() == null || p.getName().isEmpty() || !p.getName().matches("[ a-zA-Z]+"))
		{
			model.addAttribute("message", "Invalid name info");
			return "patient_register";       
		}
		//makes sure zipcode information is not null, empty, or isn't longer than 5 digits.
		else if(p.getZipcode() == null || p.getZipcode().isEmpty() || p.getZipcode().length() != 5)
		{
			model.addAttribute("message", "Invalid zipcode info");
			return "patient_register";
		}
		//makes sure patient's birth year is not earlier than 1900 or later than 2022
		else if(Integer.valueOf(p.getBirthdate().substring(0,4)) <= 1900|| (Integer.valueOf(p.getBirthdate().substring(0,4)) >= 2022))
		   {
			   model.addAttribute("message", "Invalid year info");
	           return "patient_register";  
		   }
		//if everything passes, the patient can edit their address and primary doctor information
		else {
			try (Connection con = getConnection();) {
				
				//prepared statement to find an existing primary doctor through id from doctor table 
				String doc = "select id from doctor WHERE name = ?";
				PreparedStatement stmt = con.prepareStatement(doc);
				
				//prepared statement to update patient's address or primary doctor information
	            PreparedStatement ps = con
	                    .prepareStatement("UPDATE patient SET street=?, city=?, state=?, zipcode=?, primaryID=? WHERE patientID=?");
	            ps.setString(1, p.getStreet());
	            ps.setString(2, p.getCity());
	            ps.setString(3, p.getState());
	            ps.setString(4,  p.getZipcode());
	            ps.setString(6, p.getPatientId());
	            stmt.setString(1, p.getPrimaryName());
	            
	            //executes the query and updates values that have been changed
	            ResultSet res = stmt.executeQuery();
	            while(res.next()) {
	            	ps.setString(5, res.getString("id"));
	            }
	            ps.executeUpdate();
	            
		  }catch (SQLException e) {
	            model.addAttribute("message", "SQL Error." + e.getMessage());
	            model.addAttribute("patient", p);
	            return "patient_get";
	        }
		}
		/*
		 * validate primary doctor name and other data update database
		 */
		model.addAttribute("patient", p);
		return "patient_show";
		}
	/*
	 * return JDBC Connection using jdbcTemplate in Spring Server
	 */
	private Connection getConnection() throws SQLException {
		Connection conn = jdbcTemplate.getDataSource().getConnection();
		return conn;
	}

}