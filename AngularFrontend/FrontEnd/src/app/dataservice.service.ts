import { Injectable } from '@angular/core';
import { Pin } from './pinmodel'
//Async
import { Observable } from 'rxjs/Observable';
import { of } from 'rxjs/observable/of';

import { HttpClient, HttpHeaders } from '@angular/common/http';
import { catchError, map, tap } from 'rxjs/operators';

@Injectable()
export class DataserviceService {

  //Change your locate Database here
  private URL:string = 'https://espserver.azurewebsites.net/api/pin';

  constructor(private http: HttpClient) { }

  //GET
  // getPinArray(): Observable<Pin[]> {
  //   try {
  //     return this.http.get<Pin[]>(this.URL).pipe(
  //       //Success
  //       tap(res => console.log(`response = ${JSON.stringify(res)}`)),
  //       //Fail
  //       catchError(error => of([]))
  //     );
  //   } catch (error) {
  //     return of([]);
  //   }
  // }

  //GET
  getPinNumber(pin:number):Observable<Pin>{
    try {
      let URL :string = this.URL + "/" + String(pin);
      console.log("URL: " + URL);
      return this.http.get<Pin>(URL).pipe(
        //Success
        tap(res => console.log(`response = ${JSON.stringify(res)}`)),
        // //Fail
        catchError(error => of(null))
      );
    } catch (error) {
      return null;
    }
  }

  //POST
  changeState(model: Pin): Observable<Pin> {
    try{
      let body = JSON.stringify({
        pin: model.pin,
        state: model.state
      });
      let options = { headers: new HttpHeaders({ 'Content-Type': 'application/json' }) };
      
      return this.http.post<Pin>(this.URL, body, options).pipe(
        //Success
        tap(res => console.log(`changeState response = ${JSON.stringify(res)}`)),
        //Fail
        catchError(error => of(null))
      );
    } catch (error) {
      return null;
    }
  }

  //POST
  turnOffAll(): Observable<String>{
    try{
      let body = "";
      let options = { headers: new HttpHeaders({ 'Content-Type': 'application/json' }) };
      let URL = this.URL + "/resetallpin";
      
      return this.http.post<Pin>(URL, body, options).pipe(
        //Success
        tap(res => console.log(`turnOffAll response = ${res}`)),
        //Fail
        catchError(error => of(error))
      );
    } catch (error) {
      return error;
    }
  }

}

