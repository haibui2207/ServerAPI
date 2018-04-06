
# TUTORIAL USING SERVER API
**

> TEST USING POSTMAN

**

## # PinController :http://localhost:xxxxx/api/pin
>
>PinModel
>{
	int pin; // 1 to 20
	int state;  // 0 or 1 default 0
>}

### # GET ALL
>URL : http://localhost:xxxxx/api/pin
Method : GET

### #GET A PIN ( example pin = 15 )
>URL : http://localhost:xxxxx/api/pin/15
Method : GET

### #CHANGE STATE OF PIN
### 
>URL : http://localhost:xxxxx/api/pin
Method : POST
BODY:
{
	"pin": 16,
	"state": 1
}


----------
## # UserController :http://localhost:xxxxx/api/user
>
>PinModel
>{
	int id;
	string name;
	string rfid;
>}

### # GET A User Using RFID Code
>URL : http://localhost:xxxxx/api/user/{RFID Code}
Method : GET

### #ADD NEW USER
### 
>URL : http://localhost:xxxxx/api/user
Method : POST
BODY:
{
	"name": "ABC",
	"rfid": "CODE"
}

### #REMOVE A USER
### 
>URL : http://localhost:xxxxx/api/user
Method : DELETE
BODY:
{
	"name": "ABC",
	"rfid": "CODE"
}


