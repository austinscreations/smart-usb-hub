/* Webpage HTML - this is for factory reset*/ 

#ifndef factory_html_h
#define factory_html_h

const char factory_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% RESET</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    %The_CSS%

  </head>

    <div id="container">

      <div id="header">
        <h2>%title% - <em>RESET</em></h2>
        <div class = "menu-buttons">
          <div class = "buttons ButtonClickable">
            <Button1 onclick="location.href='/home'">Home</button1>
          </div>
          <div class = "buttons ButtonClickable">
            <Button2 onclick="location.href='/management'">Management</button2>
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
        
       </br>
       
        <div class = "border">
        
        <h3 align=center>Factory Reset Performed</h3>
        <h3 align=center></h3>
        <h3 align=center>The device Will Now Be In AP Mode</h3>
        <h3 align=center></h3>
        <span class = "host">Navigate to %IDfactory% in wifi settings on mobile</host></span></br></br>
        <span class = "host">Once Connected to AP Navigate to 192.168.4.1 in Browser</host></span></br></br>
        <span class = "host">Visit the Config page</host></span></br></br>
        <span class = "host">Enter new Configuration</host></span></br></br>
        <span class = "host">Upon save the device will connect to specified WiFi SSID</host></span></br></br>
        
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
   </script>
 </body>
</html>
)rawliteral";
#endif
