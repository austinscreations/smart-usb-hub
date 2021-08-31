/* Webpage HTML - this is the homepage*/ 

#ifndef homepage_h
#define homepage_h

const char home_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Home</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">
    <meta http-equiv="expires" content="0">
    
    %The_CSS%

   </head>
  <body>
  
    <div id="container">

      <div id="header">
        <h2>%title% - <em>Home</em></h2>
        <div class = "menu-buttons">
          <div class = "buttons ButtonHere">
            <Button1>Home</button1>
          </div>
          <div class = "buttons ButtonClickable">
           <button2 onclick="location.href='/management'">Management</button2>
          </div>
          <div class = "buttons ButtonClickable">
            <Button3 onclick="location.href='/config'">Config</button3>
          </div>
          <div class = "buttons ButtonClickable">
           <button4 onclick="darkFunction()">Dark Mode</button4>
          </div>
        </div>
      </div>  <!-- HEADER -->

      <div id="body"> 
      

      <div class = "name-status" id="state" style="%online%">
       <span class = "name-text">ONLINE</name-text></span>
      </div>

      <div class = "border">
            
        <div class = "name-host">
          <span class = "name-text">IP Address: </name-text></span>
          <span class = "host">%ipplaceholder%</host></span>
        </div>

        <div class = "name-mac">
          <span class = "name-text">MAC Address: </name-text></span>
          <span class = "host">%macplaceholder%</host></span>
        </div>

        <div class = "name-sketch">
          <span class = "name-text">Memory - Sketch Size: </name-text></span>
          <span class = "host">%memsketch%</host></span>
        </div>

        </div> <!-- border -->

        </br>
        
        <div class = "border">
        
  <div class = "menu-menu">
    <div class = "menu-main">
      <div class = "outer">
        <div class = "status" id="status1" style="border-color: grey">
          <div class = "inner">
            <div class = "row">
              <div class = "column3" id="port1">
                <div class ="text">Volts:</div>
                <div class ="text">Amps:</div>
                <div class ="text"><p></p></div>
                <div class ="text">Power:</div>
                <div class ="text">Data:</div>
              </div> <!-- column3 -->
        
              <div class = "column4">
                <div class ="text" id="volt1">--- V</div>
                <div class ="text" id="ma1">---- mA</div>
                <div class ="text"><p></p></div>
                <div class ="text" id="p1">-------</div>
                <div class ="text" id="d1">-------</div>
              </div> <!-- column4 -->
            </div> <!-- row -->
       
            
            <div class = "buttons ButtonClickable">
              <button-1 onmousedown="mouseDown(1)" onmouseup="mouseUp(1)">Button 2</button-1>
            </div> <!-- buttons ButtonClickable -->
          </div> <!-- inner -->
        </div> <!-- status -->
      </div> <!-- outer -->
      
      <div class = "outer">
        <div class = "status" id="status0" style="border-color: grey">
          <div class = "inner">
            <div class = "row">
              <div class = "column3" id="port0">
                <div class ="text">Volts:</div>
                <div class ="text">Amps:</div>
                <div class ="text"><p></p></div>
                <div class ="text">Power:</div>
                <div class ="text">Data:</div>
              </div> <!-- column3 -->
        
              <div class = "column4">
                <div class ="text" id="volt0">--- V</div>
                <div class ="text" id="ma0">---- mA</div>
                <div class ="text"><p></p></div>
                <div class ="text" id="p0">-------</div>
                <div class ="text" id="d0">-------</div>
              </div> <!-- column4 -->
            </div> <!-- row -->
      
            <div class = "buttons ButtonClickable">
              <button-0 onmousedown="mouseDown(0)" onmouseup="mouseUp(0)" >Button 1</button-0>
            </div> <!-- buttons ButtonClickable -->
          </div> <!-- inner -->
        </div> <!-- status -->
      </div> <!-- outer -->
    </div> <!-- menu-main -->
   
   
    <div class = "menu-main">
      <div class = "outer">
        <div class = "status" id="status3" style="border-color: grey">
          <div class = "inner">
            <div class = "row">
              <div class = "column3" id="port3">
                <div class ="text">Volts:</div>
                <div class ="text">Amps:</div>
                <div class ="text"><p></p></div>
                <div class ="text">Power:</div>
                <div class ="text">Data:</div>
              </div> <!-- column3 -->
        
              <div class = "column4">
                <div class ="text" id="volt3">--- V</div>
                <div class ="text" id="ma3">---- mA</div>
                <div class ="text"><p></p></div>
                <div class ="text" id="p3">------</div>
                <div class ="text" id="d3">------</div>
              </div> <!-- column4 -->
            </div> <!-- row -->
      
            <div class = "buttons ButtonClickable">
              <button-3 onmousedown="mouseDown(3)" onmouseup="mouseUp(3)" >Button 4</button-3>
            </div> <!-- buttons ButtonClickable -->
          </div> <!-- inner -->
        </div> <!-- status -->
      </div> <!-- outer -->
     
      <div class = "outer">
        <div class = "status" id="status2" style="border-color: grey">
          <div class = "inner">
            <div class = "row">
              <div class = "column3" id="port2">
                <div class ="text">Volts:</div>
                <div class ="text">Amps:</div>
                <div class ="text"><p></p></div>
                <div class ="text">Power:</div>
                <div class ="text">Data:</div>
              </div> <!-- column3 -->
        
              <div class = "column4">
                <div class ="text" id="volt2">--- V</div>
                <div class ="text" id="ma2">---- mA</div>
                <div class ="text"><p></p></div>
                <div class ="text" id="p2">------</div>
                <div class ="text" id="d2">------</div>
              </div> <!-- column4 -->
            </div> <!-- row -->
      
            <div class = "buttons ButtonClickable">
              <button-2 onmousedown="mouseDown(2)" onmouseup="mouseUp(2)" >Button 3</button-2>
            </div> <!-- buttons ButtonClickable -->
          </div> <!-- inner -->
        </div> <!-- status -->
      </div> <!-- outer -->
    </div> <!-- menu-main -->
  </div> <!-- menu-menu -->
            
