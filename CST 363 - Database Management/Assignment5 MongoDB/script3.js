map1 = function() 
{
    emit (0, {qty: this.value, count: 1});
};

reduce1 = function(key, values)
{
    valueReduced = { count: 0, qty: 0 };
    for (let i = 0; i < values.length; i++) 
    {
        valueReduced.count += values[i].count;
        valueReduced.qty += values[i].qty;
    }
    return valueReduced;
 };

var function1 = function (key, valueReduced) 
{
    valueReduced.avg = valueReduced.qty/valueReduced.count;
    return valueReduced;
};

db.map_reduce.mapReduce(map1, reduce1, { out: "script3", finalize: function1 });

map2 = function()
{
    for (let k = 0; k < this.items.length; k++) 
    {
        emit(this.orderId, this.items[k].qty);
    }
};

reduce2 = function(key, values)
{
    count = 0;
    for (x of values) 
    {
        count += x;
    }
    return (key, count);
};

db.orders.mapReduce(map2, reduce2, {out: "map_reduce"});

printer = db.script3.find();

while(printer.hasNext()) 
{
    printjson(printer.next())
}