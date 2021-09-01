/* Webpage HTML - this is for failed page (OTA failure or other) */ 

#ifndef failed_h
#define failed_h

const char failed_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% FAIL</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    %The_CSS%

  </head>

    <div id="container">

      <div id="header">
        <h2>%title% - <em>FAIL</em></h2>
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
       
        <div class = "border">
        <h3 align=center>Oh No!!!</h3>
        <h3 align=center></h3>
        <h3 align=center>It Borked!!!</h3>
        <h3 align=center></h3>
        <h3 align=center>What'd ya try to do?</h3>
        </div>
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