</div> <!-- Border -->

        </br>
        
      </div>  <!-- BODY -->

      <div id="footer">
        <div class="columns mt-10">
          <span class="label label-rounded label-blank"></span> 
          <div class="columns mt-8">
            <div class="columns mt-4">
              <div class="col-12 text-center">
                <span class="label label-rounded mr-2">%IDplaceholder%</span> 
                -
                <span class="label label-rounded label-primary ml-2">%processorplaceholder%</span>
                -
                <span class="label label-rounded mr-2">%type%</span>
              </div>
            </div> 
            <div class="columns mt-8">
              <span class="label label-rounded label-error">%errorplaceholder%</span> 
            </div>
          </div>
        </div>
      </div>  <!-- FOOTER -->
    </div>

    <script>
    
     %The_SCRIPTS%

  function mouseDown(x) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/pressed?ID="+x, true);
    xhr.send();
  }

  function mouseUp(x) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/released?ID="+x, true);
    xhr.send();
  }
      
      function darkFunction() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", "/darkmode?state=1", true);
       xhr.send();
       setTimeout(function () {window.location.reload();}, 100);
      }


   var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage;
  }
  
  function onOpen(event) {
    console.log('Connection opened');
  }

  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }

  function onMessage(event) {
    <!-- console.log(event.data); -->
    var res = JSON.parse(event.data);
    document.getElementById('status0').style.borderColor = res.border0;
    document.getElementById('port0').style.color = res.port0;
    document.getElementById('volt0').style.color = res.voltstyle0;
    document.getElementById('volt0').innerHTML = res.volt0;
    document.getElementById('ma0').style.color = res.mastyle0;
    document.getElementById('ma0').innerHTML = res.ma0;
    document.getElementById('p0').innerHTML = res.p0;
    document.getElementById('d0').innerHTML = res.d0;

    document.getElementById('status1').style.borderColor = res.border1;
    document.getElementById('port1').style.color = res.port1;
    document.getElementById('volt1').style.color = res.voltstyle1;
    document.getElementById('volt1').innerHTML = res.volt1;
    document.getElementById('ma1').style.color = res.mastyle1;
    document.getElementById('ma1').innerHTML = res.ma1;
    document.getElementById('p1').innerHTML = res.p1;
    document.getElementById('d1').innerHTML = res.d1;

    document.getElementById('status2').style.borderColor = res.border2;
    document.getElementById('port2').style.color = res.port2;
    document.getElementById('volt2').style.color = res.voltstyle2;
    document.getElementById('volt2').innerHTML = res.volt2;
    document.getElementById('ma2').style.color = res.mastyle2;
    document.getElementById('ma2').innerHTML = res.ma2;
    document.getElementById('p2').innerHTML = res.p2;
    document.getElementById('d2').innerHTML = res.d2;

    document.getElementById('status3').style.borderColor = res.border3;
    document.getElementById('port3').style.color = res.port3;
    document.getElementById('volt3').style.color = res.voltstyle3;
    document.getElementById('volt3').innerHTML = res.volt3;
    document.getElementById('ma3').style.color = res.mastyle3;
    document.getElementById('ma3').innerHTML = res.ma3;
    document.getElementById('p3').innerHTML = res.p3;
    document.getElementById('d3').innerHTML = res.d3;
   }
  
  window.addEventListener('load', onLoad);
  
  function onLoad(event) {
    initWebSocket();
  }

    </script>

  </body>
</html>
)rawliteral";

#endif
