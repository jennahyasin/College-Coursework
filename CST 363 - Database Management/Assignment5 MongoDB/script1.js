// #1 & 2
 db.patients.insert({name: "Bob", ssn: 111111111, age: 10, address: "123 Main Street"})
 db.patients.insert({name: "Sam", ssn: 222222222, age: 20, address: "Mesa Rd"})
 db.patients.insert({name: "Sally", ssn: 33333333, age: 30, address: "First St", prescriptions  : [
                 { id: "RX743009", tradename : "Hydrochlorothiazide"   },
                 { id : "RX656003", tradename : "LEVAQUIN", formula : "levofloxacin"  }
                ]})


// #3
printer1 = db.patients.find();
while(printer1.hasNext()) 
{
    printjson(printer1.next())
}

// #4
db.patients.find({age: 20});

// #5
db.patients.find({age: {$lt: 25}});

// #6
db.patients.drop()

