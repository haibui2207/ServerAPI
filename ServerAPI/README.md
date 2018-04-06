
# TUTORIAL USING SERVER API <br/>
**

> TEST USING POSTMAN <br/>

**

## # PinController :http://localhost:xxxxx/api/pin <br/>
> <br/>
>PinModel <br/> 
>{
	int pin; // 1 to 20 <br/>
	int state;  // 0 or 1 default 0 <br/>
>} <br/>

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
{ <br/>
	"pin": 16, <br/>
	"state": 1 <br/>
} <br/>


----------
## # UserController :http://localhost:xxxxx/api/user <br/>
> <br/>
>PinModel <br/>
>{ <br/>
	int id; <br/>
	string name; <br/>
	string rfid; <br/>
>} <br/>

### # GET A User Using RFID Code <br/>
>URL : http://localhost:xxxxx/api/user/{RFID Code} <br/>
Method : GET <br/>

### #ADD NEW USER <br/>
>URL : http://localhost:xxxxx/api/user <br/>
Method : POST <br/>
BODY: <br/>
{ <br/>
	"name": "ABC", <br/>
	"rfid": "CODE" <br/>
} <br/>
 
### #REMOVE A USER <br/>
>URL : http://localhost:xxxxx/api/user <br/>
Method : DELETE <br/>
BODY: <br/>
{ <br/>
	"name": "ABC", <br/>
	"rfid": "CODE" <br/>
} <br/>