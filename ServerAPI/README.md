

# TUTORIAL USING SERVER API <br/>
**

> TEST USING POSTMAN <br/>

**

----------
## # PinController :http://localhost:xxxxx/api/pin <br/>
----------
>PinModel <br/> 

    {
    	int pin; // 1 to 20 
    	int state;  // 0 or 1 default 0 
    } 

### # GET ALL <br/>
>URL : http://localhost:xxxxx/api/pin <br/>
Method : GET <br/>

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

