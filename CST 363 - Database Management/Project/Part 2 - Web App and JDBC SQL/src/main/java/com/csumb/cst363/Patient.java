package com.csumb.cst363;

/*
 * This class is used to transfer data to/from patient templates.
 */
public class Patient {
	
	private String patientId;  // unique id generated by database.
	private String name;
	private String birthdate;  // yyyy-mm-dd
	private String ssn;
	private String street;
	private String city;
	private String state;
	private String zipcode;
	// following fields are data about primary doctor
	private int primaryID;       
	private String primaryName;  
	private String specialty;    
	private String years;        

	
	public String getPatientId() {
		return patientId;
	}
	public void setPatientId(String patientId) {
		this.patientId = patientId;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getBirthdate() {
		return birthdate;
	}
	public void setBirthdate(String birthdate) {
		this.birthdate = birthdate;
	}
	public String getSsn() {
		return ssn;
	}
	public void setSsn(String ssn) {
		this.ssn = ssn;
	}
	public int getPrimaryID() {
		return primaryID;
	}
	public void setPrimaryID(int primaryID) {
		this.primaryID = primaryID;
	}
	public String getPrimaryName() {
		return primaryName;
	}
	public void setPrimaryName(String primaryName) {
		this.primaryName = primaryName;
	}
	public String getSpecialty() {
		return specialty;
	}
	public void setSpecialty(String specialty) {
		this.specialty = specialty;
	}
	public String getYears() {
		return years;
	}
	public void setYears(String years) {
		this.years = years;
	}
	public String getStreet() {
		return street;
	}
	public void setStreet(String street) {
		this.street = street;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public String getState() {
		return state;
	}
	public void setState(String state) {
		this.state = state;
	}
	public String getZipcode() {
		return zipcode;
	}
	public void setZipcode(String zipcode) {
		this.zipcode = zipcode;
	}
	
	@Override
	public String toString() {
		return "Patient [id=" + patientId + ", name=" + name + ", birthdate=" + birthdate + ", ssn=" + ssn + ", primaryID="
				+ primaryID + ", primaryName=" + primaryName + ", specialty=" + specialty + ", years=" + years
				+ ", street=" + street + ", city=" + city + ", state=" + state + ", zipcode=" + zipcode + "]";
	}
	
}
