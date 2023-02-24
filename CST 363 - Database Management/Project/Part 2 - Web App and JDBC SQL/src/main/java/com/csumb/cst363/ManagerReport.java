/*
 * Manager Report: This program helps a pharmacy manager be able to view a specific
 * pharmacy's filled presccriptions from a specific date range using the pharmacy database.
 * CST 363: Intro to Database Systems- Project 2
 * Jennah Yasin & Yukio Rivera
 */
package com.csumb.cst363;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Scanner;
import java.sql.PreparedStatement;

public class ManagerReport {
	public static void main(String[] args)
	{
		String url = "jdbc:mysql://localhost:3306/pharmacy";
        String user = "root";
        String password = "Sultana123!";
    	try (Connection con = DriverManager.getConnection(url, user, password); ){
              con.setAutoCommit(false);
              //creates a keyboard to gather user's input 
              Scanner keyboard = new Scanner(System.in);
              System.out.println("Enter the pharmacy ID ");
              String pharmacyid = keyboard.next();
              System.out.println("Enter a start date: (yyyy-mm-dd) ");
              String startDate = keyboard.next();
              System.out.println("Enter an end date: (yyyy-mm-dd) ");
              String endDate = keyboard.next();
              

              String output = "select trade_name, quantity, date_filled, pharmacyID from prescription NATURAL JOIN drug NATURAL JOIN pharmacy where pharmacyID = ?"
              		 			+ "AND date_filled >=? AND date_filled <=? ORDER BY trade_name";
              //creates a prepared statement to assign the user's input to check the data in the
              //actual tables (randomly generated info from dataGenerate class) 
              PreparedStatement stmt = con.prepareStatement(output);
              stmt.setString(1, pharmacyid );
              stmt.setString(2,  startDate );
              stmt.setString(3,  endDate);
              
              //output information: outputs the prescription info for a specified pharmacy and range of dates 
              //using the user's info and connecting it to the pharmacy database
              ResultSet res = stmt.executeQuery();
              while(res.next()) {
            	  String output1 = res.getString("trade_name");
            	  String output2 = res.getString("quantity");
            	  System.out.println("\nDrug Name: " + output1 + "\nQuantity: " + output2);
              }
           
              con.commit();
        }catch (SQLException e) {
              System.out.println("Error" + e);
        }
	}

}
