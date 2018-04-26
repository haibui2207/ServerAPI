

# TUTORIAL USING SERVER API REQUIRE SQL<br/>
----------

# > SETUP SQL <br/>

----------
## Step 1 : Install EntityCoreFramework and build Database
Open Tools => NuGet Package Manager => Package Manager Console
- Install-Package Microsoft.EntityFrameworkCore.SqlServer -Version 2.0.2
- Install-Package Microsoft.EntityFrameworkCore.Tools
- Update-Database

## Step 2 : Insert data from file SeedData.cs
You only run project after Step 1 it will auto insert data contain inside SeedData.cs into new created database and run only once first time.
If step 1 skipped , perhaps throw error because no DB founded


----------

# > TEST USING POSTMAN <br/>

----------

----------
## # PinController :http://localhost:xxxxx/api/pin <br/>
----------
>PinModel <br/> 

    {
    	int pin; // 1 to 20 
    	int state;  // 0 or 1 default 0 
    } 

### # GET ALL PIN<br/>
>URL : http://localhost:xxxxx/api/pin <br/>
Method : GET <br/>

### # RESET ALL PIN<br/>
>URL : http://localhost:xxxxx/api/pin/resetallpin <br/>
Method : POST <br/>

### #GET A PIN ( example pin = 15 ) <br/>
>URL : http://localhost:xxxxx/api/pin/15 <br/>
Method : GET <br/>

### #CHANGE STATE OF PIN <br/>
>URL : http://localhost:xxxxx/api/pin <br/>
Method : POST <br/>
BODY: <br/>

    {     	
        "pin": 16, 
    	"state": 1 
    } 

----------
## # UserController :http://localhost:xxxxx/api/user <br/>
----------
>PinModel <br/>

    { 
    	int id; 
    	string name; 
    	string rfid; 
    } 

### # GET A User Using RFID Code <br/>
>URL : http://localhost:xxxxx/api/user/{RFID Code} <br/>
Method : GET <br/>

### #ADD NEW USER <br/>
>URL : http://localhost:xxxxx/api/user <br/>
Method : POST <br/>
BODY: <br/>

	{ 
		"name": "ABC",
		"rfid": "CODE"
	} 
 
### #REMOVE A USER <br/>
>URL : http://localhost:xxxxx/api/user <br/>
Method : DELETE <br/>
BODY: <br/>

    { 
    	"name": "ABC", 
    	"rfid": "CODE" 
    } 

