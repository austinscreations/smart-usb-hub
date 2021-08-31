/* Webpage HTML - this is for management page (OTA update)*/ 

#ifndef management_h
#define management_h

const char management_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html5>
<html>
  <head>
    <title>%title% Management</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="icon" href="data:,">

    %The_CSS%

  </head>
  <body>
    <div id="container">

      <div id="header">
        <h2>%title% - <em>Management</em></h2>
        <div class = "menu-buttons">
          <div class = "buttons ButtonClickable">
           <button1 onclick="location.href='/home'">Home</button1>
          </div>
          <div class = "buttons ButtonHere">
           <button2>Management</button2>
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
       <div class="col-12 mt-3 p-centered">
           <label class="label label2 mr-2">Upload Firmware Here</label>
           <div class="form-group pt-2 mt-3">
             <form method="POST" action="#" enctype="multipart/form-data" id="upload_form">
               <input type="file" name="update" id="file" accept=".bin" class="form-input file-input">
               <input type="submit" value="FLASH">
               <div class="upload-bar">
                 <div class="w3-background">
                   <div class="w3-progress" id="prg1" style="width: 0rem">
                     <span class="percent" id="prg">-</span>
                 </div>
               </div>
             </form>
           </div>
         </div>
       </div>
     </div>

     </br>
     <div class = "border">
        <div class = "name-host">
          <span class = "name-text">IP Address:</name-text></span>
          <span class = "host">%ipplaceholder%</host></span>
        </div>

        <div class = "name-mac">
          <span class = "name-text">MAC Address:</name-text></span>
          <span class = "host">%macplaceholder%</host></span>
        </div>

        <div class = "name-sketch">
          <span class = "name-text">Memory - Sketch Size: </name-text></span>
          <span class = "host">%memsketch%</host></span>
        </div>
        </div> <!-- Border -->
        
       <div class = "menu-buttons">
         <div class = "border">
           <div class = "buttons ButtonClickable">
             <button5 onclick="location.href='/reboot'">%processorplaceholder% Reboot</button5>
           </div>
         </div>
       </div>

       <div class = "menu-buttons">
         <div class = "border">
           <div class = "buttons ButtonClickable">
             <button6 onclick="location.href='/factory'">Factory Reset</button6>
           </div>
         </div>
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
   
   function darkFunction() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", "/darkmode?state=1", true);
       xhr.send();
       setTimeout(function () {window.location.reload();}, 100);
      }


            function checkConnectionStatus()
{
    let xhttp = new XMLHttpRequest();
    xhttp.timeout = 2000;
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4)
        {
            if (this.status === 200)
            {
                document.getElementById("state").style.background = this.responseText;
            }
            else
            {
                document.getElementById("state").style.background = "red";
            }
             setTimeout(checkConnectionStatus, 5000);
            // Repeat our status check only once there's a result
        }
    }
    xhttp.open("GET", "/state", true);
    xhttp.send();
}
// Initial status check
setTimeout(checkConnectionStatus, 5000);

var domReady = function(callback) {
       document.readyState === "interactive" || document.readyState === "complete" ? callback() : document.addEventListener("DOMContentLoaded", callback);
      };

     domReady(function() {
       var myform = document.getElementById('upload_form');
       var filez  = document.getElementById('file');

       myform.onsubmit = function(event) {
         event.preventDefault();

         var formData = new FormData();
         var file     = filez.files[0];

         if (!file) { return false; }

         formData.append("files", file, file.name);

         var xhr = new XMLHttpRequest();
         xhr.upload.addEventListener("progress", function(evt) {
           if (evt.lengthComputable) {
             var per  = Math.round((evt.loaded / evt.total) * 100);
             var per1 = Math.round(per/4);
             var prg  = document.getElementById('prg');
             var prg1 = document.getElementById('prg1');

             prg1.style.width  = per1 + "rem"
             prg.innerHTML     = per + "%"
            }
          }, false);
          xhr.open('POST', location.href, true);

         // Set up a handler for when the request finishes.
         xhr.onload = function () {
           if (xhr.status === 200) {
             //alert('Success');
             window.location.href = "/complete";
            } else {
             //alert('An error occurred!');
             window.location.href = "/failedOTA";
            }
          };

         xhr.send(formData);
        }
      });
   
   </script>
   )rawliteral";

#endif
