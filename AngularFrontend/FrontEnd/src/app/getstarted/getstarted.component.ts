import { Component, OnInit } from '@angular/core';
import { Pin } from '../pinmodel';
import { DataserviceService } from '../dataservice.service';

@Component({
  selector: 'app-getstarted',
  templateUrl: './getstarted.component.html',
  styleUrls: ['./getstarted.component.css']
})
export class GetstartedComponent implements OnInit {
  // pinArray: Pin[];  
  selectedItem: number = 4;  //Default as LIGHT
  currentState: number = 0;
  changedPin: Pin;
  getPin : Pin;

  constructor(private dataService: DataserviceService) { }

  ngOnInit() {
    setInterval(() => this.getPinNumber(this.selectedItem), 2000);    
  }

  // getPinArray() {
  //   this.dataService.getPinArray().subscribe(
  //     res => this.pinArray = res
  //   );
  // }

  getItemSeleted(event) {
    this.selectedItem = event.target.value;
    console.log(`selectedItem: ` + this.selectedItem.toString());
    this.getPinNumber(this.selectedItem);
  }

  getPinNumber(pin:number) {
    this.dataService.getPinNumber(pin).subscribe(
      res => { this.getPin = res ; 
         this.currentState = this.getPin.state;
         console.log(`getPinNumber Response: ${JSON.stringify(res)}`);},
      err => console.log(`getPinNumber Error : ` + err.toString())
    );
  }

  turnOn() {
    let pin : Pin = new Pin();
    pin.pin = this.selectedItem;
    pin.state = 1;
    this.currentState = 1;
    console.log(`turnOn pin : ${JSON.stringify(pin)}`);

    if(this.getPin  !=null){
      this.dataService.changeState(pin).subscribe(
        res => this.changedPin = res,
        err => console.log(`turnOn Error : ` + err.toString())
      );
    } 
    else{
      console.log("getPin NULL");
    }
  }

  turnOff() {
    let pin : Pin = new Pin();
    pin.pin = this.selectedItem;
    pin.state = 0;
    this.currentState = 0;
    console.log(`turnOff pin : ` + pin);

    this.dataService.changeState(pin).subscribe(
      res => this.changedPin = res,
      err => console.log(`turnOff Error : ` + err.toString())
    );   
  }

  turnOffAll() {
      this.dataService.turnOffAll().subscribe(
        res => this.currentState = 0,
        err => console.log(`turnOffAll Error : ` + err.toString())
      );
  }
}
