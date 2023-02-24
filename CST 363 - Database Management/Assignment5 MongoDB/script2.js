
 mapf = function() 
 {
     p = (this.address.zip.startsWith('9'));
     emit(this.address.zip, p); 
 }

 reducef = function(key, values) 
 {
      count = 0;
      for(x of values) 
      { 
         count = count + x;
      } 
      return count;
 }

 db.customers.mapReduce(mapf, reducef, {out: "script2"});
 printer = db.script2.find({value: { "$gte": 1}})

 while ( printer.hasNext()) 
 {
    printjson(printer.next());
 }