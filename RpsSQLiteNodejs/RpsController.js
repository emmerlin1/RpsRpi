module.exports = function(app, db, jsonParser){
    
//    var fields = ["EmployeeID", "LastName", "FirstName", "Title", "TitleOfCourtesy",
//                  "BirthDate", "HireDate", "Address", "City", "Region", "PostalCode",
//                  "Country", "HomePhone", "Extension"];

//                  "BirthDate", "HireDate", "Address", "City", "Region", "PostalCode",
//                  "Country", "HomePhone", "Extension"];

    var fields = ["count", "rpslowerend", "hundredth"];
    var tablename = "rpmentry_00001";
    db.all("SELECT name FROM sqlite_master WHERE type='table' ORDER BY name asc", function(err, rows) {
       //console.log(rows[rows.length-1].name);
       tablename = rows[rows.length-1].name;
       //console.log(tablename);
    });

    console.log("Registering endpoint: /api/rps");
    app.get('/api/rps', function(req, res){
//        console.log("SELECT " + fields.join(", ") + " FROM " + tablename);
        db.all("SELECT " + fields.join(", ") + " FROM " + tablename, function(err, rows) {
            res.json(rows); 
        });                       
    });
}